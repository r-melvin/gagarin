// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x5587F0 / 0x559EB0), cross-checked
//   against YRpp LoadOptionsClass.h (consult-only; reconfirmed here).
//
// LoadOptionsClass — the load/save/delete savegame dialog driver. It carries a
// COM-style vtable pointer at +0x00 (virtual dtor) followed by the dialog Mode,
// the file Extension, and the Save Description. The matched methods touch only
// Mode (+0x04) and Description (+0x0C); the rest is P2.
#ifndef GG_MATCH_UI_LOAD_OPTIONS_CLASS_H
#define GG_MATCH_UI_LOAD_OPTIONS_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LoadOptionsMode (YRpp LoadOptionsClass.h, reconfirmed from the disasm:
// LoadDialog stores 1 into Mode@+4, SaveDialog stores 2, DeleteDialog stores 3).
enum LoadOptionsMode
{
    LOM_None   = 0,
    LOM_Load   = 1,
    LOM_Save   = 2,
    LOM_Delete = 3
};

struct LoadOptionsClass
{
    bool LoadDialog();                  // GAMEMD 0x5587F0 __thiscall
    bool ProcessDialog();               // GAMEMD 0x558DD0 (worker, declared)
    static bool __stdcall DeleteMission(const char* pFilename); // GAMEMD 0x559EB0

    void*          _vtable;             // +0x00  COM vptr (virtual dtor) — P2
    LoadOptionsMode Mode;              // +0x04
    const char*    Extension;          // +0x08
    const wchar_t* Description;        // +0x0C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Mode) == 0x04);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Description) == 0x0C);
#endif

#endif  // GG_MATCH_UI_LOAD_OPTIONS_CLASS_H
