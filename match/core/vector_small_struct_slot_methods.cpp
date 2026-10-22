// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI names VectorClass/DynamicVectorClass over tagCONNECTDATA, FoggedObjectClass::DrawRecord,
// DiskID and WorldDominationTour::Centroid. Layouts are binary-confirmed placeholders.
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct tagCONNECTDATA { void* pUnk; unsigned long dwCookie; bool operator==(const tagCONNECTDATA& o) const { return dwCookie==o.dwCookie && pUnk==o.pUnk; } bool operator!=(const tagCONNECTDATA& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x004A0F80
// VectorClass<tagCONNECTDATA>::operator==
// FUNCTION: GAMEMD 0x004A0FE0
// VectorClass<tagCONNECTDATA>::SetCapacity
// FUNCTION: GAMEMD 0x004A10D0
// VectorClass<tagCONNECTDATA>::FindItemIndex
// FUNCTION: GAMEMD 0x004A1120
// VectorClass<tagCONNECTDATA>::Slot5
// FUNCTION: GAMEMD 0x004A0F00
// VectorClass<tagCONNECTDATA>::Slot6
// FUNCTION: GAMEMD 0x004A1140
// DynamicVectorClass<tagCONNECTDATA>::SetCapacity
// FUNCTION: GAMEMD 0x004A1200
// DynamicVectorClass<tagCONNECTDATA>::FindItemIndex
// FUNCTION: GAMEMD 0x004A0EE0
// DynamicVectorClass<tagCONNECTDATA>::Slot5
// VTABLE: GAMEMD 0x007E5C84 -- VectorClass<tagCONNECTDATA>.
// VTABLE: GAMEMD 0x007E5CC4 -- DynamicVectorClass<tagCONNECTDATA>.
template class VectorClass<tagCONNECTDATA>;
template class DynamicVectorClass<tagCONNECTDATA>;

class FoggedObjectClass { public: struct DrawRecord { int unknown_00; int unknown_04; unsigned char unknown_08; int unknown_0C; DrawRecord() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0) {} DrawRecord(const DrawRecord& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const DrawRecord& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const DrawRecord& o) const { return !(*this==o); } }; };
// FUNCTION: GAMEMD 0x004D29B0
// VectorClass<FoggedObjectClass::DrawRecord>::operator==
// FUNCTION: GAMEMD 0x004D2A10
// VectorClass<FoggedObjectClass::DrawRecord>::SetCapacity
// FUNCTION: GAMEMD 0x004D2B50
// VectorClass<FoggedObjectClass::DrawRecord>::FindItemIndex
// FUNCTION: GAMEMD 0x004D2BA0
// VectorClass<FoggedObjectClass::DrawRecord>::Slot5
// FUNCTION: GAMEMD 0x004D2980
// VectorClass<FoggedObjectClass::DrawRecord>::Slot6
// FUNCTION: GAMEMD 0x004D2BC0
// DynamicVectorClass<FoggedObjectClass::DrawRecord>::SetCapacity
// FUNCTION: GAMEMD 0x004D2CD0
// DynamicVectorClass<FoggedObjectClass::DrawRecord>::FindItemIndex
// FUNCTION: GAMEMD 0x004D2960
// DynamicVectorClass<FoggedObjectClass::DrawRecord>::Slot5
// VTABLE: GAMEMD 0x007E8BC0 -- VectorClass<FoggedObjectClass::DrawRecord>.
// VTABLE: GAMEMD 0x007E8BA0 -- DynamicVectorClass<FoggedObjectClass::DrawRecord>.
template class VectorClass<FoggedObjectClass::DrawRecord>;
template class DynamicVectorClass<FoggedObjectClass::DrawRecord>;

struct DiskID { int unknown_00; bool operator==(const DiskID& o) const { return unknown_00==o.unknown_00; } bool operator!=(const DiskID& o) const { return !(*this==o); } };

template class VectorClass<DiskID>;

struct WorldDominationTour { struct Centroid { int unknown_00; int unknown_04; int unknown_08; Centroid() : unknown_00(0), unknown_04(0), unknown_08(0) {} bool operator==(const Centroid& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const Centroid& o) const { return !(*this==o); } }; };
// FUNCTION: GAMEMD 0x0076A390
// VectorClass<WorldDominationTour::Centroid>::operator==
// FUNCTION: GAMEMD 0x0076A3F0
// VectorClass<WorldDominationTour::Centroid>::SetCapacity
// FUNCTION: GAMEMD 0x0076A520
// VectorClass<WorldDominationTour::Centroid>::FindItemIndex
// FUNCTION: GAMEMD 0x0076A570
// VectorClass<WorldDominationTour::Centroid>::Slot5
// VTABLE: GAMEMD 0x007F71E0 -- VectorClass<WorldDominationTour::Centroid>.
template class VectorClass<WorldDominationTour::Centroid>;

