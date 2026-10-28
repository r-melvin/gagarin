// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small bodies from
//   the 0x54E000-0x6ABD00 range; receivers are placeholder views of the members touched.
//
// Address index: 0x5BECC0 0x5BCC90

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <string.h>
#include "../ui/load_options_class_methods.h"
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x5BECC0
// Mirror the lower triangle of a 256x256 byte matrix into the upper triangle.
void MirrorMatrix256(unsigned char (*m)[256])
{
    for (int i = 0; i < 255; i++) {
        for (int j = i + 1; j < 256; j++) {
            m[i][j] = m[j][i];
        }
    }
}

// Text-grid message log (80 columns by 25 rows) placeholder view.
struct Obj_005BCC90
{
    char cells[80][25];     // +0x0000
    int attrs[80][25];      // +0x07D0
    char unknown_2710[0x24];
    unsigned char dirty;    // +0x2734
    // FUNCTION: GAMEMD 0x5BD490 (decl; reloc)
    void FUN_005BD490(int a, int b, int c, int d);
    inline void Clear()
    {
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 80; j++) {
                cells[j][i] = ' ';
                attrs[j][i] = 0;
            }
        }
        dirty = 1;
        FUN_005BD490(0, 0, 80, 25);
    }
    // FUNCTION: GAMEMD 0x5BCC90
    void FUN_005BCC90();
};
GG_STATIC_ASSERT(offsetof(Obj_005BCC90, attrs) == 0x7D0);
GG_STATIC_ASSERT(offsetof(Obj_005BCC90, dirty) == 0x2734);

// FUNCTION: GAMEMD 0x5BCC90
// Blank the whole text grid and mark it dirty.
void Obj_005BCC90::FUN_005BCC90()
{
    Clear();
}

// Dialog-window item handlers: the owning object is stored in the window's user data (offset 8).
extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(void* hWnd, int nIndex);
struct Obj_005589F0
{
    char unknown_00[0x18];
    int result;     // +0x18
};
GG_STATIC_ASSERT(offsetof(Obj_005589F0, result) == 0x18);

// FUNCTION: GAMEMD 0x5589F0
// Record which of two buttons (ids 0x686, 0x6C8) was pressed.
void __fastcall FUN_005589F0(void* hWnd, int id, int unused, int notify)
{
    Obj_005589F0* o = (Obj_005589F0*)GetWindowLongA(hWnd, 8);
    switch (id) {
    case 0x686:
        if (notify == 0) {
            o->result = 2;
        }
        break;
    case 0x6C8:
        if (notify == 0) {
            o->result = 1;
        }
        break;
    }
}

// FUNCTION: GAMEMD 0x5D3760
// Record which of three buttons (ids 1-2, 0x5AE, 0x5AF) was pressed.
void __fastcall FUN_005D3760(void* hWnd, int id, int unused, int notify)
{
    int* p = (int*)GetWindowLongA(hWnd, 8);
    switch (id) {
    case 1:
    case 2:
        if (notify == 0) {
            *p = 1;
        }
        break;
    case 0x5AE:
        if (notify == 0) {
            *p = 0;
        }
        break;
    case 0x5AF:
        if (notify == 0) {
            *p = 2;
        }
        break;
    }
}

// GLOBAL: GAMEMD 0xABF168
extern int DAT_00ABF168[];

// FUNCTION: GAMEMD 0x5BC4D0
// Blank every one of the eight text grids.
void FUN_005BC4D0()
{
    for (int i = 0; i < 8; i++) {
        ((Obj_005BCC90*)DAT_00ABF168[i])->Clear();
    }
}

// Message log: record the highlight rectangle and mode, then redraw with the given text.
struct Obj_005BD2A0
{
    char unknown_00[0x2710];
    int mode;               // +0x2710
    char unknown_2714[0x8];
    int left;               // +0x271C
    int top;                // +0x2720
    // FUNCTION: GAMEMD 0x5BD0D0 (decl; reloc)
    void FUN_005BD0D0(const char* text);
    // FUNCTION: GAMEMD 0x5BD2A0
    void FUN_005BD2A0(const char* text, int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(Obj_005BD2A0, mode) == 0x2710);
GG_STATIC_ASSERT(offsetof(Obj_005BD2A0, left) == 0x271C);
GG_STATIC_ASSERT(offsetof(Obj_005BD2A0, top) == 0x2720);

// GLOBAL: GAMEMD 0xABF23A
extern unsigned char DAT_00ABF23A;

// FUNCTION: GAMEMD 0x5BD2A0
void Obj_005BD2A0::FUN_005BD2A0(const char* text, int a, int b, int c)
{
    if (DAT_00ABF23A) {
        left = a;
        top = b;
        if (DAT_00ABF23A) {
            mode = c;
        }
        FUN_005BD0D0(text);
    }
}

// Zero-initialised record view for 0x58BDC0.
struct Obj_0058BDC0
{
    short unknown_00;
    short unknown_02;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1C;
    int unknown_20;
    int unknown_24;
    int unknown_28;
    int unknown_2C;
    int unknown_30;
    int unknown_34;
    int unknown_38;
    int unknown_3C;
    int unknown_40;
    unsigned char unknown_44;
    unsigned char unknown_45;
    unsigned char unknown_46;
    unsigned char unknown_47;
    unsigned char unknown_48;
    unsigned char unknown_49;
    unsigned char unknown_4A;
    unsigned char unknown_4B;
    // FUNCTION: GAMEMD 0x58BDC0
    Obj_0058BDC0();
};
GG_STATIC_ASSERT(offsetof(Obj_0058BDC0, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(Obj_0058BDC0, unknown_4A) == 0x4A);

// FUNCTION: GAMEMD 0x58BDC0
// Zero the record, set the +0x40 slot to -1 and the byte at +0x4A to 1.
Obj_0058BDC0::Obj_0058BDC0()
{
    unknown_08 = 0;
    unknown_10 = 0;
    unknown_18 = 0;
    unknown_20 = 0;
    unknown_28 = 0;
    unknown_30 = 0;
    unknown_00 = 0;
    unknown_02 = 0;
    unknown_0C = 0;
    unknown_14 = 0;
    unknown_1C = 0;
    unknown_24 = 0;
    unknown_2C = 0;
    unknown_34 = 0;
    unknown_38 = 0;
    unknown_3C = 0;
    unknown_40 = -1;
    unknown_44 = 0;
    unknown_45 = 0;
    unknown_46 = 0;
    unknown_47 = 0;
    unknown_48 = 0;
    unknown_49 = 0;
    unknown_4A = 1;
    unknown_4B = 0;
}

// FUNCTION: GAMEMD 0x558840
// LoadOptionsClass::DeleteDialog: open the savegame browser in Delete mode (no save description),
// then tail-call the shared dialog worker. Written as a free function so the shared class view
// needs no new member.
bool __fastcall FUN_00558840(LoadOptionsClass* self)
{
    self->Mode = LOM_Delete;
    self->Description = 0;
    return self->ProcessDialog();
}

// Window-title lookup and the accelerator-tracker list (globals shared with the window list).
struct HWND__;
extern "C" __declspec(dllimport) int __stdcall GetWindowTextA(HWND__* hWnd, char* text, int maxCount);

// GLOBAL: GAMEMD 0xABFC90
extern DynamicVectorClass<HWND__*> DAT_00ABFC90;
// GLOBAL: GAMEMD 0xABFCD0
extern char DAT_00ABFCD0[];

// FUNCTION: GAMEMD 0x5D4F20
// Find the tracked window whose title equals the text; null when none does.
HWND__* __fastcall FUN_005D4F20(const char* title)
{
    for (int i = 0; i < DAT_00ABFC90.Count; i++) {
        GetWindowTextA(DAT_00ABFC90.Items[i], DAT_00ABFCD0, 99);
        if (strcmp(DAT_00ABFCD0, title) == 0) {
            return DAT_00ABFC90.Items[i];
        }
    }
    return 0;
}

// View of the tracker vector (8-byte records): vtable slot 2 grows the array.
struct TrackerRec_005D4FA0
{
    int key;        // +0x00
    int value;      // +0x04
};

class TrackerVec_005D4FA0
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual bool SetCapacity(int capacity, void* memory);   // slot 2
    TrackerRec_005D4FA0* Items; // +0x04
    int Capacity;           // +0x08
    bool IsInitialized;     // +0x0C
    bool IsAllocated;       // +0x0D
    char unknown_0E[2];
    int Count;              // +0x10
    int CapacityIncrement;  // +0x14
};
GG_STATIC_ASSERT(offsetof(TrackerVec_005D4FA0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TrackerVec_005D4FA0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(TrackerVec_005D4FA0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TrackerVec_005D4FA0, CapacityIncrement) == 0x14);

// GLOBAL: GAMEMD 0xABFCB8
extern TrackerVec_005D4FA0 DAT_00ABFCB8;

// FUNCTION: GAMEMD 0x5D4FA0
// Append an (second, first) record to the tracker list, growing it when allowed.
void __fastcall FUN_005D4FA0(int first, int second)
{
    TrackerVec_005D4FA0& v = DAT_00ABFCB8;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            int inc = v.CapacityIncrement;
            if (!v.SetCapacity(v.Capacity + inc, 0)) {
                return;
            }
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index].key = second;
    v.Items[index].value = first;
}

// FUNCTION: GAMEMD 0x5D5010
// Remove the tracker record with the given key, closing the gap; answers the index reached.
int __fastcall FUN_005D5010(int key)
{
    TrackerVec_005D4FA0& v = DAT_00ABFCB8;
    int i;
    for (i = 0; i < v.Count; i++) {
        if (v.Items[i].key == key) {
            break;
        }
    }
    if (i < v.Count) {
        v.Count--;
        for (; i < v.Count; i++) {
            v.Items[i] = v.Items[i + 1];
        }
    }
    return i;
}

// GLOBAL: GAMEMD 0xABF23C
extern int DAT_00ABF23C;

// FUNCTION: GAMEMD 0x5BCCF0
// Make this grid the active one (blanking it on a switch), then redraw the whole grid.
void __fastcall FUN_005BCCF0(Obj_005BCC90* self)
{
    if (DAT_00ABF23A) {
        if (DAT_00ABF23C != (int)self) {
            DAT_00ABF23C = (int)self;
            self->Clear();
        }
        self->FUN_005BD490(0, 0, 80, 25);
    }
}

// FUNCTION: GAMEMD 0x5BC460
// Make grid number `index` the active one, blank it and redraw it.
void __fastcall FUN_005BC460(int index)
{
    Obj_005BCC90* grid = (Obj_005BCC90*)DAT_00ABF168[index];
    DAT_00ABF23C = (int)grid;
    grid->Clear();
    ((Obj_005BCC90*)DAT_00ABF23C)->FUN_005BD490(0, 0, 80, 25);
}

// LIBRARY: GAMEMD 0x7C8EF4 -- sprintf.
// STRING: GAMEMD 0x82D020 -- "%S"
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

struct Obj_005BD2E0
{
    char unknown_00[0x2710];
    int mode;               // +0x2710
    char unknown_2714[0x8];
    int left;               // +0x271C
    int top;                // +0x2720
    // FUNCTION: GAMEMD 0x5BD0D0 (decl; reloc)
    void FUN_005BD0D0(const char* text);
    // FUNCTION: GAMEMD 0x5BD2E0
    void FUN_005BD2E0(const wchar_t* text, int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(Obj_005BD2E0, mode) == 0x2710);
GG_STATIC_ASSERT(offsetof(Obj_005BD2E0, top) == 0x2720);

// FUNCTION: GAMEMD 0x5BD2E0
// Print a wide string into the log at a position with a mode.
void Obj_005BD2E0::FUN_005BD2E0(const wchar_t* text, int a, int b, int c)
{
    char buffer[0x400];
    if (DAT_00ABF23A) {
        left = a;
        top = b;
        if (DAT_00ABF23A) {
            mode = c;
        }
        sprintf(buffer, "%S", text);
        FUN_005BD0D0(buffer);
    }
}

// GLOBAL: GAMEMD 0xABF240
extern int DAT_00ABF240;
// GLOBAL: GAMEMD 0xABF244
extern int DAT_00ABF244;

// FUNCTION: GAMEMD 0x53E420 (decl; reloc)
void __fastcall FUN_0053E420(int window);
extern "C" __declspec(dllimport) int __stdcall DeleteObject(int object);
extern "C" __declspec(dllimport) int __stdcall DestroyWindow(int window);

// FUNCTION: GAMEMD 0x5BC300
// Free the eight text grids, then release the log window and its GDI object.
void FUN_005BC300()
{
    for (int i = 0; i < 8; i++) {
        if (DAT_00ABF168[i]) {
            delete (void*)DAT_00ABF168[i];
            DAT_00ABF168[i] = 0;
        }
    }
    if (DAT_00ABF240) {
        DeleteObject(DAT_00ABF244);
        FUN_0053E420(DAT_00ABF240);
        DestroyWindow(DAT_00ABF240);
        DAT_00ABF244 = 0;
        DAT_00ABF240 = 0;
    }
}

// Linear-congruential generator view (single seed word at +0x00).
class LCGRandom_0065C660
{
public:
    // FUNCTION: GAMEMD 0x65C660
    int RandomRanged(int min, int max);

    unsigned long Seed;   // +0x00
};
GG_STATIC_ASSERT(offsetof(LCGRandom_0065C660, Seed) == 0x00);

// FUNCTION: GAMEMD 0x65C660
// Uniform integer in [min,max] by rejection sampling over a 15-bit draw.
int LCGRandom_0065C660::RandomRanged(int min, int max)
{
    int hi = max;
    int lo = min;
    if (min == max) {
        return min;
    }
    if (min > max) {
        lo = max;
        hi = min;
    }
    int magnitude = hi - lo;
    int highbit = 14;
    while ((magnitude & (1 << highbit)) == 0 && highbit > 0) {
        --highbit;
    }
    int mask = ~(-1 << (highbit + 1));
    int pick = magnitude + 1;
    while (pick > magnitude) {
        Seed = Seed * 0x41C64E6D + 0x3039;
        pick = (Seed >> 10) & 0x7FFF;
        pick &= mask;
    }
    return pick + lo;
}

// Pixel-format shift tables (one shift pair per colour channel).
// GLOBAL: GAMEMD 0x8A0DD0
extern int DAT_008A0DD0;
// GLOBAL: GAMEMD 0x8A0DD4
extern int DAT_008A0DD4;
// GLOBAL: GAMEMD 0x8A0DD8
extern int DAT_008A0DD8;
// GLOBAL: GAMEMD 0x8A0DDC
extern int DAT_008A0DDC;
// GLOBAL: GAMEMD 0x8A0DE0
extern int DAT_008A0DE0;
// GLOBAL: GAMEMD 0x8A0DE4
extern int DAT_008A0DE4;

// FUNCTION: GAMEMD 0x620810
// Pack a 0x00BBGGRR colour into the display's pixel format; -1 passes through.
unsigned int __fastcall FUN_00620810(unsigned int colour)
{
    if (colour == 0xFFFFFFFF) {
        return colour;
    }
    unsigned int red = colour & 0xFF;
    unsigned int green = (colour >> 8) & 0xFF;
    unsigned int blue = (colour >> 16) & 0xFF;
    return ((int)red >> DAT_008A0DD4 << DAT_008A0DD0)
         | ((green >> DAT_008A0DE4 << DAT_008A0DE0) | (blue >> DAT_008A0DDC << DAT_008A0DD8));
}

// FUNCTION: GAMEMD 0x620870
// PARTIAL: 84.4% (retail masks the blue and green bytes before OR-ing the 0x200 flag into blue's
// result; here the flag OR is scheduled between the masks -- same instruction multiset)
// Unpack a display pixel into a palette-relative colour (0x02BBGGRR).
struct Rgb3_00620870 { unsigned char r, g, b; };
unsigned int __fastcall FUN_00620870(unsigned short pixel)
{
    Rgb3_00620870 c;
    c.r = (pixel >> *(unsigned short*)&DAT_008A0DD0) << DAT_008A0DD4;
    c.g = (pixel >> *(unsigned short*)&DAT_008A0DE0) << DAT_008A0DE4;
    c.b = (pixel >> *(unsigned short*)&DAT_008A0DD8) << DAT_008A0DDC;
    return 0x02000000 | ((c.b << 16) | (c.g << 8) | c.r);
}
