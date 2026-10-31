// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor FUN_0x005113F0,
//   parent AbstractTypeClass ctor 0x00410800; member writes cross-checked vs
//   YRpp. Pad anchors align_B1@0xB1, align_C4@0xC4,
//   padding_1A9@0x1A9 confirmed; ctor writes ArrayIndex@0xB4, FirepowerMult@0xC8,
//   VeteranInfantry@0x14C. P2 layout-spine.
//
// Tables 0x7EAB58 (27 slots) / 0x7EAB3C (6) / 0x7EAB34 (1) / 0x7EAB2C (1); COLs 0x8030D8 / 0x803068 / 0x803050 /
// 0x803038; chain HouseTypeClass -> AbstractTypeClass -> AbstractClass -> IPersistStream -> IPersist -> IUnknown,
// IRTTITypeInfo -> IUnknown, INoticeSink, INoticeSource. The constructor 0x5113F0 (every member store), the INI
// reader 0x511850, the CRC slot 0x512170, Load 0x512290, Save 0x512480, the scalar deleting destructor 0x512760 and
// the allocation sites 0x4755A0, 0x5126D6 and 0x6C3D3C (`PUSH 0x1B0; CALL 0x7C8E17`) fix the members below.
//
// HouseTypeClass — the [Countries]/side "blueprint" type (ParentCountry,
// per-category combat/cost/speed multipliers, veteran-unit lists, multiplayer
// flags). Derives AbstractTypeClass (the AbstractClass COM spine + ID/Name
// strings) at offset 0 and adds the country fields from 0x98.
#ifndef GG_MATCH_LAYOUT_HOUSE_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_HOUSE_TYPE_CLASS_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "../core/type_list.h"

class InfantryTypeClass;
class UnitTypeClass;
class AircraftTypeClass;

// Fixed-size string member: a char array whose default constructor writes the terminator (retail's
// constructor 0x5113F0 stores the first byte at +0x98 before the other members) and whose assignment copies the array.
template <int N> struct FixedString
{
    char Data[N];

    FixedString() { Data[0] = 0; }
    FixedString(const AbstractNoInit&) {}
    FixedString(const char* text)
    {
        if (text == 0)
            Data[0] = 0;
        else {
            strncpy(Data, text, N - 1);
            Data[N - 1] = 0;
        }
    }
    FixedString& operator=(const FixedString& other)
    {
        if (this != &other)
            memcpy(Data, other.Data, N);
        return *this;
    }
    operator const char*() const { return Data; }
};

// HouseTypeClass  (0x98..0x1AF, sizeof = 0x1B0)
class HouseTypeClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x5113F0 -- the named constructor.
    HouseTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x511650 -- the no-init constructor.
    HouseTypeClass(const AbstractNoInit& noInit);

    // Overrides of AbstractTypeClass (IPersistStream side).
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);       // 0   0x5125A0
    virtual ULONG __stdcall AddRef();                                        // 1   0x512740
    virtual ULONG __stdcall Release();                                       // 2   0x512750
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                   // 3   0x512640
    virtual HRESULT __stdcall IsDirty();                                     // 4   0x512280
    virtual HRESULT __stdcall Load(IStream* pStm);                           // 5   0x512290
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);         // 6   0x512480
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);           // 7   0x512570
    // Slot 8: the scalar deleting destructor 0x512760 is compiler output; the body is expanded into it.
    virtual ~HouseTypeClass();
    virtual int vf_11();                                                     // 11  0x512710
    virtual int vf_12();                                                     // 12  0x512720
    virtual void vf_13(struct Obj_004A1D30* crc);                            // 13  0x512170
    virtual int vf_16();                                                     // 16  0x512730
    virtual bool vf_25(CCINIClass* ini);                                     // 25  0x511850

    // FUNCTION: GAMEMD 0x5117D0 (decl; reloc) -- name to index, -1 when absent; ECX carries the name.
    static int FindIndexOfName(const char* name);
    FixedString<0x19> ParentCountry;       // +0x98
    unsigned char align_B1[3];             // +0xB1
    int           ArrayIndex;              // +0xB4
    int           ArrayIndex2;             // +0xB8
    int           SideIndex;               // +0xBC
    int           ColorSchemeIndex;        // +0xC0
    unsigned long align_C4;                // +0xC4  (DWORD)

    double        FirepowerMult;           // +0xC8
    double        GroundspeedMult;         // +0xD0
    double        AirspeedMult;            // +0xD8
    double        ArmorMult;               // +0xE0
    double        ROFMult;                 // +0xE8
    double        CostMult;                // +0xF0
    double        BuildtimeMult;           // +0xF8

    float         ArmorInfantryMult;       // +0x100
    float         ArmorUnitsMult;          // +0x104
    float         ArmorAircraftMult;       // +0x108
    float         ArmorBuildingsMult;      // +0x10C
    float         ArmorDefensesMult;       // +0x110
    float         CostInfantryMult;        // +0x114
    float         CostUnitsMult;           // +0x118
    float         CostAircraftMult;        // +0x11C
    float         CostBuildingsMult;       // +0x120
    float         CostDefensesMult;        // +0x124
    float         SpeedInfantryMult;       // +0x128
    float         SpeedUnitsMult;          // +0x12C
    float         SpeedAircraftMult;       // +0x130
    float         BuildtimeInfantryMult;   // +0x134
    float         BuildtimeUnitsMult;      // +0x138
    float         BuildtimeAircraftMult;   // +0x13C
    float         BuildtimeBuildingsMult;  // +0x140
    float         BuildtimeDefensesMult;   // +0x144
    float         IncomeMult;              // +0x148

    TypeList<const InfantryTypeClass*> VeteranInfantry;   // +0x14C
    TypeList<const UnitTypeClass*>     VeteranUnits;      // +0x168
    TypeList<const AircraftTypeClass*> VeteranAircraft;   // +0x184

    char          Suffix[4];               // +0x1A0
    char          Prefix;                  // +0x1A4
    bool          Multiplay;               // +0x1A5
    bool          MultiplayPassive;        // +0x1A6
    bool          WallOwner;               // +0x1A7
    bool          SmartAI;                 // +0x1A8
    unsigned char padding_1A9[7];          // +0x1A9  (pad to sizeof 0x1B0)
};

GG_STATIC_ASSERT(offsetof(HouseTypeClass, WallOwner) == 0x1A7);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, MultiplayPassive) == 0x1A6); // 0x6886B0 accesses
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ParentCountry)     == 0x98);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex)        == 0xB4);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ColorSchemeIndex)  == 0xC0);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, FirepowerMult)     == 0xC8);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeMult)     == 0xF8);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArmorInfantryMult) == 0x100);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, CostInfantryMult)  == 0x114);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, CostUnitsMult)     == 0x118);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, CostAircraftMult)  == 0x11C);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, CostBuildingsMult) == 0x120);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, CostDefensesMult)  == 0x124);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, IncomeMult)        == 0x148);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, VeteranInfantry)   == 0x14C);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, VeteranAircraft)   == 0x184);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, Suffix)            == 0x1A0);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, Multiplay)         == 0x1A5);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, padding_1A9)       == 0x1A9);
GG_STATIC_ASSERT(sizeof(HouseTypeClass)                      == 0x1B0);

#endif  // GG_MATCH_LAYOUT_HOUSE_TYPE_CLASS_H
