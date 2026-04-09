// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_raycast_demo.h for the primary calling header

#include "Vvga_raycast_demo_vga_raycast_demo.h"
#include "Vvga_raycast_demo__Syms.h"

#include "verilated_dpi.h"

//==========

VL_INLINE_OPT void Vvga_raycast_demo_vga_raycast_demo::_sequent__TOP__vga_raycast_demo__2(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_raycast_demo_vga_raycast_demo::_sequent__TOP__vga_raycast_demo__2\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlSymsp->TOP__vga_raycast_demo.vsync = (1U & (~ 
                                                  ((0x1eaU 
                                                    <= (IData)(vlSymsp->TOP__vga_raycast_demo.vc)) 
                                                   & (0x1ecU 
                                                      > (IData)(vlSymsp->TOP__vga_raycast_demo.vc)))));
    vlSymsp->TOP__vga_raycast_demo.hsync = (1U & (~ 
                                                  ((0x290U 
                                                    <= (IData)(vlSymsp->TOP__vga_raycast_demo.hc)) 
                                                   & (0x2f0U 
                                                      > (IData)(vlSymsp->TOP__vga_raycast_demo.hc)))));
}

VL_INLINE_OPT void Vvga_raycast_demo_vga_raycast_demo::_sequent__TOP__vga_raycast_demo__3(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_raycast_demo_vga_raycast_demo::_sequent__TOP__vga_raycast_demo__3\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vfunc_wall_at__0__Vfuncout;
    CData/*4:0*/ __Vfunc_wall_at__0__tx;
    CData/*4:0*/ __Vfunc_wall_at__0__ty;
    CData/*0:0*/ __Vfunc_wall_at__1__Vfuncout;
    CData/*4:0*/ __Vfunc_wall_at__1__tx;
    CData/*4:0*/ __Vfunc_wall_at__1__ty;
    CData/*7:0*/ __Vdly__cam_angle;
    SData/*15:0*/ __Vfunc_wall_at__0__pos_x;
    SData/*15:0*/ __Vfunc_wall_at__0__pos_y;
    SData/*15:0*/ __Vfunc_wall_at__1__pos_x;
    SData/*15:0*/ __Vfunc_wall_at__1__pos_y;
    SData/*15:0*/ __Vdly__player_x;
    SData/*15:0*/ __Vdly__player_y;
    SData/*15:0*/ __Vdly__demo_tick;
    SData/*9:0*/ __Vdly__hc;
    SData/*9:0*/ __Vdly__vc;
    // Body
    __Vdly__demo_tick = vlSymsp->TOP__vga_raycast_demo.__PVT__demo_tick;
    __Vdly__player_y = vlSymsp->TOP__vga_raycast_demo.__PVT__player_y;
    __Vdly__player_x = vlSymsp->TOP__vga_raycast_demo.__PVT__player_x;
    __Vdly__vc = vlSymsp->TOP__vga_raycast_demo.vc;
    __Vdly__hc = vlSymsp->TOP__vga_raycast_demo.hc;
    __Vdly__cam_angle = vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle;
    if (vlTOPp->rst) {
        __Vdly__demo_tick = 0U;
    } else {
        if (((0x31fU == (IData)(vlSymsp->TOP__vga_raycast_demo.hc)) 
             & (0x20cU == (IData)(vlSymsp->TOP__vga_raycast_demo.vc)))) {
            __Vdly__demo_tick = (0xffffU & ((IData)(1U) 
                                            + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__demo_tick)));
        }
    }
    if (vlTOPp->rst) {
        __Vdly__player_x = 0x380U;
        __Vdly__player_y = 0x380U;
    } else {
        if (((0x31fU == (IData)(vlSymsp->TOP__vga_raycast_demo.hc)) 
             & (0x20cU == (IData)(vlSymsp->TOP__vga_raycast_demo.vc)))) {
            vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx = 0U;
            vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy = 0U;
            if ((1U & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active)
                        ? (IData)(vlTOPp->move_fwd)
                        : (~ ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__demo_tick) 
                              >> 6U))))) {
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_cos), 7U)));
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_sin), 7U)));
            }
            if (((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active) 
                 & (IData)(vlTOPp->move_back))) {
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_cos), 7U)));
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_sin), 7U)));
            }
            if ((1U & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active)
                        ? (IData)(vlTOPp->strafe_left)
                        : ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__demo_tick) 
                           >> 8U)))) {
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_sin), 7U)));
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_cos), 7U)));
            }
            if (((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active) 
                 & (IData)(vlTOPp->strafe_right))) {
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_sin), 7U)));
                vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy 
                    = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_cos), 7U)));
            }
            __Vfunc_wall_at__0__pos_y = vlSymsp->TOP__vga_raycast_demo.__PVT__player_y;
            __Vfunc_wall_at__0__pos_x = (0xffffU & 
                                         ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__player_x) 
                                          + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx)));
            __Vfunc_wall_at__0__tx = (0x1fU & ((IData)(__Vfunc_wall_at__0__pos_x) 
                                               >> 8U));
            __Vfunc_wall_at__0__ty = (0x1fU & ((IData)(__Vfunc_wall_at__0__pos_y) 
                                               >> 8U));
            __Vfunc_wall_at__0__Vfuncout = (((((0U 
                                                == (IData)(__Vfunc_wall_at__0__tx)) 
                                               | (0U 
                                                  == (IData)(__Vfunc_wall_at__0__ty))) 
                                              | (0x1fU 
                                                 == (IData)(__Vfunc_wall_at__0__tx))) 
                                             | (0x1fU 
                                                == (IData)(__Vfunc_wall_at__0__ty))) 
                                            | ((((0U 
                                                  == 
                                                  (7U 
                                                   & (IData)(__Vfunc_wall_at__0__tx))) 
                                                 & (0U 
                                                    != 
                                                    (7U 
                                                     & (IData)(__Vfunc_wall_at__0__ty)))) 
                                                | ((0U 
                                                    == 
                                                    (7U 
                                                     & (IData)(__Vfunc_wall_at__0__ty))) 
                                                   & (0U 
                                                      != 
                                                      (7U 
                                                       & (IData)(__Vfunc_wall_at__0__tx))))) 
                                               | (((((0xaU 
                                                      <= (IData)(__Vfunc_wall_at__0__tx)) 
                                                     & (0xeU 
                                                        >= (IData)(__Vfunc_wall_at__0__tx))) 
                                                    & (0xaU 
                                                       <= (IData)(__Vfunc_wall_at__0__ty))) 
                                                   & (0xeU 
                                                      >= (IData)(__Vfunc_wall_at__0__ty))) 
                                                  | ((((0x14U 
                                                        <= (IData)(__Vfunc_wall_at__0__tx)) 
                                                       & (0x18U 
                                                          >= (IData)(__Vfunc_wall_at__0__tx))) 
                                                      & (6U 
                                                         <= (IData)(__Vfunc_wall_at__0__ty))) 
                                                     & (0xaU 
                                                        >= (IData)(__Vfunc_wall_at__0__ty))))));
            if ((1U & (~ (IData)(__Vfunc_wall_at__0__Vfuncout)))) {
                __Vdly__player_x = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__player_x) 
                                               + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dx)));
            }
            __Vfunc_wall_at__1__pos_y = (0xffffU & 
                                         ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__player_y) 
                                          + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy)));
            __Vfunc_wall_at__1__pos_x = vlSymsp->TOP__vga_raycast_demo.__PVT__player_x;
            __Vfunc_wall_at__1__tx = (0x1fU & ((IData)(__Vfunc_wall_at__1__pos_x) 
                                               >> 8U));
            __Vfunc_wall_at__1__ty = (0x1fU & ((IData)(__Vfunc_wall_at__1__pos_y) 
                                               >> 8U));
            __Vfunc_wall_at__1__Vfuncout = (((((0U 
                                                == (IData)(__Vfunc_wall_at__1__tx)) 
                                               | (0U 
                                                  == (IData)(__Vfunc_wall_at__1__ty))) 
                                              | (0x1fU 
                                                 == (IData)(__Vfunc_wall_at__1__tx))) 
                                             | (0x1fU 
                                                == (IData)(__Vfunc_wall_at__1__ty))) 
                                            | ((((0U 
                                                  == 
                                                  (7U 
                                                   & (IData)(__Vfunc_wall_at__1__tx))) 
                                                 & (0U 
                                                    != 
                                                    (7U 
                                                     & (IData)(__Vfunc_wall_at__1__ty)))) 
                                                | ((0U 
                                                    == 
                                                    (7U 
                                                     & (IData)(__Vfunc_wall_at__1__ty))) 
                                                   & (0U 
                                                      != 
                                                      (7U 
                                                       & (IData)(__Vfunc_wall_at__1__tx))))) 
                                               | (((((0xaU 
                                                      <= (IData)(__Vfunc_wall_at__1__tx)) 
                                                     & (0xeU 
                                                        >= (IData)(__Vfunc_wall_at__1__tx))) 
                                                    & (0xaU 
                                                       <= (IData)(__Vfunc_wall_at__1__ty))) 
                                                   & (0xeU 
                                                      >= (IData)(__Vfunc_wall_at__1__ty))) 
                                                  | ((((0x14U 
                                                        <= (IData)(__Vfunc_wall_at__1__tx)) 
                                                       & (0x18U 
                                                          >= (IData)(__Vfunc_wall_at__1__tx))) 
                                                      & (6U 
                                                         <= (IData)(__Vfunc_wall_at__1__ty))) 
                                                     & (0xaU 
                                                        >= (IData)(__Vfunc_wall_at__1__ty))))));
            if ((1U & (~ (IData)(__Vfunc_wall_at__1__Vfuncout)))) {
                __Vdly__player_y = (0xffffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__player_y) 
                                               + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__move_dy)));
            }
        }
    }
    if (vlTOPp->rst) {
        __Vdly__hc = 0U;
        __Vdly__vc = 0U;
    } else {
        if ((0x31fU == (IData)(vlSymsp->TOP__vga_raycast_demo.hc))) {
            __Vdly__vc = ((0x20cU == (IData)(vlSymsp->TOP__vga_raycast_demo.vc))
                           ? 0U : (0x3ffU & ((IData)(1U) 
                                             + (IData)(vlSymsp->TOP__vga_raycast_demo.vc))));
            __Vdly__hc = 0U;
        } else {
            __Vdly__hc = (0x3ffU & ((IData)(1U) + (IData)(vlSymsp->TOP__vga_raycast_demo.hc)));
        }
    }
    if (vlTOPp->rst) {
        __Vdly__cam_angle = 0U;
    } else {
        if (((0x31fU == (IData)(vlSymsp->TOP__vga_raycast_demo.hc)) 
             & (0x20cU == (IData)(vlSymsp->TOP__vga_raycast_demo.vc)))) {
            if (((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active) 
                 & (IData)(vlTOPp->turn_left))) {
                __Vdly__cam_angle = (0xffU & ((IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle) 
                                              - (IData)(2U)));
            }
            if ((1U & ((~ (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active)) 
                       | (IData)(vlTOPp->turn_right)))) {
                __Vdly__cam_angle = (0xffU & ((IData)(2U) 
                                              + (IData)(vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle)));
            }
        }
    }
    vlSymsp->TOP__vga_raycast_demo.__PVT__demo_tick 
        = __Vdly__demo_tick;
    vlSymsp->TOP__vga_raycast_demo.__PVT__player_x 
        = __Vdly__player_x;
    vlSymsp->TOP__vga_raycast_demo.__PVT__player_y 
        = __Vdly__player_y;
    vlSymsp->TOP__vga_raycast_demo.vc = __Vdly__vc;
    vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle 
        = __Vdly__cam_angle;
    vlSymsp->TOP__vga_raycast_demo.hc = __Vdly__hc;
    vlSymsp->TOP__vga_raycast_demo.__PVT__move_sin 
        = vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__sin_table
        [vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle];
    vlSymsp->TOP__vga_raycast_demo.__PVT__move_cos 
        = vlSymsp->TOP__vga_raycast_demo.__PVT__cam_lut__DOT__cos_table
        [vlSymsp->TOP__vga_raycast_demo.__PVT__cam_angle];
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

VL_INLINE_OPT void Vvga_raycast_demo_vga_raycast_demo::_combo__TOP__vga_raycast_demo__5(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_raycast_demo_vga_raycast_demo::_combo__TOP__vga_raycast_demo__5\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlSymsp->TOP__vga_raycast_demo.__PVT__manual_active 
        = ((((((IData)(vlTOPp->move_fwd) | (IData)(vlTOPp->move_back)) 
              | (IData)(vlTOPp->turn_left)) | (IData)(vlTOPp->turn_right)) 
            | (IData)(vlTOPp->strafe_left)) | (IData)(vlTOPp->strafe_right));
}
