`timescale 1ns/1ps

module tb_vga_frame_dump;
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

    integer fd;
    integer pixel_count;
    integer frame_count;
    reg capture_en;

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

    // Capture one full visible frame to a PPM image file.
    always @(posedge clk_25) begin
        if (!rst && hc == 10'd0 && vc == 10'd0)
            frame_count <= frame_count + 1;

        if (!rst && frame_count == 2 && !capture_en && hc == 10'd0 && vc == 10'd0) begin
            fd = $fopen("judge_frame.ppm", "w");
            $fwrite(fd, "P3\n640 480\n255\n");
            pixel_count = 0;
            capture_en = 1'b1;
        end

        if (capture_en && hc < 10'd640 && vc < 10'd480) begin
            $fwrite(fd, "%0d %0d %0d\n", vga_r * 17, vga_g * 17, vga_b * 17);
            pixel_count = pixel_count + 1;
            if (pixel_count == 640*480) begin
                $fclose(fd);
                $display("PASS tb_vga_frame_dump wrote judge_frame.ppm (%0d pixels)", pixel_count);
                $finish;
            end
        end
    end

    initial begin
        $dumpfile("vga_frame_dump.vcd");
        $dumpvars(0, tb_vga_frame_dump);

        move_fwd = 1'b0;
        move_back = 1'b0;
        turn_left = 1'b0;
        turn_right = 1'b0;
        strafe_left = 1'b0;
        strafe_right = 1'b0;
        manual_enable = 1'b0;

        frame_count = 0;
        pixel_count = 0;
        capture_en = 1'b0;

        rst = 1'b1;
        #100;
        rst = 1'b0;
    end
endmodule
