`timescale 1ns/1ps

module tb_vga_frame_sequence;
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

    integer pixel_count;
    integer frame_index;
    reg capture_en;

    // Keep the capture short and fast for demo runs.
    localparam FRAMES = 20;

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

    task set_controls;
        input integer idx;
        begin
            move_fwd = 0;
            move_back = 0;
            turn_left = 0;
            turn_right = 0;
            strafe_left = 0;
            strafe_right = 0;

            if (idx < 2) begin
                move_fwd = 1;
            end else if (idx < 4) begin
                move_fwd = 1;
                turn_right = 1;
            end else if (idx < 6) begin
                strafe_right = 1;
            end else begin
                move_fwd = 1;
                turn_left = 1;
            end
        end
    endtask

    localparam SAMPLE_SHIFT = 3;
    localparam CAP_W = 640 >> SAMPLE_SHIFT;
    localparam CAP_H = 480 >> SAMPLE_SHIFT;
    localparam FPS = 8;

    // Stream frames to ffmpeg via VPI. Downsample for faster dumps.
    always @(posedge clk_25) begin
        if (!rst && hc == 10'd0 && vc == 10'd0) begin
            if (!capture_en && frame_index < FRAMES) begin
                if (frame_index == 0) begin
                    $vpi_video_start(CAP_W, CAP_H, FPS, "raycast.mp4");
                end
                pixel_count = 0;
                capture_en = 1'b1;
                set_controls(frame_index);
            end
        end

        if (capture_en && hc < 10'd640 && vc < 10'd480) begin
            if (hc[SAMPLE_SHIFT-1:0] == {SAMPLE_SHIFT{1'b0}} &&
                vc[SAMPLE_SHIFT-1:0] == {SAMPLE_SHIFT{1'b0}}) begin
                $vpi_video_pixel(vga_r * 17, vga_g * 17, vga_b * 17);
                pixel_count = pixel_count + 1;
            end
            if (pixel_count == CAP_W*CAP_H) begin
                capture_en = 1'b0;
                $display("frame %0d/%0d captured", frame_index + 1, FRAMES);
                frame_index = frame_index + 1;
                if (frame_index == FRAMES) begin
                    $vpi_video_end();
                    $display("PASS tb_vga_frame_sequence wrote %0d frames", FRAMES);
                    $finish;
                end
            end
        end
    end

    initial begin
        $dumpfile("vga_frame_sequence.vcd");
        $dumpvars(0, tb_vga_frame_sequence);
        move_fwd = 0;
        move_back = 0;
        turn_left = 0;
        turn_right = 0;
        strafe_left = 0;
        strafe_right = 0;
        manual_enable = 1'b1;

        frame_index = 0;
        pixel_count = 0;
        capture_en = 1'b0;

        rst = 1'b1;
        #100;
        rst = 1'b0;
    end
endmodule
