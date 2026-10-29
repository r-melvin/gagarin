// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each body was read off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at the address in its annotation. Receiver names are
//   placeholders derived from the address.
//
// Quick-win sweep of small leaves. Ordered ascending by retail address.
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "../_rt/gg_static_assert.h"
#include "../network/wdt_rc_ptr.h"
#include "../audio/voc_class_play_at_methods.h"
#include "../audio/vox_class_play_index_methods.h"

namespace WorldDominationTour {
class Territory;
}

// ---------------------------------------------------------------------------
// 0x6F2B20: set bit 1 in a global flag byte.
// GLOBAL: GAMEMD 0xB0EA38
extern unsigned char Flags_00B0EA38;

// FUNCTION: GAMEMD 0x6F2B20
// Sets bit 1 of the global flag byte if it is not already set.
void FUN_006F2B20()
{
    if (!(Flags_00B0EA38 & 2)) {
        Flags_00B0EA38 |= 2;
    }
}

// ---------------------------------------------------------------------------
// 0x76F030: copy constructor of rc_ptr<WorldDominationTour::Territory>.
// FUNCTION: GAMEMD 0x76F030
// (the explicit instantiation below emits the copy constructor)
template class rc_ptr<WorldDominationTour::Territory>;

// ---------------------------------------------------------------------------
// 0x72F440: select one of three 3-byte colours.
struct Rgb3_0072F440
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};
GG_STATIC_ASSERT(sizeof(Rgb3_0072F440) == 3);

// GLOBAL: GAMEMD 0xB0F9D8
extern Rgb3_0072F440 ColorA_00B0F9D8;
// GLOBAL: GAMEMD 0xB0FB04
extern Rgb3_0072F440 ColorB_00B0FB04;
// GLOBAL: GAMEMD 0xB0FAA0
extern Rgb3_0072F440 ColorC_00B0FAA0;
// GLOBAL: GAMEMD 0xB0FA1C
extern Rgb3_0072F440 ColorCur_00B0FA1C;

// FUNCTION: GAMEMD 0x72F440
// Copies colour 0, 1 or (any other index) 2 into the current colour.
void __fastcall FUN_0072F440(int index)
{
    if (index == 0) {
        ColorCur_00B0FA1C = ColorA_00B0F9D8;
    } else if (index == 1) {
        ColorCur_00B0FA1C = ColorB_00B0FB04;
    } else {
        ColorCur_00B0FA1C = ColorC_00B0FAA0;
    }
}

// ---------------------------------------------------------------------------
// 0x753BF0: pack a 256-entry RGB palette into 16-bit pixel values.
// GLOBAL: GAMEMD 0xB2FB78
extern Rgb3_0072F440 Palette_00B2FB78[256];
// GLOBAL: GAMEMD 0xB2D5EC
extern unsigned short Packed_00B2D5EC[256];

// FUNCTION: GAMEMD 0x753BF0
//
// The index is unsigned (retail ends the walk with an unsigned compare, JB) and the
// first shift count is a full register (retail copies ECX to EDX whole).
// Each palette entry is shifted right then left per channel and the three
// channels are or-ed into one 16-bit value.
void __fastcall FUN_00753BF0(unsigned int shiftA, int leftA,
                             unsigned char shiftB, int leftB,
                             unsigned char shiftC, int leftC)
{
    for (unsigned i = 0; i < 256; i++) {
        unsigned short v = (unsigned short)((unsigned char)(Palette_00B2FB78[i].R >> shiftA) << leftA);
        v |= (unsigned short)((unsigned char)(Palette_00B2FB78[i].B >> shiftC) << leftC);
        v |= (unsigned short)((unsigned char)(Palette_00B2FB78[i].G >> shiftB) << leftB);
        Packed_00B2D5EC[i] = v;
    }
}

