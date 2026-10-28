// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small leaf bodies from
//   the 0x6B0000-0x6DA000 range; the receivers are placeholder views of the members touched.
//
// Address index: 0x6B10D0 0x6BA120 0x6C87D0 0x6C89B0 0x6C89D0 0x6C9820 0x6C9940 0x6CA670
//                0x6CA680 0x6CE2C0 0x6D1810 0x6D9910

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "frame_counter.h"

// A timed window: a flag, the frame it opened and the frame it closes.
struct Window_006B10D0
{
    unsigned char unknown_00[0x5C];
    int Enabled;      // +0x5C
    int CloseFrame;   // +0x60

    void FUN_006B10D0(int enabled);
};
GG_STATIC_ASSERT(offsetof(Window_006B10D0, Enabled) == 0x5C);
GG_STATIC_ASSERT(offsetof(Window_006B10D0, CloseFrame) == 0x60);

// FUNCTION: GAMEMD 0x6B10D0
// Stores the flag; turning it off stamps the current frame, turning it on opens the window
// to the far future.
void Window_006B10D0::FUN_006B10D0(int enabled)
{
    Enabled = enabled;
    if (!enabled) {
        CloseFrame = CurrentFrame;
    } else {
        CloseFrame = 0x7FFFFFFF;
    }
}

struct Obj_006B9D00
{
    // FUNCTION: GAMEMD 0x6B9D00 (decl; reloc)
    int FUN_006B9D00(unsigned int* a1, int a2, int a3);
    // FUNCTION: GAMEMD 0x6BA120
    int FUN_006BA120(unsigned int* a1);
};

// FUNCTION: GAMEMD 0x6BA120
// Forwards with both trailing flags set.
int Obj_006B9D00::FUN_006BA120(unsigned int* a1)
{
    return FUN_006B9D00(a1, 1, 1);
}

// FUNCTION: GAMEMD 0x6C87D0
// One past the index of the last non-null entry among the first n, or zero when all are null.
int __fastcall FUN_006C87D0(int* entries, int n)
{
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (entries[i]) {
            result = i + 1;
        }
    }
    return result;
}

// A heap block remembered by its start and its running end.
struct Block_006C89B0
{
    int Size;       // +0x00
    void* Start;    // +0x04
    void* Cursor;   // +0x08

    Block_006C89B0* FUN_006C89B0(int size);
    void FUN_006C89D0();
};
GG_STATIC_ASSERT(offsetof(Block_006C89B0, Start) == 0x04);
GG_STATIC_ASSERT(offsetof(Block_006C89B0, Cursor) == 0x08);

// FUNCTION: GAMEMD 0x6C89B0
// Allocates the block.
Block_006C89B0* Block_006C89B0::FUN_006C89B0(int size)
{
    Size = size;
    Start = ::operator new(size);
    Cursor = Start;
    return this;
}

// FUNCTION: GAMEMD 0x6C89D0
// Frees the block when there is one.
void Block_006C89B0::FUN_006C89D0()
{
    if (Start) {
        ::operator delete(Start);
    }
}

// GLOBAL: GAMEMD 0x7E1748 -- 0.0f.
extern const float DAT_007E1748;

struct Float4_006C9820
{
    float Values[4];

    int FUN_006C9820() const;
};

// FUNCTION: GAMEMD 0x6C9820
// Index of the first of the four values above the constant, or -1.
int Float4_006C9820::FUN_006C9820() const
{
    for (int i = 0; i < 4; i++) {
        if (Values[i] > DAT_007E1748) {
            return i;
        }
    }
    return -1;
}

struct Packed_006C9940
{
    unsigned char unknown_00[8];
    unsigned int Packed;   // +0x08

    void FUN_006C9940(unsigned char hi, unsigned char mid, unsigned char lo);
};
GG_STATIC_ASSERT(offsetof(Packed_006C9940, Packed) == 0x08);

// FUNCTION: GAMEMD 0x6C9940
// Packs three bytes into the low three bytes of the word.
void Packed_006C9940::FUN_006C9940(unsigned char hi, unsigned char mid, unsigned char lo)
{
    Packed = (((hi << 8) | mid) << 8) | lo;
}

// FUNCTION: GAMEMD 0x6CA5A0 (decl; reloc)
int __fastcall FUN_006CA5A0(short* p);

// FUNCTION: GAMEMD 0x6CA670
void __fastcall FUN_006CA670(short* p, int* out)
{
    *out = FUN_006CA5A0(p);
}

// FUNCTION: GAMEMD 0x6CA680
// Stores the second output only when the lookup finds something.
void __fastcall FUN_006CA680(short* p, int* out)
{
    unsigned int r = FUN_006CA5A0(p);
    if (r > 0) {
        out[1] = r;
    }
}

// FUNCTION: GAMEMD 0x6CE2C0
// Starts a countdown clock if it has not started.
void __fastcall FUN_006CE2C0(int* startTime)
{
    if (*startTime == -1) {
        *startTime = CurrentFrame;
    }
}

struct Zero7_006D1810
{
    int a, b, c, d, e, f;
    unsigned char g;

    Zero7_006D1810* FUN_006D1810();
};
GG_STATIC_ASSERT(offsetof(Zero7_006D1810, g) == 0x18);

// FUNCTION: GAMEMD 0x6D1810
// Clears all fields.
Zero7_006D1810* Zero7_006D1810::FUN_006D1810()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    g = 0;
    return this;
}

// FUNCTION: GAMEMD 0x4D1890 (decl; reloc)
void __fastcall FUN_004D1890(int* p);

// FUNCTION: GAMEMD 0x6D9910
void __stdcall FUN_006D9910(int* p)
{
    FUN_004D1890(p);
}
