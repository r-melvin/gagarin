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

#include "../core/deleting_dtor_sweep.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/stdcall_forward_sweep.h"

#include "../core/trivial_tu187_methods.h"

#include <windows.h>
#include <new>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" int __cdecl FUN_004068E0(const char* format, ...);

#include "radar_class.h"
#include "input_controls/ui_common.h"
#include "tooltip_manager_shared.h"
#include "shape_button_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/techno_class.h"
#include "../core/leftover_trivial_leaf_sweep.h"

// GLOBAL: GAMEMD 0x00A8EC78
extern DynamicVectorClass<TechnoClass*> DAT_00A8EC78;
#include "../platform/ccini_class_small_readers_methods.h"
#include "../platform/file_system_load_whole_methods.h"
#include "../renderer/pixel_shift_view.h"
#include "../network/multiplayer_game_mode.h"

// The native vptr at RadarClass+0x1224 is 0x7E3890, whose retail RTTI type
// is DynamicVectorClass<Cell>. Serialization reads the element's dword at +0;
// Elem_0042F670 is the existing four-byte ABI view for that value.
typedef DynamicVectorClass<Cell> RadarCellVector;
typedef DynamicVectorClass<Point2D> RadarPointVector;
GG_STATIC_ASSERT(sizeof(RadarCellVector) == 0x18);
GG_STATIC_ASSERT(offsetof(RadarCellVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(RadarCellVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(RadarCellVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(RadarCellVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(RadarCellVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(RadarCellVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(RadarPointVector) == 0x18);
GG_STATIC_ASSERT(offsetof(RadarPointVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(RadarPointVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(RadarPointVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(RadarPointVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(RadarPointVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(RadarPointVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(Elem_0042F670) == 4);
GG_STATIC_ASSERT(offsetof(Elem_0042F670, Value) == 0);

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

// GLOBAL: GAMEMD 0x00B048B0
extern int DAT_00B048B0;
// GLOBAL: GAMEMD 0x00B048B4
extern int DAT_00B048B4;
// GLOBAL: GAMEMD 0x00B048B8
extern int DAT_00B048B8;
// GLOBAL: GAMEMD 0x00B048BC
extern int DAT_00B048BC;

// FUNCTION: GAMEMD 0x6558B0 (decl; reloc) -- address stored in RadarArrayHolder.
void stub_006558B0();

// STRING: GAMEMD 0x008392DC
extern const char DAT_008392DC[]; // "RadarClass::One_Time()\n"
// STRING: GAMEMD 0x008392C0
extern const char DAT_008392C0[]; // "EVA_IncomingTransmission"
// STRING: GAMEMD 0x00839314
extern const char DAT_00839314[]; // "RadarClass::Init_Clear\n"
// STRING: GAMEMD 0x008392F4
extern const char DAT_008392F4[]; // "RadarClass::Init_Clear done\n"
// STRING: GAMEMD 0x0083932C
extern const char DAT_0083932C[]; // "RadarClass::Init_For_House()\n"
// STRING: GAMEMD 0x008393C8
extern const char DAT_008393C8[]; // "Tip:BriefingButton"
// STRING: GAMEMD 0x008393B4
extern const char DAT_008393B4[]; // "Tip:DiplomacyButton"
// STRING: GAMEMD 0x008393A0
extern const char DAT_008393A0[]; // "Tip:OptionsButton"
// GLOBAL: GAMEMD 0x00887368
extern ToolTipManager* ToolTipManager_Instance;
// Opaque declaration of the existing sidebar storage view; only its address
// is used, after reinterpretation to the binary-proven GadgetClass base.
struct SidebarButton;
// GLOBAL: GAMEMD 0x00B04A10
extern SidebarButton ExtraGadget_00B04A10;
// GLOBAL: GAMEMD 0x008391F4 (pointer to the string at 0x839288)
extern const char* DAT_008391F4;
// GLOBAL: GAMEMD 0x008391F8 (pointer to the string at 0x83927C)
extern const char* DAT_008391F8;

// GLOBAL: GAMEMD 0x007F5BF8
extern int DAT_007F5BF8;
// GLOBAL: GAMEMD 0x00886FA8
extern int DAT_00886FA8;
// GLOBAL: GAMEMD 0x00A8EB7C
extern unsigned char DAT_00A8EB7C;
// GLOBAL: GAMEMD 0x00A8EDA0
extern int DAT_00A8EDA0;
// GLOBAL: GAMEMD 0x00A8B238
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0x00A8B230 -- scenario object pointer, used at native offset +0x34B8.
extern char* DAT_00A8B230;
// GLOBAL: GAMEMD 0x00A8B23C -- game-mode object pointer.
extern MultiplayerGameMode* DAT_00A8B23C;
// GLOBAL: GAMEMD 0x00A8ED6B
extern bool DisplayFlag_00A8ED6B;
// GLOBAL: GAMEMD 0x0087F6CC -- value stored as ShapeButtonClass::Convert.
extern int DAT_0087F6CC;
// GLOBAL: GAMEMD 0x00B04A20
extern int DAT_00B04A20;
// GLOBAL: GAMEMD 0x00B04A24
extern int DAT_00B04A24;
// GLOBAL: GAMEMD 0x00B04A28
extern int DAT_00B04A28;
// GLOBAL: GAMEMD 0x00B04A30
extern int DAT_00B04A30;
// GLOBAL: GAMEMD 0x00B04A00
extern int DAT_00B04A00;
// GLOBAL: GAMEMD 0x00B04A04
extern int DAT_00B04A04;
// GLOBAL: GAMEMD 0x00B04A08
extern int DAT_00B04A08;
// GLOBAL: GAMEMD 0x00B04A0C
extern int DAT_00B04A0C;
// GLOBAL: GAMEMD 0x00B04A1C
extern int DAT_00B04A1C;
// GLOBAL: GAMEMD 0x00B048C8
extern int DAT_00B048C8;
// GLOBAL: GAMEMD 0x00B048CC
extern int DAT_00B048CC;
// GLOBAL: GAMEMD 0x00B048D0
extern int DAT_00B048D0;
// GLOBAL: GAMEMD 0x00B048D4
extern int DAT_00B048D4;
// GLOBAL: GAMEMD 0x00B048E0
extern void* DAT_00B048E0;
// GLOBAL: GAMEMD 0x00B048AC
extern void* DAT_00B048AC;
// GLOBAL: GAMEMD 0x00B048F9
extern unsigned char DAT_00B048F9;
// GLOBAL: GAMEMD 0x00B048F8
extern unsigned char DAT_00B048F8;
// GLOBAL: GAMEMD 0x00B04A38
extern ShapeHeader* DAT_00B04A38;
// GLOBAL: GAMEMD 0x00B0F9E0
extern ShapeHeader* DAT_00B0F9E0;
// GLOBAL: GAMEMD 0x00B0FA68
extern ShapeHeader* DAT_00B0FA68;
// GLOBAL: GAMEMD 0x00B049CC
extern unsigned char DAT_00B049CC;
// GLOBAL: GAMEMD 0x00B04964
extern unsigned char DAT_00B04964;
// GLOBAL: GAMEMD 0x00B049A5
extern unsigned char DAT_00B049A5;
// GLOBAL: GAMEMD 0x00B0493D
extern unsigned char DAT_00B0493D;
// GLOBAL: GAMEMD 0x00B04978
extern ShapeButtonClass RadarButtonF2_00B04978;
// GLOBAL: GAMEMD 0x00B04910
extern ShapeButtonClass RadarButtonF3_00B04910;
// GLOBAL: GAMEMD 0x00B0B3A0
extern ShapeButtonClass RepairButton_00B0B3A0;
// GLOBAL: GAMEMD 0x00B07DF8
extern ShapeButtonClass SellButton_00B07DF8;
// GLOBAL: GAMEMD 0x00B0B518
extern unsigned char SidebarTouched_00B0B518;
// GLOBAL: GAMEMD 0x00B0FA1C (three channel bytes at +0..+2; accessed as a dword and byte fields)
struct RadarColorSamples_00B0FA1C { unsigned char Red, Green, Blue, unknown_03; };
GG_STATIC_ASSERT(offsetof(RadarColorSamples_00B0FA1C, Green) == 1);
GG_STATIC_ASSERT(offsetof(RadarColorSamples_00B0FA1C, Blue) == 2);
GG_STATIC_ASSERT(sizeof(RadarColorSamples_00B0FA1C) == 4);
extern RadarColorSamples_00B0FA1C DAT_00B0FA1C;
// FUNCTION: GAMEMD 0x406060 (decl; reloc) -- end the loop on Radar's +0x14C0 audio handle.
void __fastcall FUN_00406060(Obj_00405B00* handle);
// FUNCTION: GAMEMD 0x53BAE0 (decl; reloc)
bool __cdecl FUN_0053BAE0();
// FUNCTION: GAMEMD 0x753580 (decl; reloc)
void FUN_00753580();
// FUNCTION: GAMEMD 0x65FDD0 (decl; reloc)
void FUN_0065FDD0();
// FUNCTION: GAMEMD 0x72F510 (decl; reloc)
int FUN_0072F510();

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

#include "../core/vector_class.h"

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

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<ScoutStruct>;

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<AngerStruct>;

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<SwizzlePointerClass>;

template<class K,class V> struct HashObject { K Key; V Value; HashObject() {} HashObject(const HashObject<K,V>& o) : Key(o.Key), Value(o.Value) {} bool operator==(const HashObject<K,V>& o) const { return Key==o.Key; } bool operator!=(const HashObject<K,V>& o) const { return !(*this==o); } };

template class DynamicVectorClass<HashObject<unsigned int,unsigned int> >;

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<HashObject<unsigned int,SubzoneConnectionStruct> >;

struct RadarTrackingStruct { int unknown_00; int unknown_04; int unknown_08; RadarTrackingStruct() {} RadarTrackingStruct(const RadarTrackingStruct& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08) {} bool operator==(const RadarTrackingStruct& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const RadarTrackingStruct& o) const { return !(*this==o); } }; class TechnoClass; 

typedef DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*> > RadarTrackingVector;
GG_STATIC_ASSERT(sizeof(RadarTrackingStruct) == 0x0C);
GG_STATIC_ASSERT(offsetof(RadarTrackingStruct, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(RadarTrackingStruct, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(RadarTrackingStruct, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(RadarTrackingVector) == 0x18);
GG_STATIC_ASSERT(offsetof(RadarTrackingVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(RadarTrackingVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(RadarTrackingVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(RadarTrackingVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(RadarTrackingVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(RadarTrackingVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(offsetof(TechnoClass, IsRadarTracked) == 0x423);
GG_STATIC_ASSERT(sizeof(TechnoClass) == 0x520);
GG_STATIC_ASSERT(sizeof(TechnoClass*) == 4);
GG_STATIC_ASSERT(sizeof(void*) == 4);

template class DynamicVectorClass<HashObject<RadarTrackingStruct,TechnoClass*> >;

struct AcceleratorTracker { int A; int B; AcceleratorTracker() : A(0), B(0) {} bool operator==(const AcceleratorTracker& o) const { return A==o.A && B==o.B; } bool operator!=(const AcceleratorTracker& o) const { return !(*this==o); } };

template class DynamicVectorClass<AcceleratorTracker>;

struct UndoInfoStruct { int unknown_00; int unknown_04; int unknown_08; UndoInfoStruct() : unknown_00(0), unknown_04(0), unknown_08(0) {} bool operator==(const UndoInfoStruct& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const UndoInfoStruct& o) const { return !(*this==o); } };

template class DynamicVectorClass<UndoInfoStruct>;

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

// FUNCTION: GAMEMD 0x652960
RadarClass::RadarClass()
    : DisplayClass(),
      unknown_11E8(0),
      unknown_11EC(0),
      unknown_11F0(0),
      unknown_11F4(0),
      unknown_11F8(0),
      unknown_11FC(0),
      unknown_1200(0),
      unknown_1204(0),
      unknown_120C(DAT_00B048B0),
      unknown_1210(DAT_00B048B4),
      unknown_1214(DAT_00B048B8),
      unknown_1218(DAT_00B048BC),
      unknown_121C(0),
      unknown_1220(0),
      unknown_1224(0, 0),
      unknown_123C(0),
      unknown_1240(0),
      unknown_1244(0),
      unknown_1248(0),
      unknown_124C(0),
      unknown_1250(0),
      unknown_1254(0),
      unknown_1258(0),
      unknown_125C(0, 0),
      unknown_1274(0),
      unknown_1488(0),
      unknown_148C(1),
      unknown_1490(0),
      unknown_1494(0),
      unknown_1498(0),
      RadarBounds(),
      unknown_14AC(0),
      unknown_14B0(0),
      unknown_14B4(0),
      unknown_14BC(0),
      unknown_14BD(0),
      unknown_14D4(-1),
      unknown_14D8(0),
      unknown_14D9(0),
      unknown_14DA(0),
      unknown_14DC(DAT_00B048B0),
      unknown_14E0(DAT_00B048B4),
      unknown_14E4(DAT_00B048B8),
      unknown_14E8(DAT_00B048BC),
      unknown_14FC(0)
{
    RadarBounds.X = DAT_00B048B0;
    RadarBounds.Y = DAT_00B048B4;
    RadarBounds.Width = DAT_00B048B8;
    RadarBounds.Height = DAT_00B048BC;

    RadarArrayHolder* holder = new RadarArrayHolder;
    if (holder != 0) {
        // The binary stores this code address, but its call contract is not
        // established; retain it as an opaque address in the existing field.
        holder->unknown_04 = reinterpret_cast<void*>(&stub_006558B0);
        holder->unknown_08 = 0x100;
        holder->unknown_0C = 10;

        typedef DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*> > RadarTrackingVector;
        holder->items = new RadarTrackingVector[0x100];
        // Native 0x652BC4..0x652BD3 runs this separate pass even when the
        // array allocation returned null; it is not a guarded reset.
        for (int i = 0; i < holder->unknown_08; ++i)
            holder->items[i].CapacityIncrement = holder->unknown_0C;
    }
    unknown_1258 = holder;
    unknown_125C.CapacityIncrement = 500;
    unknown_14C0.FUN_00405BE0();
}

// FUNCTION: GAMEMD 0x652C00
RadarClass::~RadarClass()
{
    unknown_14C0.FUN_00405C00();
    FUN_00655A90();
}

// FUNCTION: GAMEMD 0x652CD0
// Stores several members.
void Obj_00652CD0::FUN_00652CD0()
{
    unknown_14AC = 4;
    unknown_14FC = 0x19;
}

// FUNCTION: GAMEMD 0x652CF0
void RadarClass::vf_05()
{
    FUN_004068E0(DAT_008392DC);
    unknown_1200 = 0x8C;
    unknown_11F8 = 0x8C;
    unknown_11E4 = 0;
    unknown_11E8 = 0x10;
    unknown_11EC = 0x30;
    unknown_1204 = 0x6C;
    unknown_11FC = 0x6C;
    unknown_11F4 = 0x31;
    DisplayClass::vf_05();
    DAT_00B04A20 = unknown_11F4;
    DAT_00B04A24 = unknown_1200;
    DAT_00B04A28 = unknown_1204;
    DAT_00B04A30 = 0xDF;
    unknown_14D4 = FUN_00753250(DAT_008392C0);
}

// FUNCTION: GAMEMD 0x00652D90
void RadarClass::vf_50()
{
    if (DAT_00B048F9) {
        ::operator delete(DAT_00B048E0);
        DAT_00B048F9 = 0;
    }
    DAT_00B048E0 = 0;
    if (DAT_00B048F8) {
        ::operator delete(DAT_00B048AC);
        DAT_00B048F8 = 0;
    }
    DAT_00B048AC = 0;
}

// FUNCTION: GAMEMD 0x652DE0
void RadarClass::vf_07()
{
    DisplayClass::vf_07();
    FUN_004068E0(DAT_00839314);
    unknown_14AC = 0;
    unknown_14B0 = 0;
    unknown_14BD = 0;
    unknown_14BC = 0;
    unknown_14FC = 0;
    unknown_14D8 = 0;
    unknown_14D9 = 1;
    unknown_1224.Clear();
    unknown_125C.Clear();
    FUN_004068E0(DAT_008392F4);
}

// FUNCTION: GAMEMD 0x652E90
void RadarClass::vf_53()
{
    FUN_004068E0(DAT_0083932C);
    vf_50();
    if (*(int*)(DAT_00A8B230 + 0x34B8) == 0) {
        unknown_11F0 = (DAT_007F5BF8 - 0x90) / 2 + 4;
        DAT_00B04A00 = unknown_11E4 + 0x0B;
        DAT_00B048CC = unknown_11E8 + 4;
        DAT_00B048C8 = unknown_11E4 + 0x53;
    } else {
        unknown_11F0 = (DAT_007F5BF8 - 0x91) / 2 + 5;
        DAT_00B04A00 = unknown_11E4 + 0x0E;
        DAT_00B048CC = unknown_11E8 + 5;
        DAT_00B048C8 = unknown_11E4 + 0x56;
    }
    DAT_00B04A1C = unknown_11F0;
    DAT_00B04A04 = DAT_00B048CC;
    DAT_00B048E0 = FileSystem_LoadWholeFileEx(DAT_008391F4, (bool*)&DAT_00B048F9);
    DAT_00B048AC = FileSystem_LoadWholeFileEx(DAT_008391F8, (bool*)&DAT_00B048F8);
    DAT_00B04A08 = (int)*(short*)((char*)DAT_00B048E0 + 2);
    DAT_00B04A0C = (int)*(short*)((char*)DAT_00B048E0 + 4);
    DAT_00B048D0 = (int)*(short*)((char*)DAT_00B048AC + 2);
    DAT_00B048D4 = (int)*(short*)((char*)DAT_00B048AC + 4);
    DAT_00B04A38 = DAT_00B0FA68;
    unknown_1208 = (((unsigned int)DAT_00B0FA1C.Blue >> (gg_b_translucent_pixel_format.loss2 & 31))
                      << (gg_b_translucent_pixel_format.pos2 & 31))
        | (((unsigned int)DAT_00B0FA1C.Green >> (gg_b_translucent_pixel_format.loss1 & 31))
                      << (gg_b_translucent_pixel_format.pos1 & 31))
        | (((unsigned int)DAT_00B0FA1C.Red >> (gg_b_translucent_pixel_format.loss0 & 31))
                      << (gg_b_translucent_pixel_format.pos0 & 31));
}

// FUNCTION: GAMEMD 0x653010
void RadarClass::vf_08()
{
    DisplayClass::vf_08();
    if (!DisplayFlag_00A8ED6B) {
        ShapeButtonClass& f2 = RadarButtonF2_00B04978;
        f2.ID = 0xF2;
        f2.UsesSidebarSurface = 1;
        f2.Convert = (ColorConvert*)DAT_0087F6CC;
        DAT_00B049A5 = 0;
        f2.unknown_30 = 0;
        f2.Flags = 5;
        f2.GadgetClass::SetPosition(DAT_00B04A00, DAT_00B04A04);
        f2.ShapeButtonClass::vf_34((ShapeHeader*)DAT_00B048E0, 0, 0);
        f2.GadgetClass::MarkRedraw();

        ShapeButtonClass& f3 = RadarButtonF3_00B04910;
        f3.Convert = (ColorConvert*)DAT_0087F6CC;
        f3.ID = 0xF3;
        f3.UsesSidebarSurface = 1;
        DAT_00B0493D = 0;
        f3.unknown_30 = 0;
        f3.Flags = 5;
        f3.GadgetClass::SetPosition(DAT_00B048C8, DAT_00B048CC);
        f3.ShapeButtonClass::vf_34((ShapeHeader*)DAT_00B048AC, 0, 0);
        f3.GadgetClass::MarkRedraw();
    }
}

// FUNCTION: GAMEMD 0x653100
void RadarClass::vf_16(bool forced)
{
    if (DisplayFlag_00A8ED6B) {
        unknown_14DA = 0;
        unknown_14D9 = 0;
        return;
    }

    unknown_14DA = (unknown_14DA == 1 || forced == 1) ? 1 : 0;
    unknown_14D9 = (unknown_14D9 == 1 || unknown_14DA == 1) ? 1 : 0;
    bool timerExpired = false;

    if (unknown_14D9 == 1) {
        Point2D pos(unknown_11E4, unknown_11E8);
        Rect clip = DAT_00887300->GetRect();
        FUN_004AED70(DAT_00887300, (ColorConvert*)DAT_0087F6CC, DAT_00B0F9E0, 0,
                     &pos, &clip, 0, 0, 0, 0, 1000, 0, 0, 0,
                     Point2D(0, 0));
        RadarButtonF2_00B04978.ShapeButtonClass::Draw(1);
        RadarButtonF3_00B04910.ShapeButtonClass::Draw(1);
    }

    if (unknown_14AC != 0 && unknown_14AC != 1) {
        int remaining = unknown_1500.unknown_08;
        if (unknown_1500.unknown_00 != -1) {
            int elapsed = unknown_1500.unknown_04.GetTime()
                - unknown_1500.unknown_00;
            if (elapsed < remaining)
                remaining -= elapsed;
            else
                remaining = 0;
        }

        if (remaining == 0) {
            unknown_1500.unknown_00 = unknown_1500.unknown_04.GetTime();
            unknown_1500.unknown_08 = 4;
            timerExpired = true;

            if (unknown_14AC == 2) {
                --unknown_14FC;
                if (unknown_14FC < 1) {
                    unknown_14AC = 0;
                    FUN_00406060(&unknown_14C0);
                    unknown_14FC = 0;
                }
            } else {
                ++unknown_14FC;
                if (unknown_14FC >= 32) {
                    FUN_00406060(&unknown_14C0);
                    unknown_14AC = 1;
                    unknown_14DA = 1;
                    unknown_14FC = 32;
                }
            }
        }
    }

    if (unknown_14AC != 1 &&
        (unknown_14D9 == 1 || timerExpired) &&
        unknown_14FC >= 0 &&
        unknown_14FC < (int)DAT_00B04A38->Frames) {
        ColorConvert* convert = (ColorConvert*)FUN_0072F510();
        Point2D pos(unknown_11E4, unknown_11EC);
        Rect clip = DAT_00887300->GetRect();
        FUN_004AED70(DAT_00887300, convert, DAT_00B04A38, unknown_14FC,
                     &pos, &clip, 0, 0, 0, 0, 1000, 0, 0, 0,
                     Point2D(0, 0));
        unknown_120C = unknown_11E4;
        unknown_1210 = unknown_11EC;
        unknown_1214 = DAT_007F5BF8;
        unknown_1218 = 0x6E;
    }

    FUN_0065FDD0();
    FUN_00656EC0();

    if (unknown_14AC != 1) {
        switch (unknown_14B0) {
        case 1:
        case 4:
            break;
        case 2:
            if (unknown_14D9 == 1) {
                unknown_14D9 = 0;
                if (unknown_14DA != 0) {
                    ColorConvert* convert = (ColorConvert*)FUN_0072F510();
                    Point2D pos(unknown_11E4, unknown_11EC);
                    Rect clip = DAT_00887300->GetRect();
                    FUN_004AED70(DAT_00887300, convert, DAT_00B04A38, 0x20,
                                 &pos, &clip, 0, 0, 0, 0, 1000, 0, 0, 0,
                                 Point2D(0, 0));
                    FUN_00653FA0();
                    unknown_120C = unknown_11E4;
                    unknown_1210 = unknown_11EC;
                    unknown_1214 = 0xA8;
                    unknown_1218 = 0x6E;
                } else {
                    FUN_00653FA0();
                    unknown_120C = unknown_11F0;
                    unknown_1210 = unknown_11F4;
                    unknown_1214 = unknown_1200;
                    unknown_1218 = unknown_1204;
                }
            }
            break;
        case 3:
            FUN_006579E0();
            break;
        default:
            if (unknown_14D9 == 1) {
                unknown_14D9 = 0;
                ColorConvert* convert = (ColorConvert*)FUN_0072F510();
                Point2D pos(unknown_11E4, unknown_11EC);
                Rect clip = DAT_00887300->GetRect();
                FUN_004AED70(DAT_00887300, convert, DAT_00B04A38, 0,
                             &pos, &clip, 0, 0, 0, 0, 1000, 0, 0, 0,
                             Point2D(0, 0));
                unknown_120C = unknown_11E4;
                unknown_1210 = unknown_11EC;
                unknown_1214 = 0xA8;
                unknown_1218 = 0x6E;
            }
            break;
        }
    }

    if (unknown_14DA != 0) {
        unknown_14DA = 0;
        RepairButton_00B0B3A0.ShapeButtonClass::Draw(1);
        SellButton_00B07DF8.ShapeButtonClass::Draw(1);
    }

    if (DAT_00B049CC != 0) {
        int x = unknown_120C;
        int y = unknown_1210;
        int width = unknown_1214;
        int height = unknown_1218;
        if (width > 0 && height > 0) {
            if (DAT_00B04A08 >= 1 && DAT_00B04A0C >= 1) {
                if (DAT_00B04A00 < x) {
                    width += x - DAT_00B04A00;
                    x = DAT_00B04A00;
                }
                if (DAT_00B04A04 < y) {
                    height += y - DAT_00B04A04;
                    y = DAT_00B04A04;
                }
                if (x + width < DAT_00B04A08 + DAT_00B04A00)
                    width = DAT_00B04A08 - x + 1 + DAT_00B04A00;
                if (y + height < DAT_00B04A0C + DAT_00B04A04)
                    height = DAT_00B04A04 - y + 1 + DAT_00B04A0C;
            }
        } else {
            x = DAT_00B04A00;
            y = DAT_00B04A04;
            width = DAT_00B04A08;
            height = DAT_00B04A0C;
        }
        unknown_120C = x;
        unknown_1210 = y;
        unknown_1214 = width;
        unknown_1218 = height;
        SidebarTouched_00B0B518 = 1;
    }

    if (DAT_00B04964 != 0) {
        int x = unknown_120C;
        int y = unknown_1210;
        int width = unknown_1214;
        int height = unknown_1218;
        if (width > 0 && height > 0) {
            if (DAT_00B048D0 >= 1 && DAT_00B048D4 >= 1) {
                if (DAT_00B048C8 < x) {
                    width += x - DAT_00B048C8;
                    x = DAT_00B048C8;
                }
                if (DAT_00B048CC < y) {
                    height += y - DAT_00B048CC;
                    y = DAT_00B048CC;
                }
                if (x + width < DAT_00B048D0 + DAT_00B048C8)
                    width = DAT_00B048D0 - x + 1 + DAT_00B048C8;
                if (y + height < DAT_00B048D4 + DAT_00B048CC)
                    height = DAT_00B048D4 - y + 1 + DAT_00B048CC;
            }
        } else {
            x = DAT_00B048C8;
            y = DAT_00B048CC;
            width = DAT_00B048D0;
            height = DAT_00B048D4;
        }
        unknown_120C = x;
        unknown_1210 = y;
        unknown_1214 = width;
        unknown_1218 = height;
        SidebarTouched_00B0B518 = 1;
    }
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

// FUNCTION: GAMEMD 0x653850
void RadarClass::vf_10(int* key, Point2D* where)
{
    DisplayClass::vf_10(key, where);
    int offset = DAT_00A8EB7C ? DAT_00886FA8 : 0;
    if (DAT_00B04A00 + offset <= where->X &&
        where->X < DAT_00B04A00 + offset + DAT_00B04A08 &&
        DAT_00B04A04 <= where->Y &&
        where->Y < DAT_00B04A04 + DAT_00B04A0C)
        Map_0087F7E8.MouseClass::vf_19(0, false);
    if (DAT_00B048C8 + offset <= where->X &&
        where->X < DAT_00B048C8 + offset + DAT_00B048D0 &&
        DAT_00B048CC <= where->Y &&
        where->Y < DAT_00B048CC + DAT_00B048D4)
        Map_0087F7E8.MouseClass::vf_19(0, false);

    if (*key == 0x80F2) {
        if (DAT_00A8B238 == 0) {
            DAT_00A8EDA0 = 9;
        } else if ((DAT_00A8B238 == 3 || DAT_00A8B238 == 4) &&
                   DAT_00A8B23C != 0 && DAT_00A8B23C->vf_2() &&
                   DAT_00A8B23C->vf_1()) {
            DAT_00A8EDA0 = 9;
        } else {
            DAT_00A8EDA0 = 8;
        }
    } else if (*key == 0x80F3) {
        DAT_00A8EDA0 = 1;
    }

    if (DAT_00B45B68 > 0 && unknown_14B0 != 3 && unknown_14B0 != 4) {
        unknown_14B4 = unknown_14B0;
        FUN_00656CB0(4, 0);
        unknown_14B8 = 0;
    }
    if (unknown_14B0 == 4) {
        FUN_006578F0();
        return;
    }
    if (!FUN_0053BAE0())
        FUN_00753580();
}


// FUNCTION: GAMEMD 0x653F50  (__thiscall)
// RadarClass override of MapClass::CreateEmptyMap — a pure forward to the base
// (0x565C10) with the same four arguments and the same `this`.
void RadarClass::vf_28(RectangleStruct* mapRect, int reuse,
                       int nLevel, int bUnk2)
{
    MapClass::vf_28(mapRect, reuse, nLevel, bUnk2);
}

// FUNCTION: GAMEMD 0x654320 RadarClass::vf_34 (__thiscall)
void RadarClass::vf_34()
{
    // Native CALL 0x4AE6B0 is DisplayClass::vf_34, not a virtual dispatch.
    DisplayClass::vf_34();

    const int shift = DAT_00A8EB7C ? DAT_00886FA8 : 0;

    // These stores are the two ShapeButtonClass::OffsetX fields at +0x44.
    RadarButtonF2_00B04978.OffsetX = -shift;
    RadarButtonF2_00B04978.GadgetClass::SetPosition(
        DAT_00B04A00 + shift, DAT_00B04A04);
    RadarButtonF2_00B04978.GadgetClass::MarkRedraw();

    RadarButtonF3_00B04910.OffsetX = -shift;
    RadarButtonF3_00B04910.GadgetClass::SetPosition(
        DAT_00B048C8 + shift, DAT_00B048CC);
    RadarButtonF3_00B04910.GadgetClass::MarkRedraw();

    // RTTI at the vtable installed on 0xB04A10 proves a zero-offset
    // GadgetClass base for RadarClass::RTacticalClass. The source global keeps
    // its existing storage view; this cast selects that binary-confirmed base.
    reinterpret_cast<GadgetClass&>(ExtraGadget_00B04A10).GadgetClass::SetPosition(
        unknown_11F0 + shift, unknown_11F4);
    reinterpret_cast<GadgetClass&>(ExtraGadget_00B04A10).GadgetClass::MarkRedraw();

    ToolTip tip;
    tip.field_18 = false;
    tip.GadgetID = 0xF2;
    tip.Text = DAT_008393C8;
    if (DAT_00A8B238 != 0)
        tip.Text = DAT_008393B4;
    tip.Bounds.X = RadarButtonF2_00B04978.X;
    tip.Bounds.Y = RadarButtonF2_00B04978.Y;
    tip.Bounds.Width = RadarButtonF2_00B04978.Width;
    tip.Bounds.Height = RadarButtonF2_00B04978.Height;
    ToolTipManager_Instance->Remove(0xF2);
    ToolTipManager_Instance->Add(tip);

    tip.Bounds.X = RadarButtonF3_00B04910.X;
    tip.Bounds.Y = RadarButtonF3_00B04910.Y;
    tip.GadgetID = 0xF3;
    tip.Text = DAT_008393A0;
    tip.Bounds.Width = RadarButtonF3_00B04910.Width;
    tip.Bounds.Height = RadarButtonF3_00B04910.Height;
    ToolTipManager_Instance->Remove(0xF3);
    ToolTipManager_Instance->Add(tip);

    unknown_14DA = 1;
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
void RadarClass::vf_29(RectangleStruct* mapRect)
{
    MapClass::vf_29(mapRect);
    RadarBounds.Height = 0;
    RadarBounds.Y      = 10000;
    RadarBounds.X      = 10000;

    Cell_0050DEF0 b;
    Cell_0050DEF0 a;
    int ax = LocalRect.Y + LocalRect.X + 1;                // [0x100] + [0xFC] + 1
    int ay = (MapRect.Width - LocalRect.X) + LocalRect.Y;  // [0xF4]
    a.X = (short)ax;
    a.Y = (short)ay;
    RadarBounds.Width = 0;
    int bx = LocalRect.Width - 1;                         // [0x104]
    int by = 1 - LocalRect.Width;
    b.X = (short)bx;
    b.Y = (short)by;
    unknown_1498 = -1;
    Cell_0050DEF0 c = a + b;
    unknown_1494 = c.X - c.Y;
    unknown_1490 = a.Y - a.X;

    Instance.FUN_00578350();
    // The iterator's returned record is read at +0x24 as two shorts by this
    // native body, so view that proven record as the TU's tracking node.
    RadarTrackNode* node = (RadarTrackNode*)FUN_00578290();
    while (node != 0)
    {
        // 0x578460 receives the address of the same two-short cell. The
        // canonical MapClass declaration names that ABI-compatible value
        // CellStruct; the native accesses confirm X at +0 and Y at +2.
        if (FUN_00578460(reinterpret_cast<const CellStruct&>(node->GetCell()), true))
        {
            if (unknown_1498 == -1)
                unknown_1498 = node->Cell.Y + node->Cell.X;
            Cell_0050DEF0 cell = node->GetCell();
            int x = (unknown_1490 - cell.Y) + cell.X;
            int y = (cell.Y - unknown_1498) + cell.X;
            int span = 2;
            if (x == -1)
            {
                x = 0;
                span = 1;
            }
            else if (x == LocalRect.Width * 2 - 1)
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
        node = (RadarTrackNode*)FUN_00578290();
    }
}

// FUNCTION: GAMEMD 0x6558D0
void RadarClass::FUN_006558D0()
{
    RadarArrayHolder* holder = new RadarArrayHolder;
    if (holder == 0) {
        unknown_1258 = 0;
        return;
    }

    holder->unknown_04 = reinterpret_cast<void*>(&stub_006558B0);
    holder->unknown_08 = 0x100;
    holder->unknown_0C = 10;
    holder->items = new RadarTrackingVector[0x100];

    // Native executes this second pass even when the array allocation fails.
    // Keep the loop unguarded: the resulting null dereference is part of the
    // observed allocation-failure path.
    for (int i = 0; i < holder->unknown_08; ++i)
        holder->items[i].CapacityIncrement = holder->unknown_0C;

    unknown_1258 = holder;
}

// FUNCTION: GAMEMD 0x655990
void RadarClass::FUN_00655990()
{
    RadarArrayHolder* oldHolder = unknown_1258;
    if (oldHolder != 0) {
        if (oldHolder->items != 0)
            delete[] oldHolder->items;
        delete oldHolder;
    }

    RadarArrayHolder* holder = new RadarArrayHolder;
    if (holder != 0) {
        holder->unknown_04 = reinterpret_cast<void*>(&stub_006558B0);
        holder->unknown_08 = 0x100;
        holder->unknown_0C = 10;
        holder->items = new RadarTrackingVector[0x100];

        // Keep the separate native pass unguarded after array allocation.
        for (int i = 0; i < holder->unknown_08; ++i)
            holder->items[i].CapacityIncrement = holder->unknown_0C;
    }
    unknown_1258 = holder;

    Map_0087F7E8.RadarClass::vf_29(&Map_0087F7E8.LocalRect);
    FUN_00654650();

    for (int i = 0; i < DAT_00A8EC78.Count; ++i)
        DAT_00A8EC78.Items[i]->IsRadarTracked = 0;
}

// FUNCTION: GAMEMD 0x655A90
void RadarClass::FUN_00655A90()
{
    if (unknown_121C != 0) {
        // RTTI-backed primary bases begin at offset zero. ui_common.h supplies
        // the existing slot-0 deleting-destructor ABI view; renderer headers
        // cannot be included here because they redefine that separate view.
        reinterpret_cast<Surface*>(unknown_121C)->vf_00(1);
        unknown_121C = 0;
    }
    if (unknown_1220 != 0) {
        reinterpret_cast<Surface*>(unknown_1220)->vf_00(1);
        unknown_1220 = 0;
    }
    if (unknown_123C != 0) {
        ::operator delete(unknown_123C);
        unknown_123C = 0;
    }
    RadarArrayHolder* holder = unknown_1258;
    if (holder != 0) {
        if (holder->items != 0)
            delete[] holder->items;
        ::operator delete(holder);
        unknown_1258 = 0;
    }
    if (unknown_1274 != 0) {
        ::operator delete(unknown_1274);
        unknown_1274 = 0;
    }
}

// FUNCTION: GAMEMD 0x655B20
void RadarClass::FUN_00655B20()
{
    unknown_121C = 0;
    unknown_1220 = 0;
    unknown_123C = 0;
    unknown_1258 = 0;
    unknown_1274 = 0;

    RadarArrayHolder* holder = new RadarArrayHolder;
    if (holder != 0) {
        holder->unknown_04 = reinterpret_cast<void*>(&stub_006558B0);
        holder->unknown_08 = 0x100;
        holder->unknown_0C = 10;
        holder->items = new RadarTrackingVector[0x100];

        // Keep the separate native pass unguarded after array allocation.
        for (int i = 0; i < holder->unknown_08; ++i)
            holder->items[i].CapacityIncrement = holder->unknown_0C;
    }
    unknown_1258 = holder;

    Map_0087F7E8.RadarClass::vf_29(&Map_0087F7E8.LocalRect);
    FUN_00654650();

    for (int i = 0; i < DAT_00A8EC78.Count; ++i)
        DAT_00A8EC78.Items[i]->IsRadarTracked = 0;

    if (unknown_14B0 == 3) {
        int value = unknown_14B4;
        unknown_14AC = 5;
        FUN_00656CB0(value, 0);
        FUN_0055AF40(RulesInstance->unknown_000);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00656580
// Record number (key +0xEF0) + 197 of the 24-byte records at `this`.
Record_00656580* Obj_00656580::FUN_00656580(const Key_00656580* key)
{
    return &unknown_0[key->unknown_EF0 + 0xC5];
}

// FUNCTION: GAMEMD 0x6568A0
long RadarClass::vf_30(IStream* stream)
{
    int i;
    long hr = DisplayClass::vf_30(stream);
    if (hr < 0)
        return hr;

    int count;
    hr = stream->Read(&count, 4, 0);
    if (hr < 0)
        return hr;

    unknown_14C0.FUN_00405BE0();

    // Native resets each vector by replacing its object lifetime with a zero-capacity
    // dynamic vector: the base constructor receives (0, 0), then retail installs the
    // derived-table state. Placement construction expresses the same stores without
    // freeing any old backing block (0x658D60 and 0x42FCB0 native paths).
    new ((void*)&unknown_125C) DynamicVectorClass<Point2D>(0, 0);
    for (i = 0; i < count; ++i) {
        Point2D point;
        hr = stream->Read(&point, 8, 0);
        if (hr < 0)
            return hr;
        unknown_125C.AddItem(point);
    }

    hr = stream->Read(&count, 4, 0);
    if (hr < 0)
        return hr;

    new ((void*)&unknown_1224) DynamicVectorClass<Cell>(0, 0);
    for (i = 0; i < count; ++i) {
        Cell cell;
        hr = stream->Read(&cell, 4, 0);
        if (hr < 0)
            return hr;
        unknown_1224.AddItem(cell);
    }

    for (i = 0; i < 0x16; ++i)
        new ((void*)&unknown_1278[i]) DynamicVectorClass<Point2D>(0, 0);

    hr = stream->Read(&unknown_14B0, 4, 0);
    if (hr < 0)
        return hr;
    hr = stream->Read(&unknown_14AC, 4, 0);
    if (hr < 0)
        return hr;
    hr = stream->Read(&unknown_14B4, 4, 0);
    if (hr < 0)
        return hr;
    hr = stream->Read(&unknown_14B8, 4, 0);
    if (hr < 0)
        return hr;

    unknown_14C0.FUN_00405BE0();
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x656AC0
long RadarClass::vf_31(IStream* stream)
{
    long hr = DisplayClass::vf_31(stream);
    if (hr < 0)
        return hr;

    int pointCount = unknown_125C.Count;
    hr = stream->Write(&pointCount, 4, 0);
    if (hr < 0) return hr;
    int i;
    for (i = 0; i < pointCount; ++i) {
        hr = stream->Write(&unknown_125C.Items[i], 8, 0);
        if (hr < 0) return hr;
    }

    int valueCount = unknown_1224.Count;
    hr = stream->Write(&valueCount, 4, 0);
    if (hr < 0) return hr;
    for (i = 0; i < valueCount; ++i) {
        hr = stream->Write(&reinterpret_cast<Elem_0042F670*>(unknown_1224.Items)[i].Value, 4, 0);
        if (hr < 0) return hr;
    }

    hr = stream->Write(&unknown_14B0, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&unknown_14AC, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&unknown_14B4, 4, 0);
    if (hr < 0) return hr;
    return stream->Write(&unknown_14B8, 4, 0);
}


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
