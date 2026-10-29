// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: UnitClass ctor FUN_0x007353C0 (chains FootClass ctor
//   FUN_0x004D31E0 at offset 0, CALL @0x007353CE). Every offset in the
//   0x6C0..0x6E7 span below is read directly from a field-init store in that
//   ctor; the citations sit beside each member. The four COM vptrs are written
//   at 0x0073533A..0x0073544D and RTTI-confirmed (see below). sizeof is read
//   from the allocation site: `PUSH 0x8E8; CALL 0x007C8E17` @0x00688B37,
//   immediately before the ctor call @0x00688B66.
//
//   RTTI (read from the binary, outranks any document): the complete object
//   locator four bytes under each table resolves to ".?AVUnitClass@@" for all
//   four vptrs, with COL base-offset fields 0 / 4 / 8 / 12 — i.e. the three
//   COM interface subobjects sit at +4, +8 and +0xC exactly as the ctor stores
//   them.
//
//   Members cross-read against YRpp; all 15 named members it
//   claims were independently confirmed here. No disagreement found.
//
//   CAUTION for future scans: UnitClass::TryToDeploy @0x007393C0 contains
//   `MOV byte ptr [EBX+0x6CA],1` @0x007397ED and `[EBX+0x6CB]` @0x007397F4,
//   but EBX there is the *BuildingClass* being deployed (same body reads
//   [EBX+0x520] as a type pointer, which is BuildingClass::Type, not a
//   UnitClass field). Those two offsets are NOT UnitClass members.
//
// UnitClass — a tracked/wheeled vehicle. Derives FootClass at offset 0
// (sizeof(FootClass) == 0x6C0) and adds its own block from 0x6C0.
#ifndef GG_MATCH_LAYOUT_UNIT_CLASS_H
#define GG_MATCH_LAYOUT_UNIT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "foot_class.h"

class UnitTypeClass;
class HouseClass;

class UnitClass : public FootClass
{
public:
    // GAMEMD 0x7353C0. TClassFactory<UnitClass>::CreateInstance constructs with
    // (0, 0): PUSH 0; PUSH 0; MOV ECX,EAX; CALL 0x7353C0 @0x6C344D..0x6C3453.
    UnitClass(UnitTypeClass* type = 0, HouseClass* owner = 0);
    virtual ~UnitClass(); // external; retail scalar-deleting slot8=0x746E80
    virtual HRESULT __stdcall GetClassID(CLSID* id); // slot3 0x746DE0
    virtual HRESULT __stdcall Save(IStream* stream, BOOL clear); // slot6 0x744600
    virtual int vf_11(); // slot11 0x746E20
    virtual int vf_12(); // slot12 0x746DD0
    // Native primary slot 288: two stack dwords, target pointer and flag.
    virtual void SetDestination(AbstractClass* target, bool a2); // 288 0x741970
    // Native UnitClass slot 265 at 0x736CA0 overrides TechnoClass slot 265.
    virtual void vf_265();
    // Native UnitClass slot 313 at 0x736D50 overrides FootClass slot 313.
    virtual bool vf_313();
    // Native UnitClass slots 309/310 (0x746420/0x7464E0) override FootClass slots 309/310.
    virtual void vf_309(int a1);
    virtual void vf_310(FootClass* passenger);
    // FUNCTION: GAMEMD 0x00746D90 (decl; reloc)
    // UnitClass::FUN_00746D90
    int FUN_00746D90();
    // GAMEMD 0x70FBD0 (decl; body in movement/unit_class_methods.cpp)
    bool IsDeactivated() const;
    // GAMEMD 0x740DF0 (decl). Sets FlagHouseIndex @0x6CC when it is -1, then
    // calls primary slot 0x124/4 with 2 and returns true; only caller HouseClass::PickedUpFlag 0x4FC060.
    bool FlagAttach(int houseIndex);
    // GAMEMD 0x740E20 (decl)
    bool FlagRemove();
    // GAMEMD 0x740E80 (decl; body in movement/Unit.cpp)
    void APCOpenDoor();
    // GAMEMD 0x7441B0 (decl)
    void MarkAllOccupationBits(CoordStruct const& coords);
    // GAMEMD 0x744210 (decl)
    void UnmarkAllOccupationBits(CoordStruct const& coords);
    // GAMEMD 0x746000 (RET 8): whether a hop between two cells goes to the A* search.
    bool AStarAttempt(const CellStruct* from, const CellStruct* to);
    // Overrides recovered from retail (bodies in combat/unit_class_vslot_w3_methods.cpp).
    virtual bool IsUnderEMP();                          // 223 0x746C90
    virtual int vf_185(AbstractClass* target);          // 185 0x746CD0
    virtual bool vf_167();                              // 167 0x744180
    virtual double vf_173();                            // 173 0x7414A0
    virtual DirStruct vf_170();                         // 170 0x746E30
    virtual DirStruct vf_194();                         // 194 0x740F80
    virtual ObjectTypeClass* vf_51(bool a1);            // 51  0x7465B0
    virtual HouseClass* vf_52(bool a1);                 // 52  0x7465F0
    virtual void vf_284();                              // 284 0x746720
    virtual int vf_151();                               // 151 0x740B10
    virtual bool vf_53();                               // 53  0x7440B0
    virtual bool vf_80(int mode, CellStruct* cell, int a3, int a4); // 80  0x738910
    virtual bool vf_81(int a1, ObjectClass* a2, int a3);// 81  0x738890
    void FUN_00746630(ObjectTypeClass* type);           // 0x746630
    bool FUN_00746D10();                                // 0x746D10
    bool FUN_00746DB0();                                // 0x746DB0
    virtual void vf_10(void* target, bool removed);    // 10  0x7446E0
    virtual bool vf_245(HouseClass* house, bool a2);   // 245 0x7463A0
    virtual int vf_139();                              // 139 0x740A90
    int FUN_007438B0();                                // 0x7438B0
    void FUN_00740E60();                               // 0x740E60
    bool FUN_00736C10();                               // 0x736C10: crash-lands a unit that has left the map
    // Slots 341-343, introduced by UnitClass (344 slots in all; retail table 0x7F5C70).
    // Names are placeholders; argument counts come from RET n, return types are not recovered.
    // Each pops 0x20 or 0x24 bytes, so some of those words are by-value structures.
    virtual void vf_341(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);         // 341 0x73B470
    virtual void vf_342(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);         // 342 0x73C5F0
    virtual void vf_343(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9); // 343 0x73B140
    virtual int vf_136();                                // 136 0x744100
    virtual int vf_147();                                // 147 0x740EF0
    virtual void vf_56(void* source);                    // 56  0x744720
    virtual bool vf_65(RectangleStruct* rect, bool force, int a3); // 65 0x73B0B0

    int           CurrentFiringFrame;   // +0x6C0  ctor: MOV [ESI+0x6C0],EDI(-1) @0x007353E0
    void*         Type;                 // +0x6C4  UnitTypeClass*; ctor: MOV [ESI+0x6C4],ECX(=pType) @0x007353E6
    void*         FollowerCar;          // +0x6C8  UnitClass*;     ctor: MOV [ESI+0x6C8],EBX(0) @0x007353EC
    int           FlagHouseIndex;       // +0x6CC  ctor: MOV [ESI+0x6CC],EDI(-1) @0x007353F2
                                        //         also CMP [ECX+0x6CC],-1 @0x00740DF9 (FlagAttach)
    unsigned char IsFollowerCar;        // +0x6D0  ctor: MOV byte [ESI+0x6D0],BL @0x007353F8
    unsigned char Unloading;            // +0x6D1  ctor: MOV byte [ESI+0x6D1],BL @0x007353FE
    unsigned char IsHarvesting;         // +0x6D2  ctor: MOV byte [ESI+0x6D2],BL @0x00735404
    unsigned char TerrainPalette;       // +0x6D3  ctor: MOV byte [ESI+0x6D3],BL @0x0073540A
    int           unknown_int_6D4;      // +0x6D4  ctor: MOV [ESI+0x6D4],EDI(-1) @0x00735410
    int           DeathFrameCounter;    // +0x6D8  ctor: MOV [ESI+0x6D8],EDI(-1) @0x00735416
    class EBolt*   ElectricBolt;         // +0x6DC; ctor: MOV [ESI+0x6DC],EBX(0) @0x0073541C
    unsigned char Deployed;             // +0x6E0  ctor: MOV byte [ESI+0x6E0],BL @0x00735422
    unsigned char Deploying;            // +0x6E1  ctor: MOV byte [ESI+0x6E1],BL @0x00735428
    unsigned char Undeploying;          // +0x6E2  ctor: MOV byte [ESI+0x6E2],BL @0x0073542E
    unsigned char align_6E3;            // +0x6E3
    int           NonPassengerCount;    // +0x6E4  ctor: MOV [ESI+0x6E4],EBX(0) @0x00735434
    // ToolTipText is the only member below NOT proven by a member-access
    // instruction. It is proven by closure instead: the last confirmed field
    // ends at 0x6E8 and the allocation is 0x8E8, leaving exactly 0x200 bytes,
    // which is 0x100 wchar_t — the width YRpp claims. Treated as confirmed by
    // size closure, not as a named claim on YRpp's say-so.
    unsigned short ToolTipText[0x100];  // +0x6E8 .. 0x8E7 (wchar_t[256])
};

GG_STATIC_ASSERT(offsetof(UnitClass, CurrentFiringFrame) == 0x6C0);
GG_STATIC_ASSERT(offsetof(UnitClass, Type)               == 0x6C4);
GG_STATIC_ASSERT(offsetof(UnitClass, FollowerCar)        == 0x6C8);
GG_STATIC_ASSERT(offsetof(UnitClass, FlagHouseIndex)     == 0x6CC);
GG_STATIC_ASSERT(offsetof(UnitClass, IsFollowerCar)      == 0x6D0);
GG_STATIC_ASSERT(offsetof(UnitClass, Unloading)          == 0x6D1);
GG_STATIC_ASSERT(offsetof(UnitClass, IsHarvesting)       == 0x6D2);
GG_STATIC_ASSERT(offsetof(UnitClass, TerrainPalette)     == 0x6D3);
GG_STATIC_ASSERT(offsetof(UnitClass, unknown_int_6D4)    == 0x6D4);
GG_STATIC_ASSERT(offsetof(UnitClass, DeathFrameCounter)  == 0x6D8);
GG_STATIC_ASSERT(offsetof(UnitClass, ElectricBolt)       == 0x6DC);
GG_STATIC_ASSERT(offsetof(UnitClass, Deployed)           == 0x6E0);
GG_STATIC_ASSERT(offsetof(UnitClass, Deploying)          == 0x6E1);
GG_STATIC_ASSERT(offsetof(UnitClass, Undeploying)        == 0x6E2);
GG_STATIC_ASSERT(offsetof(UnitClass, NonPassengerCount)  == 0x6E4);
GG_STATIC_ASSERT(offsetof(UnitClass, ToolTipText)        == 0x6E8);
GG_STATIC_ASSERT(sizeof(UnitClass)                       == 0x8E8);

// VTABLE: GAMEMD 0x007F5C70  UnitClass            (COL @0x007F5C6C, base 0)
// VTABLE: GAMEMD 0x007F5C54  UnitClass::(+0x04)   (COL @0x007F5C50, base 4)
// VTABLE: GAMEMD 0x007F5C4C  UnitClass::(+0x08)   (COL @0x007F5C48, base 8)
// VTABLE: GAMEMD 0x007F5C44  UnitClass::(+0x0C)   (COL @0x007F5C40, base 12)

#endif  // GG_MATCH_LAYOUT_UNIT_CLASS_H
