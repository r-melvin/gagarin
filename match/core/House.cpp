// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Original translation unit House.CPP. The name is the source-file string at 0x824724
//   in retail gamemd.exe v1.001, passed by the assert at 0x4f8d43 inside this object's
//   code range (0x4f4f00-0x510aff). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   YRpp.
//
//   cross-checked against YRpp (each offset/address reconfirmed against the user's binary below).
//
// Translation unit: BasePlanningCellContainer growth + qsort comparator.
//
//   LIBRARY:  GAMEMD 0x7C8E17  operator new / malloc  (CRT; array new/delete)
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete / free (CRT; array new/delete)
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
//   Name cross-checked against YRpp (convention + 0xE08 offset reconfirmed against the user's binary below).
//
// Translation unit: ObjectTypeClass::IsBuildCat5.
//
// NOTE on the sibling method ObjectTypeClass::LoadVoxel @0x5F8110: that retail
// routine is 0xBCB (3019) bytes ending at the RET @0x5F8CDA, dominated by many
// fully-inlined std::string temporaries (CCFileClass/IndexClass ctor+dtor pairs
// at 0x4739F0/0x473C50/0x43AE50/0x431B80) and voxel/HVA loader calls. It is not
// matchable in a single pass and is deferred; not included in this TU.
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
// Retail RTTI names VectorClass/DynamicVectorClass over ZoneConnectionClass, WaypointClass and
// DiscreteDistributionClass<T>::DistributionObject<T*>. WaypointClass and the distribution objects have
// element destructors, so their ctor/Clear/SetCapacity bodies (array-delete paths) are not claimed here.
//
// Retail RTTI type descriptors name VectorClass<HouseClass::BuildChoiceClass*> and
// DynamicVectorClass<HouseClass::BuildChoiceClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Slot 5 of the retail DynamicVectorClass<AngerStruct>, <ScoutStruct> and
// <SwizzlePointerClass> vtables (owners read from retail RTTI). The bodies
// divide the byte offset by 8 (shr 3), agreeing with the eight-byte element
// asserts in the canonical pair-vector header. VC6 emits nothing for an
// explicit member instantiation, so the dynamic class is instantiated whole;
// only slot 5 is claimed here.
//
// Retail RTTI names VectorClass/DynamicVectorClass over the 8-byte pair structs, HashObject<K,V> and
// AcceleratorTracker/UndoInfoStruct. Only slots that reproduce retail bytes are claimed.
//
// Retail RTTI names VectorClass/DynamicVectorClass over unsigned short, bool, double and unsigned char.
// Scalar elements need no element type; the canonical templates are instantiated as-is.
//
// HouseClass entries of the house/building cluster (layout and evidence: house_class_core.h, house_views.h).
//
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT double->long; the (int) casts; reloc)

#include "../ai/house_class_anger_nodes_methods.h"

#include "../ai/house_class_find_building_methods.h"

// Index of a type in BuildingTypeClass::Array, or -1. Inlined into the search
// below (`XOR EAX,EAX; TEST EDI,EDI; JLE; ... OR EAX,-1`).
static inline int TypeIndex_004FD060(BuildingType_004FD060* type)
{
    for (int i = 0; i < DAT_00A83C78; ++i) {
        if (DAT_00A83C6C[i] == type) {
            return i;
        }
    }
    return -1;
}

#include <string.h>
#include "../ai/house_class_find_index_methods.h"

#pragma intrinsic(strcpy, strcmp)

#include "../ai/house_class_lost_powered_center_methods.h"

#include "../ai/house_class_respawn_methods.h"

#include "empty_function_family_methods.h"

#include "general_structures.h"

#include "leftover_trivial_leaf_sweep.h"

#include "member_setter_family_methods.h"

#include "object_type_class.h"

#include "positive_field_predicates.h"

#include "trivial_tu095_methods.h"

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

#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct ZoneCell { short X; short Y; ZoneCell() : X(0), Y(0) {} bool operator==(const ZoneCell& o) const { return X==o.X && Y==o.Y; } bool operator!=(const ZoneCell& o) const { return !(*this==o); } }; struct ZoneConnectionClass { ZoneCell unknown_00; ZoneCell unknown_04; unsigned char unknown_08; int unknown_0C; ZoneConnectionClass() : unknown_08(0), unknown_0C(-1) {} ZoneConnectionClass(const ZoneConnectionClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const ZoneConnectionClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const ZoneConnectionClass& o) const { return !(*this==o); } };

template class DynamicVectorClass<ZoneConnectionClass>;

struct WaypointClass { int unknown_00; int unknown_04; int unknown_08; WaypointClass(int a = 0, int b = 0, int c = 0) : unknown_00(a), unknown_04(b), unknown_08(c) {} ~WaypointClass() {} bool operator==(const WaypointClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const WaypointClass& o) const { return !(*this==o); } };

template class DynamicVectorClass<WaypointClass>;

class CellClass; template<class C> struct DiscreteDistributionClass { template<class P> struct DistributionObject { P Object; int Weight; DistributionObject() : Object(0) {} ~DistributionObject() {} DistributionObject(const DistributionObject<P>& o) : Object(o.Object), Weight(o.Weight) {} bool operator==(const DistributionObject<P>& o) const { return Object==o.Object && Weight==o.Weight; } bool operator!=(const DistributionObject<P>& o) const { return !(*this==o); } }; };

template class DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*> >;

class BuildingTypeClass; 

template class DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;

class AITriggerTypeClass; 

template class DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;

#include "vector_class_operations.h"

class HouseClass {
public:
    struct BuildChoiceClass;
};

template class DynamicVectorClass<HouseClass::BuildChoiceClass*>;

GG_STATIC_ASSERT(sizeof(HouseClass::BuildChoiceClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<HouseClass::BuildChoiceClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<HouseClass::BuildChoiceClass* >) == 0x18);

#include "pair_vector_ctor_family_methods.h"

#include "vector_class_operations.h"

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

#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<unsigned short>;

template class DynamicVectorClass<bool>;

template class DynamicVectorClass<double>;

#include <string.h>
#include <new.h>
#include "../economy/house_building/house_class_core.h"

#pragma intrinsic(memcmp)

// ---- globals / read-only externals ----------------------------------------------------------------
// GLOBAL: GAMEMD 0x7EA768 / 0x7E9B00 - IID_IHouse / IID_IPublicHouse. The library ids (IID_IUnknown
//         0x7F7C90, IID_IPersist 0x7F7C70, IID_IPersistStream 0x7F7C80, IID_IConnectionPointContainer
//         0x7F7CD0) come from the SDK import library.
extern const IID IID_IHouse;
extern const IID IID_IPublicHouse;
// GLOBAL: GAMEMD 0x820270 - the program's own copy of IID_IPersistStream (data of the original unit), used by Save.
extern const IID DAT_00820270;
// GLOBAL: GAMEMD 0x7E9AF0 - the id of the AI general interface the house loads from its stream.
extern const IID DAT_007E9AF0;
// GLOBAL: GAMEMD 0x7E9560 - CLSID_House.
extern const CLSID CLSID_House;
// GLOBAL: GAMEMD 0x7E36C0 - the interface id requested from the global object below.
extern const IID DAT_007E36C0;
// GLOBAL: GAMEMD 0x89A29C - the object the main interface is queried from.
extern unsigned char HouseMainObject;

// FUNCTION: GAMEMD 0x429360 (decl; reloc) - queries an interface of a global object.
void __stdcall HouseQueryObjectInterface(void* object, const IID* riid, void** result);

// FUNCTION: GAMEMD 0x7DC720 (decl; reloc; LIBRARY, comsupp) - throws the COM error
void __stdcall HouseComIssueError(long hr);

// GLOBAL: GAMEMD 0xA80228 - HouseClass::Array (Items at +0x04 = 0xA8022C, Count at +0x10 = 0xA80238).
extern HouseDynVector<HouseClusterView*> HouseArray;
// GLOBAL: GAMEMD 0xB0F670 / 0xB0F640 / 0xB0F5F0 / 0xB0F618 / 0xB0F720 - global object lists the
// constructor registers the house in, one after the other (element types unproven, all house pointers).
extern HouseDynVector<HouseClusterView*> HouseListB0F670;
extern HouseDynVector<HouseClusterView*> HouseListB0F640;
extern HouseDynVector<HouseClusterView*> HouseListB0F5F0;
extern HouseDynVector<HouseClusterView*> HouseListB0F618;
extern HouseDynVector<HouseClusterView*> HouseListB0F720;
// GLOBAL: GAMEMD 0xA8B228 / 0xA8E358 / 0xA83CF0 / 0xA83C78 - the type-array counts the unit trackers are sized from.
extern int HouseAircraftTypeCount;
extern int HouseInfantryTypeCount;
extern int HouseUnitTypeCount;
extern int HouseBuildingTypeCount;
// GLOBAL: GAMEMD 0x889F64 - the default interface name text copied into UINameString.
extern char HouseDefaultName[];
// GLOBAL: GAMEMD 0x7E9550 - the id handed to the connection-point source object.
extern const IID DAT_007E9550;

#include "../economy/house_class_cost_multipliers_methods.h"

#include "../economy/house_class_first_buildable_methods.h"

#include "../economy/house_class_register_built_methods.h"

#include "../economy/house_class_remove_tracking_methods.h"

#include "../economy/house_class_silos_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EA758
extern const double DAT_007EA758;
// GLOBAL: GAMEMD 0xA8EFA0
extern double DAT_00A8EFA0;
// GLOBAL: GAMEMD 0xA8F018
extern double DAT_00A8F018;
// GLOBAL: GAMEMD 0xA8F020
extern int DAT_00A8F020;
// GLOBAL: GAMEMD 0xA8F024
extern int DAT_00A8F024;
// GLOBAL: GAMEMD 0xA8F028
extern int DAT_00A8F028;
// GLOBAL: GAMEMD 0xA8F030
extern double DAT_00A8F030;

// FUNCTION: GAMEMD 0x4F4F30
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_004F4F30()
{
    DAT_00A8F030 = DAT_00A8EFA0 / DAT_007EA758;
}

// FUNCTION: GAMEMD 0x4F4F50
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_004F4F50()
{
    DAT_00A8F018 = DAT_007E1718 / DAT_00A8F030;
}

// FUNCTION: GAMEMD 0x4F50D0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_004F50D0()
{
    DAT_00A8F028 = 0;
    DAT_00A8F020 = 0x80;
    DAT_00A8F024 = 0x80;
}

// CAPPED at 98.3% (multiset identical; 17 instructions differ in order or register only: the -1 constant
// load near +0x214, the five byte stores near +0x3BB, a push near +0x69F, one add operand order near
// +0xBC6, two fill-setup orders). Variants tried: memset vs element loops for the fills, vector ctor with
// init list vs body assignments (body kept), AddItem shapes.
// FUNCTION: GAMEMD 0x4F54A0
HouseClusterView::HouseClusterView(HouseTypeView* type)
    : ArrayIndex(-1),
      Type(type),
      RelatedTags(0, 0),
      ConYards(0, 0),
      Buildings(0, 0),
      UnitRepairStations(0, 0),
      Grinders(0, 0),
      Absorbers(0, 0),
      Bunkers(0, 0),
      Occupiables(0, 0),
      CloningVats(0, 0),
      SecretLabs(0, 0),
      PsychicDetectionBuildings(0, 0),
      FactoryPlants(0, 0),
      CountResourceGatherers(0),
      CountResourceDestinations(0),
      CountWarfactories(0),
      InfantrySelfHeal(0),
      UnitsSelfHeal(0),
      StartingUnits(0, 0),
      AIDifficulty(HouseScenario->Difficulty),
      FirepowerMultiplier(1.0),
      GroundspeedMultiplier(1.0),
      AirspeedMultiplier(1.0),
      ArmorMultiplier(1.0),
      ROFMultiplier(1.0),
      CostMultiplier(1.0),
      BuildTimeMultiplier(1.0),
      RepairDelay(0.0),
      BuildDelay(0.0),
      IQLevel(0),
      TechLevel(1),
      AltAllies(0),
      StartingCredits(0),
      StartingEdge(-1),
      AIState_1E4(0),
      IsHumanPlayer(false),
      IsInPlayerControl(false),
      Production(false),
      AutocreateAllowed(false),
      NodeLogic_1F0(true),
      ShipYardConst_1F1(false),
      AITriggersActive(false),
      AutoBaseBuilding(false),
      DiscoveredByPlayer(false),
      Defeated(false),
      IsGameOver(false),
      IsWinner(false),
      IsLoser(false),
      CiviliansEvacuated(false),
      FirestormActive(false),
      HasThreatNode(false),
      RecheckTechTree(true),
      IPAddress(0),
      TournamentTeamID(0),
      LostConnection(false),
      SelectedPathIndex(-1),
      Visionary(0),
      MapIsClear(false),
      IsTiberiumShort(false),
      HasBeenSpied(false),
      HasBeenThieved(false),
      Repairing(false),
      IsBuiltSomething(false),
      IsResigner(false),
      IsGiverUpper(false),
      AllToHunt(false),
      IsParanoid(false),
      IsToLook(true),
      IQLevel2(IQLevel),
      AIMode(0),
      Supers(0, 0),
      LastBuiltBuildingType(-1),
      LastBuiltInfantryType(-1),
      LastBuiltAircraftType(-1),
      LastBuiltVehicleType(-1),
      AllowWinBlocks(0),
      Side2TechInfiltrated(false),
      Side1TechInfiltrated(false),
      Side0TechInfiltrated(false),
      BarracksInfiltrated(false),
      WarFactoryInfiltrated(false),
      InfantryAltOwner(0),
      UnitAltOwner(0),
      AircraftAltOwner(0),
      BuildingAltOwner(0),
      AirportDocks(0),
      PoweredUnitCenters(0),
      CreditsSpent(0),
      HarvestedCredits(0),
      StolenBuildingsCredits(0),
      OwnedUnits(0),
      OwnedNavy(0),
      OwnedBuildings(0),
      OwnedInfantry(0),
      OwnedAircraft(0),
      Balance(0),
      TotalStorage(0),
      NumAirpads(0),
      NumBarracks(0),
      NumWarFactories(0),
      NumConYards(0),
      NumShipyards(0),
      NumOrePurifiers(0),
      CostInfantryMult(1.0f),
      CostUnitsMult(1.0f),
      CostAircraftMult(1.0f),
      CostBuildingsMult(1.0f),
      CostDefensesMult(1.0f),
      PowerOutput(0),
      PowerDrain(0),
      Primary_ForAircraft(0),
      Primary_ForInfantry(0),
      Primary_ForVehicles(0),
      Primary_ForShips(0),
      Primary_ForBuildings(0),
      Primary_Unused1(0),
      Primary_Unused2(0),
      Primary_Unused3(0),
      Primary_ForDefenses(0),
      AircraftType_53D0(0),
      InfantryType_53D1(0),
      VehicleType_53D2(0),
      ShipType_53D3(0),
      BuildingType_53D4(0),
      unknown_53D5(0),
      unknown_53D6(0),
      unknown_53D7(0),
      DefenseType_53D8(0),
      OurFlagCarrier(0),
      OurFlagCoords(0, 0),
      TotalKilledUnits(0),
      TotalKilledBuildings(0),
      WhoLastHurtMe(-1),
      BaseSpawnCell(HouseEmptyCell),
      BaseCenter(HouseEmptyCell),
      Radius(0),
      LATime(0),
      LAEnemy(-1),
      ToCapture(0),
      RadarVisibleTo(0),
      PointTotal(0),
      PreferredTargetType(1),
      PreferredTargetCell(0, 0),
      PreferredDefensiveCell(0, 0),
      PreferredDefensiveCell2(0, 0),
      PreferredDefensiveCellStartTime(-100),
      AttackTimer(),
      InitialAttackDelay(0),
      EnemyHouseIndex(-1),
      AngerNodes(0, 0),
      ScoutNodes(0, 0),
      ProducingBuildingTypeIndex(-1),
      ProducingUnitTypeIndex(-1),
      ProducingInfantryTypeIndex(-1),
      ProducingAircraftTypeIndex(-1),
      RatioAITriggerTeam(100),
      RatioTeamAircraft(75),
      RatioTeamInfantry(75),
      RatioTeamBuildings(75),
      BaseDefenseTeamCount(0),
      CurrentDropshipIndex(0),
      HasCloakingRanges(false),
      Color(0, 0, 0),
      LaserColor(255, 255, 255),
      RecheckPower(true),
      RecheckRadar(true),
      SpySatActive(false),
      IsBeingDrained(false),
      Edge(0),
      EMPTarget(0, 0),
      NukeTarget(0, 0),
      Allies(0),
      DamageDelayTimer((int)(HouseRules->DamageDelay * 900.0)),
      TeamDelayTimer(1),
      TriggerDelayTimer(),
      SpeakAttackDelayTimer(1),
      SpeakPowerDelayTimer(1),
      SpeakMoneyDelayTimer(1),
      SpeakMaxedDelayTimer(1),
      AIGeneral(0),
      ColorSchemeIndex(0),
      unknown_16060(0),
      ConnectionPoints(0, 0),
      unknown_1607C(0),
      unknown_16080(0),
      unused_16088(1.0),
      unused_16090(1.0),
      PredictionEnemyArmor(0.33f),
      PredictionEnemyAir(0.33f),
      PredictionEnemyInfantry(0.33f),
      TotalOwnedInfantryCost(0),
      TotalOwnedVehicleCost(0),
      TotalOwnedAircraftCost(0),
      PowerSurplus(0)
{
    UINameString.Assign(HouseDefaultName);
    UIName[0] = 0;
    HBRttiBase::Create_ID();
    if (Type)
        ColorSchemeIndex = Type->ColorScheme;
    HouseListB0F670.AddItem(this);
    HouseListB0F640.AddItem(this);
    HouseListB0F5F0.AddItem(this);
    HouseListB0F618.AddItem(this);
    HouseListB0F720.AddItem(this);
    ArrayIndex = HouseArray.Count;
    if (type) {
        for (int i = 0; i < HouseArray.Count; i++) {
            HouseArray.Items[i]->AngerNodes.AddItem(HouseAngerNode(this, 0));
            AngerNodes.AddItem(HouseAngerNode(HouseArray.Items[i], 0));
            HouseArray.Items[i]->ScoutNodes.AddItem(HouseScoutNode(this, false));
            ScoutNodes.AddItem(HouseScoutNode(HouseArray.Items[i], false));
        }
    }
    HouseArray.AddItem(this);

    memset(ThreatPosedEstimates, 0, sizeof(ThreatPosedEstimates));
    for (int i = 0; i < HouseSuperTypeCount; i++) {
        HouseSuperObject* super = new HouseSuperObject(HouseSuperTypeItems[i], this);
        Supers.AddItem(super);
    }
    memset(KilledUnitsOfHouses, 0, sizeof(KilledUnitsOfHouses));
    memset(KilledBuildingsOfHouses, 0, sizeof(KilledBuildingsOfHouses));
    if (type) {
        PlainName.Assign(type->Name);
        wcscpy((wchar_t*)UIName, type->UIName);
    }
    memset(ThreatPosedEstimates, 0, sizeof(ThreatPosedEstimates));
    AltAllies |= 1 << ArrayIndex;
    int attackDelay = (int)(HouseScenario->Random.RandomRanged(450, 1800) * HouseRules->AttackDelay);
    AttackTimer = HouseTimer(attackDelay);
    InitialAttackDelay = attackDelay;
    BuiltAircraftTypes.Init(HouseAircraftTypeCount);
    BuiltInfantryTypes.Init(HouseInfantryTypeCount);
    BuiltUnitTypes.Init(HouseUnitTypeCount);
    BuiltBuildingTypes.Init(HouseBuildingTypeCount);
    KilledAircraftTypes.Init(HouseAircraftTypeCount);
    KilledInfantryTypes.Init(HouseInfantryTypeCount);
    KilledUnitTypes.Init(HouseUnitTypeCount);
    KilledBuildingTypes.Init(HouseBuildingTypeCount);
    CapturedBuildings.Init(HouseBuildingTypeCount);
    CollectedCrates.Init(19);
    for (int k = 0; k < 12; k++)
        PlanningPaths[k] = 0;
    if (type)
        HasThreatNode = true;
    SideIndex = -1;
    if (Type) {
        int side = Type->Side;
        if (side == 0)
            SideIndex = 0;
        else if (side == 1)
            SideIndex = side;
        else if (side == 2)
            SideIndex = side;
    }

    IUnknown* unknown = 0;
    HouseClusterView::QueryInterface(IID_IUnknown, (void**)&unknown);
    HouseConnPtSource* source = new HouseConnPtSource(&DAT_007E9550, unknown);
    unknown_1607C = (unsigned int)source;
    IConnectionPoint* point;
    source->QueryInterface(IID_IConnectionPoint, (void**)&point);
    ConnectionPoints.AddItem(point);
    unknown->Release();
}

// FUNCTION: GAMEMD 0x4F6830
HRESULT __stdcall HouseClusterView::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == 0)
        return E_POINTER;

    *ppv = 0;
    if (memcmp(&riid, &IID_IUnknown, sizeof(IID)) == 0)
        *ppv = this;
    if (memcmp(&riid, &IID_IHouse, sizeof(IID)) == 0)
        *ppv = static_cast<HouseIHouseBase*>(this);
    if (memcmp(&riid, &IID_IPublicHouse, sizeof(IID)) == 0)
        *ppv = static_cast<HousePublicHouseBase*>(this);
    if (memcmp(&riid, &IID_IConnectionPointContainer, sizeof(IID)) == 0)
        *ppv = static_cast<IConnectionPointContainer*>(this);
    if (memcmp(&riid, &IID_IPersist, sizeof(IID)) == 0)
        *ppv = this;
    if (memcmp(&riid, &IID_IPersistStream, sizeof(IID)) == 0)
        *ppv = this;

    if (*ppv == 0)
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

// FUNCTION: GAMEMD 0x4F6910
bool __stdcall HouseClusterView::HasEnoughPower()
{
    return PowerOutput >= PowerDrain;
}

// FUNCTION: GAMEMD 0x4F6930
IUnknown* __stdcall HouseClusterView::GetMainInterface()
{
    IUnknown* result;
    HouseQueryObjectInterface(&HouseMainObject, &DAT_007E36C0, (void**)&result);
    return result;
}

// FUNCTION: GAMEMD 0x4F6950
BSTR __stdcall HouseClusterView::GetName()
{
    WCHAR buffer[32];
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Type->NameBuffer, -1, buffer, 32);
    return SysAllocString(buffer);
}

// FUNCTION: GAMEMD 0x4F6990
int __stdcall HouseClusterView::GetCredits()
{
    float multiplier = Type->ValueMultiplier;
    return (int)(OwnedTiberium.GetTotalValue() * multiplier + Balance);
}

// FUNCTION: GAMEMD 0x4F69D0
int __stdcall HouseClusterView::GetTiberiumStored()
{
    return TotalStorage - (int)OwnedTiberium.GetTotalAmount();
}

// FUNCTION: GAMEMD 0x4F6A00
int __stdcall HouseClusterView::GetPowerOutput()
{
    return PowerOutput;
}

// FUNCTION: GAMEMD 0x4F6A10
int __stdcall HouseClusterView::GetPowerDrain()
{
    return PowerDrain;
}

// FUNCTION: GAMEMD 0x4F6A20
int __stdcall HouseClusterView::CountOwnedOfCategory(int category)
{
    int count = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        if (techno->Owner == this && techno->GetTechnoType()->Category == category)
            count++;
    }
    return count;
}

// FUNCTION: GAMEMD 0x4F6A80
int __stdcall HouseClusterView::PublicCountOwnedOfCategory(int category)
{
    int count = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        if (techno->Owner == this && techno->GetTechnoType()->Category == category)
            count++;
    }
    return count;
}

// FUNCTION: GAMEMD 0x4F6AE0
int __stdcall HouseClusterView::SumScoreOfCategory(int category)
{
    int total = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        HouseTechnoTypeView* type = techno->GetTechnoType();
        if (techno->Owner == this && type->Category == category)
            total += type->ThreatPosed + type->Points;
    }
    return total;
}

// FUNCTION: GAMEMD 0x4F6B50
int __stdcall HouseClusterView::PublicSumScoreOfCategory(int category)
{
    int total = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        HouseTechnoTypeView* type = techno->GetTechnoType();
        if (techno->Owner == this && type->Category == category)
            total += type->ThreatPosed + type->Points;
    }
    return total;
}

// FUNCTION: GAMEMD 0x4F6BC0
void* __stdcall HouseClusterView::GetBaseCenter(void* cell)
{
    HBCell center;
    center.X = HouseCellCoord(HouseBaseCell()).X / 256;
    center.Y = HouseCellCoord(HouseBaseCell()).Y / 256;
    *(HBCell*)cell = center;
    return cell;
}

// FUNCTION: GAMEMD 0x4F6D10
void* __stdcall HouseClusterView::PublicGetBaseCenter(void* cell)
{
    HBCell center;
    center.X = HouseCellCoord(HouseBaseCell()).X / 256;
    center.Y = HouseCellCoord(HouseBaseCell()).Y / 256;
    *(HBCell*)cell = center;
    return cell;
}

// FUNCTION: GAMEMD 0x4F6E60
int __stdcall HouseClusterView::GetIndex()
{
    return ArrayIndex;
}

// FUNCTION: GAMEMD 0x004F6EB0
void FUN_004F6EB0()
{
}

// FUNCTION: GAMEMD 0x4F7850
// Stores several members.
Obj_004F7850* Obj_004F7850::FUN_004F7850()
{
    unknown_00 = 0;
    unknown_04 = 1;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = -1;
    return this;
}

// FUNCTION: GAMEMD 0x4F9970
//
// Redraw every silo when the house's fill level changes. Both the previous
// and the current storage are reduced to a quarter-step (0..4, rounded) and
// nothing happens unless the step moved; then every live, on-map building of a
// silo-capable type is re-marked so its fill art updates.
void House_004F9970::UpdateAllSilos(int prevStorage, int prevTotalStorage)
{
    int before = 0;
    if (prevTotalStorage != 0) {
        before = (int)((double)prevStorage / prevTotalStorage * 4.0 + 0.5);
    }

    int after = 0;
    if (this->TotalStorage != 0) {
        after = (int)(this->OwnedTiberium.GetTotalAmount() / this->TotalStorage * 4.0 + 0.5);
    }

    if (before != after) {
        int count = this->unknown_78;
        for (int i = 0; i < count; i++) {
            Building_004F9970* b = this->BuildingItems[i];
            if (b != 0 && !b->InLimbo && b->Type->At_16A8) {
                (b->*(*(BuildingVtbl_004F9970**)b)->Mark)(2);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4FB6B0  HouseClass::RegisterJustBuilt (__thiscall, ret 4)
//
// A factory has just finished something. The house records which type it was
// per category, bumps that category's per-type tally unless the type opts out,
// and picks the "unit ready" announcement: the rules-wide one for the category,
// overridden by the type's own creation sound when it has one. Nothing is said
// for buildings unless their type supplies a sound.
void House_004FB6B0::RegisterJustBuilt(Techno_004FB6B0* pTechno)
{
    int voice = -1;

    this->At_246 = 1;

    TechnoType_004FB6B0* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();

    switch ((pTechno->*pTechno->Vtbl->WhatAmI)()) {
    case 1:
        this->At_274 = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->UnitCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        voice = RulesInstance_004FB6B0->At_178;
        break;

    case 15:
        this->At_270 = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->InfantryCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        voice = RulesInstance_004FB6B0->At_17C;
        break;

    case 6:
        this->At_26C = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->BuildingCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 2:
        this->At_278 = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->AircraftCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        voice = RulesInstance_004FB6B0->At_180;
        break;
    }

    if (pType->At_534 != -1) {
        voice = pType->At_534;
    }

    if (voice != -1) {
        Coord_004FB6B0 coords = pTechno->Location;
        VocClass_PlayAt_004FB6B0(voice, coords, 0);
    }

    this->At_1FC = 1;
}

// FUNCTION: GAMEMD 0x4FB9B0
void HouseClusterView::PointerExpired(HouseAbstractPtrView* pointer, bool removed)
{
    if (ToCapture == pointer)
        ToCapture = 0;

    HouseTagRef* tag = (HouseTagRef*)HouseRtDynamicCast(pointer, 0, HouseTypeDesc_AbstractClass, HouseTypeDesc_TagClass, 0);
    if (tag)
        RelatedTags.RemoveItem(tag);

    if (pointer->WhatAmI() == 6 && removed) {
        int index = ConYards.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            ConYards.RemoveAt(index);
        UnitRepairStations.RemoveItem((HouseBuildingRef*)pointer);
        index = Grinders.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            Grinders.RemoveAt(index);
        Absorbers.RemoveItem((HouseBuildingRef*)pointer);
        index = Bunkers.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            Bunkers.RemoveAt(index);
        Occupiables.RemoveItem((HouseBuildingRef*)pointer);
        index = CloningVats.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            CloningVats.RemoveAt(index);
        index = SecretLabs.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            SecretLabs.RemoveAt(index);
        PsychicDetectionBuildings.RemoveItem((HouseBuildingRef*)pointer);
        index = FactoryPlants.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            FactoryPlants.RemoveAt(index);
        Buildings.RemoveItem((HouseBuildingRef*)pointer);
        CalculateCostMultipliers();
    }

    for (int i = 0; i < 12; i++) {
        if (PlanningPaths[i] == pointer)
            PlanningPaths[i] = 0;
    }
    if (Primary_ForAircraft == pointer)
        Primary_ForAircraft = 0;
    if (Primary_ForInfantry == pointer)
        Primary_ForInfantry = 0;
    if (Primary_ForVehicles == pointer)
        Primary_ForVehicles = 0;
    if (Primary_ForShips == pointer)
        Primary_ForShips = 0;
    if (Primary_ForBuildings == pointer)
        Primary_ForBuildings = 0;
    if (Primary_Unused1 == pointer)
        Primary_Unused1 = 0;
    if (Primary_Unused2 == pointer)
        Primary_Unused2 = 0;
    if (Primary_Unused3 == pointer)
        Primary_Unused3 = 0;
    if (Primary_ForDefenses == pointer)
        Primary_ForDefenses = 0;
}

// FUNCTION: GAMEMD 0x4FD060
//
// The first live building this house owns whose type has the given array
// index, optionally restricted to one map sector. The per-type counter is
// consulted first so houses without such a building skip the walk.
Building_004FD060* House_004FD060::FindBuildingOfType(int index, int sector)
{
    if (this->At_5500.GetCount(index) > 0) {
        int count = this->unknown_78;
        for (int i = 0; i < count; ++i) {
            Building_004FD060* building = this->BuildingItems[i];
            if (building != 0 && building->InLimbo == 0) {
                if (TypeIndex_004FD060(building->Type) == index) {
                    if (sector == -1) {
                        return building;
                    }
                    Coord_004FD060 buf;
                    if (this->SectorOf((building->*building->Vtbl->GetCoords)(&buf)) == sector) {
                        return building;
                    }
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4FF540
void __stdcall FUN_004FF540(int)
{
}

// FUNCTION: GAMEMD 0x4FF550  HouseClass::RemoveTracking (__thiscall, ret 4)
//
// The mirror of RegisterJustBuilt: an object has left the house's books. It
// clears the object's "tracked" flag, then — unless the type opts out of
// tracking entirely — walks down the per-category owned counts and the
// per-type tally for the category the object belongs to. Buildings are split
// between two counts depending on whether they are power/production relevant;
// infantry only decrement while their "still counted" flag is set; units also
// give back a second count when their type asks for it.
void House_004FF550::RemoveTracking(Techno_004FF550* pTechno)
{
    pTechno->At_3CC = false;

    if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_232 != 0) {
        return;
    }

    if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_C9F != 0) {
        return;
    }

    switch ((pTechno->*pTechno->Vtbl->WhatAmI)()) {
    case 6:
        if (!(pTechno->*pTechno->Vtbl->At_80)()
            && (pTechno->At_520->At_408 == 0
                || pTechno->At_520->At_408->At_5EC == 0)) {
            this->At_2F0--;
        } else {
            this->At_2E8--;
        }
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->BuildingCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 2:
        this->At_2F8--;
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->AircraftCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 15:
        if (pTechno->At_438 != 0) {
            this->At_2F4--;
            pTechno->At_438 = false;
        }
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->InfantryCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 1:
        this->At_2E8--;
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->UnitCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_CCE != 0) {
            if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_5E0 == 0) {
                this->At_2EC--;
            }
        }
        break;
    }
}

// FUNCTION: GAMEMD 0x5004E0  (static __fastcall)
//
//   PUSH ESI / MOV ESI,ECX            ESI = abstractID
//   TEST EDX,EDX / JGE                idx < 0  -> return 0
//   MOV ECX,ESI / CALL 0x48DCD0       p = ObjTypeFindFromCat(abstractID, idx)
//   CMP ESI,6 JZ / CMP ESI,7 JZ       abstractID must be 6 or 7
//   (else)  XOR EAX,EAX / RET         return 0
//   MOV EAX,[EAX+0xE08] / RET         return *(int*)(p + 0xE08)
//
// abstractID is held in ESI (callee-saved) across the call so the two CMPs run
// after it; idx stays live in EDX up to the call.
int ObjectTypeClass::IsBuildCat5(int abstractID, int idx)
{
    char* p;
    if (idx < 0)
        return 0;
    p = ObjTypeFindFromCat(abstractID, idx);
    if (abstractID != 6 && abstractID != 7)
        return 0;
    return *(int*)(p + 0xE08);
}

// FUNCTION: GAMEMD 0x5013A0
int __stdcall HouseClusterView::SellAllBuildings()
{
    if (OwnedBuildings > 0) {
        int count = Buildings.Count;
        for (int i = 0; i < count; i++) {
            HouseTechnoView* building = (HouseTechnoView*)Buildings.Items[i];
            if (building && !building->InLimbo && building->Strength > 0)
                building->vf_104(1);
        }
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x501400
int __stdcall HouseClusterView::DestroyAllTechnos()
{
    for (int i = HouseTechnoArray.Count - 1; i >= 0; i--) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        if (this == techno->Owner && techno->IsOnMap && !techno->InLimbo) {
            if (techno->MindControlled && techno->GetTechnoType()->Insignificant && !IsHumanPlayer) {
                int damage = techno->GetTechnoType()->unknown_A0;
                techno->ReceiveDamage(&damage, 0, HouseRules->unknown_FA8, 0, true, true, 0);
            } else if (techno) {
                if (HouseIsFoot(techno)) {
                    if (techno->unknown_5D4)
                        techno->unknown_5D4->M_6EA870(techno, -1, 0);
                    techno->vf_122(15, 0);
                } else if (techno->WhatAmI() == 6) {
                    if (techno->vf_258() > 0)
                        techno->M_457DE0(1, 0);
                }
            }
        }
    }
    AllToHunt = true;
    return 0;
}

// FUNCTION: GAMEMD 0x5024F0
HRESULT __stdcall HouseClusterView::EnumConnectionPoints(IEnumConnectionPoints** ppEnum)
{
    if (ppEnum == 0)
        return E_POINTER;

    HouseConnPtEnum* enumerator = new HouseConnPtEnum(&ConnectionPoints);
    if (enumerator == 0)
        return E_OUTOFMEMORY;

    enumerator->AddRef();
    *ppEnum = enumerator;
    return S_OK;
}

// FUNCTION: GAMEMD 0x502550
HRESULT __stdcall HouseClusterView::FindConnectionPoint(REFIID riid, IConnectionPoint** ppCP)
{
    if (ppCP == 0)
        return E_POINTER;

    *ppCP = 0;
    for (int i = 0; i < ConnectionPoints.Count; i++) {
        IConnectionPoint* point = ConnectionPoints.Items[i];
        IID id;
        point->GetConnectionInterface(&id);
        if (memcmp(&id, &riid, sizeof(IID)) == 0) {
            *ppCP = point;
            point->AddRef();
            return S_OK;
        }
    }
    return CONNECT_E_CANNOTCONNECT;
}

// CAPPED at 91.7%: the three inlined timer reads load the start into EDX and the frame into ECX in
// retail, the reverse here (18 register-only differences, multiset identical). Variants: conditional
// form, early-return form, local-copy form, ternary form.
// FUNCTION: GAMEMD 0x502D60
void HouseClusterView::ComputeCrc(HouseCrcView* crc)
{
    HouseAbstractView::ComputeCrc(crc);
    crc->AddInt(AIDifficulty);
    crc->AddInt(Type->ArrayIndex2);
    crc->AddDouble(FirepowerMultiplier);
    crc->AddDouble(GroundspeedMultiplier);
    crc->AddDouble(AirspeedMultiplier);
    crc->AddDouble(ArmorMultiplier);
    crc->AddDouble(ROFMultiplier);
    crc->AddDouble(CostMultiplier);
    crc->AddDouble(BuildTimeMultiplier);
    crc->AddDouble(RepairDelay);
    crc->AddDouble(BuildDelay);
    crc->AddBool(IsHumanPlayer);
    crc->AddBool(Production);
    crc->AddBool(AutocreateAllowed);
    crc->AddBool(AITriggersActive);
    crc->AddBool(Defeated);
    crc->AddInt(IQLevel2);
    crc->AddInt(AIMode);
    crc->AddInt(AllowWinBlocks);
    crc->AddInt(RepairTimer.GetTimeLeft());
    crc->AddInt(AlertTimer.GetTimeLeft());
    crc->AddInt(BorrowedTime.GetTimeLeft());
    crc->AddInt(OwnedUnits);
    crc->AddInt(OwnedBuildings);
    crc->AddInt(OwnedInfantry);
    crc->AddInt(OwnedAircraft);
    crc->AddInt(Balance);
    crc->AddInt(TotalStorage);
    crc->AddInt(NumAirpads);
    crc->AddInt(NumBarracks);
    crc->AddInt(NumWarFactories);
    crc->AddInt(NumShipyards);
    crc->AddInt(NumConYards);
    crc->AddInt(NumOrePurifiers);
    crc->AddInt(PowerOutput);
    crc->AddInt(PowerDrain);
    crc->AddBool(MapIsClear);
    crc->AddInt(WhoLastHurtMe);
    crc->AddInt(EnemyHouseIndex);
    Base.ComputeCrc(crc);
}

// CAPPED at 99.6%: six instructions differ, the grown-capacity add at the ConYards / Buildings /
// UnitRepairStations loads is `add ecx,eax` in retail and `add eax,ecx` here (multiset identical).
// Variants: cap+inc, inc+cap, Capacity member without a local, grown-capacity temporary.
// FUNCTION: GAMEMD 0x503040
HRESULT __stdcall HouseClusterView::Load(IStream* pStm)
{
    int i;
    int count;
    HRESULT hr;

    ConYards.Clear();
    Buildings.Clear();
    UnitRepairStations.Clear();
    Grinders.Clear();
    Absorbers.Clear();
    Bunkers.Clear();
    Occupiables.Clear();
    CloningVats.Clear();
    SecretLabs.Clear();
    PsychicDetectionBuildings.Clear();
    FactoryPlants.Clear();
    for (i = StartingUnits.Count - 1; i >= 0; i--)
        delete StartingUnits.Items[i];
    StartingUnits.Clear();
    for (i = 0; i < ConnectionPoints.Count; i++) {
        while (ConnectionPoints.Items[i]->Release() > 0)
            ;
        ConnectionPoints.Items[i] = 0;
    }
    ConnectionPoints.Clear();
    while (Supers.Count) {
        delete Supers.Items[0];
        if (0 < Supers.Count) {
            Supers.Count = Supers.Count - 1;
            for (i = 0; i < Supers.Count; ++i)
                Supers.Items[i] = Supers.Items[i + 1];
        }
    }

    hr = HouseAbstractView::Load(pStm);
    if (hr < 0)
        return hr;
    new (this) HouseClusterView(HBNoInit());
    Base.LoadFromStream(pStm);
    OwnedBuildingTypes.Load(pStm);
    OwnedUnitTypes.Load(pStm);
    OwnedInfantryTypes.Load(pStm);
    OwnedAircraftTypes.Load(pStm);
    ActiveBuildingTypes.Load(pStm);
    ActiveUnitTypes.Load(pStm);
    ActiveInfantryTypes.Load(pStm);
    ActiveAircraftTypes.Load(pStm);
    FactoryProducedBuildingTypes.Load(pStm);
    FactoryProducedUnitTypes.Load(pStm);
    FactoryProducedInfantryTypes.Load(pStm);
    FactoryProducedAircraftTypes.Load(pStm);
    HouseSwizzle.Swizzle(&Type);
    HouseSwizzle.Swizzle(&Primary_ForInfantry);
    HouseSwizzle.Swizzle(&Primary_ForVehicles);
    HouseSwizzle.Swizzle(&Primary_ForAircraft);
    HouseSwizzle.Swizzle(&Primary_ForShips);
    HouseSwizzle.Swizzle(&Primary_ForBuildings);
    HouseSwizzle.Swizzle(&Primary_Unused1);
    HouseSwizzle.Swizzle(&Primary_Unused2);
    HouseSwizzle.Swizzle(&Primary_Unused3);
    HouseSwizzle.Swizzle(&Primary_ForDefenses);
    HouseSwizzle.Swizzle(&ToCapture);
    for (i = 0; i < 12; i++)
        HouseSwizzle.Swizzle(&PlanningPaths[i]);
    for (i = 0; i < 3; i++)
        DropshipData[i].Swizzle();

    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseSuperRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Supers.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseTagRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        RelatedTags.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseAngerNode node;
        node.House = 0;
        node.Value = 0;
        hr = pStm->Read(&node, 8, 0);
        if (hr < 0)
            return hr;
        AngerNodes.AddItem(node);
    }
    for (i = 0; i < AngerNodes.Count; i++)
        HouseSwizzle.Swizzle(&AngerNodes.Items[i]);
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseScoutNode node;
        node.Cell = 0;
        node.Flag = false;
        hr = pStm->Read(&node, 8, 0);
        if (hr < 0)
            return hr;
        ScoutNodes.AddItem(node);
    }
    for (i = 0; i < ScoutNodes.Count; i++)
        HouseSwizzle.Swizzle(&ScoutNodes.Items[ScoutNodes.Count - 1]);
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        ConYards.AddItemCapFirst(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Buildings.AddItemCapFirst(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        UnitRepairStations.AddItemCapFirst(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Grinders.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Absorbers.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Bunkers.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Occupiables.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        CloningVats.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        SecretLabs.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        PsychicDetectionBuildings.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        FactoryPlants.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseStartingUnit* unit = new HouseStartingUnit;
        int type = 0;
        short x;
        short y;
        hr = pStm->Read(&type, 4, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Read(&x, 2, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Read(&y, 2, 0);
        if (hr < 0)
            return hr;
        unit->Type = type;
        unit->X = x;
        unit->Y = y;
        StartingUnits.AddItem(unit);
    }

    for (i = 0; i < Supers.Count; i++)
        HouseSwizzle.Swizzle(&Supers.Items[i]);
    for (i = 0; i < RelatedTags.Count; i++)
        HouseSwizzle.Swizzle(&RelatedTags.Items[i]);
    for (i = 0; i < ConYards.Count; i++)
        HouseSwizzle.Swizzle(&ConYards.Items[i]);
    for (i = 0; i < Buildings.Count; i++)
        HouseSwizzle.Swizzle(&Buildings.Items[i]);
    for (i = 0; i < UnitRepairStations.Count; i++)
        HouseSwizzle.Swizzle(&UnitRepairStations.Items[i]);
    for (i = 0; i < Grinders.Count; i++)
        HouseSwizzle.Swizzle(&Grinders.Items[i]);
    for (i = 0; i < Absorbers.Count; i++)
        HouseSwizzle.Swizzle(&Absorbers.Items[i]);
    for (i = 0; i < Bunkers.Count; i++)
        HouseSwizzle.Swizzle(&Bunkers.Items[i]);
    for (i = 0; i < Occupiables.Count; i++)
        HouseSwizzle.Swizzle(&Occupiables.Items[i]);
    for (i = 0; i < CloningVats.Count; i++)
        HouseSwizzle.Swizzle(&CloningVats.Items[i]);
    for (i = 0; i < SecretLabs.Count; i++)
        HouseSwizzle.Swizzle(&SecretLabs.Items[i]);
    for (i = 0; i < PsychicDetectionBuildings.Count; i++)
        HouseSwizzle.Swizzle(&PsychicDetectionBuildings.Items[i]);
    for (i = 0; i < FactoryPlants.Count; i++)
        HouseSwizzle.Swizzle(&FactoryPlants.Items[i]);
    for (i = 0; i < StartingUnits.Count; i++)
        HouseSwizzle.Swizzle(StartingUnits.Items[i]);

    int hasAIGeneral = 0;
    hr = pStm->Read(&hasAIGeneral, 4, 0);
    if (hr < 0 || !hasAIGeneral)
        return hr;
    return OleLoadFromStream(pStm, DAT_007E9AF0, (void**)&AIGeneral);
}

// FUNCTION: GAMEMD 0x504080
HRESULT __stdcall HouseClusterView::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT result = HouseAbstractView::Save(pStm, fClearDirty);

    if (result >= 0) {
    Base.SaveToStream(pStm);
    OwnedBuildingTypes.Save(pStm);
    OwnedUnitTypes.Save(pStm);
    OwnedInfantryTypes.Save(pStm);
    OwnedAircraftTypes.Save(pStm);
    ActiveBuildingTypes.Save(pStm);
    ActiveUnitTypes.Save(pStm);
    ActiveInfantryTypes.Save(pStm);
    ActiveAircraftTypes.Save(pStm);
    FactoryProducedBuildingTypes.Save(pStm);
    FactoryProducedUnitTypes.Save(pStm);
    FactoryProducedInfantryTypes.Save(pStm);
    FactoryProducedAircraftTypes.Save(pStm);

    int i;
    int count = Supers.Count;
    HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Supers.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = RelatedTags.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&RelatedTags.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = AngerNodes.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&AngerNodes.Items[i], 8, 0);
        if (hr < 0)
            return hr;
    }
    count = ScoutNodes.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&ScoutNodes.Items[i], 8, 0);
        if (hr < 0)
            return hr;
    }
    count = ConYards.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&ConYards.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Buildings.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Buildings.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = UnitRepairStations.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&UnitRepairStations.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Grinders.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Grinders.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Absorbers.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Absorbers.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Bunkers.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Bunkers.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Occupiables.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Occupiables.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = CloningVats.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&CloningVats.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = SecretLabs.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&SecretLabs.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = PsychicDetectionBuildings.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&PsychicDetectionBuildings.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = FactoryPlants.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&FactoryPlants.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = StartingUnits.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        HouseStartingUnit* unit = StartingUnits.Items[i];
        hr = pStm->Write(unit, 4, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Write(&unit->X, 2, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Write(&unit->Y, 2, 0);
        if (hr < 0)
            return hr;
    }

    int hasAIGeneral = AIGeneral != 0;
    result = pStm->Write(&hasAIGeneral, 4, 0);
    if (result >= 0 && hasAIGeneral) {

    IUnknown* general = AIGeneral;
    IPersistStream* persist = 0;
    if (general) {
        IPersistStream* queried;
        HRESULT queryResult = general->QueryInterface(DAT_00820270, (void**)&queried);
        persist = FAILED(queryResult) ? 0 : queried;
        if (!SUCCEEDED(queryResult) && queryResult != E_NOINTERFACE)
            HouseComIssueError(queryResult);
    }
    result = OleSaveToStream(persist, pStm);
    if (persist)
        persist->Release();
    }
    }
    return result;
}

// FUNCTION: GAMEMD 0x5046F0
HRESULT __stdcall HouseClusterView::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;

    *pClassID = CLSID_House;
    return S_OK;
}

// FUNCTION: GAMEMD 0x504730
int HouseClusterView::Size()
{
    return sizeof(HouseClusterView);
}

// FUNCTION: GAMEMD 0x504790
//
// Add `scoreAdd` to the anger level of every node tracking `house`, then
// re-pick the enemy: the angriest node whose house is not defeated and not an
// ally (the ally test is the 0x4F9A50 overload inlined). The winner's array
// index lands in EnemyHouseIndex, or -1 when no node qualifies.
void House_00504790::UpdateAngerNodes(int scoreAdd, House_00504790* house)
{
    int i;

    for (i = 0; i < this->AngerNodes.Count; i++) {
        if (this->AngerNodes.Items[i].House == house)
            this->AngerNodes.Items[i].AngerLevel += scoreAdd;
    }

    House_00504790* best = 0;
    int bestLevel = 0;

    for (i = 0; i < this->AngerNodes.Count; i++) {
        int level = this->AngerNodes.Items[i].AngerLevel;
        House_00504790* h = this->AngerNodes.Items[i].House;
        if (level > bestLevel && !h->Defeated && !this->IsAlliedWith(h)) {
            bestLevel = level;
            best = h;
        }
    }

    if (best != 0)
        this->EnemyHouseIndex = best->ArrayIndex;
    else
        this->EnemyHouseIndex = -1;
}

// FUNCTION: GAMEMD 0x5051E0
//
// First type in the list this house may build: owner bit for its parent
// country, required and forbidden house masks, AI base-planning side. A type
// carrying a super weapon is skipped when supers are allowed, unless it is a
// construction-yard type or its super cannot be disabled from the shell.
TechnoType_005051E0* House_005051E0::FirstBuildableFromArray(TypeVector_005051E0* items)
{
    unsigned int owner = 1 << HouseType_FindIndexOfName_005051E0(Type->ParentCountry);

    for (int i = 0; i < items->Count; i++) {
        TechnoType_005051E0* type = items->Items[i];
        if ((type->OwnerFlags & owner)
            && (type->RequiredHouses == 0xFFFFFFFF
                || (type->RequiredHouses & (1 << Type->ArrayIndex)))
            && (type->ForbiddenHouses == 0xFFFFFFFF
                || !(type->ForbiddenHouses & (1 << Type->ArrayIndex)))
            && (type->AIBasePlanningSide == -1
                || type->AIBasePlanningSide == Type->ArrayIndex2)) {
            if (DAT_00A8B263) {
                return type;
            }
            if (type->SuperWeapon == -1) {
                return type;
            }
            for (int j = 0; j < DAT_008871E0->BuildConstCount; j++) {
                if (DAT_008871E0->BuildConstItems[j] == type) {
                    return type;
                }
            }
            if (!SupersItems[type->SuperWeapon]->Type->DisableableFromShell) {
                return type;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x506B70
// Empty function.
void __cdecl FUN_00506B70()
{
}

// FUNCTION: GAMEMD 0x506B80
// Empty function.
void __cdecl FUN_00506B80()
{
}

// FUNCTION: GAMEMD 0x005095D0
// Count the entries of the global vector at 0x8B40E8 whose +0x2C is this
// object and whose +0x24 is `kind`, walking from the end.
int Obj_005095D0::FUN_005095D0(int kind)
{
    int count = 0;
    for (int i = DAT_008B40F8 - 1; i >= 0; i--) {
        Team_005095D0* team = DAT_008B40EC[i];
        if (team != NULL && team->unknown_2C == this && kind == team->unknown_24) {
            count++;
        }
    }
    return count;
}

// FUNCTION: GAMEMD 0x509CC0
// Empty function that pops its stack arguments.
void __stdcall FUN_00509CC0(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50BF60  HouseClass::CalculateCostMultipliers
//
// Start every cost multiplier at one and fold in each owned building's five
// type factors, re-reading the list pointer and the building for every
// factor as retail does.
//
// MATCHED 100% (44/44). The one lever: write the five multipliers through a
// `float*` local aimed at the first of them rather than through the named
// members. With the named float members cl 8804's type-based alias analysis
// proves the stores cannot touch the int `Count` and hoists
// `MOV EDX,[ECX+0x150]` above the whole function (4.3%); routing them through
// a float pointer makes the Count read live again, so the entry test loads it
// and the back edge re-reads it in place (`CMP EAX,dword ptr [ECX+0x150]`),
// which is exactly retail's loop. A `*(volatile int*)&Count` read in the loop
// condition gets the re-read too but costs a `MOV EDX,mem; CMP EAX,EDX` pair
// at the back edge instead of retail's folded memory compare (84.4%).
void House_0050BF60::CalculateCostMultipliers()
{
    float* mult = &InfantryCostMult;

    mult[0] = 1.0f;
    mult[1] = 1.0f;
    mult[2] = 1.0f;
    mult[3] = 1.0f;
    mult[4] = 1.0f;

    for (int i = 0; i < Buildings.Count; ++i) {
        mult[0] = Buildings[i]->Type->FactorInfantry * mult[0];
        mult[1] = Buildings[i]->Type->FactorUnits * mult[1];
        mult[2] = Buildings[i]->Type->FactorAircraft * mult[2];
        mult[3] = Buildings[i]->Type->FactorBuildings * mult[3];
        mult[4] = Buildings[i]->Type->FactorDefenses * mult[4];
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50C160
// Fp getter.
float Obj_0050C160::FUN_0050C160() const
{
    return unknown_34->unknown_148;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50C170
//
// Walk the global house list comparing each house's name against the caller's
// string; return the index of the first hit or -1. The name is first copied
// into a 20-byte frame buffer (retail's inlined strcpy: REPNE SCASB then REP
// MOVSD/MOVSB), and the comparison is the inlined strcmp byte loop. The count
// is re-read from the global at the end of every iteration.
int House_0050C170::FindIndexByName(const char* name)
{
    char buf[20];

    for (int i = 0; i < DAT_00A80238; i++) {
        strcpy(buf, DAT_00A8022C[i]->PlainName);
        if (strcmp(buf, name) == 0) {
            return i;
        }
    }

    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50D440
//
// Re-create the house's recorded starting forces, last entry first. Each
// entry's type is asked what it is; aircraft, building, unit and infantry
// types create an object for this house, which is kept only when its flag
// byte says it is a techno. The object is then unlimboed at the centre of the
// entry's cell, and torn down again through +0xF8 when that fails.
//
// The two case groups carry the same body twice: retail keeps two copies of
// the create-and-test and cross-jumps only the flag fold. The techno pointer
// is left null for any other kind of type and the unlimbo still dereferences
// it, as retail does. Score with scripts/vc6/raw_match.py: diff_retail.py
// also counts the embedded jump/index tables (19 junk `add`s) as instructions.
//
// PARTIAL (66.0%, 68/103 by diff_retail.py; 64/83 real instructions, mnemonic
// multiset identical). The whole residual is one register swap: retail keeps
// `this` in EBX and the entry pointer in EBP, cl 8804 the other way round, so
// the prologue/epilogue pushes and every use of the two (`MOV EBX,ECX`,
// `[EBX+0x17C]`, `[EBX+0x170]`, `PUSH EBX` x2, `MOV EBP,[ECX+EAX*4]`,
// `[EBP]`, `ADD EBP,4`, `PUSH EBP`) differ by name only; the loop, the
// spilled counter, the jump table, the switch bodies, the map lookup, the
// hidden-pointer GetCoords copy and the unlimbo tail are otherwise exact.
// Tried: a `house = this` alias outside and inside the loop; all locals
// declared at function scope; the entry as a reference, as `const`, or
// re-indexed (`Items[i]->Type` / `&Items[i]->Cell`, which reloads after the
// calls: 43.7%); a named cell pointer before the switch (43.7%); an inlined
// `operator[]` on the vector; per-case block-scoped `obj`; a `default:` arm
// (breaks the table); the create-and-test in a static inline helper and in an
// inline member helper (entry as an inlined parameter); the flag fold and the
// unlimbo tail in inline helpers; swapped case order; a `while` loop. None
// moves the assignment; recorded as an allocation-ranking residual.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply. Retail sinks
// PUSH EBP/ESI/EDI below the empty-vector early-out and our output sinks the
// same three in the same place; both sides jump the early exit straight onto
// the last POP of the staircase epilogue, so the two returns are already as
// split as retail's. Four further spellings measured this pass, all 66.0% and
// byte-identical to the control: the loop body lifted into a free
// `RespawnOne(house, i)` inline helper; the whole loop lifted into a free
// `RespawnAll(house)` inline helper; `this` bound to a named `house` local;
// and the unlimbo tail lifted into its own inline helper. The EBX/EBP
// exchange is unmoved by every function boundary available in this body.
void House_0050D440::RespawnStartingForces()
{
    int i;

    for (i = this->StartingUnits.Count - 1; i >= 0; i--) {
        StartingTechno_0050D440* entry = this->StartingUnits.Items[i];
        Abs_0050D440* type = entry->Type;
        Abs_0050D440* techno = 0;
        Abs_0050D440* obj;

        switch ((type->*type->Vtbl->WhatAmI)()) {
        case 3:
        case 7:
        case 0x28:
            obj = (type->*type->Vtbl->CreateObject)(this);
            if (obj == 0) {
                techno = 0;
            } else {
                techno = (obj->Flags & 1) ? obj : 0;
            }
            break;
        case 0x10:
            obj = (type->*type->Vtbl->CreateObject)(this);
            if (obj == 0) {
                techno = 0;
            } else {
                techno = (obj->Flags & 1) ? obj : 0;
            }
            break;
        }

        Abs_0050D440* cell = MapInstance.GetCellAt(entry->Cell);
        Coord_0050D440 coord = (cell->*cell->Vtbl->GetCoords)();
        if (!(techno->*techno->Vtbl->At_490)(&coord, 0)) {
            (techno->*techno->Vtbl->At_F8)();
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050D9C0
//
// True when the signed member at +0x164 is positive.
bool FUN_0050D9C0(Predicate_0050D9C0* self)
{
    return *(int*)(self->Bytes + 0x164) > 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050D9D0
//
// True when the signed member at +0x168 is positive.
bool FUN_0050D9D0(Predicate_0050D9C0* self)
{
    return *(int*)(self->Bytes + 0x168) > 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA00
//
// Store the argument into the member at +0x54F0.
void Setter_00487C70::FUN_0050DA00(int value)
{
    *(int*)(Bytes + 0x54F0) = value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA10
void Obj_0050DA10::FUN_0050DA10()
{
    unknown_54F0 = DAT_00A8EF98;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50DA40
// Stores its argument in a member; pops its stack arguments.
void Obj_0050DA40::FUN_0050DA40(int a1)
{
    unknown_54F8 = a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA50
void Obj_0050DA10::FUN_0050DA50()
{
    unknown_54F4 = DAT_00A8EF98;
    unknown_54FC = -100;
    unknown_54F8 = DAT_00A8EF98;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA80
// +0x577C when it is 0..3, else 0.
int Obj_0050DA10::FUN_0050DA80() const
{
    int value = unknown_577C;
    if (value >= 0 && value <= 3) {
        return value;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DEF0
// +0x5490 while +0x5494 still holds the global cell at 0xA8EF98, else +0x5494.
Cell_0050DEF0 Obj_0050DA10::FUN_0050DEF0() const
{
    if (unknown_5494 == DAT_00A8EF98) {
        return unknown_5490;
    }
    return unknown_5494;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DFE0
//
// Store the argument into the member at +0x5494.
void Setter_00487C70::FUN_0050DFE0(int value)
{
    *(int*)(Bytes + 0x5494) = value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DFF0
void Obj_0050DA10::FUN_0050DFF0()
{
    unknown_5494 = DAT_00A8EF98;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050E000
//
// Store the argument into the member at +0x5490.
void Setter_00487C70::FUN_0050E000(int value)
{
    *(int*)(Bytes + 0x5490) = value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E0E0
//
// One powering centre of this house has gone. Once the count reaches zero
// every live techno of this house whose type is the powered one is
// deactivated, walking the techno array from the top; if any was, and the
// house is the local player's, the "robot tanks offline" EVA line plays.
void House_0050E0E0::LostPoweredCenter(Type_0050E0E0* type)
{
    if (--this->PoweredCenterCount == 0 && type != 0) {
        bool found = false;
        for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
            Techno_0050E0E0* techno = DAT_00A8EC78.Items[i];
            if (techno->Owner == this
                && (techno->*techno->Vtbl->GetTechnoType)() == type
                && !techno->InLimbo) {
                techno->Deactivate();
                found = true;
            }
        }
        if (found && DAT_00A8E9A0 && this->IsControlledByCurrentPlayer()
            && DAT_00A8E7AC == 0) {
            Vox_0050E0E0::Play(STR_00824E4C, -1, -1);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E340
ULONG __stdcall HouseClusterView::AddRef()
{
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E350
ULONG __stdcall HouseClusterView::Release()
{
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E360
int HouseClusterView::WhatAmI()
{
    return 13;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E370
int HouseClusterView::vf_16()
{
    return ArrayIndex;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x50E380 -- compiler-generated scalar deleting destructor.
// SYNTHETIC: GAMEMD 0x510A20 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A30 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A40 -- compiler-generated Release adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A50 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A60 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A70 -- compiler-generated Release adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A80 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A90 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AA0 -- compiler-generated Release adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AB0 -- compiler-generated GetIndex adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AC0 -- compiler-generated GetName adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AD0 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AE0 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AF0 -- compiler-generated Release adjustor thunk.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E430
// Stores several members; pops its stack arguments.
void Obj_0050E430::FUN_0050E430(unsigned char a1, unsigned char a2, unsigned char a3)
{
    unknown_00 = a1;
    unknown_01 = a2;
    unknown_02 = a3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E450
// Stores several members; pops its stack arguments.
Obj_0050E450* Obj_0050E450::FUN_0050E450(int a1, Arg2_0050E450* a2)
{
    unknown_00 = a1;
    unknown_04 = a2->unknown_00;
    unknown_08 = 0;
    unknown_0C = 0;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x50E590
// DynamicVectorClass<AngerStruct>::Slot5 (slot 5)
template class DynamicVectorClass<AngerStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x50E600
// DynamicVectorClass<ScoutStruct>::Slot5 (slot 5)
template class DynamicVectorClass<ScoutStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x50E670
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x50E690
// VectorClass<HouseClass::BuildChoiceClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x50F4E0
// VectorClass<HouseClass::BuildChoiceClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x50F520
// VectorClass<HouseClass::BuildChoiceClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x50F600
// VectorClass<HouseClass::BuildChoiceClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x50F640
// VectorClass<HouseClass::BuildChoiceClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x50F660
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x50F710
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::FindItemIndex (slot 4)
template class VectorClass<HouseClass::BuildChoiceClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050F9A0
// VectorClass<bool>::operator==
// FUNCTION: GAMEMD 0x0050F9E0
// VectorClass<bool>::SetCapacity
// FUNCTION: GAMEMD 0x0050FAC0
// VectorClass<bool>::FindItemIndex
// FUNCTION: GAMEMD 0x0050FB00
// VectorClass<bool>::Slot5
// FUNCTION: GAMEMD 0x0050FB20
// DynamicVectorClass<bool>::SetCapacity
// FUNCTION: GAMEMD 0x0050FBD0
// DynamicVectorClass<bool>::FindItemIndex
// FUNCTION: GAMEMD 0x0050E730
// DynamicVectorClass<bool>::Slot5
// VTABLE: GAMEMD 0x007EAA5C -- VectorClass<bool>.
// VTABLE: GAMEMD 0x007EAA7C -- DynamicVectorClass<bool>.
template class VectorClass<bool>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050FC00
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::operator==
// FUNCTION: GAMEMD 0x0050FDB0
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x0050FE00
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::Slot5
// FUNCTION: GAMEMD 0x0050FFB0
// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x0050E7A0
// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::Slot5
template class VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050F070
// DynamicVectorClass<AngerStruct>::SetCapacity
// FUNCTION: GAMEMD 0x0050F170
// DynamicVectorClass<AngerStruct>::FindItemIndex
// VTABLE: GAMEMD 0x007EA984 -- VectorClass<AngerStruct>.
// VTABLE: GAMEMD 0x007EA924 -- DynamicVectorClass<AngerStruct>.
template class VectorClass<AngerStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050F3A0
// DynamicVectorClass<ScoutStruct>::SetCapacity
// FUNCTION: GAMEMD 0x0050F4A0
// DynamicVectorClass<ScoutStruct>::FindItemIndex
// VTABLE: GAMEMD 0x007EA9A4 -- VectorClass<ScoutStruct>.
// VTABLE: GAMEMD 0x007EA904 -- DynamicVectorClass<ScoutStruct>.
template class VectorClass<ScoutStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50FF40
// Empty function.
void __cdecl FUN_0050FF40()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x510860  (__thiscall)
//
// Grow the cell array by `additionalCapacity` slots, preserving the existing
// Count elements. Reject a negative request; reject allocation failure. On
// success: copy the live elements, free the old buffer, publish the new buffer
// and capacity, and clear the Unknown_10 cursor.
//
// MATCHED (100%, 56/56) as plain C++. The allocation is an array new of
// BasePlanningCell, which has an (empty) default constructor: retail's
// otherwise unexplained `DEC EBX; MOV [ESP+0x14],EBX` is the counter of the
// element-construction loop, whose empty body cl removes while keeping the
// counter's store. A raw operator new call instead gives 1.8%. The success
// arms are nested so both failures fall through to the one trailing
// `return false`, as in retail.
// ---------------------------------------------------------------------------
bool BasePlanningCellContainer::AddCapacity(int additionalCapacity)
{
    if (additionalCapacity >= 0) {
        int newCapacity = Capacity + additionalCapacity;
        BasePlanningCell* newItems = new BasePlanningCell[newCapacity];
        if (newItems != 0) {
            int i = 0;
            if (Count > 0) {
                do {
                    newItems[i] = Items[i];
                    ++i;
                } while (i < Count);
            }
            delete[] Items;
            Items = newItems;
            Capacity += additionalCapacity;
            Unknown_10 = 0;
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5108F0  (__cdecl)
//
// qsort comparator over BasePlanningCell::Weight (the leading int of each
// element). Ascending: 0 when equal, +1 when a > b, -1 when a < b.
//
// MATCHED (100%, 16/16). This was recorded as a phrasing-invariant setcc-tail
// delta and is not one. Retail emits `setge dl; dec; and -2; inc` and the
// ternary written `(wa >= wb) ? 1 : -1` emits the mirror `setl dl; dec; and 2;
// dec` (81.2%). The lever is which arm carries the negative literal: writing
// the *less-than* test with -1 in the true arm, `(wa < wb) ? -1 : 1`, makes cl
// keep the comparison as written and invert the arithmetic instead, which is
// retail's tail exactly. Spelling the tail out by hand as
// `((wa >= wb) - 1 & -2) + 1` also reaches 100%, so the two forms are the same
// codegen path. Eight other spellings stay at 81.2% (`>` ternary, nested ifs,
// a named bool, a named int result, the loads written inline) and two are
// worse: `1 - 2 * (wa < wb)` is 62.5% and inverting the equality guard to
// `if (wa != wb) return ...` is 43.8%.
// ---------------------------------------------------------------------------
int __cdecl BasePlanningCellContainer::Comparator(const void* a, const void* b)
{
    int wa = *(const int*)a;
    int wb = *(const int*)b;
    if (wa == wb)
        return 0;
    return (wa < wb) ? -1 : 1;
}
