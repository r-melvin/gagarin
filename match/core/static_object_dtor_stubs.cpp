// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Exit-time destructor stub of a file-scope object: it loads the object's address into
// ECX and tail-jumps to the out-of-line destructor (MOV ECX,global; JMP dtor). The
// object is declared extern: its constructor and the atexit registration live in
// the initialiser (an __xc table entry), which belongs to the translation-unit migration.
// The destructor is a function recovered only by address, so it is declared on a
// placeholder holder named after it.

struct Obj_005B1E20
{
    // FUNCTION: GAMEMD 0x005B1E20 (decl; reloc)
    void FUN_005B1E20();
};

// GLOBAL: GAMEMD 0x00884D88
extern Obj_005B1E20 DAT_00884D88;
// FUNCTION: GAMEMD 0x0040D330
void FUN_0040D330()
{
    DAT_00884D88.FUN_005B1E20();
}
