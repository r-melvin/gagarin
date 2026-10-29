// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: AircraftClass ctor FUN_0x00413D20 (chains FootClass ctor
//   FUN_0x004D31E0 at offset 0, CALL @0x00413D2B). Every member below is read
//   from a field-init store in that ctor. sizeof is read from the allocation
//   sites: `PUSH 0x6D8` before the ctor call at all 4 call sites found by
//   `ghidra x-ref to 0x413D20`.
//
//   RTTI (read from the binary, outranks any document): FIVE complete object
//   locators name ".?AVAircraftClass@@" — four with COL base-offset 0 / 4 / 8 /
//   12 (the primary table plus the three COM interface subobjects), and a fifth
//   at 0x007E2250 with COL base-offset **1728 == 0x6C0**. That fifth locator is
//   the independent, binary-side proof that a second base subobject (YRpp names
//   it IFlyControl) begins at 0x6C0 — which is exactly where the ctor stores
//   that vptr: `MOV dword [ESI+0x6C0],0x7E2250` @0x00413DA2. So AircraftClass's
//   own data starts at 0x6C4, not 0x6C0.
//
//   Cross-read against YRpp: 10 named members claimed, 10
//   confirmed. No disagreement found. (YRpp lists Type first and leaves the
//   IFlyControl vptr implicit in the base list; the binary places it at 0x6C0,
//   so the two agree once the second base subobject is written out.)
//
// AircraftClass — a flying object. Derives FootClass at offset 0
// (sizeof(FootClass) == 0x6C0) plus a second, vtable-bearing COM-style base at
// 0x6C0, and adds its own data from 0x6C4.
#ifndef GG_MATCH_LAYOUT_AIRCRAFT_CLASS_H
#define GG_MATCH_LAYOUT_AIRCRAFT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "foot_class.h"
#include "com_interfaces.h"   // IFlyControl

class AircraftTypeClass;

class AircraftClass : public FootClass, public IFlyControl
{
public:
    // CALLEE: GAMEMD 0x00413D20 (decl; reloc) -- constructor as the class factory calls it.
    AircraftClass(int unknown_arg0 = 0, int unknown_arg1 = 0);
    virtual HRESULT __stdcall Load(IStream* pStm);   // 5   0x41B430
    virtual int vf_11();   // 11  0x41C180
    virtual int vf_12();   // 12  0x41C170
    // +0x6C0: IFlyControl vptr; ctor: MOV [ESI+0x6C0],0x7E2250 @0x00413DA2;
    //   RTTI COL base-offset 0x6C0 confirms it.
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0x414290
    virtual ULONG __stdcall AddRef();                                     // 0x4142F0
    virtual ULONG __stdcall Release();                                    // 0x414300
    // IFlyControl overrides (table 0x7E2250 slots 3-8).
    virtual int __stdcall vf_03();   // 0x41B6A0
    virtual int __stdcall vf_04();   // 0x41B760
    virtual int __stdcall vf_05();   // 0x41B7D0
    virtual int __stdcall vf_06();   // 0x41B7F0
    virtual int __stdcall vf_07();   // 0x41B840
    virtual int __stdcall vf_08();   // 0x41B860
    // Native primary slot 288: two stack dwords, target pointer and flag.
    virtual void vf_125(int mission, int a2, int a3);           // 125 0x41BB30
    virtual void vf_122(int mission, bool a2);                  // 122 0x41BA90
    virtual bool vf_123();                                      // 123 0x41B870
    virtual void vf_124(int mission);                           // 124 0x41B9F0
    virtual void SetDestination(AbstractClass* target, bool a2); // 288 0x41AA80
    virtual void* vf_330(DynamicVectorClassLayout* a1, int a2, int a3);// 330 0x41BBD0
    // IPersist::GetClassID (slot 3), 0x41C190.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    // IPersistStream::Save (slot 6), 0x41B5C0: chains FootClass::Save.
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    // Native AircraftType virtual 0x41CB20 passes its this to ctor 0x413D20;
    // 0x413D3A stores that argument at +0x6C4.
    AircraftTypeClass* Type;                    // +0x6C4  AircraftTypeClass*; ctor: MOV [ESI+0x6C4],ECX(=pType) @0x00413D3A
    unsigned char ShouldLoseAmmo;          // +0x6C8  ctor: MOV byte [ESI+0x6C8],0 @0x00413D40
    unsigned char HasPassengers;           // +0x6C9  ctor: MOV byte [ESI+0x6C9],0 @0x00413D47
    unsigned char IsKamikaze;              // +0x6CA  ctor: MOV byte [ESI+0x6CA],0 @0x00413D4E
    unsigned char align_6CB;               // +0x6CB
    void*         DockNowHeadingTo;        // +0x6CC  BuildingClass*; ctor: MOV [ESI+0x6CC],0 @0x00413D55
    unsigned char unknown_bool_6D0;        // +0x6D0  ctor: MOV byte [ESI+0x6D0],0 @0x00413D5F
    unsigned char unknown_bool_6D1;        // +0x6D1  ctor: MOV byte [ESI+0x6D1],0 @0x00413D66
    unsigned char IsLocked;                // +0x6D2  ctor: MOV byte [ESI+0x6D2],0 @0x00413D6D
    signed char   NumParadropsLeft;        // +0x6D3  ctor: MOV byte [ESI+0x6D3],5 @0x00413D74
    unsigned char IsCarryallNotLanding;    // +0x6D4  ctor: MOV byte [ESI+0x6D4],AL(=1) @0x00413D7B
    unsigned char IsReturningFromAttackRun;// +0x6D5  ctor: MOV byte [ESI+0x6D5],AL(=1) @0x00413D81
    unsigned char align_6D6[2];            // +0x6D6  (closes the object at 0x6D8)
};

GG_STATIC_ASSERT(offsetof(AircraftClass, Type)                     == 0x6C4);
GG_STATIC_ASSERT(offsetof(AircraftClass, ShouldLoseAmmo)           == 0x6C8);
GG_STATIC_ASSERT(offsetof(AircraftClass, HasPassengers)            == 0x6C9);
GG_STATIC_ASSERT(offsetof(AircraftClass, IsKamikaze)               == 0x6CA);
GG_STATIC_ASSERT(offsetof(AircraftClass, DockNowHeadingTo)         == 0x6CC);
GG_STATIC_ASSERT(offsetof(AircraftClass, unknown_bool_6D0)         == 0x6D0);
GG_STATIC_ASSERT(offsetof(AircraftClass, unknown_bool_6D1)         == 0x6D1);
GG_STATIC_ASSERT(offsetof(AircraftClass, IsLocked)                 == 0x6D2);
GG_STATIC_ASSERT(offsetof(AircraftClass, NumParadropsLeft)         == 0x6D3);
GG_STATIC_ASSERT(offsetof(AircraftClass, IsCarryallNotLanding)     == 0x6D4);
GG_STATIC_ASSERT(offsetof(AircraftClass, IsReturningFromAttackRun) == 0x6D5);
GG_STATIC_ASSERT(sizeof(AircraftClass)                             == 0x6D8);

// VTABLE: GAMEMD 0x007E22A4  AircraftClass            (COL base 0)
// VTABLE: GAMEMD 0x007E2288  AircraftClass::(+0x04)   (COL base 4)
// VTABLE: GAMEMD 0x007E2280  AircraftClass::(+0x08)   (COL base 8)
// VTABLE: GAMEMD 0x007E2278  AircraftClass::(+0x0C)   (COL base 12)
// VTABLE: GAMEMD 0x007E2250  AircraftClass::(+0x6C0)  (COL base 0x6C0 — IFlyControl subobject)

#endif  // GG_MATCH_LAYOUT_AIRCRAFT_CLASS_H
