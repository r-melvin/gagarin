// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVBuildingTypeClass@@ (TD 0x8193A8): COLs 0x7FC618 / 0x7FC5A0 / 0x7FC588 / 0x7FC570 for the
//   tables 0x7E4570 (49 slots) / 0x7E4554 (6) / 0x7E454C (1) / 0x7E4544 (1); chain BuildingTypeClass ->
//   TechnoTypeClass -> ObjectTypeClass -> AbstractTypeClass -> AbstractClass -> IPersistStream ->
//   IPersist -> IUnknown, IRTTITypeInfo -> IUnknown, INoticeSink, INoticeSource. The constructor
//   0x45DD90 (every member store below), the INI reader 0x45FE50 (every key string and member offset),
//   the CRC slot 0x464B30, Load 0x465010, Save 0x465300, the scalar deleting destructor 0x465DC0 and
//   the allocation sites 0x465416, 0x466053 and 0x6C29BC (`PUSH 0x1798; CALL 0x7C8E17`, all agreeing).
//
// BuildingTypeClass: the rules-INI template of a building ([BuildingTypes] sections). The class itself is
// the canonical one in _layout/building_type_class_layout.h (TechnoTypeClass at +0x00..+0xDF7, the building
// members at +0xDF8..+0x1797, names are the INI keys the reader proves). This header holds what only the
// BuildingTypeClass module adds: the type array and the helper values its constructor copies.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_TYPE_CLASS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_TYPE_CLASS_H

#include "types_shared.h"
#include "_layout/cell.h"
#include "_layout/building_type_class_layout.h"

class HouseClass;

// Builds a point through a named local returned by value (the constructors make a by-value return go
// through a hidden pointer, as retail's does).
inline Point2D TypesMakePoint(int x, int y)
{
    Point2D point(x, y);
    return point;
}

// GLOBAL: GAMEMD 0xA83C68 -- the building type registry (Items at 0xA83C6C).
extern DynamicVectorClass<BuildingTypeClass*> DAT_00A83C68;

// sizeof is from the allocation: `PUSH 0x1798; CALL 0x7C8E17` at 0x465416, 0x466053, 0x6C29BC.

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_TYPE_CLASS_H
