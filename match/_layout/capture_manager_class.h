// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: CaptureManagerClass ctor FUN_0x004717D0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0). Argument binding is unusually explicit here,
//   which pins three members outright: arg1 pOwner -> 0x48, arg2
//   nMaxControlNodes -> 0x3C, arg3 bInfiniteControl -> 0x40.
//   sizeof: `PUSH 0x50` before the ctor call at its allocation site.
//   RTTI: 0x007E4B40 / 0x007E4B24 (+ the +8/+0xC tables) resolve to
//   ".?AVCaptureManagerClass@@" at descriptor 0x81B6C8 (name +8),
//   establishing the class key. The ctor writes the four table pointers;
//   the explicit-vptr AbstractClass view does not recover the full COM hierarchy.
//
//   The ctor also re-proves the DynamicVectorClass layout asserted in
//   vector_class.h: for ControlNodes at 0x24 it stores the vptr at 0x24
//   (0x007E4BA4), Items 0x28, Capacity 0x2C, flag bytes 0x30=1/0x31=0,
//   Count 0x34 and CapacityIncrement 0x38 = 0xA.
//
//   YRpp supplied naming hypotheses only; the offsets below are binary facts.
//   The original declarations and semantic member names are not recovered
//   merely by confirming their storage offsets.
//
// CaptureManagerClass — mind-control link bookkeeping. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_CAPTURE_MANAGER_CLASS_H
#define GG_MATCH_LAYOUT_CAPTURE_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "vector_class.h"

struct Sink_004A1C00;
struct Gg_IStream;
struct Guid_472960;
struct Techno_00471C90;
class TechnoClass;
class HouseClass;

class CaptureManagerClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x471C90
    bool CanCapture(Techno_00471C90* target) const;
    // FUNCTION: GAMEMD 0x471FF0
    bool FreeUnit(TechnoClass* unit);
    // FUNCTION: GAMEMD 0x472140
    void FreeAll();
    // FUNCTION: GAMEMD 0x4722A0
    bool CannotControlAnyMore() const;
    // FUNCTION: GAMEMD 0x4722C0
    bool IsControllingSomething() const;
    // FUNCTION: GAMEMD 0x4722D0
    int GetControlledCount();
    // FUNCTION: GAMEMD 0x4722E0
    bool FUN_004722E0() const;
    // FUNCTION: GAMEMD 0x4722F0
    HouseClass* GetOriginalOwner(TechnoClass* unit) const;
    // FUNCTION: GAMEMD 0x4723B0 (declaration-only ABI binding; ownership provisional)
    void FUN_004723B0(TechnoClass* unit);
    // FUNCTION: GAMEMD 0x472640
    bool NeedsToDrawLinks();
    // FUNCTION: GAMEMD 0x4726C0
    bool FUN_004726C0(bool* state);
    // FUNCTION: GAMEMD 0x4726F0
    void FUN_004726F0(Sink_004A1C00* sink);
    // FUNCTION: GAMEMD 0x4728E0
    long __stdcall Save(Gg_IStream* stream, int clearDirty);
    // FUNCTION: GAMEMD 0x472960
    long __stdcall GetClassID(Guid_472960* outGuid);
    // FUNCTION: GAMEMD 0x4729A0
    int FUN_004729A0();
    // FUNCTION: GAMEMD 0x4729B0
    int FUN_004729B0();
    // FUNCTION: GAMEMD 0x4729C0
    CaptureManagerClass* FUN_004729C0(unsigned int flags);


    DynamicVectorClassLayout ControlNodes;           // +0x24 (0x18) ctor vptr @0x004717EF, fields
                                               //   @0x004717E6/0x004717E9/0x004717E2/0x004717FD/0x004717F6
    int           MaxControlNodes;             // +0x3C ctor = arg2 @0x00471822
    unsigned char InfiniteMindControl;         // +0x40 ctor = arg3 @0x00471825
    unsigned char OverloadDeathSoundPlayed;    // +0x41 ctor @0x00471828
    unsigned char align_42[2];                 // +0x42
    int           OverloadPipState;            // +0x44 ctor @0x00471832
    void*         Owner;                       // +0x48 TechnoClass*; ctor = arg1 @0x00471800
    int           OverloadDamageDelay;         // +0x4C ctor MOV [ESI+0x4C],0x1E @0x0047182B;
                                               //   closes the object at 0x50
};

GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes)            == 0x24);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, MaxControlNodes)         == 0x3C);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, InfiniteMindControl)     == 0x40);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, OverloadDeathSoundPlayed)== 0x41);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, OverloadPipState)        == 0x44);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, Owner)                   == 0x48);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, OverloadDamageDelay)     == 0x4C);
GG_STATIC_ASSERT(sizeof(CaptureManagerClass)                            == 0x50);

// VTABLE: GAMEMD 0x007E4B40  CaptureManagerClass
// VTABLE: GAMEMD 0x007E4B24  CaptureManagerClass::(+0x04)
// VTABLE: GAMEMD 0x007E4B1C  CaptureManagerClass::(+0x08)
// VTABLE: GAMEMD 0x007E4B14  CaptureManagerClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_CAPTURE_MANAGER_CLASS_H
