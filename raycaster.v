module vga_sync(
    input wire clk_25,
    input wire rst,
    output reg hsync,
    output reg vsync,
    output reg [9:0] hc,
    output reg [9:0] vc,
    output wire active
);
    localparam H_ACTIVE=640, H_FP=16, H_SYNC=96, H_TOTAL=800;
    localparam V_ACTIVE=480, V_FP=10, V_SYNC=2, V_TOTAL=525;
    localparam HS_START=H_ACTIVE+H_FP, HS_END=HS_START+H_SYNC;
    localparam VS_START=V_ACTIVE+V_FP, VS_END=VS_START+V_SYNC;

    always @(posedge clk_25 or posedge rst)
        if (rst) begin hc <= 0; vc <= 0; end
        else if (hc == H_TOTAL-1) begin hc <= 0; vc <= (vc == V_TOTAL-1) ? 0 : vc + 1; end
        else hc <= hc + 1;

    always @(posedge clk_25) begin
        hsync <= ~((hc >= HS_START) && (hc < HS_END));
        vsync <= ~((vc >= VS_START) && (vc < VS_END));
    end

    assign active = (hc < H_ACTIVE) && (vc < V_ACTIVE);
endmodule

module sin_cos_lut(
    input wire [7:0] angle,
    output reg signed [15:0] sin_out,
    output reg signed [15:0] cos_out
);
    reg signed [15:0] sin_table [0:255];
    reg signed [15:0] cos_table [0:255];
    integer i;
    integer tmp_sin;
    integer tmp_cos;
    initial for (i = 0; i < 256; i = i + 1) begin
        tmp_sin = $rtoi($sin(6.2831853 * i / 256.0) * 16384.0);
        tmp_cos = $rtoi($cos(6.2831853 * i / 256.0) * 16384.0);
        sin_table[i] = $signed(tmp_sin[15:0]);
        cos_table[i] = $signed(tmp_cos[15:0]);
    end
    always @(*) begin sin_out = sin_table[angle]; cos_out = cos_table[angle]; end
endmodule

module map_rom(
    input wire [4:0] tile_x,
    input wire [4:0] tile_y,
    output reg wall
);
    function automatic map_wall;
        input [4:0] x;
        input [4:0] y;
        begin
            if (x == 0 || y == 0 || x == 31 || y == 31)
                map_wall = 1'b1;
            else if ((x[2:0] == 0 && y[2:0] != 0) || (y[2:0] == 0 && x[2:0] != 0))
                map_wall = 1'b1;
            else if ((x >= 10 && x <= 14 && y >= 10 && y <= 14) || (x >= 20 && x <= 24 && y >= 6 && y <= 10))
                map_wall = 1'b1;
            else
                map_wall = 1'b0;
        end
    endfunction

    always @(*) wall = map_wall(tile_x, tile_y);
endmodule

module ray_dda(
    input wire [15:0] ray_x_q8_8,
    input wire [15:0] ray_y_q8_8,
    input wire signed [15:0] dir_x_q1_14,
    input wire signed [15:0] dir_y_q1_14,
    output reg hit,
    output reg [4:0] hit_tile_x,
    output reg [4:0] hit_tile_y,
    output reg [8:0] dist_steps,
    output reg side
);
    localparam MAX_STEPS = 256, STEP = 32;

    function automatic is_wall;
        input [4:0] x;
        input [4:0] y;
        begin
            if (x == 0 || y == 0 || x == 31 || y == 31)
                is_wall = 1'b1;
            else if ((x[2:0] == 0 && y[2:0] != 0) || (y[2:0] == 0 && x[2:0] != 0))
                is_wall = 1'b1;
            else if ((x >= 10 && x <= 14 && y >= 10 && y <= 14) || (x >= 20 && x <= 24 && y >= 6 && y <= 10))
                is_wall = 1'b1;
            else
                is_wall = 1'b0;
        end
    endfunction

    integer i;
    reg signed [17:0] x_fp, y_fp, abs_dx, abs_dy, err, step_x, step_y;
    reg signed [17:0] dir_x_ext, dir_y_ext;
    reg [4:0] tx, ty;

    always @(*) begin
        hit = 0; hit_tile_x = 0; hit_tile_y = 0; dist_steps = 0; side = 0;
        x_fp = {2'b0, ray_x_q8_8}; y_fp = {2'b0, ray_y_q8_8};
        dir_x_ext = {{2{dir_x_q1_14[15]}}, dir_x_q1_14};
        dir_y_ext = {{2{dir_y_q1_14[15]}}, dir_y_q1_14};
        if ((dir_x_q1_14 != 0) || (dir_y_q1_14 != 0)) begin
            abs_dx = (dir_x_ext < 0) ? -dir_x_ext : dir_x_ext;
            abs_dy = (dir_y_ext < 0) ? -dir_y_ext : dir_y_ext;
            step_x = (dir_x_ext < 0) ? -STEP : STEP;
            step_y = (dir_y_ext < 0) ? -STEP : STEP;
            err = 0;
            begin : walk
                for (i = 0; i < MAX_STEPS; i = i + 1) begin
                    if (x_fp < 0 || y_fp < 0 || x_fp >= 18'd8192 || y_fp >= 18'd8192) begin
                        hit = 1; dist_steps = i[8:0]; disable walk;
                    end
                    tx = x_fp[12:8]; ty = y_fp[12:8];
                    if (is_wall(tx, ty)) begin
                        hit = 1; hit_tile_x = tx; hit_tile_y = ty; dist_steps = i[8:0]; disable walk;
                    end
                    if (abs_dx >= abs_dy) begin
                        x_fp = x_fp + step_x; err = err + abs_dy; side = 0;
                        if (err >= abs_dx) begin y_fp = y_fp + step_y; err = err - abs_dx; side = 1; end
                    end else begin
                        y_fp = y_fp + step_y; err = err + abs_dx; side = 1;
                        if (err >= abs_dy) begin x_fp = x_fp + step_x; err = err - abs_dy; side = 0; end
                    end
                end
            end
        end
    end
endmodule

module vga_raycast_demo(
    input wire clk_25,
    input wire rst,
    input wire move_fwd,
    input wire move_back,
    input wire turn_left,
    input wire turn_right,
    input wire strafe_left,
    input wire strafe_right,
    input wire manual_enable,
    output wire active,
    output wire [9:0] hc,
    output wire [9:0] vc,
    output wire hsync,
    output wire vsync,
    output reg [3:0] vga_r,
    output reg [3:0] vga_g,
    output reg [3:0] vga_b
);
    wire hit, side;
    wire [8:0] dist_steps;
    wire [4:0] hit_tile_x, hit_tile_y;
    reg [7:0] ray_angle;
    wire signed [15:0] sin_out, cos_out;
    wire signed [15:0] move_sin, move_cos;
    reg [9:0] wall_half, wall_top, wall_bottom;
    reg [3:0] shade;
    wire [3:0] wall_lit;
    reg signed [8:0] sweep;
    reg signed [8:0] sweep_shift;
    reg signed [8:0] ray_angle_sum;
    reg [15:0] player_x, player_y;
    reg [7:0] cam_angle;
    reg [15:0] demo_tick;
    reg signed [15:0] move_dx, move_dy;
    reg [1:0] wall_type;
    reg [3:0] wall_r, wall_g, wall_b;
    reg signed [17:0] sprite_dx, sprite_dy;
    reg signed [31:0] sprite_forward, sprite_cross;
    reg signed [17:0] sprite_forward_s, sprite_cross_s;
    reg signed [15:0] sprite_off;
    reg [9:0] sprite_screen_x;
    reg [9:0] sprite_half;
    reg [9:0] sprite_top, sprite_bottom;
    reg [8:0] sprite_dist_steps;
    reg sprite_visible;
    reg sprite_on;
    wire manual_active;
    wire ctrl_fwd, ctrl_back, ctrl_left, ctrl_right, ctrl_strafe_l, ctrl_strafe_r;

    function automatic wall_at;
        input [15:0] pos_x;
        input [15:0] pos_y;
        reg [4:0] tx;
        reg [4:0] ty;
        begin
            tx = pos_x[12:8];
            ty = pos_y[12:8];
            if (tx == 0 || ty == 0 || tx == 31 || ty == 31)
                wall_at = 1'b1;
            else if ((tx[2:0] == 0 && ty[2:0] != 0) || (ty[2:0] == 0 && tx[2:0] != 0))
                wall_at = 1'b1;
            else if ((tx >= 10 && tx <= 14 && ty >= 10 && ty <= 14) || (tx >= 20 && tx <= 24 && ty >= 6 && ty <= 10))
                wall_at = 1'b1;
            else
                wall_at = 1'b0;
        end
    endfunction

    function automatic [1:0] wall_type_at;
        input [4:0] tx;
        input [4:0] ty;
        begin
            if (tx == 0 || ty == 0 || tx == 31 || ty == 31)
                wall_type_at = 2'd1; // border
            else if ((tx[2:0] == 0 && ty[2:0] != 0) || (ty[2:0] == 0 && tx[2:0] != 0))
                wall_type_at = 2'd2; // grid lines
            else if ((tx >= 10 && tx <= 14 && ty >= 10 && ty <= 14) || (tx >= 20 && tx <= 24 && ty >= 6 && ty <= 10))
                wall_type_at = 2'd3; // inner rooms
            else
                wall_type_at = 2'd0;
        end
    endfunction

    vga_sync sync_i(.clk_25(clk_25), .rst(rst), .hsync(hsync), .vsync(vsync), .hc(hc), .vc(vc), .active(active));
    sin_cos_lut l(.angle(ray_angle), .sin_out(sin_out), .cos_out(cos_out));
    sin_cos_lut cam_lut(.angle(cam_angle), .sin_out(move_sin), .cos_out(move_cos));
    ray_dda r(.ray_x_q8_8(player_x), .ray_y_q8_8(player_y), .dir_x_q1_14(cos_out), .dir_y_q1_14(sin_out), .hit(hit), .hit_tile_x(hit_tile_x), .hit_tile_y(hit_tile_y), .dist_steps(dist_steps), .side(side));

    assign manual_active = manual_enable;
    assign wall_lit = (dist_steps > 9'd120) ? (shade >> 3) :
                      (dist_steps > 9'd90)  ? (shade >> 2) :
                      (dist_steps > 9'd60)  ? (shade >> 1) : shade;
    assign ctrl_fwd = manual_active ? move_fwd : ~demo_tick[6];
    assign ctrl_back = manual_active ? move_back : 1'b0;
    assign ctrl_left = manual_active ? turn_left : 1'b0;
    assign ctrl_right = manual_active ? turn_right : 1'b1;
    assign ctrl_strafe_l = manual_active ? strafe_left : demo_tick[8];
    assign ctrl_strafe_r = manual_active ? strafe_right : 1'b0;

    always @(posedge clk_25 or posedge rst) begin
        if (rst) begin
            player_x <= 16'd896;
            player_y <= 16'd896;
            cam_angle <= 8'd0;
            demo_tick <= 16'd0;
        end else if (hc == 10'd799 && vc == 10'd524) begin
            demo_tick <= demo_tick + 16'd1;
            if (ctrl_left)  cam_angle <= cam_angle - 8'd2;
            if (ctrl_right) cam_angle <= cam_angle + 8'd2;

            move_dx = 0;
            move_dy = 0;
            if (ctrl_fwd) begin
                move_dx = move_dx + (move_cos >>> 7);
                move_dy = move_dy + (move_sin >>> 7);
            end
            if (ctrl_back) begin
                move_dx = move_dx - (move_cos >>> 7);
                move_dy = move_dy - (move_sin >>> 7);
            end
            if (ctrl_strafe_l) begin
                move_dx = move_dx + (move_sin >>> 7);
                move_dy = move_dy - (move_cos >>> 7);
            end
            if (ctrl_strafe_r) begin
                move_dx = move_dx - (move_sin >>> 7);
                move_dy = move_dy + (move_cos >>> 7);
            end

            if (!wall_at(player_x + move_dx, player_y)) player_x <= player_x + move_dx;
            if (!wall_at(player_x, player_y + move_dy)) player_y <= player_y + move_dy;
        end
    end

    always @(*) begin
        sweep = $signed({1'b0, hc[9:2]}) - 9'sd80;
        sweep_shift = {sweep[8], sweep[8:1]};
        ray_angle_sum = $signed({1'b0, cam_angle}) + sweep_shift;
        ray_angle = ray_angle_sum[7:0];

        wall_type = wall_type_at(hit_tile_x, hit_tile_y);
        case (wall_type)
            2'd1: begin wall_r = wall_lit; wall_g = 4'd2; wall_b = 4'd1; end
            2'd2: begin wall_r = 4'd2; wall_g = wall_lit; wall_b = 4'd1; end
            2'd3: begin wall_r = 4'd2; wall_g = 4'd2; wall_b = wall_lit; end
            default: begin wall_r = wall_lit; wall_g = wall_lit >> 1; wall_b = 4'd0; end
        endcase

        sprite_dx = $signed({2'b0, 16'd1408}) - $signed({2'b0, player_x});
        sprite_dy = $signed({2'b0, 16'd1152}) - $signed({2'b0, player_y});
        sprite_forward = sprite_dx * $signed(move_cos) + sprite_dy * $signed(move_sin);
        sprite_cross = sprite_dx * $signed(move_sin) - sprite_dy * $signed(move_cos);
        sprite_forward_s = $signed(sprite_forward[31:14]);
        sprite_cross_s = $signed(sprite_cross[31:14]);
        sprite_dist_steps = (sprite_forward_s[17:0] > 0) ? sprite_forward_s[17:9] : 9'd0;
        sprite_off = sprite_cross_s[15:0];
        sprite_screen_x = 10'd320 + sprite_off[9:0];
        sprite_half = (sprite_forward_s > 18'sd0) ? (10'd80 - {3'b000, sprite_forward_s[17:11]}) : 10'd0;
        if (sprite_half < 10'd6) sprite_half = 10'd6;
        sprite_top = 10'd240 - sprite_half;
        sprite_bottom = 10'd240 + sprite_half;
        sprite_visible = (sprite_forward_s > 18'sd0) && (sprite_screen_x < 10'd640);
        sprite_on = sprite_visible && (hc >= (sprite_screen_x - sprite_half)) && (hc <= (sprite_screen_x + sprite_half))
                    && (vc >= sprite_top) && (vc <= sprite_bottom) && (sprite_dist_steps < dist_steps);
        if (dist_steps > 9'd200) shade = 4'd1;
        else if (dist_steps > 9'd160) shade = 4'd2;
        else if (dist_steps > 9'd120) shade = 4'd4;
        else if (dist_steps > 9'd90) shade = 4'd6;
        else if (dist_steps > 9'd60) shade = 4'd9;
        else if (dist_steps > 9'd40) shade = 4'd11;
        else shade = 4'd13;
        wall_half = (10'd180 / (dist_steps + 1)) + 10'd6;
        wall_top = 10'd240 - wall_half;
        wall_bottom = 10'd240 + wall_half;
        if (!active) begin
            vga_r = 0; vga_g = 0; vga_b = 0;
        end else if (vc < wall_top) begin
            vga_r = 4'd1; vga_g = 4'd2; vga_b = 4'd4 + {1'b0, vc[8:6]};
        end else if (vc > wall_bottom) begin
            vga_r = 4'd1; vga_g = 4'd1 + {2'b00, vc[8:7]}; vga_b = 4'd1;
        end else if (sprite_on) begin
            vga_r = 4'd1; vga_g = 4'd12; vga_b = 4'd15;
        end else if (hit) begin
            if (hit_tile_x[0] ^ hit_tile_y[0] ^ side ^ vc[3]) begin
                vga_r = side ? (wall_r >> 1) : wall_r;
                vga_g = wall_g;
                vga_b = wall_b;
            end else begin
                vga_r = wall_r >> 2;
                vga_g = side ? (wall_g >> 1) : wall_g;
                vga_b = wall_b >> 2;
            end
        end else begin
            vga_r = 15; vga_g = 0; vga_b = 0;
        end
    end
endmodule