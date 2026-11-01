// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 0x752CA0 and 0x753500: load the object pointer at 0xB1D4D8 and, when set,
// tail-jump to a __thiscall method of it (0x407F40 / 0x407FB0). The pointee's
// class and the method names are not recovered here.

class StreamView_00B1D4D8
{
public:
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc)
    void FUN_00407F40();
    // FUNCTION: GAMEMD 0x407FB0 (decl; reloc)
    void FUN_00407FB0();
};

// GLOBAL: GAMEMD 0xB1D4D8
extern StreamView_00B1D4D8* DAT_00B1D4D8;

// FUNCTION: GAMEMD 0x752CA0
void FUN_00752CA0()
{
    if (DAT_00B1D4D8 != 0) {
        DAT_00B1D4D8->FUN_00407F40();
    }
}

// FUNCTION: GAMEMD 0x753500
void FUN_00753500()
{
    if (DAT_00B1D4D8 != 0) {
        DAT_00B1D4D8->FUN_00407FB0();
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D4D8
StreamView_00B1D4D8* DAT_00B1D4D8;
// END defined globals
