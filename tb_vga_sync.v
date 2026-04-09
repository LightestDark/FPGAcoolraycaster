// tb_vga_sync.v
`timescale 1ns/1ps

module tb_vga_sync;
    localparam H_ACTIVE = 640;
    localparam H_FP = 16;
    localparam H_SYNC = 96;
    localparam H_TOTAL = 800;
    localparam V_ACTIVE = 480;
    localparam V_FP = 10;
    localparam V_SYNC = 2;
    localparam V_TOTAL = 525;

    localparam HS_START = H_ACTIVE + H_FP;
    localparam HS_END = HS_START + H_SYNC;
    localparam VS_START = V_ACTIVE + V_FP;
    localparam VS_END = VS_START + V_SYNC;

    reg clk_25, rst;
    wire hsync, vsync, active;
    wire [9:0] hc, vc;
    reg exp_hsync, exp_vsync, exp_active;
    reg [9:0] hc_d, vc_d;
    integer errors;

    vga_sync uut (.clk_25(clk_25), .rst(rst),
                  .hsync(hsync), .vsync(vsync),
                  .hc(hc), .vc(vc), .active(active));

    // 25 MHz = 40 ns period
    initial clk_25 = 0;
    always #20 clk_25 = ~clk_25;

    always @(posedge clk_25) begin
        hc_d <= hc;
        vc_d <= vc;

        if (!rst) begin
            exp_hsync = ~((hc_d >= HS_START) && (hc_d < HS_END));
            exp_vsync = ~((vc_d >= VS_START) && (vc_d < VS_END));
            exp_active = (hc < H_ACTIVE) && (vc < V_ACTIVE);

            if (hsync !== exp_hsync) errors = errors + 1;
            if (vsync !== exp_vsync) errors = errors + 1;
            if (active !== exp_active) errors = errors + 1;
            if (hc >= H_TOTAL || vc >= V_TOTAL) errors = errors + 1;
        end
    end

    initial begin
        $dumpfile("vga_sync.vcd");
        $dumpvars(0, tb_vga_sync);
        errors = 0;
        hc_d = 0;
        vc_d = 0;
        rst = 1; #100;
        rst = 0;

        // Run for one full frame.
        #(H_TOTAL * V_TOTAL * 40);

        if (errors == 0) begin
            $display("PASS tb_vga_sync");
        end else begin
            $display("FAIL tb_vga_sync errors=%0d", errors);
        end
        $finish;
    end
endmodule