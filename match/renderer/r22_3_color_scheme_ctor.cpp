// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x68C650.
//
// Address index: 0x68C650

#include "color_scheme_find_methods.h"
#include "../core/vector_add_item_free.h"

// FUNCTION: GAMEMD 0x68C650
// Empty colour scheme: zeroed palette records, no name, no converter, shade 1; registers itself
// in the global scheme list and records its index.
ColorScheme::ColorScheme() throw()
{
    Name = 0;
    unknown_308[0] = 0;
    unknown_308[1] = 0;
    unknown_308[2] = 0;
    unknown_30C = 0;
    unknown_310 = 1;
    DynamicVectorAddItemFree(&ColorSchemeArray, this);
    unknown_000 = ColorSchemeArray.Count;
}
