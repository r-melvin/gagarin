// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// Constructor of Dial8Class, the eight-way direction dial control (vtable 0x7E5E3C), a
// ControlClass built with flags 7 and sticky. It caches the face centre and
// two rings of eight compass points (outer ring at 0.4 / 0.28 of the size,
// inner ring at 0.3 / 0.21) and the initial direction and its facing.

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/dial8_class.h"
#include "mouse_ww_mouse_class.h"
#include "abstract_class_target_direction_methods.h"
#include "shared_constants_globals.h"

// Direction held as the high byte of a 16-bit binary angle; the facing is
// read back through the full dword.
union DialDirection
{
    DialDirection() {}
    DialDirection(int dir)
    {
        Raw = (unsigned short)(dir << 8);
    }
    int Facing() const { return (((Value >> 12) + 1) >> 1) & 7; }

    unsigned       Value;
    unsigned short Raw;
};

// FUNCTION: GAMEMD 0x4A53B0
Dial8Class::Dial8Class(int id, int x, int y, int width, int height, int direction)
    : ControlClass(id, x, y, width, height, 7, 1)
{
    unknown_2C = X + Width / 2;
    unknown_30 = Y + Height / 2;
    Direction = direction;
    Facing = DialDirection(direction).Facing();
    unknown_BC = Facing;

    OuterPoint[0].X = unknown_2C;
    OuterPoint[0].Y = unknown_30 - (height * 8 / 2) / 10;
    OuterPoint[1].X = unknown_2C + (width * 56 / 2) / 100;
    OuterPoint[1].Y = unknown_30 - (height * 56 / 2) / 100;
    OuterPoint[2].X = unknown_2C + (width * 8 / 2) / 10;
    OuterPoint[2].Y = unknown_30;
    OuterPoint[3].X = unknown_2C + (width * 56 / 2) / 100;
    OuterPoint[3].Y = unknown_30 + (height * 56 / 2) / 100;
    OuterPoint[4].X = unknown_2C;
    OuterPoint[4].Y = unknown_30 + (height * 8 / 2) / 10;
    OuterPoint[5].X = unknown_2C - (width * 56 / 2) / 100;
    OuterPoint[5].Y = unknown_30 + (height * 56 / 2) / 100;
    OuterPoint[6].X = unknown_2C - (width * 8 / 2) / 10;
    OuterPoint[6].Y = unknown_30;
    OuterPoint[7].X = unknown_2C - (width * 56 / 2) / 100;
    OuterPoint[7].Y = unknown_30 - (height * 56 / 2) / 100;

    InnerPoint[0].X = unknown_2C;
    InnerPoint[0].Y = unknown_30 - (height * 6 / 2) / 10;
    InnerPoint[1].X = unknown_2C + (width * 42 / 2) / 100;
    InnerPoint[1].Y = unknown_30 - (height * 42 / 2) / 100;
    InnerPoint[2].X = unknown_2C + (width * 6 / 2) / 10;
    InnerPoint[2].Y = unknown_30;
    InnerPoint[3].X = unknown_2C + (width * 42 / 2) / 100;
    InnerPoint[3].Y = unknown_30 + (height * 42 / 2) / 100;
    InnerPoint[4].X = unknown_2C;
    InnerPoint[4].Y = unknown_30 + (height * 6 / 2) / 10;
    InnerPoint[5].X = unknown_2C - (width * 42 / 2) / 100;
    InnerPoint[5].Y = unknown_30 + (height * 42 / 2) / 100;
    InnerPoint[6].X = unknown_2C - (width * 6 / 2) / 10;
    InnerPoint[6].Y = unknown_30;
    InnerPoint[7].X = unknown_2C - (width * 42 / 2) / 100;
    InnerPoint[7].Y = unknown_30 - (height * 42 / 2) / 100;
}

// GLOBAL: GAMEMD 0x8A0148 -- set while the dial is being dragged.
extern int DAT_008A0148;

// FUNCTION: GAMEMD 0x4A5660
// While the dial is pressed or dragged, turn the mouse position into a direction and report a change of
// facing to the control base; otherwise only the release clears the drag.
int Dial8Class::Action(unsigned flags, unsigned* key, int modifier)
{
    StickyProcess(flags);
    if (flags & 1) {
        DAT_008A0148 = 1;
    }
    if ((flags & 1) || ((flags & 2) && DAT_008A0148)) {
        Point2D pos;
        Point2D mouse = *WWMouseClassInstance->vf_13(&pos);
        Point2D center;
        center.X = unknown_2C;
        center.Y = unknown_30;
        DialDirection angle;
        angle.Raw = (short)(int)((FUN_004CAE30((double)center.Y - mouse.Y, (double)mouse.X - center.X)
                                  - GG_QUARTER_TURN) * GG_RADIANS_TO_DIR16);
        Direction = (((angle.Value >> 7) + 1) >> 1) & 0xFF;
        Facing = DialDirection(Direction).Facing();
        if (Facing != unknown_BC) {
            unknown_BC = Facing;
            ControlClass::Action(flags, key, 0);
            return 1;
        }
        *key = 0;
        ControlClass::Action(0, key, 0);
        return 1;
    }
    if (flags & 4) {
        *key = 0;
        DAT_008A0148 = 0;
    }
    return ControlClass::Action(0, key, 0);
}

// SYNTHETIC: GAMEMD 0x4A59A0 -- Dial8Class scalar deleting destructor, emitted by the compiler from the virtual destructor
