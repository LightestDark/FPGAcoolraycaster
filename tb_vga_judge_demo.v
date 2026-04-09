`timescale 1ns/1ps

module tb_vga_judge_demo;
    reg clk_25;
    reg rst;
    reg move_fwd;
    reg move_back;
    reg turn_left;
    reg turn_right;
    reg strafe_left;
    reg strafe_right;

    wire hsync;
    wire vsync;
    wire [3:0] vga_r;
    wire [3:0] vga_g;
    wire [3:0] vga_b;
    wire active;
    wire [9:0] hc;
    wire [9:0] vc;

    integer errors;
    integer samples;
    reg [11:0] first_rgb;
    reg got_first;
    reg saw_change;
    reg [15:0] start_x;
    reg [15:0] start_y;
    reg [7:0] start_a;

    vga_raycast_demo uut (
        .clk_25(clk_25),
        .rst(rst),
        .move_fwd(move_fwd),
        .move_back(move_back),
        .turn_left(turn_left),
        .turn_right(turn_right),
        .strafe_left(strafe_left),
        .strafe_right(strafe_right),
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

    always @(posedge clk_25) begin
        if (!rst && active && vc == 10'd240) begin
            if (hc == 10'd80 || hc == 10'd160 || hc == 10'd320 || hc == 10'd480 || hc == 10'd560) begin
                samples = samples + 1;
                if (!got_first) begin
                    first_rgb = {vga_r, vga_g, vga_b};
                    got_first = 1'b1;
                end else if ({vga_r, vga_g, vga_b} != first_rgb) begin
                    saw_change = 1'b1;
                end
            end
        end
    end

    initial begin
        $dumpfile("vga_judge_demo.vcd");
        $dumpvars(0, tb_vga_judge_demo);

        // No manual controls: auto-demo mode should move and turn by itself.
        move_fwd = 0;
        move_back = 0;
        turn_left = 0;
        turn_right = 0;
        strafe_left = 0;
        strafe_right = 0;

        errors = 0;
        samples = 0;
        got_first = 0;
        saw_change = 0;

        rst = 1;
        #100;
        rst = 0;

        start_x = uut.player_x;
        start_y = uut.player_y;
        start_a = uut.cam_angle;

        // Run three full frames.
        #(800 * 525 * 40 * 3);

        if (uut.player_x == start_x && uut.player_y == start_y) errors = errors + 1;
        if (uut.cam_angle == start_a) errors = errors + 1;
        if (samples < 5) errors = errors + 1;
        if (!saw_change) errors = errors + 1;

        if (errors == 0) begin
            $display("PASS tb_vga_judge_demo player=(%0d,%0d) angle=%0d", uut.player_x, uut.player_y, uut.cam_angle);
        end else begin
            $display("FAIL tb_vga_judge_demo errors=%0d player=(%0d,%0d) angle=%0d", errors, uut.player_x, uut.player_y, uut.cam_angle);
        end

        $finish;
    end
endmodule
