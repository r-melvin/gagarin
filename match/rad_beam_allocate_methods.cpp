// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x659110, 0x659590, 0x659A30,
//   0x659CA0 and 0x659EE0 (the inline vector helpers below stand for the vector
//   operators retail expands in 0x659A30 and 0x659EE0).

#include "rad_beam_allocate_methods.h"
#include "pixel_shift_view.h"
#include "tactical_class_coords_to_client_methods.h"
#include "wwlib/surface/surface_class.h"
#include "trig_table_functions_004cac40.h"


// GLOBAL: GAMEMD 0x887314 -- the screen surface.
extern Surface* DAT_00887314;
// GLOBAL: GAMEMD 0x887324 -- the tactical view.
extern Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0x886FA0 -- the visible tactical rectangle.
extern RectangleStruct DAT_00886FA0;

// FUNCTION: GAMEMD 0x659110
//
// Create a beam of the given type, register it in the global beam list, and
// seed its +0x18 value from the type: 10 for type 1, 20 for anything else.
// The list's answer is discarded, and the +0x18 store is made whether or not
// the allocation succeeded (retail dereferences the result unconditionally).
RadBeam* RadBeam::Allocate(int type)
{
    RadBeam* beam = new RadBeam(type);

    DAT_00B04A60.AddItem(beam);

    int amplitude = (type != 1) ? 20 : 10;
    beam->At_18 = amplitude;

    return beam;
}

static inline void CopyVec(CoordStruct* dst, const CoordStruct* src)
{
    *dst = *src;
}

static inline CoordStruct Scale(const CoordStruct& v, int n)
{
    CoordStruct r;
    r.X = v.X * n;
    r.Y = v.Y * n;
    r.Z = v.Z * n;
    return r;
}

static inline CoordStruct Divide(int x, int y, int z, int n)
{
    CoordStruct r;
    r.X = x;
    r.Y = y;
    r.Z = z;
    if (n) {
        r.X /= n;
        r.Y /= n;
        r.Z /= n;
    }
    return r;
}

static inline CoordStruct Add(const CoordStruct& a, const CoordStruct& b)
{
    CoordStruct r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    r.Z = a.Z + b.Z;
    return r;
}

static inline void CopyColor(ColorStruct* dst, const ColorStruct* src)
{
    *dst = *src;
}

// FUNCTION: GAMEMD 0x659590
//
// Draw one line between two world points, lifted by the beam's height offset.
void RadBeam::FUN_00659590(const CoordStruct* from, const CoordStruct* to, short color)
{
    Point2D first;
    Point2D second;
    DAT_00887324->CoordsToClient(from, &first);
    DAT_00887324->CoordsToClient(to, &second);
    RectangleStruct clip = DAT_00886FA0;
    if (ClipLine(&first, &second, &clip)) {
        int fromLift = unknown_0C - Tactical::AdjustForZ(from->Z) - 2;
        int toLift = -2 - Tactical::AdjustForZ(to->Z);
        DAT_00887314->unknown_34(&DAT_00886FA0, &first, &second, color, fromLift, toLift, false);
    }
}

// FUNCTION: GAMEMD 0x659A30
void RadBeam::FUN_00659A30()
{
    int steps = (int)(unknown_68 / At_18);
    unknown_8C = steps;
    unknown_90 = Divide(unknown_5C.X, unknown_5C.Y, unknown_5C.Z, steps);
    double ratio = (double)unknown_7C / unknown_3C;
    unknown_80 = ratio * unknown_40;
    CopyVec(&unknown_9C, &unknown_24);
    CopyColor(&unknown_C0, &unknown_20);
}

// FUNCTION: GAMEMD 0x659CA0
bool RadBeam::FUN_00659CA0()
{
    if (!unknown_08) {
        unknown_08 = 1;
        FUN_00659E30();
    }
    if (unknown_09) {
        FUN_00659EE0();
        unknown_88 = 0;
        if (unknown_88 < unknown_8C) {
            do {
                CoordStruct* to = &unknown_A8;
                FUN_00659FF0();
                short packed = (unsigned short)(unknown_C0.G >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1
                             | (unsigned short)(unknown_C0.B >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2
                             | (unsigned short)(unknown_C0.R >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0;
                CoordStruct* from = &unknown_9C;
                Point2D first;
                Point2D second;
                DAT_00887324->CoordsToClient(from, &first);
                DAT_00887324->CoordsToClient(to, &second);
                RectangleStruct clip = DAT_00886FA0;
                if (ClipLine(&first, &second, &clip)) {
                    int fromLift = unknown_0C - Tactical::AdjustForZ(from->Z) - 2;
                    int toLift = -2 - Tactical::AdjustForZ(to->Z);
                    DAT_00887314->unknown_34(&DAT_00886FA0, &first, &second, packed, fromLift, toLift, false);
                }
                unknown_88++;
            } while (unknown_88 < unknown_8C);
        }
    }
    unknown_7C++;
    return unknown_7C >= unknown_3C;
}

// FUNCTION: GAMEMD 0x659EE0
void RadBeam::FUN_00659EE0()
{
    int total = unknown_3C;
    int frame = unknown_7C;
    double phase = (frame < total / 2) ? (double)(frame * 2) : (double)(total - frame * 2 % total);
    unknown_80 = phase / (double)total * unknown_40;

    int travel = (int)((double)(unknown_50 * frame) * unknown_48);
    unknown_5C = Add(unknown_5C, Scale(unknown_70, travel));

    unknown_68 = FUN_004CAC40((double)(unknown_5C.X * unknown_5C.X + unknown_5C.Y * unknown_5C.Y + unknown_5C.Z * unknown_5C.Z));
    int steps = (int)(unknown_68 / At_18);
    unknown_8C = steps;
    unknown_90 = Divide(unknown_5C.X, unknown_5C.Y, unknown_5C.Z, steps);
}
