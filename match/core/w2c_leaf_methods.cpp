// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Small leaf routines read from retail gamemd.exe v1.001; each owner is a placeholder
// `Obj_<ADDR>` pinned by offsetof asserts. Each address is verified separately.
// Address index: 0x597A10 0x5B4400 0x5BC3C0 0x5C0080 0x5C00C0 0x5C1D80 0x5C21A0 0x5C2640
//   0x5C2680 0x5C2CB0 0x5C2CE0 0x5C3F30 0x5C4670 0x5C4E90 0x5C6080 0x5CAF70 0x5CAFB0 0x5D1E50
//   0x5DB650 0x5F3540 0x5F3560 0x5F35A0 0x600630 0x622440 0x6225E0 0x622610 0x64AAA0 0x65BE90
//   0x660B80 0x6612C0 0x68EC00 0x690FC0 0x693B50 0x69EA30 0x6A83E0 0x6A94B0

#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x00693B50
// A duration by kind: 0x2A30 for kind 4, otherwise 0xE10.
int FUN_00693B50(int kind)
{
    switch (kind) {
    case 3:
        return 0xE10;
    case 4:
        return 0x2A30;
    default:
        return 0xE10;
    }
}

// GLOBAL: GAMEMD 0x88730C
extern void* DAT_0088730C;
// GLOBAL: GAMEMD 0x8A00A0
extern bool DAT_008A00A0;

struct Obj_005D1E50 {
    void FUN_005D1E50();
    void FUN_005D1E70(void* surface);
};

// FUNCTION: GAMEMD 0x005D1E50
// Raise the flag and hand the global surface to the sibling routine.
void Obj_005D1E50::FUN_005D1E50()
{
    DAT_008A00A0 = true;
    FUN_005D1E70(DAT_0088730C);
}

void* FUN_00775940(int size);
void FUN_005EC880(void* self, int a, char b, char c);

// FUNCTION: GAMEMD 0x005DB650
// Make a 0xBC-byte object through the allocator helper and initialise it.
void FUN_005DB650(int a, char b, char c)
{
    void* obj = FUN_00775940(0xBC);
    FUN_005EC880(obj, a, b, c);
}

// A wide string handle whose constructor is out of line.
struct WStr_007B66C0 {
    wchar_t* Buffer;
    void FUN_007B66C0();
};

struct Obj_00600630 {
    int Field00;          // +0x00
    WStr_007B66C0 A;      // +0x04
    WStr_007B66C0 B;      // +0x08
    int Field0C;          // +0x0C
    int Field10;          // +0x10
    int Field14;          // +0x14
    Obj_00600630* FUN_00600630();
};
GG_STATIC_ASSERT(offsetof(Obj_00600630, B) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_00600630, Field14) == 0x14);

// FUNCTION: GAMEMD 0x00600630
// Construct two empty strings and reset the three cursors to "none".
Obj_00600630* Obj_00600630::FUN_00600630()
{
    A.FUN_007B66C0();
    B.FUN_007B66C0();
    Field00 = 0;
    Field0C = -1;
    Field14 = -1;
    Field10 = 0;
    return this;
}

// A buffer pointer and an "owned" flag.
struct Obj_005B4400 {
    unsigned char unknown_00[0x12];
    bool Owned;                     // +0x12
    unsigned char unknown_13[0x11];
    void* Buffer;                   // +0x24
    void FUN_005B4400();
};
GG_STATIC_ASSERT(offsetof(Obj_005B4400, Owned) == 0x12);
GG_STATIC_ASSERT(offsetof(Obj_005B4400, Buffer) == 0x24);

// FUNCTION: GAMEMD 0x005B4400
// Free the buffer when this object owns it, then forget it.
void Obj_005B4400::FUN_005B4400()
{
    if (Buffer != 0 && Owned) {
        ::operator delete(Buffer);
    }

    Buffer = 0;
    Owned = false;
}

#include "../_layout/clock_006c8c40.h"
#include "../_layout/map_0087f7e8.h"

struct Obj_00690FC0 {
    unsigned char unknown_00[0x0C];
    int Stamp;                      // +0x0C
    Clock_006C8C40 Clock;           // +0x10
    void FUN_00690FC0();
};
GG_STATIC_ASSERT(offsetof(Obj_00690FC0, Stamp) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_00690FC0, Clock) == 0x10);

// FUNCTION: GAMEMD 0x00690FC0
// Stamp the time the first time only (a stamp of -1 means unset).
void Obj_00690FC0::FUN_00690FC0()
{
    if (Stamp == -1) {
        Stamp = Clock.GetTime();
    }
}

// A target with a run of virtual slots; only the ones reached are named.
class Target_005F3540 {
public:
    virtual void S00(); virtual void S01(); virtual int Slot02(int a, int b, int c, int d);
    virtual void S03(); virtual int Slot04(int a, int b);
};

struct Obj_005F3540 {
    virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
    virtual void S04(); virtual void S05(); virtual void S06(); virtual void S07();
    virtual void S08(); virtual void S09(); virtual void S10(); virtual void S11();
    virtual void S12();
    virtual void Slot13(int a, int b, int c, int d);
    unsigned char unknown_04[0x34];
    Target_005F3540* Target;        // +0x38
    int Enabled;                    // +0x3C
    unsigned char unknown_40[0x28];
    int Failures;                   // +0x68
    void FUN_005F3540(int a, int b, int c);
    int FUN_005F3560(int a, int b, int c, int d);
    int FUN_005F35A0(int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(Obj_005F3540, Target) == 0x38);
GG_STATIC_ASSERT(offsetof(Obj_005F3540, Enabled) == 0x3C);
GG_STATIC_ASSERT(offsetof(Obj_005F3540, Failures) == 0x68);

// FUNCTION: GAMEMD 0x005F3540
// Forward to virtual slot 13 with a trailing 1.
void Obj_005F3540::FUN_005F3540(int a, int b, int c)
{
    Slot13(a, b, c, 1);
}

// FUNCTION: GAMEMD 0x005F3560
// Pass the call to the target; count a failure when it answers zero.
int Obj_005F3540::FUN_005F3560(int a, int b, int c, int d)
{
    if (Enabled == 0) {
        return 0;
    }

    int r = Target->Slot02(a, b, c, 0);
    if (r == 0) {
        Failures++;
    }

    return r;
}

// FUNCTION: GAMEMD 0x005F35A0
// Pass the first two arguments to the target (the third is unused).
int Obj_005F3540::FUN_005F35A0(int a, int b, int c)
{
    if (Enabled == 0) {
        return 0;
    }

    return Target->Slot04(a, b);
}

// FUNCTION: GAMEMD 0x00622440
// Mark the whole window dirty and repaint it now.
int __stdcall FUN_00622440(HWND hwnd, RECT* rect)
{
    InvalidateRect(hwnd, rect, 0);
    UpdateWindow(hwnd);
    return 1;
}

// A two-state object with a "busy" query at slot 7 and enter/leave at 5 and 6.
class Gate_006225E0 {
public:
    virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
    virtual void S04();
    virtual void Enter();      // slot 5
    virtual void Leave();      // slot 6
    virtual char IsOn();       // slot 7
};

// GLOBAL: GAMEMD 0x887640
extern Gate_006225E0* DAT_00887640;
// GLOBAL: GAMEMD 0xAC48EC
extern int DAT_00AC48EC;

// FUNCTION: GAMEMD 0x006225E0
// Nest one level deeper, switching the gate off the first time if it was on.
int FUN_006225E0()
{
    if (DAT_00887640 != 0) {
        if (DAT_00887640->IsOn() == 1) {
            DAT_00887640->Enter();
        }
    }

    DAT_00AC48EC = DAT_00AC48EC + 1;
    return DAT_00AC48EC;
}

// FUNCTION: GAMEMD 0x00622610
// Leave one level; at the outermost level switch the gate back on if it is off.
int FUN_00622610()
{
    if (DAT_00AC48EC > 0) {
        DAT_00AC48EC = DAT_00AC48EC - 1;
    }

    if (DAT_00AC48EC == 0 && DAT_00887640 != 0) {
        if (DAT_00887640->IsOn() == 0) {
            DAT_00887640->Leave();
        }
    }

    return DAT_00AC48EC;
}

// FUNCTION: GAMEMD 0x005CAF70
// The performance-counter frequency: low word returned, high word stored.
DWORD __fastcall FUN_005CAF70(LONG* high)
{
    LARGE_INTEGER freq;
    if (QueryPerformanceFrequency(&freq)) {
        *high = freq.HighPart;
        return freq.LowPart;
    }

    *high = 0;
    return 0;
}

struct Obj_005C2CE0 {
    void FUN_005C2CE0(int a, int b);
    void FUN_005D6540(int a, int b);
};

// FUNCTION: GAMEMD 0x005C2CE0
// Forward both arguments, unchanged, to the sibling routine.
void Obj_005C2CE0::FUN_005C2CE0(int a, int b)
{
    FUN_005D6540(a, b);
}

// FUNCTION: GAMEMD 0x0064AAA0
// Keep a list box to 50 entries: when it has more, drop the first, then
// select the last remaining one.
void __fastcall FUN_0064AAA0(HWND list)
{
    int count = (int)SendMessageA(list, 0x18B, 0, 0);
    if (count > 0x32) {
        SendMessageA(list, 0x182, 0, 0);
        count--;
    }

    SendMessageA(list, 0x197, count - 1, 0);
}

// An embedded polymorphic part with a lookup at slot 4.
class Part_0068EC00 {
public:
    virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
    virtual int Lookup(int* key);
};

struct Obj_0068EC00 {
    unsigned char unknown_00[0x1C];
    Part_0068EC00 Part;             // +0x1C
    bool FUN_0068EC00(int key);
};
GG_STATIC_ASSERT(offsetof(Obj_0068EC00, Part) == 0x1C);

// FUNCTION: GAMEMD 0x0068EC00
// True when the part's lookup of the key comes back -1.
bool Obj_0068EC00::FUN_0068EC00(int key)
{
    bool r = Part.Lookup(&key) == -1;
    return r;
}

struct Sub_0069D9E0 {
    void FUN_0069D9E0(unsigned int* p);
};

struct Obj_0069EA30 {
    unsigned char unknown_00[0x10];
    Sub_0069D9E0 Sub;               // +0x10
    void FUN_0069EA30(unsigned int* p);
};
GG_STATIC_ASSERT(offsetof(Obj_0069EA30, Sub) == 0x10);

// FUNCTION: GAMEMD 0x0069EA30
// Forward to the sub-object at +0x10.
void Obj_0069EA30::FUN_0069EA30(unsigned int* p)
{
    Sub.FUN_0069D9E0(p);
}

// GLOBAL: GAMEMD 0xA8EB68
extern LPARAM DAT_00A8EB68;

// FUNCTION: GAMEMD 0x005C21A0
// Post the "set" message to dialog item 0x732, if the dialog has one.
void __stdcall FUN_005C21A0(HWND dialog)
{
    HWND item = GetDlgItem(dialog, 0x732);
    if (item != 0) {
        PostMessageA(item, 0x405, 1, DAT_00A8EB68);
    }
}

// GLOBAL: GAMEMD 0xABF238
extern bool DAT_00ABF238;
// GLOBAL: GAMEMD 0xABF23A
extern bool DAT_00ABF23A;
// GLOBAL: GAMEMD 0xABF234
extern HWND DAT_00ABF234;
// GLOBAL: GAMEMD 0xABF240
extern HWND DAT_00ABF240;
void FUN_005BC530();

// FUNCTION: GAMEMD 0x005BC3C0
// Show the debug window (creating it on first use) and give it the focus.
void FUN_005BC3C0()
{
    if (DAT_00ABF238) {
        if (DAT_00ABF240 == 0) {
            FUN_005BC530();
        }

        DAT_00ABF23A = true;
        ShowWindow(DAT_00ABF240, 1);
        SetFocus(DAT_00ABF234);
    }
}

void __fastcall FUN_00759E10(void* p);

// FUNCTION: GAMEMD 0x005C00C0
// Forward the pointed-to object when there is one.
void __fastcall FUN_005C00C0(void** pp)
{
    if (pp != 0 && *pp != 0) {
        FUN_00759E10(*pp);
    }
}

struct Target_00554AA0 {
    unsigned char unknown_00[0x24];
    int Field24;                    // +0x24
    void FUN_00554AA0(int a, int b, int c, int d, char e);
};
GG_STATIC_ASSERT(offsetof(Target_00554AA0, Field24) == 0x24);

struct Obj_0065BE90 {
    unsigned char unknown_00[0x24];
    Target_00554AA0* Target;        // +0x24
    unsigned char unknown_28[0x30];
    int Left;                       // +0x58
    int Top;                        // +0x5C
    int Width;                      // +0x60
    unsigned char unknown_64[4];
    int Offset;                     // +0x68
    int Divisor;                    // +0x6C
    int Multiplier;                 // +0x70
    void FUN_0065BE90();
};
GG_STATIC_ASSERT(offsetof(Obj_0065BE90, Target) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_0065BE90, Left) == 0x58);
GG_STATIC_ASSERT(offsetof(Obj_0065BE90, Offset) == 0x68);
GG_STATIC_ASSERT(offsetof(Obj_0065BE90, Multiplier) == 0x70);

// FUNCTION: GAMEMD 0x0065BE90
// Pass the target the scaled rectangle (left, top, width scaled by the ratio).
void Obj_0065BE90::FUN_0065BE90()
{
    int m = Multiplier;
    int d = Divisor;
    Target->FUN_00554AA0(Target->Field24 - Offset, Left * m / d, Top * m / d,
                         Width * m / d, 0);
}

// GLOBAL: GAMEMD 0xABF3F4
extern void* DAT_00ABF3F4;
struct Obj_00759C30 {
    char FUN_00759C30(char flag);
};

// FUNCTION: GAMEMD 0x005C0080
// Run the routine once at a time: refuse while already inside.
char __fastcall FUN_005C0080(Obj_00759C30** self, char flag)
{
    if (DAT_00ABF3F4 != 0) {
        return 0;
    }

    DAT_00ABF3F4 = self;
    char r = (*self)->FUN_00759C30(flag);
    DAT_00ABF3F4 = 0;
    return r;
}

// GLOBAL: GAMEMD 0xB04D88 -- ring head, 0xB04DD8 -- last slot touched,
// 0xB04D48 -- the eight ring slots.
extern int DAT_00B04D88;
extern int DAT_00B04DD8;
extern int DAT_00B04D48[];

// FUNCTION: GAMEMD 0x00660B80
// Push a value on the eight-entry ring, advancing the head.
void __fastcall FUN_00660B80(int* value)
{
    int i = (DAT_00B04D88 + 1) % 8;
    DAT_00B04D88 = i;
    DAT_00B04D48[i] = *value;
    DAT_00B04DD8 = i;
}

// A record of fourteen ints; the table at 0xB07E80 holds sixty per group.
struct Rec_00B07E80 {
    int v[14];
};
GG_STATIC_ASSERT(sizeof(Rec_00B07E80) == 0x38);

// GLOBAL: GAMEMD 0xB07E80
extern Rec_00B07E80 DAT_00B07E80[];


struct Obj_006A83E0 {
    unsigned char unknown_00[0x38];
    int Group;                      // +0x38
    void FUN_006A83E0();
};
GG_STATIC_ASSERT(offsetof(Obj_006A83E0, Group) == 0x38);

// FUNCTION: GAMEMD 0x006A83E0
// Hand each of this group's sixty records to the shared handler.
void Obj_006A83E0::FUN_006A83E0()
{
    for (int i = 0; i < 0x3C; i++) {
        DAT_0087F7E8.FUN_004F4450(&DAT_00B07E80[i + Group * 0x3C]);
    }
}

struct Obj_006A94B0 {
    unsigned char unknown_00[0x1C];
    bool Active;                    // +0x1C
    unsigned char unknown_1D[0x1B];
    int Group;                      // +0x38
    void FUN_006A94B0();
};
GG_STATIC_ASSERT(offsetof(Obj_006A94B0, Active) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_006A94B0, Group) == 0x38);

// FUNCTION: GAMEMD 0x006A94B0
// Clear the active flag, then hand each of the group's records to the handler.
void Obj_006A94B0::FUN_006A94B0()
{
    Active = false;
    for (int i = 0; i < 0x3C; i++) {
        DAT_0087F7E8.FUN_004F4450(&DAT_00B07E80[i + Group * 0x3C]);
    }
}

struct Obj_00597A10 {
    virtual void S00();
    virtual char Slot01(int arg);
    char FUN_005587F0();
    char FUN_00597A10(int arg);
};

// FUNCTION: GAMEMD 0x00597A10
// With an argument, ask slot 1; without, ask the local test.
char Obj_00597A10::FUN_00597A10(int arg)
{
    if (arg != 0) {
        return Slot01(arg);
    }

    bool r = FUN_005587F0() != 0;
    return r;
}

// A three-byte colour, blended toward another by a 0..255 weight.
struct Obj_006612C0 {
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02
    void FUN_006612C0(unsigned int weight, const unsigned char* other);
};
GG_STATIC_ASSERT(offsetof(Obj_006612C0, B) == 2);

// FUNCTION: GAMEMD 0x006612C0
// Move each channel toward the other colour by weight/256 of the difference.
void Obj_006612C0::FUN_006612C0(unsigned int weight, const unsigned char* other)
{
    int w = weight & 0xFF;
    R = (unsigned char)(((int)other[0] - (int)R) * w / 256) + R;
    G = (unsigned char)(((int)other[1] - (int)G) * w / 256) + G;
    B = (unsigned char)(((int)other[2] - (int)B) * w / 256) + B;
}

int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);

// FUNCTION: GAMEMD 0x005C6080
// Window-procedure helper: let the shared handler answer; for an unhandled
// command message remember the low word of the command id in the window data.
int __stdcall FUN_005C6080(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        if (msg == 0x111) {
            unsigned int* data = (unsigned int*)GetWindowLongA(h, 8);
            *data = w & 0xFFFF;
        }

        r = 0;
    }

    return r;
}

void* FUN_005E26C0();

struct Obj_005C2CB0 {
    char FUN_005C2CB0();
    void FUN_005C21D0(void* window, char flag);
};

// FUNCTION: GAMEMD 0x005C2CB0
// Find the window (creating a 0xBC6-byte one if absent) and show it.
char Obj_005C2CB0::FUN_005C2CB0()
{
    void* window = FUN_005E26C0();
    if (window == 0) {
        window = FUN_00775940(0xBC6);
        if (window == 0) {
            return 1;
        }
    }

    FUN_005C21D0(window, 1);
    return 1;
}

// An entry of the list at 0xA8DA78; the first int at +0x6B is its own index.
#pragma pack(push, 1)
struct Entry_005C3F30 {
    unsigned char unknown_00[0x6B];
    int Index;                      // +0x6B (unaligned)
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Entry_005C3F30, Index) == 0x6B);

// GLOBAL: GAMEMD 0xA8DA78 (entries), 0xA8DA84 (count)
extern Entry_005C3F30** DAT_00A8DA78;
extern int DAT_00A8DA84;

// The sub-object an options dialog keeps at +0x40.
struct Sub_0049BC80 {
    void FUN_0049B760(void* a, void* b);
    void FUN_0049BC80(void* out);
    void FUN_0049BCA0(int* out);
    void FUN_0049BCC0(int* out);
    char FUN_0049D680();
};

void* __fastcall FUN_004E37D0(int index);
void __fastcall FUN_004E3B90(void* window);

struct Flags_005C4E90 {
    char First;
    char Owned;
};

void __cdecl FUN_004068E0(const char* format, int a, int b);

struct Obj_005C2640 {
    unsigned char unknown_00[0x40];
    Sub_0049BC80* Sub;              // +0x40
    unsigned char unknown_44[0x2F8];
    unsigned char Block[4];         // +0x33C
    bool Dirty;                     // +0x340
    void FUN_005C1D80(int arg);
    void FUN_005C21D0(void* window, char flag);
    void FUN_005C23B0(void* window, void* item);
    void FUN_005C2500(void* window);
    void FUN_005C2640(void* window);
    char FUN_005C2680();
    int FUN_005C4670();
    char FUN_005C4E90(int a, void* buffer, int c, Flags_005C4E90 flags, int e, int f, int* out);
    void FUN_005C3F30();
    void FUN_005D6310(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_005C2640, Sub) == 0x40);
GG_STATIC_ASSERT(offsetof(Obj_005C2640, Block) == 0x33C);
GG_STATIC_ASSERT(offsetof(Obj_005C2640, Dirty) == 0x340);

// FUNCTION: GAMEMD 0x005C1D80
// With exactly two list entries, tell the sub-object about both, then pass on.
void Obj_005C2640::FUN_005C1D80(int arg)
{
    if (DAT_00A8DA84 == 2 && Sub != 0) {
        Sub->FUN_0049B760(DAT_00A8DA78[0], DAT_00A8DA78[1]);
    }

    FUN_005D6310(arg);
}

// FUNCTION: GAMEMD 0x005C2640
// Apply every list item to the window, then finish with the show call.
void Obj_005C2640::FUN_005C2640(void* window)
{
    if (window != 0) {
        int count = DAT_00A8DA84;
        for (int i = 0; i < count; i++) {
            FUN_005C23B0(window, FUN_004E37D0(i));
        }

        FUN_005C21D0(window, 1);
    }
}

// FUNCTION: GAMEMD 0x005C2680
// Refresh the sub-object's block, flush a pending change to the window, and
// answer the sub-object's verdict (0 when there is no sub-object).
char Obj_005C2640::FUN_005C2680()
{
    if (Sub == 0) {
        return 0;
    }

    Sub->FUN_0049BC80(&Block);
    void* window = FUN_005E26C0();
    if (window != 0 && Dirty) {
        FUN_005C2500(window);
        Dirty = false;
    }

    return Sub->FUN_0049D680();
}

// FUNCTION: GAMEMD 0x005C3F30
// Hide and release the window, then renumber every list entry.
void Obj_005C2640::FUN_005C3F30()
{
    void* window = FUN_005E26C0();
    if (window != 0) {
        FUN_005C21D0(window, 0);
        FUN_004E3B90(window);
    }

    for (int i = 0; i < DAT_00A8DA84; i++) {
        DAT_00A8DA78[i]->Index = i;
    }
}

// FUNCTION: GAMEMD 0x005C4670
// When the sub-object's two readings agree, report (and return) the bit mask
// for the shared value; otherwise zero.
int Obj_005C2640::FUN_005C4670()
{
    int mask = 0;
    if (Sub == 0) {
        return 0;
    }

    int low;
    int high;
    Sub->FUN_0049BCA0(&low);
    Sub->FUN_0049BCC0(&high);
    if (low == high) {
        int value;
        Sub->FUN_0049BC80(&value);
        mask = 1 << value;
        FUN_004068E0((const char*)0x0082DFDC, value, mask);
    }

    return mask;
}

// FUNCTION: GAMEMD 0x005C4E90
// Clear the output, free the buffer when flagged as owned, and answer whether
// there is a sub-object.
char Obj_005C2640::FUN_005C4E90(int a, void* buffer, int c, Flags_005C4E90 flags, int e, int f, int* out)
{
    *out = 0;
    if (Sub != 0) {
        if (buffer != 0 && flags.Owned) {
            ::operator delete(buffer);
        }

        return 1;
    }

    if (buffer != 0 && flags.Owned) {
        ::operator delete(buffer);
    }

    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8EB68
LPARAM DAT_00A8EB68;
// GLOBAL: GAMEMD 0xAC48EC
int DAT_00AC48EC;
// END defined globals
