// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small movie-stream handle accessors and setters read off retail gamemd.exe v1.001. The
//   handle is MovieHandle_007BD470 (movie_stream_handle.h), passed in ECX (fastcall, /Gr).
//   Address index: 0x7BE660, 0x7BF230, 0x7C0490, 0x7C04E0, 0x7C1130, 0x7C1D40, 0x7C3230, 0x7C35B0,
//   0x7C3670, 0x7C3690, 0x7C3710, 0x7C3840.

#include "movie_stream_handle.h"
#include "../renderer/trivial_tu296_methods.h"

// The empty drawer (0x7BF220) installed when none is given.
#define EMPTY_DRAWER ((MovieDrawFn_007BD470)FUN_007BF220)

// FUNCTION: GAMEMD 0x7BE660
// Clears the current file position and reports failure.
int FUN_007be660(MovieHandle_007BD470* h)
{
    h->unknown_1A0.unknown_530 = -1;
    return -1;
}

// FUNCTION: GAMEMD 0x7BF230
// Always reports failure.
int FUN_007bf230(MovieHandle_007BD470* h)
{
    return -1;
}

// Index table entry: frame number in the low word.
struct MovieHandleIndexEntry
{
    unsigned short Frame;
    unsigned short Extra;
};

// FUNCTION: GAMEMD 0x7BF470 (decl; reloc) -- steps the stream one chunk.
int FUN_007bf470(MovieHandle_007BD470* h, int mode);

// FUNCTION: GAMEMD 0x7C0490
// Steps up to the configured number of chunks; a stalled step is counted, a hard error returned.
int FUN_007c0490(MovieHandle_007BD470* h)
{
    int i = 0;
    if (h->unknown_40.unknown_48 > 0) {
        do {
            int rc = FUN_007bf470(h, 0x20);
            if (rc == -1) {
                h->unknown_14++;
            } else if (rc != -9 && rc != -11) {
                return rc;
            }
            i++;
        } while (i < h->unknown_40.unknown_48);
    }
    return -1;
}

// FUNCTION: GAMEMD 0x7C04E0
// Whether a frame is listed in the index table (always true for frame zero).
char FUN_007c04e0(MovieHandle_007BD470* h, int frame)
{
    if (frame == 0) {
        return 1;
    }
    int count = h->unknown_714;
    if (count > 0 && (*(unsigned char*)&h->unknown_716 & 3)) {
        MovieHandleIndexEntry* entry = (MovieHandleIndexEntry*)h->unknown_71C;
        for (int i = 0; i < count; i++, entry++) {
            if (frame == entry->Frame) {
                return 1;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7C1130
// Reads a chunk (rounded up to an even size) into the header's trailing area; -4 when the
// read fails.
int FUN_007c1130(MovieHandle_007BD470* h, unsigned long size)
{
    return h->unknown_40.unknown_0(h, 5, (char*)h + 0x112, (size + 1) & ~1) ? -4 : -1;
}

// FUNCTION: GAMEMD 0x7C1D40
// Reads a chunk (rounded up to an even size) into the buffer at +0x764, or into a fresh one
// when there is none; -4 and -6 name the two failures.
int FUN_007c1d40(MovieHandle_007BD470* h, unsigned long size)
{
    if (h->unknown_764) {
        if (h->unknown_40.unknown_0(h, 5, h->unknown_764, (size + 1) & ~1)) {
            return -4;
        }
    } else {
        if (h->unknown_40.unknown_0(h, 7, (void*)1, (size + 1) & ~1)) {
            return -6;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x7C3230
// Installs the two block drawers, or the empty one for a null argument.
int FUN_007c3230(MovieHandle_007BD470* h, MovieDrawFn_007BD470 first, MovieDrawFn_007BD470 second)
{
    if (first) {
        h->unknown_784 = first;
    } else {
        h->unknown_784 = EMPTY_DRAWER;
    }
    if (second) {
        h->unknown_788 = second;
    } else {
        h->unknown_788 = EMPTY_DRAWER;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x7C35B0
// The word at +0x714.
int FUN_007c35b0(MovieHandle_007BD470* h)
{
    return h->unknown_714;
}

// FUNCTION: GAMEMD 0x7C3670
// Forgets the three position members.
int FUN_007c3670(MovieHandle_007BD470* h)
{
    h->unknown_710 = -1;
    h->unknown_708 = -1;
    h->unknown_70C = -1;
    return -1;
}

// FUNCTION: GAMEMD 0x7C3690
// Replaces the member at +0x11C with a value within the header's word at +4; returns the old
// one, or -1 when the value is out of range.
int FUN_007c3690(MovieHandle_007BD470* h, int value)
{
    int old = -1;
    if (value > 0 && h->unknown_E8.unknown_4 >= value) {
        old = h->unknown_11C;
        h->unknown_11C = value & 0xFFFF;
    }
    return old;
}

// FUNCTION: GAMEMD 0x7C3710
// Reads three header bytes into the caller's ints.
int FUN_007c3710(MovieHandle_007BD470* h, int* first, int* second, int* third)
{
    *first = h->unknown_E8.unknown_A;
    *second = h->unknown_E8.unknown_B;
    *third = h->unknown_E8.unknown_20;
    return -1;
}

// FUNCTION: GAMEMD 0x7C3840
// Reads two header words into the caller's ints.
int FUN_007c3840(MovieHandle_007BD470* h, int* first, int* second)
{
    *first = h->unknown_E8.unknown_12;
    *second = h->unknown_E8.unknown_14;
    return -1;
}
