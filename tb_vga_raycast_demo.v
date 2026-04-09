`timescale 1ns/1ps

module tb_vga_raycast_demo;
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
    reg [11:0] first_rgb;
    reg got_first;
    reg saw_variation;
    integer fallback_red_count;
    integer sample_count;
    integer errors;

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
        if (!rst) begin
            if (active && vc == 10'd240) begin
                if (hc == 10'd80 || hc == 10'd160 || hc == 10'd320 || hc == 10'd480 || hc == 10'd560) begin
                    sample_count = sample_count + 1;
                    if (!got_first) begin
                        first_rgb = {vga_r, vga_g, vga_b};
                        got_first = 1'b1;
                    end else if ({vga_r, vga_g, vga_b} != first_rgb) begin
                        saw_variation = 1'b1;
                    end

                    if (vga_r == 4'd15 && vga_g == 4'd0 && vga_b == 4'd0) begin
                        fallback_red_count = fallback_red_count + 1;
                    end
                end
            end
        end
    end

    initial begin
        $dumpfile("vga_raycast_demo.vcd");
        $dumpvars(0, tb_vga_raycast_demo);

        move_fwd = 0;
        move_back = 0;
        turn_left = 0;
        turn_right = 0;
        strafe_left = 0;
        strafe_right = 0;
        got_first = 1'b0;
        saw_variation = 1'b0;
        fallback_red_count = 0;
        sample_count = 0;
        errors = 0;

        rst = 1'b1;
        #100;
        rst = 1'b0;

        move_fwd = 1'b1;
        turn_right = 1'b1;

        // Run for two full frames so movement updates and screen samples are captured.
        #(800 * 525 * 40 * 2);

        move_fwd = 1'b0;
        turn_right = 1'b0;

        if (sample_count < 5) errors = errors + 1;
        if (!saw_variation) errors = errors + 1;
        if (fallback_red_count != 0) errors = errors + 1;
        if (uut.player_x == 16'd384 || uut.cam_angle == 8'd0) errors = errors + 1;

        if (errors == 0) begin
            $display("PASS tb_vga_raycast_demo");
        end else begin
            $display("FAIL tb_vga_raycast_demo errors=%0d samples=%0d fallback_red=%0d", errors, sample_count, fallback_red_count);
        end

        $finish;
    end
endmodule
