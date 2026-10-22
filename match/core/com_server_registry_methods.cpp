// Provenance: own-binary-via-Ghidra
// COM server registry maintenance under HKEY_CLASSES_ROOT for the class id
// at 0x7E9520 and type library id at 0x7E9510: 0x6BB390 writes the ProgID,
// CLSID and type-library keys, 0x6BB760 removes them. Neither takes
// arguments; both return 0 with a plain `ret`. The key writer helper
// 0x6BB2E0 is __fastcall (key ECX, subkey EDX, value pushed, `ret 4`,
// bool in AL); 0x6BB390 inlines it for its first five uses and calls it for
// the last six. API calls go through the import slots (StringFromGUID2
// 0x7E15E0, WideCharToMultiByte 0x7E124C, lstrcpyA 0x7E1140, lstrcatA
// 0x7E1160, lstrlenA 0x7E11AC, RegCreateKeyExA 0x7E1018, RegSetValueExA
// 0x7E1014, RegCloseKey 0x7E1004, RegDeleteKeyA 0x7E1020, wsprintfA 0x7E14B0,
// GetModuleFileNameA 0x7E11A8, LoadTypeLib 0x7E1360).
#include <windows.h>
#include <objbase.h>

// GLOBAL: GAMEMD 0x7E9510
extern const GUID DAT_007e9510;
// GLOBAL: GAMEMD 0x7E9520
extern const GUID DAT_007e9520;
// GLOBAL: GAMEMD 0xB732F0
extern HINSTANCE DAT_00b732f0;
// STRING: GAMEMD 0x840B34
extern const char STR_00840B34[];
// STRING: GAMEMD 0x840B4C
extern const char STR_00840B4C[];
// STRING: GAMEMD 0x840B5C
extern const char STR_00840B5C[];
// STRING: GAMEMD 0x840B80
extern const char STR_00840B80[];
// STRING: GAMEMD 0x840B98
extern const char STR_00840B98[];
// STRING: GAMEMD 0x840BB0
extern const char STR_00840BB0[];

// FUNCTION: GAMEMD 0x6BB2E0
inline bool __fastcall FUN_006BB2E0(const char* key, const char* subkey, const char* value)
{
    HKEY hkey;
    char keybuf[260];
    bool result = false;

    lstrcpyA(keybuf, key);
    if (NULL != subkey) {
        lstrcatA(keybuf, "\\");
        lstrcatA(keybuf, subkey);
    }
    if (RegCreateKeyExA(HKEY_CLASSES_ROOT, keybuf, 0, NULL, REG_OPTION_NON_VOLATILE,
                        KEY_ALL_ACCESS, NULL, &hkey, NULL) == ERROR_SUCCESS) {
        if (NULL != value) {
            if (RegSetValueExA(hkey, NULL, 0, REG_SZ, (const BYTE*)value, lstrlenA(value) + 1) == ERROR_SUCCESS) {
                result = true;
            }
        } else {
            result = true;
        }
        RegCloseKey(hkey);
    }
    return result;
}

// FUNCTION: GAMEMD 0x6BB390
int __fastcall FUN_006bb390()
{
    char module[260];
    char clsid_text[40];
    char libid_text[40];
    char clsid_key[48];
    OLECHAR wide[40];

    GetModuleFileNameA(DAT_00b732f0, module, sizeof(module));
    StringFromGUID2(DAT_007e9520, wide, 39);
    WideCharToMultiByte(CP_ACP, 0, wide, -1, clsid_text, 39, NULL, NULL);
    StringFromGUID2(DAT_007e9510, wide, 39);
    WideCharToMultiByte(CP_ACP, 0, wide, -1, libid_text, 39, NULL, NULL);
    lstrcpyA(clsid_key, "CLSID\\");
    lstrcatA(clsid_key, clsid_text);

    FUN_006BB2E0(STR_00840B5C, NULL, STR_00840B4C);
    FUN_006BB2E0(STR_00840B5C, "CLSID", clsid_text);
    FUN_006BB2E0(STR_00840B34, NULL, STR_00840B4C);
    FUN_006BB2E0(STR_00840B34, "CurVer", STR_00840B5C);
    FUN_006BB2E0(STR_00840B34, "CLSID", clsid_text);

    FUN_006BB2E0(clsid_key, NULL, STR_00840B4C);
    FUN_006BB2E0(clsid_key, "ProgID", STR_00840B5C);
    FUN_006BB2E0(clsid_key, "VersionIndependentProgID", STR_00840B34);
    FUN_006BB2E0(clsid_key, "NotInsertable", NULL);
    FUN_006BB2E0(clsid_key, "InprocServer32", module);
    FUN_006BB2E0(clsid_key, "Typelib", libid_text);

    ITypeLib* library = NULL;
    LoadTypeLib(L"RA2.TLB", &library);
    if (library != NULL) {
        library->Release();
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6BB760
int __fastcall FUN_006bb760()
{
    char clsid_key[72];
    char clsid_text[40];
    char buffer[300];
    OLECHAR clsid_wide[40];

    StringFromGUID2(DAT_007e9520, clsid_wide, 39);
    WideCharToMultiByte(CP_ACP, WC_SEPCHARS, clsid_wide, -1, clsid_text, 39, NULL, NULL);
    lstrcpyA(clsid_key, "CLSID\\");
    lstrcatA(clsid_key, clsid_text);

    RegDeleteKeyA(HKEY_CLASSES_ROOT, STR_00840BB0);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, STR_00840B98);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, STR_00840B34);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, STR_00840B80);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, STR_00840B5C);

    wsprintfA(buffer, "%s\\%s", clsid_key, "ProgID");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, buffer);
    wsprintfA(buffer, "%s\\%s", clsid_key, "VersionIndependentProgID");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, buffer);
    wsprintfA(buffer, "%s\\%s", clsid_key, "NotInsertable");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, buffer);
    wsprintfA(buffer, "%s\\%s", clsid_key, "InprocServer32");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, buffer);
    wsprintfA(buffer, "%s\\%s", clsid_key, "Typelib");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, buffer);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, clsid_key);
    return 0;
}
