`timescale 1ns/1ps

module tb_ray_dda;
    reg [15:0] ray_x;
    reg [15:0] ray_y;
    reg signed [15:0] dir_x;
    reg signed [15:0] dir_y;

    wire hit;
    wire [4:0] hit_tile_x;
    wire [4:0] hit_tile_y;
    wire [8:0] dist_steps;
    wire side;
    integer errors;

    ray_dda uut (
        .ray_x_q8_8(ray_x),
        .ray_y_q8_8(ray_y),
        .dir_x_q1_14(dir_x),
        .dir_y_q1_14(dir_y),
        .hit(hit),
        .hit_tile_x(hit_tile_x),
        .hit_tile_y(hit_tile_y),
        .dist_steps(dist_steps),
        .side(side)
    );

    initial begin
        $dumpfile("ray_dda.vcd");
        $dumpvars(0, tb_ray_dda);
        errors = 0;

        // Player at tile (3.5, 3.5), which is empty in this map.
        ray_x = 16'd896;
        ray_y = 16'd896;

        // Cast east.
        dir_x = 16'sd16384;
        dir_y = 16'sd0;
        #10;
        if (!(hit == 1'b1 && hit_tile_x == 5'd8 && hit_tile_y == 5'd3 && side == 1'b0)) begin
            errors = errors + 1;
        end

        // Cast south.
        dir_x = 16'sd0;
        dir_y = 16'sd16384;
        #10;
        if (!(hit == 1'b1 && hit_tile_x == 5'd3 && hit_tile_y == 5'd8 && side == 1'b1)) begin
            errors = errors + 1;
        end

        // Cast north-west.
        dir_x = -16'sd11585;
        dir_y = -16'sd11585;
        #10;
        if (!(hit == 1'b1 && hit_tile_x == 5'd0 && hit_tile_y == 5'd0)) begin
            errors = errors + 1;
        end

        if (errors == 0) begin
            $display("PASS tb_ray_dda");
        end else begin
            $display("FAIL tb_ray_dda errors=%0d", errors);
        end

        $finish;
    end
endmodule
