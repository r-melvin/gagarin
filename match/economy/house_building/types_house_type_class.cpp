// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// HouseTypeClass entries (layout and evidence: types_house_type_class.h).

#include "types_house_type_class.h"

// GLOBAL: GAMEMD 0x8B4120 - SideClass::Array (read-only here).
extern DynamicVectorClass<TypesSideView*> TypesSideArray;

// GLOBAL: GAMEMD 0x7E9630 - CLSID of HouseTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_HouseType =
    { 0x1DD43928, 0x046B, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// Restores one veteran list from the stream: rebuilds the list in place, reads the count, then each
// element, appending it.
template <class T> inline void TypesLoadListImpl(IStream* stream, TypesTypeList<T>* list)
{
    new (list) TypesTypeList<T>;
    int count;
    stream->Read(&count, 4, 0);
    for (int i = 0; i < count; ++i) {
        T item;
        stream->Read(&item, 4, 0);
        list->AddItem(item);
    }
}

template <class T> inline void TypesLoadList(IStream* stream, TypesTypeList<T>* list)
{
    TypesLoadListImpl(stream, list);
}

template <class T> inline void TypesSwizzleList(TypesTypeList<T>* list)
{
    for (int i = 0; i < list->Count; ++i)
        TypesSwizzle.Swizzle((void**)&list->Items[i]);
}

// Reads one veteran list: the names after the key, split at commas, resolved through the finder and
// collected in order; without the key the existing list is returned unchanged. Retail expands this
// inline once per list (the returned list is a copy, assigned to the member by the caller).
#define TYPES_DEFINE_READ_LIST(TYPE, FIND, NAME)                                                       \
    inline TypesTypeList<TYPE*> NAME##Impl(TypesIniView* ini, const char* section, const char* key,   \
                                           const TypesTypeList<TYPE*>& current)                        \
    {                                                                                                  \
        char buffer[0x80];                                                                             \
        if (ini->ReadString(section, key, TypesEmptyText, buffer, 0x80)) {                             \
            TypesTypeList<TYPE*> list;                                                                 \
            for (char* name = strtok(buffer, ","); name; name = strtok(0, ",")) {                      \
                if (*name) {                                                                           \
                    TYPE* type = FIND(name);                                                           \
                    if (type)                                                                          \
                        list.AddItem(type);                                                            \
                }                                                                                      \
            }                                                                                          \
            return list;                                                                               \
        }                                                                                              \
        return current;                                                                                \
    }                                                                                                  \
    inline void NAME(TypesIniView* ini, const char* section, const char* key,                           \
                     TypesTypeList<TYPE*>& member)                                                      \
    {                                                                                                  \
        member = NAME##Impl(ini, section, key, member);                                                \
    }

TYPES_DEFINE_READ_LIST(InfantryTypeClass, TypesFindInfantryType, TypesReadInfantryList)
TYPES_DEFINE_READ_LIST(UnitTypeClass, TypesFindUnitType, TypesReadUnitList)
TYPES_DEFINE_READ_LIST(AircraftTypeClass, TypesFindAircraftType, TypesReadAircraftList)

// FUNCTION: GAMEMD 0x5113F0
HouseTypeClass::HouseTypeClass(const char* id)
    : HouseTypeAbstractView(id), ArrayIndex(-1), ArrayIndex2(-1), SideIndex(-1), ColorSchemeIndex(0),
      FirepowerMult(1.0), GroundspeedMult(1.0), AirspeedMult(1.0), ArmorMult(1.0), ROFMult(1.0),
      CostMult(1.0), BuildtimeMult(1.0), ArmorInfantryMult(1.0f), ArmorUnitsMult(1.0f),
      ArmorAircraftMult(1.0f), ArmorBuildingsMult(1.0f), ArmorDefensesMult(1.0f),
      CostInfantryMult(1.0f), CostUnitsMult(1.0f), CostAircraftMult(1.0f), CostBuildingsMult(1.0f),
      CostDefensesMult(1.0f), SpeedInfantryMult(1.0f), SpeedUnitsMult(1.0f), SpeedAircraftMult(1.0f),
      BuildtimeInfantryMult(1.0f), BuildtimeUnitsMult(1.0f), BuildtimeAircraftMult(1.0f),
      BuildtimeBuildingsMult(1.0f), BuildtimeDefensesMult(1.0f), IncomeMult(1.0f),
      Prefix('A'), Multiplay(false), MultiplayPassive(false), WallOwner(true), SmartAI(false)
{
    HBRttiBase::Create_ID();
    Suffix[0] = 0;
    TypesAddItemEarlyOut(TypesHouseTypeArray, this);
    ArrayIndex2 = TypesFindIndex(TypesHouseTypeArray, this);
    ArrayIndex = TypesFindIndexHoisted(TypesHouseTypeArray, this);
}

// CAPPED at 81.3% aligned-instruction match (556 of 684 retail instructions; 649 compiled) after six forms.
// Observed delta: the stack frame is 8 bytes smaller than retail's (sub esp,0xDC against 0xE4), so every local
// sits 4 to 8 bytes lower; the units and aircraft list blocks differ in which AddItem / VectorClass
// operator= expansions stay out of line (retail expands AddItem inline for units and aircraft and calls it for
// infantry); and the side-removal shift loop reads the vector fields in a different order. The prefix, doubles,
// floats and string reads (about 340 instructions) are aligned. Forms tried: everything inline in the body;
// a list helper returning the list by value; the same helper behind an extra wrapper; the wrapper doing the
// member assignment too (kept); one shared 0x20-byte name buffer against separate buffers; the positive-test
// shape `if (base) { ... return true; } return false;` (kept).
// FUNCTION: GAMEMD 0x511850
bool HouseTypeClass::ReadINI(TypesIniView* ini)
{
    ini->ClearCache();
    if (HouseTypeAbstractView::ReadINI(ini)) {
        char buffer[0x20];
        ini->ReadString(ID, "Suffix", TypesEmptyText, buffer, 4);
        if (strlen(buffer))
            strcpy(Suffix, buffer);

        ini->ReadString(ID, "ParentCountry", ID, buffer, 0x19);
        ParentCountry = TypesFixedString<0x19>(buffer);

        ColorSchemeIndex = ini->ReadColorScheme(ID, "Color", ColorSchemeIndex);

        buffer[0] = Prefix;
        buffer[1] = 0;
        char prefix[2];
        ini->ReadString(ID, "Prefix", buffer, prefix, 2);
        Prefix = prefix[0];

        FirepowerMult = ini->ReadDouble(ID, "Firepower", FirepowerMult);
        GroundspeedMult = ini->ReadDouble(ID, "Groundspeed", GroundspeedMult);
        AirspeedMult = ini->ReadDouble(ID, "Airspeed", AirspeedMult);
        ArmorMult = ini->ReadDouble(ID, "Armor", ArmorMult);
        ROFMult = ini->ReadDouble(ID, "ROF", ROFMult);
        CostMult = ini->ReadDouble(ID, "Cost", CostMult);
        BuildtimeMult = ini->ReadDouble(ID, "BuildTime", BuildtimeMult);
        Multiplay = ini->ReadBool(ID, "Multiplay", Multiplay);
        MultiplayPassive = ini->ReadBool(ID, "MultiplayPassive", MultiplayPassive);
        WallOwner = ini->ReadBool(ID, "WallOwner", WallOwner);
        SmartAI = ini->ReadBool(ID, "SmartAI", SmartAI);
        ArmorInfantryMult = (float)ini->ReadDouble(ID, "ArmorInfantryMult", ArmorInfantryMult);
        ArmorUnitsMult = (float)ini->ReadDouble(ID, "ArmorUnitsMult", ArmorUnitsMult);
        ArmorAircraftMult = (float)ini->ReadDouble(ID, "ArmorAircraftMult", ArmorAircraftMult);
        ArmorBuildingsMult = (float)ini->ReadDouble(ID, "ArmorBuildingsMult", ArmorBuildingsMult);
        ArmorDefensesMult = (float)ini->ReadDouble(ID, "ArmorDefensesMult", ArmorDefensesMult);
        CostInfantryMult = (float)ini->ReadDouble(ID, "CostInfantryMult", CostInfantryMult);
        CostUnitsMult = (float)ini->ReadDouble(ID, "CostUnitsMult", CostUnitsMult);
        CostAircraftMult = (float)ini->ReadDouble(ID, "CostAircraftMult", CostAircraftMult);
        CostBuildingsMult = (float)ini->ReadDouble(ID, "CostBuildingsMult", CostBuildingsMult);
        CostDefensesMult = (float)ini->ReadDouble(ID, "CostDefensesMult", CostDefensesMult);
        SpeedInfantryMult = (float)ini->ReadDouble(ID, "SpeedInfantryMult", SpeedInfantryMult);
        SpeedUnitsMult = (float)ini->ReadDouble(ID, "SpeedUnitsMult", SpeedUnitsMult);
        SpeedAircraftMult = (float)ini->ReadDouble(ID, "SpeedAircraftMult", SpeedAircraftMult);
        BuildtimeInfantryMult = (float)ini->ReadDouble(ID, "BuildTimeInfantryMult", BuildtimeInfantryMult);
        BuildtimeUnitsMult = (float)ini->ReadDouble(ID, "BuildTimeUnitsMult", BuildtimeUnitsMult);
        BuildtimeAircraftMult = (float)ini->ReadDouble(ID, "BuildTimeAircraftMult", BuildtimeAircraftMult);
        BuildtimeBuildingsMult = (float)ini->ReadDouble(ID, "BuildTimeBuildingsMult", BuildtimeBuildingsMult);
        BuildtimeDefensesMult = (float)ini->ReadDouble(ID, "BuildTimeDefensesMult", BuildtimeDefensesMult);
        IncomeMult = (float)ini->ReadDouble(ID, "IncomeMult", IncomeMult);

        TypesReadInfantryList(ini, ID, "VeteranInfantry", VeteranInfantry);
        TypesReadUnitList(ini, ID, "VeteranUnits", VeteranUnits);
        TypesReadAircraftList(ini, ID, "VeteranAircraft", VeteranAircraft);

        int oldSide = SideIndex;
        SideIndex = ini->ReadSide(ID, "Side", oldSide);
        if (SideIndex != oldSide) {
            if (oldSide != -1) {
                DynamicVectorClass<int>& houseTypes = TypesSideArray.Items[oldSide]->HouseTypes;
                if (ArrayIndex2 < houseTypes.Count) {
                    houseTypes.Count = houseTypes.Count - 1;
                    for (int i = ArrayIndex2; i < houseTypes.Count; ++i)
                        houseTypes.Items[i] = houseTypes.Items[i + 1];
                }
            }
            if (SideIndex != -1)
                TypesAddItemEarlyOut(TypesSideArray.Items[SideIndex]->HouseTypes, ArrayIndex2);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x512170
void HouseTypeClass::ComputeCRC(TypesCrcView& crc)
{
    HouseTypeAbstractView::ComputeCRC(crc);
    crc.AddInt(ArrayIndex2);
    crc.AddInt(SideIndex);
    crc.AddInt(ColorSchemeIndex);
    crc.AddDouble(FirepowerMult);
    crc.AddDouble(GroundspeedMult);
    crc.AddDouble(AirspeedMult);
    crc.AddDouble(ArmorMult);
    crc.AddDouble(ROFMult);
    crc.AddDouble(CostMult);
    crc.AddDouble(BuildtimeMult);
    crc.AddBytes(Suffix, strlen(Suffix));
    crc.AddByte(Prefix);
    crc.AddBool(Multiplay);
}

// FUNCTION: GAMEMD 0x512280
HRESULT __stdcall HouseTypeClass::IsDirty()
{
    return S_OK;
}

// CAPPED at 79.7% aligned-instruction match (137 of 172 retail instructions; 185 compiled) after four forms.
// Observed delta: retail keeps `this` in EDI, the infantry and unit list addresses in EBX/EBP and the loop
// counter in EBX, with the loop bound reread from the stack; this build keeps `this` in EBX and the counter in
// EDI. Retail constructs the aircraft list through an out-of-line default constructor and calls AddItem out of
// line for all three lists; this build constructs the infantry/unit lists with the Dyn(0,0) call plus vptr store
// as retail does but expands the aircraft constructor inline. Forms tried: (1) everything inline in the body
// (3.2%); (2) a per-list inline helper (31%); (3) the helper nested one level deeper (69.8%); (4) the nested
// helper plus a swizzle helper (79.7%, kept).
// FUNCTION: GAMEMD 0x512290
HRESULT __stdcall HouseTypeClass::Load(IStream* pStm)
{
    VeteranInfantry.Clear();
    VeteranUnits.Clear();
    VeteranAircraft.Clear();

    HRESULT hr = HouseTypeAbstractView::Load(pStm);
    if (hr < 0)
        return hr;

    new (this) HouseTypeClass(HBNoInit());

    TypesLoadList(pStm, &VeteranInfantry);
    TypesLoadList(pStm, &VeteranUnits);
    TypesLoadList(pStm, &VeteranAircraft);

    TypesSwizzleList(&VeteranInfantry);
    TypesSwizzleList(&VeteranUnits);
    TypesSwizzleList(&VeteranAircraft);
    return S_OK;
}

// FUNCTION: GAMEMD 0x512480
HRESULT __stdcall HouseTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = HouseTypeAbstractView::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = VeteranInfantry.Count;
        int i;
        pStm->Write(&count, 4, 0);
        for (i = 0; i < count; ++i)
            pStm->Write(&VeteranInfantry.Items[i], 4, 0);

        count = VeteranUnits.Count;
        pStm->Write(&count, 4, 0);
        for (i = 0; i < count; ++i)
            pStm->Write(&VeteranUnits.Items[i], 4, 0);

        count = VeteranAircraft.Count;
        pStm->Write(&count, 4, 0);
        for (i = 0; i < count; ++i)
            pStm->Write(&VeteranAircraft.Items[i], 4, 0);

        hr = S_OK;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x512570
HRESULT __stdcall HouseTypeClass::GetSizeMax(ULARGE_INTEGER* pcbSize)
{
    if (pcbSize == 0)
        return E_POINTER;
    pcbSize->HighPart = 0;
    pcbSize->LowPart = 0x1B4;
    return S_OK;
}

// FUNCTION: GAMEMD 0x5125A0
HRESULT __stdcall HouseTypeClass::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == 0)
        return E_POINTER;

    *ppv = 0;

    if (riid == IID_IUnknown)
        *ppv = static_cast<IPersistStream*>(this);
    if (riid == IID_IPersist)
        *ppv = static_cast<IPersistStream*>(this);
    if (riid == IID_IPersistStream)
        *ppv = static_cast<IPersistStream*>(this);
    if (riid == IID_IRTTITypeInfo)
        *ppv = static_cast<HBRttiBase*>(this);

    if (*ppv == 0)
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

// FUNCTION: GAMEMD 0x512640
HRESULT __stdcall HouseTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_HouseType;
    return S_OK;
}

// FUNCTION: GAMEMD 0x512710
int HouseTypeClass::WhatAmI()
{
    return 0xE;
}

// FUNCTION: GAMEMD 0x512720
int HouseTypeClass::Size()
{
    return 0x1B0;
}

// FUNCTION: GAMEMD 0x512730
int HouseTypeClass::GetArrayIndex()
{
    return ArrayIndex;
}

// FUNCTION: GAMEMD 0x512740
ULONG __stdcall HouseTypeClass::AddRef()
{
    return 1;
}

// FUNCTION: GAMEMD 0x512750
ULONG __stdcall HouseTypeClass::Release()
{
    return 1;
}

// SYNTHETIC: GAMEMD 0x512760 -- compiler-generated scalar deleting destructor.

// SYNTHETIC: GAMEMD 0x5139E0
// HouseTypeClass::QueryInterface`adjustor{4}' - IRTTITypeInfo table slot 0 (SUB [ESP+4],4; JMP 0x5125A0).

// SYNTHETIC: GAMEMD 0x5139F0
// HouseTypeClass::AddRef`adjustor{4}' - IRTTITypeInfo table slot 1 (-> 0x512740).

// SYNTHETIC: GAMEMD 0x513A00
// HouseTypeClass::Release`adjustor{4}' - IRTTITypeInfo table slot 2 (-> 0x512750).
