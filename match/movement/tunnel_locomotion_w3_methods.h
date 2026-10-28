// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TunnelLocomotionClass as a LocomotionClass subclass (complete-object offsets).
//   Members from the constructor at 0x728A00 (see _layout/tunnel_locomotion_class.h);
//   the ILocomotion overrides below are read off the RTTI-named vtable 0x7F5A24.
#ifndef GG_MATCH_MOVEMENT_TUNNEL_LOCOMOTION_W3_METHODS_H
#define GG_MATCH_MOVEMENT_TUNNEL_LOCOMOTION_W3_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_base.h"

struct TunnelDirStruct;

class TunnelLocomotionClass : public LocomotionClass
{
public:
    virtual bool __stdcall IsToHaveShadow();             // 8   0x72A060
    virtual int __stdcall ZGradient();                   // 15  0x72A020
    virtual void __stdcall DoTurn(unsigned long dir);    // 19  0x72A0E0
    virtual int __stdcall InWhichLayer();                // 29  0x72A1A0
    virtual bool __stdcall IsMovingNow();                // 32  0x728A60
    virtual int __stdcall CanFire();                     // 35  0x72A1C0

    int       State;       // +0x18 movement state word (0 = idle)
    LocoCoord DestCoord;   // +0x1C
};

GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, State)     == 0x18);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, DestCoord) == 0x1C);

#endif  // GG_MATCH_MOVEMENT_TUNNEL_LOCOMOTION_W3_METHODS_H
