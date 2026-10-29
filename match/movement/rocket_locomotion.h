// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, tables and slot wiring read from the retail gamemd.exe v1.001:
//   RTTI .?AVRocketLocomotionClass@@ (TD 0x8399C8): primary table 0x7F0BE8
//   (COL 0x808968, base_offset 0, 10 slots), ILocomotion table 0x7F0B1C (COL
//   0x808908, base_offset 4, 50 slots); allocation `push 0x60; call 0x7C8E17`
//   at 0x6C44BC feeds the constructor 0x661EC0 (the only caller). Member names
//   are behavioural; YRpp consulted for naming only.
//
// RocketLocomotionClass address-scoped view. The class has no IPiggyback
// subobject in the observed RTTI; the leaf fields begin at +0x18. Names below
// describe observed use and do not assert a complete game-class hierarchy.
//
//   +0x00 vptr (IPersistStream side, 0x7F0BE8)   +0x04 vptr (ILocomotion, 0x7F0B1C)
//   +0x08 Owner  +0x0C LinkedTo  +0x10 Powered  +0x11 Dirty  +0x14 RefCount
//   +0x18 Destination (3 ints)       ctor <- the 3 words at 0xB04E38
//   +0x24 PhaseTimer (RocketRateTimer, 4 ints) ctor Start = frame (0xA8ED84), TimeLeft 0, Length 0
//   +0x34 SmokeTimer (3 ints)        ctor Start = frame, TimeLeft 0
//   +0x40 State                      ctor 0; IsMovingNow = State in 3..5
//   +0x44 unknown_44                 never written by the ctor
//   +0x48 Elevation (double, 8 bytes) 0x44/0x48 as a double pair: Process does
//         `FADD [ESI+0x44]` (ESI = ILocomotion subobject) -> complete +0x48
//   +0x50 Armed (byte, ctor 1)  +0x51 Flag (byte, ctor 0)
//   +0x54 Pitch (float)  +0x58 unknown_58 (int, ctor 0)  +0x5C unknown_5C
// Complete-object offsets are used below; ILocomotion-table bodies see
// `this` = complete + 4 and the compiler adjusts.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_ROCKET_LOCOMOTION_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_ROCKET_LOCOMOTION_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <new.h>
#include "loco_base.h"
#include "rocket_locomotion_views.h"
#include "loco_foot.h"
#include "../core/vector_array_init_methods.h"
#include "../ai/aircraft_tracker_class.h"
#include "../ai/aircraft_tracker_update_methods.h"
#include "rocket_locomotion_globals_view.h"
#include "rocket_locomotion_helpers.h"
#include "rocket_locomotion_math.h"
#include "rocket_locomotion_timer.h"

// ---- value types private to this class view ---------------------------------

// Tracker storage at 0x887888 is the existing 400-element vector region.
// Calls reuse the matched tracker methods; Rocket creates no storage owner.

// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) - inferred double ABI from Rocket callers.
extern "C" double __cdecl RocketAtan(double v);

// GLOBAL: GAMEMD 0x7E9AD0 - CLSID of this locomotor (16 bytes, read from the image).
extern "C" const CLSID CLSID_RocketLocomotion;

// VTABLE: GAMEMD 0x7F0BE8 (IPersistStream side) and GAMEMD 0x7F0B1C (ILocomotion side)
class RocketLocomotionClass : public LocomotionClass
{
public:
    RocketLocomotionClass();                                    // 0x661EC0
    // No-init constructor used by Load's placement new (0x663410).
    RocketLocomotionClass(int) : LocomotionClass(0), PhaseTimer(RocketNoInit()) {}
    virtual ~RocketLocomotionClass() {}
    // Scalar deleting wrapper 0x6635C0 is compiler output (marker in the .cpp).

    // Primary table (slots 3, 5, 9 are this class's; 0-2, 4, 6, 7 inherit).
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);      // 0x6633D0
    virtual HRESULT __stdcall Load(IStream* pStm);              // 0x663410
    virtual int Size();                                         // 0x6635B0

    // ILocomotion table overrides; slot numbers are relative to AP 0x7F0B1C.
    virtual bool __stdcall IsMoving();                          // slot 4, 0x661F50
    virtual LocoCoord __stdcall Destination();                  // slot 5, hidden return, 0x661FB0
    virtual Matrix3D __stdcall DrawMatrix(unsigned int* key); // slot 9, 0x663470
    virtual bool __stdcall Process();                           // slot 16, partial, 0x6622C0
    virtual void __stdcall MoveTo(LocoCoord to);                // slot 17, partial, 0x6632E0
    virtual void __stdcall StopMoving();                        // slot 18, 0x6633C0
    virtual int __stdcall InWhichLayer();                       // slot 29, 0x663460
    virtual bool __stdcall IsMovingNow();                       // slot 32, 0x661F90

    // Non-table helpers called by Process (not in this partition; bound by address).
    // FUNCTION: GAMEMD 0x6620F0 (decl; reloc) - __thiscall, spec pointer, bool result.
    bool FUN_006620F0(RocketMissileSpec* spec);
    // FUNCTION: GAMEMD 0x663030 (decl; reloc) - __thiscall.
    void FUN_00663030();
    // FUNCTION: GAMEMD 0x662240 (decl) - pitch from the foot to the destination.
    double FUN_00662240();

    // ---- members (complete-object offsets) ----
    LocoCoord   Destination_;       // +0x18
    RocketRateTimer  PhaseTimer;         // +0x24 (16 bytes, ends at +0x34)
    RocketTimer SmokeTimer;         // +0x34
    int         State;              // +0x40
    int         unknown_44;         // +0x44
    double      Elevation;          // +0x48
    bool        Armed;              // +0x50
    bool        Flag;               // +0x51
    float       Pitch;              // +0x54
    int         unknown_58;         // +0x58
    int         unknown_5C;         // +0x5C
};
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, Destination_) == 0x18);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, PhaseTimer)   == 0x24);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, SmokeTimer)   == 0x34);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, State)        == 0x40);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_44)   == 0x44);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, Elevation)    == 0x48);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, Armed)        == 0x50);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, Flag)         == 0x51);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, Pitch)        == 0x54);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_58)   == 0x58);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_5C)   == 0x5C);
// Allocation: `push 0x60; call 0x7C8E17` at 0x6C44BC (the constructor's only caller).
GG_STATIC_ASSERT(sizeof(RocketLocomotionClass) == 0x60);

// Field accesses in the implementation use direct casts from LinkedTo to this
// non-owning prefix view. This expresses observed offsets without claiming a
// complete FootClass layout.

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_ROCKET_LOCOMOTION_H
