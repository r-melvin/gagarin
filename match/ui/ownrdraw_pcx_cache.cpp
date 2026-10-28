// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x600530 loads 0xAC4848 into ECX, calls the constructor 0x6B9450 and registers
//   the thunk at 0x600550 (`MOV ECX,0xAC4848; JMP 0x6B9530`) with atexit; both come from the one
//   global definition below, whose constructor and destructor are defined out of line elsewhere.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT

class StringHashTable_00AC4848
{
public:
    StringHashTable_00AC4848();
    ~StringHashTable_00AC4848();
};

// GLOBAL: GAMEMD 0xAC4848
// SYNTHETIC: GAMEMD 0x600550 -- exit-time destructor thunk
// SYNTHETIC: GAMEMD 0x00600530 -- initialiser of DAT_00AC4848
StringHashTable_00AC4848 DAT_00AC4848;
