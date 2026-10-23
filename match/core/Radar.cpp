// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Radar.CPP. The name is the source-file string at 0x839388
//   in retail gamemd.exe v1.001, passed by the assert at 0x65405d inside this object's
//   code range (0x652680-0x658e7f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The four argument forwarders, ordered ascending by retail address.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.
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
// Retail RTTI names VectorClass/DynamicVectorClass over the 8-byte pair structs, HashObject<K,V> and
// AcceleratorTracker/UndoInfoStruct. Only slots that reproduce retail bytes are claimed.
//
//   0x654490). Names cross-checked against YRpp (every offset/address reconfirmed against the user's binary).
//
//   GLOBAL:   GAMEMD 0x87F7E8   RadarClass::Instance

#include "deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "stdcall_forward_sweep.h"

#include "trivial_tu187_methods.h"

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
struct Cell_0050DEF0
{
    short X;
    short Y;

    Cell_0050DEF0() {}
    bool operator==(const Cell_0050DEF0& other) const
    {
        return X == other.X && Y == other.Y;
    }
};
GG_STATIC_ASSERT(sizeof(Cell_0050DEF0) == 4);

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A8EF98
extern "C" Cell_0050DEF0 DAT_00A8EF98;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

struct Team_005095D0
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[4];
    void* unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Team_005095D0, unknown_2C) == 0x2C);

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

struct Obj_005095D0
{
    int FUN_005095D0(int kind);
};


struct Obj_0050DA10
{
    char Pad_00[0x5490];
    Cell_0050DEF0 unknown_5490;
    Cell_0050DEF0 unknown_5494;
    char Pad_5498[0x54F0 - 0x5498];
    Cell_0050DEF0 unknown_54F0;
    Cell_0050DEF0 unknown_54F4;
    Cell_0050DEF0 unknown_54F8;
    int unknown_54FC;
    char Pad_5500[0x577C - 0x5500];
    int unknown_577C;

    void FUN_0050DA10();
    void FUN_0050DA50();
    int FUN_0050DA80() const;
    Cell_0050DEF0 FUN_0050DEF0() const;
    void FUN_0050DFF0();
};
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_5490) == 0x5490);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54F0) == 0x54F0);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54FC) == 0x54FC);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_577C) == 0x577C);

struct Obj_0053ECB0
{
    unsigned char unknown_0[10];

    Obj_0053ECB0();
};

struct Triple_0053EDA0
{
    short unknown_0;
    short unknown_2;
    short unknown_4;
};
GG_STATIC_ASSERT(sizeof(Triple_0053EDA0) == 6);

struct Obj_0053EDA0
{
    int unknown_0;
    Triple_0053EDA0 unknown_4;

    void FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0053EDA0, unknown_4) == 4);

struct Obj_005402B0
{
    void FUN_005402B0(int value);
};

struct Obj_00542FC0
{
    char Pad_00[0x48];
    Obj_005402B0* unknown_48;

    void FUN_00542FC0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00542FC0, unknown_48) == 0x48);

struct Entry_005657A0
{
    char Pad_00[0x24];
    Cell_0050DEF0 unknown_24;
};

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

struct Obj_005657A0
{
    char Pad_00[0x13C];
    Entry_005657A0** unknown_13C;

    Entry_005657A0* FUN_005657A0(const Cell_0050DEF0& cell) const;
};
GG_STATIC_ASSERT(offsetof(Obj_005657A0, unknown_13C) == 0x13C);

struct Obj_005B3700
{
    int unknown_0;
    char unknown_4;
    char unknown_5;
    char unknown_6;
    char unknown_7;
    char unknown_8;
    char unknown_9;
    char Pad_0A[6];
    double unknown_10;
    double unknown_18;

    Obj_005B3700();
};
GG_STATIC_ASSERT(offsetof(Obj_005B3700, unknown_10) == 0x10);

struct Slot_005B3A00
{
    char Bytes[0x20];
};

// GLOBAL: GAMEMD 0x00A8E3A8 (32-byte records)
extern "C" Slot_005B3A00 DAT_00A8E3A8[];

struct Obj_005B3A00
{
    char Pad_00[0xAC];
    int unknown_AC;
};
GG_STATIC_ASSERT(offsetof(Obj_005B3A00, unknown_AC) == 0xAC);

struct Iface_005BF500
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3(int value) = 0;
};

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

struct Vector_005C6120
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3() = 0;

    void** unknown_4;
    int Pad_08;
    int Pad_0C;
    int unknown_10;

    void FUN_005C6120();
};

struct Obj_005F9710
{
    char unknown_0;
    char unknown_1;
};

struct Quad_00645C30
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_00645C30(int a, int b, int c, int d);
};

struct Record_00656580
{
    char Bytes[0x18];
};

struct Key_00656580
{
    char Pad_00[0xEF0];
    int unknown_EF0;
};
GG_STATIC_ASSERT(offsetof(Key_00656580, unknown_EF0) == 0xEF0);

struct Obj_00656580
{
    Record_00656580 unknown_0[1];

    Record_00656580* FUN_00656580(const Key_00656580* key);
};

struct Obj_0065AD30
{
    char Pad_00[0xE4];
    int* unknown_E4;

    int FUN_0065AD30(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD30, unknown_E4) == 0xE4);

struct Pair_0065C890
{
    int unknown_0;
    int unknown_4;

    Pair_0065C890(int a, int b);
};

struct Obj_0068BCB0
{
    char Pad_00[0x214];
    int unknown_214;
};
GG_STATIC_ASSERT(offsetof(Obj_0068BCB0, unknown_214) == 0x214);

struct Obj_0068C030
{
    char Pad_00[0x1180];
    int unknown_1180[16];

    int FUN_0068C030(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0068C030, unknown_1180) == 0x1180);

struct Owner_006915D0
{
    char Pad_00[0xA0];
    unsigned int unknown_A0;
};
GG_STATIC_ASSERT(offsetof(Owner_006915D0, unknown_A0) == 0xA0);

struct Cursor_006915D0
{
    char Pad_00[0x24];
    Owner_006915D0* unknown_24;
    char Pad_28[4];
    unsigned int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Cursor_006915D0, unknown_2C) == 0x2C);

#pragma pack(push, 1)
struct Obj_00696F10
{
    char Pad_00[0x4B];
    int unknown_4B;
    int unknown_4F;
    int unknown_53;
    int unknown_57;
    int unknown_5B;
    int unknown_5F;
    int unknown_63;
    int unknown_67;

    int FUN_00696F10() const;
    int FUN_00696F20() const;
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_67) == 0x67);

struct Obj_0069B540
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[0x4C - 0x28];
    int unknown_4C[8];
    int unknown_6C[8];
};
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_6C) == 0x6C);

struct Obj_0069BBE0
{
    char Pad_00[0x30D8];
    char unknown_30D8;
};
GG_STATIC_ASSERT(offsetof(Obj_0069BBE0, unknown_30D8) == 0x30D8);

struct Type_006A46D0
{
    char Pad_00[0x24];
    char unknown_24[1];
};

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

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


struct Obj_00656E50;

struct Obj_00656E50
{
    char unknown_00[0x14AC];
    int unknown_14AC;   // +0x14AC
    int unknown_14B0;   // +0x14B0
    // FUNCTION: GAMEMD 0x656E50
    int FUN_00656E50();
};
GG_STATIC_ASSERT(offsetof(Obj_00656E50, unknown_14AC) == 0x14AC);
GG_STATIC_ASSERT(offsetof(Obj_00656E50, unknown_14B0) == 0x14B0);

struct Obj_00653F90 {
    void FUN_00578460(int, int);
    void FUN_00653F90(int a);
};
// FUNCTION: GAMEMD 0x00653F90
void Obj_00653F90::FUN_00653F90(int a)
{
    FUN_00578460(a, 1);
}

// FUNCTION: GAMEMD 0x656E50
// Branching.
int Obj_00656E50::FUN_00656E50()
{
    return unknown_14B0 == 2 && unknown_14AC == 1;
}

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<ScoutStruct>;

#include "pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<AngerStruct>;

#include "pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<SwizzlePointerClass>;

template<class K,class V> struct HashObject { K Key; V Value; HashObject() {} HashObject(const HashObject<K,V>& o) : Key(o.Key), Value(o.Value) {} bool operator==(const HashObject<K,V>& o) const { return Key==o.Key; } bool operator!=(const HashObject<K,V>& o) const { return !(*this==o); } };

template class DynamicVectorClass<HashObject<unsigned int,unsigned int> >;

#include "pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<HashObject<unsigned int,SubzoneConnectionStruct> >;

struct RadarTrackingStruct { int unknown_00; int unknown_04; int unknown_08; RadarTrackingStruct() {} RadarTrackingStruct(const RadarTrackingStruct& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08) {} bool operator==(const RadarTrackingStruct& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const RadarTrackingStruct& o) const { return !(*this==o); } }; class TechnoClass; 

template class DynamicVectorClass<HashObject<RadarTrackingStruct,TechnoClass*> >;

struct AcceleratorTracker { int A; int B; AcceleratorTracker() : A(0), B(0) {} bool operator==(const AcceleratorTracker& o) const { return A==o.A && B==o.B; } bool operator!=(const AcceleratorTracker& o) const { return !(*this==o); } };

template class DynamicVectorClass<AcceleratorTracker>;

struct UndoInfoStruct { int unknown_00; int unknown_04; int unknown_08; UndoInfoStruct() : unknown_00(0), unknown_04(0), unknown_08(0) {} bool operator==(const UndoInfoStruct& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const UndoInfoStruct& o) const { return !(*this==o); } };

template class DynamicVectorClass<UndoInfoStruct>;

#include "../ui/radar_class.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F02A8
extern const double DAT_007F02A8;
// GLOBAL: GAMEMD 0xB048D8
extern double DAT_00B048D8;
// GLOBAL: GAMEMD 0xB049E0
extern double DAT_00B049E0;
// GLOBAL: GAMEMD 0xB049E8
extern int DAT_00B049E8;
// GLOBAL: GAMEMD 0xB049EC
extern int DAT_00B049EC;
// GLOBAL: GAMEMD 0xB049F0
extern int DAT_00B049F0;
// GLOBAL: GAMEMD 0xB049F8
extern double DAT_00B049F8;

// FUNCTION: GAMEMD 0x6526B0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006526B0()
{
    DAT_00B049F8 = DAT_00B048D8 / DAT_007F02A8;
}

// FUNCTION: GAMEMD 0x6526D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006526D0()
{
    DAT_00B049E0 = DAT_007E1718 / DAT_00B049F8;
}

// FUNCTION: GAMEMD 0x652850
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00652850()
{
    DAT_00B049F0 = 0;
    DAT_00B049E8 = 0x80;
    DAT_00B049EC = 0x80;
}

// FUNCTION: GAMEMD 0x6528C0
// Empty function.
void __cdecl FUN_006528C0()
{
}

// FUNCTION: GAMEMD 0x652910
// Empty function.
void __cdecl FUN_00652910()
{
}

// FUNCTION: GAMEMD 0x652CD0
// Stores several members.
void Obj_00652CD0::FUN_00652CD0()
{
    unknown_14AC = 4;
    unknown_14FC = 0x19;
}

// FUNCTION: GAMEMD 0x653750
// Empty function that pops its stack arguments.
void __stdcall FUN_00653750(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x653830
// Calls other functions. Vtable slot 37 of RadarClass (RTTI) and 5 derived vtable(s).
bool Obj_00653830::FUN_00653830(int a1, int a2, int a3)
{
    return (FUN_004A9CA0(this, a2, a1, a2, a3) != 0) ? true : false;
}

// FUNCTION: GAMEMD 0x653F50  (__thiscall)
// RadarClass override of MapClass::CreateEmptyMap — a pure forward to the base
// (0x565C10) with the same four arguments and the same `this`.
void RadarClass::CreateEmptyMap(const RectangleStruct& mapRect, bool reuse,
                               char nLevel, bool bUnk2)
{
    Map_CreateEmptyMap(mapRect, reuse, nLevel, bUnk2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x654490  (__thiscall)
// Reset the radar's bounding rectangle to "empty" (X=Y=10000, W=H=0), recompute
// the map-pixel origin offsets, then walk the radar tracking list and grow the
// bounds to enclose every still-visible tracked cell.
//
// The 0x10-byte frame is two CellStruct locals (a at [ESP+0xC], b at
// [ESP+0x14]) whose halves are built in 32-bit from the int members and stored
// as words; the inlined operator+ then loads each pair back as a dword and adds
// before the MOVSX group. The cell handed to the visibility probe is a by-value
// GetCell() temporary bound to a const reference (the reused mapRect slot at
// [ESP+0x24]); the same getter feeds the x/y arithmetic after the call.
//
// PARTIAL (78.9%, 97/123). Mnemonic multiset identical; every diff is slot or
// register naming. (1) cl gives `a` the upper slot and `b` the lower
// ([ESP+0x14]/[ESP+0xC], retail the reverse) whichever is declared or
// assigned first; building b as a MakeCell() temporary or an operator+
// argument temporary does not swap them either. (2) Retail widens all four
// halves in place (`MOVSX ECX,CX; MOVSX EDX,DX; MOVSX EAX,AX; MOVSX EDI,DI`)
// before both SUBs; cl widens a.Y/a.X into fresh EDX/EAX after the first SUB.
// (3) In the loop retail keeps cell.Y in ECX and cell.X in EDX and interleaves
// the two sums (`SUB EAX,ECX; SUB ECX,EBP; ADD EAX,EDX; ADD ECX,EDX`); cl
// swaps the pair and finishes x before y, whether the sums are one expression
// each, split into four statements, or read through int locals. (4) The X
// bound check names Width EBX and span+x EBP where retail has EBP/EBX; both
// `x + span > Width + lo` and `lo + Width < span + x` give the same
// allocation. Earlier phrasings: 16-bit short locals (8.1%), int locals for
// left/top (swap the two leading loads), members read straight into shorts
// (16-bit loads), `return Cell;` getter (early temp store, 70.7%). This pass
// added: the four widened halves bound to int locals in retail's MOVSX order
// before the two SUBs (no change, 78.9%), and the `a`/`b` declarations
// swapped (76.4%) — cl gives the *first-used* struct the higher slot, which is
// the opposite of retail, where the first-stored struct is at [ESP+0xC].
void RadarClass::SetVisibleRect(const RectangleStruct& mapRect)
{
    Base_SetVisibleRect(mapRect);
    RadarBounds.Height = 0;
    RadarBounds.Y      = 10000;
    RadarBounds.X      = 10000;

    CellStruct b;
    CellStruct a;
    int ax = MapCellTop + MapCellLeft + 1;                 // [0x100] + [0xFC] + 1
    int ay = (MapSizeX - MapCellLeft) + MapCellTop;        // [0xF4]
    a.X = (short)ax;
    a.Y = (short)ay;
    RadarBounds.Width = 0;
    int bx = unknown_104 - 1;                             // [0x104]
    int by = 1 - unknown_104;
    b.X = (short)bx;
    b.Y = (short)by;
    unknown_1498 = -1;
    CellStruct c = a + b;
    unknown_1494 = c.X - c.Y;
    unknown_1490 = a.Y - a.X;

    Instance.Func_578350();
    RadarTrackNode* node = Iterate_578290();
    while (node != 0)
    {
        if (Func_578460(node->GetCell(), true))
        {
            if (unknown_1498 == -1)
                unknown_1498 = node->Cell.Y + node->Cell.X;
            CellStruct cell = node->GetCell();
            int x = (unknown_1490 - cell.Y) + cell.X;
            int y = (cell.Y - unknown_1498) + cell.X;
            int span = 2;
            if (x == -1)
            {
                x = 0;
                span = 1;
            }
            else if (x == unknown_104 * 2 - 1)
            {
                span = 1;
            }
            int lo = RadarBounds.X;
            if (x < lo)
                RadarBounds.X = x;
            else if (x + span > RadarBounds.Width + lo)
                RadarBounds.Width = (span - lo) + x;
            int top = RadarBounds.Y;
            if (y < top)
                RadarBounds.Y = y;
            else if (y + 1 > top + RadarBounds.Height)
                RadarBounds.Height = (y - top) + 1;
        }
        node = Iterate_578290();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00656580
// Record number (key +0xEF0) + 197 of the 24-byte records at `this`.
Record_00656580* Obj_00656580::FUN_00656580(const Key_00656580* key)
{
    return &unknown_0[key->unknown_EF0 + 0xC5];
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x656CA0
// Returns a comparison result.
bool Obj_00656CA0::FUN_00656CA0() const
{
    return unknown_14AC == 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x656DC0
// Branching.
int Obj_00656DC0::FUN_00656DC0()
{
    return unknown_14B0 == 1 && unknown_14AC == 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x656DE0
// Member getter (byte).
unsigned char Obj_00656DE0::FUN_00656DE0() const
{
    return unknown_14D8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x656E70
// Branching.
int Obj_00656E70::FUN_00656E70()
{
    return unknown_14B0 == 3 && unknown_14AC == 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x658770
void Radar_00658770::FUN_00658770(void* arg)
{
    FUN_004AE4F0(arg);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x658780
void* Obj_658780::FUN_658780(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00658AA0
// VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x00658AF0
// VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>>::Slot5
// FUNCTION: GAMEMD 0x006588E0
// VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>>::Slot6
// FUNCTION: GAMEMD 0x00658C20
// DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x006588C0
// DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*>>::Slot5
template class VectorClass<HashObject<RadarTrackingStruct,TechnoClass*> >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00658A70
// VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>> -- vtable 0x007F044C slot 3; locator 0x008083F0 -> type descriptor 0x008393E0
//   `.?AV?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@`.
template class VectorClass<HashObject<RadarTrackingStruct, TechnoClass*> >;
