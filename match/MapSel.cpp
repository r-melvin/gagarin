// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit MapSel.CPP. The name is the source-file string at 0x82c11c
//   in retail gamemd.exe v1.001, passed by the assert at 0x5add9a inside this object's
//   code range (0x5adb20-0x5ae8ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   cross-checked against YRpp.
//

#include "_layout/matrix3d.h"

#include "trivial_tu131_methods.h"
#include "scenario_class.h"
#include "_layout/map_select.h"
#include "_layout/dialog_005d3490.h"
#include "_layout/house_type_class.h"
#include "_layout/side_class.h"
#include "_layout/theme_class.h"
#include "msanim_family_methods.h"
#include "mouse_ww_mouse_class.h"

#include <stddef.h>
#include "_rt/gg_static_assert.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/ms_engine.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EDB38
extern const double DAT_007EDB38;
// GLOBAL: GAMEMD 0xABED78
extern double DAT_00ABED78;
// GLOBAL: GAMEMD 0xABEDB0
extern double DAT_00ABEDB0;
// GLOBAL: GAMEMD 0xABEDB8
extern int DAT_00ABEDB8;
// GLOBAL: GAMEMD 0xABEDBC
extern int DAT_00ABEDBC;
// GLOBAL: GAMEMD 0xABEDC0
extern int DAT_00ABEDC0;
// GLOBAL: GAMEMD 0xABEDC8
extern double DAT_00ABEDC8;



#include "_layout/matrix3d.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// GLOBAL: GAMEMD 0xA83C98 -- the house-type registry.
extern DynamicVectorClass<HouseTypeClass*> DAT_00A83C98;
// GLOBAL: GAMEMD 0x8B4120 -- the side registry.
extern DynamicVectorClass<SideClass*> DAT_008B4120;
// GLOBAL: GAMEMD 0xA83D10 -- the theme (music) player.
extern ThemeClass DAT_00A83D10;
// GLOBAL: GAMEMD 0xABCE08
extern bool DAT_00ABCE08;
// GLOBAL: GAMEMD 0x88730C -- the primary drawing surface.
extern MouseSurfaceView* DAT_0088730C;
// STRING: GAMEMD 0x889F64 -- the shared empty default string.
extern const char STR_00889F64[];

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- the debug log sink (a bare RET in retail).
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- localised string lookup.
const wchar_t* __fastcall FUN_00734E60(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x5CD850 (decl; reloc)
int __fastcall FUN_005CD850(Obj_007B66D0* text, MSFont* font, int width);

// FUNCTION: GAMEMD 0x5ADD10
char* __fastcall FUN_005ADD10(ScenarioClass* scenario)
{
    bool failed;
    {
        MapSelect select;
        failed = !select.FUN_005AE100(scenario);
    }
    if (failed) {
        Dialog_005D3490 dialog;
        dialog.FUN_005D3490(FUN_00734E60("MSG:UnableMapSelect", 0, "D:\\ra2mdpost\\MapSel.CPP", 0x86),
                            FUN_00734E60("TXT_OK", 0, "D:\\ra2mdpost\\MapSel.CPP", 0x86), 0, 0, 0);
        return 0;
    }
    FUN_004068E0("MapSelect: Scenario - %s, Stage - %ld\n", scenario->unknown_125C, scenario->unknown_35A0);
    return strlen(scenario->unknown_125C) ? scenario->unknown_125C : 0;
}

// FUNCTION: GAMEMD 0x5ADE20
const char* __fastcall FUN_005ADE20(ScenarioClass* scenario, const char* filename)
{
    bool failed;
    {
        Wstring name(filename);
        MapSelect select;
        failed = !select.FUN_005ADF20(scenario, &name);
    }
    if (failed) {
        Dialog_005D3490 dialog;
        dialog.FUN_005D3490(FUN_00734E60("MSG:UnableMapSelect", 0, "D:\\ra2mdpost\\MapSel.CPP", 0x98),
                            FUN_00734E60("TXT_OK", 0, "D:\\ra2mdpost\\MapSel.CPP", 0x98), 0, 0, 0);
        return 0;
    }
    return filename;
}

// FUNCTION: GAMEMD 0x5ADF20
bool MapSelect::FUN_005ADF20(ScenarioClass* scenario, Wstring* name)
{
    if (scenario == 0 || name->FUN_007B4710(0))
        return false;
    SideClass* side = DAT_008B4120.Items[DAT_00A83C98.Items[scenario->unknown_1C74]->SideIndex];
    if (side == 0) {
        FUN_004068E0("MapSelect: Invalid side!\n");
        return false;
    }
    FUN_004068E0("MapSelect: Side %s\n", side->ID.Data);
    bool failed;
    {
        Wstring sideName(side->ID);
        failed = !Stages.FUN_005CEEF0(&sideName);
    }
    if (failed) {
        Stages.ClearAll();
        FUN_004068E0("MapSelect: Unable to initialize choices!\n");
        return false;
    }
    MapStage* stage = Stages.GetAt(scenario->unknown_35A0);
    if (stage == 0) {
        Stages.ClearAll();
        FUN_004068E0("MapSelect: Invalid stage!\n");
        return false;
    }
    scenario->FUN_00686700(STR_00889F64);
    for (int i = 0; i < stage->unknown_54.Count; i++) {
        MapSelection* selection = stage->unknown_54.Items[i];
        if (selection != 0) {
            MapStage* found = Stages.FindByName(&selection->Name);
            Wstring title(found->Title);
            title.FUN_007B5B30();
            Wstring wanted(*name);
            wanted.FUN_007B5B30();
            if (found != 0 && title == wanted) {
                scenario->FUN_00686700(found->Title.FUN_007B5440());
                scenario->unknown_35A0 = Stages.FUN_005CF830(found);
                break;
            }
        }
    }
    Stages.ClearAll();
    return strlen(scenario->unknown_125C) > 0;
}

// FUNCTION: GAMEMD 0x5AE100
bool MapSelect::FUN_005AE100(ScenarioClass* scenario)
{
    if (!FUN_005AE220(scenario))
        return false;
    DAT_00ABCE08 = false;
    MapStage* stage;
    {
        Wstring title(scenario->unknown_125C);
        stage = Stages.FindByTitle(&title);
    }
    FUN_004068E0("MapSelect: Stage: %s\n", stage->Name.unknown_00);
    if (stage->unknown_08.FUN_007B47F0(0)) {
        DAT_00A83D10.PlaySong(DAT_00A83D10.FindIndex("LOADING"));
        const char* selected = stage->unknown_54.Items[0]->Name.FUN_007B5440();
        if (selected != 0) {
            FUN_004068E0("Selected %s\n", selected);
            MapStage* chosen;
            {
                Wstring key(selected);
                chosen = Stages.FindByName(&key);
            }
            Wstring title(chosen->Title);
            if (title.Length() != 0) {
                scenario->FUN_00686700(title.FUN_007B5400());
                scenario->unknown_35A0 = Stages.FUN_005CF830(chosen);
            }
        }
    }
    FUN_005AE460();
    return true;
}

// FUNCTION: GAMEMD 0x5AE220
bool MapSelect::FUN_005AE220(ScenarioClass* scenario)
{
    unknown_AC = 0;
    unknown_B0 = 0;
    Font = 0;
    if (scenario == 0) {
        FUN_004068E0("MapSelect: Invalid Scenario pointer!\n");
        return false;
    }
    SideClass* side = DAT_008B4120.Items[DAT_00A83C98.Items[scenario->unknown_1C74]->SideIndex];
    if (side == 0) {
        FUN_004068E0("MapSelect: Invalid side!\n");
        return false;
    }
    FUN_004068E0("MapSelect: Side %s\n", side->ID.Data);
    bool failed;
    {
        Wstring sideName(side->ID);
        failed = !Stages.FUN_005CEEF0(&sideName);
    }
    if (failed) {
        Stages.ClearAll();
        FUN_004068E0("MapSelect: Unable to initialize choices!\n");
        return false;
    }
    MapStage* stage;
    {
        Wstring title(scenario->unknown_125C);
        stage = Stages.FindByTitle(&title);
    }
    if (stage == 0) {
        FUN_004068E0("MapSelect: Invalid stage!\n");
        FUN_005AE460();
        return false;
    }
    Font = new MSFont(1);
    if (Font == 0) {
        FUN_004068E0("MapSelect: Unable to create font!\n");
        FUN_005AE460();
        return false;
    }
    unknown_48 = (DAT_0088730C->GetWidth() - 640) / 2;
    unknown_4C = (DAT_0088730C->GetHeight() - 400) / 2;
    Bounds = Stages.Bounds;
    Bounds.X += unknown_48;
    Bounds.Y += unknown_4C;
    unsigned short index = 0;
    do {
        Obj_007B66D0 text(stage->unknown_10);
        FUN_005CD850(&text, Font, Bounds.Width);
        index++;
        stage = Stages.GetAt(index);
    } while (stage != 0);
    Name = (const char*)0;
    Timer = ScenarioElapsedTimer();
    unknown_D8 = -1;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE4F0
// Returns zero; pops its stack arguments.
int __stdcall FUN_005AE4F0(int a1)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE570
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE570(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE580
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE580(int a1)
{
}

// FUNCTION: GAMEMD 0x5AE590
void MSEngine::OnRedraw(MouseSurfaceView* surface)
{
}

// SYNTHETIC: GAMEMD 0x5AE5A0 -- MapSelect::`scalar deleting destructor'

// FUNCTION: GAMEMD 0x5AE5E0
Matrix3D& Matrix3D::FUN_005AE5E0(const Matrix3D& source)
{
    for (int i = 0; i < 12; i++) {
        Row[0][i] = source.Row[0][i];
    }
    return *this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE860  (__thiscall)
// Reset to the identity transform. Retail is fully unrolled: 1.0f's bit
// pattern is hoisted into EDX, 0.0f into EAX, then the 12 cells are stored in
// source order, so the flat assignment list below reproduces it exactly.
void Matrix3D::MakeIdentity()
{
    Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
    Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
    Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE890  (__thiscall)
// Combined translate, fully unrolled x87. Per row the retail add order is
// (y*col1 + z*col2) + x*col0, then += col3.
void Matrix3D::Translate(float x, float y, float z)
{
    Row[0][3] += y * Row[0][1] + z * Row[0][2] + x * Row[0][0];
    Row[1][3] += y * Row[1][1] + z * Row[1][2] + x * Row[1][0];
    Row[2][3] += y * Row[2][1] + z * Row[2][2] + x * Row[2][0];
}
