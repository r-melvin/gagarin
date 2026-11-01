// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Native 0x688ED0: object in ECX, read-only cell address in EDX, distance
// on the stack. Caller 0x5D70B1..0x5D70BF passes the hidden result of
// HouseClass::FUN_0050DEF0 directly. A const reference expresses this ABI
// without copying the returned value; no original source spelling is claimed.
#ifndef GG_MATCH_MAP_OBJECT_PLACEMENT_H
#define GG_MATCH_MAP_OBJECT_PLACEMENT_H
class ObjectClass;
struct CellStruct;
// Declaration: GAMEMD 0x688ED0
int __fastcall FUN_00688ED0(ObjectClass* object, const CellStruct& cell, int distance);
#endif
