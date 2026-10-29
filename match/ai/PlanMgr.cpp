// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit PlanMgr.cpp. The name is the source-file string at 0x836bd4
//   in retail gamemd.exe v1.001, passed by the assert at 0x63747e inside this object's
//   code range (0x6333d0-0x63f4bf). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Leaf bodies that repeat byte for byte at several addresses and touch only
// globals: store of the ECX argument, indexed table reads, constant stores,
// and a two-value test. Each address binds to its own global (named by
// retail address, typed only as far as the instructions show) and was
// verified separately. Record structs name only the fields the bodies read.
//
// Append of a pointer to a global DynamicVectorClass, repeated for three
// element types: the canonical inline AddItem expanded at each site, with the
// result discarded. The element types are named only by placeholder; the
// global vectors are named by retail address.
//
// Polygon scan conversion into per-row {left, right} spans. Both entries
// are __fastcall free functions: 0x63F080 takes the polygon {count +0x00,
// points +0x04 (8-byte x/y pairs)} in ECX and the span buffer {height
// +0x00, top row +0x04, spans +0x08} in EDX; 0x63F2E0 walks one edge with
// x1/y1 in ECX/EDX and x2, y2, side (1 = left column), skip-first-row and
// the span cursor on the stack (`ret 0x14`). The span block is allocated on
// demand as height * 8 + 0x640 bytes (operator new 0x7C8E17).
//
// The nine tail-jump thunks, ordered ascending by retail address.
//
//   siblings.
//
//   The retail class identity and slot binding are confirmed from the binary:
//   each annotated body occupies slot 3 of the listed VectorClass<T> vtable.
//   Slot 3 is Clear, called on a live vector by retail (including the
//   ToolTipManager constructor at 0x724000); these bodies clear owned storage
//   and reset vector bookkeeping without reseating a vptr. The source template
//   is VectorClass<T>::Clear, and the element argument is recovered from RTTI.
//
//   The 68 remaining addresses are bound to VectorClass<T> tables;
//   each table's complete object locator and body address were read from the
//   retail binary. No destructor identity is inferred from the byte pattern.
//
//   KNOWN LIMITATION -- these compiled template instantiations are grouped
//   here for per-function verification. The retail binary does not establish
//   their original translation-unit grouping or final linker placement.
//   This sweep file does not establish an integrated engine link order.
// Int, ToolTip and TechnoType pointer entries use native specialization TUs.
//
// Retail RTTI TypeDescriptors 0x836890 and 0x8368C0 identify
// VectorClass<EventClass*> and DynamicVectorClass<EventClass*>; the latter's
// CHD names the former as its zero-offset base.
// Complete entry spans bind these methods. Original TUs and standalone
// constructors are unestablished; the derived deleting body needs GX off.
//
// Retail RTTI type descriptors name VectorClass<PlanningBranchClass*> and
// DynamicVectorClass<PlanningBranchClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Retail RTTI type descriptors name VectorClass<PlanningMemberClass*> and
// DynamicVectorClass<PlanningMemberClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x008368F8 and 0x00836930 identify
// VectorClass<PlanningNodeClass*> and DynamicVectorClass<PlanningNodeClass*>;
// COLs 0x00807F08 and 0x00807ED8 point at them, and the dynamic hierarchy (CHD
// 0x00807EC8, two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EFE64 and DynamicVectorClass<T> address
// point 0x007EFE44 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete PlanningNodeClass layout claim.
//
// Retail RTTI type descriptors name VectorClass<PlanningTokenClass*> and
// DynamicVectorClass<PlanningTokenClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.

#include "../core/vector_ctor_pod_family_methods.h"
#include "techno_class_clear_tokens_methods.h"

#include "techno_class_planning_node_helpers.h"

int DAT_00AC4B84[24];

#include "techno_class_planning_token_methods.h"

extern int DAT_00816108;
#include "../_layout/rec12_008b4040.h"
extern Rec12_008B4040 DAT_008B4040[];
#include "../_layout/rec12_008b3f38.h"
extern Rec12_008B3F38 DAT_008B3F38[];
#include "../_layout/rec12_008b3fc8.h"
extern Rec12_008B3FC8 DAT_008B3FC8[];
extern unsigned char DAT_00A9FAB4;
extern unsigned char DAT_00ABCD58;
extern int DAT_00ABED0C;
extern int DAT_00ABF168[];
#include "../_layout/rec28_0082d028.h"
extern Rec28_0082D028 DAT_0082D028[];
extern int DAT_00AC4C90;
extern int DAT_007F0248[];
#include "../_layout/rec16_007f0998.h"
extern Rec16_007F0998 DAT_007F0998[];
extern int DAT_00B0CB78[];
extern int DAT_008449F8[];
extern unsigned char DAT_00B0FE58;
extern unsigned char DAT_008464AC;
extern int DAT_00B780A0;

#include "../core/vector_class_operations.h"

struct Obj_005D4E70;
extern DynamicVectorClass<Obj_005D4E70*> DAT_00ABFC90;





#include <stdlib.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct PolyPoint_0063F080
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(PolyPoint_0063F080) == 8);

struct Polygon_0063F080
{
    int Count;                     // +0x00
    PolyPoint_0063F080* Points;    // +0x04
};
GG_STATIC_ASSERT(offsetof(Polygon_0063F080, Count) == 0x00);
GG_STATIC_ASSERT(offsetof(Polygon_0063F080, Points) == 0x04);

struct ScanSpan_0063F080
{
    int Left;    // +0x00
    int Right;   // +0x04
};
GG_STATIC_ASSERT(sizeof(ScanSpan_0063F080) == 8);

struct ScanBuffer_0063F080
{
    int Height;                    // +0x00
    int Top;                       // +0x04
    ScanSpan_0063F080* Spans;      // +0x08
};
GG_STATIC_ASSERT(offsetof(ScanBuffer_0063F080, Height) == 0x00);
GG_STATIC_ASSERT(offsetof(ScanBuffer_0063F080, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(ScanBuffer_0063F080, Spans) == 0x08);

void FUN_0063F2E0(int x1, int y1, int x2, int y2, int side, int skip, ScanSpan_0063F080** cursor);

#include "../core/rect_contains_point_methods.h"

#include "../core/tail_jmp_thunk_sweep.h"

#include "../core/trivial_tu180_b_methods.h"

#include "../core/trivial_tu180_methods.h"

#include "../core/vector_class.h"

#include "../_layout/house_class.h"

// ---------------------------------------------------------------------------
// The element types, declared exactly as their RTTI manglings require: a `V`
// tag becomes `class`, a `U` tag `struct`, a `W4` tag an enum, and a nested or
// scoped name gets its enclosing scope. None is defined -- the body only ever
// handles `T*`, so an incomplete type is all the template needs. A scope
// written `namespace` below could equally have been a class: MSVC mangles the
// two identically, so the binary cannot decide it.
// ---------------------------------------------------------------------------
class AITriggerTypeClass;
class AbstractClass;
class AbstractTypeClass;
struct AcceleratorTracker;
class AircraftClass;
class AircraftTypeClass;
struct AngerStruct;
class AnimClass;
class AnimTypeClass;
class BuildingClass;
class BuildingLightClass;
class BuildingTypeClass;
class BulletTypeClass;
struct ButtonFadeEffect;
class CCINIClass;
class CampaignClass;
class CellClass;
class ColorScheme;
class ConvertClass;
class CoopCampaignClass;
struct CrossDissolveEffect;
struct DamageGroup;
struct DirtyAreaStruct;
#include "../core/disk_id.h"
class DiskLaserClass;
template<class T0> class DynamicVectorClass;
class EBolt;
class EMPulseClass;
class EgoClass;
class EventClass;
class FactoryClass;
class FileEntryClass;
#include "../_layout/fogged_object_class.h"
class FootClass;
struct GlobalPacketType;
class GraphicMenuItem;
class HSVClass;
struct HWND__;
template<class T0, class T1> struct HashObject;
class HashString;
class HouseTypeClass;
struct IConnectionPoint;
class InfantryTypeClass;
class IonBlastClass;
#include "../_layout/iso_tile_type_class.h"
struct KamikazeControl;
class LaserDrawClass;
#include "../_layout/light_source_class.h"
class LineTrail;
struct MPlayerScoreType;
class MSAnim;
class MSAnimEntry;
class MSSfx;
class MSSfxEntry;
class MSTextEntry;
class MapRegionClass;
class MapSelection;
class MapStage;
class MovieHandle;
class MultiMission;
class MultiplayerGameMode;
class MultiplayerTeam;
struct NodeNameType;
class ObjectTypeClass;
class OverlayClass;
class OverlayTypeClass;
class OwnerTalkClass
{
public:
    struct ConnectionListStruct;
};
class ParasiteClass;
class ParticleClass;
class ParticleSystemClass;
class ParticleSystemTypeClass;
class ParticleTypeClass;
enum PassabilityType { PassabilityType_placeholder };
class PhoneEntryClass;
class PlanningBranchClass;
class PlanningMemberClass;
class PlanningNodeClass;
class PlanningTokenClass;
class Point2D;
class RGBClass;
class RadBeam;
class RadSiteClass;
struct RadarTrackingStruct;
class SchemeNode;
struct ScoutStruct;
class ScriptTypeClass;
class ShadowControlClass;
class SideClass;
class SlaveManagerClass;
class SmudgeClass;
class SmudgeTypeClass;
class SpawnManagerClass;
class SpotLightClass;
class SubTitle;
struct SubzoneConnectionStruct;
class SuperClass;
class SuperWeaponTypeClass;
class SwizzlePointerClass;
class TActionClass;
class TEventClass;
template<class T0> class TRect;
class TagClass;
class TagTypeClass;
class TaskForceClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TemporalClass;
class TerrainClass;
class TerrainTypeClass;
struct ThemeControl;
class TiberiumClass;
class ToolTip;
class TriggerClass;
class TriggerTypeClass;
class TubeClass;
struct UndoInfoStruct;
class UnitClass;
class UnitTypeClass;
class VeinholeMonsterClass;
class VocClass;
class VoxClass;
class VoxelAnimTypeClass;
class WaveClass;
class WaypointPathClass;
#include "../network/transport/winsock_interface_class.h"
namespace WorldDominationTour
{
    class Centroid;
    class Map
    {
        struct AnimationPalette;
    };
}  // namespace WorldDominationTour
struct ZoneConnectionClass;
struct _DDSURFACEDESC;
struct _WIN32_FIND_DATAA;
struct tConnInfoStruct;
struct tagCONNECTDATA;

// ---------------------------------------------------------------------------
// The instantiations, in ascending retail-address order.
// ---------------------------------------------------------------------------

// Actual-template layout assertions are in vector_class_layout_asserts.cpp.

#include "../core/vector_class_operations.h"
class EventClass;

// FUNCTION: GAMEMD 0x0063EFB0
// vtable constant: 0x7EFE64
GG_VECTOR_CTOR_POD_BODY(VectorClass_0063EFB0, PodElem4, 0x7EFE64)

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// VTABLE: GAMEMD 0x7EFE04 -- DynamicVectorClass<EventClass*>.
template class DynamicVectorClass<EventClass*>;

typedef VectorClass<EventClass*> GgEventVector;
typedef DynamicVectorClass<EventClass*> GgEventDynamicVector;
GG_STATIC_ASSERT(sizeof(EventClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgEventVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEventVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEventVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEventVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEventVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEventVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgEventDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class PlanningBranchClass;

template class DynamicVectorClass<PlanningBranchClass*>;

GG_STATIC_ASSERT(sizeof(PlanningBranchClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningBranchClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningBranchClass* >) == 0x18);

#include "../core/vector_class_operations.h"

class PlanningMemberClass;

template class DynamicVectorClass<PlanningMemberClass*>;

GG_STATIC_ASSERT(sizeof(PlanningMemberClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningMemberClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningMemberClass* >) == 0x18);

#include "../core/vector_class_operations.h"

class PlanningNodeClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<PlanningNodeClass*>;

// VTABLE: GAMEMD 0x007EFE64 -- VectorClass<PlanningNodeClass*>.
// VTABLE: GAMEMD 0x007EFE44 -- DynamicVectorClass<PlanningNodeClass*>.

typedef VectorClass<PlanningNodeClass*> GgPlanningNodeClassVector;
typedef DynamicVectorClass<PlanningNodeClass*> GgPlanningNodeClassDynamicVector;
GG_STATIC_ASSERT(sizeof(PlanningNodeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgPlanningNodeClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgPlanningNodeClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class PlanningTokenClass;

template class DynamicVectorClass<PlanningTokenClass*>;

GG_STATIC_ASSERT(sizeof(PlanningTokenClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningTokenClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningTokenClass* >) == 0x18);

#include "../core/vector_remove_item_family_methods.h"

#include "../renderer/pixel_pack_methods.h"

#include <stdlib.h>
#include "../ui/planning_manager_rbutton_methods.h"


// ---- from the former planning_node_methods.cpp ----
// PlanMgr.cpp continued (0x6347A0 onward; "D:\\ra2mdpost\\PlanMgr.cpp" at 0x836BD4): the PlanningNodeClass and
// PlanningTokenClass methods and helpers that follow the block in planning_manager.cpp, in retail address order.
// Built with /Ob1: only inline-declared bodies (class-body members, templates) are expanded; every
// out-of-class function stays a call, as in retail. Where retail expands 0x6339E0, 0x634510, 0x6357D0 or
// 0x638C40 this file uses private inline copies (PlanningRectAround, PlanningRectInflate,
// PlanningMissionTargetOk) because the out-of-line bodies belong to other rows.
// Loops with an early exit are written `if (n > 0) do { ... } while (...)`, which is the shape retail has.

#include "planning_manager.h"
#include "../_layout/house_class.h"
#include "../_layout/object_type_class.h"
#include "../renderer/dsurface_class.h"
#include "../ui/input_controls/mouse_ww_mouse_class.h"

#include "../_layout/tactical.h"

// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0x886FA0 -- the view origin added to every converted point.
extern Point2D DAT_00886FA0;

// FUNCTION: GAMEMD 0x633BC0 (decl; reloc) -- the coordinate a mission event points at.
CoordStruct* FUN_00633BC0(CoordStruct* out, const EventClass& event);

inline CoordStruct PlanningCoordOf(const EventClass& event)
{
    CoordStruct tmp;
    return *FUN_00633BC0(&tmp, event);
}

// FUNCTION: GAMEMD 0x6339E0 (decl; reloc) -- the view point of a world coordinate.
Point2D* FUN_006339E0(Point2D* out, const CoordStruct& coord);

// FUNCTION: GAMEMD 0x634510 (decl; reloc) -- a size-by-size rectangle centred on a point.
RectangleStruct* FUN_00634510(RectangleStruct* out, int size, Point2D center);

// GLOBAL: GAMEMD 0xAC4CF4 / 0xAC4CF5 -- planning-mode flags.
extern bool DAT_00AC4CF4;
extern bool DAT_00AC4CF5;
// GLOBAL: GAMEMD 0xAC4CCC / 0xAC4C38 / 0xAC4BF0 -- the current node pointers (cleared with the node's destructor).
extern PlanningNodeClass* DAT_00AC4CCC;
extern PlanningNodeClass* DAT_00AC4C38;
extern PlanningNodeClass* DAT_00AC4BF0;
// GLOBAL: GAMEMD 0xAC4C68 / 0xAC4C6C -- anchor X / Y; 0xAC4CB0 -- cleared on every right-button release.
extern Point2D DAT_00AC4C68;

extern bool DAT_00AC4CB0;

// FUNCTION: GAMEMD 0x652230 (decl; reloc) -- queue one event (ECX = the event).
void FUN_00652230(EventClass* event);

// GLOBAL: GAMEMD 0xAC4CF6 -- set while the selection pass below runs.
extern bool DAT_00AC4CF6;
// GLOBAL: GAMEMD 0xAC4B84 -- 24 per-house pending-request counters.
extern int DAT_00AC4B84[24];
// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern HouseClass* DAT_00A83D4C;


// The rules object (RulesInstance, 0x8871E0).
#include "../core/rules_class.h"

// FUNCTION: GAMEMD 0x750920 (decl; reloc) -- VocClass::PlayGlobal(index, flags, volume, controller).
// The volume is declared ahead of the pan so that `MOV EDX,0x2000` falls between the two pushes, as in retail.
void* FUN_00750920(int voc, float volume, unsigned int pan, void* controller);

// GLOBAL: GAMEMD 0xAC4B80 -- the object notified (slot 0) on entering and leaving planning mode.
class PlanningNotify
{
public:
    virtual void vf_0(int id, int arg);
};
extern PlanningNotify* DAT_00AC4B80;

// FUNCTION: GAMEMD 0x6521C0 (decl; reloc) -- queue an event passed by value (RET 0x70).
void FUN_006521C0(EventClass event);

// STRING: GAMEMD 0x836BD4 -- "D:\\ra2mdpost\\PlanMgr.cpp"
extern const char STR_00836BD4[];
// STRING: GAMEMD 0x836C80 -- "MSG:PlanningModeNoGuardArea"
extern const char STR_00836C80[];
// GLOBAL: GAMEMD 0xAC4C08 -- set once the "no guard area" message has been shown.
extern bool DAT_00AC4C08;
// GLOBAL: GAMEMD 0xA8ECC8 -- the selection list's count.
extern int DAT_00A8ECC8;

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- fetch a message by key (key, 0, file, line).
int FUN_00734E60(const char* key, int zero, const char* file, int line);

// FUNCTION: GAMEMD 0x730A90 (decl; reloc) -- show a message.
void FUN_00730A90(int text, int flags);

// The planner's view object, of which only +0x14 is read here.
struct PlanningView
{
    char unknown_00[0x14];
    int unknown_14;   // +0x14 (15 is the state 0x63A440 tests)
};

// STRING: GAMEMD 0x836AD4 -- "Loop Branch [%d]; Member count[%d]; Origin event location[%d, %d, %d]\n"
extern const char STR_00836AD4[];
// STRING: GAMEMD 0x836B20 -- " Member [%s]; Cell location[%d, %d]\n"
extern const char STR_00836B20[];
// STRING: GAMEMD 0x836B48 -- "Branch [%d]; Member count[%d]; Origin event location[%d, %d, %d]\n"
extern const char STR_00836B48[];

// A size-by-size rectangle centred on a point (0x634510, expanded where it is not called).
inline RectangleStruct* PlanningRectAround(RectangleStruct* out, int size, Point2D center)
{
    int half = -(size / 2);
    Point2D corner = center;
    corner.X += half;
    corner.Y += half;
    RectangleStruct rect;
    rect.X = corner.X;
    rect.Y = corner.Y;
    rect.Width = size;
    rect.Height = size;
    *out = rect;
    return out;
}

// 0x6357D0 expanded where it is not called.
inline void PlanningRectInflate(RectangleStruct* rect, int amount)
{
    int twice = amount + amount;
    if (twice < 0 && (twice >= rect->Width || twice >= rect->Height)) {
        rect->X = 0;
        rect->Y = 0;
        rect->Width = 0;
        rect->Height = 0;
        return;
    }
    rect->X -= amount;
    rect->Y -= amount;
    rect->Width += twice;
    rect->Height += twice;
}

// 0x638C40 expanded where it is not called.
inline bool PlanningMissionTargetOk(int mission, TargetClass target)
{
    if (mission == 1 || mission == 11) {
        if (target.RTTI == 11) {
            return true;
        }
        if (mission == 11 && target.RTTI == 0) {
            return true;
        }
    }
    return false;
}

// 0x638C20 is defined in trivial_tu180_methods.cpp; its body is expanded here.
inline int PlanningMissionIsMove(int mission)
{
    return mission == 7 || mission == 8 || mission == 9;
}

// FUNCTION: GAMEMD 0x634290
//
// PlanningNodeClass::FUN_00634290 -- linear scan of this node's member array for
// the one whose owner word matches `owner`; returns its index, or -1 when the
// node is empty or nothing matches. The search sits under `if (count > 0)`
// (retail's `OR EAX,0xffffffff` seeds the -1 answer before the guard) rather
// than folding the empty case into the loop test, so an empty node returns -1
// without ever touching Members.Items.
// PARTIAL (92.3%, 24/26): a `for` over the entries with a `break` on the first
// owner match, written `count > i` as the loop test, gives retail's single
// guarded loop with the walk as a raw entry-pointer increment, the `OR EAX,-1`
// seed and the unrotated test. The one residual instruction is the loop test's
// direction: retail has `CMP EDX,ESI; JL`, this has `CMP ESI,EDX; JG` (the
// `i < count` spelling gives the retail compare but swaps the EDX/ESI roles,
// 69.2%).
int PlanningNodeClass::FUN_00634290(TechnoClass* owner)
{
    int index = -1;
    int count = this->Members.Count;
    int i = 0;
    if (count > 0) {
        PlanningMemberClass** entries = this->Members.Items;
        for (; count > i; i++, entries++) {
            if ((*entries)->Owner == owner) {
                index = i;
                break;
            }
        }
    }
    return index;
}

// FUNCTION: GAMEMD 0x6347A0
PlanningBranchClass* PlanningNodeClass::FUN_006347A0(int index)
{
    return Branches.Items[index];
}

// FUNCTION: GAMEMD 0x6347B0
// The branch `techno` is on, or none.
PlanningBranchClass* PlanningNodeClass::FUN_006347B0(TechnoClass* techno)
{
    int branch = MemberOf(techno)->unknown_08;
    PlanningBranchClass* result = 0;
    if (branch != -1) {
        result = Branches.Items[branch];
    }
    return result;
}

// FUNCTION: GAMEMD 0x634800
// Returns the address of a member.
int* Obj_00634800::FUN_00634800()
{
    return &unknown_38;
}

// FUNCTION: GAMEMD 0x634810
CoordStruct PlanningNodeClass::FUN_00634810(int branch)
{
    return PlanningCoordOf(Branches.Items[branch]->Event);
}

// FUNCTION: GAMEMD 0x634850
CoordStruct PlanningNodeClass::FUN_00634850()
{
    return PlanningCoordOf(Loop().Event);
}

// FUNCTION: GAMEMD 0x634880
Point2D* PlanningNodeClass::FUN_00634880(Point2D* out, int branch)
{
    CoordStruct tmp;
    CoordStruct coord = *FUN_00633BC0(&tmp, Branches.Items[branch]->Event);
    Point2D point;
    DAT_00887324->FUN_006D2140(&coord, &point);
    point.X += DAT_00886FA0.X;
    point.Y += DAT_00886FA0.Y;
    *out = point;
    return out;
}

// FUNCTION: GAMEMD 0x6348F0
Point2D* PlanningNodeClass::FUN_006348F0(Point2D* out)
{
    CoordStruct tmp;
    CoordStruct coord = *FUN_00633BC0(&tmp, Loop().Event);
    Point2D point;
    DAT_00887324->FUN_006D2140(&coord, &point);
    point.X += DAT_00886FA0.X;
    point.Y += DAT_00886FA0.Y;
    *out = point;
    return out;
}

// FUNCTION: GAMEMD 0x634950
// Stores its argument in a member.
void Obj_00634950::FUN_00634950()
{
    unknown_1C = 1;
}

// FUNCTION: GAMEMD 0x634960
// Member getter (byte).
unsigned char Obj_00634960::FUN_00634960() const
{
    return unknown_1C;
}

// FUNCTION: GAMEMD 0x634970
void PlanningNodeClass::FUN_00634970()
{
    FUN_00635120();
    int count = Members.Count;
    for (int i = 0; i < count; i++) {
        FUN_00634E10(Members.Items[i]);
    }
    FUN_006349B0();
    unknown_1C = false;
}

// FUNCTION: GAMEMD 0x6349B0
void PlanningNodeClass::FUN_006349B0()
{
    int count = Members.Count;
    for (int i = 0; i < count; i++) {
        PlanningMemberClass* member = Members.Items[i];
        TechnoClass* techno = member->Owner;
        PlanningTokenClass* token = techno->FUN_00705D20();
        if (token->Nodes.FindItemIndex(this) == token->unknown_94) {
            member->unknown_0C = true;
            PlanningBranchClass* loop = &Loop();
            if (++loop->unknown_70 == 1) {
                PlanningNodeClass* last = techno->FUN_00705D20()->LastNode();
                int index = last->FUN_00634290(techno);
                PlanningMemberClass* source = index == -1 ? 0 : last->Members.Items[index];
                loop->Event = *source->Event;
            }
        }
    }
    unknown_B0 = -1;
    if (Loop().unknown_70 != 0) {
        EventClass origin = Loop().Event;
        int branches = Branches.Count;
        int j = 0;
        if (branches > 0) {
            do {
                EventClass event = Branches.Items[j]->Event;
                CoordStruct a = PlanningCoordOf(origin);
                CoordStruct b = PlanningCoordOf(event);
                if (a.X == b.X && a.Y == b.Y && a.Z == b.Z) {
                    unknown_B0 = j;
                    break;
                }
                j++;
            } while (j < branches);
        }
    }
}

// FUNCTION: GAMEMD 0x634B20
// Log every branch with its members, then the loop branch.
void PlanningNodeClass::FUN_00634B20()
{
    int branches = Branches.Count;
    for (int i = 0; i < branches; i++) {
        PlanningBranchClass* branch = Branches.Items[i];
        int members = branch->unknown_70;
        EventClass event = branch->Event;
        CoordStruct tmp;
        CoordStruct at = *FUN_00633BC0(&tmp, event);
        FUN_004068E0(STR_00836B48, i, members, at.X, at.Y, at.Z);
        int count = Members.Count;
        for (int j = 0; j < count; j++) {
            PlanningMemberClass* member = Members.Items[j];
            if (member->unknown_08 == i) {
                TechnoClass* techno = member->Owner;
                const char* name = techno->vf_34()->ID;
                CellStruct cell = techno->vf_110();
                FUN_004068E0(STR_00836B20, name, cell.X, cell.Y);
            }
        }
    }
    int loops = Loop().unknown_70;
    if (loops > 0) {
        EventClass event = Loop().Event;
        CoordStruct tmp;
        CoordStruct at = *FUN_00633BC0(&tmp, event);
        FUN_004068E0(STR_00836AD4, unknown_B0, loops, at.X, at.Y, at.Z);
        int count = Members.Count;
        for (int j = 0; j < count; j++) {
            PlanningMemberClass* member = Members.Items[j];
            if (member->unknown_0C) {
                TechnoClass* techno = member->Owner;
                const char* name = techno->vf_34()->ID;
                CellStruct cell = techno->vf_110();
                FUN_004068E0(STR_00836B20, name, cell.X, cell.Y);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x634CC0
// The branch of this node that starts where the node before it on `techno`'s token leaves off, or -1.
int PlanningNodeClass::FUN_00634CC0(TechnoClass* techno)
{
    PlanningTokenClass* token = techno->FUN_00705D20();
    int index = token->Nodes.FindItemIndex(this);
    PlanningNodeClass* before;
    if (index == -1) {
        before = 0;
    } else if (token->Nodes.Count == 1) {
        before = this;
    } else {
        index--;
        if (index < 0) {
            index = token->Nodes.Count - 1;
        }
        before = token->FUN_00636E60(index);
    }
    if (before != techno->FUN_00705D20()->LastNode()) {
        int member = before->FUN_00634290(techno);
        EventClass event = *(member == -1 ? 0 : before->Members.Items[member])->Event;
        int count = Branches.Count;
        if (count) {
            CoordStruct at;
            {
                CoordStruct tmp;
                at = *FUN_00633BC0(&tmp, event);
            }
            int i = 0;
            if (count > 0) {
                do {
                    PlanningBranchClass* branch = Branches.Items[i];
                    if (branch->unknown_70) {
                        EventClass other = branch->Event;
                        CoordStruct tmp2;
                        CoordStruct to = *FUN_00633BC0(&tmp2, other);
                        if (at.X == to.X && at.Y == to.Y && at.Z == to.Z) {
                            return i;
                        }
                    }
                    i++;
                } while (i < count);
            }
        }
    }
    return -1;
}

// The append expanded in this block: the count is bumped before the store (the out-of-line copy at
// 0x63E540 takes its index first).
inline bool PlanningListAdd(DynamicVectorClass<PlanningNodeClass*>& list, PlanningNodeClass* item)
{
    if (list.Count >= list.Capacity) {
        if ((list.IsAllocated || list.Capacity == 0) && list.CapacityIncrement > 0) {
            if (!list.SetCapacity(list.Capacity + list.CapacityIncrement, 0)) {
                return false;
            }
        } else {
            return false;
        }
    }
    int index = list.Count++;
    list.Items[index] = item;
    return true;
}
inline bool PlanningListAdd(DynamicVectorClass<EventClass*>& list, EventClass* item)
{
    if (list.Count >= list.Capacity) {
        if ((list.IsAllocated || list.Capacity == 0) && list.CapacityIncrement > 0) {
            if (!list.SetCapacity(list.Capacity + list.CapacityIncrement, 0)) {
                return false;
            }
        } else {
            return false;
        }
    }
    int index = list.Count++;
    list.Items[index] = item;
    return true;
}

// FUNCTION: GAMEMD 0x635060
// Take `member` off its branch (and its active mark).
void PlanningNodeClass::FUN_00635060(PlanningMemberClass* member)
{
    if (member->unknown_0C) {
        member->unknown_0C = false;
        if (--unknown_A8 == 0) {
            unknown_B0 = -1;
        }
    }
    if (member->unknown_08 != -1) {
        PlanningBranchClass* branch = Branches.Items[member->unknown_08];
        branch->unknown_74 = -1;
        unknown_B4 = -1;
        if (--branch->unknown_70 == 0 && this != 0 && !unknown_1C) {
            unknown_1C = true;
            PlanningListAdd(PlanningLists::DAT_00AC4C98, this);
        }
    }
    member->unknown_08 = -1;
}

// FUNCTION: GAMEMD 0x635120
void PlanningNodeClass::FUN_00635120()
{
    int branches = Branches.Count;
    for (int i = 0; i < branches; i++) {
        delete Branches.Items[i];
    }
    Branches.Clear();
    int members = Members.Count;
    for (int j = 0; j < members; j++) {
        PlanningMemberClass* member = Members.Items[j];
        member->unknown_08 = -1;
        member->unknown_0C = false;
    }
    Loop().unknown_70 = 0;
    unknown_B0 = -1;
}

// FUNCTION: GAMEMD 0x6351A0
bool PlanningNodeClass::FUN_006351A0(TechnoClass* techno)
{
    PlanningTokenClass* token = techno->FUN_00705D20();
    return token->Nodes.FindItemIndex(this) == token->unknown_94;
}

// FUNCTION: GAMEMD 0x6351E0
void PlanningNodeClass::FUN_006351E0(PlanningMemberClass* member)
{
    member->unknown_0C = false;
    if (--unknown_A8 == 0) {
        unknown_B0 = -1;
    }
}

// FUNCTION: GAMEMD 0x635210
void PlanningNodeClass::FUN_00635210()
{
    unknown_B0 = -1;
    if (Loop().unknown_70 != 0) {
        EventClass origin = Loop().Event;
        int branches = Branches.Count;
        int j = 0;
        if (branches > 0) {
            do {
                EventClass event = Branches.Items[j]->Event;
                CoordStruct a = PlanningCoordOf(origin);
                CoordStruct b = PlanningCoordOf(event);
                if (a.X == b.X && a.Y == b.Y && a.Z == b.Z) {
                    unknown_B0 = j;
                    break;
                }
                j++;
            } while (j < branches);
        }
    }
}

// FUNCTION: GAMEMD 0x6352D0
void PlanningNodeClass::FUN_006352D0()
{
    int count = Members.Count;
    for (int i = 0; i < count; i++) {
        TechnoClass* techno = Members.Items[i]->Owner;
        if (!techno->IsSelected) {
            techno->vf_83();
        }
    }
}

// FUNCTION: GAMEMD 0x635310
void PlanningNodeClass::FUN_00635310()
{
    int count = Members.Count;
    for (int i = 0; i < count; i++) {
        TechnoClass* techno = Members.Items[i]->Owner;
        if (techno->IsSelected) {
            techno->vf_84();
        }
    }
}

// FUNCTION: GAMEMD 0x72AD20 (decl; reloc) -- the tactical view's screen rectangle (written to `out`).
RectangleStruct* FUN_0072AD20(RectangleStruct* out);
#include "../renderer/composite_surface.h"

// FUNCTION: GAMEMD 0x635560
// PARTIAL: best 44.2%. Retail keeps the 0x634510 result pointer in ESI and
// writes the +4 inflate straight into the box; this build copies first.
// Tried: explicit field writes (40.2%), copy then inflate (40.4%).
// Draw the node's marker: a box around the first member's target, drawn three
// times, each one pixel further in.
void PlanningNodeClass::FUN_00635560(unsigned int color)
{
    RectangleStruct clip;
    {
        RectangleStruct tmp;
        clip = *FUN_0072AD20(&tmp);
    }
    Point2D center;
    RectangleStruct around;
    RectangleStruct box = *FUN_00634510(&around, 8, *FUN_006339E0(&center, PlanningCoordOf(*Members.Items[0]->Event)));
    PlanningRectInflate(&box, 4);
    for (int i = 0; i < 3; i++) {
        DAT_0088731C->DrawRectEx(&clip, &box, color);
        PlanningRectInflate(&box, -1);
    }
}

// FUNCTION: GAMEMD 0x6357D0 (defined below)
void FUN_006357D0(RectangleStruct* rect, int amount);

// FUNCTION: GAMEMD 0x6357D0
// Grow the rectangle by `amount` on every side; shrinking past its size empties it.
void FUN_006357D0(RectangleStruct* rect, int amount)
{
    int twice = amount + amount;
    if (twice < 0 && (twice >= rect->Width || twice >= rect->Height)) {
        rect->X = 0;
        rect->Y = 0;
        rect->Width = 0;
        rect->Height = 0;
        return;
    }
    rect->X -= amount;
    rect->Y -= amount;
    rect->Width += twice;
    rect->Height += twice;
}

// FUNCTION: GAMEMD 0x635DB0
void PlanningNodeClass::FUN_00635DB0(bool arg)
{
    unknown_B4 = -1;
    if (arg) {
        int count = Branches.Count;
        for (int i = 0; i < count; i++) {
            Branches.Items[i]->unknown_74 = -1;
        }
        Loop().unknown_74 = -1;
    }
}

// FUNCTION: GAMEMD 0x635DF0
// The marker rectangle of the first member's order, grown by 4 (6339E0/634510 expanded).
RectangleStruct PlanningNodeClass::FUN_00635DF0()
{
    CoordStruct tmp;
    CoordStruct coord = *FUN_00633BC0(&tmp, *Members.Items[0]->Event);
    Point2D point;
    DAT_00887324->FUN_006D2140(&coord, &point);
    point.X += DAT_00886FA0.X;
    point.Y += DAT_00886FA0.Y;
    int size = 8;
    RectangleStruct rect;
    rect.X = point.X - size / 2;
    rect.Y = point.Y - size / 2;
    rect.Width = size;
    rect.Height = size;
    rect.X -= 4;
    rect.Y -= 4;
    rect.Width += 8;
    rect.Height += 8;
    return rect;
}

// FUNCTION: GAMEMD 0x635E90
// The same rectangle grown by 4 twice (6339E0/634510 called).
RectangleStruct PlanningNodeClass::FUN_00635E90()
{
    CoordStruct tmp;
    CoordStruct coord = *FUN_00633BC0(&tmp, *Members.Items[0]->Event);
    Point2D point;
    RectangleStruct rect;
    RectangleStruct bounds = *FUN_00634510(&rect, 8, *FUN_006339E0(&point, coord));
    bounds.X -= 4;
    bounds.Y -= 4;
    bounds.Width += 8;
    bounds.Height += 8;
    bounds.X -= 4;
    bounds.Y -= 4;
    bounds.Width += 8;
    bounds.Height += 8;
    return bounds;
}

// FUNCTION: GAMEMD 0x635F20
PlanningTokenClass::PlanningTokenClass(TechnoClass* owner)
    : unknown_1C(false), unknown_8C(-1), unknown_90(-1), unknown_94(-1), unknown_98(false), unknown_99(false)
{
    Owner = owner;
}

// FUNCTION: GAMEMD 0x636110
// Member getter (dword).
int Obj_00636110::FUN_00636110() const
{
    return unknown_00;
}

// FUNCTION: GAMEMD 0x636520
// Stores its argument in a member.
void Obj_00636520::FUN_00636520()
{
    unknown_1C = 1;
}

// FUNCTION: GAMEMD 0x636530
// Stores its argument in a member.
void Obj_00636530::FUN_00636530()
{
    unknown_1C = 0;
}

// FUNCTION: GAMEMD 0x636540
// Member getter (byte).
unsigned char Obj_00636540::FUN_00636540() const
{
    return unknown_1C;
}

// FUNCTION: GAMEMD 0x636550
// Branching.
int Obj_00636550::FUN_00636550()
{
    return unknown_00->unknown_AC == 0x1C || unknown_00->unknown_B4 == 0x1C;
}

// FUNCTION: GAMEMD 0x636570
// Branching.
int Obj_00636570::FUN_00636570()
{
    return unknown_14 > 0 && (unknown_8C == -1 || unknown_8C > 0);
}

// FUNCTION: GAMEMD 0x636DA0
// Branching.
unsigned char Obj_00636DA0::FUN_00636DA0(int a1)
{
    if (unknown_8C == -1)
    {
        return 0;
    }
    return a1 >= unknown_8C;
}

// FUNCTION: GAMEMD 0x636DC0
int PlanningTokenClass::FUN_00636DC0()
{
    return Nodes.Count;
}

// FUNCTION: GAMEMD 0x636DD0
// Branching.
int Obj_00636DD0::FUN_00636DD0()
{
    if (unknown_8C == -1)
    {
        return unknown_14;
    }
    return unknown_8C;
}

// FUNCTION: GAMEMD 0x636DE0
// Branching.
int Obj_00636DE0::FUN_00636DE0()
{
    if (unknown_8C == -1)
    {
        return 0;
    }
    return unknown_14 - unknown_8C;
}

// FUNCTION: GAMEMD 0x636E00
void PlanningTokenClass::FUN_00636E00(PlanningNodeClass* node)
{
    Nodes.AddItem(node);
    if (unknown_8C == -1) {
        unknown_8C = Nodes.Count - 1;
    }
}

// FUNCTION: GAMEMD 0x636E60
PlanningNodeClass* PlanningTokenClass::FUN_00636E60(int index)
{
    if (Nodes.Count == 0) {
        return 0;
    }
    if (index >= Nodes.Count) {
        if (unknown_94 > 0 || unknown_94 == 0) {
            index = (index - unknown_94) % unknown_90 + unknown_94;
        } else {
            return 0;
        }
    }
    if (index < 0 || index >= Nodes.Count) {
        return 0;
    }
    return Nodes.Items[index];
}

// FUNCTION: GAMEMD 0x636EB0
PlanningNodeClass* PlanningTokenClass::FUN_00636EB0()
{
    return LastNode();
}

// FUNCTION: GAMEMD 0x636EE0
int PlanningTokenClass::FUN_00636EE0(PlanningNodeClass* node)
{
    return Nodes.FindItemIndex(node);
}

// FUNCTION: GAMEMD 0x636F00
EventClass PlanningTokenClass::FUN_00636F00(int node)
{
    PlanningNodeClass* target = Nodes.Items[node];
    TechnoClass* owner = Owner;
    return *target->MemberOf(owner)->Event;
}

// FUNCTION: GAMEMD 0x636F60
EventClass PlanningTokenClass::FUN_00636F60()
{
    return unknown_1D;
}

// FUNCTION: GAMEMD 0x636F80
PlanningNodeClass* PlanningTokenClass::FUN_00636F80()
{
    if (unknown_94 == -1) {
        return 0;
    }
    return Nodes.Items[unknown_94];
}

// FUNCTION: GAMEMD 0x636FA0
// Stores several members; pops its stack arguments.
void Obj_00636FA0::FUN_00636FA0(int a1, int a2)
{
    unknown_90 = a1;
    unknown_94 = a2;
    unknown_98 = 1;
}

// FUNCTION: GAMEMD 0x636FC0
// Member getter (dword).
int Obj_00636FC0::FUN_00636FC0() const
{
    return unknown_90;
}

// FUNCTION: GAMEMD 0x636FD0
// Member getter (dword).
int Obj_00636FD0::FUN_00636FD0() const
{
    return unknown_94;
}

// FUNCTION: GAMEMD 0x636FE0
// Branching.
int Obj_00636FE0::FUN_00636FE0()
{
    return unknown_94 > 0 || unknown_94 == 0;
}

// FUNCTION: GAMEMD 0x637000
// Returns a comparison result.
bool Obj_00637000::FUN_00637000() const
{
    return unknown_94 > 0;
}

// FUNCTION: GAMEMD 0x637010
// Returns a comparison result.
bool Obj_00637010::FUN_00637010() const
{
    return unknown_94 == 0;
}

// FUNCTION: GAMEMD 0x637020
// Member getter (byte).
unsigned char Obj_00637020::FUN_00637020() const
{
    return unknown_98;
}

// FUNCTION: GAMEMD 0x637030
// Member getter (byte).
unsigned char Obj_00637030::FUN_00637030() const
{
    return unknown_99;
}

// FUNCTION: GAMEMD 0x637040
void PlanningTokenClass::FUN_00637040()
{
    unknown_94--;
    unknown_94 = unknown_94 > 0 ? unknown_94 : 0;
}

// FUNCTION: GAMEMD 0x637060
// Stores to a global.
void FUN_00637060(PlanningNotify* a1)
{
    DAT_00AC4B80 = a1;
}

// FUNCTION: GAMEMD 0x637070
void FUN_00637070()
{
    DAT_00AC4CF4 = false;
    DAT_00AC4CF5 = false;
    DAT_00AC4CCC = 0;
    DAT_00AC4C38 = 0;
    DAT_00AC4BF0 = 0;
    Point2D zero;
    zero.X = 0;
    zero.Y = 0;
    DAT_00AC4C68 = zero;
    DAT_00AC4CB0 = false;
}

// FUNCTION: GAMEMD 0x6370A0
void FUN_006370A0(void* self)
{
    FUN_006370B0(self);
}

// FUNCTION: GAMEMD 0x637550
// Queue and free every event in the list, last first.
void FUN_00637550()
{
    for (int i = PlanningLists::DAT_00AC4B48.Count - 1; i >= 0; i--) {
        EventClass* event = PlanningLists::DAT_00AC4B48.Items[i];
        FUN_00652230(event);
        PlanningLists::DAT_00AC4B48.Delete(i);
        delete event;
    }
}

// FUNCTION: GAMEMD 0x6375B0
// Keep a copy of the event (a mission event is marked 2 as a planning event).
void FUN_006375B0(EventClass* event)
{
    EventClass* copy = new EventClass;
    *copy = *event;
    if (copy->Type == EVENT_MEGAMISSION) {
        copy->Data.MegaMission.IsPlanningEvent = 2;
    }
    PlanningListAdd(PlanningLists::DAT_00AC4B48, copy);
}

// FUNCTION: GAMEMD 0x637640
// Take the node off the three node lists and forget it as a current node.
void FUN_00637640(PlanningNodeClass* node)
{
    PlanningLists::DAT_00AC4C98.RemoveItem(node);
    PlanningLists::DAT_00AC4B30.RemoveItem(node);
    PlanningLists::DAT_00AC4C18.RemoveItem(node);
    if (DAT_00AC4CCC == node) {
        DAT_00AC4CCC = 0;
    }
    if (DAT_00AC4C38 == node) {
        DAT_00AC4C38 = 0;
    }
    if (DAT_00AC4BF0 == node) {
        DAT_00AC4BF0 = 0;
    }
}

// FUNCTION: GAMEMD 0x637750
void FUN_00637750(PlanningTokenClass* token)
{
    if (!DAT_00AC4CF5) {
        PlanningLists::DAT_00AC4C78.RemoveItem(token);
    }
}

// FUNCTION: GAMEMD 0x6377B0
void FUN_006377B0(TechnoClass* techno)
{
    int house = techno->Owner->ArrayIndex;
    if (techno->Owner->IsControlledByCurrentPlayer() && DAT_00A83D4C != 0) {
        house = DAT_00A83D4C->ArrayIndex;
    }
    if (house >= 0 && house < 24) {
        int pending = DAT_00AC4B84[house] - 1;
        DAT_00AC4B84[house] = pending < 0 ? 0 : pending;
    }
    PlanningLists::DAT_00AC4C40.RemoveItem(techno);
}

// FUNCTION: GAMEMD 0x637840
void FUN_00637840(TechnoClass* techno)
{
    if (DAT_00AC4CF6) {
        return;
    }
    DAT_00AC4CF6 = true;
    if (DAT_00AC4CF4) {
        PlanningTokenClass* token = techno->FUN_00705D20();
        if (token) {
            PlanningNodeClass* last = token->LastNode();
            if (last) {
                int count = last->Members.Count;
                for (int i = 0; i < count; i++) {
                    TechnoClass* member = last->Members.Items[i]->Owner;
                    if (!member->IsSelected) {
                        member->vf_83();
                    }
                }
            }
        }
    }
    DAT_00AC4CF6 = false;
}

// FUNCTION: GAMEMD 0x6378B0
void PlanningNodeClass::FUN_006378B0()
{
    if (this != 0 && !unknown_1C) {
        unknown_1C = true;
        PlanningListAdd(PlanningLists::DAT_00AC4C98, this);
    }
}

// FUNCTION: GAMEMD 0x637920
// Rebuild every node on the list, then empty the list.
void FUN_00637920()
{
    int count = PlanningLists::DAT_00AC4C98.Count;
    for (int i = 0; i < count; i++) {
        PlanningNodeClass* node = PlanningLists::DAT_00AC4C98.Items[i];
        node->FUN_00635120();
        int members = node->Members.Count;
        for (int j = 0; j < members; j++) {
            node->FUN_00634E10(node->Members.Items[j]);
        }
        node->FUN_006349B0();
        node->unknown_1C = false;
    }
    PlanningLists::DAT_00AC4C98.Clear();
}

// FUNCTION: GAMEMD 0x6379C0
void FUN_006379C0()
{
    if (!DAT_00AC4CF4) {
        RulesClass* rules = RulesInstance;
        DAT_00AC4CF4 = true;
        FUN_00750920(rules->unknown_1D4, 1.0f, 0x2000, 0);
        if (DAT_00AC4B80 != 0) {
            DAT_00AC4B80->vf_0(0x11C7, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x637A10
void FUN_00637A10()
{
    if (DAT_00AC4CF4) {
        EventClass event(DAT_00A83D4C->ArrayIndex, 0x2B);
        FUN_006521C0(event);
        DAT_00AC4CCC = 0;
        DAT_00AC4C38 = 0;
        DAT_00AC4BF0 = 0;
        DAT_00AC4CF4 = false;
        FUN_00750920(RulesInstance->unknown_1E0, 1.0f, 0x2000, 0);
        if (DAT_00AC4B80 != 0) {
            DAT_00AC4B80->vf_0(0x11C8, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x637D00
void PlanningNodeClass::FUN_00637D00()
{
    EventClass origin = *Members.Items[0]->Event;
    TargetClass* target;
    if (origin.Data.MegaMission.Target.RTTI) {
        target = &origin.Data.MegaMission.Target;
    } else if (origin.Data.MegaMission.Follow.RTTI) {
        target = &origin.Data.MegaMission.Follow;
    } else if (origin.Data.MegaMission.Destination.RTTI) {
        target = &origin.Data.MegaMission.Destination;
    } else {
        return;
    }
    TargetAbstract* object = target->FUN_006E6E20();
    if (object) {
        TargetClass id;
        EventClass event(DAT_00A83D4C->ArrayIndex, 0x2C, *id.FUN_006E6AB0(object));
        FUN_006521C0(event);
    }
}

// FUNCTION: GAMEMD 0x637DB0
// Branching.
bool FUN_00637DB0(int a1)
{
    if (DAT_00AC4CF4 == 0 || a1 != 4)
    {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x637DD0
void FUN_00637DD0(EventClass event)
{
    if (event.Type == EVENT_MEGAMISSION) {
        event.Data.MegaMission.IsPlanningEvent = 1;
        FUN_006521C0(event);
    }
}

// FUNCTION: GAMEMD 0x6385C0
//
// Advance this unit along its planning token. The token must exist, hold at
// least one node, have a usable +0x8C (-1 or positive) and not already be
// stepping (+0x1C). The unit is queued mission 0x1C, the token builds the next
// 0x6F-byte record, a heap copy of it (kind 4 forced to sub-kind 2) is
// appended to the global record list, and the token is marked as stepping.
bool TechnoClass::TryNextPlanningTokenNode()
{
    PlanningTokenClass* token = this->FUN_00705D20();
    if (token
        && token->Nodes.Count > 0
        && (token->unknown_8C == -1 || token->unknown_8C > 0)
        && !token->unknown_1C) {
        this->vf_122(0x1C, true);

        EventClass rec = token->FUN_00636590();
        EventClass* copy = new EventClass;
        *copy = rec;
        if (copy->Type == 4) {
            copy->Data.MegaMission.IsPlanningEvent = 2;
        }
        PlanningListAdd(PlanningLists::DAT_00AC4B48, copy);

        token->unknown_1C = 1;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6386E0
//
// PARTIAL: 95.5% (107/112) -- retail tests the gate's +0x1D byte through
// MOVSX EAX,byte ptr / TEST EAX,EAX; plain `gate->At_01D == 0` compiles to
// MOV AL,byte ptr / TEST AL,AL, which also shortens three forward jumps.
//
// TechnoClass::ClearPlanningTokens — tear down every planning node hanging off
// the unit's planning token. Nothing happens without a token; the gating record
// (when one is supplied and its +0x1D byte is set) and an empty node list both
// skip straight to clearing the token's +0x1C flag. Otherwise each node's entry
// for the token's owner is unhooked, its payload and the entry itself are freed
// back to the game heap, and a node left with nothing at +0x10 is deleted. If
// the list was not empty to begin with, the owner's sector (or the global
// override at 0xA83D4C when the sector says so) is refreshed and the token's
// owner is pushed onto the list at 0xAC4C40. Finally the token's sub-object is
// reset through its slot 0x0C, the three coordinate fields at +0x8C..+0x94 go
// to -1 and the two flag bytes at +0x98/+0x99 are cleared.
void Techno_006386E0::ClearPlanningTokens(Record_006386E0* gate)
{
    if (this == 0) {
        return;
    }

    Token_006386E0* token = this->FUN_00705D20();
    if (token == 0) {
        return;
    }

    void* slot;

    if ((gate == 0 || gate->At_01D == 0) && token->NodeCount > 0) {
        Token_006386E0* list = this->FUN_00705D20();
        if (list != 0) {
        int count = list->NodeCount;
        bool wasEmpty = (count == 0);

        for (int i = 0; i < count; i++) {
            Node_006386E0* node = list->Nodes[i];
            Owner_006386E0* owner = list->Owner;
            int index = node->FUN_00634290(owner);
            Entry_006386E0* entry;
            if (index == -1) {
                entry = 0;
            } else {
                entry = node->Entries[index];
            }
            slot = entry;
            if (entry != 0) {
                node->FUN_00635060(slot);
                GameDelete_006386E0(((Entry_006386E0*)slot)->At_004);
                node->FUN_0063DFD0(&slot);
                GameDelete_006386E0(slot);
                if (node->At_010 == 0 && node != 0) {
                    node->FUN_0063D9C0(1);
                }
            }
        }

        if (!wasEmpty) {
            slot = list->Owner;
            HouseClass* house = ((Owner_006386E0*)slot)->At_21C;
            int index = house->ArrayIndex;
            if (house->IsControlledByCurrentPlayer() && DAT_00A83D4C != 0) {
                index = DAT_00A83D4C->ArrayIndex;
            }
            FUN_00639F80(index);
            DAT_00AC4C40.FUN_0063E900(&slot);
        }

        (list->Sub.*list->Sub.Vtbl->At_00C)();
        list->At_08C = -1;
        list->At_090 = -1;
        list->At_094 = -1;
        list->At_098 = 0;
        list->At_099 = 0;
        }
    }

    token->At_01C = 0;
}

// FUNCTION: GAMEMD 0x00638A20
void FUN_00638A20(PlanningNodeClass* item)
{
    DynamicVectorClass<PlanningNodeClass*>& v = PlanningLists::DAT_00AC4C18;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = item;
}

// FUNCTION: GAMEMD 0x638B50
// Branching.
int FUN_00638B50(int a1)
{
    return (unsigned char)a1 == 9 || (unsigned char)a1 == 6 || (unsigned char)a1 == 7;
}

// FUNCTION: GAMEMD 0x638C20
// Branching.
int FUN_00638C20(int a1)
{
    return a1 == 7 || a1 == 8 || a1 == 9;
}

// FUNCTION: GAMEMD 0x638C40
// Whether a mission/target pair is one the planner takes (mission 1 or 11 against a type-11 target, or
// mission 11 against none).
bool FUN_00638C40(int mission, TargetClass target)
{
    if (mission == 1 || mission == 11) {
        if (target.RTTI == 11) {
            return true;
        }
        if (mission == 11 && target.RTTI == 0) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x638C70
// Whether this unit's current mission is one the planner takes (5, or the 0x638C40 cases against its target).
bool FUN_00638C70(TechnoClass* techno)
{
    if (techno == 0) {
        return false;
    }
    int mission = techno->vf_97();
    if (mission == 5) {
        return true;
    }
    TargetClass target;
    target.FUN_006E6AB0(techno->Target);
    return PlanningMissionTargetOk(mission, target);
}

// FUNCTION: GAMEMD 0x00638DC0
void FUN_00638DC0(PlanningNodeClass* item)
{
    DynamicVectorClass<PlanningNodeClass*>& v = PlanningLists::DAT_00AC4B30;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = item;
}

// FUNCTION: GAMEMD 0x638E20
void FUN_00638E20()
{
    PlanningLists::DAT_00AC4C18.Clear();
}

// GLOBAL: GAMEMD 0xAC4C3C -- the node under the cursor that cannot be made current.
extern PlanningNodeClass* DAT_00AC4C3C;

// FUNCTION: GAMEMD 0x638E60
// Track the node under the mouse: the first listed node whose marker box holds
// the cursor becomes current when it is the player's own and may be picked;
// otherwise it is only remembered at 0xAC4C3C.
void FUN_00638E60()
{
    if (DAT_00AC4CB0) {
        return;
    }
    int x = WWMouseClassInstance->vf_11();
    int y = WWMouseClassInstance->vf_12();
    PlanningNodeClass* hit;
    int count = PlanningLists::DAT_00AC4C18.Count;
    for (int i = 0; i < count; i++) {
        hit = PlanningLists::DAT_00AC4C18.Items[i];
        Point2D center;
        RectangleStruct tmp;
        RectangleStruct box = *FUN_00634510(&tmp, 8, *hit->FUN_00634400(&center));
        FUN_006357D0(&box, 4);
        if (x >= box.X && x < box.X + box.Width && y >= box.Y && y < box.Y + box.Height) {
            goto found;
        }
    }
    hit = 0;
found:
    if (hit != DAT_00AC4CCC) {
        DAT_00AC4C3C = 0;
        if (hit != 0
            && (hit->Members.Items[0]->Owner->Owner != DAT_00A83D4C
                || (DAT_00AC4C38 != 0 && DAT_00AC4C38 != hit)
                || hit->FUN_0063AC70() != -1)) {
            DAT_00AC4C3C = hit;
            hit = 0;
        }
        DAT_00AC4CCC = hit;
        if (hit) {
            hit->FUN_00634B20();
        }
    }
}

// FUNCTION: GAMEMD 0x639470
// The node on the list whose first order points at `coord`.
PlanningNodeClass* FUN_00639470(CoordStruct coord)
{
    int count = PlanningLists::DAT_00AC4C18.Count;
    int i = 0;
    if (count > 0) {
        do {
            PlanningNodeClass* node = PlanningLists::DAT_00AC4C18.Items[i];
            CoordStruct tmp;
            CoordStruct at = *FUN_00633BC0(&tmp, *node->Members.Items[0]->Event);
            if (at.X == coord.X && at.Y == coord.Y && at.Z == coord.Z) {
                return node;
            }
            i++;
        } while (i < count);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x639E30
// PARTIAL: 25.0%, same instruction multiset; retail keeps `first` in ECX and
// spills the second count, this build moves `first` to EDX. Tried: ternary
// counts (25.7%, two extra jumps), nested returns (21.6%, SETE).
// Whether two tokens' plans meet: true when neither has any nodes, false when
// only one has; otherwise each token's last node must list the other token's
// unit as a member.
bool FUN_00639E30(PlanningTokenClass* first, PlanningTokenClass* second)
{
    if (first == 0 && second == 0) {
        return true;
    }
    int firstCount = 0;
    if (first) {
        firstCount = first->Nodes.Count;
    }
    int secondCount = 0;
    if (second) {
        secondCount = second->Nodes.Count;
    }
    if (firstCount == 0 && secondCount == 0) {
        return true;
    }
    if (firstCount == 0 || secondCount == 0) {
        return false;
    }
    PlanningNodeClass* firstLast = first->NodeAt(firstCount - 1);
    PlanningNodeClass* secondLast = second->NodeAt(secondCount - 1);
    if (firstLast->MemberIndex(second->Owner) == -1) {
        return false;
    }
    if (secondLast->MemberIndex(first->Owner) == -1) {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x639F60
void FUN_00639F60(int house)
{
    if (house >= 0 && house < 24) {
        DAT_00AC4B84[house]++;
    }
}

// FUNCTION: GAMEMD 0x639F80
//
// FUN_00639F80 -- decrement the pending-request counter of a house index
// (ECX), clamped at 0 (not -1: the retail formula is `(v-1)<0 ? 0 : v-1`,
// i.e. `max(v-1, 0)`). Out of [0, 24) it is a no-op. The branchless clamp (`DEC`/`SETS`/`DEC`/`AND`)
// reproduces once the ternary's answer (0, not -1) is right and it lands in
// a fresh local rather than back into the variable that fed the comparison.
void FUN_00639F80(int house)
{
    if (house >= 0 && house < 24) {
        int dec = DAT_00AC4B84[house] - 1;
        int clamped = (dec < 0) ? 0 : dec;
        DAT_00AC4B84[house] = clamped;
    }
}

// FUNCTION: GAMEMD 0x639FB0
int FUN_00639FB0(int house)
{
    bool valid = house >= 0 && house < 24;
    int count = 0;
    if (valid) {
        count = DAT_00AC4B84[house];
    }
    return count;
}

// FUNCTION: GAMEMD 0x63A0D0
void FUN_0063A0D0()
{
    if (!DAT_00AC4C08) {
        DAT_00AC4C08 = true;
        int text = FUN_00734E60(STR_00836C80, 0, STR_00836BD4, 0xCA1);
        FUN_00730A90(text, 0x1E0);
        FUN_00750920(RulesInstance->unknown_700, 1.0f, 0x2000, 0);
    }
}

// STRING: GAMEMD 0x836D0C -- "MSG:PlanningModeLoopHelp"
extern const char STR_00836D0C[];
// STRING: GAMEMD 0x836CF0 -- "MSG:PlanningModeDeleteHelp"
extern const char STR_00836CF0[];
// GLOBAL: GAMEMD 0xAC4BF4 -- how many times each planning help message has been shown.
extern int DAT_00AC4BF4[];

// FUNCTION: GAMEMD 0x63A1B0
// Show the loop (3) or delete (4) help message the first time it is wanted, and count the request.
void __fastcall FUN_0063A1B0(int kind)
{
    if (DAT_00AC4BF4[kind] < 1) {
        if (kind == 3) {
            int text = FUN_00734E60(STR_00836D0C, 0, STR_00836BD4, 0xCA1);
            FUN_00730A90(text, 0x1E0);
        } else if (kind == 4) {
            int text = FUN_00734E60(STR_00836CF0, 0, STR_00836BD4, 0xCA1);
            FUN_00730A90(text, 0x1E0);
        }
        DAT_00AC4BF4[kind]++;
    }
}

// FUNCTION: GAMEMD 0x63A210
// Stores, then tail-calls.
void Obj_0063A210::FUN_0063A210()
{
    int c0 = FUN_00734E60(this, 0, DAT_00836BD4, 0xCA1);
    FUN_00730A90(c0, 0x1E0);
}

// FUNCTION: GAMEMD 0x63A230
// Show a planning message once (the shared "shown" latch), then play the planning sound.
void __fastcall FUN_0063A230(const char* key)
{
    if (!DAT_00AC4C08) {
        DAT_00AC4C08 = true;
        int text = FUN_00734E60(key, 0, STR_00836BD4, 0xCA1);
        FUN_00730A90(text, 0x1E0);
        FUN_00750920(RulesInstance->unknown_700, 1.0f, 0x2000, 0);
    }
}

// FUNCTION: GAMEMD 0x63A440
// The order's verdict for `view`: 0 when this kind of order is not placed, else 2 or -1 by its state.
int FUN_0063A440(PlanningView* view, EventClass* event)
{
    int mission = event->Data.MegaMission.Mission;
    if (PlanningMissionIsMove(mission)) {
        return 0;
    }
    TargetClass target = event->Data.MegaMission.Target;
    if (PlanningMissionTargetOk(mission, target)) {
        return 0;
    }
    return view->unknown_14 == 15 ? 2 : -1;
}

// FUNCTION: GAMEMD 0x63A4A0
// Stores to a global.
void FUN_0063A4A0(int a1)
{
    DAT_00AC4C90 = a1;
}

// FUNCTION: GAMEMD 0x63AAC0
void __stdcall FUN_0063AAC0(int x, int y)
{
    DAT_00AC4CB0 = true;
    Point2D none;
    none.X = -1;
    none.Y = -1;
    DAT_00AC4C68 = none;
    if (DAT_00AC4CF4 && DAT_00A8ECC8 <= 0) {
        Point2D anchor;
        anchor.X = x;
        anchor.Y = y;
        DAT_00AC4C68 = anchor;
    }
}

// FUNCTION: GAMEMD 0x63AB00
//
// Right-button release in planning mode. The drag flag is always cleared;
// then, if planning mode is on, nothing at 0xA8ECC8 is outstanding, and a
// token is pending, a release within 3 pixels of the anchor on both axes
// drops the token.
void __stdcall FUN_0063AB00(int x, int y)
{
    DAT_00AC4CB0 = false;

    if (DAT_00AC4CF4
        && DAT_00A8ECC8 <= 0
        && DAT_00AC4BF0 != 0
        && abs(x - DAT_00AC4C68.X) <= 3
        && abs(y - DAT_00AC4C68.Y) <= 3) {
        DAT_00AC4BF0 = 0;
    }
}

// FUNCTION: GAMEMD 0x63AD30
// Stores to a global.
void FUN_0063AD30(PlanningNodeClass* a1)
{
    DAT_00AC4C38 = a1;
}

// FUNCTION: GAMEMD 0x63AD40
// Returns a global (dword).
PlanningNodeClass* __cdecl FUN_0063AD40()
{
    return DAT_00AC4C38;
}

// FUNCTION: GAMEMD 0x63B050
// The object the order points at: its target, else its follow object, else its destination.
TargetAbstract* FUN_0063B050(EventClass* event)
{
    TargetAbstract* object = 0;
    if (event->Data.MegaMission.Target.RTTI) {
        object = event->Data.MegaMission.Target.FUN_006E6E20();
    } else if (event->Data.MegaMission.Follow.RTTI) {
        object = event->Data.MegaMission.Follow.FUN_006E6E20();
    } else if (event->Data.MegaMission.Destination.RTTI) {
        object = event->Data.MegaMission.Destination.FUN_006E6E20();
    }
    return object;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063B090
void FUN_0063B090()
{
    DAT_00AC4BF0 = 0;
}

// FUNCTION: GAMEMD 0x63CA80
// The coordinate an order points at, taken from `object` when the order names none.
CoordStruct* FUN_0063CA80(CoordStruct* out, const EventClass& event, TargetAbstract* object)
{
    CoordStruct coord;
    {
        CoordStruct tmp;
        coord = *FUN_00633BC0(&tmp, event);
    }
    if (coord.X == -1 && coord.Y == -1 && coord.Z == -1 && object) {
        coord = object->vf_22();
    }
    *out = coord;
    return out;
}

// GLOBAL: GAMEMD 0xA83CD9 -- the colour a planning marker is drawn in normally.
extern ColorStruct DAT_00A83CD9;
// GLOBAL: GAMEMD 0xA80220 -- white (0xFF, 0xFF, 0xFF), the colour of a selected or current-node member.
extern ColorStruct DAT_00A80220;

// The native pixel colour a planning marker for `techno` is drawn in: the
// highlight colour when the unit belongs to the current node (or, with no
// current node, when it is selected), otherwise the normal colour. Retail
// keeps it out of line at 0x63D0F0 and expands it in 0x63D2D0.
inline unsigned int PlanningMarkerColor(TechnoClass* techno)
{
    unsigned int color = PackPixel(DAT_00A83CD9);
    if (techno) {
        unsigned int highlight = PackPixel(DAT_00A80220);
        if (DAT_00AC4BF0) {
            if (DAT_00AC4BF0->MemberIndex(techno) != -1) {
                return highlight;
            }
        } else if (techno->IsSelected) {
            color = highlight;
        }
    }
    return color;
}

// FUNCTION: GAMEMD 0x63D0F0
unsigned int FUN_0063D0F0(TechnoClass* techno)
{
    return PlanningMarkerColor(techno);
}

// FUNCTION: GAMEMD 0x63D2D0
// The marker colour of a node's first member.
unsigned int FUN_0063D2D0(PlanningNodeClass* node)
{
    return PlanningMarkerColor(node->Members.Items[0]->Owner);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63D500
// Branching.
int Obj_0063D500::FUN_0063D500()
{
    int c0 = vf_97();
    if (c0 == 0xB)
    {
        return FUN_00731CE0();
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63D520
// Branching.
int Obj_0063D520::FUN_0063D520()
{
    int c0 = vf_301();
    if (c0 == 0x1D)
    {
        return FUN_00731CD0();
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63D540
// Branching.
int FUN_0063D540(Obj_0063D540* a1, int a2)
{
    int t1 = a1->unknown_0C;
    if (t1 == 0xB)
    {
        return FUN_00731CE0(a1, a2);
    }
    if (t1 == 0x1D)
    {
        return FUN_00731CD0(a1, a2);
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63DAD0
//
// Pack a raw 8-bit-per-channel {R,G,B} triple into the display's native pixel
// format: each channel is shifted right into a byte, then left into place.
unsigned int PackPixel_0063DAD0(const unsigned char* rgb)
{
    unsigned char red = rgb[0] >> gg_b_translucent_pixel_format.loss0;
    unsigned char green = rgb[1] >> gg_b_translucent_pixel_format.loss1;
    unsigned char blue = rgb[2] >> gg_b_translucent_pixel_format.loss2;
    return (red << gg_b_translucent_pixel_format.pos0) | (green << gg_b_translucent_pixel_format.pos1) | (blue << gg_b_translucent_pixel_format.pos2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63DB20
//
// Point-in-rectangle test: the X range is checked first (`pt->X >= this->X`
// then `pt->X < this->X + this->Width`), and only when it passes is the Y
// range checked at all -- the nested `if` (not a single `&&` chain across
// both axes) is what keeps the Y-range load and compare out of the X-only
// failure path, matching retail's two independent short-circuit exits to the
// same `xor eax,eax` tail. The point's own field has to be the *left*
// operand of the comparison (`pt->X >= this->X`, not `this->X <= pt->X`) --
// otherwise cl loads the rectangle field into EAX and the point field into
// EDX (the mirror of retail) and flips `JL` to `JG`, cascading through every
// register role in the rest of the axis. The return value is a plain `int`
// (`MOV EAX,1` / `XOR EAX,EAX`), not a `bool` (`MOV AL,1`).
int Rect_0063DB20::Contains(const Point_0063DB20* pt) const
{
    if (pt->X >= this->X && pt->X < this->X + this->Width) {
        if (pt->Y >= this->Y && pt->Y < this->Y + this->Height) {
            return 1;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x63DB90
// DynamicVectorClass<PlanningMemberClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DBB0
// VectorClass<PlanningMemberClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x63DD40
// VectorClass<PlanningMemberClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x63DD80
// VectorClass<PlanningMemberClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63DE60
// VectorClass<PlanningMemberClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x63DEA0
// VectorClass<PlanningMemberClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DF20
// DynamicVectorClass<PlanningMemberClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63E020
// DynamicVectorClass<PlanningMemberClass*>::FindItemIndex (slot 4)
template class VectorClass<PlanningMemberClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x63DBF0
// DynamicVectorClass<PlanningBranchClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DC10
// VectorClass<PlanningBranchClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x63E050
// VectorClass<PlanningBranchClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x63E090
// VectorClass<PlanningBranchClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63E170
// VectorClass<PlanningBranchClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x63E1B0
// VectorClass<PlanningBranchClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63E230
// DynamicVectorClass<PlanningBranchClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63E2E0
// DynamicVectorClass<PlanningBranchClass*>::FindItemIndex (slot 4)
template class VectorClass<PlanningBranchClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063DC20
// FUNCTION: GAMEMD 0x0063DC50
// FUNCTION: GAMEMD 0x0063DC70
// FUNCTION: GAMEMD 0x0063E310
// FUNCTION: GAMEMD 0x0063E350
// FUNCTION: GAMEMD 0x0063E400
// FUNCTION: GAMEMD 0x0063E430
// FUNCTION: GAMEMD 0x0063E470
// FUNCTION: GAMEMD 0x0063E490
// FUNCTION: GAMEMD 0x0063E620
// FUNCTION: GAMEMD 0x0063ED90
// FUNCTION: GAMEMD 0x0063EDE0
template class VectorClass<PlanningNodeClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63DC80
// DynamicVectorClass<EventClass*>::Clear
// FUNCTION: GAMEMD 0x63DCB0
// DynamicVectorClass<EventClass*>::Slot5
// FUNCTION: GAMEMD 0x63DCD0
// VectorClass<EventClass*>::Slot6
// FUNCTION: GAMEMD 0x63E650
// VectorClass<EventClass*>::operator==
// FUNCTION: GAMEMD 0x63E690
// VectorClass<EventClass*>::SetCapacity
// FUNCTION: GAMEMD 0x63E740
// VectorClass<EventClass*>::Clear
// FUNCTION: GAMEMD 0x63E770
// VectorClass<EventClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x63E7B0
// VectorClass<EventClass*>::Slot5
// FUNCTION: GAMEMD 0x63E7D0
// DynamicVectorClass<EventClass*>::SetCapacity
// FUNCTION: GAMEMD 0x63E8D0
// DynamicVectorClass<EventClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x63EE30
// VectorClass<EventClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x63EE80
// DynamicVectorClass<EventClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EFE24 -- VectorClass<EventClass*>.
template class VectorClass<EventClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x63DD10
// DynamicVectorClass<PlanningTokenClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DD30
// VectorClass<PlanningTokenClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x63E950
// VectorClass<PlanningTokenClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x63E990
// VectorClass<PlanningTokenClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63EA70
// VectorClass<PlanningTokenClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x63EAB0
// VectorClass<PlanningTokenClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63EAD0
// DynamicVectorClass<PlanningTokenClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63EC20
// DynamicVectorClass<PlanningTokenClass*>::FindItemIndex (slot 4)
template class VectorClass<PlanningTokenClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063DE30
// VectorClass<PlanningMemberClass*> -- vtable 0x007EFF04 slot 3; locator 0x008080A0 -> type descriptor 0x00836A60
//   `.?AV?$VectorClass@PAVPlanningMemberClass@@@@`.
template class VectorClass<PlanningMemberClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063DFD0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool ItemVector_0063DFD0::FUN_000063DFD0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063E140
// VectorClass<PlanningBranchClass*> -- vtable 0x007EFF24 slot 3; locator 0x008080D0 -> type descriptor 0x008369E8
//   `.?AV?$VectorClass@PAVPlanningBranchClass@@@@`.
template class VectorClass<PlanningBranchClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063E5D0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool ItemVector_0063DFD0::FUN_000063E5D0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063E900
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool ItemVector_0063DFD0::FUN_000063E900(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063EA40
// VectorClass<PlanningTokenClass*> -- vtable 0x007EFEA4 slot 3; locator 0x00807FA0 -> type descriptor 0x00836970
//   `.?AV?$VectorClass@PAVPlanningTokenClass@@@@`.
template class VectorClass<PlanningTokenClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063EBD0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool ItemVector_0063DFD0::FUN_000063EBD0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63F080
void FUN_0063F080(Polygon_0063F080* polygon, ScanBuffer_0063F080* buffer)
{
    PolyPoint_0063F080* points = polygon->Points;
    int count = polygon->Count;
    if (count == 0) return;

    int top = points[0].Y;
    int bottom = top;
    int top_index = 0;
    int bottom_index = 0;
    for (int index = 1; index < count; index++) {
        int y = points[index].Y;
        if (y < top) {
            top_index = index;
            top = y;
        } else if (y > bottom) {
            bottom_index = index;
            bottom = y;
        }
    }
    if (top == bottom) return;

    int right = top_index;
    while (points[right].Y == top) {
        right = (right + 1) % count;
    }
    right = (count + right - 1) % count;

    int left = top_index;
    while (points[left].Y == top) {
        left = (count + left - 1) % count;
    }
    left = (left + 1) % count;

    int direction = -1;
    int pointed = (points[left].X != points[right].X);
    if (pointed == 1) {
        if (points[left].X > points[right].X) {
            int swap = left;
            left = right;
            right = swap;
            direction = pointed;
        }
    } else {
        int after = (right + 1) % count;
        int before = (count + left - 1) % count;
        if ((points[before].Y - points[left].Y) * (points[after].X - points[left].X)
            - (points[after].Y - points[left].Y) * (points[before].X - points[left].X) < 0) {
            int swap = left;
            left = right;
            right = swap;
            direction = 1;
        }
    }

    buffer->Height = pointed - top - 1 + bottom;
    if (buffer->Height <= 0) return;
    buffer->Top = top - pointed + 1;
    if (buffer->Spans == NULL) {
        buffer->Spans = (ScanSpan_0063F080*)operator new(buffer->Height * sizeof(ScanSpan_0063F080) + 0x640);
    }
    if (buffer->Spans == NULL) {
        buffer->Height = 0;
        return;
    }

    ScanSpan_0063F080* cursor = buffer->Spans;
    int skip = (pointed == 0);
    int first = skip;
    int current = left;
    int next;
    do {
        if (direction > 0) {
            next = (current + 1) % polygon->Count;
        } else {
            next = (current + polygon->Count - 1) % polygon->Count;
        }
        FUN_0063F2E0(points[current].X, points[current].Y, points[next].X, points[next].Y, 1, first, &cursor);
        first = 0;
        current = next;
    } while (next != bottom_index);

    cursor = buffer->Spans;
    first = skip;
    direction = -direction;
    current = right;
    do {
        if (direction > 0) {
            next = (current + 1) % polygon->Count;
        } else {
            next = (current + polygon->Count - 1) % polygon->Count;
        }
        FUN_0063F2E0(points[current].X - 1, points[current].Y, points[next].X - 1, points[next].Y, 0, first, &cursor);
        first = 0;
        current = next;
    } while (next != bottom_index);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x63F2E0
void FUN_0063F2E0(int x1, int y1, int x2, int y2, int side, int skip, ScanSpan_0063F080** cursor)
{
    ScanSpan_0063F080* span = *cursor;
    int dx = x2 - x1;
    int step = (dx > 0) ? 1 : -1;
    int dy = y2 - y1;
    if (dy <= 0) return;

    int adx = abs(dx);
    int count;
    if (adx == 0) {
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            span++;
        }
    } else if (dy == adx) {
        if (skip) x1 += step;
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            x1 += step;
            span++;
        }
    } else if (dy > adx) {
        int error = (dx >= 0) ? 0 : 1 - dy;
        if (skip) {
            error += adx;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
        }
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            error += adx;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
            span++;
        }
    } else {
        int whole = (adx / dy) * step;
        int fraction = adx % dy;
        int error = (dx >= 0) ? 0 : 1 - dy;
        if (skip) {
            error += fraction;
            x1 += whole;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
        }
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            error += fraction;
            x1 += whole;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
            span++;
        }
    }
    *cursor = span;
}
