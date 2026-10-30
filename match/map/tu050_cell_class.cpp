// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | RE-findings-cross-check
//   Original translation unit TU050 of retail gamemd.exe v1.001 (CellClass); its source-file
//   name is not attested by the binary, so the file keeps a placeholder name. Code range
//   0x47b150-0x4882cf; this file holds the CellClass-owned functions (RTTI class ownership,
//   vtable slots), in ascending retail address order. Other-class rows of the range stay
//   in their own files.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Small leaf helpers; the receivers are per-function placeholder views
//   that name only the fields each body reads.
//
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Round-13 sweep of small members and list walkers between 0x401000 and 0x4A0000.
//
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Small unowned leaves between 0x401000 and 0x540000: accessors, flag setters,
// zeroing initialisers and one-line forwarders. Ordered ascending by retail address.
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
//   owning classes are not named by RTTI at these addresses, so each receiver
//   keeps a placeholder name derived from its address.
//
//   Each body read from the entry-bounded retail function in gamemd.exe v1.001.
//   Owners are placeholders (Obj_<ADDR>) declaring only the fields touched,
//   with offset asserts.
//
//   Each body read from the entry-bounded retail function in gamemd.exe v1.001.
//   Owners are placeholders (Obj_<ADDR>) declaring only the fields touched,
//   with offset asserts.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names.
//
// Small leaves (64 bytes or less) between 0x470000 and 0x500000 that other
// translation units already declared as callees but nothing defined.
//
//   len 0x1F, 0x486770 len 0x1F, 0x486790 len 0x1A).
//
//   GLOBAL:   GAMEMD 0xAA0E28  GgBridgeTileBase
//   GLOBAL:   GAMEMD 0xABAD1C  GgWoodBridgeTileBase
//   GLOBAL:   GAMEMD 0xAA0E24  GgTileBase_00AA0E24
//
// Three half-open iso-tile range tests: a tile set is sixteen consecutive
// iso-tile indices starting at a global the map loader fills in, and the cell
// belongs to the set when its own index falls inside that window. Two of the
// three treat -1 in the base as "this map has no such set".
//
// CellClass fog helper, ordered ascending by retail address.
//
// Retail CellClass slot 18 contains 0x486840; its override keeps the native
// virtual dispatch used by CellClass::vf_22. Entry bytes establish RET 4.
// Signed word reads at this+24/+26 establish the cell coordinate fields;
// the output stores establish CoordStruct's three dwords and hidden result.
//
// CellClass accessors, ordered ascending by retail address.
//
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp.
//
//   GLOBAL:   GAMEMD 0x00A8E9A0 CellOccupiersValid (byte; reloc-normalised)
//
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp.
//
//   GLOBAL:   GAMEMD 0x00A8E9A0 CellOccupiersValid (byte; reloc-normalised)
//
//   Bytes diffed against the user's retail gamemd.exe v1.001; bodies ascending
//   by retail address.
//
//   Names cross-checked against YRpp
//   (every offset/address reconfirmed against the binary).
//
// reccmp annotation:
//   GLOBAL:   GAMEMD 0xA80228   HouseClass::Array (DynamicVectorClass<HouseClass*>)
//   GLOBAL:   GAMEMD 0x87F7E8   the cell -> threat-region lookup object
//
// CellClass tiberium / shroud accessors, ordered ascending by retail address.
//
//   CellClass members between 0x47B3A0 and 0x488280 (the inferred cell translation unit).

#include <stdlib.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Declaration: GAMEMD 0x5F5850 -- one-argument query.
bool __stdcall FUN_005F5850(int a);
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

struct Obj_00487C90
{
    char   unknown_00[0xF0];
    double unknown_F0;     // +0x00F0
    // FUNCTION: GAMEMD 0x487C90
    int FUN_00487C90() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00487C90, unknown_F0) == 0xF0);

// GLOBAL: GAMEMD 0xAA0E18
extern int DAT_00AA0E18;
// GLOBAL: GAMEMD 0xAA0748
extern int DAT_00AA0748;

struct Obj_004867B0
{
    char unknown_00[0x38];
    int  unknown_38;     // +0x0038
    // FUNCTION: GAMEMD 0x4867B0
    bool FUN_004867B0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004867B0, unknown_38) == 0x38);

// Four-byte-stride index into a table of 36-byte records.
struct Rec36_0048B720
{
    int flags;           // +0x00 bit 0: record in use
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
    char unknown_14[4];
    int unknown_18;
    char unknown_1C[4];
    unsigned short unknown_20;
    char unknown_22[2];
};
GG_STATIC_ASSERT(sizeof(Rec36_0048B720) == 0x24);
GG_STATIC_ASSERT(offsetof(Rec36_0048B720, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Rec36_0048B720, unknown_20) == 0x20);

struct Obj_0048B720
{
    char             unknown_00[4];
    int              Count;       // +0x0004
    char             unknown_08[0x24 - 0x08];
    Rec36_0048B720*  Records;     // +0x0024
    int              Used;        // +0x0028
    char             unknown_2C[0x30 - 0x2C];
    int*             Order;       // +0x0030
    // FUNCTION: GAMEMD 0x48B720
    Rec36_0048B720* FUN_0048B720(int position) const;
    // FUNCTION: GAMEMD 0x48B390
    void FUN_0048B390();
};
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Count) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Records) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Used) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Order) == 0x30);

// Same lookup over 24-byte records.
struct Rec24_0048B9E0
{
    int flags;           // +0x00 bit 0: record in use
    char unknown_04[0x14];
};
GG_STATIC_ASSERT(sizeof(Rec24_0048B9E0) == 0x18);

struct Obj_0048B9E0
{
    char             unknown_00[0x34];
    Rec24_0048B9E0*  Records;     // +0x0034
    char             unknown_38[0x40 - 0x38];
    int*             Order;       // +0x0040
    // FUNCTION: GAMEMD 0x48B9E0
    Rec24_0048B9E0* FUN_0048B9E0(int position) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0048B9E0, Records) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_0048B9E0, Order) == 0x40);

// A pair of 16-bit components; 0x4D03D0 compares their magnitudes.
struct Obj_004D03D0
{
    short X;    // +0x0000
    // FUNCTION: GAMEMD 0x4D03D0
    bool FUN_004D03D0(const Obj_004D03D0* other) const;
};

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0748
extern int DAT_00AA0748;
// GLOBAL: GAMEMD 0xAA0E18
extern int DAT_00AA0E18;
// END defined globals

#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../core/intrusive_list_methods.h"
#include "../core/clamped_scale_methods.h"
#include "../core/triple_timer_init_methods.h"
#include "../core/vector_class.h"
#include "../core/vector_class_operations.h"

// ---------------------------------------------------------------------------
// 0x402900 / 0x402BB0 / 0x402C40 - walkers over the pending-node list that hangs
// off the global at 0x815E98 (circular, header at +0xC).
struct QEntry_00402900
{
    char Pad_00[0xC];
    unsigned unknown_0C;
    void (__fastcall *unknown_10)(void* self);
    char Pad_14[4];
    void (__fastcall *unknown_18)(void* self);
};
GG_STATIC_ASSERT(offsetof(QEntry_00402900, unknown_18) == 0x18);

struct QNode_00402900 : ListNode
{
    QEntry_00402900* unknown_0C;
    char             Pad_10[8];
    int              unknown_18;
};
GG_STATIC_ASSERT(offsetof(QNode_00402900, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(QNode_00402900, unknown_18) == 0x18);

// GLOBAL: GAMEMD 0x815E98
extern ListNode* DAT_00815E98;
// GLOBAL: GAMEMD 0x87DE28
extern int DAT_0087DE28;
// GLOBAL: GAMEMD 0x87DE2C
extern int DAT_0087DE2C;
extern "C" void __cdecl FUN_007C8B3D(void* block);
void __fastcall FUN_00407450(ListNode* node);

// ---------------------------------------------------------------------------
// 0x406190 / 0x4062C0 - level setters for the sink group inside Obj_004061D0.
static inline unsigned Clamp_00406190(unsigned level)
{
    unsigned clamped = level;
    if (level > 0x4000)
        clamped = 0x4000;
    else if ((int)level < 0)
        clamped = 0;
    return clamped;
}

// ---------------------------------------------------------------------------
// 0x426E80 - index of the run that contains `pos`, or -1.
struct Run_00426E80
{
    unsigned short unknown_00;
    unsigned short unknown_02;
    unsigned short unknown_04;
};

struct Obj_00426E80
{
    char           Pad_00[0x92];
    unsigned short unknown_92;
    char           Pad_94[0xCC - 0x94];
    int            unknown_CC;
    char           Pad_D0[0x80C - 0xD0];
    Run_00426E80   unknown_80C[1];
    // FUNCTION: GAMEMD 0x426E80
    int FindRun(int pos);
};
GG_STATIC_ASSERT(offsetof(Obj_00426E80, unknown_92) == 0x92);
GG_STATIC_ASSERT(offsetof(Obj_00426E80, unknown_CC) == 0xCC);
GG_STATIC_ASSERT(offsetof(Obj_00426E80, unknown_80C) == 0x80C);

// ---------------------------------------------------------------------------
// 0x4115A0 - scalar deleting destructor.
extern char VTABLE_007E2198[];
struct Obj_004115A0
{
    // FUNCTION: GAMEMD 0x4115A0
    void* Destroy(unsigned char flags);
};

// ---------------------------------------------------------------------------
// 0x42AA40 - facing between two adjacent cells, or 8 when they are not neighbours.
struct Cell_0042AA40
{
    short unknown_00;
    short unknown_02;
};

// GLOBAL: GAMEMD 0x818760
extern int DAT_00818760[9];

// ---------------------------------------------------------------------------
// 0x42EAD0 / 0x42F340 - linear searches over a vector of 16-byte records.
struct Rec_0042EAD0
{
    int            unknown_00;
    unsigned short unknown_04;
    unsigned short unknown_06;
    char           unknown_08;
    char           Pad_09[7];
};

struct Key_0042EAD0
{
    unsigned short unknown_00;
    unsigned short unknown_02;
};

struct Owner_0042F340
{
    char Pad_00[0xDF8];
    int  unknown_DF8;
};
GG_STATIC_ASSERT(offsetof(Owner_0042F340, unknown_DF8) == 0xDF8);

struct Obj_0042EAD0
{
    char          Pad_00[8];
    Rec_0042EAD0* unknown_08;
    char          Pad_0C[8];
    int           unknown_14;
    // FUNCTION: GAMEMD 0x42EAD0
    Rec_0042EAD0* FindByKey(const Key_0042EAD0* key);
    // FUNCTION: GAMEMD 0x42F340
    Rec_0042EAD0* FindFree(const Owner_0042F340* owner);
};
GG_STATIC_ASSERT(offsetof(Obj_0042EAD0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0042EAD0, unknown_14) == 0x14);

// ---------------------------------------------------------------------------
// 0x4129C0 - append every element of row `index` to the collected vector.
struct Obj_004129C0
{
    DynamicVectorClass<int> unknown_0000[400];
    DynamicVectorClass<int> unknown_2580;
    // FUNCTION: GAMEMD 0x4129C0
    void CollectRow(int index);
};
GG_STATIC_ASSERT(offsetof(Obj_004129C0, unknown_2580) == 0x2580);

// ---------------------------------------------------------------------------
// 0x42CF10 - add the ordered pair (smaller in the high half) to row `index`.
struct Obj_0042CF10
{
    char                    Pad_00[0x74];
    DynamicVectorClass<int> unknown_74[1];
    // FUNCTION: GAMEMD 0x42CF10
    void AddPair(unsigned a, unsigned b, int index);
};
GG_STATIC_ASSERT(offsetof(Obj_0042CF10, unknown_74) == 0x74);

// ---------------------------------------------------------------------------
// 0x43A700 - register an item with this owner while there is room.
struct Obj_0043A700;
struct Item_0043A700
{
    char          Pad_00[0x2C];
    Obj_0043A700* unknown_2C;
};
struct Obj_0043A700
{
    char                              Pad_00[4];
    DynamicVectorClass<Item_0043A700*> unknown_04;
    char                              Pad_1C[4];
    int                               unknown_20;
    // FUNCTION: GAMEMD 0x43A700
    bool Register(Item_0043A700* item);
};
GG_STATIC_ASSERT(offsetof(Obj_0043A700, unknown_20) == 0x20);

// ---------------------------------------------------------------------------
// CellClass members. The cell is modelled by a receiver view carrying only the
// fields these bodies touch.
int __fastcall OverlayTypeIndexToTiberium_00483780(int overlayIndex);

struct Tiberium_R13Cell
{
    char   Pad_00[0xA0];
    double unknown_A0;
    char   Pad_A8[8];
    double unknown_B0;
    char   Pad_B8[0xE4 - 0xB8];
    int    unknown_E4;
};
GG_STATIC_ASSERT(offsetof(Tiberium_R13Cell, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Tiberium_R13Cell, unknown_E4) == 0xE4);


// GLOBAL: GAMEMD 0xA8B230
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0xB0F4EC
extern Tiberium_R13Cell** DAT_00B0F4EC;
// GLOBAL: GAMEMD 0x7E3810
extern const double DAT_007E3810;

struct Cell_R13
{
    char          Pad_00[0x44];
    int           unknown_44;
    char          Pad_48[0x50 - 0x48];
    int           unknown_50;
    char          Pad_54[0xE4 - 0x54];
    void*         unknown_E4;
    char          Pad_E8[0x11C - 0xE8];
    unsigned char unknown_11C;
    char          Pad_11D;
    unsigned char unknown_11E;
    char          Pad_11F[0x124 - 0x11F];
    unsigned char unknown_124;
    char          Pad_125[3];
    unsigned char unknown_128;
    char          Pad_129[0x140 - 0x129];
    unsigned int  unknown_140;

    // FUNCTION: GAMEMD 0x4834A0 (decl; reloc)
    bool IsClearToMove(int a, bool b, bool c, int d, int e, int f, bool g);
    // FUNCTION: GAMEMD 0x487190 (decl; reloc)
    bool FUN_00487190(int tiberium, int amount);

    // FUNCTION: GAMEMD 0x483410
    bool FUN_00483410(int value);
    // FUNCTION: GAMEMD 0x483620
    bool FUN_00483620();
    // FUNCTION: GAMEMD 0x483690
    bool FUN_00483690();
    // FUNCTION: GAMEMD 0x483710
    bool FUN_00483710();
};
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_E4) == 0xE4);
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_11C) == 0x11C);
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_11E) == 0x11E);
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_124) == 0x124);
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_128) == 0x128);
GG_STATIC_ASSERT(offsetof(Cell_R13, unknown_140) == 0x140);

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x818760
extern int DAT_00818760[9];
// GLOBAL: GAMEMD 0x87DE28
extern int DAT_0087DE28;
// GLOBAL: GAMEMD 0x7E3810
extern const double DAT_007E3810;
// GLOBAL: GAMEMD 0xB0F4EC
extern Tiberium_R13Cell** DAT_00B0F4EC;
// END defined globals

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A 36-byte element of a pointer-and-count table (Items at +0x00, Count at +0x04).
struct Elem_004011B0
{
    char Data[0x14];
    int  Field14;
    char Rest[0x24 - 0x18];
};
GG_STATIC_ASSERT(sizeof(Elem_004011B0) == 0x24);
GG_STATIC_ASSERT(offsetof(Elem_004011B0, Field14) == 0x14);

struct Table_004011B0
{
    Elem_004011B0* Items;   // +0x00
    int            Count;   // +0x04
};
GG_STATIC_ASSERT(offsetof(Table_004011B0, Count) == 0x04);

// GLOBAL: GAMEMD 0x815E88 -- fallback element returned for an out-of-range index.
extern Elem_004011B0 DAT_00815E88;

struct Obj_004A52E0
{
    char Pad_00[0x18];
    char unknown_18;
    char unknown_19;
    // FUNCTION: GAMEMD 0x4A5110
    bool BothSet();
    // FUNCTION: GAMEMD 0x4A52E0
    void ClearBoth();
};
GG_STATIC_ASSERT(offsetof(Obj_004A52E0, unknown_19) == 0x19);

// Circular list whose sentinel node sits at +0x0C of its owner.
struct ListNode_00401BE0
{
    ListNode_00401BE0* Next;    // +0x00
    char               Pad_04[0x14];
    int                unknown_18;
};
GG_STATIC_ASSERT(offsetof(ListNode_00401BE0, unknown_18) == 0x18);

struct Obj_00401BE0
{
    char               Pad_00[0x0C];
    ListNode_00401BE0  Sentinel;    // +0x0C
    // FUNCTION: GAMEMD 0x401BE0
    void ClearNodeFlags();
};
GG_STATIC_ASSERT(offsetof(Obj_00401BE0, Sentinel) == 0x0C);

struct Block32_004031B0
{
    int Words[8];
};

struct Obj_004031B0
{
    char            Pad_00[0x44];
    Block32_004031B0 unknown_44;
};
GG_STATIC_ASSERT(offsetof(Obj_004031B0, unknown_44) == 0x44);

struct Obj_00426A50
{
    char Pad_00[0xA6];
    char unknown_A6;
    char Pad_A7[0xCC - 0xA7];
    int  unknown_CC;
    // FUNCTION: GAMEMD 0x426A50
    int AdjustedCount();
};
GG_STATIC_ASSERT(offsetof(Obj_00426A50, unknown_CC) == 0xCC);

struct Obj_0042E100
{
    char Pad_00[8];
    int  unknown_08;
    int  unknown_0C;
    // FUNCTION: GAMEMD 0x42E100
    bool IsOver();
};

struct Obj_0042E800
{
    char  Pad_00[8];
    char* unknown_08;
    // FUNCTION: GAMEMD 0x42E800
    char ByteAt(int index);
};

struct Obj_004305E0
{
    char          Pad_00[0x0C];
    unsigned char unknown_0C_0 : 1;
    unsigned char unknown_0C_1 : 1;
    // FUNCTION: GAMEMD 0x4305E0
    void SetFlag1(bool value);
};

struct Obj_00432BF0Inner
{
    char         Pad_00[0x14];
    unsigned int unknown_14;
    unsigned int unknown_18;
};

struct Obj_00432BF0
{
    char               Pad_00[4];
    Obj_00432BF0Inner* unknown_04;
    // FUNCTION: GAMEMD 0x432BF0
    unsigned int PerSecond();
};

struct Obj_004333E0Inner
{
    char Pad_00[0x0C];
    int  unknown_0C;
};

struct Obj_004333E0
{
    char               Pad_00[4];
    Obj_004333E0Inner* unknown_04;
    char               Pad_08[0x24 - 0x08];
    int                unknown_24;
    // FUNCTION: GAMEMD 0x4333E0
    int Product();
};
GG_STATIC_ASSERT(offsetof(Obj_004333E0, unknown_24) == 0x24);

struct Obj_00487110
{
    char Pad_00[0x78];
    unsigned int unknown_78;
    // FUNCTION: GAMEMD 0x487110
    void SetBit(int bit);
};

struct Obj_00487C80
{
    char Pad_00[0xF8];
    int  unknown_F8;
    // FUNCTION: GAMEMD 0x487C80
    int Get_F8();
};

struct Obj_00487D50
{
    char         Pad_00[0x11B];
    signed char  unknown_11B;
    char         Pad_11C[0x140 - 0x11C];
    unsigned int unknown_140;
    // FUNCTION: GAMEMD 0x487D50
    int Combined();
};
GG_STATIC_ASSERT(offsetof(Obj_00487D50, unknown_140) == 0x140);

struct Obj_00430910
{
    char Block[0x60];   // +0x00
    int  unknown_60;
    char Pad_64[0x7C - 0x64];
    int  unknown_7C;
    // FUNCTION: GAMEMD 0x430910
    Obj_00430910* Clear();
};
GG_STATIC_ASSERT(offsetof(Obj_00430910, unknown_7C) == 0x7C);

struct Obj_00479710
{
    int Words[0x1A];
    // FUNCTION: GAMEMD 0x479710
    Obj_00479710* Clear();
};

struct Obj_004A2350
{
    int  unknown_00;
    int  unknown_04;
    char unknown_08;
    char unknown_09;
    char unknown_0A;
    int  unknown_0C;
    // FUNCTION: GAMEMD 0x4A2350
    Obj_004A2350* Reset();
};
GG_STATIC_ASSERT(offsetof(Obj_004A2350, unknown_0C) == 0x0C);

struct Obj_004B9BD0
{
    char unknown_00;
    char unknown_01;
    char unknown_02;
    // FUNCTION: GAMEMD 0x4B9BD0
    Obj_004B9BD0* Reset();
};

struct Obj_004AEB10
{
    char          Pad_00[0x119C];
    char          unknown_119C;
    char          Pad_119D[3];
    void*         unknown_11A0;
    // FUNCTION: GAMEMD 0x4AEB10
    void* Selected();
};
GG_STATIC_ASSERT(offsetof(Obj_004AEB10, unknown_11A0) == 0x11A0);

struct Obj_004C3CE0
{
    char Pad_00[8];
    int  unknown_08;
    // FUNCTION: GAMEMD 0x4C3CE0
    bool Subtract(int amount);
};

struct Obj_004F3AB0
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5(char value);  // slot 5
    char Pad_04[5];
    char unknown_09;
    // FUNCTION: GAMEMD 0x4F3AB0
    void Set(char value);
};
GG_STATIC_ASSERT(offsetof(Obj_004F3AB0, unknown_09) == 0x09);

// FUNCTION: GAMEMD 0x55ABB0 (decl; reloc) -- stdcall member taking its object as the only argument.
int __stdcall FUN_0055ABB0(void* self);

// A pair of ints ordered by the comparator at 0x4A48C0.
struct IntPair_004A48C0
{
    int First;
    int Second;
};

// One 32-byte record of the table at 0x4A35F0 (only the fields it writes are named).
struct Entry_004A35F0
{
    int   unknown_00;
    int   unknown_04;
    int   unknown_08;
    float One;          // +0x0C
    int   unknown_10[2];
    int   unknown_18;
    int   unknown_1C;

    // FUNCTION: GAMEMD 0x4A35F0
    void FUN_004A35F0(int index, int a, int b, int c, int d, int e);
};
GG_STATIC_ASSERT(sizeof(Entry_004A35F0) == 0x20);
GG_STATIC_ASSERT(offsetof(Entry_004A35F0, One) == 0x0C);
GG_STATIC_ASSERT(offsetof(Entry_004A35F0, unknown_18) == 0x18);

// An object owned through the global pointer at 0xA9FA9C; only its virtual destructor is used.
struct Obj_00A9FA9C
{
    virtual ~Obj_00A9FA9C() {}
};
// GLOBAL: GAMEMD 0xA9FA9C
extern Obj_00A9FA9C* DAT_00A9FA9C;

// A six-byte value copied as a dword and a word.
struct Bytes6_0053EDC0
{
    unsigned char Bytes[6];
};

struct Obj_0053EDC0
{
    char           Pad_00[4];
    Bytes6_0053EDC0 unknown_04;
    // FUNCTION: GAMEMD 0x53EDC0
    void Get(Bytes6_0053EDC0* out);
    // FUNCTION: GAMEMD 0x53EDE0
    void Set(const Bytes6_0053EDC0* in);
};

// GLOBAL: GAMEMD 0x828140
extern int DAT_00828140;

struct Obj_0053F200
{
    short unknown_00;
    // FUNCTION: GAMEMD 0x53F200
    void SetIfMode2(short value);
};

struct Obj_00424CB0
{
    char Pad_00[0xC8];
    char* unknown_C8;
    int   unknown_CC;
    // FUNCTION: GAMEMD 0x424CB0
    int Kind();
};
GG_STATIC_ASSERT(offsetof(Obj_00424CB0, unknown_CC) == 0xCC);

struct Obj_00465930Item
{
    char Pad_00[0xEE4];
    int  unknown_EE4;
};
GG_STATIC_ASSERT(offsetof(Obj_00465930Item, unknown_EE4) == 0xEE4);

struct Obj_00465930
{
    void*             Vtbl;
    Obj_00465930Item** Items;       // +0x04
    char              Pad_08[8];
    int               Count;        // +0x10
    // FUNCTION: GAMEMD 0x465930
    int MaxValue();
};
GG_STATIC_ASSERT(offsetof(Obj_00465930, Count) == 0x10);

struct Obj_00487130
{
    char         Pad_00[0x78];
    unsigned int unknown_78;
    // FUNCTION: GAMEMD 0x487130
    void ClearBit(int bit);
};

struct Obj_0049FB40
{
    void* Vtbl;
    int*  Items;        // +0x04
    int   Capacity;     // +0x08
    char  Pad_0C[4];
    int   Count;        // +0x10
    // FUNCTION: GAMEMD 0x49FB40
    void ZeroAndEmpty();
};
GG_STATIC_ASSERT(offsetof(Obj_0049FB40, Count) == 0x10);

struct Pair_0049FF40
{
    int First;      // +0x00
    int Second;     // +0x04
};

struct Obj_004C9680
{
    char  Pad_00[0x14];
    short unknown_14;
    // FUNCTION: GAMEMD 0x4C9680
    void SetHigh(int value);
};

struct Obj_004E0080
{
    char Pad_00[0x68F];
    char unknown_68F;
    char unknown_690;
    char unknown_691;
    // FUNCTION: GAMEMD 0x4E0080
    int AnySet();
};
GG_STATIC_ASSERT(offsetof(Obj_004E0080, unknown_691) == 0x691);

struct Obj_0048BAD0
{
    char Pad_00[0x44];
    int  unknown_44;
    int  unknown_48;
    int  unknown_4C;
    int  unknown_50;
    int  unknown_54;
    // FUNCTION: GAMEMD 0x48BAD0
    void Set(int a, int b, int c, int d, int e);
};
GG_STATIC_ASSERT(offsetof(Obj_0048BAD0, unknown_54) == 0x54);

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA9FA9C
extern Obj_00A9FA9C* DAT_00A9FA9C;
// GLOBAL: GAMEMD 0x828140
extern int DAT_00828140;
// END defined globals

#include "../core/leftover_trivial_leaf_sweep.h"

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x829FF4
extern int DAT_00829FF4;
// GLOBAL: GAMEMD 0x829FF8
extern int DAT_00829FF8;
// END defined globals

#include "../core/member_setter_family_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../renderer/surface_class.h"
#include "../_layout/color_convert.h"

// ---------------------------------------------------------------------------
// 0x42E150: a rectangle with a palette colour, drawn as an outline.
struct Box_0042E150
{
    RectangleStruct Rect;          // +0x0000
    char            _pad010[0x8];  // +0x0010
    int             ColorIndex;    // +0x0018

    void FUN_0042E150();
};
GG_STATIC_ASSERT(offsetof(Box_0042E150, ColorIndex) == 0x18);

// GLOBAL: GAMEMD 0x87F6C4 -- the palette-to-pixel lookup.
extern ColorConvert* DAT_0087F6C4;
// GLOBAL: GAMEMD 0x887314 -- DSurface::Temp.
extern Surface* DAT_00887314;

// ---------------------------------------------------------------------------
// 0x486E30: a cell's veinhole check. The coordinate pair sits at +0x24.
struct Coord_00486E30 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Coord_00486E30) == 4);

struct Cell_00486E30;

// The veinhole monster found for a coordinate (receiver of the 0x74EF10 handler).
struct Vein_00486E30
{
    // FUNCTION: GAMEMD 0x74EF10 (decl; reloc) -- react to the cell.
    void FUN_0074EF10(Cell_00486E30* cell);
};

// The cell a map lookup returns (receiver of the 0x485590 handler).
struct CellRef_00486E30
{
    // FUNCTION: GAMEMD 0x485590 (decl; reloc) -- react to the cell.
    void FUN_00485590();
};

struct Map_00486E30
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- MapClass::GetCellAt.
    CellRef_00486E30* GetCellAt(const Coord_00486E30* coord);
};

// GLOBAL: GAMEMD 0x87F7E8 -- the map object (used by address, ECX).
extern Map_00486E30 DAT_0087F7E8_00486E30;

// FUNCTION: GAMEMD 0x74CDB0 (decl; reloc) -- the veinhole monster covering a coordinate, or 0.
Vein_00486E30* FUN_0074CDB0(const Coord_00486E30* coord);

struct Cell_00486E30
{
    char           _pad000[0x24];  // +0x0000
    Coord_00486E30 MapCoords;      // +0x0024

    int FUN_00486E30();
};
GG_STATIC_ASSERT(offsetof(Cell_00486E30, MapCoords) == 0x24);

// ---------------------------------------------------------------------------
// 0x488210: a toggle-style gadget press handler (the +0x2D byte is the on flag).
struct Obj_00488210
{
    char          _pad000[0x2D];   // +0x0000
    unsigned char IsOn;            // +0x002D

    // FUNCTION: GAMEMD 0x723EA0 (decl; reloc) -- turn on.
    void FUN_00723EA0();
    // FUNCTION: GAMEMD 0x723EB0 (decl; reloc) -- turn off.
    void FUN_00723EB0();
    // FUNCTION: GAMEMD 0x723EC0 (decl; reloc) -- the action handler.
    int FUN_00723EC0(unsigned flags, int key, int modifier);

    void FUN_00488210(unsigned flags, int key, int unused);
};
GG_STATIC_ASSERT(offsetof(Obj_00488210, IsOn) == 0x2D);

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F6C4
extern ColorConvert* DAT_0087F6C4;
// END defined globals

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Two parallel 24-entry word tables at +0x7C and +0xAC; each accessor tests
// whether an entry is positive.
struct Obj_004870D0
{
    char unknown_00[0x7C];
    short unknown_7C[0x18];   // +0x007C
    short unknown_AC[0x18];   // +0x00AC
    // FUNCTION: GAMEMD 0x4870D0
    bool FUN_004870D0(int index) const;
    // FUNCTION: GAMEMD 0x4870F0
    bool FUN_004870F0(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_004870D0, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Obj_004870D0, unknown_AC) == 0xAC);

struct Obj_004A52D0
{
    char unknown_00[0x18];
    bool unknown_18;   // +0x0018
    bool unknown_19;   // +0x0019
    // FUNCTION: GAMEMD 0x4A52D0
    void FUN_004A52D0();
};
GG_STATIC_ASSERT(offsetof(Obj_004A52D0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_004A52D0, unknown_19) == 0x19);

struct Obj_004B6BE0
{
    char unknown_00[0x14];
    int unknown_14[1];   // +0x0014 (open-ended table)
    // FUNCTION: GAMEMD 0x4B6BE0
    int FUN_004B6BE0(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_004B6BE0, unknown_14) == 0x14);

// Two key members at +0x4C and +0x50, each set through the key's assignment
// operator (0x7B4940, defined out of line).
struct Key_007B4940
{
    int Data;   // +0x00
    // FUNCTION: GAMEMD 0x7B4940 (decl; reloc)
    Key_007B4940& operator=(const Key_007B4940& other);
};

struct Obj_004F2680
{
    char unknown_00[0x4C];
    Key_007B4940 unknown_4C;   // +0x004C
    Key_007B4940 unknown_50;   // +0x0050
    // FUNCTION: GAMEMD 0x4F2680
    void FUN_004F2680(const Key_007B4940& key);
    // FUNCTION: GAMEMD 0x4F2800
    void FUN_004F2800(const Key_007B4940& key);
};
GG_STATIC_ASSERT(offsetof(Obj_004F2680, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_004F2680, unknown_50) == 0x50);

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/header_init_shapes.h"
#include "../_layout/fogged_object_class.h"

// A circular list whose sentinel sits at +0x0C; each node holds a key at +0x14
// and a payload pointer at +0x18.
struct Node_00401BB0
{
    Node_00401BB0* Next;   // +0x00
    char unknown_04[0x10];
    int Key;               // +0x14
    void* Payload;         // +0x18
};
struct Obj_00401BB0
{
    char unknown_00[0x0C];
    Node_00401BB0 Sentinel;   // +0x000C
    // FUNCTION: GAMEMD 0x401BB0
    Node_00401BB0* __fastcall FUN_00401BB0(int key);
};
GG_STATIC_ASSERT(offsetof(Node_00401BB0, Key) == 0x14);
GG_STATIC_ASSERT(offsetof(Node_00401BB0, Payload) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_00401BB0, Sentinel) == 0x0C);

// GLOBAL: GAMEMD 0x87E2A0 -- selects whether the per-object table is consulted.
extern int DAT_0087E2A0;
// GLOBAL: GAMEMD 0x816204 -- fallback record when the selector is clear.
extern char DAT_00816204[];
// GLOBAL: GAMEMD 0x816210 -- fallback record when the object has no table.
extern char DAT_00816210[];

struct Obj_00406340
{
    char unknown_00[0x24];
    char* unknown_24;   // +0x0024
    // FUNCTION: GAMEMD 0x406340
    char* FUN_00406340();
};
GG_STATIC_ASSERT(offsetof(Obj_00406340, unknown_24) == 0x24);

// An eight-byte key: a dword and two words.
struct Key_0042E640
{
    unsigned long unknown_00;    // +0x0000
    unsigned short unknown_04;   // +0x0004
    unsigned short unknown_06;   // +0x0006
    // FUNCTION: GAMEMD 0x42E640
    bool operator==(const Key_0042E640& other) const;
    // FUNCTION: GAMEMD 0x42E670
    bool operator!=(const Key_0042E640& other) const;
    // The equality test as retail inlines it into the inequality.
    int Same(const Key_0042E640& other) const
    {
        if (unknown_00 == other.unknown_00 && unknown_04 == other.unknown_04
            && unknown_06 == other.unknown_06) {
            return 1;
        }
        return 0;
    }
};
GG_STATIC_ASSERT(offsetof(Key_0042E640, unknown_06) == 0x06);
GG_STATIC_ASSERT(sizeof(Key_0042E640) == 8);

// A bit stream cursor: byte pointer at +0x00, bit index at +0x04.
struct Obj_00433570
{
    unsigned char* unknown_00;   // +0x0000
    unsigned char unknown_04;    // +0x0004
    // FUNCTION: GAMEMD 0x433570
    bool FUN_00433570();
    // FUNCTION: GAMEMD 0x4335B0
    void __fastcall FUN_004335B0(unsigned char bit);
};
GG_STATIC_ASSERT(offsetof(Obj_00433570, unknown_04) == 4);

// Window starts held in globals; an object's value at +0x38 is tested against
// short runs beginning at each.
// GLOBAL: GAMEMD 0xABC1D8
extern int DAT_00ABC1D8;
// GLOBAL: GAMEMD 0xAA1058
extern int DAT_00AA1058;

struct Obj_004863A0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4863A0
    bool FUN_004863A0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004863A0, unknown_38) == 0x38);

// Run starts held in globals for the two range tests below.
// GLOBAL: GAMEMD 0xABAD20
extern int DAT_00ABAD20;
// GLOBAL: GAMEMD 0xABC1D4
extern int DAT_00ABC1D4;
// GLOBAL: GAMEMD 0xAA10AC
extern int DAT_00AA10AC;
// GLOBAL: GAMEMD 0xABAD28
extern int DAT_00ABAD28;
// GLOBAL: GAMEMD 0xAA0738
extern int DAT_00AA0738;
// GLOBAL: GAMEMD 0xAA073C
extern int DAT_00AA073C;
// GLOBAL: GAMEMD 0xABB110
extern int DAT_00ABB110;
// GLOBAL: GAMEMD 0xAA1050
extern int DAT_00AA1050;
// GLOBAL: GAMEMD 0xAA10A0
extern int DAT_00AA10A0;

struct Obj_004865D0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4865D0
    bool FUN_004865D0() const;
    // FUNCTION: GAMEMD 0x486690
    bool FUN_00486690() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004865D0, unknown_38) == 0x38);

// Four counters at +0x14..+0x20.
struct Obj_0048BAA0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    int unknown_18;   // +0x0018
    int unknown_1C;   // +0x001C
    int unknown_20;   // +0x0020
    // FUNCTION: GAMEMD 0x48BAA0
    void FUN_0048BAA0(bool clear);
};
GG_STATIC_ASSERT(offsetof(Obj_0048BAA0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0048BAA0, unknown_20) == 0x20);

// Three colour slots (+0x10, +0x30, +0x50) each followed by an opaque alpha word.
struct Obj_004A35A0
{
    char unknown_00[0x10];
    unsigned long unknown_10;   // +0x0010
    unsigned long unknown_14;   // +0x0014
    char unknown_18[0x18];
    unsigned long unknown_30;   // +0x0030
    unsigned long unknown_34;   // +0x0034
    char unknown_38[0x18];
    unsigned long unknown_50;   // +0x0050
    unsigned long unknown_54;   // +0x0054
    // FUNCTION: GAMEMD 0x4A35A0
    void FUN_004A35A0(unsigned long r, unsigned long g, unsigned long b);
};
GG_STATIC_ASSERT(offsetof(Obj_004A35A0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_004A35A0, unknown_54) == 0x54);

// GLOBAL: GAMEMD 0xA8ED84 -- the frame counter.
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x8209D8 -- the frame the counter below last ran in.
extern int DAT_008209D8;
// GLOBAL: GAMEMD 0x8A39FC -- per-frame call counter.
extern unsigned char DAT_008A39FC;

struct Obj_004C6570
{
    // FUNCTION: GAMEMD 0x4C6570
    unsigned char FUN_004C6570();
};

// Five dwords of the map-math header group (a count at 0xABC554 and a four-int
// block at 0xAA1060) cleared in one go.
// GLOBAL: GAMEMD 0xABC554
extern int DAT_00ABC554;
// GLOBAL: GAMEMD 0xAA1060
extern int DAT_00AA1060;
// GLOBAL: GAMEMD 0xAA1064
extern int DAT_00AA1064;
// GLOBAL: GAMEMD 0xAA1068
extern int DAT_00AA1068;
// GLOBAL: GAMEMD 0xAA106C
extern int DAT_00AA106C;

// A chained record: the next link is at +0x2BC, a table of short-pair pointers at +0x2A8,
// a link count at +0x2F0 and a cleared slot at +0x308.
struct Obj_00544E00
{
    char unknown_00[0x2A8];
    short** unknown_2A8;        // +0x02A8
    char unknown_2AC[0x10];
    Obj_00544E00* unknown_2BC;  // +0x02BC
    char unknown_2C0[0x8];
    int unknown_2C8;            // +0x02C8
    char unknown_2CC[0x24];
    int unknown_2F0;            // +0x02F0
    char unknown_2F4[0x14];
    int unknown_308;            // +0x0308
    // FUNCTION: GAMEMD 0x544E00
    Obj_00544E00* FUN_00544E00(int steps);
    // FUNCTION: GAMEMD 0x549DD0
    void FUN_00549DD0(int link, int unused);
    // FUNCTION: GAMEMD 0x549E20
    short FUN_00549E20(int row, int column, bool flag);
};
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2A8) == 0x2A8);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2C8) == 0x2C8);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2F0) == 0x2F0);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_308) == 0x308);

// GLOBAL: GAMEMD 0x8B4154 -- table of link objects.
extern int* DAT_008B4154;

// GLOBAL: GAMEMD 0xA8F2CC
extern int DAT_00A8F2CC;

struct Obj_00524760
{
    // FUNCTION: GAMEMD 0x524760
    CoordStruct FUN_00524760();
};

// GLOBAL: GAMEMD 0xA8ED38 -- number of chain heads.
extern int DAT_00A8ED38;
// GLOBAL: GAMEMD 0xA8ED2C -- the chain heads.
extern Obj_00544E00** DAT_00A8ED2C;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A39FC
extern unsigned char DAT_008A39FC;
// GLOBAL: GAMEMD 0xA8ED2C
extern Obj_00544E00** DAT_00A8ED2C;
// GLOBAL: GAMEMD 0xA8ED38
extern int DAT_00A8ED38;
// GLOBAL: GAMEMD 0xAA0738
extern int DAT_00AA0738;
// GLOBAL: GAMEMD 0xAA073C
extern int DAT_00AA073C;
// GLOBAL: GAMEMD 0xAA1050
extern int DAT_00AA1050;
// GLOBAL: GAMEMD 0xAA1058
extern int DAT_00AA1058;
// GLOBAL: GAMEMD 0xAA1060
extern int DAT_00AA1060;
// GLOBAL: GAMEMD 0xAA1064
extern int DAT_00AA1064;
// GLOBAL: GAMEMD 0xAA1068
extern int DAT_00AA1068;
// GLOBAL: GAMEMD 0xAA106C
extern int DAT_00AA106C;
// GLOBAL: GAMEMD 0xAA10A0
extern int DAT_00AA10A0;
// GLOBAL: GAMEMD 0xAA10AC
extern int DAT_00AA10AC;
// GLOBAL: GAMEMD 0xABAD20
extern int DAT_00ABAD20;
// GLOBAL: GAMEMD 0xABAD28
extern int DAT_00ABAD28;
// GLOBAL: GAMEMD 0xABB110
extern int DAT_00ABB110;
// GLOBAL: GAMEMD 0xABC1D4
extern int DAT_00ABC1D4;
// GLOBAL: GAMEMD 0xABC1D8
extern int DAT_00ABC1D8;
// GLOBAL: GAMEMD 0xABC554
extern int DAT_00ABC554;
// GLOBAL: GAMEMD 0x8209D8
extern int DAT_008209D8;
// GLOBAL: GAMEMD 0x87E2A0
extern int DAT_0087E2A0;
// END defined globals

#include "../_layout/bullet_class.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" size_t __cdecl strlen(const char* s);
#pragma intrinsic(strlen)

// GLOBAL: GAMEMD 0x00A8ED84
extern "C" int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x00AA0738
extern "C" int DAT_00AA0738;
// GLOBAL: GAMEMD 0x007E1B60 (five string pointers)
extern "C" const char* const DAT_007E1B60[5];
// GLOBAL: GAMEMD 0x007E523C (nineteen string pointers)
extern "C" const char* const DAT_007E523C[19];
// GLOBAL: GAMEMD 0x0081DA28 (twelve string pointers)
extern "C" const char* const DAT_0081DA28[12];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

// 0x4CAC40: x87 helper taking one double and returning one (callee only).
double __cdecl FUN_004CAC40(double value);
// 0x5117D0: name -> index, -1 when absent (callee only).
int FUN_005117D0(const char* name);

// ---------------------------------------------------------------------------

#include "../_layout/obj_00483460.h"

#include "../_layout/obj_00485060.h"

#include "../_layout/obj_004870b0.h"

#include "../_layout/geometry2d.h"

#include "../_layout/obj_0048ba80.h"

#include "../_layout/obj_004a1d30.h"

#include "../_layout/obj_004a50f0.h"

#include "../_layout/pair_004c1b50.h"


#include "../_layout/obj_004c91c0.h"

#include "../_layout/obj_004ca160.h"

// GLOBAL: GAMEMD 0x0085D0A4 (4096-entry float table)
extern "C" const float DAT_0085D0A4[4096];

struct Obj_004D2790;

struct Vtbl_004D2790;

#include "../_layout/obj_004d2790.h"


#include "../_layout/vtbl_004d2790.h"

#include "../_layout/record_004d2790.h"

// 0x7C5F3D and 0x7C5FFF: runtime-library helpers with no binary name; the
// first returns a byte (callees only).
extern "C" char __cdecl FUN_007C5F3D();
extern "C" void __cdecl FUN_007C5FFF();
extern "C" char* __cdecl strncpy(char* dst, const char* src, size_t count);

// GLOBAL: GAMEMD 0x0084E863
extern "C" signed char DAT_0084E863;
// GLOBAL: GAMEMD 0x0084E865
extern "C" const char DAT_0084E865[];


extern "C" char* __cdecl strcpy(char* dst, const char* src);
#pragma intrinsic(strcpy)
extern "C" char* __cdecl _strupr(char* text);

#include "../_layout/text_004f4cb0.h"

#include "../_layout/obj_004f4c20.h"

#include <new.h>
#include "cell_class_activate_veins_methods.h"

#include "cell_class_bridge_tile_queries.h"

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0E24
int GgTileBase_00AA0E24;
// GLOBAL: GAMEMD 0xAA0E28
int GgBridgeTileBase;
// GLOBAL: GAMEMD 0xABAD1C
int GgWoodBridgeTileBase;
// END defined globals

#include "cell_class_fog_cell_methods.h"

// The retail MapClass singleton lives at this fixed address.
#define FogMapInstance (reinterpret_cast<MapClass_00486A70*>(0x87F7E8))

#include "cell_class_fog_methods.h"

// The retail MapClass singleton lives at this fixed address; calling through it
// makes cl emit `mov ecx,0x87F7E8` exactly as retail does.
#define MapInstance (reinterpret_cast<MapView_5657A0_2*>(0x87F7E8))

#include "../core/vector_class_operations.h"
#include "../_layout/cell_class.h"
#include "../_layout/geometry2d.h"
#include "cell_flag_search_shared.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/stream_persist_methods.h"
#include <new.h>

namespace CellLoadABIAssertions {
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(FoggedObjectClass*) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->MapCoords) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->IsoTileTypeIndex) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FoggedObjects) == 4);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<FoggedObjectClass*>) == 0x18);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->Capacity) == 4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->IsInitialized) == 1);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->IsAllocated) == 1);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->Items) == 4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->Count) == 4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->CapacityIncrement) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->BridgeOwnerCell) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->unknown_30) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->LightConvert) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->Passability) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->PixelFX) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->OverlayTypeIndex) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->OverlayData) == 1);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->AttachedTag) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->Jumpjet) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FirstObject) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->AltObject) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->RadSite) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->Rubble) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->MapCoords.X) == 2);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->MapCoords.Y) == 2);
}

// CellClass::Save calls the native base-save helper at 0x00410320 (__stdcall).
extern "C" HRESULT __stdcall FUN_00410320(void* subject, void* stream,
                                          int clearDirty);
// GLOBAL: GAMEMD 0x0089E7B4
extern int DAT_0089E7B4;
// GLOBAL: GAMEMD 0x00AA0738
extern int DAT_00AA0738;

#include "cell_class_methods.h"

#include "cell_class_nearest_techno_methods.h"

#include "cell_class_occupier_methods.h"

// AbstractType discriminants returned by WhatAmI() (YRpp).
#define ABS_UNIT     0x01  // CMP EAX,0x01
#define ABS_AIRCRAFT 0x02  // CMP EAX,0x02
#define ABS_INFANTRY 0x0F  // CMP EAX,0x0F

// Read the occupier's WhatAmI() through its primary vtable slot +0x2C.
// `MOV EAX,[obj]; MOV ECX,obj; CALL [EAX+0x2C]`.
#define WHAT_AM_I(obj) ((*(WhatAmIFunc*)(*(char**)(obj) + 0x2c))(obj))

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8E9A0
unsigned char CellOccupiersValid;
// END defined globals

#include "cell_class_query_methods.h"

// AbstractType discriminants returned by WhatAmI() (YRpp).
#define ABS_BUILDING 6     // CMP EAX,0x06
#define ABS_TERRAIN  0x24  // CMP EAX,0x24

// Read the occupier's WhatAmI() through its primary vtable slot +0x2C.
// `MOV EAX,[obj]; MOV ECX,obj; CALL [EAX+0x2C]`.
#define WHAT_AM_I(obj) ((*(WhatAmIFunc*)(*(char**)(obj) + 0x2c))(obj))

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8B413C
TunnelClass** TunnelArrayItems;
// GLOBAL: GAMEMD 0x8B4148
int TunnelArrayCount;
// END defined globals

#include "cell_class_remove_content_methods.h"

// AbstractType discriminants returned by WhatAmI().
#define ABS_BUILDING 6      // CMP EAX,0x06
#define ABS_INFANTRY 0xF    // CMP EAX,0x0F

#define VTBL(obj) (*(Vtbl_0047EA90**)(obj))

#include "cell_class_sensor_methods.h"

#include "cell_class_spread_tiberium_methods.h"

#include "cell_class_threat_methods.h"

// ---------------------------------------------------------------------------
// Offset-pinned model of the global HouseClass::Array (DynamicVectorClass head).
// Confirmed from 0x481870: `MOV EDX,[0xA8022C]` == &Array.Items (Array @0xA80228,
// Items @+0x04) and `MOV EAX,[0xA80238]` == Array.Count (@+0x10).
// ---------------------------------------------------------------------------
struct DynamicVectorClass_HousePtr
{
    void*        vtable;             // +0x00
    HouseClass** Items;             // +0x04
    int          Capacity;          // +0x08
    int          IsAllocated;       // +0x0C
    int          Count;             // +0x10
    int          CapacityIncrement; // +0x14
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_HousePtr, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_HousePtr, Count) == 0x10);
#endif

// GLOBAL: GAMEMD 0xA80228 — the engine's global array of all houses.
extern DynamicVectorClass_HousePtr HouseArray;
// GLOBAL: GAMEMD 0x87F7E8 — cell-coordinate -> threat-region lookup.
extern RegionLookupClass RegionLookup;

#include "cell_class_tiberium_germinate_methods.h"

// First building / terrain object occupying the cell, or null. Both walks are
// gated by the IsActive byte and are inlined by retail (WhatAmI == 6 for a
// building, 0x24 for a terrain object); the not-found exit of each walk is
// threaded straight past the caller's null test.
inline Obj_004838E0* Cell_004838E0::GetBuilding() const
{
    if (DAT_00A8E9A0) {
        for (Obj_004838E0* obj = this->FirstObject; obj; obj = obj->NextObject) {
            if ((obj->*obj->Vtbl->WhatAmI)() == 6) {
                return obj;
            }
        }
    }
    return 0;
}

inline Obj_004838E0* Cell_004838E0::GetTerrain() const
{
    if (DAT_00A8E9A0) {
        for (Obj_004838E0* obj = this->FirstObject; obj; obj = obj->NextObject) {
            if ((obj->*obj->Vtbl->WhatAmI)() == 0x24) {
                return obj;
            }
        }
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8ED28
IsoTileVector_004838E0 IsoTileArray_004838E0;
// END defined globals

#include "cell_class_tiberium_methods.h"

#include "../core/vector_class_operations.h"
#include "../_layout/cell_class.h"
#include "../_layout/light_convert_class.h"
#include "../_layout/pixel_fx_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/fogged_object_class.h"

// GLOBAL: GAMEMD 0x886FA4
extern int DAT_00886FA4;

// FUNCTION: GAMEMD 0x5FDCC0 (decl; reloc) -- overlay type draw offset, written through `out`.
Point2D* __fastcall FUN_005FDCC0(Point2D* out, int typeIndex);

// GLOBAL: GAMEMD 0xAA1020
extern int DAT_00AA1020;
// GLOBAL: GAMEMD 0xAA073C
extern int DAT_00AA073C;
// GLOBAL: GAMEMD 0xABB110
extern int DAT_00ABB110;
// GLOBAL: GAMEMD 0xAA1050
extern int DAT_00AA1050;
// GLOBAL: GAMEMD 0xAA10A0
extern int DAT_00AA10A0;
// GLOBAL: GAMEMD 0xABBEBC
extern int DAT_00ABBEBC;
// GLOBAL: GAMEMD 0xABAD24
extern int DAT_00ABAD24;
// GLOBAL: GAMEMD 0xAA0E28
extern int DAT_00AA0E28;
// GLOBAL: GAMEMD 0xABAD1C
extern int DAT_00ABAD1C;
// GLOBAL: GAMEMD 0xABC2C8
extern int DAT_00ABC2C8;
// GLOBAL: GAMEMD 0xAA101C
extern int DAT_00AA101C;
// GLOBAL: GAMEMD 0x880944
extern DynamicVectorClass<CellStruct> DAT_00880944;
// GLOBAL: GAMEMD 0xA8E9A0
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0x89E748
extern CellStruct DAT_0089E748;

#include "cell_class_wall_owner_methods.h"

#include "trivial_tu050_methods.h"

// AdjacentCell[FacingType] -- the static {dX,dY} step table at 0x89F688.
// Referenced by absolute address so cl emits the same displacement retail does.
#define AdjacentCell (reinterpret_cast<CellStruct const*>(0x89F688))

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0E20
int DAT_00AA0E20;
// GLOBAL: GAMEMD 0xAA1094
int DAT_00AA1094;
// GLOBAL: GAMEMD 0xAA10A4
int DAT_00AA10A4;
// GLOBAL: GAMEMD 0xABBEC4
int DAT_00ABBEC4;
// GLOBAL: GAMEMD 0xABBEC8
int DAT_00ABBEC8;
// GLOBAL: GAMEMD 0xABC2B0
int DAT_00ABC2B0;
// GLOBAL: GAMEMD 0xABC2C8
int DAT_00ABC2C8;
// END defined globals

// FUNCTION: GAMEMD 0x47B360
CellClass::CellClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), LightConvert(0), Passability(0)
{
}

// FUNCTION: GAMEMD 0x47BB60
CellClass::~CellClass()
{
    if (FoggedObjects != 0) {
        delete FoggedObjects;
        FoggedObjects = 0;
    }
    if (PixelFX != 0) {
        delete PixelFX;
        PixelFX = 0;
    }
    FirstObject = 0;
    if (MapCoords != DAT_0089E748 && LightConvert != 0) {
        if (DAT_00A8E9A0 != 0)
            LightConvert->unknown_194--;
        LightConvert = 0;
    }
}

// FUNCTION: GAMEMD 0x47C3D0
//
// Nearest techno in this cell's occupier list (ground or bridge) to a pixel
// offset inside the cell, skipping one object. The offset is scaled by seven
// up front; each candidate's sub-cell lepton position (low byte of X and Y)
// is measured against it in double precision and truncated.
//
// Four phrasings are load-bearing. The head pointer is a separate variable
// from the loop cursor and the null test on the cursor sits inside the loop
// (retail re-tests it and jumps to the increment); the techno flag is a
// function-scope bool assigned in its own block and tested in the next, which
// is what stores it to the frame; a single `return best` after the guarded
// loop lets the null path return the zero register; and the X/Y difference is
// a 12-byte CoordStruct whose Z is never written, which gives the FILD slots
// their own 12 bytes and pushes the hidden-return temporary up to 0x28.
Obj_0047C3D0* Cell_0047C3D0::FindTechnoNearestTo(Point_0047C3D0* offset,
                                                 bool alt,
                                                 Obj_0047C3D0* exclude)
{
    Obj_0047C3D0* best = 0;
    int bestDist = 0;
    int x = offset->X * 7;
    int y = offset->Y * 7;
    bool techno;

    Obj_0047C3D0* head = alt ? AltObject : FirstObject;
    if (head != 0) {
        Obj_0047C3D0* obj = head;
        do {
            techno = false;
            if (obj != 0) {
                techno = (obj->AbstractFlags & 1) != 0;
            }
            if (techno && obj != exclude) {
                Coord_0047C3D0 c = (obj->*obj->Vptr->GetCoords)();
                Coord_0047C3D0 d;
                d.X = (c.X & 0xFF) - x;
                d.Y = (c.Y & 0xFF) - y;
                int dist = (int)FUN_004CAC40((double)d.X * d.X + (double)d.Y * d.Y);
                if (best == 0 || dist < bestDist) {
                    best = obj;
                    bestDist = dist;
                }
            }
            obj = obj->NextObject;
        } while (obj != 0);
    }
    return best;
}

// FUNCTION: GAMEMD 0x47C4D0  (__thiscall)
// Walk the selected occupier list, returning the first object whose runtime
// AbstractType equals the requested discriminant.
ObjectClass* CellClass::FindObjectOfType(int abs, bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == abs) {
                return obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47C520  (__thiscall)
// First building occupying the cell (ground list only).
BuildingClass* CellClass::GetBuilding() const
{
    if (CellOccupiersValid) {
        for (ObjectClass* obj = (ObjectClass*)this->FirstObject; obj;
             obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_BUILDING) {
                return (BuildingClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47C550  (__thiscall)
// First terrain object occupying the cell; `alt` selects the on-bridge list.
TerrainClass* CellClass::GetTerrain(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_TERRAIN) {
                return (TerrainClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47C5A0  CellClass::GetSomeObject (__thiscall, ret 0x8)
// Three-stage lookup: an occupier of AbstractType 2, then whatever
// FindObjectAt turns up, then an occupier of AbstractType 0x24 (terrain).
//
// The two occupier scans are written differently on purpose, because retail
// compiles them differently. The first breaks out and re-tests afterwards —
// retail re-checks the pointer at 0x47C60E even though the break guarantees it
// non-null, which is the merge point of the break and fall-through paths. The
// second returns straight from inside the loop, and retail has no such re-test.
ObjectClass* CellClass::GetSomeObject(int a, int b)
{
    ObjectClass* object = 0;

    if (CellOccupiersValid) {
        for (object = (ObjectClass*)FirstObject; object != 0; object = (ObjectClass*)object->NextObject) {
            if (WHAT_AM_I(object) == 2)
                break;
        }

        if (object != 0)
            return object;
    }

    ObjectClass* found = FindObjectAt(a, b, false);
    if (found != 0)
        return found;

    if (CellOccupiersValid) {
        for (object = (ObjectClass*)FirstObject; object != 0; object = (ObjectClass*)object->NextObject) {
            if (WHAT_AM_I(object) == ABS_TERRAIN)
                return object;
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x47D210  CellClass::SetWallOwner (__thiscall)
//
// When the cell carries a wall overlay, find the nearest building whose owner
// is a wall-owning house (and whose two state bytes at +0x90/+0x74 are set)
// and record that building's owning-house index in the cell. With no such
// building the cell's wall owner becomes -1. Cells without a wall overlay are
// left untouched.
void CellClass::SetWallOwner()
{
    if (OverlayTypeIndex != -1 && DAT_00A83D84[OverlayTypeIndex]->Wall) {
        int owner = -1;
        int best = 0x7FFFFFFF;

        for (int i = 0; i < DAT_00A8EB50; i++) {
            Building_0047D210* b = DAT_00A8EB44[i];
            if (b->At_90 && b->At_74 && b->Owner->Type->WallOwner) {
                int dist = b->DistanceFrom3D(this);
                if (dist < best) {
                    best = dist;
                    owner = (b->*b->Vtbl->GetOwningHouseIndex)();
                }
            }
        }
        WallOwnerIndex = owner;
    }
}

// FUNCTION: GAMEMD 0x47EA90
//
// Unlink an occupier from the cell's ground (or, with `alt`, on-bridge) singly
// linked occupier list. When the object was the head the head is advanced;
// otherwise the list is walked for its predecessor. In either found case the
// object's own link is cleared. Afterwards every non-infantry object that
// answers slot +0xC0 gets its slot +0xF4 called with a coordinate: buildings
// are handed the centre of this cell, everything else its own Location.
void CellClass::RemoveContent(ObjectClass* object, bool alt)
{
    if (object == 0)
        return;

    ObjectClass* head = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
    if (head == object) {
        if (alt)
            this->AltObject = (ObjectClass*)object->NextObject;
        else
            this->FirstObject = (ObjectClass*)object->NextObject;
        object->NextObject = 0;
    } else {
        ObjectClass* prev = head;
        while (prev != 0) {
            if (prev->NextObject == object) {
                prev->NextObject = object->NextObject;
                object->NextObject = 0;
                break;
            }
            prev = (ObjectClass*)prev->NextObject;
        }
    }

    if ((object->*VTBL(object)->WhatAmI)() != ABS_INFANTRY
        && (object->*VTBL(object)->At_C0)()) {
        if ((object->*VTBL(object)->WhatAmI)() == ABS_BUILDING) {
            CoordStruct coord;
            coord.X = (this->MapCoords.X << 8) + 0x80;
            coord.Y = (this->MapCoords.Y << 8) + 0x80;
            coord.Z = 0;
            (object->*VTBL(object)->At_F4)(&coord);
        } else {
            CoordStruct coord = object->Location;
            (object->*VTBL(object)->At_F4)(&coord);
        }
    }
}

// FUNCTION: GAMEMD 0x47EBA0  (__thiscall)
// First unit occupying the cell; `alt` selects the on-bridge list.
UnitClass* CellClass::GetUnit(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_UNIT) {
                return (UnitClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47EBF0  (__thiscall)
// First aircraft occupying the cell; `alt` selects the on-bridge list.
AircraftClass* CellClass::GetAircraft(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_AIRCRAFT) {
                return (AircraftClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47EC40  (__thiscall)
// First infantry occupying the cell; `alt` selects the on-bridge list.
InfantryClass* CellClass::GetInfantry(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_INFANTRY) {
                return (InfantryClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x480110
void CellClass::FUN_00480110(Point2D* out)
{
    Point2D offset;
    Point2D pt = *FUN_005FDCC0(&offset, OverlayTypeIndex);
    if (Flags & 0x80) {
        pt.Y -= 0x10;
        if (OverlayData >= 9 && OverlayData <= 0x11)
            pt.Y -= 0xF;
    } else if (OverlayTypeIndex == 0xEF) {
        pt.Y -= 0xF;
    }
    pt.X += 0x1E;
    pt.Y += DAT_00886FA4 - Level * 15;
    pt.Y += 0xF;
    *out = pt;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x481810  CellClass::GetNeighbourCell (__thiscall)
//   For facing < 8 returns the cell at MapCoords + AdjacentCell[facing&7];
//   otherwise returns this.
CellClass* CellClass::GetNeighbourCell(int facing) const
{
    if ((unsigned int)facing < 8u)
    {
        CellStruct mc = this->MapCoords;
        return DAT_0087F7E8.FUN_005657A0(mc + AdjacentCell[facing & 7]);
    }
    return const_cast<CellClass*>(this);
}

// FUNCTION: GAMEMD 0x481870  (__thiscall)
//
// Called whenever anything moves: once to remove this cell's threat from the
// mover's old position, once to add it at the new one. For every foreign house
// not allied with `SourceHouse`, fold this cell's region into that house's
// per-region threat table.
// ---------------------------------------------------------------------------
void CellClass::UpdateThreat(unsigned int SourceHouse, int ThreatLevel)
{
    CellStruct coords = this->MapCoords;
    int region = RegionLookup.CoordsToRegion(&coords);

    for (int i = 0; i < HouseArray.Count; ++i) {
        HouseClass* pHouse = HouseArray.Items[i];
        if (pHouse
            && (unsigned int)pHouse->ArrayIndex != SourceHouse
            && !pHouse->IsAlliedWith((int)SourceHouse)) {
            pHouse->FUN_004FA2E0(region, ThreatLevel);
        }
    }
}

// FUNCTION: GAMEMD 0x483410
// Claims the cell for `value` once, when a ground unit could move into it.
bool Cell_R13::FUN_00483410(int value)
{
    if (!(unknown_140 & 0x10) && IsClearToMove(1, false, false, -1, 0, -1, true))
    {
        unknown_140 |= 0x10;
        unknown_50 = value;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x00483460
// Clear bit 0x10 of +0x140 and reset +0x50; true if the bit was set.
bool FUN_00483460(Obj_00483460* self)
{
    unsigned int flags = self->unknown_140;
    if (flags & 0x10) {
        flags &= ~0x10;
        self->unknown_50 = -1;
        self->unknown_140 = flags;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x483480  CellClass::RevealCellObjects (__thiscall)
// Walk the ground occupier list and let each object reveal itself (virtual slot
// +0xFC). Nothing is read back, so the loop is a plain forward walk.
void CellClass::RevealCellObjects()
{
    for (ObjectClass* object = (ObjectClass*)FirstObject; object != 0; object = (ObjectClass*)object->NextObject) {
        (*(RevealFunc*)(*(char**)object + 0xFC))(object);
    }
}

// FUNCTION: GAMEMD 0x483610
// Returns a computed value.
int Obj_00483610::FUN_00483610() const
{
    return (unknown_140 >> 8) & 1;
}

// FUNCTION: GAMEMD 0x483620
// True when the tiberium here is mature and rich enough to grow (no layer change).
bool Cell_R13::FUN_00483620()
{
    if (!DAT_00A8B230->unknown_34A6)
        return false;
    int index = OverlayTypeIndexToTiberium_00483780(unknown_44);
    if (index == -1)
        return false;
    Tiberium_R13Cell* type = DAT_00B0F4EC[index];
    if (unknown_11C != 0)
        return false;
    if (unknown_11E >= type->unknown_E4 - 1)
        return false;
    if (type->unknown_B0 < DAT_007E3810)
        return false;
    return true;
}

// FUNCTION: GAMEMD 0x483690
// True when the tiberium here is past halfway, unmarked, rich enough and unoccupied.
bool Cell_R13::FUN_00483690()
{
    if (!(DAT_00A8B230->unknown_0000 & 0x80))
        return false;
    int index = OverlayTypeIndexToTiberium_00483780(unknown_44);
    if (index == -1)
        return false;
    if (unknown_11E <= index / 2)
        return false;
    if (unknown_11C != 0)
        return false;
    if (DAT_00B0F4EC[index]->unknown_A0 < DAT_007E3810)
        return false;
    bool empty = unknown_E4 == 0;
    return empty;
}

// FUNCTION: GAMEMD 0x483710
// As 0x483620, then lays one unit of the tiberium down.
bool Cell_R13::FUN_00483710()
{
    if (DAT_00A8B230->unknown_34A6)
    {
        int index = OverlayTypeIndexToTiberium_00483780(unknown_44);
        if (index != -1)
        {
            Tiberium_R13Cell* type = DAT_00B0F4EC[index];
            if (unknown_11C == 0 && unknown_11E < type->unknown_E4 - 1 && !(type->unknown_B0 < DAT_007E3810))
            {
                int again = OverlayTypeIndexToTiberium_00483780(unknown_44);
                return FUN_00487190(again, 1);
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x483780
//
// PARTIAL (76.7%, 89/116; instruction multiset identical). Everything up to the
// neighbour walk is exact; the residual delta is inside the inlined neighbour
// step, where cl 12.00.8804 names the two halves of the cell addition in DX/AX
// (loading the table word and adding the cell word) while retail accumulates
// both into CX, and picks a different frame slot for the spilled tiberium index
// (retail reuses the dead `forced` parameter home slot at [ESP+0x20]).
// Variants tried for that block: the two coordinates added by hand into a named
// temp (57-60%), the second table access bound to a pointer local (60.7%), a
// by-reference `operator+` with an explicit result local (60.7%, and it costs
// an extra MOV), and a by-value first operand mutated in place and returned
// (76.7%, kept; `a.Y = b.Y + a.Y` and `a.Y = a.Y + b.Y` score the same).
// Retail's frame is 4 bytes larger because it keeps the sum in its own
// CellStruct slot at [ESP+0x10] and copies it into `cell` at [ESP+0x14] as a
// whole dword; an explicit `CellStruct sum = cell + tbl[f]; cell = sum;`
// spelling is copy-propagated away by cl (still 76.7%), and giving operator+ an
// explicit result local instead of mutating the by-value operand costs a MOV
// and drops to 60.7%.
// The `if (facing >= 8) result = this; else ...` spelling is what puts retail's
// `this` arm on the fallthrough path, and the `forced == 0` arm has to come
// first for the two -1 tests to land in retail's order.
//
// CellClass::SpreadTiberium — try to push this cell's ore into one of its eight
// neighbours. Unless the caller forces it, the scenario must have the spread
// flag, the cell must actually carry tiberium, its overlay data must be past
// the halfway mark for that tiberium index, the cell must not be flagged at
// +0x11C, the tiberium's +0xA0 must not be below the rules constant, and the
// cell must be empty. The eight neighbours are then visited starting from a
// random facing, and the first one that will accept germination gets three
// units of this cell's tiberium laid into it.
bool Cell_00483780::SpreadTiberium(char forced)
{
    if (forced == 0) {
        if ((DAT_00A8B230->unknown_0000 & 0x80) == 0) {
            return false;
        }
        int index = OverlayTypeIndexToTiberium_00483780(this->OverlayTypeIndex);
        if (index == -1) {
            return false;
        }
        if (this->OverlayData <= index / 2) {
            return false;
        }
        if (this->At_11C != 0) {
            return false;
        }
        if (TiberiumArrayItems_00483780[index]->At_0A0 < DAT_007E3810) {
            return false;
        }
        if (this->FirstObject != 0) {
            return false;
        }
    }

    int tiberium = OverlayTypeIndexToTiberium_00483780(this->OverlayTypeIndex);
    if (forced == 0) {
        if (tiberium == -1) {
            return false;
        }
    } else {
        if (tiberium == -1) {
            tiberium = 0;
        }
    }

    Tiberium_00483780* type = TiberiumArrayItems_00483780[tiberium];
    int start = DAT_00A8B230->unknown_0218.RandomRanged(0, 7);

    for (int i = 0; i < 8; i++) {
        Cell_00483780* neighbour = this->GetNeighbourCell((i + start) & 7);
        if (neighbour != 0 && neighbour->CanTiberiumGerminate(type)) {
            return neighbour->FUN_00487190(tiberium, 3);
        }
    }

    return false;
}

// FUNCTION: GAMEMD 0x4838E0
//
// Can ore/gems spread into this cell?  The cell must be inside the usable map
// area, carry neither of the two blocking flags, not sit under a live building
// whose type forbids growth, not hold a terrain object whose type forbids it,
// have a land type that accepts ore, carry no overlay yet, have nothing at
// +0x11C, and its isometric tile type (when in range) must allow tiberium.
// The tiberium argument is not consulted.  Written as one conjunction so every
// failing guard shares the single trailing `return false` block.
bool Cell_004838E0::CanTiberiumGerminate(void* tiberium)
{
    Building_004838E0* bld;
    Terrain_004838E0* ter;
    int idx;
    if (MapInstance_004838E0.IsWithinUsableArea(&this->MapCoords, true)
        && !(this->Flags & 0x500)
        && !((bld = (Building_004838E0*)this->GetBuilding()) != 0
             && ((Obj_004838E0*)bld)->Health > 0
             && !bld->Type->At_C9A
             && !bld->Type->At_1701)
        && !((ter = (Terrain_004838E0*)this->GetTerrain()) != 0
             && ter->Type->At_2B1)
        && GroundTable_004838E0[this->LandType].At_000
        && this->OverlayTypeIndex == -1
        && !this->At_11C
        && ((idx = this->IsoTileTypeIndex) < 0
            || idx >= IsoTileArray_004838E0.Count
            || IsoTileArray_004838E0.Items[idx]->At_306)) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4839F0
HRESULT __stdcall CellClass::Load(IStream* pStm)
{
    HRESULT result = FUN_00410380(
        reinterpret_cast<Subject_00410320*>(this),
        reinterpret_cast<Stream_00410320*>(pStm));
    if (result < 0) {
        return result;
    }

    new (this) CellClass(AbstractNoInit());

    if (FoggedObjects != 0) {
        FoggedObjects = new DynamicVectorClass<FoggedObjectClass*>(0, 0);

        int count;
        result = pStm->Read(&count, sizeof(count), 0);
        if (result < 0) {
            return result;
        }

        for (int i = 0; i < count; ++i) {
            FoggedObjectClass* object = 0;
            result = pStm->Read(&object, sizeof(object), 0);
            if (result < 0) {
                return 0;
            }
            FoggedObjects->AddItem(object);
        }

        for (int j = 0; j < FoggedObjects->Count; ++j)
            DAT_00B0C110.SwizzleManagerClass::vf_4(&FoggedObjects->Items[j]);
    }

    PixelFX = 0;
    int cellIndex = MapCoords.Y * 512 + MapCoords.X;
    if (DAT_0087F924[cellIndex] != 0) {
        delete DAT_0087F924[cellIndex];
        DAT_0087F924[cellIndex] = 0;
    }
    DAT_0087F924[cellIndex] = this;

    DAT_00B0C110.SwizzleManagerClass::vf_4(&BridgeOwnerCell);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_30);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AttachedTag);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Jumpjet);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirstObject);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AltObject);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&RadSite);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Rubble);

    if (OverlayTypeIndex == 0xB3 || OverlayTypeIndex == 0xF2) {
        OverlayTypeIndex = -1;
        OverlayData = 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x483C10
HRESULT __stdcall CellClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT result = FUN_00410320(this, pStm, fClearDirty);
    if (result < 0) {
        return result;
    }

    if (FoggedObjects != 0) {
        int count = FoggedObjects->Count;
        result = pStm->Write(&count, 4, 0);
        if (result < 0) {
            return result;
        }

        for (int i = 0; i < count; ++i) {
            result = pStm->Write(&FoggedObjects->Items[i],
                                 sizeof(FoggedObjectClass*), 0);
            if (result < 0) {
                break;
            }
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x484A80
// Updates one member in place.
void __stdcall FUN_00484A80(Arg1_00484A80* a1)
{
    a1->unknown_194++;
}

// FUNCTION: GAMEMD 0x484A90
// Branching.
void __stdcall FUN_00484A90(Arg1_00484A90* a1)
{
    if (DAT_00A8E9A0 != 0)
    {
        a1->unknown_194--;
    }
}

// FUNCTION: GAMEMD 0x484F10
bool __stdcall FUN_00484F10(int)
{
    return true;
}

// FUNCTION: GAMEMD 0x484F20  CellClass::GetTunnel (__thiscall)
// The tunnel index is a signed short, so both ends are checked: negative means
// "no tunnel here", and the upper bound guards a stale index against the live
// array count.
TunnelClass* CellClass::GetTunnel() const
{
    if (TubeIndex >= 0 && TubeIndex < TunnelArrayCount)
        return TunnelArrayItems[TubeIndex];

    return 0;
}

// FUNCTION: GAMEMD 0x484FF0  CellClass::GetUIName (__thiscall)
// Same overlay->tiberium lookup as GetContainedTiberiumIndex below, then the
// tiberium type's UI name; a cell with no tiberium overlay yields a null name.
const wchar_t* CellClass::GetUIName() const
{
    int idxTiberium = OverlayTypeIndexToTiberium(this->OverlayTypeIndex);
    if (idxTiberium != -1)
        return TiberiumArrayItems[idxTiberium]->UIName;

    return 0;
}

// FUNCTION: GAMEMD 0x485010  CellClass::GetContainedTiberiumIndex (__thiscall)
//   mov ecx,[ecx+0x44]; jmp 0x5fdd20  — forward OverlayTypeIndex to the lookup.
int CellClass::GetContainedTiberiumIndex() const
{
    return OverlayTypeIndexToTiberium(this->OverlayTypeIndex);
}

// FUNCTION: GAMEMD 0x485020  CellClass::GetContainedTiberiumValue (__thiscall)
//   ecx=[esi+0x44]; call 0x5fdd20; if eax==-1 return 0;
//   edx=TiberiumArrayItems[eax]; return [edx+0xb8] * ([esi+0x11e] + 1).
int CellClass::GetContainedTiberiumValue() const
{
    int idx = OverlayTypeIndexToTiberium(this->OverlayTypeIndex);
    if (idx == -1)
        return 0;
    return TiberiumArrayItems[idx]->Value * (this->OverlayData + 1);
}

// FUNCTION: GAMEMD 0x00485060
// Is +0x38 inside the 14-wide window that starts at the global 0xAA0738.
int FUN_00485060(Obj_00485060* self)
{
    int value = self->unknown_38;
    if (value >= DAT_00AA0738 && value < DAT_00AA0738 + 14) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x485130
void CellClass::FUN_00485130(void* target)
{
    if (AttachedTag == target) {
        if (AttachedTag != 0)
            AttachedTag->InstanceCount--;
        AttachedTag = 0;
        DAT_00880944.RemoveItem(MapCoords);
    }
    if (BridgeOwnerCell == target)
        BridgeOwnerCell = 0;
    if (unknown_30 == target)
        unknown_30 = 0;
    if (FoggedObjects != 0) {
        if (((AbstractClass*)target)->vf_11() == 0x3D) {
            FoggedObjectClass* fogged = (FoggedObjectClass*)target;
            FoggedObjects->RemoveItem(fogged);
        }
    }
}

// FUNCTION: GAMEMD 0x485240  CellClass::SetMapCoords (__thiscall)
//   mov eax,[esp+4]; mov edx,[eax]; mov [ecx+0x24],edx; ret 4
void CellClass::SetMapCoords(CellStruct const* coords)
{
    this->MapCoords = *coords;
}

// FUNCTION: GAMEMD 0x486380
// Branching.
bool Obj_00486380::FUN_00486380()
{
    if (unknown_38 == 0xFFFF || unknown_38 == 0)
    {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4863A0
// True when the value lies in either of two runs (0x14 and 0xC long).
bool Obj_004863A0::FUN_004863A0() const
{
    int v = unknown_38;
    if ((v >= DAT_00ABC1D8 && v < DAT_00ABC1D8 + 0x14)
        || (v >= DAT_00AA1058 && v < DAT_00AA1058 + 0xC)) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4863D0
bool CellClass::FUN_004863D0()
{
    if (DAT_00AA1020 != -1 && IsoTileTypeIndex >= DAT_00AA1020 && IsoTileTypeIndex < DAT_00AA1020 + 0x28)
        return true;
    if (DAT_00AA073C != -1 && IsoTileTypeIndex >= DAT_00AA073C && IsoTileTypeIndex < DAT_00AA073C + 4) {
        if (IsoTileTypeIndex == DAT_00AA073C || IsoTileTypeIndex == DAT_00AA073C + 3) {
            if (Height == 0 || Height == 4)
                return false;
        }
        return true;
    }
    if (DAT_00ABB110 != -1 && IsoTileTypeIndex >= DAT_00ABB110 && IsoTileTypeIndex < DAT_00ABB110 + 4) {
        if (IsoTileTypeIndex == DAT_00ABB110 || IsoTileTypeIndex == DAT_00ABB110 + 3) {
            if (Height == 1 || Height == 3)
                return false;
        }
        return true;
    }
    if (DAT_00AA1050 != -1 && IsoTileTypeIndex >= DAT_00AA1050 && IsoTileTypeIndex < DAT_00AA1050 + 4) {
        if (IsoTileTypeIndex == DAT_00AA1050 || IsoTileTypeIndex == DAT_00AA1050 + 3) {
            if (Height == 0 || Height == 1)
                return false;
        }
        return true;
    }
    if (DAT_00AA10A0 != -1 && IsoTileTypeIndex >= DAT_00AA10A0 && IsoTileTypeIndex < DAT_00AA10A0 + 4) {
        if (IsoTileTypeIndex == DAT_00AA10A0 || IsoTileTypeIndex == DAT_00AA10A0 + 3) {
            if (Height == 2 || Height == 3)
                return false;
        }
        return true;
    }
    if (DAT_00ABBEBC != -1 && IsoTileTypeIndex >= DAT_00ABBEBC && IsoTileTypeIndex < DAT_00ABBEBC + 0x14)
        return true;
    if (DAT_00ABAD24 != -1 && IsoTileTypeIndex >= DAT_00ABAD24 && IsoTileTypeIndex < DAT_00ABAD24 + 4)
        return true;
    if (DAT_00AA0E28 != -1 && IsoTileTypeIndex >= DAT_00AA0E28 && IsoTileTypeIndex < DAT_00AA0E28 + 0x10)
        return true;
    if (DAT_00ABAD1C != -1 && IsoTileTypeIndex >= DAT_00ABAD1C && IsoTileTypeIndex < DAT_00ABAD1C + 0x10)
        return true;
    if (DAT_00ABC2C8 != -1 && IsoTileTypeIndex >= DAT_00ABC2C8 && IsoTileTypeIndex < DAT_00ABC2C8 + 2)
        return true;
    if (DAT_00AA101C != -1 && IsoTileTypeIndex >= DAT_00AA101C && IsoTileTypeIndex < DAT_00AA101C + 0x1C)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x4865B0
// Branching.
bool Obj_004865B0::FUN_004865B0()
{
    if (unknown_38 < DAT_00ABAD28 || unknown_38 >= DAT_00ABAD28 + 0x2A)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x4865D0
// True when the value at +0x38 lies in any of six runs.
bool Obj_004865D0::FUN_004865D0() const
{
    int v = unknown_38;
    if (v >= DAT_00ABAD28 && v < DAT_00ABAD28 + 0x2A) {
        return true;
    }
    if ((v >= DAT_00AA0738 && v < DAT_00AA0738 + 0xE)
        || (v >= DAT_00AA073C && v < DAT_00AA073C + 4)
        || (v >= DAT_00ABB110 && v < DAT_00ABB110 + 4)
        || (v >= DAT_00AA1050 && v < DAT_00AA1050 + 4)
        || (v >= DAT_00AA10A0 && v < DAT_00AA10A0 + 4)) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x486650
// Branching.
bool Obj_00486650::FUN_00486650()
{
    if (unknown_38 < DAT_00AA10A4 || unknown_38 >= DAT_00AA10A4 + 0xE)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486670
// Branching.
bool Obj_00486670::FUN_00486670()
{
    if (unknown_38 < DAT_00ABC2B0 || unknown_38 >= DAT_00ABC2B0 + 0x10)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486690
// True when the value at +0x38 lies in any of three runs.
bool Obj_004865D0::FUN_00486690() const
{
    int v = unknown_38;
    if ((v >= DAT_00ABAD20 && v < DAT_00ABAD20 + 0xB)
        || (v >= DAT_00ABC1D4 && v < DAT_00ABC1D4 + 0x18)
        || (v >= DAT_00AA10AC && v < DAT_00AA10AC + 0x42)) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4866D0
// Branching.
bool Obj_004866D0::FUN_004866D0()
{
    if (unknown_38 < DAT_00ABBEC8 || unknown_38 >= DAT_00ABBEC8 + 0xF)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x4866F0
// Branching.
bool Obj_004866F0::FUN_004866F0()
{
    if (unknown_38 < DAT_00ABBEC4 || unknown_38 >= DAT_00ABBEC4 + 4)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486710
// Branching.
bool Obj_00486710::FUN_00486710()
{
    if (unknown_38 < DAT_00AA1094 || unknown_38 >= DAT_00AA1094 + 4)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486730
// Branching.
bool Obj_00486730::FUN_00486730()
{
    if (unknown_38 < DAT_00AA0E20 || unknown_38 >= DAT_00AA0E20 + 0xE)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486750  (__thiscall)
// Is this cell a concrete bridge tile?
//
// LEVER, measured over six spellings in one probe compile: the base must be
// referenced as the global on all three occurrences, NOT copied into a named
// local first. With a local cl colours the global EAX and the member ECX
// (53.8%, multiset identical, pure register naming); referencing the global
// directly makes cl keep it in EDX and give the member EAX, which is retail
// exactly. Hoisting the member into a local, an early `return false` on the
// -1 arm, and a single `&&` chain all reproduce the losing colouring.
// The upper bound is written as `base + 0x10` so cl emits retail's in-place
// `ADD EDX,0x10`, and the success arm is nested so `return false` stays the
// trailing fall-through and cl materialises `MOV AL,0x1`.
bool CellClass::IsBridgeTile()
{
    if (GgBridgeTileBase != -1) {
        if (this->IsoTileTypeIndex >= GgBridgeTileBase
            && this->IsoTileTypeIndex < GgBridgeTileBase + 0x10) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x486770  (__thiscall)
// Is this cell a wooden bridge tile? Same window test against the wood set.
bool CellClass::IsWoodBridgeTile()
{
    if (GgWoodBridgeTileBase != -1) {
        if (this->IsoTileTypeIndex >= GgWoodBridgeTileBase
            && this->IsoTileTypeIndex < GgWoodBridgeTileBase + 0x10) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x486790  (__thiscall)
// The same window test against the set at 0x00AA0E24, without the "-1 means
// absent" guard the other two carry. Retail loads the member before the global
// here, which is the order the member-first expression gives.
bool CellClass::IsTileInSet00AA0E24()
{
    if (this->IsoTileTypeIndex >= GgTileBase_00AA0E24
        && this->IsoTileTypeIndex < GgTileBase_00AA0E24 + 0x10) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4867B0
// Whether the stored value is one global, or falls in the sixteen values
// starting at another.
bool Obj_004867B0::FUN_004867B0() const
{
    int value = unknown_38;
    if (value == DAT_00AA0E18 || (value >= DAT_00AA0748 && value < DAT_00AA0748 + 0x10)) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4867E0
bool CellClass::IsOnFloor() const
{
    if (IsoTileTypeIndex < DAT_00AA0738 ||
        IsoTileTypeIndex >= DAT_00AA0738 + 0xE) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x486840
CoordStruct CellClass::vf_18()
{
    int x = MapCoords.X * 256 + 128;
    int y = MapCoords.Y * 256 + 128;
    Point2D center(x, y);
    int z = GetFloorHeight(center);
    CoordStruct result = { x, y, z };
    return result;
}

// FUNCTION: GAMEMD 0x486890
CoordStruct CellClass::vf_22()
{
    if ((Flags & 0x100) != 0) {
        int zAdjustment = DAT_0089E7B4;
        CoordStruct result = vf_18();
        result.Z += zAdjustment;
        return result;
    }

    return vf_18();
}

// FUNCTION: GAMEMD 0x486900
// Branching.
unsigned char Obj_00486900::FUN_00486900()
{
    if (unknown_38 == DAT_00ABC2C8)
    {
        return 1;
    }
    return (unknown_38 == (DAT_00ABC2C8 + 1)) ? true : false;
}

// FUNCTION: GAMEMD 0x486920
//
// Wake the veins in a grown, flat vein cell the first time something
// vulnerable stands in it: a low-flying techno without vein immunity and
// without the ability that protects it gets the attack animation played at
// the cell centre, and the cell is flagged so it only happens once.
//
// Load-bearing: the map coordinate pair is copied whole into a local before
// its halves are used (retail spills the dword and reads Y back out of the
// spill), the coordinate arithmetic is written before the sub-cell offset
// so the shared half-cell constant is materialised after the shifts, the
// corner is a separate inline helper returning by value so the offsets come
// out as LEAs rather than in-place subtractions, and the techno flag is
// assigned inside the guard chain so it is stored to the frame while its
// own AND sets the flags.
void Cell_00486920::ActivateVeins()
{
    if (OverlayTypeIndex == 0x7E && OverlayData >= 0x30 && SlopeIndex == 0
        && !(Flags & 0x20000)) {
        bool techno;
        for (Obj_00486920* obj = FirstObject; obj != 0; obj = obj->NextObject) {
            if ((obj->*obj->Vptr->GetHeight)() <= 5 && obj != 0
                && (techno = (obj->AbstractFlags & 1) != 0) != false) {
                if (techno
                    && !(obj->*obj->Vptr->GetTechnoType)()->At_C91
                    && !obj->FUN_0070D0D0(8)) {
                    Anim_00486920* anim =
                        (Anim_00486920*)operator new(sizeof(Anim_00486920));
                    if (anim != 0) {
                        Coord_00486920 at = GetCornerCoords();
                        anim->Construct(DAT_008871E0->At_E8, &at, 0, 1, 0x600, 0, 0);
                    }
                    Flags |= 0x20000;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x486A70  CellClass::FogCell (__thiscall)
//
// Freeze what this cell currently shows into a fog snapshot. Only when the
// scenario's 0x1000 flag is set: the same diagonal stripe CleanFog walks
// (i = 1,3,..,15 with the coord stepping (+1,+1)) is visited, and for every
// cell whose Level sits in [i-2, i] and that is not already fogged a fresh
// fogged-object vector is built, every occupier of that cell is asked to
// record itself into it, the fog bit is set, and the vector is kept only if
// anything landed in it.
//
// MATCHED 100% (123/123 instructions; 358/375 bytes, 5 relocation slots).
//
// The lever was the allocation's *name*, not the register allocator. The
// earlier spelling re-assigned the allocation to its own variable
// (`FogVec* fogged = (FogVec*)op_new(0x18); fogged = fogged ? fogged->Construct()
// : 0;`), which makes cl home the raw `operator new` result in `fogged`'s
// callee-saved register immediately (`MOV ESI,EAX` ahead of `ADD ESP,4`) and
// run the seven constructor stores through that register. Retail keeps the
// result in EAX across the null test and all seven stores and only copies it
// into the vector register at the join (`MOV EDI,EAX; JMP` / `XOR EDI,EDI`) —
// the ordinary `T* p = new T;` shape, where the constructed value is a fresh
// name. Binding the raw allocation to its own `void* raw` and naming the
// constructed pointer separately reproduces it, and the ESI/EDI exchange that
// ran through the rest of the body (the 0x400000 literal, the occupier cursor
// and the vector) fell into line by itself: 68.3% to 100% on that one edit.
//
// Four spellings of the same split all reach 100% and are interchangeable:
// the `void* raw` ternary used here; a free `FogConstruct(p)` taking the
// vector as a parameter; an if/else that calls `p->Construct()` for effect and
// then assigns `fogged = p`; and an inline `FogNew()` helper holding the whole
// allocate-and-construct pair. Only the self-assigning control stays at 68.3%.
//
// The tail-merge diagnostic from the eleventh batch does NOT apply here: there
// is a single return, retail's four callee-saved pushes are already sunk below
// the scenario-flag test, and our prologue reproduced their order and offsets
// exactly even at 68.3%. The register exchange was downstream of the naming.
// Previously tried without effect: `if (p) p = p->Construct();` in place of the
// ternary (0%), a `FogVecBase` temporary struct-assigned inside Construct
// (adds 12 frame bytes, 0%), and the vector pointer declared at the top of the
// stripe body (68.3%, byte-identical residual).
void CellClass::FogCell()
{
    if (DAT_00A8B230->unknown_0000 & 0x1000)
    {
        CellStruct coords = this->MapCoords;
        int i = 1;
        do
        {
            CellClass* cell = FogMapInstance->GetCellAt(coords);
            int level = cell->Level;
            if (level >= i - 2 && level <= i && (cell->Flags & 0x400000) == 0)
            {
                void* raw = FogOperatorNew(sizeof(FogVec_00486A70));
                FogVec_00486A70* fogged =
                    raw ? ((FogVec_00486A70*)raw)->Construct() : 0;
                (fogged->*fogged->Vptr->At_08)(1, 0);
                fogged->CapacityIncrement = 1;

                cell->Flags |= 0x400000;

                for (Obj_00486A70* obj = (Obj_00486A70*)cell->FirstObject; obj != 0;
                     obj = obj->NextObject)
                {
                    int rtti = obj->RTTI.Vptr->WhatAmI(&obj->RTTI);
                    if (rtti == 6)
                    {
                        CellStruct where;
                        (obj->*obj->Vptr->GetMapCoords)(&where);
                        if (obj->CheckFog())
                        {
                            bool flag;
                            if (!(obj->*obj->Vptr->At_80)())
                            {
                                flag = true;
                                if (obj->Unknown_6ED == 0xF) {
                                    flag = false;
                                }
                            }
                            else
                            {
                                flag = false;
                            }
                            obj->FUN_00457AA0(fogged, cell, flag);
                        }
                    }
                    else if (rtti == 1 || rtti == 2 || rtti == 0xF)
                    {
                        (obj->*obj->Vptr->At_150)();
                    }
                }

                if (fogged->Count > 0) {
                    cell->FoggedObjects = (DynamicVectorClass<FoggedObjectClass*>*)fogged;
                } else if (fogged != 0) {
                    (fogged->*fogged->Vptr->At_00)(1);
                }
            }
            ++coords.X;
            ++coords.Y;
            i += 2;
        } while (i <= 15);
    }
}

// FUNCTION: GAMEMD 0x486BF0  CellClass::CleanFog (__thiscall)
//   Walks a small diagonal stripe of cells starting at this cell's MapCoords:
//   i runs 1,3,5,...,13; each step the running coord steps (+1,+1). For every
//   cell whose Level falls within [i-2, i] the fog bit (0x400000) is cleared
//   from Flags and its fogged objects are dropped.
void CellClass::CleanFog()
{
    CellStruct coords = this->MapCoords;
    int i = 1;
    do
    {
        CellClass* cell = MapInstance->GetCellAt(coords);
        int level = cell->Level;
        if (level >= i - 2 && level <= i)
        {
            cell->Flags &= 0xFFBFFFFF;
            cell->ClearFoggedObjects();
        }
        ++coords.X;
        ++coords.Y;
        i += 2;
    } while (i < 15);
}

// FUNCTION: GAMEMD 0x486E30
//
// If a veinhole monster covers this cell, hand the cell to it; otherwise let the
// map's cell record for these coordinates react. Always returns 0.
int Cell_00486E30::FUN_00486E30()
{
    Vein_00486E30* vein = FUN_0074CDB0(&MapCoords);
    if (vein) {
        vein->FUN_0074EF10(this);
        return 0;
    }
    DAT_0087F7E8_00486E30.GetCellAt(&MapCoords)->FUN_00485590();
    return 0;
}

// FUNCTION: GAMEMD 0x004870B0
// Is bit `bit` of +0x78 set.
int Obj_004870B0::FUN_004870B0(int bit) const
{
    return (unknown_78 & (1 << bit)) != 0;
}

// FUNCTION: GAMEMD 0x4870D0
// True when the entry in the first table is positive.
bool Obj_004870D0::FUN_004870D0(int index) const
{
    return unknown_7C[index] > 0;
}

// FUNCTION: GAMEMD 0x4870F0
// True when the entry in the second table is positive.
bool Obj_004870D0::FUN_004870F0(int index) const
{
    return unknown_AC[index] > 0;
}

// FUNCTION: GAMEMD 0x487110
void Obj_00487110::SetBit(int bit)
{
    unknown_78 |= 1 << bit;
}

// FUNCTION: GAMEMD 0x487130
void Obj_00487130::ClearBit(int bit)
{
    unknown_78 &= ~(1 << bit);
}

// FUNCTION: GAMEMD 0x487150
// Register one more sensor (a unit able to detect cloaked objects) belonging to
// house `idxHouse` over this cell.
void CellClass::IncreaseSensorsOfHouse(int idxHouse)
{
    ++this->SensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487160
// Drop one sensor belonging to house `idxHouse` from this cell.
void CellClass::DecreaseSensorsOfHouse(int idxHouse)
{
    --this->SensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487170
// Register one more disguise-piercing sensor for house `idxHouse` over this
// cell. Same counter shape as above against the second array.
void CellClass::IncreaseDisguiseSensorsOfHouse(int idxHouse)
{
    ++this->DisguiseSensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487180
// Drop one disguise-piercing sensor for house `idxHouse` from this cell.
void CellClass::DecreaseDisguiseSensorsOfHouse(int idxHouse)
{
    --this->DisguiseSensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487630  CellClass::ReduceShroudCounter (__thiscall)
//   Decrements ShroudCounter (snapping a value of 1 to 0 first); once it hits
//   zero either flags the cell shrouded (AltFlags |= 0x18) or, when already
//   shrouded, clears Flags bit 0x20.
//
//   Screened for the inline-assembly signature first and it is absent: the
//   function has no prologue at all, every value lives in EAX/EDX off ECX, and
//   every instruction is one cl emits from a C expression. Retail was compiled
//   from C++.
//
//   The two flag blocks have to be placed by hand. Retail lays the reshroud
//   block as the fallthrough (`TEST AL,8; JZ +2` skips only the second test)
//   and parks the already-shrouded block after it; cl normalises every
//   conjunction to the mirror layout, both tests jumping to the far block with
//   the &&-then falling through. All of `&&`/`||`, the condition inverted,
//   nested ifs, early returns in either arm, `if (cond) goto`, an explicit
//   two-goto skeleton, the decrement written out rather than pre-decremented
//   and the flags word named in the second arm sit at 48.1% with an identical
//   multiset bar one branch polarity. Only the fully spelled-out skeleton below
//   -- each failing test jumping to the reshroud label and an unconditional
//   jump to the shrouded label after them -- makes cl reverse the second test
//   and emit retail's order.
void CellClass::ReduceShroudCounter()
{
    if (ShroudCounter == 1) {
        ShroudCounter = 0;
    }

    int remaining = --ShroudCounter;
    unsigned alt = AltFlags;

    if ((alt & 8) == 0) goto reshroud;
    if ((alt & 0x10) == 0) goto reshroud;
    goto shrouded;

reshroud:
    if (remaining <= 0) AltFlags = alt | 0x18;
    return;

shrouded:
    if (remaining <= 0 && (Flags & 0x20) == 0x20) Flags &= ~0x20;
}

// FUNCTION: GAMEMD 0x487690  CellClass::IncreaseShroudCounter (__thiscall)
//   normalise a -1 counter to 0, ++ it, clamp to GapsCoveringThisCell, and if it
//   crossed up through zero set Flags |= 0x20.
void CellClass::IncreaseShroudCounter()
{
    int old = this->ShroudCounter;
    if (old == -1)
        this->ShroudCounter = 0;
    this->ShroudCounter = this->ShroudCounter + 1;
    if (this->ShroudCounter > (int)this->GapsCoveringThisCell)
        this->ShroudCounter = this->GapsCoveringThisCell;
    if (old <= 0 && this->ShroudCounter > 0)
        this->Flags = (CellFlags)(this->Flags | 0x20);
}

// FUNCTION: GAMEMD 0x4876F0  CellClass::Unshroud (__thiscall)
// Force the cell visible: set the two "revealed" bits in AltFlags, and if the
// cell still carries shroud counters, mark the shroud-redraw bit in Flags too.
// Retail sets all three through the AL byte lane (`OR AL,0x18` / `OR AL,0x20`
// on the loaded dword), which is what VC6 emits for a small-constant OR.
void CellClass::Unshroud()
{
    AltFlags |= 0x18;

    if (ShroudCounter > 0)
        Flags |= 0x20;
}

// FUNCTION: GAMEMD 0x00487C70
//
// Store the argument into the member at +0xF8.
void Setter_00487C70::FUN_00487C70(int value)
{
    *(int*)(Bytes + 0xF8) = value;
}

// FUNCTION: GAMEMD 0x487C80
int Obj_00487C80::Get_F8()
{
    return unknown_F8;
}

// FUNCTION: GAMEMD 0x487C90
// Whether the stored double is above the shared constant.
int Obj_00487C90::FUN_00487C90() const
{
    return unknown_F0 > DAT_007E1718;
}

// FUNCTION: GAMEMD 0x487CB0  CellClass::GetRadLevel (__thiscall)
// The cell's radiation, clamped to the rules ceiling and truncated to an int.
// Retail tail-jumps into the CRT double-to-long helper at 0x7C5F00 rather than
// calling it, which is what a cast in return position produces.
//
// The compare is `FLD RadLevel; FCOMP` against the ceiling already on the
// stack, testing C0 alone (`TEST AH,1`). That shape comes from binding
// RadLevel to a double local that is used *only* in the comparison, with the
// ternary's result arm re-reading the member (retail's second `FLD [ECX+0xF0]`
// at 0x487CCC). Comparing the member directly folds it into `FCOM qword ptr
// [ECX+0xF0]` with `TEST AH,0x41` (20.0%); using the local in the result arm
// too spills it to a frame retail does not have (0.0%).
int CellClass::GetRadLevel()
{
    double ceiling = RulesGlobalPtr->RadLevelMax;
    double rad = RadLevel;

    return (int)(rad < ceiling ? RadLevel : ceiling);
}

// FUNCTION: GAMEMD 0x487CE0  CellClass::RadLevel_Increase (__thiscall)
//   fld [esp+4]; fadd [ecx+0xf0]; fstp [ecx+0xf0]; ret 8
void CellClass::RadLevel_Increase(double amount)
{
    this->RadLevel += amount;
}

// FUNCTION: GAMEMD 0x487D50
int Obj_00487D50::Combined()
{
    return unknown_11B + ((unknown_140 >> 7) & 1) * 4;
}

// FUNCTION: GAMEMD 0x487DF0
// One-line land-type predicate: true when the cell's LandType is 5.
bool CellClass::IsLandType5() const
{
    if (this->LandType == 5) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x487E00
// Report whether the cell counts as covered for occupation-height purposes.
// While the occupier list is valid the cell is walked for an occupier whose
// WhatAmI() is 6; finding one with a covering height of exactly 1 clears the
// answer. Otherwise the answer is simply "the covering height is non-zero".
//
// The redundant null test retail performs on the occupier it has just
// dereferenced is reproduced verbatim -- it is the source's own belt-and-braces
// guard and dropping it loses the branch.
bool CellClass::FUN_00487E00() const
{
    if (CellOccupiersValid) {
        for (ObjectClass* obj = (ObjectClass*)this->FirstObject; obj != 0;
             obj = (ObjectClass*)obj->NextObject) {
            if (((WhatAmIFunc)((void**)*(void**)obj)[11])(obj) == 6) {
                if (obj != 0 && this->OccupyHeightsCoveringMe == 1) {
                    return false;
                }
                break;
            }
        }
    }
    return this->OccupyHeightsCoveringMe != 0;
}

// FUNCTION: GAMEMD 0x487E50
int __stdcall CellClass::vf_rtti_3()
{
    return 0x0B;
}

// FUNCTION: GAMEMD 0x487E60
// Returns a constant. Vtable slot 11 of CellClass (RTTI).
int Obj_00487E60::FUN_00487E60() const
{
    return 0xB;
}

// FUNCTION: GAMEMD 0x487E70
// Returns a constant. Vtable slot 12 of CellClass (RTTI).
int Obj_00487E70::FUN_00487E70() const
{
    return 0x148;
}

// FUNCTION: GAMEMD 0x487E80
// VC6 emits this scalar deleting destructor from CellClass's virtual destructor declaration.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F924
CellClass** DAT_0087F924;
