// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include "../_layout/connection_point_class.h"
#include "../_layout/enum_connections_class.h"
#include "../_layout/enum_connection_points_class.h"
#include "vector_class_dynamic_ctor.h"
// Native 4A045F/466, 4A047A-4A04A6; 4A0DBF/C6 and 4A0DDA-4A0E06.
GG_STATIC_ASSERT(offsetof(tagCONNECTDATA, pUnk) == 0);
GG_STATIC_ASSERT(offsetof(tagCONNECTDATA, dwCookie) == 4);
GG_STATIC_ASSERT(sizeof(tagCONNECTDATA) == 8);
GG_STATIC_ASSERT(sizeof(LONG) == 4);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(IUnknown*) == 4);
GG_STATIC_ASSERT(sizeof(IConnectionPoint*) == 4);
GG_STATIC_ASSERT(sizeof(IID) == 0x10);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.Capacity) == 0x0C);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.IsAllocated) == 0x11);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.Capacity) == 0x14);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.IsAllocated) == 0x19);
// Native 4A0870-4A08C3 and 4A08D4-4A0911.
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Connections.Items) == 0x20);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Connections.Capacity) == 0x24);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Connections.IsAllocated) == 0x29);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Connections.IsInitialized) == 0x28);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Connections.Count) == 0x2C);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Connections.CapacityIncrement) == 0x30);
// GLOBAL: GAMEMD 0xABCD3C
extern int DAT_00ABCD3C;
GG_STATIC_ASSERT(sizeof(DAT_00ABCD3C) == 4);
// FUNCTION: GAMEMD 0x4A0450
EnumConnectionsClass::~EnumConnectionsClass() {
    for (int i = 0; i < Connections.Count; ++i) Connections.Items[i].pUnk->Release();
    Connections.Clear();
}
// FUNCTION: GAMEMD 0x4A0540
ULONG __stdcall ConnectionPointClass::Release() {
    --DAT_00ABCD3C;
    LONG count = InterlockedDecrement(&RefCount);
    if (count == 0) delete this;
    return count;
}
// FUNCTION: GAMEMD 0x4A0870
ConnectionPointClass::ConnectionPointClass(const IID* iid, IUnknown* container)
    : Iid(*iid), RefCount(0), Container(container), Connections() { Container->AddRef(); }
// FUNCTION: GAMEMD 0x4A08D0
ConnectionPointClass::~ConnectionPointClass() { Container->Release(); Connections.Clear(); }
// FUNCTION: GAMEMD 0x4A09B0
ULONG __stdcall EnumConnectionPointsClass::Release() {
    --DAT_00ABCD3C;
    LONG count = InterlockedDecrement(&RefCount);
    if (count == 0) delete this;
    return count;
}
// FUNCTION: GAMEMD 0x4A0DB0
EnumConnectionPointsClass::~EnumConnectionPointsClass() {
    for (int i = 0; i < Points.Count; ++i) Points.Items[i]->Release();
    Points.Clear();
}
