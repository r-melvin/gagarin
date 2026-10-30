// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Support declarations for the six BuildingClass virtual bodies at 0x43DA80, 0x43F180, 0x440580, 0x445880,
//   0x448260 and 0x44ACF0 (primary-table slots 313, 73, 54, 53, 245 and 132 of .?AVBuildingClass@@, type
//   descriptor 0x818D60, table 0x7E3EBC). The bodies are written against the canonical BuildingClass,
//   HouseClass, BuildingTypeClass and CellClass in _layout. What remains here are small partial views of
//   objects that have no canonical header yet (the display and game-session singletons, the cell-placement
//   table, the local vector and list helpers) and the retail entry points the bodies call.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A4_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A4_VIEWS_H

#include <stddef.h>
#include "../../_layout/session_class.h"
#include "../../_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "../../_layout/building_class.h"
#include "../../_layout/cell_class.h"
#include "../../_layout/anim_class.h"
#include "../../_layout/house_class.h"
#include "../../_layout/house_type_class.h"
#include "../../_layout/factory_class.h"
#include "../../_layout/light_source_class.h"
#include "../../_layout/building_light_class.h"
#include "../../_layout/overlay_type_class.h"
#include "../../_layout/airstrike_class.h"
#include "../../_layout/anim_type_class.h"
#include "../../_layout/iso_tile_type_class.h"
#include "../../_layout/map_0087f7e8.h"
#include "../../_layout/tactical.h"
#include "../../_layout/player_ptr_00a83d4c.h"
#include "../../_layout/scenario_ptr_00a8b230.h"
#include "../../_layout/matrix3d.h"
#include "../../_layout/global_0089c818.h"
#include "../../_layout/rules_class.h"
#include "../../_layout/unit_tracker_class.h"
#include "../../core/mission_class_methods.h"
#include "../../core/vector_class_operations.h"
#include "../../core/cell_step_tables.h"
#include "house_building_common_types.h"
#include "house_building_common_types.h"
#include "house_building_common_types.h"

class BuildingTypeClass;
class HouseClass;
class BuildingClass;
struct CellClass;

// A pointer-sized vector (vptr, Items, Capacity, IsInitialized, IsAllocated, Count, CapacityIncrement; 0x18 bytes). Only
// slot 2 (SetCapacity) is reached by the inlined AddItem.
template <class T> class BA4Vector
{
public:
    BA4Vector(int size, T* mem);   // FUNCTION: GAMEMD 0x45AE50 (read-only here)
    virtual ~BA4Vector() { if (Items && IsAllocated) delete [] Items; }   // slot 0
    virtual bool vt_1();
    virtual bool SetCapacity(int capacity, T* mem);   // slot 2
    virtual void vt_3();
    virtual int FindItemIndex(T* item);               // slot 4

    T*            Items;               // +0x04
    int           Capacity;            // +0x08
    bool          IsInitialized;       // +0x0C
    bool          IsAllocated;         // +0x0D
    unsigned char unknown_0E[2];       // +0x0E
    int           Count;               // +0x10
    int           CapacityIncrement;   // +0x14

    // DynamicVectorClass::RemoveItem, expanded inline by the original.
    bool RemoveItem(T item)
    {
        int index = FindItemIndex(&item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index) {
                Items[index] = Items[index + 1];
            }
            return true;
        }
        return false;
    }

    // DynamicVectorClass::AddItem, expanded inline by the original as one short-circuit condition.
    bool AddItem(const T& item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && SetCapacity(CapacityIncrement + cap, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(sizeof(BA4Vector<int*>) == 0x18);

// The audio/EVA entry points used by the owner-change body (read-only here).
// FUNCTION: GAMEMD 0x752700 (read-only here) - the speech name in ECX, two further arguments (EDX and the stack).
void FUN_00752700(const char* name, int a, int b);
// FUNCTION: GAMEMD 0x752480 (read-only here)
void FUN_00752480(int id, int a, int b);
// FUNCTION: GAMEMD 0x65FA70 (read-only here)
bool FUN_0065FA70(int a, CellStruct cell);
extern const char s_EVA_BuildingCaptured_00818FAC[];
extern const char s_EVA_TechBuildingLost_00818FC4[];

// The cell standing at a coordinate offset (the by-reference spelling of Map_0087F7E8's 0x5657A0).
inline CellStruct BA4Off(short x, short y)
{
    CellStruct c;
    c.X = x;
    c.Y = y;
    return c;
}
inline CellClass* BA4At(const CellStruct& cell)
{
    return DAT_0087F7E8.FUN_005657A0(&cell);
}

// The object created by the ctor at 0x5FC380 (0xB0 bytes allocated, opaque here).
class BA4Spawned
{
public:
    BA4Spawned(OverlayTypeClass* type, CellStruct* cell, int value);
    static void* operator new(unsigned int size);
};

class ParticleSystemTypeClass;
class BA4Tracker
{
public:
    // FUNCTION: GAMEMD 0x62DC50 (read-only here)
    BA4Tracker(ParticleSystemTypeClass* type, CoordStruct* where, CellClass* cell, int a, int* table, int b);
    static void* operator new(unsigned int size);
};

// An entry of the list gathered while changing owner: an object and one flag byte (8 bytes, allocated with the game's operator new).
struct BA4Held
{
    TechnoClass*  Object;   // +0x00
    unsigned char Flag;     // +0x04
    BA4Held(TechnoClass* object, unsigned char flag) { Object = object; Flag = flag; }
    static void* operator new(unsigned int size);
};

// The local list of BA4Held* of the owner-change body: base constructor out of line, growth set by the derived part.
class BA4HeldList : public BA4Vector<BA4Held*>
{
public:
    BA4HeldList() : BA4Vector<BA4Held*>(0, 0) { Count = 0; CapacityIncrement = 10; }
};

// A target reference (a 32-bit value and one tag byte; copied member-wise as five bytes).
#pragma pack(push, 1)
// Not merged: takes this cluster's BuildingClass view (see house_building_views.h).
struct BA4TargetRef
{
    int           Value;   // +0x00
    unsigned char Tag;     // +0x04
    // FUNCTION: GAMEMD 0x6E6AB0 (read-only here) - builds the reference to a building in place.
    BA4TargetRef* FUN_006E6AB0(BuildingClass* b);
};
#pragma pack(pop)
GG_STATIC_ASSERT(sizeof(BA4TargetRef) == 5);




// The identity matrix local of the draw body: the constructor (MakeIdentity, 0x5AE860) runs; the scratch matrices
// of the same body are plain Matrix3D objects (no constructor code).
typedef Matrix3D BA4MatrixTemp;
struct BA4Matrix : public Matrix3D
{
    BA4Matrix() { MakeIdentity(); }
};
GG_STATIC_ASSERT(sizeof(BA4Matrix) == 0x30);
// FUNCTION: GAMEMD 0x5AF980 (read-only here) - dest in ECX, the second operand in EDX, the first on the stack.
BA4MatrixTemp* FUN_005AF980(BA4MatrixTemp* dest, BA4MatrixTemp* b, BA4MatrixTemp* a);













// An entry of the table at *0xA8EC1C (partial): a footprint of w by h cells.
struct BA4Placed
{
    char _pad_0000[0x298];   // +0x0000
    int unknown_298;   // +0x0298
    int unknown_29C;   // +0x029C
};
GG_STATIC_ASSERT(offsetof(BA4Placed, unknown_298) == 0x298);
GG_STATIC_ASSERT(offsetof(BA4Placed, unknown_29C) == 0x29C);

// The map object, the session object, the global tables and flags touched by the bodies.
extern OverlayTypeClass** DAT_00A83D84;

extern unsigned char DAT_00880CF4;
extern int DAT_00A8E7AC;
extern unsigned char DAT_00A8E9A0;
extern BA4Placed** DAT_00A8EC1C;
#include "../../core/scenario_class_methods.h"
extern int DAT_0089C848;
// LIBRARY: GAMEMD 0x7C8D20 (LIBRARY: _stricmp) / 0x7C91D0 (LIBRARY: strncpy)
extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" char* __cdecl strncpy(char* dest, const char* src, unsigned int count);
extern int DAT_00A8ED84;
extern int DAT_0088098C;
extern int DAT_00880990;
extern int DAT_00880994;
extern const double DAT_007E27F8;
extern const double DAT_007E1718;
// FUNCTION: GAMEMD 0x4CAC40 (read-only here)
double __cdecl FUN_004CAC40(double a);
// LIBRARY: GAMEMD 0x7C5F00 is the compiler's float-to-int helper (LIBRARY: _ftol)
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)

// The inline "is it this kind of object" cast of the original: the pointer or null, by the RTTI id of slot 11.
template <class To, class From> inline To* BA4As(From* p, int id)
{
    return p ? (p->vf_11() == id ? static_cast<To*>(p) : 0) : 0;
}
extern int DAT_00B73550;
extern unsigned char DAT_00A8ED6B;
extern unsigned char DAT_00887418;
extern int DAT_00818CB0;
extern unsigned char DAT_00818CB4;
extern RectangleStruct DAT_00886FA0;
extern const double DAT_007E4408;
// FUNCTION: GAMEMD 0x4BBC90 (read-only here) - the pixel-format code of the display.
int __cdecl FUN_004BBC90();
// FUNCTION: GAMEMD 0x6D20E0 (read-only here)
int FUN_006D20E0(int key);





#endif
