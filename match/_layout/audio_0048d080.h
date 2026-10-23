// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing receiver view at 0xAC4F58, shared by 0x48D080 and 0x684370.
// Identity and complete extent remain unconfirmed; no fields are read here.
#ifndef GG_MATCH_LAYOUT_AUDIO_0048D080_H
#define GG_MATCH_LAYOUT_AUDIO_0048D080_H
#include <stddef.h>
class LoadProgressMgr;

struct Audio_0048D080
{
    char opaque[4];
    void FUN_00642A60(double progress, int players, int flags); // FUNCTION: GAMEMD 0x642A60 (decl; 0x684706)
    void FUN_00642AD0(); // FUNCTION: GAMEMD 0x642AD0 (decl; 0x684BE5)
    void FUN_00642B10(int side); // FUNCTION: GAMEMD 0x642B10 (decl; 0x6847C9)
    void FUN_00642C20(const char* filename, int flags, int resource); // FUNCTION: GAMEMD 0x642C20 (decl; 0x684800)
    void FUN_00642C80(int x, int y, const wchar_t* caption, bool a, bool b); // FUNCTION: GAMEMD 0x642C80 (decl; 0x68482F)
    void FUN_00642DF0(int value); // FUNCTION: GAMEMD 0x642DF0 (decl; 0x684841)
    void FUN_00643E80(LoadProgressMgr* manager); // FUNCTION: GAMEMD 0x643E80 (decl; 0x68476B)
    double FUN_006433D0(); // FUNCTION: GAMEMD 0x6433D0 (decl; ST0 at 0x6843E0)
    double FUN_00643E90(int index); // FUNCTION: GAMEMD 0x643E90 (decl; 0x68454B)
    void FUN_00643C50(int flag, double value, int a3, int a4); // FUNCTION: GAMEMD 0x643C50 (decl)
};
// GLOBAL: GAMEMD 0xAC4F58
extern Audio_0048D080 DAT_00AC4F58;
#endif
