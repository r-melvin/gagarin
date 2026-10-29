// SPDX-License-Identifier: GPL-3.0-or-later
// /Ob2: retail Clone inlines its copy constructor, vector copying and sink retention.
// Provenance: own-binary-via-Ghidra
#include "../_layout/enum_connections_class.h"
#include <ocidl.h>
// Native 0x4A0FA3 compares cookie and pointer for vector operations.
inline bool operator==(const tagCONNECTDATA& left, const tagCONNECTDATA& right)
{
    return left.dwCookie == right.dwCookie && left.pUnk == right.pUnk;
}
inline bool operator!=(const tagCONNECTDATA& left, const tagCONNECTDATA& right)
{
    return !(left == right);
}
#include "vector_class_operations.h"
#include <new.h>

// Native 0x4A0190..0x4A0282 accesses the copied vector and sink pointers.
GG_STATIC_ASSERT(offsetof(tagCONNECTDATA, pUnk) == 0);
GG_STATIC_ASSERT(offsetof(tagCONNECTDATA, dwCookie) == 4);
GG_STATIC_ASSERT(sizeof(tagCONNECTDATA) == 8);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.Capacity) == 0x0C);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.IsInitialized) == 0x10);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.IsAllocated) == 0x11);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.CapacityIncrement) == 0x18);

// GLOBAL: GAMEMD 0xABCD3C
extern int DAT_00ABCD3C;
GG_STATIC_ASSERT(sizeof(DAT_00ABCD3C) == 4);

// FUNCTION: GAMEMD 0x4A0010
ULONG __stdcall EnumConnectionsClass::Release() {
    --DAT_00ABCD3C;
    LONG count = InterlockedDecrement(&RefCount);
    if (count == 0) delete this;
    return count;
}

// FUNCTION: GAMEMD 0x4A0190
HRESULT __stdcall EnumConnectionsClass::Clone(IEnumConnections** ppEnum)
{
    if (ppEnum == 0) return E_POINTER;
    EnumConnectionsClass* copy = new EnumConnectionsClass(*this);
    if (copy == 0) return E_OUTOFMEMORY;
    copy->RefCount = 0;
    copy->AddRef();
    *ppEnum = copy;
    return S_OK;
}

// FUNCTION: GAMEMD 0x4A02B0
EnumConnectionsClass::EnumConnectionsClass(const DynamicVectorClass<tagCONNECTDATA>& connections)
    : Connections(connections), Index(0), RefCount(0)
{
    for (int i = 0; i < Connections.Count; ++i)
        Connections.Items[i].pUnk->AddRef();
}

// FUNCTION: GAMEMD 0x4A0380
// Native 0x4A0380: copy the vector and cursor, clear the reference count,
// and retain each sink.
EnumConnectionsClass::EnumConnectionsClass(const EnumConnectionsClass& other)
    : Connections(other.Connections), Index(other.Index), RefCount(0)
{
    for (int i = 0; i < Connections.Count; ++i)
        Connections.Items[i].pUnk->AddRef();
}

// FUNCTION: GAMEMD 0x4A0450
EnumConnectionsClass::~EnumConnectionsClass() {
    for (int i = 0; i < Connections.Count; ++i) Connections.Items[i].pUnk->Release();
    Connections.Clear();
}
