// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Movie stream shutdown read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI.
//   Address index: 0x7C2C60.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Movie stream object (same layout family as MovieStream_007BD210): two callbacks at +0x40/+0x44,
// flag bytes at +0x84/+0xEA/+0x150, a buffer at +0x158, and a flag word at +0x7BC.
struct MovieStream_007C2C60
{
    char unknown_000[0x40];
    void (__cdecl* Callback40)(MovieStream_007C2C60* self, int op, int a, int b);   // +0x40
    void (__cdecl* Callback44)(MovieStream_007C2C60* self, int op, int a, int b);   // +0x44
    char unknown_048[0x3C];
    unsigned char Flags84;                                                           // +0x84
    char unknown_085[0x65];
    unsigned char FlagsEA;                                                           // +0xEA
    char unknown_0EB[0x65];
    unsigned char Flags150;                                                          // +0x150
    char unknown_151[7];
    int Buffer;                                                                      // +0x158
    int Stride;                                                                      // +0x15C
    int Rows;                                                                        // +0x160
    char unknown_164[0x658];
    unsigned int Flags;                                                              // +0x7BC
};
GG_STATIC_ASSERT(offsetof(MovieStream_007C2C60, Callback44) == 0x44);
GG_STATIC_ASSERT(offsetof(MovieStream_007C2C60, Flags84) == 0x84);
GG_STATIC_ASSERT(offsetof(MovieStream_007C2C60, FlagsEA) == 0xEA);
GG_STATIC_ASSERT(offsetof(MovieStream_007C2C60, Flags150) == 0x150);
GG_STATIC_ASSERT(offsetof(MovieStream_007C2C60, Buffer) == 0x158);
GG_STATIC_ASSERT(offsetof(MovieStream_007C2C60, Rows) == 0x160);
GG_STATIC_ASSERT(offsetof(MovieStream_007C2C60, Flags) == 0x7BC);

// FUNCTION: GAMEMD 0x7BD210 (decl; reloc) -- stops the stream.
void __fastcall FUN_007BD210(MovieStream_007C2C60* self);
// FUNCTION: GAMEMD 0x7BDF80 (decl; reloc)
void __fastcall FUN_007BDF80(MovieStream_007C2C60* self);
// FUNCTION: GAMEMD 0x412600 (decl; reloc)
void __cdecl FUN_00412600();

// FUNCTION: GAMEMD 0x7C2C60
// Closes the stream: stops playback, releases a locked buffer, then sends the shutdown ops.
void __fastcall FUN_007C2C60(MovieStream_007C2C60* self)
{
    if ((self->Flags84 & 1) && (self->FlagsEA & 3)) {
        FUN_007BD210(self);
        if (self->Flags & 0x40000000) {
            FUN_00412600();
            self->Flags &= ~0x40000000;
        }
    }
    if ((self->Flags150 & 0x20) && self->Buffer) {
        self->Callback44(self, 5, self->Buffer, self->Rows * self->Stride);
        self->Callback44(self, 3, self->Buffer, 0);
    }
    FUN_007BDF80(self);
    self->Callback40(self, 4, 0, 0);
    self->Callback44(self, 5, (int)self, 0x7DC);
    self->Callback44(self, 3, (int)self, 0);
}
