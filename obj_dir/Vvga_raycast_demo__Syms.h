// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VVGA_RAYCAST_DEMO__SYMS_H_
#define _VVGA_RAYCAST_DEMO__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vvga_raycast_demo.h"

// SYMS CLASS
class Vvga_raycast_demo__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vvga_raycast_demo*             TOPp;
    
    // CREATORS
    Vvga_raycast_demo__Syms(Vvga_raycast_demo* topp, const char* namep);
    ~Vvga_raycast_demo__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
