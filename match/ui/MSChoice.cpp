// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Original translation unit MSChoice.cpp. The name is the source-file string at 0x8304e0
//   in retail gamemd.exe v1.001, passed by the assert at 0x5cfa90 inside this object's
//   code range (0x5ced71-0x5d316f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The nine tail-jump thunks, ordered ascending by retail address.
//
// Retail RTTI names VectorClass/DynamicVectorClass over Cell, BaseNodeClass, TPoint3D<int>, Point2D,
// TRect<int> and DirtyAreaStruct. Element layouts and compare shapes are read from the FindItemIndex,
// Slot5, Slot6 and SetCapacity bodies; field names are placeholders.
//
// Retail RTTI TypeDescriptors 0x8303D8 and 0x830408 identify
// VectorClass<MapSelection*> and DynamicVectorClass<MapSelection*>; the latter's
// CHD names the former as its zero-offset base.
//
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830200 and 0x00830230 identify
// VectorClass<MapStage*> and DynamicVectorClass<MapStage*>; COLs 0x008069F0
// and 0x00806928 point at them, and the dynamic hierarchy (CHD 0x00806918,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EEAB4 and DynamicVectorClass<T> address
// point 0x007EEA94 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MapStage layout claim.
//
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX reproduces its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830558 and 0x00830580 identify
// VectorClass<MSAnim*> and DynamicVectorClass<MSAnim*>; COLs 0x00806D48 and
// 0x00806CB8 point at them, and the dynamic hierarchy (CHD 0x00806CA8, two
// base classes, BCD 0x00806C68 for the vector at zero offset) records the
// vector as its zero-offset base.
// VectorClass<T> address point 0x007EEC24 and DynamicVectorClass<T> address
// point 0x007EEC04 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MSAnim layout claim.
//
//   Provenance note: own-binary-via-Ghidra; retail TypeDescriptors/COLs and all 12
// entry-origin spans plus both address-point tables were confirmed directly.
// The dynamic deleting-dtor full span needs /GX disabled; with /GX, only that
// emitted wrapper is short. The base deleting dtor also matches with /GX.
// Vtable checks use recorded weak defaults and are conditional, not final-link proof.
//
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830500 and 0x00830528 identify
// VectorClass<MSSfx*> and DynamicVectorClass<MSSfx*>; COLs 0x00806D18 and
// 0x00806C50 point at them, and the dynamic hierarchy (CHD 0x00806C40, two
// base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EEC44 and DynamicVectorClass<T> address
// point 0x007EEBE4 are each seven-slot tables whose COL is at address-4; the
// words after each table's seventh slot are the next table's COL.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MSSfx layout claim.
//
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830268 and 0x00830298 identify
// VectorClass<MSSfxEntry*> and DynamicVectorClass<MSSfxEntry*>; COLs 0x00806A20
// and 0x00806990 point at them, and the dynamic hierarchy (CHD 0x00806980,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EEAF4 and DynamicVectorClass<T> address
// point 0x007EEA54 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MSSfxEntry layout claim.
//
//   Bytes matched against the user's retail gamemd.exe v1.001 across
//   0x5CEE60..0x5CF8D6. See the header for how the container's identity and
//   layout were read out of the image's runtime type information.
//
//   VTABLE:   GAMEMD 0x7EEAB4  VectorClass<MapStage*>
//   VTABLE:   GAMEMD 0x7EEAD4  VectorClass<MSAnimEntry*>  (+0x2C)
//   VTABLE:   GAMEMD 0x7EEAF4  VectorClass<MSSfxEntry*>   (+0x44)
//   GLOBAL:   GAMEMD 0x87E728  the campaign session pointer
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete (CRT; excluded from the match)

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/empty_function_family_methods.h"

#include "../core/tail_jmp_thunk_sweep.h"

#include "../core/trivial_tu153_methods.h"

#include "../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../_layout/cell.h"

template class DynamicVectorClass<Cell>;

 struct BaseNodeClass { int unknown_00; Cell unknown_04; unsigned char unknown_08; int unknown_0C; BaseNodeClass() {} BaseNodeClass(const BaseNodeClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const BaseNodeClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const BaseNodeClass& o) const { return !(*this==o); } };

template class DynamicVectorClass<BaseNodeClass>;

template<class T> struct TPoint3D { T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };

#include "../_layout/geometry2d.h"

template class DynamicVectorClass<Point2D>;

template class DynamicVectorClass<TRect<int> >;


#include "../_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;

#include "../core/vector_class_operations.h"
class MapSelection;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
// This specialization records the vector ABI, not the owning element class layout or original TU.
// No constructors were evidenced here. The size asserts describe these compiled vector models,
// not a complete owner object. Full spans match with /GX off; /GX shortens the dynamic
// scalar-deleting destructor. Vtable checks use conditional weak-default resolution, not final-link proof.

// VTABLE: GAMEMD 0x7EEB14 -- DynamicVectorClass<MapSelection*>.
template class DynamicVectorClass<MapSelection*>;

typedef VectorClass<MapSelection*> GgMapSelectionVector;
typedef DynamicVectorClass<MapSelection*> GgMapSelectionDynamicVector;
GG_STATIC_ASSERT(sizeof(MapSelection*) == 4);
GG_STATIC_ASSERT(sizeof(GgMapSelectionVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMapSelectionDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class MapStage;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<MapStage*>;

// VTABLE: GAMEMD 0x007EEAB4 -- VectorClass<MapStage*>.
// VTABLE: GAMEMD 0x007EEA94 -- DynamicVectorClass<MapStage*>.

typedef VectorClass<MapStage*> GgMapStageVector;
typedef DynamicVectorClass<MapStage*> GgMapStageDynamicVector;
GG_STATIC_ASSERT(sizeof(MapStage*) == 4);
GG_STATIC_ASSERT(sizeof(GgMapStageVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMapStageDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class MSAnim;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<MSAnim*>;

// VTABLE: GAMEMD 0x007EEC24 -- VectorClass<MSAnim*>.
// VTABLE: GAMEMD 0x007EEC04 -- DynamicVectorClass<MSAnim*>.

typedef VectorClass<MSAnim*> GgMSAnimVector;
typedef DynamicVectorClass<MSAnim*> GgMSAnimDynamicVector;
GG_STATIC_ASSERT(sizeof(MSAnim*) == 4);
GG_STATIC_ASSERT(sizeof(GgMSAnimVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMSAnimDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class MSAnimEntry;

template class DynamicVectorClass<MSAnimEntry*>;

// VTABLE: GAMEMD 0x007EEA74 -- DynamicVectorClass<MSAnimEntry*>.
// VTABLE: GAMEMD 0x007EEAD4 -- VectorClass<MSAnimEntry*>.
typedef VectorClass<MSAnimEntry*> GgMsAnimEntryVector;
typedef DynamicVectorClass<MSAnimEntry*> GgMsAnimEntryDynamicVector;
GG_STATIC_ASSERT(sizeof(MSAnimEntry*) == 4);
GG_STATIC_ASSERT(sizeof(GgMsAnimEntryVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMsAnimEntryDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class MSSfx;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<MSSfx*>;

// VTABLE: GAMEMD 0x007EEC44 -- VectorClass<MSSfx*>.
// VTABLE: GAMEMD 0x007EEBE4 -- DynamicVectorClass<MSSfx*>.

typedef VectorClass<MSSfx*> GgMSSfxVector;
typedef DynamicVectorClass<MSSfx*> GgMSSfxDynamicVector;
GG_STATIC_ASSERT(sizeof(MSSfx*) == 4);
GG_STATIC_ASSERT(sizeof(GgMSSfxVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMSSfxDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class MSSfxEntry;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<MSSfxEntry*>;

// VTABLE: GAMEMD 0x007EEAF4 -- VectorClass<MSSfxEntry*>.
// VTABLE: GAMEMD 0x007EEA54 -- DynamicVectorClass<MSSfxEntry*>.

typedef VectorClass<MSSfxEntry*> GgMSSfxEntryVector;
typedef DynamicVectorClass<MSSfxEntry*> GgMSSfxEntryDynamicVector;
GG_STATIC_ASSERT(sizeof(MSSfxEntry*) == 4);
GG_STATIC_ASSERT(sizeof(GgMSSfxEntryVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMSSfxEntryDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, CapacityIncrement) == 0x14);

#include "../map/map_stage_list_methods.h"


// Retail PAVMSTextEntry RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// Retail RTTI type descriptors name VectorClass<Point2D> and
// DynamicVectorClass<Point2D>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables). The
// element compare in operator== and FindItemIndex is Point2D's member-wise
// equality from geometry2d.h.

#include "../core/vector_class_operations.h"

class MSTextEntry;

// VTABLE: GAMEMD 0x7EEB94 -- VectorClass<MSTextEntry*>.
template class VectorClass<MSTextEntry*>;
typedef VectorClass<MSTextEntry*> GgMSTextEntryVectorClass;
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EEB34 -- DynamicVectorClass<MSTextEntry*>.
template class DynamicVectorClass<MSTextEntry*>;
typedef DynamicVectorClass<MSTextEntry*> GgMSTextEntryDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(MSTextEntry*) == 4);

#include "../core/vector_class_operations.h"
#include "../_layout/geometry2d.h"

template class DynamicVectorClass<Point2D>;

GG_STATIC_ASSERT(sizeof(VectorClass<Point2D>) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<Point2D>) == 0x18);

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CEDD0
// Build an empty container. The three vectors and the name string are built
// in declaration order, and then the body empties the two the constructor
// bothers to empty -- retail leaves the third alone, which is the direct
// evidence that the body is three statements and not a call to ClearAll.
MapStageList* MapStageList::Construct()
{
    Stages.Init();
    Name.Text.Init();
    Strings.Init();
    Titles.Init();

    Stages.Clear();
    Name.Text.Reset();
    Strings.Clear();
    return this;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CEE60
// Tear the container down: empty it first, then let the three vectors and the
// name string go in reverse declaration order, which is the order retail's
// stores walk back through (+0x44, +0x2C, +0x28, +0x00).
MapStageList::~MapStageList() throw()
{
    ClearAll();
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CF5F0
// Empty every list the container owns and put the drawing bounds back to the
// full 640x400 screen. Each of the three sweeps frees its elements one by one
// and then asks the vector itself to drop its block, and each walks a signed
// index against the live count reloaded every turn -- retail's `JL` on a
// reloaded `Count` is a plain indexed `for`, not a pointer walk.
//
// PARTIAL, 90.3% (65/72, multiset identical). Retail issues the four bounds
// stores before the second loop's first Count load; cl hoists that load above
// them. Per-loop counters and a `while` form for the second sweep score the
// same.
void MapStageList::ClearAll()
{
    int i;

    for (i = 0; i < Titles.Count; ++i) {
        Obj_007B4620* title = Titles.Vector[i];

        if (title != 0) {
            title->Destruct();
            ::operator delete(title);
        }
    }

    Titles.Clear();

    BoundsX = 0;
    BoundsY = 0;
    BoundsW = 640;
    BoundsH = 400;

    for (i = 0; i < Strings.Count; ++i) {
        Obj_007B4620* text = Strings.Vector[i];

        if (text != 0) {
            text->Destruct();
            ::operator delete(text);
        }
    }

    Strings.Clear();

    for (i = 0; i < Stages.Count; ++i) {
        MapStage* stage = Stages.Vector[i];

        if (stage != 0) {
            stage->Destruct();
            ::operator delete(stage);
        }
    }

    Stages.Clear();
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CF6B0
// Find the stage whose name matches, case-insensitively. Both sides are
// lower-cased into temporaries inside the loop, so the key is rebuilt on every
// turn exactly as retail does it; the two temporaries are released on both the
// hit and the miss path.
MapStage* MapStageList::FindByName(Obj_007B4620* key)
{
    if (key->At(0) != 0) {
        for (int i = 0; i < Stages.Count; ++i) {
            Obj_007B4620 wanted(*key);
            wanted.FUN_007B5B30();

            Obj_007B4620 candidate(Stages.Vector[i]->Name);
            candidate.FUN_007B5B30();

            if (wanted == candidate) {
                MapStage* hit = Stages.Vector[i];
                candidate.Destruct();
                wanted.Destruct();
                return hit;
            }

            candidate.Destruct();
            wanted.Destruct();
        }
    }

    return 0;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CF760
// The same search against each stage's title rather than its name. The only
// difference in retail is the `ADD ECX,4` that steps to the second string.
MapStage* MapStageList::FindByTitle(Obj_007B4620* key)
{
    if (key->At(0) != 0) {
        for (int i = 0; i < Stages.Count; ++i) {
            Obj_007B4620 wanted(*key);
            wanted.FUN_007B5B30();

            Obj_007B4620 candidate(Stages.Vector[i]->Title);
            candidate.FUN_007B5B30();

            if (wanted == candidate) {
                MapStage* hit = Stages.Vector[i];
                candidate.Destruct();
                wanted.Destruct();
                return hit;
            }

            candidate.Destruct();
            wanted.Destruct();
        }
    }

    return 0;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CF810
// The bounds-checked subscript. The index is a 16-bit quantity -- retail's
// `AND EAX,0xFFFF` is the parameter's own width, not a mask the source wrote --
// and the bound is the signed live count.
MapStage* MapStageList::GetAt(unsigned short index)
{
    if (Stages.Count <= index) {
        return 0;
    }

    return Stages.Vector[index];
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CF830
// Append through the vector's own virtual Add, which takes its argument by
// reference; the whole body is the address of the parameter and the indirect
// call.
int MapStageList::AddStage(MapStage* stage)
{
    return Stages.Add(stage);
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5CF840
// Find a title line by text, but only once a campaign session exists. Unlike
// the two stage searches this one lower-cases the stored line first and the
// caller's key second, which is the order retail's two constructor calls run
// in.
Obj_007B4620* MapStageList::FindTitle(Obj_007B4620* key)
{
    if (SessionExists()) {
        int i;

    for (i = 0; i < Titles.Count; ++i) {
            Obj_007B4620* line = Titles.Vector[i];

            Obj_007B4620 stored(*line);
            stored.FUN_007B5B30();

            Obj_007B4620 wanted(*key);
            wanted.FUN_007B5B30();

            if (stored == wanted) {
                wanted.Destruct();
                stored.Destruct();
                return line;
            }

            wanted.Destruct();
            stored.Destruct();
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x5D0580
void FUN_005D0580(void* self)
{
    FUN_007B46F0(self);
}

// FUNCTION: GAMEMD 0x005D0590
void FUN_005D0590()
{
}

// TEMPLATE: GAMEMD 0x5D05D0
// DynamicVectorClass<Point2D>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5D05F0
// VectorClass<Point2D>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x5D07F0
// VectorClass<Point2D>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x5D0950
// VectorClass<Point2D>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x5D09A0
// VectorClass<Point2D>::Slot5 (slot 5)
template class VectorClass<Point2D>;

// FUNCTION: GAMEMD 0x5D0610
// DynamicVectorClass<MSTextEntry*>::Clear

// FUNCTION: GAMEMD 0x5D0640
// DynamicVectorClass<MSTextEntry*>::Slot5

// FUNCTION: GAMEMD 0x5D0660
// VectorClass<MSTextEntry*>::Slot6

// FUNCTION: GAMEMD 0x5D0AE0
// VectorClass<MSTextEntry*>::operator==

// FUNCTION: GAMEMD 0x5D0B20
// VectorClass<MSTextEntry*>::SetCapacity

// FUNCTION: GAMEMD 0x5D0BD0
// VectorClass<MSTextEntry*>::Clear

// FUNCTION: GAMEMD 0x5D0C00
// VectorClass<MSTextEntry*>::FindItemIndex

// FUNCTION: GAMEMD 0x5D0C40
// VectorClass<MSTextEntry*>::Slot5

// FUNCTION: GAMEMD 0x5D0C60
// DynamicVectorClass<MSTextEntry*>::SetCapacity

// FUNCTION: GAMEMD 0x5D0D10
// DynamicVectorClass<MSTextEntry*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5D1760
// VectorClass<MSTextEntry*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5D17B0
// DynamicVectorClass<MSTextEntry*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5D0670
// DynamicVectorClass<MapSelection*>::Clear
// FUNCTION: GAMEMD 0x5D06A0
// DynamicVectorClass<MapSelection*>::Slot5
// FUNCTION: GAMEMD 0x5D06C0
// VectorClass<MapSelection*>::Slot6
// FUNCTION: GAMEMD 0x5D0D40
// VectorClass<MapSelection*>::operator==
// FUNCTION: GAMEMD 0x5D0D80
// VectorClass<MapSelection*>::SetCapacity
// FUNCTION: GAMEMD 0x5D0E30
// VectorClass<MapSelection*>::Clear
// FUNCTION: GAMEMD 0x5D0E60
// VectorClass<MapSelection*>::FindItemIndex
// FUNCTION: GAMEMD 0x5D0EA0
// VectorClass<MapSelection*>::Slot5
// FUNCTION: GAMEMD 0x5D0EC0
// DynamicVectorClass<MapSelection*>::SetCapacity
// FUNCTION: GAMEMD 0x5D0F70
// DynamicVectorClass<MapSelection*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x5D1800
// VectorClass<MapSelection*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x5D1850
// DynamicVectorClass<MapSelection*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EEBB4 -- VectorClass<MapSelection*>.
template class VectorClass<MapSelection*>;

// FUNCTION: GAMEMD 0x005D06D0
// FUNCTION: GAMEMD 0x005D0700
// FUNCTION: GAMEMD 0x005D0720
// FUNCTION: GAMEMD 0x005D0FA0
// FUNCTION: GAMEMD 0x005D0FE0
// FUNCTION: GAMEMD 0x005D1090
// FUNCTION: GAMEMD 0x005D10C0
// FUNCTION: GAMEMD 0x005D1100
// FUNCTION: GAMEMD 0x005D1120
// FUNCTION: GAMEMD 0x005D11D0
// FUNCTION: GAMEMD 0x005D18A0
// FUNCTION: GAMEMD 0x005D18F0
template class VectorClass<MapStage*>;

// FUNCTION: GAMEMD 0x005D0730
// FUNCTION: GAMEMD 0x005D0760
// FUNCTION: GAMEMD 0x005D0780
// FUNCTION: GAMEMD 0x005D1200
// FUNCTION: GAMEMD 0x005D1240
// FUNCTION: GAMEMD 0x005D12F0
// FUNCTION: GAMEMD 0x005D1320
// FUNCTION: GAMEMD 0x005D1360
// FUNCTION: GAMEMD 0x005D1380
// FUNCTION: GAMEMD 0x005D1430
// FUNCTION: GAMEMD 0x005D1940
// FUNCTION: GAMEMD 0x005D1990
template class VectorClass<MSAnimEntry*>;

// FUNCTION: GAMEMD 0x005D0790
// FUNCTION: GAMEMD 0x005D07C0
// FUNCTION: GAMEMD 0x005D07E0
// FUNCTION: GAMEMD 0x005D1460
// FUNCTION: GAMEMD 0x005D14A0
// FUNCTION: GAMEMD 0x005D1550
// FUNCTION: GAMEMD 0x005D1580
// FUNCTION: GAMEMD 0x005D15C0
// FUNCTION: GAMEMD 0x005D15E0
// FUNCTION: GAMEMD 0x005D1690
// FUNCTION: GAMEMD 0x005D19E0
// FUNCTION: GAMEMD 0x005D1A30
template class VectorClass<MSSfxEntry*>;

// FUNCTION: GAMEMD 0x005D0850
// VectorClass<Point2D>::SetCapacity
// FUNCTION: GAMEMD 0x005D09C0
// DynamicVectorClass<Point2D>::SetCapacity
// FUNCTION: GAMEMD 0x005D0AA0
// DynamicVectorClass<Point2D>::FindItemIndex
// VTABLE: GAMEMD 0x007EEB74 -- VectorClass<Point2D>.
// VTABLE: GAMEMD 0x007EEB54 -- DynamicVectorClass<Point2D>.
template class VectorClass<Point2D>;

// FUNCTION: GAMEMD 0x5D26F0
// Empty function. Vtable slot 2 of MSEngine (RTTI) and 1 derived vtable(s).
void Obj_005D26F0::FUN_005D26F0()
{
}

// FUNCTION: GAMEMD 0x5D2700
void* Obj_5D2700::FUN_5D2700(unsigned int flags)
{
    FUN_005D1B30(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x005D2720
// FUNCTION: GAMEMD 0x005D2750
// FUNCTION: GAMEMD 0x005D2770
// FUNCTION: GAMEMD 0x005D27E0
// FUNCTION: GAMEMD 0x005D2820
// FUNCTION: GAMEMD 0x005D28D0
// FUNCTION: GAMEMD 0x005D2900
// FUNCTION: GAMEMD 0x005D2940
// FUNCTION: GAMEMD 0x005D2960
// FUNCTION: GAMEMD 0x005D2A10
// FUNCTION: GAMEMD 0x005D2CA0
// FUNCTION: GAMEMD 0x005D2CF0
template class VectorClass<MSAnim*>;

// FUNCTION: GAMEMD 0x005D2780
// FUNCTION: GAMEMD 0x005D27B0
// FUNCTION: GAMEMD 0x005D27D0
// FUNCTION: GAMEMD 0x005D2A40
// FUNCTION: GAMEMD 0x005D2A80
// FUNCTION: GAMEMD 0x005D2B30
// FUNCTION: GAMEMD 0x005D2B60
// FUNCTION: GAMEMD 0x005D2BA0
// FUNCTION: GAMEMD 0x005D2BC0
// FUNCTION: GAMEMD 0x005D2C70
// FUNCTION: GAMEMD 0x005D2D40
// FUNCTION: GAMEMD 0x005D2D90
template class VectorClass<MSSfx*>;
