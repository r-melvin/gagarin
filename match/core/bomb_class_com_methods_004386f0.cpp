// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry ranges, stack cleanup, vtable words, RTTI and global addresses were
//   checked in the pinned gamemd.exe v1.001 with Ghidra CLI and focused REA
//   records /tmp/gagarin_rea_4386f0.json, /tmp/gagarin_rea_438b00.json and
//   /tmp/gagarin_rea_438bd0.json. The main vtable's COL at 0x7FC0F0 points to
//   TypeDescriptor 0x818C18, whose binary name is .?AVBombClass@@.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "small_misc18_methods.h"
#include "bomb_class_vtables_004386f0.h"

// A narrow object view for the four words initialized at 0x4386F0. Each word
// is overwritten by a retail instruction at this offset after the base call.
struct BombClassCtorView_004386F0
{
    void* unknown_00;
    void* unknown_04;
    void* unknown_08;
    void* unknown_0C;

    BombClassCtorView_004386F0(int arg);
};
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(BombClassCtorView_004386F0, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BombClassCtorView_004386F0, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BombClassCtorView_004386F0, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BombClassCtorView_004386F0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(sizeof(BombClassCtorView_004386F0) == 0x10);

// FUNCTION: GAMEMD 0x004386F0 — constructor-like BombClass initializer;
// ECX is the object and one stack word is forwarded to 0x4101C0 (RET 4).
BombClassCtorView_004386F0::BombClassCtorView_004386F0(int arg)
{
    ((Obj_004101C0*)this)->FUN_004101C0(arg);

    // VTABLE: GAMEMD 0x007E3D10 — RTTI identifies the BombClass main view.
    unknown_00 = (void*)0x007E3D10;
    // VTABLE: GAMEMD 0x007E3CF4 — installed at object offset 4.
    unknown_04 = (void*)0x007E3CF4;
    // VTABLE: GAMEMD 0x007E3CEC — installed at object offset 8.
    unknown_08 = (void*)0x007E3CEC;
    // VTABLE: GAMEMD 0x007E3CE4 — installed at object offset 0xC.
    unknown_0C = (void*)0x007E3CE4;
}

struct GuidWords_00438B00
{
    unsigned long unknown_00;
    unsigned long unknown_04;
    unsigned long unknown_08;
    unsigned long unknown_0C;
};
GG_STATIC_ASSERT(offsetof(GuidWords_00438B00, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(GuidWords_00438B00, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(GuidWords_00438B00, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(GuidWords_00438B00, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(sizeof(GuidWords_00438B00) == 0x10);

// GLOBAL: GAMEMD 0x007E98B0 — first dword of the 16-byte GUID copied below.
extern "C" unsigned long rclsid_007E98B0;
// GLOBAL: GAMEMD 0x007E98B4 — second dword copied to the GUID output.
extern "C" unsigned long DAT_007E98B4;
// GLOBAL: GAMEMD 0x007E98B8 — third dword copied to the GUID output.
extern "C" unsigned long DAT_007E98B8;
// GLOBAL: GAMEMD 0x007E98BC — fourth dword copied to the GUID output.
extern "C" unsigned long DAT_007E98BC;

// FUNCTION: GAMEMD 0x00410320 (decl; reloc) — three stdcall arguments,
// RET 0xC; the final argument is the clear-dirty flag.
extern "C" long __stdcall FUN_00410320(void* subject, void* stream, int clearDirty);

// FUNCTION: GAMEMD 0x00438B00 — slot 3 of the BombClass IPersistStream view;
// GetClassID uses stdcall with the interface pointer and output GUID on stack.
extern "C" long __stdcall FUN_00438B00(void* self, GuidWords_00438B00* outGuid)
{
    if (outGuid == 0) {
        return (long)0x80004003;
    }
    outGuid->unknown_00 = rclsid_007E98B0;
    outGuid->unknown_04 = DAT_007E98B4;
    outGuid->unknown_08 = DAT_007E98B8;
    outGuid->unknown_0C = DAT_007E98BC;
    return 0;
}

// FUNCTION: GAMEMD 0x00438BD0 — slot 6 of the BombClass IPersistStream view;
// stdcall forwarding wrapper to the binary-verified persistence helper.
extern "C" long __stdcall FUN_00438BD0(void* self, void* stream, int clearDirty)
{
    return FUN_00410320(self, stream, clearDirty);
}
