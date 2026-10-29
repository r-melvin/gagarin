// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Movie player methods read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at
//   the address in each annotation. The receiver is a placeholder view named after its address.
//   Address index: 0x7597A0, 0x759BC0.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "movie_stream_handle.h"

int __fastcall FUN_007C2590(const char* name, MovieConfig_007BD470* config, MovieHandle_007BD470** out);
int __fastcall FUN_007C30D0(MovieHandle_007BD470* h, int frame, int arg);

struct MoviePlayer_r24
{
    char unknown_000[0x71];
    char Name[1];                // +0x71
    char unknown_72[0x178 - 0x72];
    MovieConfig_007BD470 Config; // +0x178
    MovieHandle_007BD470* Handle;     // +0x200
    char unknown_204[0x300];
    int Position;                // +0x504
    int FrameCount;              // +0x508
    int Rate;                    // +0x50C
    char unknown_510[4];
    bool Active;                 // +0x514
    char unknown_515[3];
    int Width;                   // +0x518
    int Height;                  // +0x51C

    // FUNCTION: GAMEMD 0x7597A0 (__thiscall)
    bool FUN_007597A0();
    // FUNCTION: GAMEMD 0x759BC0 (__thiscall)
    void FUN_00759BC0(int frame);
    void FUN_00759940(int frame, int flag);
};
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Name) == 0x71);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Config) == 0x178);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Handle) == 0x200);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Position) == 0x504);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, FrameCount) == 0x508);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Rate) == 0x50C);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Active) == 0x514);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Width) == 0x518);
GG_STATIC_ASSERT(offsetof(MoviePlayer_r24, Height) == 0x51C);

// FUNCTION: GAMEMD 0x7597A0
// Opens the movie named in this object; on success caches its frame count, rate and size
// and marks the player active, otherwise clears the active flag.
bool MoviePlayer_r24::FUN_007597A0()
{
    if (FUN_007C2590(Name, &Config, &Handle) != -1) {
        Active = false;
        return false;
    }
    FrameCount = Handle->unknown_10;
    Rate = Handle->unknown_C;
    Width = Handle->unknown_2;
    Height = Handle->unknown_4;
    Active = true;
    return true;
}

// FUNCTION: GAMEMD 0x759BC0
// Seeks to a frame (-1 means the last one) and refreshes the display; wraps the position
// back to the start when it runs off the end.
void MoviePlayer_r24::FUN_00759BC0(int frame)
{
    if (frame == -1) {
        frame = FrameCount - 1;
    }
    if (Position != frame) {
        if (FUN_007C30D0(Handle, frame, 0) != -6) {
            Position = frame;
        }
        Position = frame;
    }
    FUN_00759940(frame, 0);
    if ((unsigned int)Position >= (unsigned int)FrameCount) {
        Position = 0;
    }
}
