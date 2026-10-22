// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x5587F0 / 0x559EB0), cross-checked
//   against YRpp (reconfirmed here).
//
// LoadOptionsClass — the load/save/delete savegame dialog driver. It carries a
// COM-style vtable pointer at +0x00 (virtual dtor) followed by the dialog Mode,
// the file Extension, and the Save Description. The matched methods touch only
// Mode (+0x04) and Description (+0x0C); the rest is P2.
#ifndef GG_MATCH_UI_LOAD_OPTIONS_CLASS_H
#define GG_MATCH_UI_LOAD_OPTIONS_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LoadOptionsMode (YRpp, reconfirmed from the disasm:
// LoadDialog stores 1 into Mode@+4, SaveDialog stores 2, DeleteDialog stores 3).
enum LoadOptionsMode
{
    LOM_None   = 0,
    LOM_Load   = 1,
    LOM_Save   = 2,
    LOM_Delete = 3
};

// VTABLE: GAMEMD 0x7ED2E4 (RTTI .?AVLoadOptionsClass@@, no base; 9 slots). The
// slot bodies never touch `this`; each takes its arguments from the first stack
// slots (RET 4 / RET 8), i.e. __thiscall with an unused ECX. DeleteMission
// (0x559EB0) is slot 3: the same body as the former static __stdcall view.
struct LoadOptionsClass
{
    virtual ~LoadOptionsClass();                                           // slot 0, 0x55A0D0 (scalar deleting)
    virtual bool Slot1(const char* fileName);                              // slot 1, 0x559D60
    virtual bool Slot2(const char* fileName, const wchar_t* description);  // slot 2, 0x559E40
    virtual bool DeleteMission(const char* pFilename);                     // slot 3, 0x559EB0
    virtual bool Slot4(void* out, void* entry);                            // slot 4, 0x559ED0
    virtual const wchar_t* Slot5();                                        // slot 5, 0x55A050
    virtual const wchar_t* Slot6();                                        // slot 6, 0x55A070
    virtual const wchar_t* Slot7();                                        // slot 7, 0x55A090
    virtual const wchar_t* Slot8();                                        // slot 8, 0x55A0B0

    bool LoadDialog();                  // GAMEMD 0x5587F0 __thiscall
    bool ProcessDialog();               // GAMEMD 0x558DD0 (worker, declared)

    LoadOptionsMode Mode;              // +0x04
    const char*    Extension;          // +0x08
    const wchar_t* Description;        // +0x0C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Mode) == 0x04);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Description) == 0x0C);
#endif

#endif  // GG_MATCH_UI_LOAD_OPTIONS_CLASS_H
