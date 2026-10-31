// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Startup.CPP. The name is the source-file string at 0x840e0c
//   in retail gamemd.exe v1.001, passed by the assert at 0x6bc2d3 inside this object's
//   code range (0x6bb070-0x6bed7a). Functions are in ascending retail address order.
//   The range ends at the last non-template function (0x6bed50-0x6bed7a). The COMDAT
//   blocks that follow (0x6bed80-0x6c6450: the class-factory instantiations and the
//   VectorClass<unsigned long> pieces) are in ClassFactoryInst.cpp; the 0x6c663f end
//   used earlier was an upper bound taken from the next object, not an attested edge.
//
// This file holds the part of the object that is not template machinery: the math-table
// initialisers, the COM server registry maintenance and YRDDraw::DisposeOfStuff. The persistence
// class-factory instantiations that follow in the retail address range are in ClassFactoryInst.cpp.
//
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

#include "mathtbl_init_shapes.h"
#include "../_layout/tube_class.h"
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

#include "../renderer/yrddraw_dispose_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F3700
extern const double DAT_007F3700;
// GLOBAL: GAMEMD 0xB0BC70
extern double DAT_00B0BC70;

// SYNTHETIC: GAMEMD 0x006BB0A0
// GLOBAL: GAMEMD 0x00B0BCD8
double DAT_00B0BCD8 = DAT_00B0BC70 / DAT_007F3700;

// SYNTHETIC: GAMEMD 0x006BB0C0
// GLOBAL: GAMEMD 0x00B0BCC0
double DAT_00B0BCC0 = DAT_007E1718 / DAT_00B0BCD8;

// SYNTHETIC: GAMEMD 0x006BB240
// GLOBAL: GAMEMD 0x00B0BCC8
MathTblCoord DAT_00B0BCC8;

// FUNCTION: GAMEMD 0x6BB2E0
inline bool FUN_006BB2E0(const char* key, const char* subkey, const char* value)
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
int FUN_006bb390()
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
int FUN_006bb760()
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

// FUNCTION: GAMEMD 0x6BB8E0
//
// Shutdown of the DirectDraw layer. The sidebar/tab surfaces go first if they
// were ever built, then -- once only, guarded by the 0xB0BCF5 flag -- the six
// global surfaces are deleted and nulled and the display is restored.
void YRDDraw::DisposeOfStuff()
{
    if (DAT_008A0DEF != 0)
        FUN_004C19B0();

    if (DAT_00B0BCF5 == 0) {
        if (DAT_0088730C != 0) {
            delete DAT_0088730C;
            DAT_0088730C = 0;
        }
        if (DAT_00887310 != 0) {
            delete DAT_00887310;
            DAT_00887310 = 0;
        }
        if (DAT_008872FC != 0) {
            delete DAT_008872FC;
            DAT_008872FC = 0;
        }
        if (DAT_00887300 != 0) {
            delete DAT_00887300;
            DAT_00887300 = 0;
        }
        if (DAT_0088731C != 0) {
            delete DAT_0088731C;
            DAT_0088731C = 0;
        }
        if (DAT_00887308 != 0) {
            delete DAT_00887308;
            DAT_00887308 = 0;
        }
        Restore();
        DAT_00B0BCF5 = 1;
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A0DEF
char DAT_008A0DEF;
// GLOBAL: GAMEMD 0xB0BC68
CellStruct DAT_00B0BC68;
// GLOBAL: GAMEMD 0xB0BCF5
char DAT_00B0BCF5;
// GLOBAL: GAMEMD 0xB732F0
HINSTANCE DAT_00b732f0;
// GLOBAL: GAMEMD 0x7F3700
extern const double DAT_007F3700 = 60.0;
// GLOBAL: GAMEMD 0x7E9510
extern const GUID DAT_007e9510 = {0xB45A4A80, 0x86DA, 0x11D1, {0xB7, 0x06, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9520
extern const GUID DAT_007e9520 = {0xB45A4A81, 0x86DA, 0x11D1, {0xB7, 0x06, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x817BC0
extern const IID DAT_00817BC0 = {0x00000000, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
// END defined globals

