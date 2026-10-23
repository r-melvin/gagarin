// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit WDTSel.cpp. The name is the source-file string at 0x848de4
//   in retail gamemd.exe v1.001, passed by the assert at 0x76c5b1 inside this object's
//   code range (0x76c0a0-0x76f27f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
// The seven vtable-seating base destructors, ordered ascending by address.
//
// VectorCursor<T, Container>: a small polymorphic cursor over a vector. RTTI
// names eight instantiations (".?AV?$VectorCursor@...") with one vtable each;
// every scalar deleting destructor stores its own instantiation's vtable,
// frees the object when bit 0 of the flag is set and returns `this`, so the
// destructor is an empty virtual one. These bodies are compiler output: the
// explicit instantiations compile the inline constructor, which emits each
// vtable and its `??_G`. No member is touched, so no layout is modelled.
// The element and container types are only named here, never defined.

#include "../core/deleting_dtor_sweep.h"
#include "transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/leftover_trivial_leaf_sweep.h"

#include "../core/position_below_limit_family_methods.h"

#include "../core/seat_vtable_tail_dtor_sweep.h"

#include "../core/trivial_tu278_methods.h"

template <class T> class VectorClass;
template <class T> class DynamicVectorClass;
template <class T> class rc_ptr;
template <class T> class TRect;
class GraphicMenuItem;
class MSSfxEntry;
class MSAnim;
namespace WorldDominationTour {
class Conflict;
class GameOption;
class Territory;
}

template <class T, class Container>
class VectorCursor
{
public:
    VectorCursor() {}
    virtual ~VectorCursor() {}
};

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F72A0
extern const double DAT_007F72A0;
// GLOBAL: GAMEMD 0xB72A30
extern double DAT_00B72A30;
// GLOBAL: GAMEMD 0xB72A68
extern double DAT_00B72A68;
// GLOBAL: GAMEMD 0xB72A70
extern int DAT_00B72A70;
// GLOBAL: GAMEMD 0xB72A74
extern int DAT_00B72A74;
// GLOBAL: GAMEMD 0xB72A78
extern int DAT_00B72A78;
// GLOBAL: GAMEMD 0xB72A80
extern double DAT_00B72A80;

// FUNCTION: GAMEMD 0x76C0D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076C0D0()
{
    DAT_00B72A80 = DAT_00B72A30 / DAT_007F72A0;
}

// FUNCTION: GAMEMD 0x76C0F0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076C0F0()
{
    DAT_00B72A68 = DAT_007E1718 / DAT_00B72A80;
}

// FUNCTION: GAMEMD 0x76C270
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0076C270()
{
    DAT_00B72A78 = 0;
    DAT_00B72A70 = 0x80;
    DAT_00B72A74 = 0x80;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76EFE0
void* Obj_76EFE0::FUN_76EFE0(unsigned int flags)
{
    FUN_0076C6E0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F000
// Calls other functions.
int Obj_0076F000::FUN_0076F000(int a1, int a2)
{
    FUN_0076FF40(a1, &unknown_2C, a2);
    return a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F020
int FUN_0076F020(LeafObj_0x04* self)
{
    return self->unknown_04;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F060
// VTABLE: GAMEMD 0x7F71C4
void FUN_0076F060(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F71C4;
    FUN_0065D460(self);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F070
int FUN_0076F070(LeafObj_0x04* self)
{
    return self->unknown_04;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F080
int FUN_0076F080(LeafObj_0x04* self)
{
    return self->unknown_04;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0076F0B0
//
// Is this cursor still inside its owner's limit.
bool FUN_0076F0B0(Cursor_004F28B0* self)
{
    return self->Position < self->Owner->Limit;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0076F0E0
//
// Is this cursor still inside its owner's limit.
bool FUN_0076F0E0(Cursor_004F28B0* self)
{
    return self->Position < self->Owner->Limit;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0076F0F0
//
// Is this cursor still inside its owner's limit.
bool FUN_0076F0F0(Cursor_004F28B0* self)
{
    return self->Position < self->Owner->Limit;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x76F100
// VectorCursor<MSSfxEntry*> (vtable 0x7F72C4)
template class VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*> >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x76F120
// VectorCursor<rc_ptr<Territory> > (vtable 0x7F72D8)
template class VectorCursor<rc_ptr<WorldDominationTour::Territory>, DynamicVectorClass<rc_ptr<WorldDominationTour::Territory> > >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x76F140
// VectorCursor<MSAnim*> (vtable 0x7F72EC)
template class VectorCursor<MSAnim*, DynamicVectorClass<MSAnim*> >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F160
// Updates one member in place. Vtable slot 2 of VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*>> (RTTI).
Obj_0076F160* Obj_0076F160::FUN_0076F160()
{
    unknown_08++;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F170
// Updates one member in place. Vtable slot 3 of VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*>> (RTTI).
Obj_0076F170* Obj_0076F170::FUN_0076F170()
{
    unknown_08--;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F180
// Updates one member in place. Vtable slot 2 of VectorCursor<WorldDominationTour::VTerritory::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::Territory>> (RTTI).
Obj_0076F180* Obj_0076F180::FUN_0076F180()
{
    unknown_08++;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F190
// Updates one member in place. Vtable slot 3 of VectorCursor<WorldDominationTour::VTerritory::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::Territory>> (RTTI).
Obj_0076F190* Obj_0076F190::FUN_0076F190()
{
    unknown_08--;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F1A0
// Updates one member in place. Vtable slot 2 of VectorCursor<MSAnim*, DynamicVectorClass<MSAnim*>> (RTTI).
Obj_0076F1A0* Obj_0076F1A0::FUN_0076F1A0()
{
    unknown_08++;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76F1B0
// Updates one member in place. Vtable slot 3 of VectorCursor<MSAnim*, DynamicVectorClass<MSAnim*>> (RTTI).
Obj_0076F1B0* Obj_0076F1B0::FUN_0076F1B0()
{
    unknown_08--;
    return this;
}
