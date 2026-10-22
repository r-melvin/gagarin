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

#include "../ai/techno_class_clear_tokens_methods.h"

#include "../ai/techno_class_planning_node_helpers.h"

int DAT_00AC4B84[24];

#include "../ai/techno_class_planning_token_methods.h"

extern int DAT_00816108;
struct Rec12_008B4040 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B4040 DAT_008B4040[];
struct Rec12_008B3F38 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B3F38 DAT_008B3F38[];
struct Rec12_008B3FC8 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B3FC8 DAT_008B3FC8[];
extern unsigned char DAT_00A9FAB4;
extern unsigned char DAT_00ABCD58;
extern int DAT_00ABED0C;
extern int DAT_00ABF168[];
struct Rec28_0082D028 { int f00; int f04; int unknown_08[5]; };
extern Rec28_0082D028 DAT_0082D028[];
extern int DAT_00AC4B80;
extern int DAT_00AC4C90;
extern int DAT_00AC4C38;
extern int DAT_00AC4BF0;
extern int DAT_007F0248[];
struct Rec16_007F0998 { int f00; int f04; int f08; int f0C; };
extern Rec16_007F0998 DAT_007F0998[];
extern int DAT_00B0CB78[];
extern int DAT_008449F8[];
extern unsigned char DAT_00B0FE58;
extern unsigned char DAT_008464AC;
extern int DAT_00B780A0;

#include "vector_class_operations.h"

struct Obj_005D4E70;
extern DynamicVectorClass<Obj_005D4E70*> DAT_00ABFC90;

struct Obj_00638A20;
extern DynamicVectorClass<Obj_00638A20*> DAT_00AC4C18;

struct Obj_00638DC0;
extern DynamicVectorClass<Obj_00638DC0*> DAT_00AC4B30;

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

void __fastcall FUN_0063F2E0(int x1, int y1, int x2, int y2, int side, int skip, ScanSpan_0063F080** cursor);

#include "rect_contains_point_methods.h"

#include "tail_jmp_thunk_sweep.h"

#include "trivial_tu180_b_methods.h"

#include "trivial_tu180_methods.h"

#include "vector_class.h"

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
enum DiskID { DiskID_placeholder };
class DiskLaserClass;
template<class T0> class DynamicVectorClass;
class EBolt;
class EMPulseClass;
class EgoClass;
class EventClass;
class FactoryClass;
class FileEntryClass;
class FoggedObjectClass
{
public:
    struct DrawRecord;
};
class FootClass;
struct GlobalPacketType;
class GraphicMenuItem;
class HSVClass;
struct HWND__;
template<class T0, class T1> struct HashObject;
class HashString;
class HouseClass
{
public:
    struct BuildChoiceClass;
    struct StartingTechnoStruct;
};
class HouseTypeClass;
struct IConnectionPoint;
class InfantryTypeClass;
class IonBlastClass;
class IsometricTileTypeClass
{
public:
    struct TileInsertType;
};
struct KamikazeControl;
class LaserDrawClass;
class LightSourceClass
{
public:
    class PendingCellClass;
};
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
class SlaveManagerClass
{
public:
    struct SlaveControl;
};
class SmudgeClass;
class SmudgeTypeClass;
class SpawnManagerClass
{
public:
    struct SpawnControl;
};
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

#include "vector_class_operations.h"
class EventClass;

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

#include "vector_class_operations.h"

class PlanningBranchClass;

template class DynamicVectorClass<PlanningBranchClass*>;

GG_STATIC_ASSERT(sizeof(PlanningBranchClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningBranchClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningBranchClass* >) == 0x18);

#include "vector_class_operations.h"

class PlanningMemberClass;

template class DynamicVectorClass<PlanningMemberClass*>;

GG_STATIC_ASSERT(sizeof(PlanningMemberClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningMemberClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningMemberClass* >) == 0x18);

#include "vector_class_operations.h"

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

#include "vector_class_operations.h"

class PlanningTokenClass;

template class DynamicVectorClass<PlanningTokenClass*>;

GG_STATIC_ASSERT(sizeof(PlanningTokenClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningTokenClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningTokenClass* >) == 0x18);

#include "vector_remove_item_family_methods.h"

#include "../renderer/pixel_pack_methods.h"

#include <stdlib.h>
#include "../ui/planning_manager_rbutton_methods.h"

// FUNCTION: GAMEMD 0x634290
//
// Node_006386E0::FUN_00634290 -- linear scan of this node's entry array for
// the one whose owner word matches `owner`; returns its index, or -1 when the
// node is empty or nothing matches. The search sits under `if (count > 0)`
// (retail's `OR EAX,0xffffffff` seeds the -1 answer before the guard) rather
// than folding the empty case into the loop test, so an empty node returns -1
// without ever touching `Entries`.
// PARTIAL (92.3%, 24/26): a `for` over the entries with a `break` on the first
// owner match, written `count > i` as the loop test, gives retail's single
// guarded loop with the walk as a raw entry-pointer increment, the `OR EAX,-1`
// seed and the unrotated test. The one residual instruction is the loop test's
// direction: retail has `CMP EDX,ESI; JL`, this has `CMP ESI,EDX; JG` (the
// `i < count` spelling gives the retail compare but swaps the EDX/ESI roles,
// 69.2%).
int Node_006386E0::FUN_00634290(void* owner)
{
    int index = -1;
    int count = this->At_010;
    int i = 0;
    if (count > 0) {
        Entry_006386E0** entries = this->Entries;
        for (; count > i; i++, entries++) {
            if (*(int*)*entries == (int)owner) {
                index = i;
                break;
            }
        }
    }
    return index;
}

// FUNCTION: GAMEMD 0x634800
// Returns the address of a member.
int* Obj_00634800::FUN_00634800()
{
    return &unknown_38;
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

// FUNCTION: GAMEMD 0x637060
// Stores to a global.
void FUN_00637060(int a1)
{
    DAT_00AC4B80 = a1;
}

// FUNCTION: GAMEMD 0x6370A0
void __fastcall FUN_006370A0(void* self)
{
    FUN_006370B0(self);
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

// FUNCTION: GAMEMD 0x6385C0
//
// Advance this unit along its planning token. The token must exist, hold at
// least one node, have a usable +0x8C (-1 or positive) and not already be
// stepping (+0x1C). The unit is queued mission 0x1C, the token builds the next
// 0x6F-byte record, a heap copy of it (kind 4 forced to sub-kind 2) is
// appended to the global record list, and the token is marked as stepping.
bool Techno_006385C0::TryNextPlanningTokenNode()
{
    Token_006385C0* token = this->FUN_00705D20();
    if (token
        && token->NodeCount > 0
        && (token->At_08C == -1 || token->At_08C > 0)
        && !token->At_01C) {
        (this->*this->Vtbl->QueueMission)(0x1C, 1);

        Node_006385C0 rec = token->FUN_00636590();
        Node_006385C0* copy = new Node_006385C0;
        *copy = rec;
        if (copy->At_000 == 4) {
            copy->At_01D = 2;
        }
        DAT_00AC4B48.AddItem(copy);

        token->At_01C = 1;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6386E0
//
// MATCHED (100.0%, 112/112). The gate-byte test only reaches retail's
// MOVSX EAX,byte ptr [EDI+0x1D] / TEST EAX,EAX when the char is bound to an
// int through a ternary that supplies the null-gate fallback
// (`int gateFlag = (gate != 0) ? gate->At_01D : 0;`): the ternary's int type
// forces the widening while the short-circuit shape of the branch is kept.
// Every in-place spelling of the test (plain `== 0`, an `(int)` cast, `!expr`,
// `expr + 0 == 0`, `(expr | 0) == 0`, an inline accessor returning int, an
// inline accessor binding the char to an int local) narrows to
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
void __fastcall Techno_006386E0::ClearPlanningTokens(Record_006386E0* gate)
{
    if (this == 0) {
        return;
    }

    Token_006386E0* token = this->FUN_00705D20();
    if (token == 0) {
        return;
    }

    void* slot;

    int gateFlag = (gate != 0) ? gate->At_01D : 0;
    if (gateFlag == 0 && token->NodeCount > 0) {
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
            Sector_006386E0* sector = ((Owner_006386E0*)slot)->At_21C;
            Scene_006386E0* scene = sector->At_030;
            if (sector->FUN_0050B6F0() && DAT_00A83D4C != 0) {
                scene = DAT_00A83D4C->At_030;
            }
            scene->FUN_00639F80();
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
void FUN_00638A20(Obj_00638A20* item)
{
    DynamicVectorClass<Obj_00638A20*>& v = DAT_00AC4C18;
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

// FUNCTION: GAMEMD 0x00638DC0
void FUN_00638DC0(Obj_00638DC0* item)
{
    DynamicVectorClass<Obj_00638DC0*>& v = DAT_00AC4B30;
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

// FUNCTION: GAMEMD 0x639F80
//
// MATCHED (100.0%, 12/12). Scene_006386E0::FUN_00639F80 -- decrement the
// pending-request counter for this house index, clamped at 0 (not -1: the
// retail formula is `(v-1)<0 ? 0 : v-1`, i.e. `max(v-1, 0)`). Called as
// `scene->FUN_00639F80()` from TechnoClass::ClearPlanningTokens
// (match/ai/techno_class_clear_tokens_methods.cpp, read not edited), where
// the "scene" pointer is really a small house index carried in the receiver
// register rather than a dereferenced object -- this function never reads
// through `this`, only compares and indexes with its bit pattern. Out of
// [0, 24) it is a no-op. The branchless clamp (`DEC`/`SETS`/`DEC`/`AND`)
// reproduces once the ternary's answer (0, not -1) is right and it lands in
// a fresh local rather than back into the variable that fed the comparison.
void Scene_006386E0::FUN_00639F80()
{
    if ((int)this >= 0 && (int)this < 24) {
        int dec = DAT_00AC4B84[(int)this] - 1;
        int clamped = (dec < 0) ? 0 : dec;
        DAT_00AC4B84[(int)this] = clamped;
    }
}

// FUNCTION: GAMEMD 0x63A210
// Stores, then tail-calls.
void Obj_0063A210::FUN_0063A210()
{
    int c0 = FUN_00734E60(this, 0, DAT_00836BD4, 0xCA1);
    FUN_00730A90(c0, 0x1E0);
}

// FUNCTION: GAMEMD 0x63A4A0
// Stores to a global.
void FUN_0063A4A0(int a1)
{
    DAT_00AC4C90 = a1;
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
        && abs(x - DAT_00AC4C68) <= 3
        && abs(y - DAT_00AC4C6C) <= 3) {
        DAT_00AC4BF0 = 0;
    }
}

// FUNCTION: GAMEMD 0x63AD30
// Stores to a global.
void FUN_0063AD30(int a1)
{
    DAT_00AC4C38 = a1;
}

// FUNCTION: GAMEMD 0x63AD40
// Returns a global (dword).
int __cdecl FUN_0063AD40()
{
    return DAT_00AC4C38;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0063B090
void FUN_0063B090()
{
    DAT_00AC4BF0 = 0;
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
// MATCHED (100.0%, 26/26). The final combination is `(blue | green) | red`,
// but retail's LOAD/SHIFT instruction sequences run green first, then blue,
// then red -- the source order `blue; green; red;` (matching the textual
// left-to-right of the OR chain) has cl 8804 schedule the green and blue
// instruction groups swapped (confirmed via the object's relocation table,
// not the operand text: the first `mov cl,[global]` after the swap resolves
// to DAT_008A0DE4, green's, even though blue's OR still combines correctly).
// Declaring green before blue -- with the final `blue | green | red`
// expression left unchanged -- reproduces retail's instruction order exactly.
unsigned int __fastcall PackPixel_0063DAD0(const unsigned char* rgb)
{
    unsigned int green = (rgb[1] >> DAT_008A0DE4) << DAT_008A0DE0;
    unsigned int blue  = (rgb[2] >> DAT_008A0DDC) << DAT_008A0DD8;
    unsigned int red   = (rgb[0] >> DAT_008A0DD4) << DAT_008A0DD0;
    return blue | green | red;
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
void __fastcall FUN_0063F080(Polygon_0063F080* polygon, ScanBuffer_0063F080* buffer)
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
void __fastcall FUN_0063F2E0(int x1, int y1, int x2, int y2, int side, int skip, ScanSpan_0063F080** cursor)
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
