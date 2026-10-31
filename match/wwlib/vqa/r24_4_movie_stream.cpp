// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Movie-stream step routines read off retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. The handle is MovieHandle_007BD470 (movie_stream_handle.h), passed
//   in ECX (fastcall, /Gr).
//   Address index: 0x7BF140, 0x7C19F0, 0x7C3430.

#include "movie_stream_handle.h"

// Helpers owned elsewhere.
int FUN_007bea80(MovieHandle_007BD470* h);
void FUN_007befe0(MovieHandle_007BD470* h);
void FUN_007be940(MovieHandle_007BD470* h, MovieFrame_007BD470* node);
int FUN_007c34b0(MovieHandle_007BD470* h, int start, int end, int a, int b);

// FUNCTION: GAMEMD 0x7BF140
// Steps the drawer to the next frame; when that reports -1, hands the node to the 0x7BE940 helper,
// publishes it as the shown frame and moves the drawer on unless it is holding.
// PARTIAL: 90.9%. Retail stores the shown frame before loading the drawer flags; VC6 hoists the
// flag load above the store for every plain ordering tried (temp node, direct fields, drawer pointer).
int FUN_007bf140(MovieHandle_007BD470* h)
{
    int r = FUN_007bea80(h);
    if (r == -1) {
        FUN_007befe0(h);
        MovieFrame_007BD470* node = h->unknown_1A0.unknown_0;
        FUN_007be940(h, node);
        h->unknown_6DC = node;
        if (!(h->unknown_1A0.unknown_4 & 8)) {
            h->unknown_1A0.unknown_0 = node->unknown_C;
        }
        return -1;
    }
    return r;
}

// Six-byte key table entry: the first frame of the group comes first.
struct MovieKeyEntry_r24
{
    unsigned short Frame;
    unsigned short Extra[2];
};

// FUNCTION: GAMEMD 0x7C19F0
// Finds the key group holding a frame: the last entry when none matches. Reports the group's first
// frame and the frame before the next group, and returns the group index.
int FUN_007c19f0(MovieHandle_007BD470* h, int frame, int* keyStart, int* keyEnd)
{
    MovieKeyEntry_r24* table = (MovieKeyEntry_r24*)h->unknown_754;
    int count = h->unknown_74C;
    int group = 0;
    for (int i = 1; i < count; i++) {
        if (frame >= table[i - 1].Frame && frame < table[i].Frame) {
            goto found;
        }
        group++;
    }
    group = count - 1;
found:
    int prev;
    int next;
    if (group == 0) {
        prev = 0;
        next = 0;
    } else {
        prev = group - 1;
        next = group;
    }
    if (keyStart) {
        *keyStart = table[prev].Frame;
    }
    if (keyEnd) {
        *keyEnd = table[next].Frame - 1;
    }
    return group;
}

// FUNCTION: GAMEMD 0x7C3430
// Seeks to a table entry: rejects an index outside the entry count (or any index when a counted
// stream has no entries), otherwise remembers it as the current entry and plays the entry's
// start/end range.
int FUN_007c3430(MovieHandle_007BD470* h, int index, int a, int b)
{
    int count = h->unknown_714;
    if (index >= count || index < 0 || ((h->unknown_40.unknown_44 & 1) && h->unknown_714 == 0)) {
        return -23;
    }
    unsigned short* entry = (unsigned short*)h->unknown_71C + index * 2;
    int hi = entry[1];
    int lo = entry[0];
    h->unknown_120 = index;
    int r = FUN_007c34b0(h, lo, hi, a, b);
    if (r == -1) {
        h->unknown_120 = index;
    }
    return r;
}
