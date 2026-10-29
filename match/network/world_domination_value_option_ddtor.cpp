// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// WorldDominationTour::ValueGameOption<unsigned char> (RTTI chain
// ValueGameOption<uc> -> GameOption -> ReferenceCounted). Its scalar deleting
// destructor at 0x766B90 destroys the member at +0x14, calls the out-of-line
// GameOption destructor 0x767300 and frees the object when bit 0 of the flag
// is set. The body is compiler output: the explicit instantiation compiles
// the inline constructor, which emits the vtable and the `??_G` from the
// implicit destructor (no vtable store of its own). The GameOption
// constructor and destructor are declared only.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Out-of-line destructor 0x7B46F0 (a four-byte member: a string handle).
#include "../_layout/member_7b46f0.h"

namespace WorldDominationTour {

class GameOption
{
public:
    GameOption();
    virtual ~GameOption();   // 0x767300
    char unknown_04[0x10];   // +0x04
};

template <class T>
class ValueGameOption : public GameOption
{
public:
    ValueGameOption() {}
    Member_7B46F0 Name;   // +0x14
};

}  // namespace WorldDominationTour


// SYNTHETIC: GAMEMD 0x766B90
// ValueGameOption<unsigned char> scalar deleting destructor
template class WorldDominationTour::ValueGameOption<unsigned char>;

// offsetof on a template-id must follow the instantiation under VC6.
typedef WorldDominationTour::ValueGameOption<unsigned char> ValueGameOptionUC;
GG_STATIC_ASSERT(offsetof(ValueGameOptionUC, Name) == 0x14);
