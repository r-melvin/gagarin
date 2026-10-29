// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small RadarClass members from Radar.CPP's code range (0x652680-0x658E7F), bytes matched against
//   retail gamemd.exe v1.001. Layout and evidence: input_controls/ui_display_chain.h.
//   Ordered ascending by retail address.

#include "radar_class.h"
#include "shape_button_class.h"
#include "../_layout/tactical.h"

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log, printf style.
void __cdecl FUN_004068E0(const char* format, ...);

struct RadarDiamond
{
    int X;
    int Y;
    int Mode;
    int Valid;
};

// GLOBAL: GAMEMD 0xB04978
extern ShapeButtonClass RadarButtonF2_00B04978;
// GLOBAL: GAMEMD 0xB04910
extern ShapeButtonClass RadarButtonF3_00B04910;

// FUNCTION: GAMEMD 0x652E50
// Add (or remove) the two radar buttons to the screen's button list.
void RadarClass::FUN_00652E50(bool on)
{
    if (on) {
        AddButton((DisplayGadget*)&RadarButtonF2_00B04978);
        AddButton((DisplayGadget*)&RadarButtonF3_00B04910);
    } else {
        vf_13((DisplayGadget*)&RadarButtonF2_00B04978);
        vf_13((DisplayGadget*)&RadarButtonF3_00B04910);
    }
}

// FUNCTION: GAMEMD 0x653810
bool RadarClass::vf_36(CellStruct* cell, DisplayHouse* house)
{
    bool r = DisplayClass::vf_36(cell, house) != 0;
    return r;
}

// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// FUNCTION: GAMEMD 0x653F70
// Centre the tactical view on a coordinate.
void RadarClass::vf_52(const CoordStruct* where)
{
    DAT_00887324->FUN_006D6070(where);
}

// FUNCTION: GAMEMD 0x656DF0
// Switch the tactical map on or off, log it, and apply the change.
void RadarClass::FUN_00656DF0(bool on)
{
    if (unknown_14D8 != on) {
        unknown_14D8 = on;
        FUN_004068E0("Radar: TacticalMap availability is %s\n", on ? "on" : "off");
        if (unknown_14B0 == 1)
            FUN_00656BE0(on, 1);
        else
            FUN_00656CB0(1, 1);
    }
}

// FUNCTION: GAMEMD 0x656E90
void RadarClass::FUN_00656E90(bool force)
{
    int v = 1;
    unknown_14D9 = v;
    if (!unknown_14DA && !force)
        v = 0;
    unknown_14DA = v;
}

// Hash keys over small integer records, used through function pointers by the radar code (0x652960 and
// 0x6558D0 take the address of 0x6558B0).
struct RadarKey_00655890
{
    int A;
    int B;
    int FUN_00655890();
};

struct RadarKey_006558B0
{
    int A;
    int B;
    int C;
    int FUN_006558B0();
};

// GLOBAL: GAMEMD 0x7E5168
extern const float DAT_007E5168;

// FUNCTION: GAMEMD 0x655050
// Convert a map cell to the radar's diamond coordinates; mode 1 marks an edge column.
RadarDiamond RadarClass::FUN_00655050(const Cell_0050DEF0& cell)
{
    int cx = cell.X;
    int cy = cell.Y;
    int x = unknown_1490 - cy + cx;
    int y = cy - unknown_1498 + cx;
    int mode = 2;
    if (x == -1) {
        x = 0;
        mode = 1;
    } else if (x == LocalRect.Width * 2 - 1) {
        mode = 1;
    }
    RadarDiamond r;
    r.X = x;
    r.Y = y;
    r.Mode = mode;
    r.Valid = 1;
    return r;
}

// FUNCTION: GAMEMD 0x655150
// Convert a radar-space point back to the map cell under it.
// PARTIAL: 91.3% -- same instructions; retail stores the first result word before the second multiply.
Cell_0050DEF0 RadarClass::FUN_00655150(const Point2D* point)
{
    double x = (double)point->X / *(float*)&unknown_1488 - unknown_1490;
    double y = (double)point->Y / *(float*)&unknown_1488 + unknown_1498;
    Cell_0050DEF0 result;
    int ix = (int)((x + y) * DAT_007E5168 + 0.5);
    double d = y - x;
    result.X = (short)ix;
    result.Y = (short)(int)(d * DAT_007E5168 + 0.5);
    return result;
}

// FUNCTION: GAMEMD 0x655890
int RadarKey_00655890::FUN_00655890()
{
    return A + B * 251;
}

// FUNCTION: GAMEMD 0x6558B0
int RadarKey_006558B0::FUN_006558B0()
{
    return B + C * 251;
}
