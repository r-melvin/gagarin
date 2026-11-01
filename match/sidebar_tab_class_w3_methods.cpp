// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. The TabClass command-bar
//   shape table helpers (layout and evidence: sidebar_class_layout.h), as free routines.
//
// Address index: 0x6D0F10 loads the 25 shapes, 0x6D0F70 frees them.

#include "sidebar_class_layout.h"
#include "file_system_load_whole_methods.h"
#include "cell_coord_globals.h"

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// FUNCTION: GAMEMD 0x6D0F10
// Loads Button00.SHP to Button24.SHP.
void FUN_006D0F10()
{
    char name[0x100];
    bool owned = false;
    for (int i = 0; i < 25; ++i) {
        sprintf(name, "Button%02d.SHP", i);
        CommandShapes_00B0C148[i] = static_cast<SidebarShapeFile*>(FileSystem_LoadWholeFileEx(name, &owned));
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
