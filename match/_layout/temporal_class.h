// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   RTTI: primary vtable 0x7F5180 (IPersistStream), 0x7F5164 (IRTTITypeInfo,
//   +0x04), 0x7F515C (INoticeSink, +0x08), 0x7F5154 (INoticeSource, +0x0C),
//   stored by every constructor (0x71A450, 0x71A4E0, 0x71A5A0). Size 0x50 from
//   slot 12 (0x71B190 returns 0x50); slot 11 (0x71B1A0) returns 0x46.
//   Fields from the constructor 0x71A4E0 (one argument stored at +0x24, the
//   rest cleared) and from Load 0x71A660, which swizzles the six pointers at
//   +0x24, +0x28, +0x40, +0x44, +0x38 and +0x3C.
//
//   The older address-local views (combat/temporal_class_methods.h,
//   temporal_class_let_go_methods.h, temporal_class_warp_target_methods.h)
//   disagree about which of +0x40 / +0x44 is the forward link; nothing in this
//   header's bodies decides it, so both keep placeholder names here.
//   GetWarpPerStep and Detach are declared under the names their matched
//   definitions in combat/temporal_class_methods.cpp carry, so the calls
//   bind to them. Those bodies cannot move into this unit: under its /Ob2
//   (needed for the initialisers) cl expands GetWarpPerStep into 0x71A760,
//   which retail calls.
#ifndef GG_MATCH_LAYOUT_TEMPORAL_CLASS_H
#define GG_MATCH_LAYOUT_TEMPORAL_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "../vector_class.h"
#include "../frame_counter.h"

struct Obj_004A1D30;

// A frame timer: StartTime from the frame counter 0xA8ED84, an unwritten
// clock slot, TimeLeft (the 0x71A450 / 0x71A4E0 stores to +0x2C / +0x34).
struct TemporalTimer
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    TemporalTimer() : StartTime(CurrentFrame), TimeLeft(0) {}
    TemporalTimer(const AbstractNoInit&) {}
};
GG_STATIC_ASSERT(offsetof(TemporalTimer, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(TemporalTimer) == 0xC);

class TemporalClass;
class TechnoClass;
class SuperClass;

// VTABLE: GAMEMD 0x7F5180 (IPersistStream side)
// VTABLE: GAMEMD 0x7F5164 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7F515C (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7F5154 (INoticeSource side, +0x0C)
class TemporalClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x71A450 (declaration)
    TemporalClass();
    // FUNCTION: GAMEMD 0x71A4E0 (declaration)
    TemporalClass(TechnoClass* owner);
    // FUNCTION: GAMEMD 0x71A5A0 (declaration; no-initialisation constructor)
    TemporalClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x71A5D0 (declaration; destructor; slot 8 = 0x71B1B0)
    virtual ~TemporalClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x71A720
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x71A660
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x71A700
    virtual int vf_11();                                                  // 11  0x71B1A0
    virtual int vf_12();                                                  // 12  0x71B190
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x71A650

    // FUNCTION: GAMEMD 0x71A760 (declaration; slot 23 of the primary vtable 0x7F517C)
    virtual void vf_23();
    // FUNCTION: GAMEMD 0x71AB10 (decl; reloc) -- the warp per step of a chain;
    // defined in combat/temporal_class_methods.cpp under this name.
    int GetWarpPerStep(int depth = 0) const;
    // FUNCTION: GAMEMD 0x71AB60 (declaration)
    void FUN_0071AB60(void* object);
    // FUNCTION: GAMEMD 0x71ABC0 (decl; reloc)
    void FUN_0071ABC0();
    // FUNCTION: GAMEMD 0x71ACB0 (declaration)
    void FUN_0071ACB0();
    // FUNCTION: GAMEMD 0x71ACD0 (declaration)
    void FUN_0071ACD0();
    // FUNCTION: GAMEMD 0x71AD30 (declaration)
    void FUN_0071AD30();
    // FUNCTION: GAMEMD 0x71AD40 (decl; reloc) -- defined in
    // combat/temporal_class_methods.cpp under this name.
    void JustLetGo();
    // FUNCTION: GAMEMD 0x71AE50 (decl; reloc) -- can this warp the target.
    bool FUN_0071AE50(TechnoClass* target);
    // FUNCTION: GAMEMD 0x71ADB0 (declaration)
    void FUN_0071ADB0();
    // FUNCTION: GAMEMD 0x71ADE0 (decl; reloc) -- defined in
    // combat/temporal_class_methods.cpp under this name.
    void Detach();
    // FUNCTION: GAMEMD 0x71AF20 (declaration)
    void FUN_0071AF20(TechnoClass* target);

    TechnoClass*        Owner;       // +0x24 ctor argument @0x0071A51C
    TechnoClass*        Target;      // +0x28 ctor @0x0071A51F; its TemporalTargetingMe (+0x278) points back
    TemporalTimer       unknown_2C;  // +0x2C ctor @0x0071A529..0x0071A52F
    void*               unknown_38;  // +0x38 ctor @0x0071A58E; swizzled by Load
    SuperClass*         unknown_3C;  // +0x3C ctor @0x0071A591; swizzled by Load; 0x71A760 calls SuperClass::SetOnHold (0x6CB4D0) on it
    TemporalClass*      unknown_40;  // +0x40 ctor @0x0071A532; a chain link
    TemporalClass*      unknown_44;  // +0x44 ctor @0x0071A535; a chain link
    int                 unknown_48;  // +0x48 ctor @0x0071A588
    mutable int         unknown_4C;  // +0x4C ctor @0x0071A58B; cached by 0x71A760 and by the const 0x71AB10

    // GLOBAL: GAMEMD 0xB0EC60
    static DynamicVectorClass<TemporalClass*> Array;
};
GG_STATIC_ASSERT(offsetof(TemporalClass, Owner)      == 0x24);
GG_STATIC_ASSERT(offsetof(TemporalClass, Target)     == 0x28);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(sizeof(TemporalClass) == 0x50);

#endif  // GG_MATCH_LAYOUT_TEMPORAL_CLASS_H
