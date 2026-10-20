// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x68C9C0. Array globals 0x00B054D4 (Items) and
//   0x00B054E0 (Count) are +0x04 and +0x10 of one vector, so the object sits at
//   0x00B054D0. Argument count and order cross-checked against YRpp's
//   `ColorScheme::Find_Or_Make(name, HSVClass&, PaletteClass*, PaletteClass*,
//   int)` (consult-only) and confirmed from the six pushes at the constructor.
//
// The control flow is unusual and deliberate: the scan is wrapped in an outer
// infinite loop. On a miss the function allocates and constructs a scheme, then
// jumps *back to the top of the scan* rather than returning — so the newly made
// entry is found by the next pass and its index returned. A failed allocation
// re-enters the same loop. That is why both 0x68CA24 and 0x68CA3C target
// 0x68C9D3, and it is what makes the function return an index rather than the
// pointer it just built.
#ifndef GG_MATCH_RENDERER_COLOR_SCHEME_FIND_METHODS_H
#define GG_MATCH_RENDERER_COLOR_SCHEME_FIND_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

struct HSVClass;
struct PaletteClass;

struct ColorScheme
{
    char        _pad000[0x304];        // +0x0000
    // A `char*`, not an inline buffer: retail loads a dword from +0x304 and
    // passes it straight to _stricmp. Modelling it as an array makes VC6 emit
    // `ADD EAX,0x304` (taking the address) instead of the load.
    const char* Name;                  // +0x0304
    char        _pad308[0x310 - 0x308];// +0x0308
    int         unknown_310;           // +0x0310  matched alongside the name
    char _pad314[0x33C - 0x314];

    ColorScheme(const char* name, HSVClass* hsv, PaletteClass* pal1,
                PaletteClass* pal2, int shade, bool flag) throw();   // GAMEMD 0x68C710

    static int __fastcall FindByName(const char* name, HSVClass* hsv,
                                     PaletteClass* pal1, PaletteClass* pal2,
                                     int shade);   // GAMEMD 0x68C9C0
};
GG_STATIC_ASSERT(offsetof(ColorScheme, Name)        == 0x304);
GG_STATIC_ASSERT(offsetof(ColorScheme, unknown_310) == 0x310);
GG_STATIC_ASSERT(sizeof(ColorScheme) == 0x33C);

// GLOBAL: GAMEMD 0x00B054D0 — ColorScheme::Array.
extern DynamicVectorClassLayout ColorSchemeArray;

#endif  // GG_MATCH_RENDERER_COLOR_SCHEME_FIND_METHODS_H
