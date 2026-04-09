`timescale 1ns/1ps

module tb_lut_map;
    reg [7:0] angle;
    wire [15:0] s;
    wire [15:0] c;

    reg [4:0] tx;
    reg [4:0] ty;
    wire wall;
    integer errors;

    sin_cos_lut lut (
        .angle(angle),
        .sin_out(s),
        .cos_out(c)
    );

    map_rom map (
        .tile_x(tx),
        .tile_y(ty),
        .wall(wall)
    );

    initial begin
        $dumpfile("lut_map.vcd");
        $dumpvars(0, tb_lut_map);
        errors = 0;

        angle = 8'd0;   #10;
        if ($signed(s) != 0 || $signed(c) != 16384) errors = errors + 1;

        angle = 8'd64;  #10;
        if ($signed(s) != 16384 || $signed(c) != 0) errors = errors + 1;

        angle = 8'd128; #10;
        if ($signed(s) != 0 || $signed(c) != -16384) errors = errors + 1;

        angle = 8'd192; #10;
        if ($signed(s) != -16384 || $signed(c) != 0) errors = errors + 1;

        tx = 5'd0;  ty = 5'd0;  #10;
        if (wall != 1'b1) errors = errors + 1;

        tx = 5'd31; ty = 5'd31; #10;
        if (wall != 1'b1) errors = errors + 1;

        tx = 5'd1;  ty = 5'd1;  #10;
        if (wall != 1'b0) errors = errors + 1;

        if (errors == 0) begin
            $display("PASS tb_lut_map");
        end else begin
            $display("FAIL tb_lut_map errors=%0d", errors);
        end

        $finish;
    end
endmodule
