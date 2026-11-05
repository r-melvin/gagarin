// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit GOptions.CPP. The name is the source-file string at 0x8240bc
//   in retail gamemd.exe v1.001, passed by the assert at 0x4f1277 inside this object's
//   code range (0x4f0ef0-0x4f363f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
#include "deleting_dtor_sweep.h"
#include "mathtbl_init_shapes.h"
#include "winsock_interface_class.h"
#include "_layout/pipe.h"
#include "_layout/straw.h"
#include <math.h>
#include "header_init_shapes.h"


#include "trivial_tu092_methods.h"
#include "_layout/elapsed_timer.h"
#include "event_queue.h"
#include "menus_graphic_menu.h"
#include "_layout/graphic_menu.h"
#include "_layout/load_options_class.h"
#include "_layout/session_class.h"
#include "scenario_session_globals.h"
#include "game_options_class_methods.h"
#include "dialog_enable_methods.h"
#include "ccfile_class.h"
#include "menus_load_options.h"
#include "ui_updated_methods.h"
#include "vector_cursor.h"
#include "house_class_can_ally_methods.h"
#include "_layout/ini_class.h"
#include "_layout/generic_list_ctor_first_inline.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7EA5E0
extern const double DAT_007EA5E0;
// GLOBAL: GAMEMD 0xA8EE00
extern double DAT_00A8EE00;


// Retail PAVGraphicMenuItem RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "vector_class_operations.h"

class GraphicMenuItem;

// VTABLE: GAMEMD 0x7EA624 -- VectorClass<GraphicMenuItem*>.
template class VectorClass<GraphicMenuItem*>;
typedef VectorClass<GraphicMenuItem*> GgGraphicMenuItemVectorClass;
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA604 -- DynamicVectorClass<GraphicMenuItem*>.
template class DynamicVectorClass<GraphicMenuItem*>;
typedef DynamicVectorClass<GraphicMenuItem*> GgGraphicMenuItemDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(GraphicMenuItem*) == 4);

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7EA5E8 -- degrees to radians
const double DAT_007EA5E8 = 0.017453292519943295;
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4F0EF0
// GLOBAL: GAMEMD 0xA8EE00
double DAT_00A8EE00 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);

// SYNTHETIC: GAMEMD 0x004F0F20
// dynamic initializer for DAT_00A8EE70
// GLOBAL: GAMEMD 0x00A8EE70
double DAT_00A8EE70 = DAT_00A8EE00 / DAT_007EA5E0;

// SYNTHETIC: GAMEMD 0x004F0F40
// dynamic initializer for DAT_00A8EE58
// GLOBAL: GAMEMD 0x00A8EE58
double DAT_00A8EE58 = 1.0 / DAT_00A8EE70;

GG_STATIC_ASSERT(sizeof(DAT_00A8EE70) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00A8EE58) == 8);

// SYNTHETIC: GAMEMD 0x4F0F60
// GLOBAL: GAMEMD 0xA8EE50
double DAT_00A8EE50 = DAT_007EA5E8 * 45.0;

// SYNTHETIC: GAMEMD 0x4F0F80
// GLOBAL: GAMEMD 0xA8EE08
double DAT_00A8EE08 = DAT_007EA5E8 * 60.0;

// SYNTHETIC: GAMEMD 0x4F0FA0
// GLOBAL: GAMEMD 0xA8EDE0
double DAT_00A8EDE0 = DAT_007EA5E8 * 90.0;

// SYNTHETIC: GAMEMD 0x4F0FC0
// GLOBAL: GAMEMD 0xA8EE78
int DAT_00A8EE78 = (int)(FUN_004CAD50(DAT_00A8EDE0 - DAT_00A8EE08) * DAT_00A8EE00 * 0.5);

// SYNTHETIC: GAMEMD 0x4F1000
// GLOBAL: GAMEMD 0xA8EE10
double DAT_00A8EE10 = FUN_004CADE0(DAT_00A8EE78 * 0.00390625);

// SYNTHETIC: GAMEMD 0x4F1030
// GLOBAL: GAMEMD 0xA8EE28
double DAT_00A8EE28 = FUN_004CADE0((DAT_00A8EE78 * 2) / DAT_00A8EE00);

// SYNTHETIC: GAMEMD 0x4F1060
// GLOBAL: GAMEMD 0xA8EE6C
int DAT_00A8EE6C = (int)(DAT_00A8EE78 * 4 + 0.5);

// SYNTHETIC: GAMEMD 0x4F1090
// GLOBAL: GAMEMD 0xA8EDFC
HeaderCellInit DAT_00A8EDFC(0, 0);

// SYNTHETIC: GAMEMD 0x4F10A0
// GLOBAL: GAMEMD 0xA8EE18
HeaderCoordInit DAT_00A8EE18(0, 0, 0);

// SYNTHETIC: GAMEMD 0x004F10C0
// GLOBAL: GAMEMD 0x00A8EE60
MathTblCoord DAT_00A8EE60;

// FUNCTION: GAMEMD 0x4F1700
// Empty function: the exit-time destructor of the timer at 0xA8EE40.
void __cdecl FUN_004F1700()
{
}

// FUNCTION: GAMEMD 0x4F1710
// Empty function.
void __cdecl FUN_004F1710()
{
}

// USER32 SendMessageA (IAT 0x7E14A4).
extern "C" __declspec(dllimport) long __stdcall SendMessageA(HWND_ hWnd, unsigned uMsg, unsigned wParam, long lParam);

// GLOBAL: GAMEMD 0xA8DB9C
extern int DAT_00A8DB9C;
// GLOBAL: GAMEMD 0xA8EB60
extern GameOptionsClass DAT_00A8EB60;

// FUNCTION: GAMEMD 0x4F1720
// Refresh the dialog controls from the session state: the load-game controls in
// a campaign or mode-5 session, the two slider controls in a mode-4 session.
void FUN_004F1720(HWND_ dlg)
{
    int mode = Session_00A8B238.GameMode;
    if (mode == 0 || mode == 5) {
        bool found = LoadOptionsClass().FUN_00559C20();
        HWND_ item = GetDlgItem(dlg, 0x51E);
        if (item != 0) {
            EnableWindow(item, found);
        }
        item = GetDlgItem(dlg, 0x520);
        if (item != 0) {
            EnableWindow(item, found);
        }
    } else if (mode == 4 && DAT_00A8B538 == 0) {
        HWND_ item = GetDlgItem(dlg, 0x3EF);
        if (item != 0) {
            int pos = 3 - DAT_00A8DB9C;
            SendMessageA(item, 0x406, 1, 0x30000);
            SendMessageA(item, 0x405, 1, pos);
        }
        item = GetDlgItem(dlg, 0x529);
        if (item != 0) {
            SendMessageA(item, 0x406, 1, 0x60000);
            SendMessageA(item, 0x405, 1, 6 - DAT_00A8EB60.GameSpeed);
        }
    }
}

static const char GOptionsFile[] = "D:\\ra2mdpost\\GOptions.CPP";

// USER32 imports used by the dialog code below.
extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(HWND_ hWnd, int nIndex);
extern "C" __declspec(dllimport) long __stdcall SetWindowLongA(HWND_ hWnd, int nIndex, long value);
extern "C" __declspec(dllimport) int __stdcall ShowWindow(HWND_ hWnd, int cmdShow);

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int FUN_00622B50(HWND_ window, unsigned message, unsigned wParam, long lParam);
// FUNCTION: GAMEMD 0x622650 (decl; reloc) -- UI::BeginDialog.
void* UI_BeginDialog(unsigned short id, int (__stdcall* proc)(void*, unsigned, unsigned, long), int param);
// FUNCTION: GAMEMD 0x603E40 (decl; reloc) -- __fastcall(control, value).
void FUN_00603E40(HWND_ control, int value);

// GLOBAL: GAMEMD 0xA8EE7C -- the result of the dialog's left button.
int DAT_00A8EE7C;
// GLOBAL: GAMEMD 0xA8EE80 -- the result of the dialog's second button.
int DAT_00A8EE80;
// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern HouseClass* DAT_00A83D4C;

int __stdcall FUN_004F18B0(void* window, unsigned message, unsigned wParam, long lParam);

// FUNCTION: GAMEMD 0x4F1840
// Run the in-game leave dialog (resource 0xB6) until its procedure stores a
// result or the UI loop reports an update; returns the result.
int FUN_004F1840()
{
    int result = 0;
    HWND_ window = (HWND_)UI_BeginDialog(0xB6, FUN_004F18B0, 0);
    if (window != 0) {
        SetWindowLongA(window, 8, (long)&result);
        MenusFocusOnWindow(window);
        while (result == 0) {
            if (UI::Updated() == 1) {
                result = 1;
            }
        }
        MenusEndDialog(window);
    }
    return result;
}

// FUNCTION: GAMEMD 0x4F18B0
// Dialog procedure of the leave dialog: on init, label the two buttons (leave,
// plus restart, observe or nothing depending on the session); on a click, store
// the chosen result through the window's user data.
int __stdcall FUN_004F18B0(void* hwnd, unsigned message, unsigned wParam, long lParam)
{
    HWND_ window = (HWND_)hwnd;
    int result = FUN_00622B50(window, message, wParam, lParam);
    if (result == 0) {
        switch (message) {
        case 0x111: {
            unsigned short notify = (unsigned short)(wParam >> 16);
            int* data = (int*)GetWindowLongA(window, 8);
            int id = wParam & 0xFFFF;
            if (notify == 0) {
                switch (id) {
                case 1:
                case 0x686:
                    *data = 1;
                    break;
                case 0x6C9:
                    *data = DAT_00A8EE7C;
                    break;
                case 0x712:
                    *data = DAT_00A8EE80;
                    break;
                }
            }
            break;
        }
        case 0x497: {
            HWND_ leave = GetDlgItem(window, 0x6C9);
            SendMessageA(leave, 0x4B2, 0, (long)MenusGetText("GUI:Leave", 0, GOptionsFile, 0x223));
            DAT_00A8EE7C = 2;
            HWND_ second = GetDlgItem(window, 0x712);
            DAT_00A8EE80 = 0;
            int mode = Session_00A8B238.GameMode;
            if (mode == 0) {
                SendMessageA(second, 0x4B2, 0, (long)MenusGetText("GUI:Restart", 0, GOptionsFile, 0x22E));
                DAT_00A8EE80 = 5;
            } else if (mode == 5) {
                ShowWindow(second, 0);
            } else if (mode == 3 || mode == 4) {
                int humans = 0;
                for (int i = 0; i < DAT_00A80238; i++) {
                    HouseClass* house = DAT_00A8022C[i];
                    if (house->IsHumanPlayer && !house->Defeated) {
                        humans++;
                    }
                }
                if (humans >= 2 && !DAT_00A83D4C->Defeated) {
                    DAT_00A8EE7C = 3;
                    SendMessageA(second, 0x4B2, 0, (long)MenusGetText("GUI:Observe", 0, GOptionsFile, 0x24A));
                    DAT_00A8EE80 = 4;
                } else {
                    ShowWindow(second, 0);
                }
            }
            FUN_00603E40(leave, DAT_00A8EE7C);
            FUN_00603E40(second, DAT_00A8EE80);
            break;
        }
        }
        result = 0;
    }
    return result;
}

// WinMM import: GAMEMD 0x007E1530 (timeGetTime).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

// FUNCTION: GAMEMD 0x4F1AA0
// Append `*item` at the head slot, stamp it with the wall-clock time, and
// advance the head (modulo 128). Returns 0 when the queue already holds 128.
template<>
int EventQueue<128>::FUN_004F1AA0(const EventQueueItem* item)
{
    if (Count < 128) {
        List[Head] = *item;
        Time[Head] = timeGetTime();
        Head = (Head + 1) & 0x7F;
        Count++;
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4F1B00
// Out-of-line copy of the duration constructor: stamp the start tick and
// store the duration.
ScenarioElapsedTimer* ScenarioElapsedTimer::FUN_004F1B00(int ticks)
{
    unknown_00 = unknown_04.GetTime();
    unknown_08 = ticks;
    return this;
}


// FUNCTION: GAMEMD 0x4F1B20
// Ticks remaining: the stored duration, less the time elapsed since the start
// tick unless the timer is paused (start tick -1).
int ScenarioElapsedTimer::FUN_004F1B20()
{
    int left = unknown_08;
    if (unknown_00 != -1) {
        int elapsed = unknown_04.GetTime();
        elapsed -= unknown_00;
        if (elapsed < left) {
            return left - elapsed;
        }
        return 0;
    }
    return left;
}


// FUNCTION: GAMEMD 0x4F1CA0 (decl; reloc) -- __fastcall(ini, name).
int __fastcall FUN_004F1CA0(INIClass* ini, const char* name);

// FUNCTION: GAMEMD 0x4F1B80
// Open the named file, read it as an INI and hand it to the 0x4F1CA0 reader.
int __fastcall FUN_004F1B80(const Wstring& file_name, const char* key)
{
    CCFileClass file(file_name);
    if (!file.Exists(0)) {
        return 0;
    }
    INIClass ini((INIClass::SectionIndexClass::InlineIndex()));
    int result;
    if (ini.FUN_00525A10(&file, 0) > 0) {
        result = FUN_004F1CA0(&ini, key);
    } else {
        result = 0;
    }
    return result;
}

// FUNCTION: GAMEMD 0x4F2140
// Build the screen engine, the two default names and an empty item list.
GraphicMenu::GraphicMenu()
    : Engine(), Background("Title.PCX"), Name("Intro"), unknown_54(0), Items(0, 0)
{
}

// GLOBAL: GAMEMD 0x887308 / 0x88730C / 0x887310 -- the screen surfaces cleared by the destructor.
extern Surface* DAT_00887308;
extern Surface* DAT_0088730C;
extern Surface* DAT_00887310;

// FUNCTION: GAMEMD 0x4F21A0
// Delete every item, clear the two work surfaces and copy the second onto the
// first; the members are then torn down in reverse order.
GraphicMenu::~GraphicMenu()
{
    typedef VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*> > ItemCursor;
    for (ItemCursor it(&Items, 0); it; ++it) {
        delete it.unknown_04->Items[it.unknown_08];
    }
    DAT_00887310->Fill(0);
    DAT_0088730C->Fill(0);
    DAT_00887308->CopyFromWhole(DAT_0088730C, false, true);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4F2850
// DynamicVectorClass<GraphicMenuItem*>::Clear

// FUNCTION: GAMEMD 0x4F2880
// DynamicVectorClass<GraphicMenuItem*>::Slot5

// FUNCTION: GAMEMD 0x4F28A0
// VectorClass<GraphicMenuItem*>::Slot6

// FUNCTION: GAMEMD 0x4F28E0
// VectorClass<GraphicMenuItem*>::operator==

// FUNCTION: GAMEMD 0x4F2920
// VectorClass<GraphicMenuItem*>::SetCapacity

// FUNCTION: GAMEMD 0x4F29D0
// VectorClass<GraphicMenuItem*>::Clear

// FUNCTION: GAMEMD 0x4F2A00
// VectorClass<GraphicMenuItem*>::FindItemIndex

// FUNCTION: GAMEMD 0x4F2A40
// VectorClass<GraphicMenuItem*>::Slot5

// FUNCTION: GAMEMD 0x4F2A60
// DynamicVectorClass<GraphicMenuItem*>::SetCapacity

// FUNCTION: GAMEMD 0x4F2B10
// DynamicVectorClass<GraphicMenuItem*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F2B60
// VectorClass<GraphicMenuItem*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F2BB0
// DynamicVectorClass<GraphicMenuItem*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5CB590 (decl; reloc) -- the palette object for a file name; __fastcall, the name in ECX.
MenusFlagSink* FUN_005CB590(const Wstring& name);

// FUNCTION: GAMEMD 0x4F2F10
// Build an animation item: copy the rectangle, then, when both the shape file and
// the palette file exist, look the palette object up, make the shape animation
// and queue it on the engine.
GraphicMenuAnimItem::GraphicMenuAnimItem(int id, MSEngine* engine, const Point2D* position, const RectangleStruct* rect,
                                         const Wstring& shape, const Wstring& palette, int field24, bool field34)
    : GraphicMenuItem(id), Rect(*rect), Unknown20(0), Anim(0)
{
    CCFileClass shapeFile(shape);
    CCFileClass paletteFile(palette);
    if (shapeFile.Exists(0) && paletteFile.Exists(0)) {
        {
            Wstring paletteName(palette.FUN_007B5440());
            Anim = FUN_005CB590(paletteName);
        }
        MSShapeAnim* anim = new MSShapeAnim(shape, position->X, position->Y, (int)Anim, field24, field34, 0);
        if (anim != 0) {
            engine->AddAnim(anim);
        }
    }
}

// GLOBAL: GAMEMD 0x889F64 -- the shared empty default string.
extern char DAT_00889F64[];

// FUNCTION: GAMEMD 0x4F2C70
// Read an animation item from `section`: its id (none means no item), shape and
// palette names, origin and active rectangle (both shifted by the caller's
// offset), loop flag and rate, then build the item.
//
// PARTIAL (93.5%, 214 of 214 instructions, same multiset). The residual is the
// scheduling of the origin and active-rectangle shifts: retail stores the
// shifted X, builds the next key string, and only then adds the Y offset. Tried:
// `+=` on both members (81.8%), per-member `x = x + offset` (81.8%), the shifted
// point built through the Point2D constructor (93.5%, kept) and the rectangle
// read back through a field-wise copy of a separate fallback (50.7%).
GraphicMenuAnimItem* FUN_004F2C70(const Wstring* section, INIClass* ini, MSEngine* engine, const Point2D* offset)
{
    int id;
    {
        Wstring key("ID");
        id = ini->FUN_005278F0(*section, key, -1);
    }
    if (id == -1) {
        return 0;
    }
    Wstring shape;
    {
        Wstring fallback(DAT_00889F64);
        Wstring key("Image");
        ini->FUN_00528C00(section, &key, &fallback, &shape);
    }
    if (shape.Length() == 0) {
        return 0;
    }
    Wstring palette;
    {
        Wstring fallback(DAT_00889F64);
        Wstring key("Palette");
        ini->FUN_00528C00(section, &key, &fallback, &palette);
    }
    if (palette.Length() == 0) {
        return 0;
    }
    Point2D position(0, 0);
    {
        Wstring key("Origin");
        position = ini->FUN_00529A30(section, &key, &position);
    }
    position = Point2D(position.X + offset->X, position.Y + offset->Y);
    RectangleStruct rect = { 0, 0, 0, 0 };
    {
        Wstring key("ActiveRect");
        rect = ini->FUN_00527F20(section, &key, &rect);
    }
    rect.X = rect.X + offset->X;
    rect.Y = rect.Y + offset->Y;
    bool loop = ini->FUN_005295F0(section->FUN_007B5440(), "Loop", true);
    int rate;
    {
        Wstring key("Rate");
        rate = ini->FUN_005278F0(*section, key, 5);
    }
    return new GraphicMenuAnimItem(id, engine, &position, &rect, shape, palette, rate, loop);
}

// FUNCTION: GAMEMD 0x4F3070
// Releases the owned animation, then runs the base destructor. (The scalar deleting destructor 0x4F30E0 is
// not reproduced: cl emits ??_G only beside a constructor, and the factory 0x4F2C70 expands it inline.)
GraphicMenuAnimItem::~GraphicMenuAnimItem()
{
    delete Anim;
}

// SYNTHETIC: GAMEMD 0x4F30E0 -- GraphicMenuAnimItem::`scalar deleting destructor' (compiler-generated ??_G beside the out-of-line destructor)

// FUNCTION: GAMEMD 0x4F3090
// Hit test: true when the item is visible and the point lies inside its rectangle.
bool GraphicMenuAnimItem::Slot2(const Point2D* point)
{
    return Visible
        && point->X >= Rect.X && point->X < Rect.X + Rect.Width
        && point->Y >= Rect.Y && point->Y < Rect.Y + Rect.Height;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EA5E0
extern const double DAT_007EA5E0 = 60.0;
// END defined globals
