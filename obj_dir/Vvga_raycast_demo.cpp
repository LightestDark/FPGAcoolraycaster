// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_raycast_demo.h for the primary calling header

#include "Vvga_raycast_demo.h"
#include "Vvga_raycast_demo__Syms.h"

//==========

void Vvga_raycast_demo::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vvga_raycast_demo::eval\n"); );
    Vvga_raycast_demo__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("raycaster.v", 136, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vvga_raycast_demo::_eval_initial_loop(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("raycaster.v", 136, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vvga_raycast_demo::_sequent__TOP__2(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_sequent__TOP__2\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->vsync = (1U & (~ ((0x1eaU <= (IData)(vlTOPp->vc)) 
                              & (0x1ecU > (IData)(vlTOPp->vc)))));
    vlTOPp->hsync = (1U & (~ ((0x290U <= (IData)(vlTOPp->hc)) 
                              & (0x2f0U > (IData)(vlTOPp->hc)))));
}

VL_INLINE_OPT void Vvga_raycast_demo::_sequent__TOP__3(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_sequent__TOP__3\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__0__Vfuncout;
    CData/*4:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__0__tx;
    CData/*4:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__0__ty;
    CData/*0:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__1__Vfuncout;
    CData/*4:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__1__tx;
    CData/*4:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__1__ty;
    CData/*7:0*/ __Vdly__vga_raycast_demo__DOT__cam_angle;
    SData/*15:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__0__pos_x;
    SData/*15:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__0__pos_y;
    SData/*15:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__1__pos_x;
    SData/*15:0*/ __Vfunc_vga_raycast_demo__DOT__wall_at__1__pos_y;
    SData/*15:0*/ __Vdly__vga_raycast_demo__DOT__player_x;
    SData/*15:0*/ __Vdly__vga_raycast_demo__DOT__player_y;
    SData/*15:0*/ __Vdly__vga_raycast_demo__DOT__demo_tick;
    SData/*9:0*/ __Vdly__hc;
    SData/*9:0*/ __Vdly__vc;
    // Body
    __Vdly__vga_raycast_demo__DOT__demo_tick = vlTOPp->vga_raycast_demo__DOT__demo_tick;
    __Vdly__vga_raycast_demo__DOT__player_y = vlTOPp->vga_raycast_demo__DOT__player_y;
    __Vdly__vga_raycast_demo__DOT__player_x = vlTOPp->vga_raycast_demo__DOT__player_x;
    __Vdly__vc = vlTOPp->vc;
    __Vdly__hc = vlTOPp->hc;
    __Vdly__vga_raycast_demo__DOT__cam_angle = vlTOPp->vga_raycast_demo__DOT__cam_angle;
    if (vlTOPp->rst) {
        __Vdly__vga_raycast_demo__DOT__demo_tick = 0U;
    } else {
        if (((0x31fU == (IData)(vlTOPp->hc)) & (0x20cU 
                                                == (IData)(vlTOPp->vc)))) {
            __Vdly__vga_raycast_demo__DOT__demo_tick 
                = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->vga_raycast_demo__DOT__demo_tick)));
        }
    }
    if (vlTOPp->rst) {
        __Vdly__vga_raycast_demo__DOT__player_x = 0x380U;
        __Vdly__vga_raycast_demo__DOT__player_y = 0x380U;
    } else {
        if (((0x31fU == (IData)(vlTOPp->hc)) & (0x20cU 
                                                == (IData)(vlTOPp->vc)))) {
            vlTOPp->vga_raycast_demo__DOT__move_dx = 0U;
            vlTOPp->vga_raycast_demo__DOT__move_dy = 0U;
            if ((1U & ((IData)(vlTOPp->vga_raycast_demo__DOT__manual_active)
                        ? (IData)(vlTOPp->move_fwd)
                        : (~ ((IData)(vlTOPp->vga_raycast_demo__DOT__demo_tick) 
                              >> 6U))))) {
                vlTOPp->vga_raycast_demo__DOT__move_dx 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dx) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_cos), 7U)));
                vlTOPp->vga_raycast_demo__DOT__move_dy 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dy) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_sin), 7U)));
            }
            if (((IData)(vlTOPp->vga_raycast_demo__DOT__manual_active) 
                 & (IData)(vlTOPp->move_back))) {
                vlTOPp->vga_raycast_demo__DOT__move_dx 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dx) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_cos), 7U)));
                vlTOPp->vga_raycast_demo__DOT__move_dy 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dy) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_sin), 7U)));
            }
            if ((1U & ((IData)(vlTOPp->vga_raycast_demo__DOT__manual_active)
                        ? (IData)(vlTOPp->strafe_left)
                        : ((IData)(vlTOPp->vga_raycast_demo__DOT__demo_tick) 
                           >> 8U)))) {
                vlTOPp->vga_raycast_demo__DOT__move_dx 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dx) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_sin), 7U)));
                vlTOPp->vga_raycast_demo__DOT__move_dy 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dy) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_cos), 7U)));
            }
            if (((IData)(vlTOPp->vga_raycast_demo__DOT__manual_active) 
                 & (IData)(vlTOPp->strafe_right))) {
                vlTOPp->vga_raycast_demo__DOT__move_dx 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dx) 
                                  - VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_sin), 7U)));
                vlTOPp->vga_raycast_demo__DOT__move_dy 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__move_dy) 
                                  + VL_SHIFTRS_III(16,16,32, (IData)(vlTOPp->vga_raycast_demo__DOT__move_cos), 7U)));
            }
            __Vfunc_vga_raycast_demo__DOT__wall_at__0__pos_y 
                = vlTOPp->vga_raycast_demo__DOT__player_y;
            __Vfunc_vga_raycast_demo__DOT__wall_at__0__pos_x 
                = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__player_x) 
                              + (IData)(vlTOPp->vga_raycast_demo__DOT__move_dx)));
            __Vfunc_vga_raycast_demo__DOT__wall_at__0__tx 
                = (0x1fU & ((IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__pos_x) 
                            >> 8U));
            __Vfunc_vga_raycast_demo__DOT__wall_at__0__ty 
                = (0x1fU & ((IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__pos_y) 
                            >> 8U));
            __Vfunc_vga_raycast_demo__DOT__wall_at__0__Vfuncout 
                = (((((0U == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx)) 
                      | (0U == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty))) 
                     | (0x1fU == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx))) 
                    | (0x1fU == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty))) 
                   | ((((0U == (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx))) 
                        & (0U != (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty)))) 
                       | ((0U == (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty))) 
                          & (0U != (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx))))) 
                      | (((((0xaU <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx)) 
                            & (0xeU >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx))) 
                           & (0xaU <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty))) 
                          & (0xeU >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty))) 
                         | ((((0x14U <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx)) 
                              & (0x18U >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__tx))) 
                             & (6U <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty))) 
                            & (0xaU >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__ty))))));
            if ((1U & (~ (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__0__Vfuncout)))) {
                __Vdly__vga_raycast_demo__DOT__player_x 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__player_x) 
                                  + (IData)(vlTOPp->vga_raycast_demo__DOT__move_dx)));
            }
            __Vfunc_vga_raycast_demo__DOT__wall_at__1__pos_y 
                = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__player_y) 
                              + (IData)(vlTOPp->vga_raycast_demo__DOT__move_dy)));
            __Vfunc_vga_raycast_demo__DOT__wall_at__1__pos_x 
                = vlTOPp->vga_raycast_demo__DOT__player_x;
            __Vfunc_vga_raycast_demo__DOT__wall_at__1__tx 
                = (0x1fU & ((IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__pos_x) 
                            >> 8U));
            __Vfunc_vga_raycast_demo__DOT__wall_at__1__ty 
                = (0x1fU & ((IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__pos_y) 
                            >> 8U));
            __Vfunc_vga_raycast_demo__DOT__wall_at__1__Vfuncout 
                = (((((0U == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx)) 
                      | (0U == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty))) 
                     | (0x1fU == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx))) 
                    | (0x1fU == (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty))) 
                   | ((((0U == (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx))) 
                        & (0U != (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty)))) 
                       | ((0U == (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty))) 
                          & (0U != (7U & (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx))))) 
                      | (((((0xaU <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx)) 
                            & (0xeU >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx))) 
                           & (0xaU <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty))) 
                          & (0xeU >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty))) 
                         | ((((0x14U <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx)) 
                              & (0x18U >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__tx))) 
                             & (6U <= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty))) 
                            & (0xaU >= (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__ty))))));
            if ((1U & (~ (IData)(__Vfunc_vga_raycast_demo__DOT__wall_at__1__Vfuncout)))) {
                __Vdly__vga_raycast_demo__DOT__player_y 
                    = (0xffffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__player_y) 
                                  + (IData)(vlTOPp->vga_raycast_demo__DOT__move_dy)));
            }
        }
    }
    if (vlTOPp->rst) {
        __Vdly__hc = 0U;
        __Vdly__vc = 0U;
    } else {
        if ((0x31fU == (IData)(vlTOPp->hc))) {
            __Vdly__vc = ((0x20cU == (IData)(vlTOPp->vc))
                           ? 0U : (0x3ffU & ((IData)(1U) 
                                             + (IData)(vlTOPp->vc))));
            __Vdly__hc = 0U;
        } else {
            __Vdly__hc = (0x3ffU & ((IData)(1U) + (IData)(vlTOPp->hc)));
        }
    }
    if (vlTOPp->rst) {
        __Vdly__vga_raycast_demo__DOT__cam_angle = 0U;
    } else {
        if (((0x31fU == (IData)(vlTOPp->hc)) & (0x20cU 
                                                == (IData)(vlTOPp->vc)))) {
            if (((IData)(vlTOPp->vga_raycast_demo__DOT__manual_active) 
                 & (IData)(vlTOPp->turn_left))) {
                __Vdly__vga_raycast_demo__DOT__cam_angle 
                    = (0xffU & ((IData)(vlTOPp->vga_raycast_demo__DOT__cam_angle) 
                                - (IData)(2U)));
            }
            if ((1U & ((~ (IData)(vlTOPp->vga_raycast_demo__DOT__manual_active)) 
                       | (IData)(vlTOPp->turn_right)))) {
                __Vdly__vga_raycast_demo__DOT__cam_angle 
                    = (0xffU & ((IData)(2U) + (IData)(vlTOPp->vga_raycast_demo__DOT__cam_angle)));
            }
        }
    }
    vlTOPp->vga_raycast_demo__DOT__demo_tick = __Vdly__vga_raycast_demo__DOT__demo_tick;
    vlTOPp->vga_raycast_demo__DOT__player_x = __Vdly__vga_raycast_demo__DOT__player_x;
    vlTOPp->vga_raycast_demo__DOT__player_y = __Vdly__vga_raycast_demo__DOT__player_y;
    vlTOPp->vc = __Vdly__vc;
    vlTOPp->vga_raycast_demo__DOT__cam_angle = __Vdly__vga_raycast_demo__DOT__cam_angle;
    vlTOPp->hc = __Vdly__hc;
    vlTOPp->vga_raycast_demo__DOT__move_sin = vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__sin_table
        [vlTOPp->vga_raycast_demo__DOT__cam_angle];
    vlTOPp->vga_raycast_demo__DOT__move_cos = vlTOPp->vga_raycast_demo__DOT__cam_lut__DOT__cos_table
        [vlTOPp->vga_raycast_demo__DOT__cam_angle];
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

VL_INLINE_OPT void Vvga_raycast_demo::_combo__TOP__5(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_combo__TOP__5\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->vga_raycast_demo__DOT__manual_active = 
        ((((((IData)(vlTOPp->move_fwd) | (IData)(vlTOPp->move_back)) 
            | (IData)(vlTOPp->turn_left)) | (IData)(vlTOPp->turn_right)) 
          | (IData)(vlTOPp->strafe_left)) | (IData)(vlTOPp->strafe_right));
}

void Vvga_raycast_demo::_eval(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_eval\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk_25) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk_25)))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
    }
    if ((((IData)(vlTOPp->clk_25) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk_25))) 
         | ((IData)(vlTOPp->rst) & (~ (IData)(vlTOPp->__Vclklast__TOP__rst))))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk_25 = vlTOPp->clk_25;
    vlTOPp->__Vclklast__TOP__rst = vlTOPp->rst;
}

VL_INLINE_OPT QData Vvga_raycast_demo::_change_request(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_change_request\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vvga_raycast_demo::_change_request_1(Vvga_raycast_demo__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_change_request_1\n"); );
    Vvga_raycast_demo* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vvga_raycast_demo::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_raycast_demo::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk_25 & 0xfeU))) {
        Verilated::overWidthError("clk_25");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((move_fwd & 0xfeU))) {
        Verilated::overWidthError("move_fwd");}
    if (VL_UNLIKELY((move_back & 0xfeU))) {
        Verilated::overWidthError("move_back");}
    if (VL_UNLIKELY((turn_left & 0xfeU))) {
        Verilated::overWidthError("turn_left");}
    if (VL_UNLIKELY((turn_right & 0xfeU))) {
        Verilated::overWidthError("turn_right");}
    if (VL_UNLIKELY((strafe_left & 0xfeU))) {
        Verilated::overWidthError("strafe_left");}
    if (VL_UNLIKELY((strafe_right & 0xfeU))) {
        Verilated::overWidthError("strafe_right");}
}
#endif  // VL_DEBUG
