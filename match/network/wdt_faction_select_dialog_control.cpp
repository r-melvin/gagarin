// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x7AF500 and 0x7B0440; RTTI .?AVFactionSelectDialogControl@WorldDominationTour@@
//   (vtable 0x7F791C, bases OwnerDraw::SimpleDialogControl -> OwnerDraw::DialogControl). The vtable
//   overrides only slot 0; slots 1-4 are SimpleDialogControl's.
//   Address index: 0x7AF500 (destructor), 0x7B0440 (scalar deleting destructor).
#include "../FUNCTION.H"
#include "../ui/ownrdraw_dialog_control.h"

// What the three owned pointers point at: polymorphic objects released through their slot 0.
struct Obj_007AF500
{
    virtual ~Obj_007AF500();
};

namespace WorldDominationTour {

// VTABLE: GAMEMD 0x7F791C
class FactionSelectDialogControl : public OwnerDraw::SimpleDialogControl
{
public:
    virtual ~FactionSelectDialogControl();

    int unknown_0C;           // +0x0C
    Obj_007AF500* Owned10;    // +0x10
    Obj_007AF500* Owned14;    // +0x14
    Obj_007AF500* Owned18;    // +0x18
};
GG_STATIC_ASSERT(offsetof(FactionSelectDialogControl, Owned10) == 0x10);
GG_STATIC_ASSERT(offsetof(FactionSelectDialogControl, Owned18) == 0x18);

// FUNCTION: GAMEMD 0x7AF500
// Releases the three owned objects, then the base destructor.
FactionSelectDialogControl::~FactionSelectDialogControl()
{
    delete Owned10;
    delete Owned14;
    delete Owned18;
}

}  // namespace WorldDominationTour

// SYNTHETIC: GAMEMD 0x7B0440 -- FactionSelectDialogControl::`scalar deleting destructor' (the destructor body
// expanded, then the free).
