// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVHouseTypeClass@@ (TD 0x825268): COLs 0x8030D8 / 0x803068 / 0x803050 / 0x803038 for the
//   tables 0x7EAB58 (27 slots) / 0x7EAB3C (6) / 0x7EAB34 (1) / 0x7EAB2C (1); chain HouseTypeClass ->
//   AbstractTypeClass -> AbstractClass -> IPersistStream -> IPersist -> IUnknown, IRTTITypeInfo ->
//   IUnknown, INoticeSink, INoticeSource. The constructor 0x5113F0 (every member store below), the
//   INI reader 0x511850 (every key string and member offset), the CRC slot 0x512170, Load 0x512290,
//   Save 0x512480, the scalar deleting destructor 0x512760 and the allocation sites 0x4755A0,
//   0x5126D6 and 0x6C3D3C (`PUSH 0x1B0; CALL 0x7C8E17`, three sites, all agreeing).
//
// HouseTypeClass: the [Countries] blueprint of a house (rules INI [Countries] sections).
//   +0x00..+0x97  HouseTypeAbstractView (the AbstractClass / AbstractTypeClass part; READ-ONLY)
//   +0x98 ParentCountry  +0xB4 ArrayIndex  +0xB8 ArrayIndex2  +0xBC SideIndex  +0xC0 ColorSchemeIndex
//   +0xC8..+0xF8 seven double multipliers  +0x100..+0x148 nineteen float multipliers
//   +0x14C / +0x168 / +0x184 the three veteran lists  +0x1A0 Suffix  +0x1A4 Prefix  +0x1A5..+0x1A8
//   four flags.  sizeof 0x1B0 (from the allocation)
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_HOUSE_TYPE_CLASS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_HOUSE_TYPE_CLASS_H

#include "types_shared.h"

class InfantryTypeClass;
class UnitTypeClass;
class AircraftTypeClass;
class HouseTypeClass;

// ABI view of AbstractTypeClass (sizeof 0x98), the base of HouseTypeClass. Slot numbers are the retail
// primary-table indices (table 0x7EAB58, 27 slots). The IPersistStream slots 0-7 are __stdcall with
// `this` on the stack; every other slot is __thiscall. Inherited slots are READ-ONLY here.
// VTABLE: GAMEMD 0x7EAB58 (IPersistStream side), GAMEMD 0x7EAB3C (IRTTITypeInfo side), GAMEMD 0x7EAB34
//         (INoticeSink side), GAMEMD 0x7EAB2C (INoticeSource side)
class HouseTypeAbstractView : public IPersistStream, public HBRttiBase,
                              public HBNoticeSinkBase, public HBNoticeSourceBase
{
public:
    // FUNCTION: GAMEMD 0x410800 (AbstractTypeClass named constructor; read-only here)
    HouseTypeAbstractView(const char* id);
    // FUNCTION: GAMEMD 0x410960 (AbstractTypeClass no-init constructor; read-only here)
    HouseTypeAbstractView(const HBNoInit& noInit);

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);       // 0   overridden (0x5125A0)
    virtual ULONG __stdcall AddRef();                                        // 1   overridden (0x512740)
    virtual ULONG __stdcall Release();                                       // 2   overridden (0x512750)
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                   // 3   overridden (0x512640)
    virtual HRESULT __stdcall IsDirty();                                     // 4   overridden (0x512280)
    virtual HRESULT __stdcall Load(IStream* pStm);                           // 5   base 0x410380; overridden (0x512290)
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);         // 6   base 0x410320; overridden (0x512480)
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);           // 7   overridden (0x512570)
    virtual ~HouseTypeAbstractView();                                        // 8   base 0x4109C0; overridden (0x512760)
    virtual void vf_9();                                                     // 9   0x410470
    virtual void vf_10();                                                    // 10  0x410480
    virtual int WhatAmI();                                                   // 11  overridden (0x512710)
    virtual int Size();                                                      // 12  overridden (0x512720)
    virtual void ComputeCRC(TypesCrcView& crc);                              // 13  base 0x410BE0; overridden (0x512170)
    virtual void vf_14();                                                    // 14  0x410490
    virtual void vf_15();                                                    // 15  0x4104A0
    virtual int GetArrayIndex();                                             // 16  overridden (0x512730)
    virtual void vf_17();                                                    // 17  0x410440
    virtual void vf_18();                                                    // 18  0x4104C0
    virtual void vf_19();                                                    // 19  0x4104F0
    virtual void vf_20();                                                    // 20  0x410520
    virtual void vf_21();                                                    // 21  0x410530
    virtual void vf_22();                                                    // 22  0x410540
    virtual void vf_23();                                                    // 23  0x410570
    virtual void vf_24();                                                    // 24  0x410C20
    virtual bool ReadINI(TypesIniView* ini);                                 // 25  base 0x410A60; overridden (0x511850)
    virtual void vf_26();                                                    // 26  0x410B90

    char unknown_10[0x14];    // +0x10..+0x23  AbstractClass members
    char ID[0x18];            // +0x24         AbstractTypeClass::ID, the INI section name
    char unknown_3C[0x98 - 0x3C];   // +0x3C..+0x97
};
GG_STATIC_ASSERT(offsetof(HouseTypeAbstractView, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(HouseTypeAbstractView, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(HouseTypeAbstractView) == 0x98);

// Side objects (read-only view): the only member the house type touches is the list of house type
// indices at +0x98 (a DynamicVectorClass<int>).
struct TypesSideView
{
    char unknown_00[0x98];
    DynamicVectorClass<int> HouseTypes;   // +0x98
};
GG_STATIC_ASSERT(offsetof(TypesSideView, HouseTypes) == 0x98);

// GLOBAL: GAMEMD 0xA83C98 - HouseTypeClass::Array, every house type (DynamicVectorClass; read-only here).
extern DynamicVectorClass<HouseTypeClass*> TypesHouseTypeArray;

// VTABLE: GAMEMD 0x7EAB58 (IPersistStream side) and GAMEMD 0x7EAB3C / 0x7EAB34 / 0x7EAB2C
class HouseTypeClass : public HouseTypeAbstractView
{
public:
    // FUNCTION: GAMEMD 0x5113F0 - the named constructor.
    HouseTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x511650 (no-init constructor; not part of this cluster - bound)
    HouseTypeClass(const HBNoInit& noInit);

    // ---- overrides (IPersistStream side) -----------------------------------------------------
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);       // 0   0x5125A0
    virtual ULONG __stdcall AddRef();                                        // 1   0x512740
    virtual ULONG __stdcall Release();                                       // 2   0x512750
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                   // 3   0x512640
    virtual HRESULT __stdcall IsDirty();                                     // 4   0x512280
    virtual HRESULT __stdcall Load(IStream* pStm);                           // 5   0x512290
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);         // 6   0x512480
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);           // 7   0x512570
    // Slot 8: the scalar deleting destructor 0x512760 is compiler output; the destructor body is inline
    // (expanded into that entry) and the base body 0x4109C0 is out of line.
    // FUNCTION: GAMEMD 0x512760 (scalar deleting destructor; ??_G)
    virtual ~HouseTypeClass()
    {
        TypesAnnouncePointerExpired(this, true);
        TypesHouseTypeArray.RemoveItem(this);
    }
    virtual int WhatAmI();                                                   // 11  0x512710
    virtual int Size();                                                      // 12  0x512720
    virtual void ComputeCRC(TypesCrcView& crc);                              // 13  0x512170
    virtual int GetArrayIndex();                                             // 16  0x512730
    virtual bool ReadINI(TypesIniView* ini);                                 // 25  0x511850

    // ---- members (complete-object offsets) ---------------------------------------------------
    TypesFixedString<0x19> ParentCountry;   // +0x98
    unsigned char unknown_B1[3];            // +0xB1
    int           ArrayIndex;               // +0xB4
    int           ArrayIndex2;              // +0xB8
    int           SideIndex;                // +0xBC
    int           ColorSchemeIndex;         // +0xC0
    unsigned char unknown_C4[4];            // +0xC4
    double        FirepowerMult;            // +0xC8
    double        GroundspeedMult;          // +0xD0
    double        AirspeedMult;             // +0xD8
    double        ArmorMult;                // +0xE0
    double        ROFMult;                  // +0xE8
    double        CostMult;                 // +0xF0
    double        BuildtimeMult;            // +0xF8
    float         ArmorInfantryMult;        // +0x100
    float         ArmorUnitsMult;           // +0x104
    float         ArmorAircraftMult;        // +0x108
    float         ArmorBuildingsMult;       // +0x10C
    float         ArmorDefensesMult;        // +0x110
    float         CostInfantryMult;         // +0x114
    float         CostUnitsMult;            // +0x118
    float         CostAircraftMult;         // +0x11C
    float         CostBuildingsMult;        // +0x120
    float         CostDefensesMult;         // +0x124
    float         SpeedInfantryMult;        // +0x128
    float         SpeedUnitsMult;           // +0x12C
    float         SpeedAircraftMult;        // +0x130
    float         BuildtimeInfantryMult;    // +0x134
    float         BuildtimeUnitsMult;       // +0x138
    float         BuildtimeAircraftMult;    // +0x13C
    float         BuildtimeBuildingsMult;   // +0x140
    float         BuildtimeDefensesMult;    // +0x144
    float         IncomeMult;               // +0x148
    TypesTypeList<InfantryTypeClass*> VeteranInfantry;   // +0x14C
    TypesTypeList<UnitTypeClass*>     VeteranUnits;      // +0x168
    TypesTypeList<AircraftTypeClass*> VeteranAircraft;   // +0x184
    char          Suffix[4];                // +0x1A0
    char          Prefix;                   // +0x1A4
    bool          Multiplay;                // +0x1A5
    bool          MultiplayPassive;         // +0x1A6
    bool          WallOwner;                // +0x1A7
    bool          SmartAI;                  // +0x1A8
    unsigned char unknown_1A9[7];           // +0x1A9
};

GG_STATIC_ASSERT(offsetof(HouseTypeClass, ParentCountry) == 0x98);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex) == 0xB4);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex2) == 0xB8);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, SideIndex) == 0xBC);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ColorSchemeIndex) == 0xC0);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, FirepowerMult) == 0xC8);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeMult) == 0xF8);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArmorInfantryMult) == 0x100);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, IncomeMult) == 0x148);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, VeteranInfantry) == 0x14C);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, VeteranUnits) == 0x168);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, VeteranAircraft) == 0x184);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, Suffix) == 0x1A0);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, Prefix) == 0x1A4);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, Multiplay) == 0x1A5);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, SmartAI) == 0x1A8);
// sizeof is from the allocation: `PUSH 0x1B0; CALL 0x7C8E17` at 0x4755A0, 0x5126D6, 0x6C3D3C.
GG_STATIC_ASSERT(sizeof(HouseTypeClass) == 0x1B0);

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_HOUSE_TYPE_CLASS_H
