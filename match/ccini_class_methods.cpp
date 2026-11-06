// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (each
//   address/convention reconfirmed against the user's binary below).
//
// Translation unit: three CCINIClass/INIClass INI writers/queries, all pure
// __thiscall forwarders that touch NO member offset of `this` (confirmed: every
// referenced register is an incoming stack arg or the preserved `this` in ECX).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x529560   INIClass::WriteBool        (__thiscall)
//   FUNCTION: GAMEMD 0x5297E0   INIClass::Write2Integers   (__thiscall)
//   FUNCTION: GAMEMD 0x679F40   CCINIClass::Exists         (__thiscall)
//   FUNCTION: GAMEMD 0x528660   INIClass::WriteString      (forwarded callee)
//   FUNCTION: GAMEMD 0x526810   INIClass::GetSection       (forwarded callee)
//   FUNCTION: GAMEMD 0x526B10   INIClass::GetEntry         (forwarded callee)
//   DATA:     GAMEMD 0x825BF8   "yes"   (WriteBool true literal)
//   DATA:     GAMEMD 0x825BF4   "no"    (WriteBool false literal)
//   DATA:     GAMEMD 0x81C000   "%d,%d" (Write2Integers format)
//   LIBRARY:  GAMEMD 0x7C8EF4   sprintf (CRT; cdecl; excluded from match target)

#include "ccini_class_methods.h"
#include "ccfile_class.h"
#include <stdio.h>
#include "multiplayer_game_mode.h"
#include "mp_game_mode_class_get_methods.h"

// GLOBAL: GAMEMD 0xB053B4 -- cached checksum of CoopCampMD.ini.
int DAT_00B053B4;
// GLOBAL: GAMEMD 0xB053B8 -- set once CoopCampMD.ini has been read.
bool DAT_00B053B8;

// FUNCTION: GAMEMD 0x5D5ED0 (decl; reloc) -- the number of registered game modes.
int FUN_005D5ED0();

// GLOBAL: GAMEMD 0x887180 -- the art INI.
extern CCINIClass DAT_00887180;

// FUNCTION: GAMEMD 0x679CC0
//
// The checksum of CoopCampMD.ini, read once and cached.
int FUN_00679CC0()
{
    if (!DAT_00B053B8) {
        CCINIClass ini((INIClass::SectionIndexClass::InlineIndex()));
        CCFileClass file("CoopCampMD.ini");
        if (ini.ReadCCFile(&file, false, false)) {
            DAT_00B053B4 = ini.GetCRC();
        }
        DAT_00B053B8 = true;
    }
    return DAT_00B053B4;
}

// FUNCTION: GAMEMD 0x679D90
//
// The rules checksum plus the checksum of each game mode's INI, plus the
// cached CoopCampMD.ini checksum.
int FUN_00679D90()
{
    int sum = DAT_00887048->GetCRC();
    int count = FUN_005D5ED0();
    for (int i = 1; i <= count; i++) {
        MultiplayerGameMode* mode = MultiplayerGameMode_Get(i);
        if (mode != 0) {
            sum += mode->FUN_005D67B0()->GetCRC();
        }
    }
    return sum + FUN_00679CC0();
}

// FUNCTION: GAMEMD 0x679EE0
//
// Empty the art INI, then read ARTMD.INI into it.
void FUN_00679EE0()
{
    DAT_00887180.Clear(0, 0);
    CCFileClass file("ARTMD.INI");
    DAT_00887180.ReadCCFile(&file, false, false);
}



// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x679F40
// 0x679F40  CCINIClass::Exists
//   If pKey is null only the section is probed (GetSection != null); otherwise
//   the entry is probed (GetEntry != null). The nonzero-test is materialised as
//   VC6's NEG/SBB/NEG 0-or-1 boolean.
// ---------------------------------------------------------------------------
bool CCINIClass::Exists(const char* pSection, const char* pKey)
{
    if (pKey == 0) {
        return GetSection(pSection) != 0;
    }
    return GetEntry(pSection, pKey) != 0;
}

