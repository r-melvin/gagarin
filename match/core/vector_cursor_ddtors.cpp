// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// VectorCursor<T, Container>: a small polymorphic cursor over a vector. RTTI
// names eight instantiations (".?AV?$VectorCursor@...") with one vtable each;
// every scalar deleting destructor stores its own instantiation's vtable,
// frees the object when bit 0 of the flag is set and returns `this`, so the
// destructor is an empty virtual one. These bodies are compiler output: the
// explicit instantiations compile the inline constructor, which emits each
// vtable and its `??_G`. No member is touched, so no layout is modelled.
// The element and container types are only named here, never defined.

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

// SYNTHETIC: GAMEMD 0x4F28C0
// VectorCursor<GraphicMenuItem*> (vtable 0x7EA644)
template class VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*> >;
// SYNTHETIC: GAMEMD 0x4F3FD0
// VectorCursor<unsigned int> (vtable 0x7EA6C8)
template class VectorCursor<unsigned int, DynamicVectorClass<unsigned int> >;
// SYNTHETIC: GAMEMD 0x765770
// VectorCursor<rc_ptr<Conflict> > (vtable 0x7F6F9C)
template class VectorCursor<rc_ptr<WorldDominationTour::Conflict>, DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict> > >;
// SYNTHETIC: GAMEMD 0x7669F0
// VectorCursor<rc_ptr<GameOption> > (vtable 0x7F702C)
template class VectorCursor<rc_ptr<WorldDominationTour::GameOption>, DynamicVectorClass<rc_ptr<WorldDominationTour::GameOption> > >;
// SYNTHETIC: GAMEMD 0x769DC0
// VectorCursor<TRect<int> > (vtable 0x7F71CC)
template class VectorCursor<TRect<int>, VectorClass<TRect<int> > >;
// SYNTHETIC: GAMEMD 0x76F100
// VectorCursor<MSSfxEntry*> (vtable 0x7F72C4)
template class VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*> >;
// SYNTHETIC: GAMEMD 0x76F120
// VectorCursor<rc_ptr<Territory> > (vtable 0x7F72D8)
template class VectorCursor<rc_ptr<WorldDominationTour::Territory>, DynamicVectorClass<rc_ptr<WorldDominationTour::Territory> > >;
// SYNTHETIC: GAMEMD 0x76F140
// VectorCursor<MSAnim*> (vtable 0x7F72EC)
template class VectorCursor<MSAnim*, DynamicVectorClass<MSAnim*> >;
