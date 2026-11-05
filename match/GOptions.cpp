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
#include "_layout/ini_class.h"

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


// FUNCTION: GAMEMD 0x4F2140
// Build the screen engine, the two default names and an empty item list.
GraphicMenu::GraphicMenu()
    : Engine(), Background("Title.PCX"), Name("Intro"), unknown_54(0), Items(0, 0)
{
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
