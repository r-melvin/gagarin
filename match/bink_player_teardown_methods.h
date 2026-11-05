// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, guards and import identities read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x432700 and
//   0x432A60. Neither address is bound by YRpp.
//
// Two byte-identical teardowns for a Bink video player object: release the
// helper allocation at +0x20, close the Bink handle at +0x04, close the Win32
// file handle at +0x28. Each is written out longhand rather than shared, per
// the family rule.
//
// The two import slots are identified from the call sites: 0x7E15A4 is
// BinkClose (it sits in the BINKW32 block alongside the already-confirmed
// BinkPause at 0x7E15B0) and 0x7E11E0 is CloseHandle, which is why the third
// field's empty value is -1 rather than 0.
#ifndef GG_MATCH_PLATFORM_BINK_PLAYER_TEARDOWN_METHODS_H
#define GG_MATCH_PLATFORM_BINK_PLAYER_TEARDOWN_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "wwlib/surface/surface_class.h"
#include "_layout/geometry2d.h"

// Declared __declspec(dllimport) so the calls go indirect through the IAT slot
// (`CALL dword ptr [0x7E15A4]`, six bytes) as retail does; without it cl emits
// a five-byte direct call to an import thunk and the lengths diverge.
extern "C" __declspec(dllimport) void __stdcall BinkClose(void* bink);      // IAT 0x7E15A4
extern "C" __declspec(dllimport) int  __stdcall CloseHandle(void* handle);  // IAT 0x7E11E0

// The helper at +0x20 is destroyed by hand and then freed: retail calls
// 0x6C9AE0 with the pointer in ECX, then pushes it to the __cdecl free at
// 0x7C8B3D. That is an explicit destructor call followed by operator delete,
// not the compiler-generated deleting destructor - a `??_G` would have folded
// the two into one call.
void FUN_006C9AE0(void* helper);
extern "C" void __cdecl FUN_007C8B3D(void* block);

// The Bink file header the player reads (dimensions and frame counters).
extern "C" __declspec(dllimport) int __stdcall BinkWait(void* bink);   // IAT 0x7E15C0

struct BinkFileHeader_00432AB0
{
    int Width;          // +0x00
    int Height;         // +0x04
    unsigned int Frames;        // +0x08
    unsigned int CurrentFrame;  // +0x0C
};

// The helper at +0x20: a back buffer with a source rectangle (+0x14) and a
// rectangle to clear (+0x24).
struct BinkHelper_00433270
{
    // FUNCTION: GAMEMD 0x6C9C60 (decl; reloc)
    bool FUN_006C9C60(int value);

    int Active;                 // +0x00
    char _pad04[0x0C];          // +0x04
    Surface* Buffer;            // +0x10
    RectangleStruct SourceRect; // +0x14
    RectangleStruct ClearRect;  // +0x24
};

// The Bink playback object held by MSBinkAnim. Its destructor is an ordinary
// non-virtual one: 0x5CEC83 is `MOV ECX,EDI; CALL 0x432700` followed by the
// plain `operator delete`, which is exactly what a `delete` of a class with a
// non-virtual destructor expands to.
// 0x4326C0 allocates 0x34 bytes (0x5CC7D7) and fills the fields below, and 0x432700 is this class's destructor.
class MSBinkPlayer
{
public:
    MSBinkPlayer(const char* file, int flags);  // FUNCTION: GAMEMD 0x4326C0 (decl)
    void Move(int x, int y);             // FUNCTION: GAMEMD 0x432AB0 (decl)
    bool IsDone();                       // FUNCTION: GAMEMD 0x432C50 (decl)

    bool  StopRequested;                // +0x0000
    char  _pad001[0x3];
    BinkFileHeader_00432AB0* Bink;      // +0x0004
    unsigned int Flags;                 // +0x0008
    Surface* Screen;                    // +0x000C
    RectangleStruct Area;               // +0x0010
    BinkHelper_00433270* Helper;        // +0x0020
    int unknown_24;                     // +0x0024
    void* File;                         // +0x0028  Win32 HANDLE, empty value INVALID_HANDLE_VALUE
    bool Playing;                       // +0x002C
    bool unknown_2D;                    // +0x002D
    char _pad02E[2];
    unsigned int LastFrame;             // +0x0030

    bool FrameReady() const { return BinkWait(Bink) == 0; }

    // FUNCTION: GAMEMD 0x432700
    ~MSBinkPlayer();
    // FUNCTION: GAMEMD 0x432A60
    void FUN_00432A60();
    // FUNCTION: GAMEMD 0x432C70
    void FUN_00432C70();
    // FUNCTION: GAMEMD 0x432E40 (decl; reloc)
    bool FUN_00432E40(Surface* surface, int x, int y);
    // FUNCTION: GAMEMD 0x433060
    void FUN_00433060();
    // FUNCTION: GAMEMD 0x433180 (BinkCopyToBuffer into a surface, then restore the border)
    void FUN_00433180(Surface* surface, int x, int y);
    // FUNCTION: GAMEMD 0x4331F0
    void FUN_004331F0(Surface* surface, int x, int y, bool flag);

    // FUNCTION: GAMEMD 0x433270
    void FUN_00433270(Surface* surface);
    // FUNCTION: GAMEMD 0x433330
    void FUN_00433330(Surface* surface);
    // FUNCTION: GAMEMD 0x4333F0
    void FUN_004333F0();
};
GG_STATIC_ASSERT(offsetof(MSBinkPlayer, Bink) == 0x04);
GG_STATIC_ASSERT(offsetof(MSBinkPlayer, Helper) == 0x20);
GG_STATIC_ASSERT(offsetof(MSBinkPlayer, Area) == 0x10);
GG_STATIC_ASSERT(offsetof(MSBinkPlayer, Playing) == 0x2C);
GG_STATIC_ASSERT(offsetof(MSBinkPlayer, LastFrame) == 0x30);
GG_STATIC_ASSERT(offsetof(BinkHelper_00433270, Buffer) == 0x10);
GG_STATIC_ASSERT(offsetof(BinkHelper_00433270, ClearRect) == 0x24);
GG_STATIC_ASSERT(offsetof(MSBinkPlayer, File) == 0x28);

// FUNCTION: GAMEMD 0x4331F0
#endif  // GG_MATCH_PLATFORM_BINK_PLAYER_TEARDOWN_METHODS_H
