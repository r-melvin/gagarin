// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI TD0x8174B0/COL0x802510 names .?AVINIClass@@, table0x7EA5F4.
// Destructor0x5256F0 confirms list+C/index+28. Entry0x5CEEF0 initializes
// the local through +3C; the adjacent live CCFile begins exactly +40 after it.
// Fields at +4/+8/+3C keep unknown names: writes alone do not establish semantics.
#ifndef GG_MATCH_LAYOUT_INI_CLASS_H
#define GG_MATCH_LAYOUT_INI_CLASS_H
#include "generic_list.h"
#include "index_class_layout.h"
// VTABLE: GAMEMD 0x7EA5F4 -- INIClass, one deleting slot.
class INIClass
{
public:
    // Retail TypeDescriptors name these nested structs.
    struct INIEntry;
    struct INISection;
    // FUNCTION: GAMEMD 0x5256F0
    virtual ~INIClass();
    // FUNCTION: GAMEMD 0x5257C0
    bool Clear(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526810
    INISection* GetSection(const char* section);
    // FUNCTION: GAMEMD 0x526960
    int GetKeyCount(const char* section);
    // FUNCTION: GAMEMD 0x526B00
    void Reset();
    // FUNCTION: GAMEMD 0x526B10
    INIEntry* GetEntry(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526CC0
    const char* GetKeyName(const char* section, int index);
    // FUNCTION: GAMEMD 0x5275C0
    bool WriteInteger(const char* section, const char* key, int value, int format);
    // FUNCTION: GAMEMD 0x528660
    bool WriteString(const char* section, const char* key, const char* value);
    // FUNCTION: GAMEMD 0x529560
    bool WriteBool(const char* section, const char* key, bool value);
    // FUNCTION: GAMEMD 0x5297E0
    bool Write2Integers(const char* section, const char* key, int* values);
    // FUNCTION: GAMEMD 0x52AA90
    static void __fastcall Strip_Comments(char* buffer);
    // FUNCTION: GAMEMD 0x52AAC0
    static bool __fastcall Line_Contains_Section(char* buffer);
    void* unknown_04;
    void* unknown_08;
    // RTTI table 0x7E1AFC; explicit inherited vptr view is retained.
    List<INISection*> Sections;
    IndexClassRaw SectionIndex;
    unsigned int unknown_3C;
};
GG_STATIC_ASSERT(offsetof(INIClass, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(INIClass, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(INIClass, Sections) == 0xC);
GG_STATIC_ASSERT(offsetof(INIClass, SectionIndex) == 0x28);
GG_STATIC_ASSERT(offsetof(INIClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(List<INIClass::INISection*>) == 0x1C);
GG_STATIC_ASSERT(sizeof(INIClass) == 0x40);
#endif
