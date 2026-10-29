// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: RTTI chain OwnerDraw::SimpleDialogControl -> OwnerDraw::DialogControl; the base
//   vtable 0x7EF720 holds the pure-call stub in slots 1-4, 0x7EF738 holds the overrides.
#ifndef GG_MATCH_UI_OWNRDRAW_DIALOG_CONTROL_H
#define GG_MATCH_UI_OWNRDRAW_DIALOG_CONTROL_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

namespace OwnerDraw {

// VTABLE: GAMEMD 0x7EF720
class DialogControl
{
public:
    virtual ~DialogControl();   // FUNCTION: GAMEMD 0x624130
    virtual void          Slot1(int key, int value) = 0;
    virtual unsigned char Slot2() const = 0;
    virtual int           Slot3() = 0;
    virtual bool          Slot4() const = 0;
};

// VTABLE: GAMEMD 0x7EF738
class SimpleDialogControl : public DialogControl
{
public:
    SimpleDialogControl();                    // FUNCTION: GAMEMD 0x624110
    virtual void          Slot1(int key, int value);   // FUNCTION: GAMEMD 0x624140
    virtual unsigned char Slot2() const;               // FUNCTION: GAMEMD 0x6241C0
    virtual int           Slot3();                     // FUNCTION: GAMEMD 0x6241D0
    virtual bool          Slot4() const;               // FUNCTION: GAMEMD 0x6241E0
    int           unknown_04;   // +0x04
    unsigned char unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(SimpleDialogControl, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(SimpleDialogControl, unknown_08) == 0x08);

}  // namespace OwnerDraw

#endif  // GG_MATCH_UI_OWNRDRAW_DIALOG_CONTROL_H
