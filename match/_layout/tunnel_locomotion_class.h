// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TunnelLocomotionClass::TunnelLocomotionClass 0x00728A00, which chains
//   the LocomotionClass base constructor 0x0055A6C0 and writes every one of its
//   own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 from the citing instruction beside it. YRpp ships a
//   TunnelLocomotionClass header with no member list, so nothing here is a lift.
//
//   sizeof = 0x3C, proven twice and independently:
//     * the single allocation site - `PUSH 0x3C` @0x006C463C, `CALL operator new
//       (0x007C8E17)` @0x006C463E, `MOV ECX,EAX`, `CALL 0x00728A00` @0x006C464C;
//     * the class's own virtual size accessor, persist-vtable (0x007F5AF0) slot
//       +0x24 = 0x0072A200, whose entire body is `MOV EAX,0x3C / RET`.
//   The layout CLOSES: the last ctor write is the byte at 0x38 (@0x00728A39) and
//   0x38+1 = 0x39 <= 0x3C, with three untouched tail bytes.
//
//   RTTI: ".?AVTunnelLocomotionClass@@", type descriptor 0x00844AA0, has exactly
//   TWO complete object locators - 0x0080CB48 (base offset 0, vtable 0x007F5AF0,
//   IPersistStream) and 0x0080CAE8 (base offset 4, vtable 0x007F5A24,
//   ILocomotion). No IPiggyback. So this class has FlyLocomotionClass's base
//   shape: it derives LocomotionClass directly and its own data starts at 0x18,
//   with 0x18 a data member rather than a vptr.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_TUNNEL_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_TUNNEL_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/loco_base.h"
#include "frame_timer.h"

struct TunnelDirStruct;

class TunnelLocomotionClass : public LocomotionClass
{
public:
    // FUNCTION: GAMEMD 0x728A00 (constructor)
    TunnelLocomotionClass();
    // The stream loader's in-place construction.
    TunnelLocomotionClass(int) : LocomotionClass(0), Timer_28(0), unknown_34(0) {}
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);  // 3   0x72A110
    virtual HRESULT __stdcall Load(IStream* pStm);       // 5   0x72A150
    virtual int Size();                                  // 9   0x72A200
    virtual LocoCoord __stdcall Destination();           // 5   0x728A90
    virtual int __stdcall CanEnterCell(int cell);        // 7   0x72A090
    virtual bool __stdcall IsToHaveShadow();             // 8   0x72A060
    virtual int __stdcall ZGradient();                   // 15  0x72A020
    virtual void __stdcall DoTurn(unsigned long dir);    // 19  0x72A0E0
    virtual int __stdcall InWhichLayer();                // 29  0x72A1A0
    virtual bool __stdcall IsMovingNow();                // 32  0x728A60
    virtual int __stdcall CanFire();                     // 35  0x72A1C0

    void FinishIfTimed();                                // 0x729480
    void FUN_00729AA0();                                 // 0x729AA0
    void FUN_007294E0();                                 // 0x7294E0

    int       State;       // +0x18 movement state word (0 = idle)
    LocoCoord DestCoord;   // +0x1C
    CDTimerClass Timer_28; // +0x28 (what it times is unproven)
    int       unknown_34;  // +0x34
    char      unknown_38;  // +0x38
};

GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, State)     == 0x18);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, DestCoord) == 0x1C);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, Timer_28)  == 0x28);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(sizeof(TunnelLocomotionClass)                == 0x3C);

#endif  // GG_MATCH_LAYOUT_TUNNEL_LOCOMOTION_CLASS_H
