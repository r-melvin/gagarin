// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x45E8F0.

#include "font_bias_methods.h"

// FUNCTION: GAMEMD 0x45E8F0
//
// Load the image once and rebias every non-zero pixel by 0x41, in place. The
// global is both the "already loaded" flag and the result, so a second call does
// nothing.
//
// Zero pixels are left alone rather than being biased to a negative value — that
// is what makes 0 the transparent index and everything else an offset into a
// palette that starts at 'A'.
//
// PARTIAL (95.3%, 41/43) — identical multiset. One register delta remains: the
// inner load and store swap the SIB base and index roles (`[EDX+ECX]` against
// `[ECX+EDX]`) — the cheap addressing class in section 4.8. The global-store
// ordering delta recorded earlier no longer shows in the current build.
//
// Eleven further spellings were measured this pass and every one holds at
// 86.0% or drops. For the global store: the surface bound to a local with the
// global assigned from it and the load call made through the local; the same
// with the call made through the global; the store folded into an inline
// `Store(p)` helper whose result is the call's receiver; the scratch buffer
// bound to a `void*` local first; the load call lifted into an inline helper
// taking the surface as `Image_0045E8F0* const&` (the lever that resolved
// 0x40A260); and a volatile-qualified store of the global (81.4%). For the SIB
// roles: the reversed subscript `x[row]`, the pointer form `*(row + x)`, an
// unsigned loop index (81.4%), and the row rebound to a `char* const line`
// inside the loop. The rebias walk lifted into its own inline function scores
// 81.4%, so the two loops are one function in retail.
//
// The cursor and the row counter are separate locals copied from the pixel
// pointer and the height, and that is load-bearing rather than style. Retail
// copies both (`MOV EDX,EAX; MOV EDI,ECX` at 0x45E94C) because the originals stay
// live; walking the returned pointer directly and counting down the height
// in place removes both copies and scores 16.3%. Two extra locals, seventy
// points.
void FUN_0045E8F0()
{
    char scratch[0x10];

    if (DAT_0089DDBC != 0) {
        return;
    }

    DAT_0089DDBC = FUN_005B40B0(&DAT_008193F4, 0);
    DAT_0089DDBC->FUN_0069E7E0(scratch, 0);
    char* pixels = DAT_0089DDBC->FUN_0069E740(0);

    int width = DAT_0089DDBC->Width;
    int height = DAT_0089DDBC->Height;
    if (height <= 0) {
        return;
    }

    char* row = pixels;
    int rows = height;
    do {
        for (int x = 0; x < width; x++) {
            if (row[x] != 0) {
                row[x] = row[x] - 0x41;
            }
        }
        row += width;
        rows--;
    } while (rows != 0);
}
