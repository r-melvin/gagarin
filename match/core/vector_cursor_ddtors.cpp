// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// VectorCursor<T, Container>: a small polymorphic cursor over a vector. RTTI
// names eight instantiations (".?AV?$VectorCursor@...") with one vtable each;
// every scalar deleting destructor stores its own instantiation's vtable,
// frees the object when bit 0 of the flag is set and returns `this`, so the
// destructor is an empty virtual one. These bodies are compiler output: the
// explicit instantiations compile the inline constructor, which emits each
// vtable and its `??_G`. The class (members included) is vector_cursor.h.
// The element and container types are only named here, never defined.

#include "vector_cursor.h"
#include "vector_cursor_members.h"

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

// SYNTHETIC: GAMEMD 0x4F28B0 -- VectorCursor<GraphicMenuItem*> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x4F28C0 -- VectorCursor<GraphicMenuItem*> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x4F2B40 -- VectorCursor<GraphicMenuItem*> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x4F2B50 -- VectorCursor<GraphicMenuItem*> slot 3 (decrement)
// VectorCursor<GraphicMenuItem*> (vtable 0x7EA644)
template class VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*> >;
// SYNTHETIC: GAMEMD 0x4F3FC0 -- VectorCursor<unsigned int> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x4F3FD0 -- VectorCursor<unsigned int> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x4F3FF0 -- VectorCursor<unsigned int> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x4F4000 -- VectorCursor<unsigned int> slot 3 (decrement)
// VectorCursor<unsigned int> (vtable 0x7EA6C8)
template class VectorCursor<unsigned int, DynamicVectorClass<unsigned int> >;
// SYNTHETIC: GAMEMD 0x765700 -- VectorCursor<rc_ptr<Conflict>> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x765770 -- VectorCursor<rc_ptr<Conflict>> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x765B40 -- VectorCursor<rc_ptr<Conflict>> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x765B50 -- VectorCursor<rc_ptr<Conflict>> slot 3 (decrement)
// VectorCursor<rc_ptr<Conflict> > (vtable 0x7F6F9C)
template class VectorCursor<rc_ptr<WorldDominationTour::Conflict>, DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict> > >;
// SYNTHETIC: GAMEMD 0x766920 -- VectorCursor<rc_ptr<GameOption>> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x7669F0 -- VectorCursor<rc_ptr<GameOption>> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x766FA0 -- VectorCursor<rc_ptr<GameOption>> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x766FB0 -- VectorCursor<rc_ptr<GameOption>> slot 3 (decrement)
// VectorCursor<rc_ptr<GameOption> > (vtable 0x7F702C)
template class VectorCursor<rc_ptr<WorldDominationTour::GameOption>, DynamicVectorClass<rc_ptr<WorldDominationTour::GameOption> > >;
// SYNTHETIC: GAMEMD 0x769D60 -- VectorCursor<TRect<int>> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x769DC0 -- VectorCursor<TRect<int>> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x76A5A0 -- VectorCursor<TRect<int>> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x76A5B0 -- VectorCursor<TRect<int>> slot 3 (decrement)
// VectorCursor<TRect<int> > (vtable 0x7F71CC)
template class VectorCursor<TRect<int>, VectorClass<TRect<int> > >;
// SYNTHETIC: GAMEMD 0x76F0B0 -- VectorCursor<MSSfxEntry*> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x76F0E0 -- VectorCursor<rc_ptr<Territory>> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x76F0F0 -- VectorCursor<MSAnim*> slot 1 (in-range test)
// SYNTHETIC: GAMEMD 0x76F100 -- VectorCursor<MSSfxEntry*> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x76F120 -- VectorCursor<rc_ptr<Territory>> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x76F140 -- VectorCursor<MSAnim*> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x76F160 -- VectorCursor<MSSfxEntry*> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x76F170 -- VectorCursor<MSSfxEntry*> slot 3 (decrement)
// SYNTHETIC: GAMEMD 0x76F180 -- VectorCursor<rc_ptr<Territory>> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x76F190 -- VectorCursor<rc_ptr<Territory>> slot 3 (decrement)
// SYNTHETIC: GAMEMD 0x76F1A0 -- VectorCursor<MSAnim*> slot 2 (increment)
// SYNTHETIC: GAMEMD 0x76F1B0 -- VectorCursor<MSAnim*> slot 3 (decrement)
// VectorCursor<MSSfxEntry*> (vtable 0x7F72C4)
template class VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*> >;

// VectorCursor<rc_ptr<Territory> > (vtable 0x7F72D8)
template class VectorCursor<rc_ptr<WorldDominationTour::Territory>, DynamicVectorClass<rc_ptr<WorldDominationTour::Territory> > >;

// VectorCursor<MSAnim*> (vtable 0x7F72EC)
template class VectorCursor<MSAnim*, DynamicVectorClass<MSAnim*> >;
