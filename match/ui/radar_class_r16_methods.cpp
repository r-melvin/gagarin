// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below (Radar.CPP code range
//   0x652680-0x658E7F). Layout and evidence for the members: input_controls/ui_display_chain.h.
//   The members are declared on a TU-local derived view so the shared header stays untouched.
//
// Address index: 0x6550C0 0x6551C0 0x6557F0 0x656BE0

#include "radar_class.h"
#include "../core/vector_class_operations.h"

struct RadarDiamond_006550C0
{
    int X;
    int Y;
    int Mode;
    int Valid;
};

struct RadarView_R16 : public RadarClass
{
    RadarDiamond_006550C0 FUN_006550C0(const Cell_0050DEF0* cell);
    void FUN_006551C0(const Cell* cell);
    Point2D* FUN_006557F0(Point2D* out, const Point2D* point, bool clamp);
    void FUN_00656BE0(bool on, bool sound);
};

// The radar's activation timer at +0x14C0, restarted by 0x406060.
struct RadarTimer_00406060
{
    // FUNCTION: GAMEMD 0x406060 (decl; reloc)
    void FUN_00406060();
};


// GLOBAL: GAMEMD 0x8871E0 -- the rules object.
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log, printf style.
void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x750920 (decl; reloc) -- play a sound effect.
void* FUN_00750920(int voc, float volume, unsigned int pan, void* controller);

// GLOBAL: GAMEMD 0x7F0424
extern const float DAT_007F0424;

// FUNCTION: GAMEMD 0x6550C0
// Convert a map cell to the radar's screen position (scaled by the radar zoom).
RadarDiamond_006550C0 RadarView_R16::FUN_006550C0(const Cell_0050DEF0* cell)
{
    int cx = cell->X;
    int cy = cell->Y;
    int left = RadarBounds.X;
    int x = (int)((double)(unknown_1490 - cy + cx) * *(float*)&unknown_1488 + left);
    int y = (int)((double)(cy - unknown_1498 + cx) * *(float*)&unknown_1488 + RadarBounds.Y);
    if (x == left - 1) {
        x++;
    }
    RadarDiamond_006550C0 r;
    r.X = x;
    r.Y = y;
    r.Mode = 1;
    r.Valid = 1;
    return r;
}

// FUNCTION: GAMEMD 0x6551C0
// Queue a cell for the radar's redraw list (once) and flag the radar dirty.
void RadarView_R16::FUN_006551C0(const Cell* cell)
{
    for (int i = unknown_1224.Count - 1; i >= 0; i--) {
        if (unknown_1224.Items[i] == *cell) {
            return;
        }
    }
    unknown_1224.AddItem(*cell);
    unknown_14D9 = 1;
}

// FUNCTION: GAMEMD 0x6557F0
// Convert a map point to the radar's pixel position at the fixed scale, optionally clamped to the radar's size.
Point2D* RadarView_R16::FUN_006557F0(Point2D* out, const Point2D* point, bool clamp)
{
    int cx = point->X;
    int cy = point->Y;
    double dx = (double)((unknown_1490 << 8) - cy + cx) * *(float*)&unknown_1488;
    int x = (int)(dx * DAT_007F0424);
    double dy = (double)(cy - (unknown_1498 << 8) + cx) * *(float*)&unknown_1488;
    int y = (int)(dy * DAT_007F0424);
    if (clamp) {
        if (x < 0) {
            x = 0;
        }
        if (x >= RadarBounds.Width) {
            x = RadarBounds.Width - 1;
        }
        if (y < 0) {
            y = 0;
        }
        if (y >= RadarBounds.Height) {
            y = RadarBounds.Height - 1;
        }
    }
    out->X = x;
    out->Y = y;
    return out;
}

// FUNCTION: GAMEMD 0x656BE0
// Switch the radar between its on and off transition, optionally playing the matching sound.
void RadarView_R16::FUN_00656BE0(bool on, bool sound)
{
    if (on == true) {
        if (unknown_14AC == 0 || unknown_14AC == 2) {
            unknown_14AC = 3;
            ((RadarTimer_00406060*)&unknown_14C0)->FUN_00406060();
            if (sound) {
                FUN_00750920(DAT_008871E0->RadarOn, 1.0f, 0x2000, 0);
            }
            FUN_004068E0("Radar: ACTIVATING\n");
        }
    } else {
        ((RadarTimer_00406060*)&unknown_14C0)->FUN_00406060();
        unknown_14AC = 2;
        if (sound) {
            FUN_00750920(DAT_008871E0->RadarOff, 1.0f, 0x2000, 0);
        }
        FUN_004068E0("Radar: DEACTIVING\n");
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0424
extern const float DAT_007F0424 = 0.00390625f;
// END defined globals
