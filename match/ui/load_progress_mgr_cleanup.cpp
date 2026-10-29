// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x554370 (0x8F bytes, plain RET).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#include "../_layout/load_progress_mgr.h"

// An object released through its virtual destructor (slot 0, flag 1).
struct Deletable_00554370
{
    virtual ~Deletable_00554370() {}
};

// FUNCTION: GAMEMD 0x72B460 (decl; reloc)
void FUN_0072B460();
// FUNCTION: GAMEMD 0x72B870 (decl; reloc)
void FUN_0072B870();

// FUNCTION: GAMEMD 0x554370
// Release the three owned buffers, shut down the screen helpers and delete
// the objects the manager holds.
void LoadProgressMgr::FUN_00554370()
{
    if (unknown_50 && unknown_44) {
        delete (char*)unknown_44;
    }
    unknown_44 = 0;
    if (unknown_51 && unknown_48) {
        delete (char*)unknown_48;
    }
    unknown_48 = 0;
    if (unknown_52 && unknown_4C) {
        delete (char*)unknown_4C;
    }
    unknown_4C = 0;
    FUN_0072B460();
    FUN_0072B870();
    if (unknown_04) {
        delete (Deletable_00554370*)unknown_04;
        unknown_04 = 0;
    }
    if (unknown_08) {
        delete (Deletable_00554370*)unknown_08;
        unknown_08 = 0;
    }
    if (unknown_60) {
        delete (Deletable_00554370*)unknown_60;
    }
    unknown_60 = 0;
}
