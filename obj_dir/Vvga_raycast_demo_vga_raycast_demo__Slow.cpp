// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_raycast_demo.h for the primary calling header

#include "Vvga_raycast_demo_vga_raycast_demo.h"
#include "Vvga_raycast_demo__Syms.h"

#include "verilated_dpi.h"

//==========

VL_CTOR_IMP(Vvga_raycast_demo_vga_raycast_demo) {
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vvga_raycast_demo_vga_raycast_demo::__Vconfigure(Vvga_raycast_demo__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
}

Vvga_raycast_demo_vga_raycast_demo::~Vvga_raycast_demo_vga_raycast_demo() {
}

void Vvga_raycast_demo_vga_raycast_demo::_initial__TOP__vga_raycast_demo__1(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_raycast_demo_vga_raycast_demo::_initial__TOP__vga_raycast_demo__1\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i = 0U;
    while (VL_GTS_III(1,32,32, 0x100U, vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i)) {
        vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__tmp_sin 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * sin(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i)) 
                                  / 256.0))));
        vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__tmp_cos 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * cos(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i)) 
                                  / 256.0))));
        vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__sin_table[(0xffU 
                                                                       & vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i)] 
            = (0xffffU & vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__tmp_sin);
        vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__cos_table[(0xffU 
                                                                       & vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i)] 
            = (0xffffU & vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__tmp_cos);
        vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i 
            = ((IData)(1U) + vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__i);
    }
    vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i = 0U;
    while (VL_GTS_III(1,32,32, 0x100U, vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i)) {
        vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__tmp_sin 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * sin(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i)) 
                                  / 256.0))));
        vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__tmp_cos 
            = VL_RTOI_I_D((1.63840000000000000e+04 
                           * cos(((6.28318530000000042e+00 
                                   * VL_ITOR_D_I(vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i)) 
                                  / 256.0))));
        vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__sin_table[(0xffU 
                                                                 & vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i)] 
            = (0xffffU & vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__tmp_sin);
        vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__cos_table[(0xffU 
                                                                 & vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i)] 
            = (0xffffU & vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__tmp_cos);
        vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i 
            = ((IData)(1U) + vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__i);
    }
}

void Vvga_raycast_demo_vga_raycast_demo::_settle__TOP__vga_raycast_demo__4(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_raycast_demo_vga_raycast_demo::_settle__TOP__vga_raycast_demo__4\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active 
        = ((((((IData)(vlTOPp->move_fwd) | (IData)(vlTOPp->move_back)) 
              | (IData)(vlTOPp->turn_left)) | (IData)(vlTOPp->turn_right)) 
            | (IData)(vlTOPp->strafe_left)) | (IData)(vlTOPp->strafe_right));
    vlSymsp->TOP__vga_raycast_demo.active = ((0x280U 
                                              > (IData)(vlSymsp->TOP__vga_raycast_demo.hc)) 
                                             & (0x1e0U 
                                                > (IData)(vlSymsp->TOP__vga_raycast_demo.vc)));
    vlSymsp->TOP__vga_raycast_demo.__PVT__sweep = (0x1ffU 
                                                   & ((0xffU 
                                                       & ((IData)(vlSymsp->TOP__vga_raycast_demo.hc) 
                                                          >> 2U)) 
                                                      - (IData)(0x50U)));
    vlSymsp->TOP__vga_raycast_demo.__PVT__sweep_shift 
        = (0x1ffU & VL_SHIFTRS_III(9,9,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__sweep), 1U));
    vlSymsp->TOP__vga_raycast_demo.__PVT__ray_angle_sum 
        = (0x1ffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle) 
                     + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__sweep_shift)));
    vlSymsp->TOP__vga_raycast_demo.__PVT__ray_angle 
        = (0xffU & (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__ray_angle_sum));
    vlSymsp->TOP__vga_raycast_demo.__PVT__move_sin 
        = vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__sin_table
        [vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle];
    vlSymsp->TOP__vga_raycast_demo.__PVT__move_cos 
        = vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__cos_table
        [vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle];
    vlSymsp->TOP__vga_raycast_demo.__PVT__sin_out = 
        vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__sin_table
        [vlSymsp->TOP__vga_raycast_demo.__PVT__ray_angle];
    vlSymsp->TOP__vga_raycast_demo.__PVT__cos_out = 
        vlSymsp->TOP__vga_raycast_demo.__PVT__l__DOT__cos_table
        [vlSymsp->TOP__vga_raycast_demo.__PVT__ray_angle];
    vlSymsp->TOP__vga_raycast_demo.__PVT__hit = 0U;
    vlSymsp->TOP__vga_raycast_demo.__PVT__hit_tile_x = 0U;
    vlSymsp->TOP__vga_raycast_demo.__PVT__hit_tile_y = 0U;
    vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps = 0U;
    vlSymsp->TOP__vga_raycast_demo.__PVT__side = 0U;
    vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp 
        = vlSymsp->TOP__vga_raycast_demo.__PVT__player_x;
    vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp 
        = vlSymsp->TOP__vga_raycast_demo.__PVT__player_y;
    vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_x_ext 
        = ((0x30000U & ((- (IData)((1U & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__cos_out) 
                                          >> 0xfU)))) 
                        << 0x10U)) | (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__cos_out));
    vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_y_ext 
        = ((0x30000U & ((- (IData)((1U & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__sin_out) 
                                          >> 0xfU)))) 
                        << 0x10U)) | (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__sin_out));
    if (((0U != VL_EXTENDS_II(32,16, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__cos_out))) 
         | (0U != VL_EXTENDS_II(32,16, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__sin_out))))) {
        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dx 
            = (0x3ffffU & (VL_GTS_III(1,32,32, 0U, 
                                      VL_EXTENDS_II(32,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_x_ext))
                            ? (- vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_x_ext)
                            : vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_x_ext));
        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dy 
            = (0x3ffffU & (VL_GTS_III(1,32,32, 0U, 
                                      VL_EXTENDS_II(32,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_y_ext))
                            ? (- vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_y_ext)
                            : vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_y_ext));
        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__step_x 
            = (VL_GTS_III(1,32,32, 0U, VL_EXTENDS_II(32,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_x_ext))
                ? 0x3ffe0U : 0x20U);
        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__step_y 
            = (VL_GTS_III(1,32,32, 0U, VL_EXTENDS_II(32,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__dir_y_ext))
                ? 0x3ffe0U : 0x20U);
        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err = 0U;
        {
            {
                vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__i = 0U;
                while (VL_GTS_III(1,32,32, 0x100U, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__i)) {
                    if ((((VL_GTS_III(1,32,32, 0U, 
                                      VL_EXTENDS_II(32,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp)) 
                           | VL_GTS_III(1,32,32, 0U, 
                                        VL_EXTENDS_II(32,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp))) 
                          | (0x2000U <= vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp)) 
                         | (0x2000U <= vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp))) {
                        vlSymsp->TOP__vga_raycast_demo.__PVT__hit = 1U;
                        vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps 
                            = (0x1ffU & vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__i);
                        goto __Vlabel2;
                    }
                    vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__tx 
                        = (0x1fU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp 
                                    >> 8U));
                    vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__ty 
                        = (0x1fU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp 
                                    >> 8U));
                    vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y 
                        = vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__ty;
                    vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x 
                        = vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__tx;
                    vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__Vfuncout 
                        = (((((0U == (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x)) 
                              | (0U == (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y))) 
                             | (0x1fU == (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x))) 
                            | (0x1fU == (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y))) 
                           | ((((0U == (7U & (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x))) 
                                & (0U != (7U & (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y)))) 
                               | ((0U == (7U & (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y))) 
                                  & (0U != (7U & (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x))))) 
                              | (((((0xaU <= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x)) 
                                    & (0xeU >= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x))) 
                                   & (0xaU <= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y))) 
                                  & (0xeU >= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y))) 
                                 | ((((0x14U <= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x)) 
                                      & (0x18U >= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__x))) 
                                     & (6U <= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y))) 
                                    & (0xaU >= (IData)(vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__y))))));
                    if (vlSymsp->TOP__vga_raycast_demo.__Vfunc_r__DOT__is_wall__2__Vfuncout) {
                        vlSymsp->TOP__vga_raycast_demo.__PVT__hit = 1U;
                        vlSymsp->TOP__vga_raycast_demo.__PVT__hit_tile_x 
                            = vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__tx;
                        vlSymsp->TOP__vga_raycast_demo.__PVT__hit_tile_y 
                            = vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__ty;
                        vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps 
                            = (0x1ffU & vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__i);
                        goto __Vlabel1;
                    }
                    if (VL_GTES_III(1,18,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dx, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dy)) {
                        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp 
                            = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp 
                                           + vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__step_x));
                        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                            = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                                           + vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dy));
                        vlSymsp->TOP__vga_raycast_demo.__PVT__side = 0U;
                        if (VL_GTES_III(1,18,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dx)) {
                            vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp 
                                = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp 
                                               + vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__step_y));
                            vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                                = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                                               - vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dx));
                            vlSymsp->TOP__vga_raycast_demo.__PVT__side = 1U;
                        }
                    } else {
                        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp 
                            = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__y_fp 
                                           + vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__step_y));
                        vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                            = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                                           + vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dx));
                        vlSymsp->TOP__vga_raycast_demo.__PVT__side = 1U;
                        if (VL_GTES_III(1,18,18, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err, vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dy)) {
                            vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp 
                                = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__x_fp 
                                               + vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__step_x));
                            vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                                = (0x3ffffU & (vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__err 
                                               - vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__abs_dy));
                            vlSymsp->TOP__vga_raycast_demo.__PVT__side = 0U;
                        }
                    }
                    vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__i 
                        = ((IData)(1U) + vlSymsp->TOP__vga_raycast_demo.__PVT__r__DOT__i);
                }
                __Vlabel2: ;
            }
            __Vlabel1: ;
        }
    }
    vlSymsp->TOP__vga_raycast_demo.__PVT__shade = (
                                                   (0xb4U 
                                                    < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps))
                                                    ? 1U
                                                    : 
                                                   ((0x78U 
                                                     < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps))
                                                     ? 3U
                                                     : 
                                                    ((0x50U 
                                                      < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps))
                                                      ? 6U
                                                      : 
                                                     ((0x28U 
                                                       < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps))
                                                       ? 9U
                                                       : 0xcU))));
    vlSymsp->TOP__vga_raycast_demo.__PVT__wall_lit 
        = (0xfU & ((0x78U < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps))
                    ? ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__shade) 
                       >> 3U) : ((0x5aU < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps))
                                  ? ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__shade) 
                                     >> 2U) : ((0x3cU 
                                                < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps))
                                                ? ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__shade) 
                                                   >> 1U)
                                                : (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__shade)))));
    vlSymsp->TOP__vga_raycast_demo.__PVT__wall_half 
        = (0x3ffU & ((IData)(6U) + VL_DIV_III(32, (IData)(0xb4U), 
                                              ((IData)(1U) 
                                               + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__dist_steps)))));
    vlSymsp->TOP__vga_raycast_demo.__PVT__wall_top 
        = (0x3ffU & ((IData)(0xf0U) - (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_half)));
    vlSymsp->TOP__vga_raycast_demo.__PVT__wall_bottom 
        = (0x3ffU & ((IData)(0xf0U) + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_half)));
    if (vlSymsp->TOP__vga_raycast_demo.active) {
        if (((IData)(vlSymsp->TOP__vga_raycast_demo.vc) 
             < (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_top))) {
            vlSymsp->TOP__vga_raycast_demo.vga_r = 1U;
            vlSymsp->TOP__vga_raycast_demo.vga_g = 2U;
            vlSymsp->TOP__vga_raycast_demo.vga_b = 
                (0xfU & ((IData)(4U) + (7U & ((IData)(vlSymsp->TOP__vga_raycast_demo.vc) 
                                              >> 6U))));
        } else {
            if (((IData)(vlSymsp->TOP__vga_raycast_demo.vc) 
                 > (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_bottom))) {
                vlSymsp->TOP__vga_raycast_demo.vga_r = 1U;
                vlSymsp->TOP__vga_raycast_demo.vga_g 
                    = (0xfU & ((IData)(1U) + (3U & 
                                              ((IData)(vlSymsp->TOP__vga_raycast_demo.vc) 
                                               >> 7U))));
                vlSymsp->TOP__vga_raycast_demo.vga_b = 1U;
            } else {
                if (vlSymsp->TOP__vga_raycast_demo.__PVT__hit) {
                    if ((1U & ((((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__hit_tile_x) 
                                 ^ (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__hit_tile_y)) 
                                ^ (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__side)) 
                               ^ ((IData)(vlSymsp->TOP__vga_raycast_demo.vc) 
                                  >> 3U)))) {
                        vlSymsp->TOP__vga_raycast_demo.vga_r 
                            = (0xfU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__side)
                                        ? ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_lit) 
                                           >> 1U) : (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_lit)));
                        vlSymsp->TOP__vga_raycast_demo.vga_b = 0U;
                        vlSymsp->TOP__vga_raycast_demo.vga_g 
                            = (0xfU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_lit) 
                                       >> 2U));
                    } else {
                        vlSymsp->TOP__vga_raycast_demo.vga_r = 0U;
                        vlSymsp->TOP__vga_raycast_demo.vga_g 
                            = (0xfU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__side)
                                        ? ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_lit) 
                                           >> 1U) : (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_lit)));
                        vlSymsp->TOP__vga_raycast_demo.vga_b 
                            = (0xfU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__wall_lit) 
                                       >> 2U));
                    }
                } else {
                    vlSymsp->TOP__vga_raycast_demo.vga_r = 0xfU;
                    vlSymsp->TOP__vga_raycast_demo.vga_g = 0U;
                    vlSymsp->TOP__vga_raycast_demo.vga_b = 0U;
                }
            }
        }
    } else {
        vlSymsp->TOP__vga_raycast_demo.vga_r = 0U;
        vlSymsp->TOP__vga_raycast_demo.vga_g = 0U;
        vlSymsp->TOP__vga_raycast_demo.vga_b = 0U;
    }
}

void Vvga_raycast_demo_vga_raycast_demo::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_raycast_demo_vga_raycast_demo::_ctor_var_reset\n"); );
    // Body
    clk_25 = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    move_fwd = VL_RAND_RESET_I(1);
    move_back = VL_RAND_RESET_I(1);
    turn_left = VL_RAND_RESET_I(1);
    turn_right = VL_RAND_RESET_I(1);
    strafe_left = VL_RAND_RESET_I(1);
    strafe_right = VL_RAND_RESET_I(1);
    hsync = VL_RAND_RESET_I(1);
    vsync = VL_RAND_RESET_I(1);
    vga_r = VL_RAND_RESET_I(4);
    vga_g = VL_RAND_RESET_I(4);
    vga_b = VL_RAND_RESET_I(4);
    active = VL_RAND_RESET_I(1);
    __PVT__hit = VL_RAND_RESET_I(1);
    __PVT__side = VL_RAND_RESET_I(1);
    hc = VL_RAND_RESET_I(10);
    vc = VL_RAND_RESET_I(10);
    __PVT__dist_steps = VL_RAND_RESET_I(9);
    __PVT__hit_tile_x = VL_RAND_RESET_I(5);
    __PVT__hit_tile_y = VL_RAND_RESET_I(5);
    __PVT__ray_angle = VL_RAND_RESET_I(8);
    __PVT__sin_out = VL_RAND_RESET_I(16);
    __PVT__cos_out = VL_RAND_RESET_I(16);
    __PVT__move_sin = VL_RAND_RESET_I(16);
    __PVT__move_cos = VL_RAND_RESET_I(16);
    __PVT__wall_half = VL_RAND_RESET_I(10);
    __PVT__wall_top = VL_RAND_RESET_I(10);
    __PVT__wall_bottom = VL_RAND_RESET_I(10);
    __PVT__shade = VL_RAND_RESET_I(4);
    __PVT__wall_lit = VL_RAND_RESET_I(4);
    __PVT__sweep = VL_RAND_RESET_I(9);
    __PVT__sweep_shift = VL_RAND_RESET_I(9);
    __PVT__ray_angle_sum = VL_RAND_RESET_I(9);
    __PVT__player_x = VL_RAND_RESET_I(16);
    __PVT__player_y = VL_RAND_RESET_I(16);
    __PVT__cam_angle = VL_RAND_RESET_I(8);
    __PVT__demo_tick = VL_RAND_RESET_I(16);
    __PVT__move_dx = VL_RAND_RESET_I(16);
    __PVT__move_dy = VL_RAND_RESET_I(16);
    __PVT__manual_active = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            __PVT__l__DOT__sin_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            __PVT__l__DOT__cos_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    __PVT__l__DOT__i = VL_RAND_RESET_I(32);
    __PVT__l__DOT__tmp_sin = VL_RAND_RESET_I(32);
    __PVT__l__DOT__tmp_cos = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            __PVT__cam_lut__DOT__sin_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            __PVT__cam_lut__DOT__cos_table[__Vi0] = VL_RAND_RESET_I(16);
    }}
    __PVT__cam_lut__DOT__i = VL_RAND_RESET_I(32);
    __PVT__cam_lut__DOT__tmp_sin = VL_RAND_RESET_I(32);
    __PVT__cam_lut__DOT__tmp_cos = VL_RAND_RESET_I(32);
    __PVT__r__DOT__i = VL_RAND_RESET_I(32);
    __PVT__r__DOT__x_fp = VL_RAND_RESET_I(18);
    __PVT__r__DOT__y_fp = VL_RAND_RESET_I(18);
    __PVT__r__DOT__abs_dx = VL_RAND_RESET_I(18);
    __PVT__r__DOT__abs_dy = VL_RAND_RESET_I(18);
    __PVT__r__DOT__err = VL_RAND_RESET_I(18);
    __PVT__r__DOT__step_x = VL_RAND_RESET_I(18);
    __PVT__r__DOT__step_y = VL_RAND_RESET_I(18);
    __PVT__r__DOT__dir_x_ext = VL_RAND_RESET_I(18);
    __PVT__r__DOT__dir_y_ext = VL_RAND_RESET_I(18);
    __PVT__r__DOT__tx = VL_RAND_RESET_I(5);
    __PVT__r__DOT__ty = VL_RAND_RESET_I(5);
    __Vfunc_r__DOT__is_wall__2__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_r__DOT__is_wall__2__x = VL_RAND_RESET_I(5);
    __Vfunc_r__DOT__is_wall__2__y = VL_RAND_RESET_I(5);
}
