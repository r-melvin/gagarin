// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x533F50 (0x74 bytes): walks the global command list (Items 0x87F65C, Count
//   0x87F668), compares each command's name (vtable slot 1, +0x04) with the argument by an inlined strcmp
//   and runs the first match (slot 8, +0x20) with key 0.
#include <string.h>
#include "../core/vector_class.h"
#include "command_class.h"

// GLOBAL: GAMEMD 0x87F658 -- every registered keyboard command (defined in static_vector_dtor_stubs.cpp).
extern DynamicVectorClass<const CommandClass*> DAT_0087F658;

// FUNCTION: GAMEMD 0x533F50
// Run the keyboard command called `name`, if there is one.
void FUN_00533F50(const char* name)
{
    for (int i = 0; i < DAT_0087F658.Count; ++i) {
        if (strcmp(DAT_0087F658.Items[i]->vf_1(), name) == 0) {
            DAT_0087F658.Items[i]->vf_8(0);
            return;
        }
    }
}
