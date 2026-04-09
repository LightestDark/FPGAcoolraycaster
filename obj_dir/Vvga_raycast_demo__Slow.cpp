// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_raycast_demo.h for the primary calling header

#include "Vvga_raycast_demo.h"
#include "Vvga_raycast_demo__Syms.h"

//==========

VL_CTOR_IMP(Vvga_raycast_demo) {
    Vvga_raycast_demo__Syms* __restrict vlSymsp = __VlSymsp = new Vvga_raycast_demo__Syms(this, name());
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vvga_raycast_demo::__Vconfigure(Vvga_raycast_demo__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vvga_raycast_demo::~Vvga_raycast_demo() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vvga_raycast_demo::_initial__TOP__1(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_initial__TOP__1\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i = 0U;
    while (VL_GTS_III(1,32,32, 0x100U, vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i)) {
        vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__tmp_sin 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * sin(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i)) 
                                  / 256.0))));
        vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__tmp_cos 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * cos(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i)) 
                                  / 256.0))));
        vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__sin_table[(0xffU 
                                                                & vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i)] 
            = (0xffffU & vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__tmp_sin);
        vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__cos_table[(0xffU 
                                                                & vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i)] 
            = (0xffffU & vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__tmp_cos);
        vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i 
            = ((IData)(1U) + vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__i);
    }
    vlTOPp->vga_raycast_demo__DOT__l__DOT__i = 0U;
    while (VL_GTS_III(1,32,32, 0x100U, vlTOPp->vga_raycast_demo__DOT__l__DOT__i)) {
        vlTOPp->vga_raycast_demo__DOT__l__DOT__tmp_sin 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * sin(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlTOPp->vga_raycast_demo__DOT__l__DOT__i)) 
                                  / 256.0))));
        vlTOPp->vga_raycast_demo__DOT__l__DOT__tmp_cos 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * cos(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlTOPp->vga_raycast_demo__DOT__l__DOT__i)) 
                                  / 256.0))));
        vlTOPp->vga_raycast_demo__DOT__l__DOT__sin_table[(0xffU 
                                                          & vlTOPp->vga_raycast_demo__DOT__l__DOT__i)] 
            = (0xffffU & vlTOPp->vga_raycast_demo__DOT__l__DOT__tmp_sin);
        vlTOPp->vga_raycast_demo__DOT__l__DOT__cos_table[(0xffU 
                                                          & vlTOPp->vga_raycast_demo__DOT__l__DOT__i)] 
            = (0xffffU & vlTOPp->vga_raycast_demo__DOT__l__DOT__tmp_cos);
        vlTOPp->vga_raycast_demo__DOT__l__DOT__i = 
            ((IData)(1U) + vlTOPp->vga_raycast_demo__DOT__l__DOT__i);
    }
}

void Vvga_raycast_demo::_settle__TOP__4(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_settle__TOP__4\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->vga_raycast_demo__DOT__manual_active = 
        ((((((IData)(vlTOPp->move_fwd) | (IData)(vlTOPp->move_back)) 
            | (IData)(vlTOPp->turn_left)) | (IData)(vlTOPp->turn_right)) 
          | (IData)(vlTOPp->strafe_left)) | (IData)(vlTOPp->strafe_right));
    vlTOPp->active = ((0x280U > (IData)(vlTOPp->hc)) 
                      & (0x1e0U > (IData)(vlTOPp->vc)));
    vlTOPp->vga_raycast_demo__DOT__sweep = (0x1ffU 
                                            & ((0xffU 
                                                & ((IData)(vlTOPp->hc) 
                                                   >> 2U)) 
                                               - (IData)(0x50U)));
    vlTOPp->vga_raycast_demo__DOT__sweep_shift = ((0x100U 
                                                   & (IData)(vlTOPp->vga_raycast_demo__DOT__sweep)) 
                                                  | (0xffU 
                                                     & ((IData)(vlTOPp->vga_raycast_demo__DOT__sweep) 
                                                        >> 1U)));
    vlTOPp->vga_raycast_demo__DOT__ray_angle_sum = 
        (0x1ffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__cam_angle) 
                   + (IData)(vlTOPp->vga_raycast_demo__DOT__sweep_shift)));
    vlTOPp->vga_raycast_demo__DOT__ray_angle = (0xffU 
                                                & (IData)(vlTOPp->vga_raycast_demo__DOT__ray_angle_sum));
    vlTOPp->vga_raycast_demo__DOT__move_sin = vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__sin_table
        [vlTOPp->vga_raycast_demo__DOT__cam_angle];
    vlTOPp->vga_raycast_demo__DOT__move_cos = vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__cos_table
        [vlTOPp->vga_raycast_demo__DOT__cam_angle];
    vlTOPp->vga_raycast_demo__DOT__sin_out = vlTOPp->vga_raycast_demo__DOT__l__DOT__sin_table
        [vlTOPp->vga_raycast_demo__DOT__ray_angle];
    vlTOPp->vga_raycast_demo__DOT__cos_out = vlTOPp->vga_raycast_demo__DOT__l__DOT__cos_table
        [vlTOPp->vga_raycast_demo__DOT__ray_angle];
    vlTOPp->vga_raycast_demo__DOT__hit = 0U;
    vlTOPp->vga_raycast_demo__DOT__hit_tile_x = 0U;
    vlTOPp->vga_raycast_demo__DOT__hit_tile_y = 0U;
    vlTOPp->vga_raycast_demo__DOT__dist_steps = 0U;
    vlTOPp->vga_raycast_demo__DOT__side = 0U;
    vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp = vlTOPp->vga_raycast_demo__DOT__player_x;
    vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp = vlTOPp->vga_raycast_demo__DOT__player_y;
    vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_x_ext 
        = ((0x30000U & ((- (IData)((1U & ((IData)(vlTOPp->vga_raycast_demo__DOT__cos_out) 
                                          >> 0xfU)))) 
                        << 0x10U)) | (IData)(vlTOPp->vga_raycast_demo__DOT__cos_out));
    vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_y_ext 
        = ((0x30000U & ((- (IData)((1U & ((IData)(vlTOPp->vga_raycast_demo__DOT__sin_out) 
                                          >> 0xfU)))) 
                        << 0x10U)) | (IData)(vlTOPp->vga_raycast_demo__DOT__sin_out));
    if (((0U != VL_EXTENDS_II(32,16, (IData)(vlTOPp->vga_raycast_demo__DOT__cos_out))) 
         | (0U != VL_EXTENDS_II(32,16, (IData)(vlTOPp->vga_raycast_demo__DOT__sin_out))))) {
        vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dx 
            = (0x3ffffU & (VL_GTS_III(1,32,32, 0U, 
                                      VL_EXTENDS_II(32,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_x_ext))
                            ? (- vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_x_ext)
                            : vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_x_ext));
        vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dy 
            = (0x3ffffU & (VL_GTS_III(1,32,32, 0U, 
                                      VL_EXTENDS_II(32,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_y_ext))
                            ? (- vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_y_ext)
                            : vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_y_ext));
        vlTOPp->vga_raycast_demo__DOT__r__DOT__step_x 
            = (VL_GTS_III(1,32,32, 0U, VL_EXTENDS_II(32,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_x_ext))
                ? 0x3ffe0U : 0x20U);
        vlTOPp->vga_raycast_demo__DOT__r__DOT__step_y 
            = (VL_GTS_III(1,32,32, 0U, VL_EXTENDS_II(32,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__dir_y_ext))
                ? 0x3ffe0U : 0x20U);
        vlTOPp->vga_raycast_demo__DOT__r__DOT__err = 0U;
        {
            {
                vlTOPp->vga_raycast_demo__DOT__r__DOT__i = 0U;
                while (VL_GTS_III(1,32,32, 0x100U, vlTOPp->vga_raycast_demo__DOT__r__DOT__i)) {
                    if ((((VL_GTS_III(1,32,32, 0U, 
                                      VL_EXTENDS_II(32,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp)) 
                           | VL_GTS_III(1,32,32, 0U, 
                                        VL_EXTENDS_II(32,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp))) 
                          | (0x2000U <= vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp)) 
                         | (0x2000U <= vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp))) {
                        vlTOPp->vga_raycast_demo__DOT__hit = 1U;
                        vlTOPp->vga_raycast_demo__DOT__dist_steps 
                            = (0x1ffU & vlTOPp->vga_raycast_demo__DOT__r__DOT__i);
                        goto __Vlabel2;
                    }
                    vlTOPp->vga_raycast_demo__DOT__r__DOT__tx 
                        = (0x1fU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp 
                                    >> 8U));
                    vlTOPp->vga_raycast_demo__DOT__r__DOT__ty 
                        = (0x1fU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp 
                                    >> 8U));
                    vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y 
                        = vlTOPp->vga_raycast_demo__DOT__r__DOT__ty;
                    vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x 
                        = vlTOPp->vga_raycast_demo__DOT__r__DOT__tx;
                    vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__Vfuncout 
                        = (((((0U == (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x)) 
                              | (0U == (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y))) 
                             | (0x1fU == (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x))) 
                            | (0x1fU == (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y))) 
                           | ((((0U == (7U & (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x))) 
                                & (0U != (7U & (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y)))) 
                               | ((0U == (7U & (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y))) 
                                  & (0U != (7U & (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x))))) 
                              | (((((0xaU <= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x)) 
                                    & (0xeU >= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x))) 
                                   & (0xaU <= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y))) 
                                  & (0xeU >= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y))) 
                                 | ((((0x14U <= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x)) 
                                      & (0x18U >= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x))) 
                                     & (6U <= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y))) 
                                    & (0xaU >= (IData)(vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y))))));
                    if (vlTOPp->__Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__Vfuncout) {
                        vlTOPp->vga_raycast_demo__DOT__hit = 1U;
                        vlTOPp->vga_raycast_demo__DOT__hit_tile_x 
                            = vlTOPp->vga_raycast_demo__DOT__r__DOT__tx;
                        vlTOPp->vga_raycast_demo__DOT__hit_tile_y 
                            = vlTOPp->vga_raycast_demo__DOT__r__DOT__ty;
                        vlTOPp->vga_raycast_demo__DOT__dist_steps 
                            = (0x1ffU & vlTOPp->vga_raycast_demo__DOT__r__DOT__i);
                        goto __Vlabel1;
                    }
                    if (VL_GTES_III(1,18,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dx, vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dy)) {
                        vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp 
                            = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp 
                                           + vlTOPp->vga_raycast_demo__DOT__r__DOT__step_x));
                        vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                            = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                                           + vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dy));
                        vlTOPp->vga_raycast_demo__DOT__side = 0U;
                        if (VL_GTES_III(1,18,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__err, vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dx)) {
                            vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp 
                                = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp 
                                               + vlTOPp->vga_raycast_demo__DOT__r__DOT__step_y));
                            vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                                = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                                               - vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dx));
                            vlTOPp->vga_raycast_demo__DOT__side = 1U;
                        }
                    } else {
                        vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp 
                            = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__y_fp 
                                           + vlTOPp->vga_raycast_demo__DOT__r__DOT__step_y));
                        vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                            = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                                           + vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dx));
                        vlTOPp->vga_raycast_demo__DOT__side = 1U;
                        if (VL_GTES_III(1,18,18, vlTOPp->vga_raycast_demo__DOT__r__DOT__err, vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dy)) {
                            vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp 
                                = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__x_fp 
                                               + vlTOPp->vga_raycast_demo__DOT__r__DOT__step_x));
                            vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                                = (0x3ffffU & (vlTOPp->vga_raycast_demo__DOT__r__DOT__err 
                                               - vlTOPp->vga_raycast_demo__DOT__r__DOT__abs_dy));
                            vlTOPp->vga_raycast_demo__DOT__side = 0U;
                        }
                    }
                    vlTOPp->vga_raycast_demo__DOT__r__DOT__i 
                        = ((IData)(1U) + vlTOPp->vga_raycast_demo__DOT__r__DOT__i);
                }
                __Vlabel2: ;
            }
            __Vlabel1: ;
        }
    }
    vlTOPp->vga_raycast_demo__DOT__shade = ((0xb4U 
                                             < (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps))
                                             ? 1U : 
                                            ((0x78U 
                                              < (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps))
                                              ? 3U : 
                                             ((0x50U 
                                               < (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps))
                                               ? 6U
                                               : ((0x28U 
                                                   < (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps))
                                                   ? 9U
                                                   : 0xcU))));
    vlTOPp->vga_raycast_demo__DOT__wall_lit = (0xfU 
                                               & ((0x78U 
                                                   < (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps))
                                                   ? 
                                                  ((IData)(vlTOPp->vga_raycast_demo__DOT__shade) 
                                                   >> 3U)
                                                   : 
                                                  ((0x5aU 
                                                    < (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps))
                                                    ? 
                                                   ((IData)(vlTOPp->vga_raycast_demo__DOT__shade) 
                                                    >> 2U)
                                                    : 
                                                   ((0x3cU 
                                                     < (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps))
                                                     ? 
                                                    ((IData)(vlTOPp->vga_raycast_demo__DOT__shade) 
                                                     >> 1U)
                                                     : (IData)(vlTOPp->vga_raycast_demo__DOT__shade)))));
    vlTOPp->vga_raycast_demo__DOT__wall_half = (0x3ffU 
                                                & ((IData)(6U) 
                                                   + 
                                                   VL_DIV_III(32, (IData)(0xb4U), 
                                                              ((IData)(1U) 
                                                               + (IData)(vlTOPp->vga_raycast_demo__DOT__dist_steps)))));
    vlTOPp->vga_raycast_demo__DOT__wall_top = (0x3ffU 
                                               & ((IData)(0xf0U) 
                                                  - (IData)(vlTOPp->vga_raycast_demo__DOT__wall_half)));
    vlTOPp->vga_raycast_demo__DOT__wall_bottom = (0x3ffU 
                                                  & ((IData)(0xf0U) 
                                                     + (IData)(vlTOPp->vga_raycast_demo__DOT__wall_half)));
    if (vlTOPp->active) {
        if (((IData)(vlTOPp->vc) < (IData)(vlTOPp->vga_raycast_demo__DOT__wall_top))) {
            vlTOPp->vga_r = 1U;
            vlTOPp->vga_g = 2U;
            vlTOPp->vga_b = (0xfU & ((IData)(4U) + 
                                     (7U & ((IData)(vlTOPp->vc) 
                                            >> 6U))));
        } else {
            if (((IData)(vlTOPp->vc) > (IData)(vlTOPp->vga_raycast_demo__DOT__wall_bottom))) {
                vlTOPp->vga_r = 1U;
                vlTOPp->vga_g = (0xfU & ((IData)(1U) 
                                         + (3U & ((IData)(vlTOPp->vc) 
                                                  >> 7U))));
                vlTOPp->vga_b = 1U;
            } else {
                if (vlTOPp->vga_raycast_demo__DOT__hit) {
                    if ((1U & ((((IData)(vlTOPp->vga_raycast_demo__DOT__hit_tile_x) 
                                 ^ (IData)(vlTOPp->vga_raycast_demo__DOT__hit_tile_y)) 
                                ^ (IData)(vlTOPp->vga_raycast_demo__DOT__side)) 
                               ^ ((IData)(vlTOPp->vc) 
                                  >> 3U)))) {
                        vlTOPp->vga_r = (0xfU & ((IData)(vlTOPp->vga_raycast_demo__DOT__side)
                                                  ? 
                                                 ((IData)(vlTOPp->vga_raycast_demo__DOT__wall_lit) 
                                                  >> 1U)
                                                  : (IData)(vlTOPp->vga_raycast_demo__DOT__wall_lit)));
                        vlTOPp->vga_b = 0U;
                        vlTOPp->vga_g = (0xfU & ((IData)(vlTOPp->vga_raycast_demo__DOT__wall_lit) 
                                                 >> 2U));
                    } else {
                        vlTOPp->vga_r = 0U;
                        vlTOPp->vga_g = (0xfU & ((IData)(vlTOPp->vga_raycast_demo__DOT__side)
                                                  ? 
                                                 ((IData)(vlTOPp->vga_raycast_demo__DOT__wall_lit) 
                                                  >> 1U)
                                                  : (IData)(vlTOPp->vga_raycast_demo__DOT__wall_lit)));
                        vlTOPp->vga_b = (0xfU & ((IData)(vlTOPp->vga_raycast_demo__DOT__wall_lit) 
                                                 >> 2U));
                    }
                } else {
                    vlTOPp->vga_r = 0xfU;
                    vlTOPp->vga_g = 0U;
                    vlTOPp->vga_b = 0U;
                }
            }
        }
    } else {
        vlTOPp->vga_r = 0U;
        vlTOPp->vga_g = 0U;
        vlTOPp->vga_b = 0U;
    }
}

void Vvga_raycast_demo::_eval_initial(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_eval_initial\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk_25 = vlTOPp->clk_25;
    vlTOPp->__Vclklast__TOP__rst = vlTOPp->rst;
}

void Vvga_raycast_demo::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::final\n"); );
    // Variables
    Vvga_raycast_demo__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vvga_raycast_demo::_eval_settle(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_eval_settle\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__4(vlSymsp);
}

void Vvga_raycast_demo::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_ctor_var_reset\n"); );
    // Body
    clk_25 = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    move_fwd = VL_RAND_RESET_I(1);
    move_back = VL_RAND_RESET_I(1);
    turn_left = VL_RAND_RESET_I(1);
    turn_right = VL_RAND_RESET_I(1);
    strafe_left = VL_RAND_RESET_I(1);
    strafe_right = VL_RAND_RESET_I(1);
    active = VL_RAND_RESET_I(1);
    hc = VL_RAND_RESET_I(10);
    vc = VL_RAND_RESET_I(10);
    hsync = VL_RAND_RESET_I(1);
    vsync = VL_RAND_RESET_I(1);
    vga_r = VL_RAND_RESET_I(4);
    vga_g = VL_RAND_RESET_I(4);
    vga_b = VL_RAND_RESET_I(4);
    vga_raycast_demo__DOT__hit = VL_RAND_RESET_I(1);
    vga_raycast_demo__DOT__side = VL_RAND_RESET_I(1);
    vga_raycast_demo__DOT__dist_steps = VL_RAND_RESET_I(9);
    vga_raycast_demo__DOT__hit_tile_x = VL_RAND_RESET_I(5);
    vga_raycast_demo__DOT__hit_tile_y = VL_RAND_RESET_I(5);
    vga_raycast_demo__DOT__ray_angle = VL_RAND_RESET_I(8);
    vga_raycast_demo__DOT__sin_out = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__cos_out = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__move_sin = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__move_cos = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__wall_half = VL_RAND_RESET_I(10);
    vga_raycast_demo__DOT__wall_top = VL_RAND_RESET_I(10);
    vga_raycast_demo__DOT__wall_bottom = VL_RAND_RESET_I(10);
    vga_raycast_demo__DOT__shade = VL_RAND_RESET_I(4);
    vga_raycast_demo__DOT__wall_lit = VL_RAND_RESET_I(4);
    vga_raycast_demo__DOT__sweep = VL_RAND_RESET_I(9);
    vga_raycast_demo__DOT__sweep_shift = VL_RAND_RESET_I(9);
    vga_raycast_demo__DOT__ray_angle_sum = VL_RAND_RESET_I(9);
    vga_raycast_demo__DOT__player_x = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__player_y = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__cam_angle = VL_RAND_RESET_I(8);
    vga_raycast_demo__DOT__demo_tick = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__move_dx = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__move_dy = VL_RAND_RESET_I(16);
    vga_raycast_demo__DOT__manual_active = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            vga_raycast_demo__DOT__l__DOT__sin_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            vga_raycast_demo__DOT__l__DOT__cos_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    vga_raycast_demo__DOT__l__DOT__i = VL_RAND_RESET_I(32);
    vga_raycast_demo__DOT__l__DOT__tmp_sin = VL_RAND_RESET_I(32);
    vga_raycast_demo__DOT__l__DOT__tmp_cos = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            vga_raycast_demo__DOT__cam_lut__DOT__sin_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            vga_raycast_demo__DOT__cam_lut__DOT__cos_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    vga_raycast_demo__DOT__cam_lut__DOT__i = VL_RAND_RESET_I(32);
    vga_raycast_demo__DOT__cam_lut__DOT__tmp_sin = VL_RAND_RESET_I(32);
    vga_raycast_demo__DOT__cam_lut__DOT__tmp_cos = VL_RAND_RESET_I(32);
    vga_raycast_demo__DOT__r__DOT__i = VL_RAND_RESET_I(32);
    vga_raycast_demo__DOT__r__DOT__x_fp = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__y_fp = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__abs_dx = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__abs_dy = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__err = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__step_x = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__step_y = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__dir_x_ext = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__dir_y_ext = VL_RAND_RESET_I(18);
    vga_raycast_demo__DOT__r__DOT__tx = VL_RAND_RESET_I(5);
    vga_raycast_demo__DOT__r__DOT__ty = VL_RAND_RESET_I(5);
    __Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__x = VL_RAND_RESET_I(5);
    __Vfunc_vga_raycast_demo__DOT__r__DOT__is_wall__2__y = VL_RAND_RESET_I(5);
}
