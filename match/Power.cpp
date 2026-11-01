// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Power.CPP. The name is the source-file string at 0x836db8
//   in retail gamemd.exe v1.001, passed by the assert at 0x640473 inside this object's
//   code range (0x63f4c0-0x6404ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The nine tail-jump thunks, ordered ascending by retail address.
//
//   PowerClass members (vtable 0x7EFF54) from Power.CPP's code range, bytes matched against
//   retail gamemd.exe v1.001. Layout and evidence: input_controls/ui_display_chain.h.
//
//   0x63F6B0  PowerClass::PowerClass
//   0x63F730  PowerClass::vf_07
//   0x63F7E0  PowerClass::vf_50
//   0x63F810  PowerClass::FUN_0063F810
//   0x63F8F0  PowerClass::FUN_0063F8F0
//   0x63F940  FUN_0063F940
//   0x63FDC0  PowerClass::FUN_0063FDC0
//   0x63FE30  PowerClass::FUN_0063FE30
//   0x640450  PowerClass::vf_33

#include "deleting_dtor_sweep.h"
#include "mathtbl_init_shapes.h"
#include "winsock_interface_class.h"
#include "_layout/pipe.h"
#include "_layout/straw.h"

#include "tail_jmp_thunk_sweep.h"

#include "trivial_tu181_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EFF40
extern const double DAT_007EFF40;
// GLOBAL: GAMEMD 0xAC4D18
extern double DAT_00AC4D18;

#include "FUNCTION.H"
#include "ui_display_chain.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xB0B504
extern int StripHeight_00B0B504;
// GLOBAL: GAMEMD 0xAC4E74
extern void* DAT_00AC4E74;
// GLOBAL: GAMEMD 0xAC4E78
extern bool DAT_00AC4E78;
// GLOBAL: GAMEMD 0x7E3568
extern const double DAT_007E3568;
// GLOBAL: GAMEMD 0xAC4D30
extern wchar_t DAT_00AC4D30[];

// GLOBAL: GAMEMD 0x836DA8
extern const char STR_00836DA8[];
// GLOBAL: GAMEMD 0x836DB8
extern const char STR_00836DB8[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- fetch a message by key (key, 0, file, line).
const wchar_t* FUN_00734E60(const char* key, int zero, const char* file, int line);

// LIBRARY: GAMEMD 0x7CA564 -- CRT swprintf.
int __cdecl swprintf(wchar_t* out, const wchar_t* format, ...);

// GLOBAL: GAMEMD 0x7E3568
extern const double DAT_007E3568 = 5.0;
// GLOBAL: GAMEMD 0x836DA8
extern const char STR_00836DA8[] = "TXT_POWER_DRAIN";
// GLOBAL: GAMEMD 0x836DB8
extern const char STR_00836DB8[] = "D:\\ra2mdpost\\Power.CPP";
// GLOBAL: GAMEMD 0xAC4E74
void* DAT_00AC4E74;
// END defined globals

// SYNTHETIC: GAMEMD 0x0063F4F0
// GLOBAL: GAMEMD 0x00AC4E68
double DAT_00AC4E68 = DAT_00AC4D18 / DAT_007EFF40;

// SYNTHETIC: GAMEMD 0x0063F510
// GLOBAL: GAMEMD 0x00AC4E50
double DAT_00AC4E50 = DAT_007E1718 / DAT_00AC4E68;

// SYNTHETIC: GAMEMD 0x0063F690
// GLOBAL: GAMEMD 0x00AC4E58
MathTblCoord DAT_00AC4E58;

// FUNCTION: GAMEMD 0x63F6B0
PowerClass::PowerClass()
    : unknown_150C(false), unknown_151C(0), unknown_152C(0), unknown_1530(0), unknown_1534(0),
      unknown_1538(false), unknown_153C(-1), unknown_1540(-1)
{
}

// FUNCTION: GAMEMD 0x63F730
// Reset: base reset, then clear the bar state and restart both timers.
void PowerClass::vf_07()
{
    RadarClass::vf_07();
    unknown_153C = -1;
    unknown_1540 = -1;
    unknown_1510 = ScenarioElapsedTimer();
    unknown_151C = 0;
    unknown_1520 = ScenarioElapsedTimer();
    unknown_152C = 0;
    unknown_1530 = 0;
    unknown_1534 = 0;
    unknown_1538 = false;
}

// FUNCTION: GAMEMD 0x63F7B0
void FUN_0063F7B0(void* self)
{
    RadarClass_OneTime(self);
}

// FUNCTION: GAMEMD 0x63F7C0
// Calls other functions. Vtable slot 53 of PowerClass (RTTI).
void* FUN_0063F7C0(Obj_0063F7C0* a1, int a2)
{
    FUN_00652E90(a1, a2);
    void* c1 = FileSystem_LoadWholeFileEx(DAT_00836D9C, &DAT_00AC4E78);
    DAT_00AC4E74 = c1;
    return c1;
}

// FUNCTION: GAMEMD 0x63F7E0
// Free the art, then release the cached buffer if one is held.
void PowerClass::vf_50()
{
    RadarClass::vf_50();
    if (DAT_00AC4E78) {
        ::operator delete(DAT_00AC4E74);
        DAT_00AC4E78 = false;
    }
}

// FUNCTION: GAMEMD 0x63F810
void PowerClass::FUN_0063F810()
{
    unknown_151C = 10;
    unknown_1510 = ScenarioElapsedTimer(3);
}

// FUNCTION: GAMEMD 0x63F8F0
int PowerClass::FUN_0063F8F0()
{
    int total = FUN_0063F850();
    int used = unknown_1534 + unknown_1530 + unknown_152C;
    int part = used;
    if (used > total)
        part = total;
    return (int)((double)part / total * DAT_007E3568);
}

// FUNCTION: GAMEMD 0x63F940
int FUN_0063F940()
{
    return (StripHeight_00B0B504 + 3) / 3;
}

// FUNCTION: GAMEMD 0x63FDC0
void PowerClass::FUN_0063FDC0()
{
    int a, c, b;
    FUN_0063F960(&a, &c, &b);
    if (unknown_152C > a) {
        --unknown_152C;
        return;
    }
    if (unknown_1534 > b) {
        --unknown_1534;
        return;
    }
    if (unknown_1530 > c)
        --unknown_1530;
}

// FUNCTION: GAMEMD 0x63FE30
void PowerClass::FUN_0063FE30()
{
    int a, c, b;
    FUN_0063F960(&b, &c, &a);
    if (unknown_1534 < a) {
        ++unknown_1534;
        return;
    }
    if (unknown_152C < b) {
        ++unknown_152C;
        return;
    }
    if (unknown_1530 < c)
        ++unknown_1530;
}

// FUNCTION: GAMEMD 0x640450
// Tooltip text: id 999 formats the player's power output and drain; anything else is the radar's.
const wchar_t* PowerClass::vf_33(int id)
{
    if (id == 999) {
        swprintf(DAT_00AC4D30,
                 FUN_00734E60(STR_00836DA8, 0, STR_00836DB8, 0x29E),
                 CurrentPlayer->PowerOutput, CurrentPlayer->PowerDrain);
        return DAT_00AC4D30;
    }
    return RadarClass::vf_33(id);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x6404B0 -- PowerClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0B504
int StripHeight_00B0B504;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EFF40
extern const double DAT_007EFF40 = 60.0;
// END defined globals
