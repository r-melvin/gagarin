// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   Receivers that RTTI does not name keep a placeholder derived from the address.
//
// Round 14 small unowned leaves between 0x403000 and 0x550000, ascending by retail
// address. Address index (in file order):
//   0x402900 0x4202F0 0x425630 0x487EE0 0x48BA10 0x48DEE0 0x4CA180 0x4F4EB0 0x53E470 0x544E30 0x549A00
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../platform/debug_window_list_methods.h"

// ---------------------------------------------------------------------------
// 0x402900: run the update callback of every enabled node of the global list.
struct ListNode_00402900
{
    ListNode_00402900* Next;     // +0x00
    char               Pad_04[8];
    unsigned char      Flags;    // +0x0C -- bit 1 set = skip this node
    char               Pad_0D[0x10C - 0x0D];
    void (__fastcall *Callback)(ListNode_00402900* self);  // +0x10C
};
GG_STATIC_ASSERT(offsetof(ListNode_00402900, Flags) == 0x0C);
GG_STATIC_ASSERT(offsetof(ListNode_00402900, Callback) == 0x10C);

struct ListHolder_00402900
{
    char               Pad_00[0x0C];
    ListNode_00402900* First;    // +0x0C -- circular list; the head sentinel is this address
    char               Pad_10[8];
    int                Busy;     // +0x18
};
GG_STATIC_ASSERT(offsetof(ListHolder_00402900, First) == 0x0C);
GG_STATIC_ASSERT(offsetof(ListHolder_00402900, Busy) == 0x18);

extern int DAT_0087DE2C;                    // GAMEMD 0x0087DE2C
extern ListHolder_00402900* DAT_00815E98;   // GAMEMD 0x00815E98

// FUNCTION: GAMEMD 0x402900
void FUN_00402900()
{
    if (DAT_0087DE2C != 0 && DAT_00815E98->Busy == 0) {
        ListNode_00402900* head = (ListNode_00402900*)&DAT_00815E98->First;
        for (ListNode_00402900* node = DAT_00815E98->First; node != head; node = node->Next) {
            if ((node->Flags & 2) == 0)
                node->Callback(node);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x4202F0: fill a 64K-entry table of 8-bit shades (high byte of each ushort) scaled to `limit`.
struct ShadeTable_004202F0
{
    unsigned short Values[0x10000];  // +0x00000
    int            Limit;            // +0x20000
    int            Reserved;         // +0x20004
    // Returns this.
    ShadeTable_004202F0* Fill(int limit);
};
GG_STATIC_ASSERT(offsetof(ShadeTable_004202F0, Limit) == 0x20000);
GG_STATIC_ASSERT(offsetof(ShadeTable_004202F0, Reserved) == 0x20004);

// FUNCTION: GAMEMD 0x4202F0
ShadeTable_004202F0* ShadeTable_004202F0::Fill(int limit)
{
    Limit = limit;
    Reserved = 0;
    int max = limit - 1;
    for (int i = 0; i <= 0xFFFF; i++) {
        int v = ((i & 0xFF) * (i >> 8) * max) / 0x7E02;
        if (v > max)
            v = max;
        Values[i] = (unsigned short)((unsigned char)v << 8);
    }
    return this;
}

// ---------------------------------------------------------------------------
// 0x425630: the object's third coordinate component plus that of the object it is linked to.
struct Coord3_00425630
{
    int X;
    int Y;
    int Z;
};

struct Linked_00425630
{
    char             Pad_00[0x9C];
    Coord3_00425630  Location;   // +0x9C
    char             Pad_A8[0xCC - 0xA8];
    Linked_00425630* Link;       // +0xCC
    int Height();
};
GG_STATIC_ASSERT(offsetof(Linked_00425630, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(Linked_00425630, Link) == 0xCC);

// FUNCTION: GAMEMD 0x425630
int Linked_00425630::Height()
{
    Coord3_00425630 c = Location;
    int result = c.Z;
    if (Link) {
        Coord3_00425630 d = Link->Location;
        result += d.Z;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x487EE0: rectangle shifted back by a point (origin subtracted, extent kept).
struct Pt_00487EE0
{
    int X;
    int Y;
    Pt_00487EE0(int x, int y) : X(x), Y(y) {}
    Pt_00487EE0 operator-(const Pt_00487EE0& o) const { return Pt_00487EE0(X - o.X, Y - o.Y); }
};

struct Rect_00487EE0
{
    int X;  // +0x00
    int Y;  // +0x04
    int W;  // +0x08
    int H;  // +0x0C
    Rect_00487EE0(int x, int y, int w, int h) : X(x), Y(y), W(w), H(h) {}
    Rect_00487EE0 Shift(const Pt_00487EE0& origin) const;
};
GG_STATIC_ASSERT(sizeof(Rect_00487EE0) == 0x10);

// FUNCTION: GAMEMD 0x487EE0
Rect_00487EE0 Rect_00487EE0::Shift(const Pt_00487EE0& origin) const
{
    Pt_00487EE0 p = Pt_00487EE0(X, Y) - origin;
    return Rect_00487EE0(p.X, p.Y, W, H);
}

// ---------------------------------------------------------------------------
// 0x48BA10: running average over up to 256 samples, plus the largest sample seen.
struct RunAvg_0048BA10
{
    char         Pad_00[0x14];
    unsigned int Sum;     // +0x14
    unsigned int Count;   // +0x18
    unsigned int Average; // +0x1C
    unsigned int Max;     // +0x20
    void Add(unsigned int sample);
};
GG_STATIC_ASSERT(offsetof(RunAvg_0048BA10, Sum) == 0x14);
GG_STATIC_ASSERT(offsetof(RunAvg_0048BA10, Max) == 0x20);

// FUNCTION: GAMEMD 0x48BA10
void RunAvg_0048BA10::Add(unsigned int sample)
{
    unsigned int avg;
    unsigned int round = 0;
    if (Count == 0x100) {
        Sum += sample - Average;
        if ((Sum & 0xFF) > 0x7F)
            round = 1;
        avg = (Sum >> 8) + round;
    } else {
        Count++;
        Sum += sample;
        avg = Sum / Count;
    }
    Average = avg;
    if (sample > Max)
        Max = sample;
}

// ---------------------------------------------------------------------------
// 0x48DEE0: copy a cell list up to and including its 0x7FFF,0x7FFF terminator.
// When the count runs out first, the last copied slot is overwritten by the terminator.
// FUNCTION: GAMEMD 0x48DEE0
void __fastcall FUN_0048DEE0(CellStruct* src, int count, CellStruct* dest)
{
    if (src == 0 || dest == 0)
        return;
    for (; count > 0; count--) {
        *dest = *src;
        if (dest->X == 0x7FFF && dest->Y == 0x7FFF)
            return;
        dest++;
        src++;
    }
    CellStruct end;
    end.X = 0x7FFF;
    end.Y = 0x7FFF;
    dest[-1] = end;
}

// ---------------------------------------------------------------------------
// 0x4CA180: progress ratio of a production timer (0 when nothing is being built).
struct Factory_004CA180
{
    char Pad_00[0x24];
    int  Rate;      // +0x24
    char Pad_28[0x58 - 0x28];
    void* Object;   // +0x58
    char Pad_5C[4];
    int  Value;     // +0x60
    int Scaled() const;
};
GG_STATIC_ASSERT(offsetof(Factory_004CA180, Rate) == 0x24);
GG_STATIC_ASSERT(offsetof(Factory_004CA180, Object) == 0x58);
GG_STATIC_ASSERT(offsetof(Factory_004CA180, Value) == 0x60);

// FUNCTION: GAMEMD 0x4CA180
int Factory_004CA180::Scaled() const
{
    if (Object != 0) {
        int divisor = 0x36 - Rate;
        int v = Value;
        if (divisor == 0)
            return v;
        return v / divisor;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x4F4EB0: squeeze 4-byte pixels to 3 bytes in place by dropping the first byte of each.
// FUNCTION: GAMEMD 0x4F4EB0
void __fastcall FUN_004F4EB0(unsigned char* pixels, int a, int b, int c)
{
    unsigned int n = a * b * c;
    unsigned char* src = pixels;
    unsigned char* dst = pixels;
    for (; n > 0; n--) {
        unsigned char c0 = *++src;
        src++;
        *dst++ = c0;
        unsigned char c1 = *src++;
        *dst++ = c1;
        unsigned char c2 = *src++;
        *dst++ = c2;
    }
}

// ---------------------------------------------------------------------------
// 0x53E470: slot index of a registered window, remembering the last lookup.
extern int DebugWindowLastKey;    // GAMEMD 0x00AA0470
extern int DebugWindowLastIndex;  // GAMEMD 0x00AA0474

// FUNCTION: GAMEMD 0x53E470
int __fastcall FUN_0053E470(int window)
{
    if (DebugWindowListActive != 0) {
        int last = DebugWindowLastKey;
        int* slots = (int*)DebugWindowList;
        if (window == last)
            return DebugWindowLastIndex;
        int i = 0;
        for (; i < DebugWindowListCapacity; i++) {
            if (slots[i] == window) {
                DebugWindowLastKey = window;
                DebugWindowLastIndex = i;
                return i;
            }
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x544E30: add up the second field of every entry whose first field is not above the index.
struct TileStep_00544E30
{
    int Limit;   // +0x00
    int Add;     // +0x04
};
extern TileStep_00544E30** DAT_00AA107C;  // GAMEMD 0x00AA107C
extern int DAT_00AA1088;                  // GAMEMD 0x00AA1088

// FUNCTION: GAMEMD 0x544E30
int __fastcall FUN_00544E30(int index)
{
    int result = index;
    if (index == 0xFFFF)
        return result;
    for (int i = 0; i < DAT_00AA1088; i++) {
        TileStep_00544E30* e = DAT_00AA107C[i];
        if (e->Limit > index)
            break;
        result += e->Add;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x549A00: isometric cell offset to pixel offset (30 per cell across, 15 down).
// FUNCTION: GAMEMD 0x549A00
void __fastcall FUN_00549A00(int a, int b, int* outX, int* outY)
{
    *outX = (a * 60) / 2;
    *outY = (a * 30) / 2;
    *outX += (b * -60) / 2;
    *outY += (b * 30) / 2;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0374
int DebugWindowListCapacity;
// GLOBAL: GAMEMD 0xAA044C
void** DebugWindowList;
// GLOBAL: GAMEMD 0xAA0470
int DebugWindowLastKey;
// GLOBAL: GAMEMD 0xAA0474
int DebugWindowLastIndex;
// GLOBAL: GAMEMD 0xAA107C
TileStep_00544E30** DAT_00AA107C;
// GLOBAL: GAMEMD 0xAA1088
int DAT_00AA1088;
// GLOBAL: GAMEMD 0x87DE2C
int DAT_0087DE2C = 0;
// GLOBAL: GAMEMD 0xAA0448
int DebugWindowListActive;
// END defined globals
