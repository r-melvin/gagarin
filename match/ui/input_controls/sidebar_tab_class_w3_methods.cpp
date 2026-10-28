// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. The TabClass command-bar
//   shape table helpers (layout and evidence: sidebar_class_layout.h), as free routines.
//
// Address index: 0x6D0F10 loads the 25 shapes, 0x6D0F70 frees them.

#include "sidebar_class_layout.h"

// GLOBAL: GAMEMD 0xB0C148 -- the 25 command-bar button shapes.
extern SidebarShapeFile* CommandShapes_00B0C148[25];
// GLOBAL: GAMEMD 0xB0CBDC -- "owns the memory" flag of each command-bar shape.
extern bool CommandShapeOwned_00B0CBDC[25];

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// FUNCTION: GAMEMD 0x4A38D0 (decl; reloc) -- loads a whole file, reporting whether the block is owned.
void* __fastcall FUN_004A38D0(const char* name, char* owned);

// FUNCTION: GAMEMD 0x6D0F10
// Loads Button00.SHP to Button24.SHP.
void FUN_006D0F10()
{
    char name[0x100];
    bool owned = false;
    for (int i = 0; i < 25; ++i) {
        sprintf(name, "Button%02d.SHP", i);
        CommandShapes_00B0C148[i] = static_cast<SidebarShapeFile*>(FUN_004A38D0(name, reinterpret_cast<char*>(&owned)));
        CommandShapeOwned_00B0CBDC[i] = owned;
    }
}

// FUNCTION: GAMEMD 0x6D0F70
// Frees the shapes that own their memory and clears the table.
void FUN_006D0F70()
{
    for (int i = 0; i < 25; ++i) {
        if (CommandShapeOwned_00B0CBDC[i]) {
            delete CommandShapes_00B0C148[i];
            CommandShapeOwned_00B0CBDC[i] = false;
        }
        CommandShapes_00B0C148[i] = 0;
    }
}
