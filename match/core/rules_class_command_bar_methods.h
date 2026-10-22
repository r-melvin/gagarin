// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and argument slots read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x674650: the multiplayer flag is the
//   byte at [ESP+0x8] and the INI object the dword at [ESP+0x20C] after the
//   0x200-byte frame (`this` in ECX is never touched; RET 8). The section
//   name is one of the two .data slots 0x7F0CEC (multiplayer) / 0x7F0CE8
//   (single player); the key and its default are the slots 0x7F0CF0 /
//   0x7F0CF4. Callees: INIClass::GetSection 0x526810, ReadString 0x528A10
//   (section, key, default, 512-byte buffer, 0x200), the CRT strtok 0x7C9CC2
//   with the "," literal at 0x817F70, ShapeButtonClass::FindIndex 0x6CFCC0
//   (__fastcall name), the __fastcall slot writer 0x6CFD20 (index, value)
//   run over 25 slots with the not-found index at 0x8427CC, and the
//   __fastcall count setter 0x6CFDB0. Names cross-checked against YRpp
//   (consult-only; every slot reconfirmed above).
#ifndef GG_MATCH_CORE_RULES_CLASS_COMMAND_BAR_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_COMMAND_BAR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C9CC2 -- CRT strtok (excluded from the match target).
extern "C" char* __cdecl strtok(char* str, const char* delim);

// Opaque INI parser; the out-of-line members are declared only, so cl emits
// reloc-normalised __thiscall CALLs.
class CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc)
    void* GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc)
    void* GetEntry(const char* pSection, const char* pKey);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) -- INIClass::ReadString.
    int   ReadString(const char* pSection, const char* pKey, const char* pDefault,
                     char* pBuffer, int size);

    // FUNCTION: GAMEMD 0x679F40 -- CCINIClass::Exists (matched out of line in
    // match/platform/ccini_class_methods.cpp). Here it is the header inline
    // VC6 expands at the section test: with the key defaulted to null the
    // entry branch folds away and the section probe survives as a
    // materialised bool (`TEST EAX,EAX; SETNZ AL; TEST AL,AL`).
    bool Exists(const char* pSection, const char* pKey = 0)
    {
        if (pKey == 0) {
            return GetSection(pSection) != 0;
        }
        return GetEntry(pSection, pKey) != 0;
    }
};

// FUNCTION: GAMEMD 0x6CFCC0 (decl; reloc) -- ShapeButtonClass::FindIndex
// (matched in match/ui/shape_button_class.cpp).
int __fastcall FUN_006CFCC0(const char* name);
// FUNCTION: GAMEMD 0x6CFD20 (decl; reloc) -- store `value` in command slot
// `index` of the table at 0xB0CB78.
void __fastcall FUN_006CFD20(int index, int value);
// FUNCTION: GAMEMD 0x6CFDB0 (decl; reloc) -- set the button count (0xB0CB54)
// and recompute the bar origin.
void __fastcall FUN_006CFDB0(int count);

// GLOBAL: GAMEMD 0x8427CC -- the not-found command index.
extern int DefaultCommandIndex;

// GLOBAL: GAMEMD 0x7F0CE8 -- pointer to the "AdvancedCommandBar" section name.
extern char* AdvancedCommandBarSection;
// GLOBAL: GAMEMD 0x7F0CEC -- pointer to the "MultiplayerAdvancedCommandBar"
// section name.
extern char* MultiplayerAdvancedCommandBarSection;
// GLOBAL: GAMEMD 0x7F0CF0 -- pointer to the "ButtonList" key name.
extern char* ButtonListKey;
// GLOBAL: GAMEMD 0x7F0CF4 -- pointer to the default button list text.
extern char* ButtonListDefault;

struct RulesClass
{
    // FUNCTION: GAMEMD 0x674650
    bool Read_AdvancedCommandBar(CCINIClass* pINI, bool multiplayer);
};

// STRING: GAMEMD 0x817F70 -- ",".

#endif  // GG_MATCH_CORE_RULES_CLASS_COMMAND_BAR_METHODS_H
