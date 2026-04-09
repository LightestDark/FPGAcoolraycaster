// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vvga_raycast_demo.h for the primary calling header

#ifndef _VVGA_RAYCAST_DEMO_VGA_RAYCAST_DEMO_H_
#define _VVGA_RAYCAST_DEMO_VGA_RAYCAST_DEMO_H_  // guard

#include "verilated.h"
#include "Vvga_raycast_demo__Dpi.h"

//==========

class Vvga_raycast_demo__Syms;

//----------

VL_MODULE(Vvga_raycast_demo_vga_raycast_demo) {
  public:
    
    // PORTS
    VL_IN8(clk_25,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(move_fwd,0,0);
    VL_IN8(move_back,0,0);
    VL_IN8(turn_left,0,0);
    VL_IN8(turn_right,0,0);
    VL_IN8(strafe_left,0,0);
    VL_IN8(strafe_right,0,0);
    VL_OUT8(hsync,0,0);
    VL_OUT8(vsync,0,0);
    VL_OUT8(vga_r,3,0);
    VL_OUT8(vga_g,3,0);
    VL_OUT8(vga_b,3,0);
    
    // LOCAL SIGNALS
    CData/*0:0*/ active;
    CData/*0:0*/ __PVT__hit;
    CData/*0:0*/ __PVT__side;
    CData/*4:0*/ __PVT__hit_tile_x;
    CData/*4:0*/ __PVT__hit_tile_y;
    CData/*7:0*/ __PVT__ray_angle;
    CData/*3:0*/ __PVT__shade;
    CData/*3:0*/ __PVT__wall_lit;
    CData/*7:0*/ __PVT__cam_angle;
    CData/*0:0*/ __PVT__manual_active;
    CData/*4:0*/ __PVT__r__DOT__tx;
    CData/*4:0*/ __PVT__r__DOT__ty;
    SData/*9:0*/ hc;
    SData/*9:0*/ vc;
    SData/*8:0*/ __PVT__dist_steps;
    SData/*15:0*/ __PVT__sin_out;
    SData/*15:0*/ __PVT__cos_out;
    SData/*15:0*/ __PVT__move_sin;
    SData/*15:0*/ __PVT__move_cos;
    SData/*9:0*/ __PVT__wall_half;
    SData/*9:0*/ __PVT__wall_top;
    SData/*9:0*/ __PVT__wall_bottom;
    SData/*8:0*/ __PVT__sweep;
    SData/*8:0*/ __PVT__sweep_shift;
    SData/*8:0*/ __PVT__ray_angle_sum;
    SData/*15:0*/ __PVT__player_x;
    SData/*15:0*/ __PVT__player_y;
    SData/*15:0*/ __PVT__demo_tick;
    SData/*15:0*/ __PVT__move_dx;
    SData/*15:0*/ __PVT__move_dy;
    IData/*31:0*/ __PVT__l__DOT__i;
    IData/*31:0*/ __PVT__l__DOT__tmp_sin;
    IData/*31:0*/ __PVT__l__DOT__tmp_cos;
    IData/*31:0*/ __PVT__cam_lut__DOT__i;
    IData/*31:0*/ __PVT__cam_lut__DOT__tmp_sin;
    IData/*31:0*/ __PVT__cam_lut__DOT__tmp_cos;
    IData/*31:0*/ __PVT__r__DOT__i;
    IData/*17:0*/ __PVT__r__DOT__x_fp;
    IData/*17:0*/ __PVT__r__DOT__y_fp;
    IData/*17:0*/ __PVT__r__DOT__abs_dx;
    IData/*17:0*/ __PVT__r__DOT__abs_dy;
    IData/*17:0*/ __PVT__r__DOT__err;
    IData/*17:0*/ __PVT__r__DOT__step_x;
    IData/*17:0*/ __PVT__r__DOT__step_y;
    IData/*17:0*/ __PVT__r__DOT__dir_x_ext;
    IData/*17:0*/ __PVT__r__DOT__dir_y_ext;
    SData/*15:0*/ __PVT__l__DOT__sin_table[256];
    SData/*15:0*/ __PVT__l__DOT__cos_table[256];
    SData/*15:0*/ __PVT__cam_lut__DOT__sin_table[256];
    SData/*15:0*/ __PVT__cam_lut__DOT__cos_table[256];
    
    // LOCAL VARIABLES
    CData/*0:0*/ __Vfunc_r__DOT__is_wall__2__Vfuncout;
    CData/*4:0*/ __Vfunc_r__DOT__is_wall__2__x;
    CData/*4:0*/ __Vfunc_r__DOT__is_wall__2__y;
    
    // INTERNAL VARIABLES
  private:
    Vvga_raycast_demo__Syms* __VlSymsp;  // Symbol table
  public:
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vvga_raycast_demo_vga_raycast_demo);  ///< Copying not allowed
  public:
    Vvga_raycast_demo_vga_raycast_demo(const char* name = "TOP");
    ~Vvga_raycast_demo_vga_raycast_demo();
    
    // INTERNAL METHODS
    void __Vconfigure(Vvga_raycast_demo__Syms* symsp, bool first);
    static void _combo__TOP__vga_raycast_demo__5(Vvga_raycast_demo__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _initial__TOP__vga_raycast_demo__1(Vvga_raycast_demo__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__vga_raycast_demo__2(Vvga_raycast_demo__Syms* __restrict vlSymsp);
    static void _sequent__TOP__vga_raycast_demo__3(Vvga_raycast_demo__Syms* __restrict vlSymsp);
    static void _settle__TOP__vga_raycast_demo__4(Vvga_raycast_demo__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
