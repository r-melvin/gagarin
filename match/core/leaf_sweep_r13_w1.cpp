// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Round-13 sweep of small members and list walkers between 0x401000 and 0x4A0000.
// Ordered ascending by retail address.
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"
#include "clamped_scale_methods.h"
#include "triple_timer_init_methods.h"
#include "vector_class.h"
#include "vector_class_operations.h"

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

// FUNCTION: GAMEMD 0x402BB0
// Drains the pending list: detach each node, run its entry callback, clear the
// entry's low flag bit, free the node.
void FUN_00402BB0()
{

    QNode_00402900* it = (QNode_00402900*)DAT_00815E98->FUN_004073C0();
    QNode_00402900* node = it;
    for (; it; node = it)
    {
        it = (QNode_00402900*)it->FUN_004073E0();
        FUN_00407450(node);
        node->unknown_0C->unknown_18(node);
        node->unknown_0C->unknown_0C &= ~1u;
        FUN_007C8B3D(node);
        DAT_0087DE28 = 0;
    }
}

// FUNCTION: GAMEMD 0x402C40
// Sum of the +0x18 field over every pending node.
int FUN_00402C40()
{

    int sum = 0;
    QNode_00402900* node = (QNode_00402900*)DAT_00815E98->FUN_004073C0();
    while (node)
    {
        sum += node->unknown_18;
        if (!node)
            break;
        node = (QNode_00402900*)node->FUN_004073E0();
    }
    return sum;
}

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

// FUNCTION: GAMEMD 0x406190
// Scales the clamped level by the rate and applies it to the first sink.
void __fastcall FUN_00406190(Obj_004061D0* self, unsigned level)
{
    self->Sink.Set((self->Rate->Value >> 16) * Clamp_00406190(level) >> 14);
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

// FUNCTION: GAMEMD 0x426E80
int Obj_00426E80::FindRun(int pos)
{
    if (pos < unknown_CC)
    {
        int count = unknown_92;
        int i = 0;
        if (count > 0)
        {
            Run_00426E80* run = unknown_80C;
            for (; i < count; i++, run++)
            {
                int start = run->unknown_00;
                if (start <= pos && start + run->unknown_02 > pos)
                    return i;
            }
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x4115A0 - scalar deleting destructor.
extern char VTABLE_007E2198[];
struct Obj_004115A0
{
    // FUNCTION: GAMEMD 0x4115A0
    void* Destroy(unsigned char flags);
};

// FUNCTION: GAMEMD 0x4115A0
void* Obj_004115A0::Destroy(unsigned char flags)
{
    *(char**)this = VTABLE_007E2198;
    if (flags & 1)
        FUN_007C8B3D(this);
    return this;
}

// ---------------------------------------------------------------------------
// 0x42AA40 - facing between two adjacent cells, or 8 when they are not neighbours.
struct Cell_0042AA40
{
    short unknown_00;
    short unknown_02;
};

// GLOBAL: GAMEMD 0x818760
extern int DAT_00818760[9];

// FUNCTION: GAMEMD 0x42AA40
int __fastcall FUN_0042AA40(Cell_0042AA40* from, Cell_0042AA40* to)
{
    int dy = to->unknown_02 - from->unknown_02;
    if (abs(dy) <= 1)
    {
        int fx = from->unknown_00;
        int tx = to->unknown_00;
        if (abs(tx - fx) <= 1)
            return DAT_00818760[dy * 3 - fx + tx];
    }
    return 8;
}

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

// FUNCTION: GAMEMD 0x42EAD0
// PARTIAL: 94.3% - same instructions; retail loads the key pointer into EDI before the
// record pointer into ESI, ours loads them the other way round (variants tried: key
// declared before/after/inside the guard, pointer-walk vs index).
Rec_0042EAD0* Obj_0042EAD0::FindByKey(const Key_0042EAD0* key)
{
    int i = 0;
    int count = unknown_14;
    if (count > 0)
    {
        const unsigned short* k = &key->unknown_00;
        Rec_0042EAD0* items = unknown_08;
        const unsigned short* r = &items->unknown_04;
        for (;;)
        {
            if (k[0] == r[0] && k[1] == r[1])
                return &items[i];
            i++;
            r += 8;
            if (i >= count)
                break;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x42F340
// First record owned by `owner` whose flag byte is clear, or null.
Rec_0042EAD0* Obj_0042EAD0::FindFree(const Owner_0042F340* owner)
{
    int i = 0;
    int key = owner->unknown_DF8;
    int count = unknown_14;
    if (count > 0)
    {
        Rec_0042EAD0* r = unknown_08;
        for (;;)
        {
            if (r->unknown_00 == key && !r->unknown_08)
                return r;
            i++;
            r++;
            if (i >= count)
                break;
        }
    }
    return 0;
}

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

// FUNCTION: GAMEMD 0x4129C0
void Obj_004129C0::CollectRow(int index)
{
    DynamicVectorClass<int>* row = &unknown_0000[index];
    int count = row->Count;
    for (int i = 0; i < count; i++)
    {
        int value = row->Slot6(i);
        unknown_2580.AddItem(value);
    }
}

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

// FUNCTION: GAMEMD 0x42CF10
void Obj_0042CF10::AddPair(unsigned a, unsigned b, int index)
{
    if (a == b)
        return;
    if (b < a)
    {
        unsigned t = b;
        b = a;
        a = t;
    }
    int key = (a << 16) | b;
    unknown_74[index].AddItem(key);
}

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

// FUNCTION: GAMEMD 0x43A700
bool Obj_0043A700::Register(Item_0043A700* item)
{
    if (unknown_04.Count < unknown_20)
    {
        unknown_04.AddItem(item);
        item->unknown_2C = this;
        return true;
    }
    return false;
}

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
#include "scenario_class_methods.h"
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
