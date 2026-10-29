// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Operations on the global undo list DynamicVectorClass<UndoInfoStruct> at 0xB0B650
//   (defined in core/static_vector_dtor_stubs_b.cpp), read off the retail
//   disassembly of 0x6B2430 and 0x6B24A0.
//
//   0x6B2430  FUN_006B2430  append one undo record
//   0x6B24A0  FUN_006B24A0  replay the list newest-first and empty it

#include "../core/vector_class_operations.h"
#include "../core/undo_info_struct.h"

// GLOBAL: GAMEMD 0xB0B650
extern DynamicVectorClass<UndoInfoStruct> DAT_00B0B650;

// GLOBAL: GAMEMD 0x8759A4
extern int DAT_008759A4;

// One eight-byte slot of the grid at 0xB0B6EC; only its first word is written.
struct UndoGridSlot_006B24A0
{
    int unknown_00;
    int unknown_04;
};

// GLOBAL: GAMEMD 0xB0B6EC
extern UndoGridSlot_006B24A0* DAT_00B0B6EC;

// FUNCTION: GAMEMD 0x6B2430
// PARTIAL: 90%. Same instructions as retail; retail adds the increment before loading the
// vtable pointer for the SetCapacity call, the shared AddItem expansion loads it after.
// Appends (cell x, cell y, value) to the undo list.
void __fastcall FUN_006B2430(const int* cell, int value)
{
    UndoInfoStruct record;
    record.unknown_00 = cell[0];
    record.unknown_04 = cell[1];
    record.unknown_08 = value;
    DAT_00B0B650.AddItem(record);
}

// FUNCTION: GAMEMD 0x6B24A0
// Writes each saved value back into the grid, last record first, then empties
// the list.
void FUN_006B24A0()
{
    for (int i = DAT_00B0B650.Count - 1; i >= 0; i--) {
        UndoInfoStruct& record = DAT_00B0B650.Items[i];
        DAT_00B0B6EC[record.unknown_04 * DAT_008759A4 + record.unknown_00].unknown_00 = record.unknown_08;
    }
    DAT_00B0B650.Clear();
}
