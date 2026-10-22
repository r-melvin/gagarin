// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The object slot 13 of the AbstractClass family receives: each override
//   feeds its fields to it through 0x4A1CA0 (one byte, RET 4) and 0x4A1D50
//   (one dword, RET 4), both __thiscall on the passed pointer.
#ifndef GG_MATCH_LAYOUT_OBJ_004A1D30_H
#define GG_MATCH_LAYOUT_OBJ_004A1D30_H

struct Obj_004A1D30
{
    // FUNCTION: GAMEMD 0x4A1CA0 (decl; reloc) -- add one byte.
    void FUN_004A1CA0(bool value);
    // FUNCTION: GAMEMD 0x4A1D30 (decl; reloc) -- add one word.
    void FUN_004A1D30(unsigned short value);
    // FUNCTION: GAMEMD 0x4A1D50 (decl; reloc) -- add one dword.
    void FUN_004A1D50(int value);
};

#endif  // GG_MATCH_LAYOUT_OBJ_004A1D30_H
