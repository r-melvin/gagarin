// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Small shared views for the BuildingTypeClass / HouseTypeClass module (cluster "types"), each
//   declared once. Everything was read from the retail gamemd.exe v1.001:
//     the IRTTITypeInfo / INoticeSink / INoticeSource secondary tables (the bodies 0x410210 /
//     0x410220 / 0x410230, 0x410580 and 0x410590 shared by every type class), the CRC accumulator
//     entries 0x4A1C10 / 0x4A1CA0 / 0x4A1D50 / 0x4A1D90 / 0x4A1DE0, the INI reader entries
//     0x526B00 / 0x5276D0 / 0x5283D0 / 0x528A10 / 0x5295F0 / 0x4754B0 / 0x474A90 / 0x4756F0 /
//     0x474B50, and the swizzle manager entry 0x6CF240.
//
// None of these views claims to be the canonical class: every body here is READ-ONLY and bound by
// address. `Types`-prefixed names are scoped to this module until they are consolidated with the tree's canonical bases.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_SHARED_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_SHARED_H

#include <stddef.h>
#include <new.h>
#include <string.h>
#include <objidl.h>   // IStream, IPersistStream, CLSID, IID, HRESULT (VC98 SDK, LIBRARY)
#include "../../_rt/gg_static_assert.h"
#include "house_building_views.h"
#include "house_building_com_bases.h"
#include "house_building_views.h"
#include "house_building_com_bases.h"
#include "house_building_views.h"
#include "house_building_com_bases.h"
#include "../../core/vector_class.h"
#include "../../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0x7E9AE0 - IID of the IRTTITypeInfo interface (the +4 base of every type class); the
// QueryInterface bodies compare against it. Declared, never defined here.
extern "C" const IID IID_IRTTITypeInfo;

// The CRC accumulator the CRC slots feed (read-only here).
class TypesCrcView
{
public:
    // FUNCTION: GAMEMD 0x4A1C10 (read-only here)
    void AddByte(unsigned char value);
    // FUNCTION: GAMEMD 0x4A1CA0 (read-only here)
    void AddBool(bool value);
    // FUNCTION: GAMEMD 0x4A1D50 (read-only here)
    void AddInt(int value);
    // FUNCTION: GAMEMD 0x4A1D90 (read-only here)
    void AddDouble(double value);
    // FUNCTION: GAMEMD 0x4A1DB0 (read-only here) - a NUL-terminated string.
    void AddString(const char* text);
    // FUNCTION: GAMEMD 0x4A1DE0 (read-only here) - a byte run (pointer, length).
    void AddBytes(const void* data, int length);
};

// The rules / art INI reader (read-only here). Every Read* is __thiscall with the section name and
// the key first and the default value last.
class TypesIniView
{
public:
    // FUNCTION: GAMEMD 0x526B00 (read-only here) - clears the reader's two cached positions
    void ClearCache();
    // FUNCTION: GAMEMD 0x5276D0 (read-only here)
    int ReadInt(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x5283D0 (read-only here) - the double comes back in ST(0)
    double ReadDouble(const char* section, const char* key, double defaultValue);
    // FUNCTION: GAMEMD 0x5295F0 (read-only here)
    bool ReadBool(const char* section, const char* key, bool defaultValue);
    // FUNCTION: GAMEMD 0x474A90 (read-only here) - a colour scheme name read.
    int ReadColorScheme(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4756F0 (read-only here) - a side name read.
    int ReadSide(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475060 (read-only here) - a build category name read.
    int ReadBuildCat(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474FA0 (read-only here) - an EVA event name read.
    int ReadEvaEvent(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474FF0 (read-only here) - a factory type name read.
    int ReadFactory(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474F50 (read-only here) - a super weapon name read.
    int ReadSuperWeapon(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474DA0 (read-only here) - a foundation name read.
    int ReadFoundation(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x529CA0 (read-only here) - a coordinate triple; the result comes back through a
    // hidden pointer and the default is passed by reference.
    HBCoord ReadCoord(const char* section, const char* key, const HBCoord& defaultValue);
    // FUNCTION: GAMEMD 0x529880 (read-only here) - a point pair, same convention.
    struct TypesPoint2D ReadPoint(const char* section, const char* key, const struct TypesPoint2D& defaultValue);
    // FUNCTION: GAMEMD 0x528A10 (read-only here) - the length read, 0 when the key is absent.
    int ReadString(const char* section, const char* key, const char* defaultValue, char* buffer, int size);
};

extern HBSwizzleView TypesSwizzle;

// FUNCTION: GAMEMD 0x7258D0 (read-only here) - announces that a pointer is going away. __fastcall: the
// object in ECX, the flag in DL. Every destructor calls it with 1 (the object is gone).
void __fastcall TypesAnnouncePointerExpired(void* object, bool removed);

// TypeList<T> (match/_layout/techno_type_class.h: DynamicVectorClass plus one trailing dword, 0x1C).
// The retail ctor expansion is `VectorClass(0, 0)` out of line, then the CapacityIncrement / Count
// stores and its own vtable.
template <class T> class TypesTypeList : public DynamicVectorClass<T>
{
public:
    TypesTypeList() : DynamicVectorClass<T>(0, 0) {}

    // DynamicVectorClass::AddItem (out of line in retail: 0x512F20 / 0x5132F0 / 0x5136C0).
    bool AddItem(const T& item);

    int unknown_18;   // +0x18
};

template <class T> bool TypesTypeList<T>::AddItem(const T& item)
{
    if (this->Count >= this->Capacity) {
        if (!this->IsAllocated && this->Capacity != 0)
            return false;
        if (this->CapacityIncrement <= 0)
            return false;
        if (!this->SetCapacity(this->CapacityIncrement + this->Capacity, 0))
            return false;
    }
    this->Items[this->Count++] = item;
    return true;
}

// Placement construction of a member list through a helper (adds an inline level).
template <class L> inline void TypesConstructInPlace(L* list)
{
    new (list) L;
}

// Fixed-size string: a fixed char array with a bounded assignment from a C string.
template <int N> struct TypesFixedString
{
    char Data[N];

    TypesFixedString() { Data[0] = 0; }
    TypesFixedString& operator=(const TypesFixedString& other)
    {
        if (this != &other)
            memcpy(Data, other.Data, N);
        return *this;
    }

    TypesFixedString(const char* text)
    {
        if (text == 0)
            Data[0] = 0;
        else {
            strncpy(Data, text, N - 1);
            Data[N - 1] = 0;
        }
    }
};

// DynamicVectorClass::AddItem as the type constructors expand it inline (Count loaded before
// Capacity, early outs), and the FindIndex expansion that follows it. The two AddItem shapes
// (AddItemEarlyOut here, TypesAddItem below) are not interchangeable: they schedule differently.
template <class T> inline bool TypesAddItemEarlyOut(DynamicVectorClass<T>& v, const T& item)
{
    if (v.Count >= v.Capacity) {
        int cap = v.Capacity;
        if (!v.IsAllocated && cap != 0)
            return false;
        if (v.CapacityIncrement <= 0)
            return false;
        if (!v.SetCapacity(v.CapacityIncrement + cap, 0))
            return false;
    }
    int index = v.Count++;
    v.Items[index] = item;
    return true;
}

template <class T> inline bool TypesAddItem(DynamicVectorClass<T>& v, const T& item)
{
    int cap = v.Capacity;
    if (v.Count < cap
        || ((v.IsAllocated || cap == 0)
            && v.CapacityIncrement > 0
            && v.SetCapacity(v.CapacityIncrement + cap, 0))) {
        v.Items[v.Count++] = item;
        return true;
    }
    return false;
}

template <class T> inline int TypesFindIndex(const DynamicVectorClass<T>& v, const T& item)
{
    int i;
    for (i = 0; i < v.Count; ++i) {
        if (v.Items[i] == item)
            return i;
    }
    return -1;
}

// The same lookup with the count read once before the loop (schedules differently from
// TypesFindIndex when it is the last statement of a constructor).
template <class T> inline int TypesFindIndexHoisted(const DynamicVectorClass<T>& v, const T& item)
{
    for (int i = 0, n = v.Count; i < n; ++i) {
        if (v.Items[i] == item)
            return i;
    }
    return -1;
}

// GLOBAL: GAMEMD 0x889F64 - the shared empty string the readers use as their text default.
extern const char TypesEmptyText[];

// FUNCTION: GAMEMD 0x7C9CC2 (LIBRARY) - strtok
// The three finders the veteran lists use; the name arrives in ECX (__fastcall shape).
// FUNCTION: GAMEMD 0x524CB0 (read-only here)
class InfantryTypeClass;
class UnitTypeClass;
class AircraftTypeClass;
InfantryTypeClass* __fastcall TypesFindInfantryType(const char* name);
// FUNCTION: GAMEMD 0x7480D0 (read-only here)
UnitTypeClass* __fastcall TypesFindUnitType(const char* name);
// FUNCTION: GAMEMD 0x41CEF0 (read-only here)
AircraftTypeClass* __fastcall TypesFindAircraftType(const char* name);

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_SHARED_H
