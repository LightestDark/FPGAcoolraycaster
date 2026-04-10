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
            else if ((x >= 6 && x <= 25 && (y == 6 || y == 25)) || (y >= 6 && y <= 25 && (x == 6 || x == 25)))
                map_wall = 1'b1;
            else if ((x >= 10 && x <= 21 && (y == 10 || y == 21)) || (y >= 10 && y <= 21 && (x == 10 || x == 21)))
                map_wall = 1'b1;
            else if ((x == 16 && y >= 6 && y <= 25) || (y == 16 && x >= 6 && x <= 25))
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
    output reg [17:0] hit_x_fp,
    output reg [17:0] hit_y_fp,
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
            else if ((x >= 6 && x <= 25 && (y == 6 || y == 25)) || (y >= 6 && y <= 25 && (x == 6 || x == 25)))
                is_wall = 1'b1;
            else if ((x >= 10 && x <= 21 && (y == 10 || y == 21)) || (y >= 10 && y <= 21 && (x == 10 || x == 21)))
                is_wall = 1'b1;
            else if ((x == 16 && y >= 6 && y <= 25) || (y == 16 && x >= 6 && x <= 25))
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
        hit_x_fp = 0; hit_y_fp = 0;
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
                        hit = 1; dist_steps = i[8:0]; hit_x_fp = x_fp; hit_y_fp = y_fp; disable walk;
                    end
                    tx = x_fp[12:8]; ty = y_fp[12:8];
                    if (is_wall(tx, ty)) begin
                        hit = 1; hit_tile_x = tx; hit_tile_y = ty; dist_steps = i[8:0];
                        hit_x_fp = x_fp; hit_y_fp = y_fp; disable walk;
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
    wire [17:0] hit_x_fp, hit_y_fp;
    reg [7:0] ray_angle;
    wire signed [15:0] sin_out, cos_out;
    wire signed [15:0] move_sin, move_cos;
    reg [9:0] wall_half, wall_top, wall_bottom;
    reg [9:0] wall_height;
    reg signed [10:0] wall_top_s, wall_bottom_s;
    reg [9:0] wall_top_clamped, wall_bottom_clamped;
    reg [3:0] shade;
    reg [3:0] shade_banded;
    reg signed [8:0] sweep;
    reg signed [8:0] sweep_shift;
    reg signed [8:0] ray_angle_sum;
    reg [15:0] player_x, player_y;
    reg [7:0] cam_angle;
    reg [15:0] demo_tick;
    reg signed [15:0] move_dx, move_dy;
    reg [1:0] wall_tex_id;
    reg [3:0] wall_r, wall_g, wall_b;
    reg [9:0] tex_u, tex_v;
    reg [9:0] wall_h;
    reg [3:0] tex_idx;
    reg [11:0] tex_color;
    reg [3:0] tex_r, tex_g, tex_b;
    reg [15:0] tex_step;
    reg [23:0] tex_pos;
    reg [4:0] tex_u_5;
    reg [4:0] tex_v_5;
    reg signed [17:0] hit_dx;
    reg signed [17:0] hit_dy;
    reg signed [33:0] hit_dot;
    reg signed [33:0] hit_dot_shift;
    reg signed [17:0] perp_dist;
    reg [9:0] perp_steps;
    reg [7:0] wall_u_frac;
        localparam BRICK_W = 64;
        localparam BRICK_H = 32;
        localparam MORTAR_X = 4;
        localparam MORTAR_Y = 3;
        localparam BRICK_W_BITS = 6;
        localparam BRICK_H_BITS = 5;
        localparam BRICK_W_MASK = BRICK_W - 1;
        localparam BRICK_H_MASK = BRICK_H - 1;
    reg signed [17:0] sprite_dx, sprite_dy;
    reg signed [31:0] sprite_forward, sprite_cross;
    reg signed [17:0] sprite_forward_s, sprite_cross_s;
    reg signed [15:0] sprite_off;
    reg [9:0] sprite_screen_x;
    reg [9:0] sprite_half;
    reg [9:0] sprite_left, sprite_right;
    reg signed [11:0] moon_dx, moon_dy;
    reg signed [11:0] moon_dx2, moon_dy2;
    reg [23:0] moon_dist, moon_dist2;
    reg moon_on;
    reg moon_disk;
    reg moon_crescent;
    reg star_on;
    reg star_on2;
    reg star_twinkle;
    reg star_static;
    reg [4:0] star_cell_x;
    reg [4:0] star_cell_y;
    reg [7:0] star_hash;
    reg [7:0] star_cell_mix;
    reg dust_on;
    reg moon_rim;
    reg meteor_on;
    reg flash_on;
    reg signed [10:0] meteor_dx;
    reg [9:0] meteor_x;
    reg [9:0] meteor_y;
    reg [10:0] sky_x1;
    reg [10:0] sky_x2;
    reg [3:0] water_g;
    reg [3:0] water_b;
    reg [4:0] water_g_tmp;
    reg [4:0] water_b_tmp;
    reg [3:0] wall_r_base;
    reg [3:0] wall_g_base;
    reg [3:0] wall_b_base;
    reg [15:0] lfsr;
    reg [3:0] sky_base;
    reg [3:0] fog_strength;
    reg edge_on;
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
            else if ((tx >= 6 && tx <= 25 && (ty == 6 || ty == 25)) || (ty >= 6 && ty <= 25 && (tx == 6 || tx == 25)))
                wall_at = 1'b1;
            else if ((tx >= 10 && tx <= 21 && (ty == 10 || ty == 21)) || (ty >= 10 && ty <= 21 && (tx == 10 || tx == 21)))
                wall_at = 1'b1;
            else if ((tx == 16 && ty >= 6 && ty <= 25) || (ty == 16 && tx >= 6 && tx <= 25))
                wall_at = 1'b1;
            else
                wall_at = 1'b0;
        end
    endfunction

    function automatic is_wall_tile;
        input [4:0] x;
        input [4:0] y;
        begin
            if (x == 0 || y == 0 || x == 31 || y == 31)
                is_wall_tile = 1'b1;
            else if ((x >= 6 && x <= 25 && (y == 6 || y == 25)) || (y >= 6 && y <= 25 && (x == 6 || x == 25)))
                is_wall_tile = 1'b1;
            else if ((x >= 10 && x <= 21 && (y == 10 || y == 21)) || (y >= 10 && y <= 21 && (x == 10 || x == 21)))
                is_wall_tile = 1'b1;
            else if ((x == 16 && y >= 6 && y <= 25) || (y == 16 && x >= 6 && x <= 25))
                is_wall_tile = 1'b1;
            else
                is_wall_tile = 1'b0;
        end
    endfunction


    function automatic [3:0] tex_index;
        input [1:0] tex_id;
        input [9:0] u;
        input [9:0] v;
        integer u_mod;
        integer v_mod;
        integer brick_x;
        integer brick_y;
        integer row_off;
        reg [31:0] u_ext;
        reg [31:0] v_ext;
        reg mortar;
        reg edge_hi;
        reg edge_lo;
        reg inner;
        reg noise;
        reg [3:0] idx;
        begin
            u_ext = {22'd0, u};
            v_ext = {22'd0, v};
            brick_y = v_ext >> BRICK_H_BITS;
            row_off = (brick_y[0] != 0) ? (BRICK_W >> 1) : 0;
            u_mod = (u_ext + row_off) & BRICK_W_MASK;
            v_mod = v_ext & BRICK_H_MASK;
            brick_x = (u_ext + row_off) >> BRICK_W_BITS;
            mortar = (u_mod < MORTAR_X) || (u_mod >= (BRICK_W - MORTAR_X)) ||
                     (v_mod < MORTAR_Y) || (v_mod >= (BRICK_H - MORTAR_Y));
            edge_hi = (v_mod < 2) || (u_mod < 2);
            edge_lo = (v_mod >= (BRICK_H - 2)) || (u_mod >= (BRICK_W - 2));
            inner = u_mod[4] ^ v_mod[3] ^ brick_x[0];
            noise = brick_x[1] ^ brick_y[0];
            idx = 4'd8;

            case (tex_id)
                default: begin
                    if (mortar) idx = 4'd1;
                    else if (edge_hi) idx = 4'd11;
                    else if (edge_lo) idx = 4'd6;
                    else if (brick_x[0] ^ brick_y[0]) idx = 4'd9;
                    else idx = 4'd8 + {3'b000, (inner ^ noise)};
                end
            endcase
            tex_index = idx;
        end
    endfunction

    function automatic [3:0] shade_from_dist;
        input [8:0] d;
        begin
            case (d[8:5])
                4'd0: shade_from_dist = 4'd14;
                4'd1: shade_from_dist = 4'd13;
                4'd2: shade_from_dist = 4'd12;
                4'd3: shade_from_dist = 4'd11;
                4'd4: shade_from_dist = 4'd10;
                4'd5: shade_from_dist = 4'd9;
                4'd6: shade_from_dist = 4'd8;
                4'd7: shade_from_dist = 4'd7;
                4'd8: shade_from_dist = 4'd6;
                4'd9: shade_from_dist = 4'd5;
                4'd10: shade_from_dist = 4'd4;
                4'd11: shade_from_dist = 4'd3;
                default: shade_from_dist = 4'd2;
            endcase
        end
    endfunction

    function automatic [11:0] tex_palette;
        input [1:0] tex_id;
        input [3:0] idx;
        reg [3:0] base;
        reg [3:0] r;
        reg [3:0] g;
        reg [3:0] b;
        begin
            base = 4'd6;
            case (idx)
                4'd1: base = 4'd3;
                4'd6: base = 4'd5;
                4'd8: base = 4'd8;
                4'd9: base = 4'd9;
                4'd10: base = 4'd10;
                4'd11: base = 4'd11;
                default: base = 4'd7;
            endcase
            // Subtle warm tint while preserving the brick contrast.
            r = base + ((base >= 4'd2) ? 4'd1 : 4'd0);
            g = (base > 4'd1) ? (base - 4'd1) : 4'd0;
            b = (base > 4'd2) ? (base - 4'd2) : 4'd0;
            tex_palette = {r, g, b};
        end
    endfunction

    vga_sync sync_i(.clk_25(clk_25), .rst(rst), .hsync(hsync), .vsync(vsync), .hc(hc), .vc(vc), .active(active));
    sin_cos_lut l(.angle(ray_angle), .sin_out(sin_out), .cos_out(cos_out));
    sin_cos_lut cam_lut(.angle(cam_angle), .sin_out(move_sin), .cos_out(move_cos));
    ray_dda r(.ray_x_q8_8(player_x), .ray_y_q8_8(player_y), .dir_x_q1_14(cos_out), .dir_y_q1_14(sin_out), .hit(hit), .hit_tile_x(hit_tile_x), .hit_tile_y(hit_tile_y), .hit_x_fp(hit_x_fp), .hit_y_fp(hit_y_fp), .dist_steps(dist_steps), .side(side));

    assign manual_active = manual_enable;
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
            lfsr <= 16'h1d2b;
        end else if (hc == 10'd799 && vc == 10'd524) begin
            demo_tick <= demo_tick + 16'd1;
            lfsr <= {lfsr[14:0], lfsr[15] ^ lfsr[13] ^ 1'b1};
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
        sprite_left = sprite_screen_x - sprite_half;
        sprite_right = sprite_screen_x + sprite_half;
        sprite_visible = (sprite_forward_s > 18'sd0) && (sprite_screen_x < 10'd640);
        sprite_on = sprite_visible && (hc >= (sprite_screen_x - sprite_half)) && (hc <= (sprite_screen_x + sprite_half))
            && (vc >= sprite_top) && (vc <= sprite_bottom) && (sprite_dist_steps < dist_steps);
        hit_dx = $signed(hit_x_fp) - $signed({2'b0, player_x});
        hit_dy = $signed(hit_y_fp) - $signed({2'b0, player_y});
        hit_dot = (hit_dx * $signed(cos_out)) + (hit_dy * $signed(sin_out));
        hit_dot_shift = hit_dot >>> 14;
        perp_dist = $signed(hit_dot_shift[17:0]);
        if (perp_dist[17]) perp_dist = -perp_dist;
        perp_steps = perp_dist[17:8];
        shade = shade_from_dist(perp_steps[8:0]);
        shade_banded = {shade[3:1], 1'b0};
        wall_height = (perp_steps != 10'd0) ? (10'd240 / perp_steps) : 10'd240;
        if (wall_height > 10'd238) wall_height = 10'd238;
        wall_half = {1'b0, wall_height[9:1]};
        if (wall_half < 10'd1) wall_half = 10'd1;
        wall_top_s = 11'sd240 - $signed({1'b0, wall_half});
        wall_bottom_s = 11'sd240 + $signed({1'b0, wall_half});
        wall_top = wall_top_s[9:0];
        wall_bottom = wall_bottom_s[9:0];
        if (wall_top_s < 0) wall_top_clamped = 10'd0;
        else if (wall_top_s > 11'sd479) wall_top_clamped = 10'd479;
        else wall_top_clamped = wall_top_s[9:0];
        if (wall_bottom_s < 0) wall_bottom_clamped = 10'd0;
        else if (wall_bottom_s > 11'sd479) wall_bottom_clamped = 10'd479;
        else wall_bottom_clamped = wall_bottom_s[9:0];

        wall_tex_id = 2'd0;
        wall_u_frac = side ? hit_x_fp[7:0] : hit_y_fp[7:0];
        tex_u_5 = wall_u_frac[7:3];
        if ((side == 1'b0) && (cos_out > 0)) tex_u_5 = 5'd31 - tex_u_5;
        if ((side == 1'b1) && (sin_out < 0)) tex_u_5 = 5'd31 - tex_u_5;
        tex_u = {5'd0, tex_u_5};
        wall_h = (wall_bottom_clamped > wall_top_clamped) ? (wall_bottom_clamped - wall_top_clamped) : 10'd1;
        tex_step = (16'd32 << 8) / {6'd0, wall_h};
        if (vc < wall_top_clamped) begin
            tex_v = 10'd0;
        end else if (vc > wall_bottom_clamped) begin
            tex_v = 10'd0;
        end else begin
            tex_pos = {8'd0, (vc - wall_top_clamped)} * tex_step;
            tex_v_5 = tex_pos[12:8];
            tex_v = {5'd0, tex_v_5};
        end
        tex_idx = tex_index(wall_tex_id, tex_u, tex_v);
        tex_color = tex_palette(wall_tex_id, tex_idx);
        tex_r = tex_color[11:8];
        wall_r_base = tex_r;
        wall_r = wall_r_base;
        if (side) wall_r = wall_r >> 1;
        wall_g = wall_r;
        wall_b = wall_r;
        moon_dx = $signed({1'b0, hc}) - 12'sd520;
        moon_dy = $signed({1'b0, vc}) - 12'sd110;
        moon_dx2 = moon_dx + 12'sd8;
        moon_dy2 = moon_dy;
        moon_dist = moon_dx * moon_dx + moon_dy * moon_dy;
        moon_dist2 = moon_dx2 * moon_dx2 + moon_dy2 * moon_dy2;
        moon_disk = (moon_dist <= 24'd900);
        moon_crescent = moon_disk && (moon_dist2 > 24'd784);
        moon_on = moon_disk;
        moon_rim = moon_disk && (moon_dist > 24'd784);
        sky_x1 = {1'b0, hc} + {2'b0, cam_angle} + {4'b0000, demo_tick[6:0]};
        sky_x2 = {1'b0, hc} + {3'b000, cam_angle[7:1]} + {5'b00000, demo_tick[5:0]};
          star_cell_x = hc[7:3];
          star_cell_y = vc[7:3];
          star_cell_mix = {3'b000, star_cell_x} + ({3'b000, star_cell_x} << 2) +
                    ({3'b000, star_cell_y} << 3) + {3'b000, star_cell_y};
          star_hash = star_cell_mix ^ {vc[3:0], hc[7:4]};
          star_on = (star_hash[7:6] == 2'b00) && (hc[2:0] == star_hash[2:0]) &&
                (vc[2:0] == star_hash[5:3]) && (vc < 10'd140);
        star_on2 = 1'b0;
        dust_on = 1'b0;
          star_twinkle = star_on && demo_tick[2];
          star_static = 1'b0;
        meteor_x = {lfsr[7:0], 2'b00} + demo_tick[9:0];
        meteor_y = {lfsr[15:8], 2'b00} + {demo_tick[9:1], 1'b0};
        meteor_dx = $signed({1'b0, hc}) - $signed({1'b0, meteor_x});
        meteor_on = 1'b0;
        flash_on = (lfsr[7:0] == 8'h5a) && (demo_tick[2:0] == 3'b000);

        sky_base = 4'd2 + {1'b0, vc[8:6]};
        edge_on = hit && (hc == 0 || hc == 10'd639 || vc == wall_top_clamped || vc == wall_bottom_clamped);

        if (!active) begin
            vga_r = 0; vga_g = 0; vga_b = 0;
        end else if (vc < wall_top_clamped) begin
            if (moon_on && (hc < 10'd620) && (vc < 10'd160)) begin
                vga_r = 4'd10; vga_g = 4'd10; vga_b = 4'd10;
                if (moon_crescent) begin
                    vga_r = 4'd15; vga_g = 4'd15; vga_b = 4'd15;
                end
            end else if ((star_on || star_on2 || star_static) && (vc < 10'd140)) begin
                if (star_twinkle) begin
                    vga_r = 4'd15; vga_g = 4'd15; vga_b = 4'd15;
                end else begin
                    vga_r = 4'd11; vga_g = 4'd11; vga_b = 4'd11;
                end
            end else if (dust_on && (vc < 10'd180)) begin
                vga_r = 4'd9; vga_g = 4'd9; vga_b = 4'd9;
            end else begin
                vga_r = 4'd2; vga_g = 4'd2; vga_b = sky_base;
            end
        end else if (vc > wall_bottom_clamped) begin
            water_g_tmp = 5'd3 + {2'b00, vc[8:7]} + {2'b00, vc[6:5]} + {3'b000, cam_angle[7:6]};
            water_b_tmp = 5'd2 + {2'b00, vc[7:6]};
            water_g = water_g_tmp[3:0];
            water_b = water_b_tmp[3:0];
            if (((hc[2:0] == (demo_tick[2:0] ^ cam_angle[2:0])) && (vc[2:0] == demo_tick[5:3])) ||
                ((hc[4] ^ vc[3] ^ demo_tick[4]) && (hc[1:0] == (demo_tick[1:0] ^ cam_angle[1:0]))) ||
                ((hc[3:0] == demo_tick[3:0]) && (vc[3:0] == (demo_tick[7:4] ^ cam_angle[3:0]))) ||
                ((hc[4:1] == demo_tick[5:2]) && (vc[4:1] == demo_tick[9:6])) ||
                ((hc[2:0] == 3'd0) && (vc[2:0] == 3'd0)) ||
                ((hc[3:0] == demo_tick[3:0]) && (vc[2:0] == demo_tick[6:4])) ||
                ((hc[5:2] == demo_tick[5:2]) && (vc[3:0] == demo_tick[7:4]))) begin
                vga_r = 4'd0; vga_g = water_g + 4'd1; vga_b = water_b;
            end else if ((hc[4] ^ vc[5]) && (hc[2:0] == 3'd0)) begin
                vga_r = 4'd0; vga_g = water_g; vga_b = water_b + 4'd1;
            end else begin
                vga_r = 4'd0; vga_g = water_g; vga_b = water_b;
            end
        end else if (sprite_on) begin
            if (hc <= (sprite_left + 10'd1) || hc >= (sprite_right - 10'd1) ||
                vc <= (sprite_top + 10'd1) || vc >= (sprite_bottom - 10'd1)) begin
                vga_r = 4'd4; vga_g = 4'd4; vga_b = 4'd4;
            end else begin
                vga_r = 4'd10; vga_g = 4'd10; vga_b = 4'd10;
            end
        end else if (hit) begin
            vga_r = wall_r;
            vga_g = vga_r;
            vga_b = vga_r;
            if (edge_on) begin
                vga_r = vga_r - 4'd2;
                vga_g = vga_r;
                vga_b = vga_r;
            end
        end else begin
            vga_r = 15; vga_g = 0; vga_b = 0;
        end
        if (flash_on) begin
            vga_r = vga_r + 4'd2;
            vga_g = vga_g + 4'd2;
            vga_b = vga_b + 4'd2;
        end
    end
endmodule