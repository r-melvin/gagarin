// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit GOptions.CPP. The name is the source-file string at 0x8240bc
//   in retail gamemd.exe v1.001, passed by the assert at 0x4f1277 inside this object's
//   code range (0x4f0ef0-0x4f363f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// VectorCursor<T, Container>: a small polymorphic cursor over a vector. RTTI
// names eight instantiations (".?AV?$VectorCursor@...") with one vtable each;
// every scalar deleting destructor stores its own instantiation's vtable,
// frees the object when bit 0 of the flag is set and returns `this`, so the
// destructor is an empty virtual one. These bodies are compiler output: the
// explicit instantiations compile the inline constructor, which emits each
// vtable and its `??_G`. The class (members included) is core/vector_cursor.h.
// The element and container types are only named here, never defined.

#include "../core/deleting_dtor_sweep.h"
#include "../core/mathtbl_init_shapes.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/position_below_limit_family_methods.h"

#include "../core/trivial_tu092_methods.h"
#include "../_layout/elapsed_timer.h"
#include "../network/event_queue.h"
#include "input_controls/menus_graphic_menu.h"

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

#include "../core/vector_cursor.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7EA5E0
extern const double DAT_007EA5E0;
// GLOBAL: GAMEMD 0xA8EE00
extern double DAT_00A8EE00;


// Retail PAVGraphicMenuItem RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

class GraphicMenuItem;

// VTABLE: GAMEMD 0x7EA624 -- VectorClass<GraphicMenuItem*>.
template class VectorClass<GraphicMenuItem*>;
typedef VectorClass<GraphicMenuItem*> GgGraphicMenuItemVectorClass;
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA604 -- DynamicVectorClass<GraphicMenuItem*>.
template class DynamicVectorClass<GraphicMenuItem*>;
typedef DynamicVectorClass<GraphicMenuItem*> GgGraphicMenuItemDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgGraphicMenuItemDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(GraphicMenuItem*) == 4);

// SYNTHETIC: GAMEMD 0x004F0F20
// dynamic initializer for DAT_00A8EE70
// GLOBAL: GAMEMD 0x00A8EE70
double DAT_00A8EE70 = DAT_00A8EE00 / DAT_007EA5E0;

// SYNTHETIC: GAMEMD 0x004F0F40
// dynamic initializer for DAT_00A8EE58
// GLOBAL: GAMEMD 0x00A8EE58
double DAT_00A8EE58 = 1.0 / DAT_00A8EE70;

GG_STATIC_ASSERT(sizeof(DAT_00A8EE70) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00A8EE58) == 8);

// SYNTHETIC: GAMEMD 0x004F10C0
// GLOBAL: GAMEMD 0x00A8EE60
MathTblCoord DAT_00A8EE60;

// FUNCTION: GAMEMD 0x4F1710
// Empty function.
void __cdecl FUN_004F1710()
{
}

// WinMM import: GAMEMD 0x007E1530 (timeGetTime).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

// FUNCTION: GAMEMD 0x4F1AA0
// Append `*item` at the head slot, stamp it with the wall-clock time, and
// advance the head (modulo 128). Returns 0 when the queue already holds 128.
template<>
int EventQueue<128>::FUN_004F1AA0(const EventQueueItem* item)
{
    if (Count < 128) {
        List[Head] = *item;
        Time[Head] = timeGetTime();
        Head = (Head + 1) & 0x7F;
        Count++;
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4F1B00
// Out-of-line copy of the duration constructor: stamp the start tick and
// store the duration.
ScenarioElapsedTimer* ScenarioElapsedTimer::FUN_004F1B00(int ticks)
{
    unknown_00 = unknown_04.GetTime();
    unknown_08 = ticks;
    return this;
}

// FUNCTION: GAMEMD 0x4F1B20
// Ticks remaining: the stored duration, less the time elapsed since the start
// tick unless the timer is paused (start tick -1).
int ScenarioElapsedTimer::FUN_004F1B20()
{
    int left = unknown_08;
    if (unknown_00 != -1) {
        int elapsed = unknown_04.GetTime();
        elapsed -= unknown_00;
        if (elapsed < left) {
            return left - elapsed;
        }
        return 0;
    }
    return left;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4F2850
// DynamicVectorClass<GraphicMenuItem*>::Clear

// FUNCTION: GAMEMD 0x4F2880
// DynamicVectorClass<GraphicMenuItem*>::Slot5

// FUNCTION: GAMEMD 0x4F28A0
// VectorClass<GraphicMenuItem*>::Slot6

// FUNCTION: GAMEMD 0x4F28E0
// VectorClass<GraphicMenuItem*>::operator==

// FUNCTION: GAMEMD 0x4F2920
// VectorClass<GraphicMenuItem*>::SetCapacity

// FUNCTION: GAMEMD 0x4F29D0
// VectorClass<GraphicMenuItem*>::Clear

// FUNCTION: GAMEMD 0x4F2A00
// VectorClass<GraphicMenuItem*>::FindItemIndex

// FUNCTION: GAMEMD 0x4F2A40
// VectorClass<GraphicMenuItem*>::Slot5

// FUNCTION: GAMEMD 0x4F2A60
// DynamicVectorClass<GraphicMenuItem*>::SetCapacity

// FUNCTION: GAMEMD 0x4F2B10
// DynamicVectorClass<GraphicMenuItem*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F2B60
// VectorClass<GraphicMenuItem*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F2BB0
// DynamicVectorClass<GraphicMenuItem*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004F28B0
//
// Is this cursor still inside its owner's limit.
bool FUN_004F28B0(Cursor_004F28B0* self)
{
    return self->Position < self->Owner->Limit;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x4F28C0
// VectorCursor<GraphicMenuItem*> (vtable 0x7EA644)
template class VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*> >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4F2B40
// Updates one member in place. Vtable slot 2 of VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*>> (RTTI).
Obj_004F2B40* Obj_004F2B40::FUN_004F2B40()
{
    unknown_08++;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4F2B50
// Updates one member in place. Vtable slot 3 of VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*>> (RTTI).
Obj_004F2B50* Obj_004F2B50::FUN_004F2B50()
{
    unknown_08--;
    return this;
}

// FUNCTION: GAMEMD 0x4F3070
// Releases the owned animation, then runs the base destructor. (The scalar deleting destructor 0x4F30E0 is
// not reproduced: cl emits ??_G only beside a constructor, and the factory 0x4F2C70 expands it inline.)
GraphicMenuAnimItem::~GraphicMenuAnimItem()
{
    delete Anim;
}

// SYNTHETIC: GAMEMD 0x4F30E0 -- GraphicMenuAnimItem::`scalar deleting destructor' (compiler-generated ??_G beside the out-of-line destructor)

// FUNCTION: GAMEMD 0x4F3090
// Hit test: true when the item is visible and the point lies inside its rectangle.
bool GraphicMenuAnimItem::Slot2(const Point2D* point)
{
    return Visible
        && point->X >= Rect.X && point->X < Rect.X + Rect.Width
        && point->Y >= Rect.Y && point->Y < Rect.Y + Rect.Height;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EA5E0
extern const double DAT_007EA5E0 = 60.0;
// END defined globals
