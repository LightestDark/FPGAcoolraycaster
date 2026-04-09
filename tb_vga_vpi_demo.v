`timescale 1ns/1ps

module tb_vga_vpi_demo;
    reg clk_25;
    reg rst;
    reg move_fwd;
    reg move_back;
    reg turn_left;
    reg turn_right;
    reg strafe_left;
    reg strafe_right;
    reg manual_enable;

    wire hsync;
    wire vsync;
    wire [3:0] vga_r;
    wire [3:0] vga_g;
    wire [3:0] vga_b;
    wire active;
    wire [9:0] hc;
    wire [9:0] vc;

    integer keymask;
    integer last_keymask;

    vga_raycast_demo uut (
        .clk_25(clk_25),
        .rst(rst),
        .move_fwd(move_fwd),
        .move_back(move_back),
        .turn_left(turn_left),
        .turn_right(turn_right),
        .strafe_left(strafe_left),
        .strafe_right(strafe_right),
        .manual_enable(manual_enable),
        .active(active),
        .hc(hc),
        .vc(vc),
        .hsync(hsync),
        .vsync(vsync),
        .vga_r(vga_r),
        .vga_g(vga_g),
        .vga_b(vga_b)
    );

    initial clk_25 = 1'b0;
    always #20 clk_25 = ~clk_25;

    task apply_keys;
        begin
            move_fwd = (keymask >> 0) & 1;
            move_back = (keymask >> 1) & 1;
            turn_left = (keymask >> 2) & 1;
            turn_right = (keymask >> 3) & 1;
            strafe_left = (keymask >> 4) & 1;
            strafe_right = (keymask >> 5) & 1;
        end
    endtask

    always @(posedge clk_25) begin
        if (!rst && hc == 10'd799) begin
            // Sample keys once per scanline for more responsive input.
            keymask = 0;
            $kbd(keymask);
            apply_keys();
            if (keymask != last_keymask) begin
                $display("keymask=%0h fwd=%0d back=%0d left=%0d right=%0d strL=%0d strR=%0d", keymask,
                         move_fwd, move_back, turn_left, turn_right, strafe_left, strafe_right);
                last_keymask = keymask;
            end
            if ((keymask >> 6) & 1) begin
                $display("Exiting on ESC");
                $finish;
            end
        end
    end

    initial begin
        $dumpfile("vga_vpi_demo.vcd");
        $dumpvars(0, tb_vga_vpi_demo);
        move_fwd = 0;
        move_back = 0;
        turn_left = 0;
        turn_right = 0;
        strafe_left = 0;
        strafe_right = 0;
        manual_enable = 1'b1;
        last_keymask = 0;

        rst = 1'b1;
        #100;
        rst = 1'b0;
    end
endmodule
