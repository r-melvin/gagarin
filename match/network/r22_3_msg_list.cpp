// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x64AC90.
//
// Address index: 0x64AC90

#include "../core/vector_class_operations.h"
#include "../core/vector_add_item_free.h"

// A 0x1C7-byte record kept in the global pointer list at 0xA8BB28.
struct Record_0064AC90
{
    char Bytes[0x1C7];

    // FUNCTION: GAMEMD 0x64AC90 (__thiscall)
    void FUN_0064AC90();
};

// GLOBAL: GAMEMD 0xA8BB28
extern DynamicVectorClass<Record_0064AC90*> DAT_00A8BB28;

// FUNCTION: GAMEMD 0x64AC90
// Append a heap copy of this record to the global list.
void Record_0064AC90::FUN_0064AC90()
{
    Record_0064AC90* copy = new Record_0064AC90;
    *copy = *this;
    DynamicVectorAddItemFree(&DAT_00A8BB28, copy);
}
