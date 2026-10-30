// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TAction.CPP. The name is the source-file string at 0x842bf8
//   in retail gamemd.exe v1.001, passed by the assert at 0x6de10c inside this object's
//   code range (0x6dcd70-0x6e4b4f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The six ID-resolving commands, ordered ascending by retail address.
//
// Two phrasing points carry the whole body. The three failure exits have to be
// one shared `goto`, not three `return false` statements: written as returns cl
// duplicates the two-instruction failure tail at each site and the layout
// diverges from the first branch (14.3%). And the predicate arm has to be a
// ternary feeding one assignment rather than an if/else assigning in both arms,
// which is what keeps retail's shared `MOV ECX,ESI` ahead of the test.
//
// Nine small guarded predicates across three shapes: a flag-gated
// out-parameter copy, a bool-selected float constant, and a null-guarded relay.
// Within a shape the bodies are byte-identical apart from the member offset,
// the float constant or the relayed call displacement, so each is written once
// as a macro and expanded per instantiation. Ordered ascending by retail
// address.
//
// Retail IPersist::GetClassID (slot 3 of each class's primary vtable) copies a
// 16-byte CLSID global to the caller and returns E_POINTER for a null pointer.
// The owning class of each address is read from the RTTI-named vtable that holds
// it in slot 3.

#include "taction_class_mode_methods.h"
#include "../core/mathtbl_init_shapes.h"

#include "../core/id_resolve_command_sweep.h"

#include "../core/leftover_predicate_sweep.h"

#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"

// GLOBAL: GAMEMD 0x007E9800 -- CLSID of TActionClass.
extern const CLSID DAT_007E9800;

#include "../core/trivial_tu230_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F43B8
extern const double DAT_007F43B8;
// GLOBAL: GAMEMD 0xB0E688
extern double DAT_00B0E688;


// ---- from the former TAction.cpp ----
//   CLI (disasm from each entry point). Original TU: TAction.CPP, attested by
//   the __FILE__ assert string at 0x842BF8 ("D:\ra2mdpost\TAction.CPP"); the
//   TU spans 0x6DCD70-0x6E4B4F. Every name is a placeholder (FUN_/DAT_/
//   unknown_) derived from an address or offset in that binary.

#include "taction_class_methods.h"
#include "../core/scenario_class_methods.h"
#include "../_layout/house_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/trigger_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/tag_type_class.h"
#include "../_layout/building_class.h"
#include <new.h>
#include "../_layout/object_class.h"
#include <string.h>
#include "../movement/locomotion_load_support.h"
#include "../core/vector_class_operations.h"
#include "../core/frame_counter.h"

// ---- external state and callees, bound by address ----

// GLOBAL: GAMEMD 0xA8B230 -- the scenario object.
extern ScenarioClass* DAT_00A8B230;


// Retail PAVTActionClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

class TActionClass;

// VTABLE: GAMEMD 0x7F43F0 -- VectorClass<TActionClass*>.
template class VectorClass<TActionClass*>;
typedef VectorClass<TActionClass*> GgTActionClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F43D0 -- DynamicVectorClass<TActionClass*>.
template class DynamicVectorClass<TActionClass*>;
typedef DynamicVectorClass<TActionClass*> GgTActionClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TActionClass*) == 4);

// FUNCTION: GAMEMD 0x53A140 (decl; reloc)
void __stdcall FUN_0053A140(CellStruct cell);

// FUNCTION: GAMEMD 0x53B460 (decl; reloc)
void FUN_0053B460(int value);

// FUNCTION: GAMEMD 0x684060 (decl; reloc)
void FUN_00684060(int value);

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E47F0
// DynamicVectorClass<TActionClass*>::Clear

// FUNCTION: GAMEMD 0x6E4820
// DynamicVectorClass<TActionClass*>::Slot5

// FUNCTION: GAMEMD 0x6E4840
// VectorClass<TActionClass*>::Slot6

// FUNCTION: GAMEMD 0x6E4850
// VectorClass<TActionClass*>::operator==

// FUNCTION: GAMEMD 0x6E4890
// VectorClass<TActionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E4940
// VectorClass<TActionClass*>::Clear

// FUNCTION: GAMEMD 0x6E4970
// VectorClass<TActionClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x6E49B0
// VectorClass<TActionClass*>::Slot5

// FUNCTION: GAMEMD 0x6E49D0
// DynamicVectorClass<TActionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E4A80
// DynamicVectorClass<TActionClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6E4AB0
// VectorClass<TActionClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x6E4B00
// DynamicVectorClass<TActionClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x750920 (decl; reloc)
void* FUN_00750920(int index, float volume, unsigned int pan, void* controller);

// GLOBAL: GAMEMD 0xA8EAEC / 0xA8EAF8 -- TriggerClass::Array items and count.
extern TriggerClass** DAT_00A8EAEC;
extern int DAT_00A8EAF8;
// GLOBAL: GAMEMD 0xB0E724 / 0xB0E730 -- TagClass::Array items and count.
extern TagClass** DAT_00B0E724;
extern int DAT_00B0E730;
// GLOBAL: GAMEMD 0xB0E680 -- the undefined cell.
extern CellStruct DAT_00B0E680;
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while the scenario is being set up.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x53AD00 (decl; reloc)
void FUN_0053AD00(int a, int b, int c, int d);

// FUNCTION: GAMEMD 0x726910 (decl; reloc) -- the house a trigger belongs to.
HouseClass* FUN_00726910(TriggerClass* trigger);

// FUNCTION: GAMEMD 0x510F60 (decl; reloc)
bool FUN_00510F60(int index);

// The house named by an action's parameter (same lookup as 0x6E45E0, which retail also inlines here).
static __inline HouseClass* FindActionHouseInner(TriggerClass* trigger, int index)
{
    if (index == 0x2325)
        return FUN_00726910(trigger);

    if (index == -1)
        return 0;

    if (FUN_00510F60(index))
        return FUN_00510ED0(index);

    return FUN_00502D30(index);
}

static __inline HouseClass* FindActionHouse(TriggerClass* trigger, int index)
{
    if (trigger == 0)
        return 0;

    return FindActionHouseInner(trigger, index);
}


// The rules object (GLOBAL 0x8871E0); only the dword read here is named.
struct TActionRulesView
{
    unsigned char unknown_00[0xFA8];
    int unknown_FA8;                        // +0xFA8
    unsigned char unknown_FAC[0x1668 - 0xFAC];
    double unknown_1668;                    // +0x1668
    double unknown_1670;                    // +0x1670
};
GG_STATIC_ASSERT(offsetof(TActionRulesView, unknown_FA8) == 0xFA8);
GG_STATIC_ASSERT(offsetof(TActionRulesView, unknown_1668) == 0x1668);
GG_STATIC_ASSERT(offsetof(TActionRulesView, unknown_1670) == 0x1670);
// GLOBAL: GAMEMD 0x8871E0
extern TActionRulesView* DAT_008871E0;

// FUNCTION: GAMEMD 0x48A620 (decl; reloc)
void FUN_0048A620(int a, int b, CoordStruct where, char c, unsigned int d);

// GLOBAL: GAMEMD 0xA8EB44 / 0xA8EB50 -- BuildingClass::Array items and count.
extern BuildingClass** DAT_00A8EB44;
extern int DAT_00A8EB50;
// GLOBAL: GAMEMD 0x8B3DC4 / 0x8B3DD0 -- a techno array, items and count.
extern TechnoClass** DAT_008B3DC4;
extern int DAT_008B3DD0;
// GLOBAL: GAMEMD 0xA8EC7C / 0xA8EC88 -- a techno array, items and count.
extern TechnoClass** DAT_00A8EC7C;
extern int DAT_00A8EC88;
// GLOBAL: GAMEMD 0xA8020C / 0xA80218 -- an object array, items and count.
extern ObjectClass** DAT_00A8020C;
extern int DAT_00A80218;

// A 0x14-byte object created at a map coordinate by 0x6E3380 (constructor 0x53CB10).
class Obj_0053CB10
{
public:
    unsigned char unknown_00[0x14];
    // FUNCTION: GAMEMD 0x53CB10 (decl; reloc)
    Obj_0053CB10(CoordStruct where);
};
GG_STATIC_ASSERT(sizeof(Obj_0053CB10) == 0x14);

// One strip of the sidebar (stride 0xF94 from 0x880D2C); only the predicate is called here.
struct Obj_00880D2C
{
    unsigned char unknown_00[0xF94];
    // FUNCTION: GAMEMD 0x6ABAC0 (decl; reloc)
    bool FUN_006ABAC0();
};
GG_STATIC_ASSERT(sizeof(Obj_00880D2C) == 0xF94);
// GLOBAL: GAMEMD 0x880D2C
extern Obj_00880D2C DAT_00880D2C[4];

// An entry of the named array at 0xA8EB04 (count at 0xA8EB10); only its text at +0x24 is read here.
struct Obj_00A8EB04
{
    unsigned char unknown_00[0x24];
    char unknown_24[0x19];
};
// GLOBAL: GAMEMD 0xA8EB04 / 0xA8EB10 -- the array's items and count.
extern Obj_00A8EB04** DAT_00A8EB04;
extern int DAT_00A8EB10;

static __inline int FindNamedIndex(const char* name)
{
    int result = -1;
    int i = DAT_00A8EB10;
    i--;
    for (; i >= 0; i--) {
        if (strcmp(DAT_00A8EB04[i]->unknown_24, name) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

// GLOBAL: GAMEMD 0xB0F670 / 0xB0F658 / 0xB0E658 -- the registries a TActionClass leaves when destroyed.
extern DynamicVectorClass<TActionClass*> DAT_00B0F670;
extern DynamicVectorClass<TActionClass*> DAT_00B0F658;
extern DynamicVectorClass<TActionClass*> DAT_00B0E658;

// 0x6DD1D6..0x6DD2AF accesses registry item storage at +4 and count at +0x10.
typedef DynamicVectorClass<TActionClass*> TActionRegistry;
GG_STATIC_ASSERT(offsetof(TActionRegistry, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TActionRegistry, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(TActionRegistry) == 0x18);

// SYNTHETIC: GAMEMD 0x006DCDA0
// GLOBAL: GAMEMD 0x00B0E6D8
double DAT_00B0E6D8 = DAT_00B0E688 / DAT_007F43B8;

// SYNTHETIC: GAMEMD 0x006DCDC0
// GLOBAL: GAMEMD 0x00B0E6C0
double DAT_00B0E6C0 = DAT_007E1718 / DAT_00B0E6D8;

// SYNTHETIC: GAMEMD 0x006DCF40
// GLOBAL: GAMEMD 0x00B0E6C8
MathTblCoord DAT_00B0E6C8;

struct Obj_006E4790;

// LIBRARY: GAMEMD 0x7C91D0 (decl; reloc)
void __cdecl FUN_007C91D0(Obj_006E4790*, int, int);

struct Obj_006E4790
{
    unsigned char unknown_00;   // +0x0000
    char unknown_01[0x1E];
    unsigned char unknown_1F;   // +0x001F
    // FUNCTION: GAMEMD 0x6E4790
    Obj_006E4790* FUN_006E4790(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006E4790, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_006E4790, unknown_1F) == 0x1F);

// FUNCTION: GAMEMD 0x6DD1B0
TActionClass::~TActionClass()
{
    AnnounceExpiredPointer(1);
    DAT_00B0F670.RemoveItem(this);
    DAT_00B0F658.RemoveItem(this);
    DAT_00B0E658.RemoveItem(this);
    unknown_6D[0] = 0;
}

// FUNCTION: GAMEMD 0x6DD2C0
void TActionClass::vf_10(void* target, bool removed)
{
    if (unknown_28 == target) {
        unknown_28 = unknown_28->unknown_28;
    }
    if (unknown_30 == target) {
        unknown_30 = 0;
    }
    if (unknown_50 == target) {
        unknown_50 = 0;
    }
    if (unknown_4C == target) {
        unknown_4C = 0;
    }
}

// FUNCTION: GAMEMD 0x6E0040
// Returns a constant boolean; pops its stack arguments.
bool __stdcall FUN_006E0040(int a1, int a2, int a3, int a4)
{
    return true;
}

// FUNCTION: GAMEMD 0x6E0050
bool TActionClass::FUN_006E0050(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_0053A140(DAT_00A8B230->GetWaypointCoords(unknown_44));
    return true;
}

// FUNCTION: GAMEMD 0x6E0080
bool TActionClass::FUN_006E0080(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct where = DAT_00A8B230->GetWaypointCoords(unknown_44);
    for (int i = 0; i < DAT_00A80218; i++) {
        ObjectClass* o = DAT_00A8020C[i];
        if (o->IsAlive) {
            CellStruct at = o->vf_110();
            if (at.X == where.X && at.Y == where.Y) {
                o->vf_62();
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E0250
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0250::FUN_006E0250(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A7 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0270
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0270::FUN_006E0270(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A6 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0290
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0290::FUN_006E0290(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A8 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E02B0
bool TActionClass::FUN_006E02B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    for (int i = 0; i < DAT_008B3DD0; i++) {
        TechnoClass* t = DAT_008B3DC4[i];
        if (t->vf_97() == 0 && t->Health > 0 && t->IsAlive && t->IsOnMap && !t->InLimbo && house != t->Owner) {
            t->vf_122(5, false);
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E0330
bool TActionClass::FUN_006E0330(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    for (int i = 0; i < DAT_008B3DD0; i++) {
        TechnoClass* t = DAT_008B3DC4[i];
        if (t->vf_97() == 0x17 && t->Health > 0 && t->IsAlive && t->IsOnMap && !t->InLimbo && t->Owner == house) {
            t->vf_122(5, false);
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E03B0
bool TActionClass::FUN_006E03B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    for (int i = 0; i < DAT_00A8EC88; i++) {
        TechnoClass* t = DAT_00A8EC7C[i];
        if (t->Group == unknown_90 && (t->vf_97() == 0 || t->vf_97() == 0x17) && t->Health > 0 && t->IsAlive
            && t->IsOnMap && !t->InLimbo) {
            t->vf_122(5, false);
        }
    }
    return true;
}

extern HouseClass* DAT_00A83D4C;

struct Obj_006E0440 {
    bool FUN_006E0440(int, int, int, int);
    bool FUN_006E0460(int, int, int, int);
};
// FUNCTION: GAMEMD 0x006E0440
bool Obj_006E0440::FUN_006E0440(int, int, int, int)
{
    DAT_00A83D4C->Win(1);
    return true;
}
// FUNCTION: GAMEMD 0x006E0460
bool Obj_006E0440::FUN_006E0460(int, int, int, int)
{
    DAT_00A83D4C->Lose(1);
    return true;
}

// FUNCTION: GAMEMD 0x6E0790
bool TActionClass::FUN_006E0790(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    int sound = DAT_008871E0->unknown_FA8;
    CoordStruct where = DAT_00A8B230->FUN_0068BD00(unknown_90);
    FUN_0048A620(0x32, sound, where, 0, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E07F0
bool TActionClass::FUN_006E07F0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    int sound = DAT_008871E0->unknown_FA8;
    CoordStruct where = DAT_00A8B230->FUN_0068BD00(unknown_90);
    FUN_0048A620(100, sound, where, 0, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E0850
bool TActionClass::FUN_006E0850(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    int sound = DAT_008871E0->unknown_FA8;
    CoordStruct where = DAT_00A8B230->FUN_0068BD00(unknown_90);
    FUN_0048A620(300, sound, where, 0, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E08B0
bool TActionClass::FUN_006E08B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    bool result = false;
    for (int i = 0; i < DAT_00A8EB50; i++) {
        BuildingClass* b = DAT_00A8EB44[i];
        if (b->IsAlive && b->IsOnMap && !b->InLimbo && b->AttachedTag && b->AttachedTag->ContainsTrigger(trigger)) {
            b->vf_104(1);
            result = true;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x6E09A0
bool TActionClass::FUN_006E09A0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    bool result = false;
    for (int i = 0; i < DAT_00A8EB50; i++) {
        BuildingClass* b = DAT_00A8EB44[i];
        if (b->IsAlive && b->IsOnMap && !b->InLimbo && b->AttachedTag && b->AttachedTag->ContainsTrigger(trigger)
            && b->HasPower) {
            b->FUN_00452360();
            result = true;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x6E0A20
bool TActionClass::FUN_006E0A20(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    bool result = false;
    for (int i = 0; i < DAT_00A8EB50; i++) {
        BuildingClass* b = DAT_00A8EB44[i];
        if (b->IsAlive && b->IsOnMap && !b->InLimbo && b->AttachedTag && b->AttachedTag->ContainsTrigger(trigger)
            && !b->HasPower) {
            b->FUN_00452260();
            result = true;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x6E0CA0
bool TActionClass::FUN_006E0CA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    house->FUN_0050D290(target);
    return true;
}

// FUNCTION: GAMEMD 0x6E0D00
bool TActionClass::FUN_006E0D00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    house->FUN_0050D2D0(target);
    return true;
}

// FUNCTION: GAMEMD 0x6E0DF0
bool TActionClass::FUN_006E0DF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    house->FUN_004F9B70(target, false);
    target->FUN_004F9B70(house, false);
    return true;
}

// FUNCTION: GAMEMD 0x6E0E60
bool TActionClass::FUN_006E0E60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    house->FUN_004F9F90(target, false);
    target->FUN_004F9F90(house, false);
    return true;
}

// FUNCTION: GAMEMD 0x6E0ED0
// Branching.
unsigned char Obj_006E0ED0::FUN_006E0ED0(Arg1_006E0ED0* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_54EC = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E0FA0
// Calls other functions.
bool Obj_006E0FA0::FUN_006E0FA0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689670(unknown_90, 1);
    return true;
}

// FUNCTION: GAMEMD 0x6E0FC0
// Calls other functions.
bool Obj_006E0FC0::FUN_006E0FC0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689670(unknown_90, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E1180
bool TActionClass::FUN_006E1180(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct where = DAT_00A8B230->GetWaypointCoords(unknown_90);
    MapInstance.FUN_0057B790(&where);
    return true;
}

// FUNCTION: GAMEMD 0x6E13A0
bool TActionClass::FUN_006E13A0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (DAT_00A8B230->Timer_11E8.IsOff()) {
        DAT_00A8B230->Timer_11E8.Start();
        MapInstance.FUN_006D0F00();
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E13E0
bool TActionClass::FUN_006E13E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (DAT_00A8B230->Timer_11E8.IsOn()) {
        DAT_00A8B230->Timer_11E8.Stop();
        MapInstance.FUN_006D0F00();
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E1440
bool TActionClass::FUN_006E1440(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    ScenarioTimer& timer = DAT_00A8B230->Timer_11E8;
    timer = ScenarioTimer(timer.GetTimeLeft() + unknown_90 * 15);
    MapInstance.FUN_006D0F00();
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1720
// Calls other functions.
bool Obj_006E1720::FUN_006E1720(int a1, int a2, int a3, int a4)
{
    FUN_005BF390(unknown_90, false);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1740
// Calls other functions.
bool Obj_006E1740::FUN_006E1740(int a1, int a2, int a3, int a4)
{
    FUN_005BF390(unknown_90, true);
    return true;
}

// FUNCTION: GAMEMD 0x6E1760
bool TActionClass::FUN_006E1760(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_00750920(unknown_90, 1.0f, 0x2000, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E1A40
bool TActionClass::FUN_006E1A40(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct where = DAT_00A8B230->GetWaypointCoords(unknown_44);
    house->FUN_0050D6D0(where);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1B90
// Calls other functions.
bool FUN_006E1B90(Obj_006E1B90* a1, int a2, int a3, int a4, int a5, int a6)
{
    FUN_00720B20(DAT_00A83D10, a2, a1->unknown_90);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1BB0
// Calls other functions.
bool Obj_006E1BB0::FUN_006E1BB0(int a1, int a2, int a3, int a4)
{
    FUN_00752480(unknown_90, 2, -1);
    return true;
}

// FUNCTION: GAMEMD 0x6E1E40
bool TActionClass::FUN_006E1E40(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    target->Production = 1;
    return true;
}

// FUNCTION: GAMEMD 0x6E1EA0
bool TActionClass::FUN_006E1EA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    target->AIMode = 4;
    return true;
}

// FUNCTION: GAMEMD 0x6E1F00
bool TActionClass::FUN_006E1F00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    target->AutocreateAllowed = 1;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1F90
// Branching.
unsigned char Obj_006E1F90::FUN_006E1F90(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        unknown_30->FUN_006F0A70();
        return 1;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1FB0
// Branching.
unsigned char FUN_006E1FB0(Obj_006E1FB0* a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1->unknown_30 != 0)
    {
        return FUN_0065D8E0(a1->unknown_30, -1);
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1FD0
// Branching.
unsigned char Obj_006E1FD0::FUN_006E1FD0(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        if (unknown_44 != -1)
        {
            return FUN_0065D8E0(unknown_30, unknown_44);
        }
        return 0;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E21D0
// Returns a constant boolean; pops its stack arguments.
bool __stdcall FUN_006E21D0(int a1, int a2, int a3, int a4)
{
    return true;
}

struct Obj_006E26C0 {
    void FUN_00684290();
    bool FUN_006E26C0(int, int, int, int);
};
// FUNCTION: GAMEMD 0x006E26C0
bool Obj_006E26C0::FUN_006E26C0(int, int, int, int)
{
    FUN_00684290();
    return true;
}

struct Obj_006E2850 {
    void FUN_007315A0();
    bool FUN_006E2850(int, int, int, int);
};
// FUNCTION: GAMEMD 0x006E2850
bool Obj_006E2850::FUN_006E2850(int, int, int, int)
{
    FUN_007315A0();
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2950
// Calls other functions.
bool FUN_006E2950(int a1, int a2, int a3, int a4, int a5, int a6)
{
    FUN_00577C90(DAT_0087F7E8, a2, a3);
    return true;
}

// FUNCTION: GAMEMD 0x6E2A10
bool TActionClass::FUN_006E2A10(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_50) {
        for (int i = DAT_00A8EAF8 - 1; i >= 0; i--) {
            if (DAT_00A8EAEC[i]->Type == unknown_50) {
                DAT_00A8EAEC[i]->Destroy();
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E2A50
bool TActionClass::FUN_006E2A50(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_4C) {
        int count = DAT_00B0E730;
        for (int i = 0; i < count; i++) {
            if (DAT_00B0E724[i]->Type == unknown_4C) {
                if (DAT_00B0E724[i]) {
                    delete DAT_00B0E724[i];
                }
                i--;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E2AA0
bool TActionClass::FUN_006E2AA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_50) {
        for (int i = 0; i < DAT_00A8EAF8; i++) {
            if (DAT_00A8EAEC[i]->Type == unknown_50) {
                DAT_00A8EAEC[i]->FireActions(0, DAT_00B0E680);
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E2AF0
bool TActionClass::FUN_006E2AF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_50) {
        for (int i = 0; i < DAT_00A8EAF8; i++) {
            TriggerClass* t = DAT_00A8EAEC[i];
            TriggerTypeClass* type = t->Type;
            if (type == unknown_50) {
                int difficulty = DAT_00A8B230->Difficulty;
                if (!((difficulty == 0 && !type->Difficulty_9C) || (difficulty == 1 && !type->Difficulty_9D)
                      || (difficulty == 2 && !type->Difficulty_9E))) {
                    t->FUN_007268F0();
                }
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E2B70
bool TActionClass::FUN_006E2B70(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_50) {
        for (int i = 0; i < DAT_00A8EAF8; i++) {
            if (DAT_00A8EAEC[i]->Type == unknown_50) {
                DAT_00A8EAEC[i]->FUN_00726900();
            }
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2BE0
// Calls other functions.
bool Obj_006E2BE0::FUN_006E2BE0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689910(unknown_90, 1);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2C00
// Calls other functions.
bool Obj_006E2C00::FUN_006E2C00(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689910(unknown_90, 0);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2E20
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E2E20::FUN_006E2E20(int a1, int a2, int a3, int a4)
{
    DAT_008871E0->unknown_1670 = unknown_90;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2E40
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E2E40::FUN_006E2E40(int a1, int a2, int a3, int a4)
{
    DAT_008871E0->unknown_1668 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E2E60
bool TActionClass::FUN_006E2E60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_0053AD00(unknown_90 * 10, DAT_00A8B230->unknown_3538 * 10, DAT_00A8B230->unknown_353C * 10, 0);
    DAT_00A8B230->unknown_3534 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E2EB0
bool TActionClass::FUN_006E2EB0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_0053AD00(DAT_00A8B230->unknown_3534 * 10, unknown_90 * 10, DAT_00A8B230->unknown_353C * 10, 0);
    DAT_00A8B230->unknown_3538 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E2F50
bool TActionClass::FUN_006E2F50(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    DAT_00A8B230->unknown_3528 = unknown_90;
    if (!DAT_00A8B230->FUN_0053A100()) {
        DAT_00A8B230->unknown_3530 = DAT_00A8B230->unknown_3528;
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E2F90
bool TActionClass::FUN_006E2F90(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_0053B460(unknown_90);
    return true;
}

// FUNCTION: GAMEMD 0x6E3000
bool TActionClass::FUN_006E3000(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    target->AITriggersActive = 0;
    return true;
}

// FUNCTION: GAMEMD 0x6E3060
bool TActionClass::FUN_006E3060(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouse(trigger, unknown_90);
    if (target == 0) {
        return false;
    }
    target->FUN_0050C8C0();
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E30C0
bool IdCommandOwner::FUN_006E30C0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_0050D440(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3120
bool IdCommandOwner::FUN_006E3120(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_0050D320(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3180
bool IdCommandOwner::FUN_006E3180(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC6D0(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E31E0
bool IdCommandOwner::FUN_006E31E0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC790(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3240
bool IdCommandOwner::FUN_006E3240(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC820(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E32A0
bool IdCommandOwner::FUN_006E32A0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC8D0(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3300
// Branching.
unsigned char Obj_006E3300::FUN_006E3300(Arg1_006E3300* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_565C = unknown_90;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3320
// Branching.
unsigned char Obj_006E3320::FUN_006E3320(Arg1_006E3320* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5660 = unknown_90;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3340
// Branching.
unsigned char Obj_006E3340::FUN_006E3340(Arg1_006E3340* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5664 = unknown_90;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3360
// Branching.
unsigned char Obj_006E3360::FUN_006E3360(Arg1_006E3360* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5668 = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E3380
bool TActionClass::FUN_006E3380(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct wp = DAT_00A8B230->GetWaypointCoords(unknown_44);
    CoordStruct where;
    where.Z = 0;
    where.Y = wp.Y * 256 + 0x80;
    where.X = wp.X * 256 + 0x80;
    where.Z = MapInstance.FUN_00578080(&where);
    new Obj_0053CB10(where);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3890
// Branching.
unsigned char Obj_006E3890::FUN_006E3890(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        if (unknown_44 != -1)
        {
            return FUN_0065EC30(unknown_30, unknown_44);
        }
        return 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6E38B0
bool TActionClass::FUN_006E38B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct where = DAT_00A8B230->GetWaypointCoords(unknown_44);
    return MapInstance.FUN_0056BEC0(where, unknown_90);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3B20
// Stores its argument in a member; pops its stack arguments.
bool __stdcall FUN_006E3B20(int a1, int a2, int a3, int a4)
{
    bool t1 = DAT_00A8B230->unknown_34A5;
    DAT_00A8B230->unknown_34A5 = DAT_00A8B230->unknown_34A5 == 0;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3B40
// Branching.
unsigned char Obj_006E3B40::FUN_006E3B40(Arg1_006E3B40* a1, int a2, int a3, int a4)
{
    if (a1 == 0)
    {
        return 0;
    }
    a1->FUN_0050BCD0(unknown_90);
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3B60  TActionClass::GetMode
//
// Which parameter-editing mode a trigger action kind uses. The cases are
// written in the order of their result blocks in the retail image.
int TActionClass_006E3B60::GetMode(int kind)
{
    switch (kind) {
    case 0x0B: case 0x67:
        return 0x27;
    case 0x21: case 0x22: case 0x86:
        return 0x11;
    case 0x01: case 0x02: case 0x03: case 0x06: case 0x09: case 0x0D: case 0x0E:
    case 0x24: case 0x25: case 0x26: case 0x4A: case 0x4B: case 0x71: case 0x77:
    case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7E: case 0x82:
        return 0x0D;
    case 0x1E: case 0x55: case 0x56: case 0x57:
        return 0x10;
    case 0x04: case 0x05: case 0x07: case 0x69:
        return 0x0C;
    case 0x68:
        return 0x28;
    case 0x50: case 0x6B:
        return 0x22;
    case 0x58:
        return 0x23;
    case 0x0C: case 0x16: case 0x35: case 0x36:
        return 0x0B;
    case 0x14:
        return 0x01;
    case 0x0A: case 0x64: case 0x75:
        return 0x02;
    case 0x13: case 0x62:
        return 0x03;
    case 0x15:
        return 0x04;
    case 0x46:
        return 0x1A;
    case 0x6A: case 0x73:
        return 0x2B;
    case 0x81: case 0x84: case 0x85:
        return 0x2E;
    case 0x1C: case 0x1D:
        return 0x16;
    case 0x38: case 0x39:
        return 0x1D;
    case 0x23:
        return 0x0F;
    case 0x28:
        return 0x15;
    case 0x29:
        return 0x17;
    case 0x63:
        return 0x26;
    case 0x08: case 0x11: case 0x12: case 0x3B: case 0x3F: case 0x40: case 0x41:
    case 0x42: case 0x59: case 0x5A: case 0x5E: case 0x5F: case 0x60: case 0x65:
    case 0x66: case 0x6D: case 0x70: case 0x74: case 0x80: case 0x87: case 0x89:
    case 0x8C:
        return 0x09;
    case 0x2A:
        return 0x18;
    case 0x2B:
        return 0x1B;
    case 0x30:
        return 0x1E;
    case 0x19: case 0x1A: case 0x1B: case 0x27: case 0x2C: case 0x49: case 0x4C:
    case 0x4D: case 0x4E: case 0x4F: case 0x54: case 0x6E: case 0x72: case 0x7F:
    case 0x8B: case 0x8E: case 0x8F: case 0x90:
        return 0x0A;
    case 0x34:
        return 0x19;
    case 0x37:
        return 0x1C;
    case 0x3A:
        return 0x1F;
    case 0x47: case 0x48:
        return 0x21;
    case 0x6C:
        return 0x2C;
    case 0x7D:
        return 0x2D;
    case 0x83:
        return 0x2F;
    default:
        return 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006E3D70
HRESULT __stdcall TActionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9800;
    return S_OK;
}

// FUNCTION: GAMEMD 0x6E3DB0
HRESULT __stdcall TActionClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TActionClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_28);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_30);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_4C);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_50);
    return 0;
}

// FUNCTION: GAMEMD 0x6E3F70
CoordStruct TActionClass::FUN_006E3F70()
{
    return DAT_00A8B230->FUN_0068BD00(unknown_90);
}

// FUNCTION: GAMEMD 0x6E3FB0
void TActionClass::FUN_006E3FB0(const unsigned char* text)
{
    unknown_6D[0] = 0;
    if (text) {
        while (*text && *text <= ' ') {
            text++;
        }
        if (*text) {
            strncpy(unknown_6D, (const char*)text, 0x1f);
            unknown_6D[0x1f] = 0;
            int length = strlen(unknown_6D);
            while (length && (unsigned char)unknown_6D[length - 1] <= ' ') {
                length--;
            }
            unknown_6D[length] = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x6E4010
const char* TActionClass::FUN_006E4010()
{
    return unknown_6D[0] ? unknown_6D : 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4020
// Branching.
unsigned char FUN_006E4020(Obj_006E4020* a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1->unknown_30 != 0)
    {
        FUN_006F1F30(a1->unknown_30, a2, a1->unknown_90);
        return 1;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E4080
bool TActionClass::FUN_006E4080(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_00684060(unknown_90);
    return true;
}

// FUNCTION: GAMEMD 0x6E4100
bool TActionClass::FUN_006E4100(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    int index = unknown_90;
    if (index < 4 && index >= 0 && DAT_00880D2C[index].FUN_006ABAC0()) {
        MapInstance.FUN_006A7590(index);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E4150
bool TActionClass::FUN_006E4150(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    int index = FindNamedIndex(unknown_54);
    if (index < DAT_00A8EB10 && index >= 0) {
        MapInstance.FUN_006AC5F0(DAT_00A8EB04[index], unknown_90);
        return true;
    }
    return false;
}

struct Elem_006E4360 {
    void FUN_006CC290();
};
struct Rec_006E4360 {
    unsigned char unknown_00[0x258];
    Elem_006E4360** unknown_258;
    int unknown_25C;
    int unknown_260;
    int unknown_264;
};
GG_STATIC_ASSERT(offsetof(Rec_006E4360, unknown_258) == 0x258);
GG_STATIC_ASSERT(offsetof(Rec_006E4360, unknown_264) == 0x264);
struct Obj_006E4360 {
    unsigned char unknown_00[0x90];
    int unknown_90;
    bool FUN_006E4360(Rec_006E4360* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E4360, unknown_90) == 0x90);
// FUNCTION: GAMEMD 0x006E4360
bool Obj_006E4360::FUN_006E4360(Rec_006E4360* a1, int a2, int a3, int a4)
{
    if (a1 && unknown_90 >= 0 && unknown_90 <= a1->unknown_264) {
        a1->unknown_258[unknown_90]->FUN_006CC290();
        return true;
    }
    return false;
}

struct Elem_006E43A0 {
    void FUN_006CE0B0();
};
struct Rec_006E43A0 {
    unsigned char unknown_00[0x258];
    Elem_006E43A0** unknown_258;
    int unknown_25C;
    int unknown_260;
    int unknown_264;
};
GG_STATIC_ASSERT(offsetof(Rec_006E43A0, unknown_258) == 0x258);
GG_STATIC_ASSERT(offsetof(Rec_006E43A0, unknown_264) == 0x264);
struct Obj_006E43A0 {
    unsigned char unknown_00[0x90];
    int unknown_90;
    bool FUN_006E43A0(Rec_006E43A0* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E43A0, unknown_90) == 0x90);
// FUNCTION: GAMEMD 0x006E43A0
bool Obj_006E43A0::FUN_006E43A0(Rec_006E43A0* a1, int a2, int a3, int a4)
{
    if (a1 && unknown_90 >= 0 && unknown_90 <= a1->unknown_264) {
        a1->unknown_258[unknown_90]->FUN_006CE0B0();
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E43E0
bool TActionClass::FUN_006E43E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (house == 0) {
        return false;
    }
    CellStruct where = DAT_00A8B230->GetWaypointCoords(unknown_44);
    if (where.X == DAT_00B0E680.X && where.Y == DAT_00B0E680.Y) {
        return false;
    }
    house->FUN_0050DA00(where);
    return true;
}

// FUNCTION: GAMEMD 0x6E4460
bool TActionClass::FUN_006E4460(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (house == 0) {
        return false;
    }
    CellStruct where = DAT_00A8B230->GetWaypointCoords(unknown_44);
    if (where.X == DAT_00B0E680.X && where.Y == DAT_00B0E680.Y) {
        return false;
    }
    house->FUN_0050DA20(where);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006E44C0
bool __stdcall FUN_006E44C0(void* p, int, int, int)
{
    if (p == 0) {
        return false;
    }
    FUN_0050DA50(p);
    return true;
}

// FUNCTION: GAMEMD 0x6E44E0
bool TActionClass::FUN_006E44E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (house == 0) {
        return false;
    }
    CellStruct where = DAT_00A8B230->GetWaypointCoords(unknown_44);
    if (where.X == DAT_00B0E680.X && where.Y == DAT_00B0E680.Y) {
        return false;
    }
    house->FUN_0050DFE0(where);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006E4540
bool __stdcall FUN_006E4540(void* p, int, int, int)
{
    if (p == 0) {
        return false;
    }
    FUN_0050DFF0(p);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4630
// Returns a constant. Vtable slot 12 of TActionClass (RTTI).
int TActionClass::vf_12()
{
    return 0x94;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4640
// Returns a constant. Vtable slot 11 of TActionClass (RTTI).
int TActionClass::vf_11()
{
    return 0x2F;
}

GG_STATIC_ASSERT(offsetof(TActionClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(sizeof(((TActionClass*)0)->unknown_24) == 4);

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4650
// Member getter (dword). Vtable slot 16 of TActionClass (RTTI).
int TActionClass::vf_16()
{
    // Retail 0x6E4650 loads a dword at [ECX+0x24]; interpret the four-byte storage as that field.
    return *(int*)unknown_24;
}

// SYNTHETIC: GAMEMD 0x6E4660 -- scalar deleting destructor.

// FUNCTION: GAMEMD 0x6E4790
// Branching.
Obj_006E4790* Obj_006E4790::FUN_006E4790(int a1)
{
    if (a1 == 0)
    {
        unknown_00 = a1;
        return this;
    }
    FUN_007C91D0(this, a1, 0x1F);
    unknown_1F = 0;
    return this;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x880D2C
Obj_00880D2C DAT_00880D2C[4];
// GLOBAL: GAMEMD 0x8871E0
TActionRulesView* DAT_008871E0;
// GLOBAL: GAMEMD 0x8B3DC4
TechnoClass** DAT_008B3DC4;
// GLOBAL: GAMEMD 0x8B3DD0
int DAT_008B3DD0;
// GLOBAL: GAMEMD 0xA8B230
ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0xA8EAEC
TriggerClass** DAT_00A8EAEC;
// GLOBAL: GAMEMD 0xA8EAF8
int DAT_00A8EAF8;
// GLOBAL: GAMEMD 0xA8EB44
BuildingClass** DAT_00A8EB44;
// GLOBAL: GAMEMD 0xA8EB50
int DAT_00A8EB50;
// GLOBAL: GAMEMD 0xA8EC7C
TechnoClass** DAT_00A8EC7C;
// GLOBAL: GAMEMD 0xA8EC88
int DAT_00A8EC88;
// GLOBAL: GAMEMD 0xB0E680
CellStruct DAT_00B0E680;
// GLOBAL: GAMEMD 0xB0F658
DynamicVectorClass<TActionClass*> DAT_00B0F658;
// GLOBAL: GAMEMD 0xB0F670
DynamicVectorClass<TActionClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718 = 1.0;
// GLOBAL: GAMEMD 0x7F43B8
extern const double DAT_007F43B8 = 60.0;
// GLOBAL: GAMEMD 0x7E9800
extern const CLSID DAT_007E9800 = {0x4F0EC392, 0x0A55, 0x11D2, {0xAC, 0xA7, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// END defined globals
