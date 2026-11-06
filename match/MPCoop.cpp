// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MPCoop.cpp. The name is the source-file string at 0x82dc4c
//   in retail gamemd.exe v1.001, passed by the assert at 0x5c2272 inside this object's
//   code range (0x5c10f0-0x5c5aef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The header initialiser group at 0x5C1120, 0x5C1140 and 0x5C12C0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE268 reads 60.0 (ghidra memory read).
//
//   MPCoop.cpp (0x5C10F0..0x5C5AEF).

#include "FUNCTION.H"
#include "vector_ctor_pod_family_methods.h"
#include "deleting_dtor_sweep.h"
#include "winsock_interface_class.h"
#include <math.h>
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"

#include "header_init_shapes.h"
#include "scenario_session_globals.h"

// GLOBAL: GAMEMD 0xABF420
extern double DAT_00ABF420;
// GLOBAL: GAMEMD 0x7EE268
const double DAT_007EE268 = 60.0;


#include "mp_cooperative.h"
#include "_layout/ini_class.h"
#include "ccfile_class.h"
#include "_layout/house_type_class.h"
#include "_layout/node_name_type.h"
#include "mp_game_mode_class_methods.h"
#include "house_class_accessor_methods.h"


// LIBRARY: GAMEMD 0x7CD680 -- CRT _strnicmp (cdecl, locale-flag fast path).
extern "C" int __cdecl _strnicmp(const char* a, const char* b, size_t n);

// A record handed out by the 0x89F518 list: three 0x104-byte names behind +0x0C.
// Its +0x10 vector holds DynamicVectorClass-shaped string lists (Items +0x04,
// Count +0x10).
struct Rec_0049E3B0
{
    int   unknown_00;         // +0x00
    void* unknown_04;         // +0x04
    char  unknown_08[4];      // +0x08
    char (*Names)[0x104];     // +0x0C three MAX_PATH-sized strings
    DynamicVectorClassLayoutOf<DynamicVectorClassLayoutOf<const char*>*> Lists;   // +0x10 (Items +0x14, Count +0x20)
    DynamicVectorClassLayoutOf<DynamicVectorClassLayoutOf<const char*>*> Lists2;  // +0x28 (Items +0x2c, Count +0x38)
};
GG_STATIC_ASSERT(offsetof(Rec_0049E3B0, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Rec_0049E3B0, Names) == 0x0C);
GG_STATIC_ASSERT(offsetof(Rec_0049E3B0, Lists) == 0x10);
GG_STATIC_ASSERT(offsetof(Rec_0049E3B0, Lists2) == 0x28);


// Retail PAUMPlayerScoreType RTTI identifies mutable struct pointers and
// DynamicVectorClass -> VectorClass at offset zero. Complete entry-origin
// spans establish the bound methods; no GX emits the full deleting bodies.
// No TypeList or dynamic capacity constructor is claimed. Original TU
// boundaries, final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// Retail PAVCoopCampaignClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// Retail PAUNodeNameType RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct MPlayerScoreType;

// VTABLE: GAMEMD 0x7EE3D0 -- VectorClass<MPlayerScoreType*>.
template class VectorClass<MPlayerScoreType*>;
typedef VectorClass<MPlayerScoreType*> GgMPlayerScoreVectorClass;
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EE3F0 -- DynamicVectorClass<MPlayerScoreType*>.
template class DynamicVectorClass<MPlayerScoreType*>;
typedef DynamicVectorClass<MPlayerScoreType*> GgMPlayerScoreDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(MPlayerScoreType*) == 4);


class CoopCampaignClass;

// VTABLE: GAMEMD 0x7EE3B0 -- VectorClass<CoopCampaignClass*>.
template class VectorClass<CoopCampaignClass*>;
typedef VectorClass<CoopCampaignClass*> GgCoopCampaignClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EE350 -- DynamicVectorClass<CoopCampaignClass*>.
template class DynamicVectorClass<CoopCampaignClass*>;
typedef DynamicVectorClass<CoopCampaignClass*> GgCoopCampaignClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(CoopCampaignClass*) == 4);


struct NodeNameType;

// VTABLE: GAMEMD 0x7EE390 -- VectorClass<NodeNameType*>.
template class VectorClass<NodeNameType*>;
typedef VectorClass<NodeNameType*> GgNodenametypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EE370 -- DynamicVectorClass<NodeNameType*>.
template class DynamicVectorClass<NodeNameType*>;
typedef DynamicVectorClass<NodeNameType*> GgNodenametypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(NodeNameType*) == 4);

// FUNCTION: GAMEMD 0x49D9F0 (decl; reloc) -- look a name up; an index or -1.
int FUN_0049D9F0(const char* name);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);
// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7EE270
const double DAT_007EE270 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5C10F0
// GLOBAL: GAMEMD 0xABF420
double DAT_00ABF420 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));

// SYNTHETIC: GAMEMD 0x5C1120
// GLOBAL: GAMEMD 0xABF490
double DAT_00ABF490 = DAT_00ABF420 / DAT_007EE268;

// SYNTHETIC: GAMEMD 0x5C1140
// GLOBAL: GAMEMD 0xABF458
double DAT_00ABF458 = 1.0 / DAT_00ABF490;

// SYNTHETIC: GAMEMD 0x5C1160
// GLOBAL: GAMEMD 0xABF450
double DAT_00ABF450 = DAT_007EE270 * 45.0;

// SYNTHETIC: GAMEMD 0x5C1180
// GLOBAL: GAMEMD 0xABF428
double DAT_00ABF428 = DAT_007EE270 * 60.0;

// SYNTHETIC: GAMEMD 0x5C11A0
// GLOBAL: GAMEMD 0xABF400
double DAT_00ABF400 = DAT_007EE270 * 90.0;

// SYNTHETIC: GAMEMD 0x5C11C0
// GLOBAL: GAMEMD 0xABF498
int DAT_00ABF498 = (int)(FUN_004CAD50(DAT_00ABF400 - DAT_00ABF428) * DAT_00ABF420 * 0.5);

// SYNTHETIC: GAMEMD 0x5C1200
// GLOBAL: GAMEMD 0xABF430
double DAT_00ABF430 = FUN_004CADE0(DAT_00ABF498 * 0.00390625);

// SYNTHETIC: GAMEMD 0x5C1230
// GLOBAL: GAMEMD 0xABF448
double DAT_00ABF448 = FUN_004CADE0((DAT_00ABF498 * 2) / DAT_00ABF420);

// SYNTHETIC: GAMEMD 0x5C1260
// GLOBAL: GAMEMD 0xABF48C
int DAT_00ABF48C = (int)(DAT_00ABF498 * 4 + 0.5);

// SYNTHETIC: GAMEMD 0x5C1290
// GLOBAL: GAMEMD 0xABF418
HeaderCellInit DAT_00ABF418(0, 0);

// SYNTHETIC: GAMEMD 0x5C12A0
// GLOBAL: GAMEMD 0xABF438
HeaderCoordInit DAT_00ABF438(0, 0, 0);

// SYNTHETIC: GAMEMD 0x5C12C0
// GLOBAL: GAMEMD 0xABF480
HeaderCoordInit DAT_00ABF480(128, 128, 0);

// SYNTHETIC: GAMEMD 0x5C12E0
// GLOBAL: GAMEMD 0xABF408
MathTblZero4 DAT_00ABF408;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4F30
// DynamicVectorClass<MPlayerScoreType*>::copy constructor

// SYNTHETIC: GAMEMD 0x5C4FC0
// DynamicVectorClass<MPlayerScoreType*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5C5010
// DynamicVectorClass<MPlayerScoreType*>::Clear

// FUNCTION: GAMEMD 0x5C5040
// DynamicVectorClass<MPlayerScoreType*>::Slot5

// FUNCTION: GAMEMD 0x5C5060
// VectorClass<MPlayerScoreType*>::Slot6

// FUNCTION: GAMEMD 0x5C5130
// VectorClass<MPlayerScoreType*>::operator==

// FUNCTION: GAMEMD 0x5C5170
// VectorClass<MPlayerScoreType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5220
// VectorClass<MPlayerScoreType*>::Clear

// FUNCTION: GAMEMD 0x5C5250
// VectorClass<MPlayerScoreType*>::FindItemIndex

// FUNCTION: GAMEMD 0x5C5290
// VectorClass<MPlayerScoreType*>::Slot5

// FUNCTION: GAMEMD 0x5C52B0
// DynamicVectorClass<MPlayerScoreType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5360
// DynamicVectorClass<MPlayerScoreType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5C5850
// VectorClass<MPlayerScoreType*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5C59E0
// VectorClass<MPlayerScoreType*>::capacity constructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C5070
// DynamicVectorClass<NodeNameType*>::Clear

// FUNCTION: GAMEMD 0x5C50A0
// DynamicVectorClass<NodeNameType*>::Slot5

// FUNCTION: GAMEMD 0x5C50C0
// VectorClass<NodeNameType*>::Slot6

// FUNCTION: GAMEMD 0x5C5390
// VectorClass<NodeNameType*>::operator==

// FUNCTION: GAMEMD 0x5C53D0
// VectorClass<NodeNameType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5480
// VectorClass<NodeNameType*>::Clear

// FUNCTION: GAMEMD 0x5C54B0
// VectorClass<NodeNameType*>::FindItemIndex

// FUNCTION: GAMEMD 0x5C54F0
// VectorClass<NodeNameType*>::Slot5

// FUNCTION: GAMEMD 0x5C5510
// DynamicVectorClass<NodeNameType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C55C0
// DynamicVectorClass<NodeNameType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5C58A0
// VectorClass<NodeNameType*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5C58F0
// DynamicVectorClass<NodeNameType*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C50D0
// DynamicVectorClass<CoopCampaignClass*>::Clear

// FUNCTION: GAMEMD 0x5C5100
// DynamicVectorClass<CoopCampaignClass*>::Slot5

// FUNCTION: GAMEMD 0x5C5120
// VectorClass<CoopCampaignClass*>::Slot6

// FUNCTION: GAMEMD 0x5C55F0
// VectorClass<CoopCampaignClass*>::operator==

// FUNCTION: GAMEMD 0x5C5630
// VectorClass<CoopCampaignClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5C56E0
// VectorClass<CoopCampaignClass*>::Clear

// FUNCTION: GAMEMD 0x5C5710
// VectorClass<CoopCampaignClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x5C5750
// VectorClass<CoopCampaignClass*>::Slot5

// FUNCTION: GAMEMD 0x5C5770
// DynamicVectorClass<CoopCampaignClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5820
// DynamicVectorClass<CoopCampaignClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5C5940
// VectorClass<CoopCampaignClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5C5990
// DynamicVectorClass<CoopCampaignClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- StringTable::LoadString.
wchar_t* StringTable_LoadString(const char* label, int* out,
                                const char* file, int line);

// STRING: GAMEMD 0x82DC78 -- "GUI:Random".
extern const char STR_0082DC78[];
// STRING: GAMEMD 0x82DC4C -- this module's __FILE__ ("D:\\ra2mdpost\\MPCoop.cpp").
extern const char STR_0082DC4C[];

// FUNCTION: GAMEMD 0x5EBC00 (decl; reloc) -- __fastcall (dialog, mode).
void FUN_005EBC00(HWND dialog, int mode);

// FUNCTION: GAMEMD 0x5E8760 (decl; reloc) -- the caller tests AL, so the
// result is a bool here (the matched body is typed int in netshare_slot_nodes).
bool FUN_005E8760();

// FUNCTION: GAMEMD 0x005C5A80
// vtable constant: 0x7EE3B0
GG_VECTOR_CTOR_POD_BODY(VectorClass_005C5A80, PodElem4, 0x7EE3B0)

// STRING: GAMEMD 0x82DC64 -- "NAME:COOPDESC%d%d".
extern const char STR_0082DC64[];
// GLOBAL: GAMEMD 0xA8EB68 -- the value posted with message 0x405.
extern LPARAM DAT_00A8EB68;

// FUNCTION: GAMEMD 0x5E6520 (decl; reloc) -- __fastcall, the slot count of the selected entry.
int FUN_005E6520(int entry);
// GLOBAL: GAMEMD 0xA8B274 -- the number of AI players being added.
extern int DAT_00A8B274;

// FUNCTION: GAMEMD 0x5E2700 (decl; reloc) -- cdecl (id, text).
void __cdecl FUN_005E2700(int id, const wchar_t* text);
// GLOBAL: GAMEMD 0xA8DA74 -- the lobby's player node vector (also MPGameModeArray below).
extern DynamicVectorClass<NodeNameType*> DAT_00A8DA74;
// FUNCTION: GAMEMD 0x5C6120 (decl; reloc) -- __fastcall: delete every item of the vector, then its slot 3.
void FUN_005C6120(DynamicVectorClass<NodeNameType*>* vector);
// LIBRARY: GAMEMD 0x7DD0F8 -- CRT _wcsicmp.
extern "C" int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
// LIBRARY: GAMEMD 0x7CA489 -- CRT wcscpy.
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
// GLOBAL: GAMEMD 0xA8B54C -- the number of nodes mirrored by 0x5C4CA0.
extern int DAT_00A8B54C;
// GLOBAL: GAMEMD 0x89E04C -- a flag read and cleared by 0x5C42D0.
extern bool DAT_0089E04C;
// LIBRARY: GAMEMD 0x7C9CC2 -- CRT strtok.
extern "C" char* __cdecl strtok(char* str, const char* delim);
// LIBRARY: GAMEMD 0x7C9B72 (decl; reloc) -- a CRT text-to-int parser (not the 0x7C9BFD one).
extern "C" int __cdecl FUN_007C9B72(const char* text);
// FUNCTION: GAMEMD 0x5E3720 (decl; reloc) -- __fastcall (text).
void FUN_005E3720(const char* text);
// FUNCTION: GAMEMD 0x775940 (decl; reloc) -- __fastcall (id): a dialog handle, or null.
HWND FUN_00775940(int id);
// GLOBAL: GAMEMD 0x8316A4 -- set to -1 by 0x5C1A10.
extern int DAT_008316A4;
// FUNCTION: GAMEMD 0x775B10 (decl; reloc) -- the current dialog window.
HWND __cdecl FUN_00775B10();
// LIBRARY: GAMEMD 0x7C8D20 -- CRT _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);
// FUNCTION: GAMEMD 0x5E7BF0 (decl; reloc) -- __fastcall (index).
void FUN_005E7BF0(int index);
// FUNCTION: GAMEMD 0x5E2EF0 (decl; reloc) -- __fastcall (dialog, mode).
void FUN_005E2EF0(HWND dialog, struct MPCooperative* mode);
// FUNCTION: GAMEMD 0x5E2F60 (decl; reloc) -- __fastcall (dialog).
void FUN_005E2F60(HWND dialog);
// FUNCTION: GAMEMD 0x5E74E0 (decl; reloc) -- __fastcall (dialog); EDX is left over.
void FUN_005E74E0(HWND dialog);
// FUNCTION: GAMEMD 0x5E32D0 (decl; reloc) -- __fastcall (force, poll).
void FUN_005E32D0(char force, char poll);
// GLOBAL: GAMEMD 0x887734 -- the object both arguments of 0x49B760 name.
extern char DAT_00887734[];

// FUNCTION: GAMEMD 0x4E37D0 (decl; reloc) -- the control id for slot `index`.
int FUN_004E37D0(int index);

// FUNCTION: GAMEMD 0x4E3F70 (decl; reloc) -- __fastcall (dialog, id) + one stack word.
void FUN_004E3F70(HWND dialog, int id, int value);

// FUNCTION: GAMEMD 0x5E26C0 (decl; reloc) -- a dialog handle, or null.
HWND FUN_005E26C0();

// GLOBAL: GAMEMD 0xA8DA90 -- the eight lobby slots.
extern MPGameModeEntry* DAT_00A8DA90[8];

// An entry of the 0xA83C98 vector; +0x60 is handed to the combo as item text.
struct Entry_00A83C9C
{
    char   unknown_00[0x60];  // +0x00
    const wchar_t* unknown_60; // +0x60 item text
};
// GLOBAL: GAMEMD 0xA83C9C -- that vector's Items.
extern Entry_00A83C9C** DAT_00A83C9C;
// GLOBAL: GAMEMD 0xA83CA8 -- that vector's Count.
extern int DAT_00A83CA8;
struct List_0089F518
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x49E3B0 (decl; reloc) -- fetch record `index` into *out; RET 8.
    void FUN_0049E3B0(int index, Rec_0049E3B0** out);
    // FUNCTION: GAMEMD 0x49E4F0 (decl; reloc) -- the record count into *out; RET 4.
    void FUN_0049E4F0(int* out);
};
// GLOBAL: GAMEMD 0x89F518
extern List_0089F518 DAT_0089F518;
// GLOBAL: GAMEMD 0x89F574 -- the record count.
extern int DAT_0089F574;
// An entry of the 0xA8B8C8 vector; its name starts at +0x58.
struct Entry_00A8B8CC
{
    char unknown_00[0x58];    // +0x00
    char Name[1];             // +0x58
};
// GLOBAL: GAMEMD 0xA8B8CC -- that vector's Items.
extern Entry_00A8B8CC** DAT_00A8B8CC;
// FUNCTION: GAMEMD 0x5E66D0 (decl; reloc) -- the selected index.
int FUN_005E66D0();
// FUNCTION: GAMEMD 0x775B20 (decl; reloc) -- the current dialog's template id.
int __cdecl FUN_00775B20();
// GLOBAL: GAMEMD 0xA8B8D8 -- that vector's Count.
extern int DAT_00A8B8D8;
// GLOBAL: GAMEMD 0xA8B254 -- the selected entry index (0 = none).
extern int DAT_00A8B254;

// FUNCTION: GAMEMD 0x688380 (decl; reloc) -- the start cells for a map.
DynamicVectorClass<Cell> FUN_00688380(bool flag);
// GLOBAL: GAMEMD 0xA8B27C -- the per-slot choice tables lie back to back, eight ints each
// (0xA8B27C AI difficulty, 0xA8B29C start position, 0xA8B2BC, 0xA8B2DC colour, 0xA8B2FC team);
// retail addresses them from the one base with a single induction pointer (`[esi+0x20]`,
// `[eax-0x40]`), so they are indexed here as rows of eight from DAT_00A8B27C (declared
// extern int[8] in scenario_session_globals.h).
enum { SLOT_ROW = 8, ROW_START = 1 * SLOT_ROW, ROW_UNKNOWN = 2 * SLOT_ROW, ROW_COLOUR = 3 * SLOT_ROW, ROW_TEAM = 4 * SLOT_ROW };

// GLOBAL: GAMEMD 0xABF460 -- eight per-entry values (`MOV ECX,8; REP STOSD`).
int DAT_00ABF460[8];

// GLOBAL: GAMEMD 0xABF490
extern double DAT_00ABF490;

// GLOBAL: GAMEMD 0xABF458
extern double DAT_00ABF458;


// LIBRARY: GAMEMD 0x7C8EF4 -- CRT sprintf.
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// FUNCTION: GAMEMD 0x5C1470
// The base gets `false` for its fifth argument. Then empty the campaign list
// (keeping its capacity) and refill it with one campaign per record of the
// 0x89F518 list.
//
// PARTIAL (99.4% now that the campaign count is read through GetCount(); was 56.6%). Everything up to the +0x324 member matches; retail then
// calls the out-of-line VectorClass<CoopCampaignClass*> constructor 0x5C5A80
// while cl expands it inline (it keeps the VectorClass<int> calls out of line),
// shifting the rest. Declaring the instantiation `extern template` reaches
// 91.8% but also un-inlines the destructor's vector teardown (0x5C1640 drops
// to 41.3%), so it is not kept; the decision is cl's inliner, not the source.
MPCooperative::MPCooperative(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, false, f)
{
    unknown_40 = 0;
    unknown_44 = 0;
    unknown_33C = 0;
    unknown_50 = 0;
    unknown_04 = false;
    unknown_48 = false;
    unknown_49 = false;
    unknown_4C = 0;
    unknown_340 = true;

    for (int i = Campaigns.GetCount() - 1; i >= 0; i--) {
        delete Campaigns.Items[i];
    }
    int capacity = Campaigns.Capacity;
    Campaigns.Clear();
    Campaigns.SetCapacity(capacity, 0);

    int count;
    DAT_0089F518.FUN_0049E4F0(&count);
    for (int n = 0; n < count; n++) {
        CoopCampaignClass* campaign = new CoopCampaignClass;
        campaign->FUN_0049CAF0(n);
        Campaigns.AddItem(campaign);
    }
}

// FUNCTION: GAMEMD 0x5C1640
MPCooperative::~MPCooperative()
{
    if (unknown_40 != 0) {
        delete unknown_40;
        unknown_40 = 0;
    }
    int i;
    for (i = Campaigns.Count - 1; i >= 0; i--) {
        delete Campaigns.Items[i];
    }
    Campaigns.Clear();
    for (i = Nodes.Count - 1; i >= 0; i--) {
        operator delete(Nodes.Items[i]);
    }
    int capacity = Nodes.Capacity;
    Nodes.Clear();
    Nodes.SetCapacity(capacity, 0);
    if (unknown_50 != 0) {
        delete unknown_50;
        unknown_50 = 0;
    }
    unknown_04 = false;
}

// FUNCTION: GAMEMD 0x5C17B0
// Whether the current campaign's record at +0x33C accepts `a`: true when the
// record is absent, when the position at +0x40 is past its list, for -3, and
// for -2 with more than one name; otherwise true when one of the position's
// names resolves to `a`.
bool MPCooperative::FUN_005C17B0(int a)
{
    int cur = 0;
    Rec_0049E3B0* rec;
    DAT_0089F518.FUN_0049E3B0(unknown_33C, &rec);
    if (rec == 0) {
        return true;
    }
    if (unknown_40 != 0) {
        if (!unknown_40->FUN_0049BCC0(&cur)) {
            cur = 0;
        }
    } else {
        cur = 0;
    }
    if (cur >= rec->Lists.Count) {
        return true;
    }
    if (a == -2) {
        if (rec->Lists.Items[cur]->Count > 1) {
            return true;
        }
    } else if (a == -3) {
        return true;
    }
    bool found = false;
    for (int i = 0; i < rec->Lists.Items[cur]->Count; i++) {
        if (FUN_0049D9F0(rec->Lists.Items[cur]->Items[i]) == a) {
            found = true;
            break;
        }
    }
    return found;
}

// FUNCTION: GAMEMD 0x5C18A0
// Empty the campaign list (keeping its capacity) and refill it with one
// campaign per record of the 0x89F518 list, as the constructor does. Always true.
//
// PARTIAL (84.7%). Same instructions as retail; register naming differs: retail keeps `this` in
// EBX, the loop index in EDI and the element in ESI, then reuses ESI as &Campaigns (LEA); cl keeps
// `this` in ESI and ends with ADD ESI,0x324. Tried: GetCount() against Count for the loop start, a
// `while (--i >= 0)` loop, a named element local (all 84.7%).
bool MPCooperative::FUN_005C18A0()
{
    for (int i = Campaigns.Count - 1; i >= 0; i--) {
        delete Campaigns.Items[i];
    }
    int capacity = Campaigns.Capacity;
    Campaigns.Clear();
    Campaigns.SetCapacity(capacity, 0);

    int count;
    DAT_0089F518.FUN_0049E4F0(&count);
    for (int n = 0; n < count; n++) {
        CoopCampaignClass* campaign = new CoopCampaignClass;
        campaign->FUN_0049CAF0(n);
        Campaigns.AddItem(campaign);
    }
    return true;
}

// FUNCTION: GAMEMD 0x5C1980
// The last record one of whose three names prefixes-matches (case-blind, for
// the name's own length) the selected entry's name, or -1.
//
// PARTIAL (11.9%). Same blocks and calls; retail keeps the result in a stack
// slot (`SUB ESP,8`, record index in EBP, name offset in EBX) where cl gives
// the result a register, so every instruction shifts. Tried a nested if with a
// name local (10.2%), one && condition (11.9%) and the names as char[][0x104]
// (11.9%).
int FUN_005C1980()
{
    int found = -1;
    for (int i = 0; i < DAT_0089F574; i++) {
        Rec_0049E3B0* rec;
        DAT_0089F518.FUN_0049E3B0(i, &rec);
        for (int j = 0; j < 3; j++) {
            if (DAT_00A8B254 != 0
                && _strnicmp(DAT_00A8B8CC[DAT_00A8B254]->Name, rec->Names[j],
                             strlen(rec->Names[j])) == 0) {
                found = i;
            }
        }
    }
    return found;
}

// FUNCTION: GAMEMD 0x5C1CB0
// Sets the byte at +0x340 to one. MPCooperative vtable slot 9.
void MPCooperative::vf_9()
{
    unknown_340 = 1;
}

// FUNCTION: GAMEMD 0x5C1CC0
// Make sure the campaign helper exists, reset it to the first record and find
// the map entry whose name begins with the helper's name. Returns its index;
// when none matches, calls virtual slot 4 and returns -1. -1 when the list is empty.
int MPCooperative::FUN_005C1CC0()
{
    int i = 0;
    int count = 0;
    const char* name = 0;
    DAT_0089F518.FUN_0049E4F0(&count);
    if (count != 0) {
        if (unknown_40 == 0) {
            unknown_40 = new CoopCampaignClass;
        }
        unknown_40->FUN_0049CAF0(0);
        unknown_40->FUN_0049D070(&name, 0);
        for (; i < DAT_00A8B8D8; i++) {
            const char* entryName = DAT_00A8B8CC[i]->Name;
            if (_strnicmp(entryName, name, strlen(name)) == 0) {
                return i;
            }
        }
        vf_4();
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5C1DC0
// Apply the selected campaign index. Past the record count, send the helper
// to the game modes and flag it; on the dialog case swap in a fresh campaign
// at the index. Then, for the helper's position, mark every game-mode entry
// that slot 7 rejects with -2 (several names) or its first name's index.
// False when the helper, or the record, is missing.
bool MPCooperative::FUN_005C1DC0()
{
    if (unknown_40 == 0) {
        return false;
    }
    int count;
    DAT_0089F518.FUN_0049E4F0(&count);
    int index = FUN_005E66D0();
    if (index >= count) {
        if (MPGameModeArray.Count == 2) {
            unknown_40->FUN_0049B760(((void**)MPGameModeArray.Items)[0],
                                     ((void**)MPGameModeArray.Items)[1]);
        }
        if (!unknown_40->FUN_0049C0D0()) {
            return false;
        }
        unknown_48 = true;
    } else if (FUN_00775B20() == 0x6B) {
        delete unknown_40;
        unknown_40 = Campaigns.Items[index];
        Campaigns.Items[index] = new CoopCampaignClass;
        Campaigns.Items[index]->FUN_0049CAF0(index);
        unknown_4C = index;
        if (MPGameModeArray.Count == 2) {
            unknown_40->FUN_0049B760(((void**)MPGameModeArray.Items)[0],
                                     ((void**)MPGameModeArray.Items)[1]);
        }
    }

    int cur = 0;
    Rec_0049E3B0* rec;
    DAT_0089F518.FUN_0049E3B0(unknown_33C, &rec);
    if (rec == 0) {
        return false;
    }
    if (unknown_40 == 0 || !unknown_40->FUN_0049BCC0(&cur)) {
        cur = 0;
    }
    if (cur >= rec->Lists.Count) {
        return false;
    }
    if (rec->Lists.Count == 0) {
        return false;
    }
    int names = rec->Lists.Items[cur]->Count;
    FUN_005C2500(FUN_005E26C0());
    for (int i = 0; i < MPGameModeArray.Count; i++) {
        if (!vf_7(((MPGameModeEntry**)MPGameModeArray.Items)[i]->Classify())) {
            if (names > 1) {
                ((MPGameModeEntry**)MPGameModeArray.Items)[i]->FUN_00696F90(-2);
            } else {
                ((MPGameModeEntry**)MPGameModeArray.Items)[i]->FUN_00696F90(
                    FUN_0049D9F0(rec->Lists.Items[cur]->Items[0]));
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5C2040
// Make sure the helper exists, note when its position changes, and hand the
// new position and the vector to the helper. MPCooperative vtable slot 22.
//
// The vector argument is passed by value through 0x4779E0 as retail does. The call to 0x5C3EC0
// stays a call because that helper's result is built with a result variable and an if/else.
bool MPCooperative::vf_22(int a, MPGameModeArgVector v, int b, int c)
{
    if (unknown_40 == 0) {
        FUN_005C3EC0();
        unknown_340 = true;
    }
    if (unknown_40 == 0) {
        return false;
    }
    int cur;
    unknown_40->FUN_0049BC80(&cur);
    if (cur != a) {
        unknown_340 = true;
    }
    unknown_40->FUN_0049CCF0(a, v, b, c);
    unknown_33C = a;
    return true;
}

// FUNCTION: GAMEMD 0x5C2100
// Hand both campaign copies of `pair` to the helper at +0x40 with the two
// indices; when its position changed, or a refresh is pending, redraw the
// dialog and clear the pending flag. False when there is no helper.
bool MPCooperative::FUN_005C2100(int a, int b, CoopCampaignClass* pair)
{
    if (unknown_40 == 0) {
        return false;
    }
    int cur;
    unknown_40->FUN_0049BCC0(&cur);
    bool result = unknown_40->FUN_0049CC50(a, b, pair[0], pair[1]);
    if (cur != a || unknown_340) {
        HWND dialog = FUN_005E26C0();
        if (dialog != 0) {
            FUN_005C2500(dialog);
            unknown_340 = false;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x5C21D0
// Show or hide the co-op description and the four related controls. The
// description text comes from "NAME:COOPDESC<a+1><b+1>" when the campaign at
// +0x40 reports both of its values.
//
// Each show/hide and enable is an if/else of two whole calls; cl merges their
// common argument pushes into retail's `je; push 5; jmp; push 0` shape. A
// `show ? SW_SHOW : SW_HIDE` argument is computed with neg/sbb instead and
// keeps `show` live in a register (3.4%).
void MPCooperative::FUN_005C21D0(HWND dialog, bool show)
{
    bool ok = true;
    if (show) {
        FUN_005EBC00(dialog, 2);
    }
    if (unknown_40 != 0) {
        int a;
        int b;
        if (!unknown_40->FUN_0049BC80(&a)) {
            ok = false;
        }
        if (unknown_40->FUN_0049BCC0(&b) && ok) {
            char label[0x40];
            sprintf(label, STR_0082DC64, a + 1, b + 1);
            HWND text = GetDlgItem(dialog, 0x72F);
            if (text == 0) {
                return;
            }
            SendMessageA(text, 0x4B2, 0,
                (LPARAM)StringTable_LoadString(label, 0, STR_0082DC4C, 0x281));
            if (show) {
                ShowWindow(text, SW_SHOW);
                InvalidateRect(text, 0, FALSE);
            } else {
                ShowWindow(text, SW_HIDE);
                InvalidateRect(text, 0, FALSE);
            }
        }
    }

    HWND control = GetDlgItem(dialog, 0x732);
    if (control != 0) {
        PostMessageA(control, 0x4AC, 0, 0);
        PostMessageA(control, 0x406, 1, 0x20000);
        PostMessageA(control, 0x405, 1, DAT_00A8EB68);
        if (show) {
            ShowWindow(control, SW_SHOW);
        } else {
            ShowWindow(control, SW_HIDE);
        }
        if (FUN_005E8760()) {
            EnableWindow(control, TRUE);
        } else {
            EnableWindow(control, FALSE);
        }
        InvalidateRect(control, 0, TRUE);
    }
    control = GetDlgItem(dialog, 0x78E);
    if (control != 0) {
        if (show) {
            ShowWindow(control, SW_SHOW);
        } else {
            ShowWindow(control, SW_HIDE);
        }
    }
    control = GetDlgItem(dialog, 0x78D);
    if (control != 0) {
        if (show) {
            ShowWindow(control, SW_SHOW);
        } else {
            ShowWindow(control, SW_HIDE);
        }
    }
    control = GetDlgItem(dialog, 0x78C);
    if (control != 0) {
        if (show) {
            ShowWindow(control, SW_SHOW);
        } else {
            ShowWindow(control, SW_HIDE);
        }
    }
}

// FUNCTION: GAMEMD 0x5C23B0
// Refill one combo with the choices of the current campaign record: a
// "GUI:Random" item (data -2) when there is more than one, then every listed
// name that resolves to a valid entry, tagged with that entry's index.
//
// PARTIAL (98.3%): the entry's +0x60 text is loaded into EDX where retail
// uses EAX (multiset identical). Typing the field LPARAM or wchar_t* gives
// the same; only a redundant `text` local reaches 100%, which the no-steering
// rule excludes.
void MPCooperative::FUN_005C23B0(HWND dialog, int id)
{
    int count = DAT_00A83CA8;
    if (count == 0) {
        return;
    }
    HWND combo = GetDlgItem(dialog, id);
    ShowWindow(combo, SW_HIDE);
    SendMessageA(combo, CB_RESETCONTENT, 0, 0);

    Rec_0049E3B0* rec;
    int index = 0;
    DAT_0089F518.FUN_0049E3B0(unknown_33C, &rec);
    if (rec == 0 || rec->Lists.Count == 0) {
        return;
    }
    if (unknown_40 == 0 || !unknown_40->FUN_0049BCC0(&index)) {
        index = 0;
    }
    if (index >= rec->Lists.Count) {
        return;
    }
    int n = ((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Count;
    if (n > 1) {
        LRESULT item = SendMessageA(combo, 0x4C2, 0,
            (LPARAM)StringTable_LoadString(STR_0082DC78, 0, STR_0082DC4C, 0x2ED));
        SendMessageA(combo, CB_SETITEMDATA, item, -2);
    }
    for (int i = 0; i < n; i++) {
        int entry = FUN_0049D9F0(((char**)((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Items)[i]);
        if (entry >= 0 && entry < count) {
            LRESULT item = SendMessageA(combo, 0x4C2, 0, (LPARAM)DAT_00A83C9C[entry]->unknown_60);
            SendMessageA(combo, CB_SETITEMDATA, item, entry);
        }
    }
    SendMessageA(combo, CB_SETCURSEL, 0, 0);
    ShowWindow(combo, SW_SHOW);
}

// FUNCTION: GAMEMD 0x5C2500
// For every slot up to the player limit: refill its combo, then select the
// random item (-2) when the campaign record lists several choices, else the
// one listed name's entry; mirror the choice into the slot. Then show the
// co-op controls on the dialog 0x5E26C0 reports.
void MPCooperative::FUN_005C2500(HWND dialog)
{
    if (dialog == 0) {
        return;
    }
    int limit = SessionPlayerLimit;
    Rec_0049E3B0* rec;
    int index = 0;
    DAT_0089F518.FUN_0049E3B0(unknown_33C, &rec);
    if (rec == 0 || rec->Lists.Count == 0) {
        return;
    }
    if (unknown_40 != 0) {
        if (!unknown_40->FUN_0049BCC0(&index)) {
            index = 0;
        }
    } else {
        index = 0;
    }
    if (index >= rec->Lists.Count) {
        return;
    }
    int n = ((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Count;
    for (int i = 0; i < limit; i++) {
        int id = FUN_004E37D0(i);
        FUN_005C23B0(dialog, id);
        if (n > 1) {
            FUN_004E3F70(dialog, id, -2);
            DAT_00A8DA90[i]->FUN_00696F90(-2);
        } else {
            int entry = FUN_0049D9F0(((char**)((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Items)[0]);
            FUN_004E3F70(dialog, id, entry);
            DAT_00A8DA90[i]->FUN_00696F90(entry);
        }
    }
    FUN_005EBC00(dialog, limit);
    HWND shown = FUN_005E26C0();
    if (shown != 0) {
        FUN_005C21D0(shown, true);
    }
}

// FUNCTION: GAMEMD 0x5C26D0
// Reset the table to -2, then fill one slot per game-mode array entry from
// the entry's 0x696F30.
void FUN_005C26D0()
{
    int i;

    for (i = 0; i < 8; i++) {
        DAT_00ABF460[i] = -2;
    }
    int count = MPGameModeArray.Count;
    for (i = 0; i < count; i++) {
        DAT_00ABF460[i] = ((MPGameModeEntry**)MPGameModeArray.Items)[i]->FUN_00696F30();
    }
}

// FUNCTION: GAMEMD 0x5C2D00
// Give `house` a start spot. While fewer spots are taken than there are human
// houses, pick a random co-op spot and walk forward (wrapping) to a free one;
// otherwise take the first free spot from the co-op count onwards. Mark it
// taken and record the house on the scenario.
void MPCooperative::FUN_005C2D00(int house, DynamicVectorClassLayout* spots, bool* taken)
{
    int used = 0;
    int i;
    for (i = 0; i < spots->Count; i++) {
        if (taken[i]) {
            used++;
        }
    }

    int humans = 0;
    for (i = 0; i < HouseClass_Array.Count; i++) {
        HouseClass* h = HouseClass_Array.Items[i];
        if (h != 0 && h->IsControlledByHuman()) {
            humans++;
        }
    }

    int spot;
    if (used < humans) {
        int coop = MPCoopScenario_00A8B230->NumCoopHumanStartSpots - 1;
        spot = MPCoopScenario_00A8B230->Random.FUN_0065C7E0(0, coop);
        while (taken[spot]) {
            spot = (spot + 1) % MPCoopScenario_00A8B230->NumCoopHumanStartSpots;
        }
    } else {
        spot = MPCoopScenario_00A8B230->NumCoopHumanStartSpots;
        while (taken[spot] && spot < spots->Count) {
            spot++;
        }
    }
    taken[spot] = true;
    MPCoopScenario_00A8B230->StartHouse[spot] = house;
}

// FUNCTION: GAMEMD 0x5C30C0
// Fill the AI slots after the human start spots: as many as the selected
// entry has slots beyond the humans get a difficulty (2 when the posted
// value is 0, else 1 only for the value 1) and -2 for position, colour and
// team; the rest are cleared to -1. False when there is nothing to add or the
// record or its position is missing.
bool MPCooperative::FUN_005C30C0()
{
    int ai = FUN_005E6520(DAT_00A8B254) - MPCoopScenario_00A8B230->NumCoopHumanStartSpots;
    FUN_004068E0("@@@@ Adding %d AI players\n", ai);
    if (ai <= 0) {
        return false;
    }
    int added = 0;
    int cur = 0;
    DAT_00A8B274 = ai;
    Rec_0049E3B0* rec;
    DAT_0089F518.FUN_0049E3B0(unknown_33C, &rec);
    if (rec == 0) {
        return false;
    }
    if (rec->Lists2.Count == 0) {
        return false;
    }
    if (unknown_40 == 0 || !unknown_40->FUN_0049BCC0(&cur)) {
        cur = 0;
    }
    if (cur >= rec->Lists2.Count) {
        return false;
    }
    for (int n = MPCoopScenario_00A8B230->NumCoopHumanStartSpots; n < 8; n++) {
        if (added < ai) {
            FUN_004068E0("@@@@ Setting slot %d for AI\n", n);
            if (DAT_00A8EB68 == 0) {
                DAT_00A8B27C[n] = 2;
            } else {
                DAT_00A8B27C[n] = DAT_00A8EB68 == 1;
            }
            FUN_004068E0("@@@@     AI difficulty: %d\n", DAT_00A8B27C[n]);
            DAT_00A8B27C[ROW_START + n] = -2;
            DAT_00A8B27C[ROW_UNKNOWN + n] = -2;
            DAT_00A8B27C[ROW_COLOUR + n] = -2;
            DAT_00A8B27C[ROW_TEAM + n] = -2;
            added++;
        } else {
            DAT_00A8B27C[n] = -1;
            DAT_00A8B27C[ROW_START + n] = -1;
            DAT_00A8B27C[ROW_UNKNOWN + n] = -1;
            DAT_00A8B27C[ROW_COLOUR + n] = -1;
            DAT_00A8B27C[ROW_TEAM + n] = -1;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5C34F0
// Pick a random map entry that the current position's first list of the
// record at the helper's index names, and return its index. 0 when the
// record or position is missing. MPCooperative vtable slot 27.
int MPCooperative::vf_27()
{
    int count = DAT_00A83CA8;
    bool found = false;
    int index = 0;
    unknown_40->FUN_0049BC80(&index);
    int cur = 0;
    Rec_0049E3B0* rec;
    DAT_0089F518.FUN_0049E3B0(index, &rec);
    if (rec == 0) {
        return 0;
    }
    if (unknown_40 == 0 || !unknown_40->FUN_0049BCC0(&cur)) {
        cur = 0;
    }
    if (cur >= rec->Lists.Count) {
        return 0;
    }
    int pick;
    do {
        pick = MPCoopScenario_00A8B230->Random.FUN_0065C7E0(0, count - 1);
        for (int i = 0; i < rec->Lists.Items[cur]->Count; i++) {
            if (pick == FUN_0049D9F0(rec->Lists.Items[cur]->Items[i])) {
                found = true;
            }
        }
    } while (!found);
    FUN_004068E0("@@@@ Choosing a random player house: %d(%s)\n", pick,
                 NarrowName_007350C0(DAT_00A83C9C[pick]->unknown_60));
    return pick;
}

// FUNCTION: GAMEMD 0x5C35F0
// The same for the record's second list. MPCooperative vtable slot 28.
int MPCooperative::vf_28()
{
    int count = DAT_00A83CA8;
    bool found = false;
    int index = 0;
    unknown_40->FUN_0049BC80(&index);
    int cur = 0;
    Rec_0049E3B0* rec;
    DAT_0089F518.FUN_0049E3B0(index, &rec);
    if (rec == 0) {
        return 0;
    }
    if (unknown_40 == 0 || !unknown_40->FUN_0049BCC0(&cur)) {
        cur = 0;
    }
    if (cur >= rec->Lists2.Count) {
        return 0;
    }
    int pick;
    do {
        pick = MPCoopScenario_00A8B230->Random.FUN_0065C7E0(0, count - 1);
        for (int i = 0; i < rec->Lists2.Items[cur]->Count; i++) {
            if (pick == FUN_0049D9F0(rec->Lists2.Items[cur]->Items[i])) {
                found = true;
            }
        }
    } while (!found);
    FUN_004068E0("@@@@ Choosing a random AI house: %d(%s)\n", pick,
                 NarrowName_007350C0(DAT_00A83C9C[pick]->unknown_60));
    return pick;
}

// FUNCTION: GAMEMD 0x5C36F0
// Tail-forwards to another function. Vtable slot 35 of MPCooperative (RTTI).
bool MPCooperative::vf_35()
{
    return MultiplayerGameMode::vf_35();
}

// FUNCTION: GAMEMD 0x5C3700
// Returns a constant boolean. Vtable slot 15 of MPCooperative (RTTI).
bool MPCooperative::vf_15()
{
    return false;
}

// FUNCTION: GAMEMD 0x5C3EC0
// (A result variable set in an if/else keeps cl from expanding this into 0x5C2040; the
// ternary form is expanded there.)
// Replace the helper at +0x40 with a fresh one, run its 0x49CAF0(0), and with
// exactly two entries in the game-mode array hand both to 0x49B760. True when
// the helper exists.
bool MPCooperative::FUN_005C3EC0()
{
    if (unknown_40 != 0) {
        delete unknown_40;
    }
    unknown_40 = 0;
    unknown_40 = new CoopCampaignClass;
    unknown_40->FUN_0049CAF0(0);
    if (MPGameModeArray.Count == 2) {
        unknown_40->FUN_0049B760(((void**)MPGameModeArray.Items)[0],
                                 ((void**)MPGameModeArray.Items)[1]);
    }
    bool result;
    if (unknown_40) {
        result = true;
    } else {
        result = false;
    }
    return result;
}

// FUNCTION: GAMEMD 0x5C3F80
// Refresh the lobby after a change. On the dialog with id 0x6B, while the
// pending flag at +0x49 is set, drop the last entry of control 0x553 (also
// the one before it when that one is selected) and clear the flag. On any
// other dialog, when the helper is flagged at +0x48, reset it to the
// current position, find the map named after the helper's entry and select
// it, then redraw the dialog. Either way hand the helper its two default
// arguments last. MPCooperative vtable slot 36.
void MPCooperative::vf_36()
{
    if (FUN_00775B20() == 0x6B) {
        if (unknown_49) {
            HWND control = GetDlgItem(FUN_00775B10(), 0x553);
            int last = SendMessageA(control, 0x18B, 0, 0);
            if (last == -1) {
                if (unknown_40 != 0) {
                    unknown_40->FUN_0049B760(DAT_00887734, DAT_00887734);
                }
                return;
            }
            if (SendMessageA(control, 0x188, 0, 0) == last - 1) {
                SendMessageA(control, 0x186, last - 2, 0);
            }
            SendMessageA(control, 0x182, last - 1, 0);
            unknown_49 = false;
        }
    } else {
        if (unknown_40 != 0 && unknown_48) {
            if (unknown_4C != 0) {
                unknown_40->FUN_0049CAF0(0);
                unknown_40->FUN_0049CAF0(unknown_4C);
            } else {
                unknown_40->FUN_0049CAF0(1);
                unknown_40->FUN_0049CAF0(unknown_4C);
            }
            const char* name;
            unknown_40->FUN_0049D070(&name, -1);
            int count = DAT_00A8B8D8;
            char file[0x104];
            sprintf(file, "%s.MAP", name);
            int i = 0;
            for (; i < count; i++) {
                Entry_00A8B8CC* entry = DAT_00A8B8CC[i];
                if (_stricmp(entry->Name, file) == 0) {
                    break;
                }
            }
            DAT_00A8B254 = i;
            MPCoopScenario_00A8B230->unknown_1254 = i;
            FUN_005E7BF0(i);
        }
        HWND dialog = FUN_005E26C0();
        if (dialog != 0) {
            FUN_005E2EF0(dialog, this);
            FUN_005E2F60(dialog);
            FUN_005E74E0(dialog);
        }
        FUN_005E32D0(1, 1);
    }
    if (unknown_40 != 0) {
        unknown_40->FUN_0049B760(DAT_00887734, DAT_00887734);
    }
}

// FUNCTION: GAMEMD 0x5C4110
// Offer the saved campaign map: make sure the helper exists, give it the two
// game modes, run virtual slot 24, and when the helper accepts, on the dialog
// 0x6B (with the offer not yet shown) find the map named `<helper name>.MAP`
// and insert the "use saved game" line for it into control 0x553. On any
// other dialog show the "save campaign available" notice. MPCooperative
// vtable slot 37.
void MPCooperative::vf_37()
{
    if (unknown_40 == 0) {
        unknown_40 = new CoopCampaignClass;
        unknown_40->FUN_0049CAF0(0);
    }
    if (unknown_40 != 0) {
        if (MPGameModeArray.Count == 2) {
            unknown_40->FUN_0049B760(((void**)MPGameModeArray.Items)[0],
                                     ((void**)MPGameModeArray.Items)[1]);
        }
        vf_24();
        if (unknown_40->FUN_0049D120()) {
            if (FUN_00775B20() == 0x6B) {
                if (!unknown_49) {
                    char file[0x104];
                    unknown_40->FUN_0049D390(file);
                    strcat(file, ".MAP");
                    Entry_00A8B8CC* found = 0;
                    int count = DAT_00A8B8D8;
                    for (int i = 0; i < count && found == 0; i++) {
                        Entry_00A8B8CC* entry = DAT_00A8B8CC[i];
                        if (_stricmp(entry->Name, file) == 0) {
                            found = DAT_00A8B8CC[i];
                        }
                    }
                    if (found != 0) {
                        HWND control = GetDlgItem(FUN_00775B10(), 0x553);
                        int last = SendMessageA(control, 0x18B, 0, 0);
                        if (last != -1) {
                            SendMessageA(control, 0x4CD, 0,
                                (LPARAM)StringTable_LoadString("TXT_COOP_USE_SAVE", 0, STR_0082DC4C, 0x77A));
                            SendMessageA(control, 0x19A, last, (LPARAM)found);
                            unknown_49 = true;
                        }
                    }
                }
            } else {
                FUN_005E2700(-1, StringTable_LoadString("TXT_SAVE_CAMP_AVAILABLE", 0, STR_0082DC4C, 0x780));
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C42C0
// Returns a constant. Vtable slot 38 of MPCooperative (RTTI).
int MPCooperative::vf_38()
{
    return 2;
}

// FUNCTION: GAMEMD 0x5C4CA0
// Rebuild the lobby's node vector from this mode's own nodes: for every node
// whose name matches a house, stamp the house index on the node and append a
// fresh copy of it (name, flags, address and the chosen values) to the lobby
// vector, counting each. MPCooperative vtable slot 43.
void MPCooperative::vf_43()
{
    FUN_005C6120(&DAT_00A8DA74);
    DAT_00A8B54C = 0;
    for (int n = 0; n < Nodes.Count; n++) {
        for (int h = 0; h < HouseClass_Array.Count; h++) {
            if (_wcsicmp(HouseClass_Array.Items[h]->UIName, Nodes.Items[n]->Name) == 0) {
                Nodes.Items[n]->unknown_6F = h;
                NodeNameType* copy = new NodeNameType;
                wcscpy(copy->Name, Nodes.Items[n]->Name);
                copy->unknown_7B = Nodes.Items[n]->unknown_7B;
                copy->unknown_4B = Nodes.Items[n]->unknown_4B;
                copy->unknown_53 = Nodes.Items[n]->unknown_53;
                strcpy((char*)copy->unknown_34, (const char*)Nodes.Items[n]->unknown_34);
                copy->unknown_4F = Nodes.Items[n]->unknown_4F;
                copy->unknown_57 = Nodes.Items[n]->unknown_57;
                copy->unknown_6B = Nodes.Items[n]->unknown_6B;
                copy->unknown_73 = Nodes.Items[n]->unknown_73;
                copy->unknown_77 = Nodes.Items[n]->unknown_77;
                copy->unknown_7B = Nodes.Items[n]->unknown_7B;
                NetworkNumberType network;
                NodeAddressType node;
                unsigned short port;
                Nodes.Items[n]->Address.FUN_0053ED60(&network, &node, &port);
                copy->Address.FUN_0053ED20(&network, &node, port);
                DAT_00A8DA74.AddItem(copy);
                DAT_00A8B54C++;
                break;
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4EE0
// Returns a constant boolean. Vtable slot 1 of MPCooperative (RTTI).
bool MPCooperative::vf_1()
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4EF0
// Returns a constant boolean. Vtable slot 2 of MPCooperative (RTTI).
bool MPCooperative::vf_2()
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4F00
// Returns a constant boolean. Vtable slot 47 of MPCooperative (RTTI).
bool MPCooperative::vf_47()
{
    return false;
}

// SYNTHETIC: GAMEMD 0x5C4F10 -- MPCooperative scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89F518
List_0089F518 DAT_0089F518;
// GLOBAL: GAMEMD 0xA8DA74
DynamicVectorClassLayout MPGameModeArray;
// GLOBAL: GAMEMD 0x82DC4C
extern const char STR_0082DC4C[] = "D:\\ra2mdpost\\MPCoop.cpp";
// GLOBAL: GAMEMD 0x82DC64
extern const char STR_0082DC64[] = "NAME:COOPDESC%d%d";
// END defined globals
