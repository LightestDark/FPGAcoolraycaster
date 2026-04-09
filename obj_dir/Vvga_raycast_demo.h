// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VVGA_RAYCAST_DEMO_H_
#define _VVGA_RAYCAST_DEMO_H_  // guard

#include "verilated.h"

//==========

class Vvga_raycast_demo__Syms;

//----------

VL_MODULE(Vvga_raycast_demo) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk_25,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(move_fwd,0,0);
    VL_IN8(move_back,0,0);
    VL_IN8(turn_left,0,0);
    VL_IN8(turn_right,0,0);
    VL_IN8(strafe_left,0,0);
    VL_IN8(strafe_right,0,0);
    VL_OUT8(active,0,0);
    VL_OUT8(hsync,0,0);
    VL_OUT8(vsync,0,0);
    VL_OUT8(vga_r,3,0);
    VL_OUT8(vga_g,3,0);
    VL_OUT8(vga_b,3,0);
    VL_OUT16(hc,9,0);
    VL_OUT16(vc,9,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*0:0*/ vga_raycast_demo__DOT__hit;
    CData/*0:0*/ vga_raycast_demo__DOT__side;
    CData/*4:0*/ vga_raycast_demo__DOT__hit_tile_x;
    CData/*4:0*/ vga_raycast_demo__DOT__hit_tile_y;
    CData/*7:0*/ vga_raycast_demo__DOT__ray_angle;
    CData/*3:0*/ vga_raycast_demo__DOT__shade;
    CData/*3:0*/ vga_raycast_demo__DOT__wall_lit;
    CData/*7:0*/ vga_raycast_demo__DOT__cam_angle;
    CData/*0:0*/ vga_raycast_demo__DOT__manual_active;
    CData/*4:0*/ vga_raycast_demo__DOT__r__DOT__tx;
    CData/*4:0*/ vga_raycast_demo__DOT__r__DOT__ty;
    SData/*8:0*/ vga_raycast_demo__DOT__dist_steps;
    SData/*15:0*/ vga_raycast_demo__DOT__sin_out;
    SData/*15:0*/ vga_raycast_demo__DOT__cos_out;
    SData/*15:0*/ vga_raycast_demo__DOT__move_sin;
    SData/*15:0*/ vga_raycast_demo__DOT__move_cos;
    SData/*9:0*/ vga_raycast_demo__DOT__wall_half;
    SData/*9:0*/ vga_raycast_demo__DOT__wall_top;
    SData/*9:0*/ vga_raycast_demo__DOT__wall_bottom;
    SData/*8:0*/ vga_raycast_demo__DOT__sweep;
    SData/*8:0*/ vga_raycast_demo__DOT__sweep_shift;
    SData/*8:0*/ vga_raycast_demo__DOT__ray_angle_sum;
    SData/*15:0*/ vga_raycast_demo__DOT__player_x;
    SData/*15:0*/ vga_raycast_demo__DOT__player_y;
    SData/*15:0*/ vga_raycast_demo__DOT__demo_tick;
    SData/*15:0*/ vga_raycast_demo__DOT__move_dx;
    SData/*15:0*/ vga_raycast_demo__DOT__move_dy;
    IData/*31:0*/ vga_raycast_demo__DOT__l__DOT__i;
    IData/*31:0*/ vga_raycast_demo__DOT__l__DOT__tmp_sin;
    IData/*31:0*/ vga_raycast_demo__DOT__l__DOT__tmp_cos;
    IData/*31:0*/ vga_raycast_demo__DOT__cam_lut__DOT__i;
    IData/*31:0*/ vga_raycast_demo__DOT__cam_lut__DOT__tmp_sin;
    IData/*31:0*/ vga_raycast_demo__DOT__cam_lut__DOT__tmp_cos;
    IData/*31:0*/ vga_raycast_demo__DOT__r__DOT__i;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__x_fp;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__y_fp;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__abs_dx;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__abs_dy;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__err;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__step_x;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__step_y;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__dir_x_ext;
    IData/*17:0*/ vga_raycast_demo__DOT__r__DOT__dir_y_ext;
    SData/*15:0*/ vga_raycast_demo__DOT__l__DOT__sin_table[256];
    SData/*15:0*/ vga_raycast_demo__DOT__l__DOT__cos_table[256];
    SData/*15:0*/ vga_raycast_demo__DOT__cam_lut__DOT__sin_table[256];
    SData/*15:0*/ vga_raycast_demo__DOT__cam_lut__DOT__cos_table[256];
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__Vfuncout;
    CData/*4:0*/ __Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x;
    CData/*4:0*/ __Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y;
    CData/*0:0*/ __Vclklast__TOP__clk_25;
    CData/*0:0*/ __Vclklast__TOP__rst;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vvga_raycast_demo__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vvga_raycast_demo);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vvga_raycast_demo(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vvga_raycast_demo();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vvga_raycast_demo__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vvga_raycast_demo__Syms* symsp, bool first);
  private:
    static QData _change_request(Vvga_raycast_demo__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vvga_raycast_demo__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__5(Vvga_raycast_demo__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vvga_raycast_demo__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vvga_raycast_demo__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vvga_raycast_demo__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vvga_raycast_demo__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__2(Vvga_raycast_demo__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vvga_raycast_demo__Syms* __restrict vlSymsp);
    static void _settle__TOP__4(Vvga_raycast_demo__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
