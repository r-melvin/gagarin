// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Small leaf bodies that repeat byte for byte at many addresses, each bound to
// its own global: release of a counted heap block, release of a counted array
// of string objects, and address-of-global accessors. Globals are named by
// retail address and typed only as far as the instructions show (a count at
// +0x00, a heap pointer at +0x08 for the two release shapes). The same shape
// at other addresses belongs to other statics; each address here is verified
// separately against retail.
//
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
//
// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);
// FUNCTION: GAMEMD 0x007B46F0 (decl; reloc) -- string object destructor (this in ECX).
extern void FUN_007B46F0(void* self);

struct CountedBlock {
    int count;          // +0x00
    int unknown_04;
    void* data;         // +0x08
    // The file-scope object's constructor zeroes the three words; its
    // destructor frees the block and clears the count.
    CountedBlock() : count(0), unknown_04(0), data(0) {}
    ~CountedBlock()
    {
        void* block = data;
        count = 0;
        gg_free(block);
    }
};
struct CountedStringArray {
    int count;          // +0x00
    int unknown_04;
    unsigned char* data; // +0x08, elements of 4 bytes
};

extern CountedBlock DAT_00AC1DE0;
extern char DAT_00B2FF78;
extern CountedBlock DAT_00B778D8;
extern CountedBlock DAT_00B73E10;
extern CountedBlock DAT_00B76AE0;
extern CountedBlock DAT_00B77900;
extern CountedBlock DAT_00B76520;
extern CountedStringArray DAT_00B777A0;
extern CountedStringArray DAT_00B73BD8;
extern CountedStringArray DAT_00B76510;
extern CountedStringArray DAT_00B73AE8;
extern CountedStringArray DAT_00B77820;
extern CountedStringArray DAT_00B73708;
extern CountedStringArray DAT_00B76188;
extern CountedStringArray DAT_00B73AA8;
extern CountedStringArray DAT_00B76980;
extern CountedStringArray DAT_00B779B0;
extern CountedStringArray DAT_00B76AD0;
extern CountedStringArray DAT_00B76970;
extern char DAT_00B77F70;
extern char DAT_00B77F78;
extern char DAT_0084E7C0;
extern char DAT_0084E7C4;


// SYNTHETIC: GAMEMD 0x006C6B40 -- initialiser of DAT_00B0BD50, registers the exit stub
// SYNTHETIC: GAMEMD 0x006C6B60 -- exit stub of DAT_00B0BD50 (destructor)
// GLOBAL: GAMEMD 0xB0BD50
CountedBlock DAT_00B0BD50;

