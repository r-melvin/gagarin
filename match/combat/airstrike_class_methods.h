// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x41D830 (`MOV AL,[ECX+0x3C]`, `CMP EAX,[ECX+0x50]`). Method names
//   cross-checked against YRpp AirstrikeClass.h (consult-only, no LICENSE),
//   which binds StartMission @0x41D830 and ResetTarget @0x41DA20.
//   The rest of the layout comes from the constructor 0x41D380 (stores at
//   +0x24..+0x5C), the stream loader 0x41D6F0 (pointers swizzled at +0x4C,
//   +0x50, +0x54, +0x58, +0x5C) and slot 12 (0x41DD30 returns 0x60). RTTI:
//   TypeDescriptor ".?AVAirstrikeClass@@" (name at 0x8180C8), primary table
//   0x7E29A8.
#ifndef GG_MATCH_COMBAT_AIRSTRIKE_CLASS_METHODS_H
#define GG_MATCH_COMBAT_AIRSTRIKE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_class.h"
#include "../core/vector_class.h"

class ObjectClass;
class TechnoClass;
struct FootClass;
struct AircraftTypeClass;

// VTABLE: GAMEMD 0x7E29A8 (IPersistStream side)
// VTABLE: GAMEMD 0x7E298C (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E2984 (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E297C (INoticeSource side, +0x0C)
class AirstrikeClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x41D380 (declaration; constructor) -- RET 4.
    AirstrikeClass(TechnoClass* owner);
    // FUNCTION: GAMEMD 0x41D490 (declaration; no-initialisation constructor)
    AirstrikeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x41D4C0 (declaration; destructor; slot 8 = 0x41DD50)
    virtual ~AirstrikeClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x41D6F0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x41D780
    virtual int vf_11();                                                  // 11  0x41DD40
    virtual int vf_12();                                                  // 12  0x41DD30
    virtual void vf_23();                                                 // 23  0x41DC50

    // Declared ascending by retail address.
    void StartMission(ObjectClass* target);   // GAMEMD 0x41D830 (matched)

    // Retail callees we are NOT matching here — declared (no body) so cl emits
    // reloc-normalised direct __thiscall calls.
    void BeginMission(ObjectClass* target);   // GAMEMD 0x41D860 (placeholder name)
    void ResetTarget(ObjectClass* target);    // GAMEMD 0x41DA20
    // FUNCTION: GAMEMD 0x41DC60 (declaration)
    void FUN_0041DC60();
    // FUNCTION: GAMEMD 0x41DD10 (declaration)
    void FUN_0041DD10();

    int                 unknown_24;   // +0x24 from the owner's type +0x61C
    int                 unknown_28;   // +0x28 from the owner's type +0x620
    int                 unknown_2C;   // +0x2C
    int                 unknown_30;   // +0x30 the limit 0x41DC60 counts +0x34 up to
    int                 unknown_34;   // +0x34
    int                 unknown_38;   // +0x38
    bool                unknown_3C;   // +0x3C gates which path StartMission takes
    bool                unknown_3D;   // +0x3D
    unsigned char       _pad3E[2];    // +0x3E
    int                 unknown_40;   // +0x40 the frame 0x41DD10 stamps
    int                 unknown_44;   // +0x44 from the owner's type +0x62C
    int                 unknown_48;   // +0x48 from the owner's type +0x630
    TechnoClass*        unknown_4C;   // +0x4C the owner
    ObjectClass*        Target;       // +0x50
    AircraftTypeClass*  unknown_54;   // +0x54 from the owner's type +0x624
    AircraftTypeClass*  unknown_58;   // +0x58 from the owner's type +0x628
    FootClass*          unknown_5C;   // +0x5C

    // GLOBAL: GAMEMD 0x889FB8
    static DynamicVectorClass<AirstrikeClass*> Array;
};
GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_3D) == 0x3D);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, Target) == 0x50);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(sizeof(AirstrikeClass) == 0x60);

#endif  // GG_MATCH_COMBAT_AIRSTRIKE_CLASS_METHODS_H
