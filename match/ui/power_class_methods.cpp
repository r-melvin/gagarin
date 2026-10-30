// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   PowerClass members (vtable 0x7EFF54) from Power.CPP's code range, bytes matched against
//   retail gamemd.exe v1.001. Layout and evidence: input_controls/ui_display_chain.h.
//   Ordered ascending by retail address.
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
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /Ob2 /MT

#include "input_controls/ui_display_chain.h"
#include "../_layout/house_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"

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

// GLOBAL: GAMEMD 0x836DA8
extern const char STR_00836DA8[];
// GLOBAL: GAMEMD 0x836DB8
extern const char STR_00836DB8[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- fetch a message by key (key, 0, file, line).
const wchar_t* FUN_00734E60(const char* key, int zero, const char* file, int line);
// LIBRARY: GAMEMD 0x7CA564 -- CRT swprintf.
int __cdecl swprintf(wchar_t* out, const wchar_t* format, ...);

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

// SYNTHETIC: GAMEMD 0x6404B0 -- PowerClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0B504
int StripHeight_00B0B504;
// GLOBAL: GAMEMD 0x7E3568
extern const double DAT_007E3568 = 5.0;
// GLOBAL: GAMEMD 0x836DA8
extern const char STR_00836DA8[] = "TXT_POWER_DRAIN";
// GLOBAL: GAMEMD 0x836DB8
extern const char STR_00836DB8[] = "D:\\ra2mdpost\\Power.CPP";
// GLOBAL: GAMEMD 0xAC4E74
void* DAT_00AC4E74;
// END defined globals
