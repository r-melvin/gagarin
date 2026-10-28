// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x6F19B0, read instruction by instruction from gamemd.exe v1.001: loads every entry of
// the [TeamTypes] section, the TeamType counterpart of ScriptTypeClass::LoadFromINIList.
#include "../core/type_find_or_allocate_family_methods.h"
#include "script_type_class.h"

// Dispatch-only view of a team type's primary vtable: LoadFromINI is slot 25 (offset 0x64).
struct ILoad_006F19B0 {
    virtual void _s00(); virtual void _s01(); virtual void _s02(); virtual void _s03();
    virtual void _s04(); virtual void _s05(); virtual void _s06(); virtual void _s07();
    virtual void _s08(); virtual void _s09(); virtual void _s10(); virtual void _s11();
    virtual void _s12(); virtual void _s13(); virtual void _s14(); virtual void _s15();
    virtual void _s16(); virtual void _s17(); virtual void _s18(); virtual void _s19();
    virtual void _s20(); virtual void _s21(); virtual void _s22(); virtual void _s23();
    virtual void _s24();
    virtual void LoadFromINI(CCINIClass* ini);
};

// FUNCTION: GAMEMD 0x6F19B0
// For every key in [TeamTypes], finds or creates the named team type, loads it and stamps +0xE8.
void __fastcall FUN_006F19B0(CCINIClass* ini, int isGlobal)
{
    char buffer[0x20];

    int count = ini->GetKeyCount("TeamTypes");
    for (int n = 0; n < count; ++n) {
        const char* key = ini->GetKeyName("TeamTypes", n);
        ini->ReadString("TeamTypes", key, "", buffer, 0x20);
        TypeClass_006F1920* item;
        if (gg_strcmpi("<none>", buffer) != 0 && gg_strcmpi("none", buffer) != 0) {
            int i = 0;
            while (i < TypeClass_006F1920_Array.Count) {
                if (gg_strcmpi(TypeClass_006F1920_Array.Items[i]->ID.Data, buffer) == 0) {
                    item = TypeClass_006F1920_Array.Items[i];
                    goto have_item;
                }
                ++i;
            }
            item = (TypeClass_006F1920*)::operator new(0xF8);
            if (item) {
                item = item->Construct(buffer);
                goto have_item;
            }
        }
        item = 0;
have_item:
        ((ILoad_006F19B0*)item)->LoadFromINI(ini);
        *(int*)((char*)item + 0xE8) = isGlobal;
    }
}

// The INI writer view used by the save routine below.
struct TeamIni_006F1AB0 {
    // FUNCTION: GAMEMD 0x526960 (decl; reloc)
    int GetKeyCount(const char* section);
    // FUNCTION: GAMEMD 0x526CC0 (decl; reloc)
    const char* GetKeyName(const char* section, int index);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc)
    int ReadString(const char* section, const char* key, const char* def, char* buffer, int size);
    // FUNCTION: GAMEMD 0x5257C0 (decl; reloc)
    bool Clear(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc)
    bool WriteString(const char* section, const char* key, const char* value);
};

// Dispatch-only view: SaveToINI is slot 26 (offset 0x68).
struct ISave_006F1AB0 {
    virtual void _s00(); virtual void _s01(); virtual void _s02(); virtual void _s03();
    virtual void _s04(); virtual void _s05(); virtual void _s06(); virtual void _s07();
    virtual void _s08(); virtual void _s09(); virtual void _s10(); virtual void _s11();
    virtual void _s12(); virtual void _s13(); virtual void _s14(); virtual void _s15();
    virtual void _s16(); virtual void _s17(); virtual void _s18(); virtual void _s19();
    virtual void _s20(); virtual void _s21(); virtual void _s22(); virtual void _s23();
    virtual void _s24(); virtual void _s25();
    virtual void SaveToINI(TeamIni_006F1AB0* ini);
};

// LIBRARY: GAMEMD 0x7C8EF4 (decl; reloc) -- sprintf.
int __cdecl FUN_007C8EF4(char* buffer, const char* format, ...);

// FUNCTION: GAMEMD 0x6F1AB0
// Rewrites [TeamTypes]: drops the old entries, then writes every team type whose +0xE8 matches.
void __fastcall FUN_006F1AB0(TeamIni_006F1AB0* ini, int isGlobal)
{
    char buffer[0x20];

    int count = ini->GetKeyCount("TeamTypes");
    for (int n = 0; n < count; ++n) {
        const char* key = ini->GetKeyName("TeamTypes", n);
        ini->ReadString("TeamTypes", key, "", buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear("TeamTypes", 0);
    int written = 0;
    for (int i = 0; i < TypeClass_006F1920_Array.Count; ++i) {
        if (*(int*)((char*)TypeClass_006F1920_Array.Items[i] + 0xE8) == isGlobal) {
            FUN_007C8EF4(buffer, "%d", written++);
            ini->WriteString("TeamTypes", buffer, TypeClass_006F1920_Array.Items[i]->ID.Data);
            ((ISave_006F1AB0*)TypeClass_006F1920_Array.Items[i])->SaveToINI(ini);
        }
    }
}
