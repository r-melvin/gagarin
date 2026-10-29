// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// /Ob2 inlines the local copy constructor into Clone: default flags score 0% there, /Ob2 scores 95.7%.

#include "../_layout/enum_connection_points_class.h"
#include "vector_class_operations.h"

GG_STATIC_ASSERT(sizeof(HRESULT) == 4);
GG_STATIC_ASSERT(sizeof(LONG) == 4);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(IConnectionPoint*) == 4);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Index) == 0x04);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, RefCount) == 0x08);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.Items) == 0x10);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.Capacity) == 0x14);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.IsInitialized) == 0x18);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.IsAllocated) == 0x19);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.Count) == 0x1C);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.CapacityIncrement) == 0x20);
GG_STATIC_ASSERT(sizeof(EnumConnectionPointsClass) == 0x24);

// FUNCTION: GAMEMD 0x4A0B20
HRESULT __stdcall EnumConnectionPointsClass::Clone(IEnumConnectionPoints** out)
{
    if (out == 0)
        return E_POINTER;

    EnumConnectionPointsClass* clone = new EnumConnectionPointsClass(*this);
    if (clone == 0)
        return E_OUTOFMEMORY;

    clone->AddRef();
    *out = clone;
    return S_OK;
}

// FUNCTION: GAMEMD 0x4A0C20
EnumConnectionPointsClass::EnumConnectionPointsClass(
    const DynamicVectorClass<IConnectionPoint*>& points)
    : Index(0), RefCount(0), Points(points)
{
    int i = 0;
    if (i < Points.Count) {
        do {
            Points.Items[i]->AddRef();
            ++i;
        } while (i < Points.Count);
    }
}

// FUNCTION: GAMEMD 0x4A0CE0
EnumConnectionPointsClass::EnumConnectionPointsClass(
    const EnumConnectionPointsClass& other)
    : Index(other.Index), RefCount(0), Points(other.Points)
{
    int i = 0;
    if (i < Points.Count) {
        do {
            Points.Items[i]->AddRef();
            ++i;
        } while (i < Points.Count);
    }
}
