// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, vtable slots and globals read from the user's retail gamemd.exe v1.001: RTTI .?AVMouseClass@@
//   (type descriptor 0x816C90; primary vtable 0x7E1964 with 55 slots, COL 0x7FAB38; second locator 0x7FA9B8 at
//   base offset 0x5518 with the one-slot table 0x7E195C; bases MouseClass -> ScrollClass -> TabClass ->
//   SidebarClass -> PowerClass -> RadarClass -> DisplayClass -> MapClass -> GScreenClass), the scalar deleting
//   destructor 0x40D290, Save 0x5BE6D0 (`PUSH 0x556C` is the byte size written for the object) and the entries in
//   mouse_mouse_class_methods.cpp.
//
// The MouseClass members (+0x555C CursorFlag, +0x5560 CursorIndex, +0x5564 RequestedCursor, +0x5568 CursorFrame)
// are declared with the class in ui_display_chain.h.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_MOUSE_MOUSE_CLASS_H
#define GG_MATCH_UI_INPUT_CONTROLS_MOUSE_MOUSE_CLASS_H

#include <stddef.h>
#include "mouse_ww_mouse_class.h"
#include <ole2.h>
#include "../../core/game_timing_methods.h"
#include "ui_display_chain.h"

// One row of the cursor table at 0x82D028 (stride 0x1C).
struct MouseCursorEntry
{
    int StartFrame;       // +0x00
    int FrameCount;       // +0x04
    int Delay;            // +0x08  animation delay; 0 = static
    int AltStartFrame;    // +0x0C  first frame of the alternate set, -1 = none
    int AltFrameCount;    // +0x10
    int unknown_14;             // +0x14  pixel, or MouseHotCenter / MouseHotFar
    int unknown_18;             // +0x18
};
GG_STATIC_ASSERT(sizeof(MouseCursorEntry) == 0x1C);
GG_STATIC_ASSERT(offsetof(MouseCursorEntry, Delay) == 0x08);
GG_STATIC_ASSERT(offsetof(MouseCursorEntry, AltStartFrame) == 0x0C);
GG_STATIC_ASSERT(offsetof(MouseCursorEntry, unknown_14) == 0x14);

// The two sentinel hot-spot values the code compares against (0x3039 and 0xD431): half the shape extent and the
// whole extent.
enum { MouseHotCenter = 12345, MouseHotFar = 54321 };

// GLOBAL: GAMEMD 0x0082D028 - the cursor table (5 rows are initialised).
extern MouseCursorEntry MouseCursorTable[];
// GLOBAL: GAMEMD 0x00ABF294 - the loaded MOUSE.SHA shape file.
extern Obj_0069E430* DAT_00ABF294;
// GLOBAL: GAMEMD 0x00ABF2DC - the load-flag byte handed to FileSystem::LoadWholeFileEx.
extern char MouseShapeFlag;
// GLOBAL: GAMEMD 0x00ABF2DD - set once a cursor has been applied.
extern bool MouseCursorApplied;

// The cursor animation timer at 0x00ABF2A0: start tick, the clock member and the delay.
struct MouseCursorTimer
{
    GameTimerClass Timer;   // +0x00 start tick, +0x04 clock
    int Delay;              // +0x08
    MouseCursorTimer(int delay) : Delay(delay) {}
};
GG_STATIC_ASSERT(sizeof(MouseCursorTimer) == 0x0C);
// GLOBAL: GAMEMD 0x00ABF2A0
extern MouseCursorTimer MouseTimer;

// FUNCTION: GAMEMD 0x4A38D0 (decl; reloc) - FileSystem::LoadWholeFileEx, __fastcall (name in ECX, flag byte in EDX).
void* FUN_004A38D0(const char* name, char* flag);

// The MapClass containers Load rebuilds (canonical vector specializations, MapBucketTable and MapWordEntry) are
// declared in ui_display_chain.h with the class chain.

// An element the cell iteration (MapClass 0x578290) yields: an IPersistStream-fronted object whose +0x24 holds a
// packed cell.
struct MapSavedObject : public IPersistStream
{
    char unknown_04[0x24 - 4];   // +0x04
    CellStruct Cell;             // +0x24
    CellStruct GetCell() { return Cell; }
};

// The object ScenarioClass keeps at +0x1258; Save writes the pointer value, Load re-reads it and runs these methods on
// the object it names.
class MouseSceneTarget
{
public:
    // FUNCTION: GAMEMD 0x71DCA0 / 0x545150 (DL = 1) / 0x547110 / 0x546DA0 (DL = 0, CL = 0) / 0x5FE620 / 0x45E970 /
    // 0x427940 / 0x6B5490 (decl; reloc) - all __thiscall / __fastcall on the target.
    void Method_71DCA0();
    void Method_547110();
    static void Method_545150(MouseSceneTarget* self, bool arg);
    static void Method_546DA0(bool a, bool b);
    void Method_5FE620();
    void Method_45E970();
    void Method_427940();
    void Method_6B5490();
};

struct MouseScenarioView
{
    char unknown_00[0x1258];
    MouseSceneTarget* Target;   // +0x1258
};
GG_STATIC_ASSERT(offsetof(MouseScenarioView, Target) == 0x1258);
// GLOBAL: GAMEMD 0x00A8B230 - ScenarioClass::Instance.
extern MouseScenarioView* MouseScenarioInstance;
// GLOBAL: GAMEMD 0x00822CF8 - the target of the last load (-1 until the next load completes).
extern MouseSceneTarget* MouseLastTarget;
#define MOUSE_NO_TARGET ((MouseSceneTarget*)-1)

// GLOBAL: GAMEMD 0x007F7C90 - the interface id the saved owned objects are loaded as.
extern const IID MouseObjectIid;



// ---- MouseClass -----------------------------------------------------------------------------------------------
// MouseClass and its whole base chain are declared in ui_display_chain.h. Its scalar deleting destructor:
// FUNCTION: GAMEMD 0x40D290 - PARTIAL (see the mouse rows). Retail stores both vptrs, tears down the four strips
// (cameo vector destructor, then the empty out-of-line destructor 0x40D300 of the timer at strip +0x08, ECX =
// strip+8) and calls the RadarClass destructor body 0x652C00. The shared StripClass (ui_display_chain.h) gives the
// timer the implicit destructor that the SidebarClass / TabClass / ScrollClass destructors need (they do not call
// 0x40D300), so the 0x40D300 call is the remaining difference here.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MOUSE_MOUSE_CLASS_H
