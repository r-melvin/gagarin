// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the addresses annotated
//   below. Layout offsets are read numerically off the disassembly; the surface
//   vtable slots (+0x5C Lock, +0x60 Unlock, +0x74 GetPitch, +0x78 GetRect,
//   +0x80 GetHeight, +0x14 FillRect, +0x08 CopyFromPart) are the canonical Surface
//   slots.
//
// Methods of the Bink video player object (the one whose teardown is
// 0x432700). Functions are ordered ascending by retail address.

#include <windows.h>
#include "bink_player_teardown_methods.h"

extern "C" __declspec(dllimport) int __stdcall BinkCopyToBuffer(void* bink, void* dest, unsigned int pitch,
    unsigned int height, int x, int y, unsigned int flags);

extern "C" __declspec(dllimport) int __stdcall BinkPause(void* bink, int pause);   // IAT 0x7E15B0

// GLOBAL: GAMEMD 0x887308
extern Surface* DAT_00887308;
// GLOBAL: GAMEMD 0xB73550 -- the game window.
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0xA8ED80 -- set while the game window is active.
extern bool DAT_00A8ED80;
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x433060
// Redraw the current frame; when the player draws on the primary surface the
// area is offset by the client origin on screen.
void MSBinkPlayer::FUN_00433060()
{
    if (Screen == DAT_00887308) {
        RECT rect;
        GetClientRect(DAT_00B73550, &rect);
        ClientToScreen(DAT_00B73550, (POINT*)&rect);
        int x = Area.X + rect.left;
        int y = Area.Y + rect.top;
        Surface* surface = Screen;
        FUN_00433330(surface);
        void* buffer = surface->Lock(Point2D(0, 0));
        if (buffer) {
            unsigned int pitch = surface->GetPitch();
            unsigned int height = surface->GetHeight();
            BinkCopyToBuffer(Bink, buffer, pitch, height, x, y, Flags | 0x80000000);
            surface->Unlock();
        }
        FUN_00433270(surface);
    } else {
        int y = Area.Y;
        int x = Area.X;
        Surface* surface = Screen;
        FUN_00433330(surface);
        void* buffer = surface->Lock(Point2D(0, 0));
        if (buffer) {
            unsigned int pitch = surface->GetPitch();
            unsigned int height = surface->GetHeight();
            BinkCopyToBuffer(Bink, buffer, pitch, height, x, y, Flags | 0x80000000);
            surface->Unlock();
        }
        FUN_00433270(surface);
    }
}

// FUNCTION: GAMEMD 0x433180
void MSBinkPlayer::FUN_00433180(Surface* surface, int x, int y)
{
    FUN_00433330(surface);
    void* buffer = surface->Lock(Point2D(0, 0));
    if (buffer) {
        unsigned int pitch = surface->GetPitch();
        unsigned int height = surface->GetHeight();
        BinkCopyToBuffer(Bink, buffer, pitch, height, x, y, Flags | 0x80000000);
        surface->Unlock();
    }
    FUN_00433270(surface);
}

// FUNCTION: GAMEMD 0x4331F0
void MSBinkPlayer::FUN_004331F0(Surface* surface, int x, int y, bool flag)
{
    if (flag)
        FUN_00433330(surface);
    void* buffer = surface->Lock(Point2D(0, 0));
    if (buffer) {
        unsigned int pitch = surface->GetPitch();
        unsigned int height = surface->GetHeight();
        unsigned int flags = Flags;
        if (flag)
            flags |= 0x80000000;
        BinkCopyToBuffer(Bink, buffer, pitch, height, x, y, flags);
        surface->Unlock();
    }
    FUN_00433270(surface);
}

// FUNCTION: GAMEMD 0x4333F0
// Follow the window's activation: pause the movie when it goes inactive, and
// resume it (redrawing the frame) when it becomes active again.
void MSBinkPlayer::FUN_004333F0()
{
    if (!DAT_00A8ED80) {
        if (Playing == true) {
            FUN_004068E0("Pause bink movie\n");
            Playing = false;
            BinkPause(Bink, 1);
        }
        return;
    }
    if (Playing)
        return;
    FUN_004068E0("Resume bink movie\n");
    Playing = true;
    BinkPause(Bink, 0);
    if (Screen == DAT_00887308) {
        RECT rect;
        GetClientRect(DAT_00B73550, &rect);
        ClientToScreen(DAT_00B73550, (POINT*)&rect);
        int x = Area.X + rect.left;
        int y = Area.Y + rect.top;
        Surface* surface = Screen;
        FUN_00433330(surface);
        void* buffer = surface->Lock(Point2D(0, 0));
        if (buffer) {
            unsigned int pitch = surface->GetPitch();
            unsigned int height = surface->GetHeight();
            BinkCopyToBuffer(Bink, buffer, pitch, height, x, y, Flags | 0x80000000);
            surface->Unlock();
        }
        FUN_00433270(surface);
    } else {
        int y = Area.Y;
        int x = Area.X;
        Surface* surface = Screen;
        FUN_00433330(surface);
        void* buffer = surface->Lock(Point2D(0, 0));
        if (buffer) {
            unsigned int pitch = surface->GetPitch();
            unsigned int height = surface->GetHeight();
            BinkCopyToBuffer(Bink, buffer, pitch, height, x, y, Flags | 0x80000000);
            surface->Unlock();
        }
        FUN_00433270(surface);
    }
}
