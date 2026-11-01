// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Element of the DynamicVectorClass<UndoInfoStruct> at 0xB0B650 (RTTI name from
// the vtable of that global; 12-byte stride read off 0x6B2430 and 0x6B24A0).
// Field meanings: two cell coordinates and the value to restore.
#ifndef GG_MATCH_CORE_UNDO_INFO_STRUCT_H
#define GG_MATCH_CORE_UNDO_INFO_STRUCT_H

struct UndoInfoStruct
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    UndoInfoStruct() : unknown_00(0), unknown_04(0), unknown_08(0) {}
    bool operator==(const UndoInfoStruct& o) const { return unknown_00 == o.unknown_00 && unknown_04 == o.unknown_04 && unknown_08 == o.unknown_08; }
    bool operator!=(const UndoInfoStruct& o) const { return !(*this == o); }
};

#endif
