// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing receiver view at 0xAC4F58, shared by 0x48D080 and 0x684370.
// Identity and complete extent remain unconfirmed; no fields are read here.
#ifndef GG_MATCH_LAYOUT_AUDIO_0048D080_H
#define GG_MATCH_LAYOUT_AUDIO_0048D080_H
struct Audio_0048D080
{
    char opaque[4];
    double FUN_006433D0(); // FUNCTION: GAMEMD 0x6433D0 (decl; ST0 at 0x6843E0)
    double FUN_00643E90(int index); // FUNCTION: GAMEMD 0x643E90 (decl; 0x68454B)
    void FUN_00643C50(int flag, double value, int a3, int a4); // FUNCTION: GAMEMD 0x643C50 (decl)
};
// GLOBAL: GAMEMD 0xAC4F58
extern Audio_0048D080 DAT_00AC4F58;
#endif
