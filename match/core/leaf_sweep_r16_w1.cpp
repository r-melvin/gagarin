// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies disassembled from retail gamemd.exe v1.001 at the addresses below.
//   Receiver types are per-function views (names carry the address) because no
//   canonical class has been recovered for them.

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <new.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/geometry2d.h"
#include "../combat/ion_blast_draw_methods.h"
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x87F914 / 0x87F918 -- map width / height in cells.
extern int DAT_0087F914;
extern int DAT_0087F918;

// FUNCTION: GAMEMD 0x412AC0
// Maps a cell onto a 20x20 grid of map regions (0x14 columns, row-major).
int __stdcall FUN_00412AC0(CellStruct cell)
{
    int x = cell.X < 0 ? 0 : cell.X;
    int y = cell.Y < 0 ? 0 : cell.Y;
    x /= DAT_0087F914 / 20;
    int col = x > 19 ? 19 : x;
    y = y / (DAT_0087F918 / 20);
    if (y > 19) {
        y = 19;
    }
    return col + y * 20;
}

// Receiver of 0x42E0B0: a record of seven caller-supplied words, then zeroed state.
struct Rec_0042E0B0
{
    int F0, F1, F2, F3, F4, F5, F6;   // +0x00..+0x18
    int _pad1C;                       // +0x1C
    int Z20, Z24, Z28, Z2C;           // +0x20..+0x2C
    char Flag;                        // +0x30

    Rec_0042E0B0* FUN_0042E0B0(int a, int b, int c, int d, int e, int f, int g);
};
GG_STATIC_ASSERT(offsetof(Rec_0042E0B0, Flag) == 0x30);

// FUNCTION: GAMEMD 0x42E0B0
// PARTIAL: 77.3% (instruction multiset identical; 5 of 22 differ). Retail loads the
// second argument before the first and sinks the first store; cl keeps source order.
// Variants tried: store order permutations, a 200 s permuter run (no score below 40).
// Fill the seven leading words from the arguments, clear the rest, return this.
Rec_0042E0B0* Rec_0042E0B0::FUN_0042E0B0(int a, int b, int c, int d, int e, int f, int g)
{
    F0 = a;
    F2 = c;
    F4 = e;
    F1 = b;
    F6 = g;
    F3 = d;
    Z20 = 0;
    Z28 = 0;
    F5 = f;
    Z24 = 0;
    Z2C = 0;
    Flag = 0;
    return this;
}

// GLOBAL: GAMEMD 0x89C430 -- the default 3-int value that Obj_00430590 leaves untouched.
extern HeaderCoordInit DAT_0089C430;

// Receiver of 0x430590: a 3-int value at +0x0, a flag byte at +0xC, an index at +0x110.
struct Obj_00430590
{
    int Value[3];        // +0x00
    char Flags;          // +0x0C
    char _pad0D[0x103];  // +0x0D
    int Index;           // +0x110

    void FUN_00430590(int a, int b, int c, int index);
};
GG_STATIC_ASSERT(offsetof(Obj_00430590, Flags) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_00430590, Index) == 0x110);

// FUNCTION: GAMEMD 0x430590
// PARTIAL: 84.6% (multiset identical; 4 of 26 differ). Retail loads the default X
// into EDX before pushing ESI and compares in that order; cl loads it into EDI after
// the pushes. Variants tried: raw-parameter compare (76.9%), temp struct inside the
// branch, per-field stores, and a 300 s permuter run (no improvement on the base).
// Stores the 3-int value unless it equals the default, and records the index
// (setting flag bit 0) when it is below 8.
void Obj_00430590::FUN_00430590(int a, int b, int c, int index)
{
    HeaderCoordInit v(a, b, c);
    if (v.X != DAT_0089C430.X || v.Y != DAT_0089C430.Y || v.Z != DAT_0089C430.Z) {
        *(CoordStruct*)Value = v;
    }
    if (index < 8) {
        Index = index;
        Flags |= 1;
    }
}

// WIN32_FIND_DATAA, for the drive probe at 0x47AA50.
struct FindData_0047AA50
{
    unsigned long dwFileAttributes;
    unsigned long ftCreationTime[2];
    unsigned long ftLastAccessTime[2];
    unsigned long ftLastWriteTime[2];
    unsigned long nFileSizeHigh;
    unsigned long nFileSizeLow;
    unsigned long dwReserved0;
    unsigned long dwReserved1;
    char cFileName[260];
    char cAlternateFileName[14];
};
GG_STATIC_ASSERT(sizeof(FindData_0047AA50) == 0x140);

// LIBRARY: IAT 0x7E1208 KERNEL32!FindFirstFileA, 0x7E1300 KERNEL32!FindClose.
extern "C" __declspec(dllimport) void* __stdcall FindFirstFileA(const char* name, FindData_0047AA50* data);
extern "C" __declspec(dllimport) int __stdcall FindClose(void* find);

// STRING: GAMEMD 0x81C8F0  "?:\*.*"
// FUNCTION: GAMEMD 0x47AA50
// Whether drive letter `drive` (0 = A) holds anything: probes "X:\*.*".
int __fastcall FUN_0047AA50(char drive)
{
    char path[7] = "?:\\*.*";
    FindData_0047AA50 data;
    path[0] = drive + 'A';
    void* find = FindFirstFileA(path, &data);
    if (find == (void*)-1) {
        return 0;
    }
    FindClose(find);
    return 1;
}

// MSG, as the message pump at 0x53E730 sees it.
struct MsgView_0053E730
{
    void* hwnd;            // +0x00
    unsigned int message;  // +0x04
    unsigned int wParam;   // +0x08
    long lParam;           // +0x0C
    unsigned long time;    // +0x10
    long pt[2];            // +0x14
};
GG_STATIC_ASSERT(offsetof(MsgView_0053E730, message) == 4);

// FUNCTION: GAMEMD 0x53E770 (decl; reloc) -- fetch or peek one message into *msg; 0 when none.
int __fastcall FUN_0053E770(MsgView_0053E730* msg, void* hwnd, unsigned int filterMin,
                            unsigned int filterMax, int remove);

// FUNCTION: GAMEMD 0x53E730
// Waits until a message arrives; returns 0 for WM_QUIT (0x12), else the fetch result.
int __fastcall FUN_0053E730(MsgView_0053E730* msg, void* hwnd, unsigned int filterMin,
                            unsigned int filterMax)
{
    int result;
    do {
        result = FUN_0053E770(msg, hwnd, filterMin, filterMax, 1);
    } while (result == 0);
    if (msg->message == 0x12) {
        result = 0;
    }
    return result;
}

// DLLVERSIONINFO, for the version probe at 0x4AECD0.
struct DllVersionInfo_004AECD0
{
    unsigned long cbSize;
    unsigned long dwMajorVersion;
    unsigned long dwMinorVersion;
    unsigned long dwBuildNumber;
    unsigned long dwPlatformID;
};
GG_STATIC_ASSERT(sizeof(DllVersionInfo_004AECD0) == 0x14);

typedef int (__stdcall *DllGetVersionFn_004AECD0)(DllVersionInfo_004AECD0*);

// LIBRARY: IAT 0x7E1220 KERNEL32!LoadLibraryA, 0x7E1250 GetProcAddress, 0x7E1224 FreeLibrary.
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(void* module);

// STRING: GAMEMD 0x8201D4  "DllGetVersion"
// FUNCTION: GAMEMD 0x4AECD0
// Loads `name`, asks it for DllGetVersion and packs major:minor into one dword
// (major in the high word); 0 when the library or the export is missing.
unsigned int __fastcall FUN_004AECD0(const char* name)
{
    void* module;
    unsigned int version = 0;
    module = LoadLibraryA(name);
    if (module != 0) {
        DllGetVersionFn_004AECD0 getVersion = (DllGetVersionFn_004AECD0)GetProcAddress(module, "DllGetVersion");
        if (getVersion != 0) {
            DllVersionInfo_004AECD0 info;
            memset(&info, 0, sizeof(info));
            info.cbSize = 0x14;
            if (getVersion(&info) >= 0) {
                unsigned short major = info.dwMajorVersion & 0xFFFF;
                version = (major << 16) | (info.dwMinorVersion & 0xFFFF);
            }
        }
        FreeLibrary(module);
    }
    return version;
}

// FUNCTION: GAMEMD 0x53D8E0
// Spiral cell ordering around the origin: index 1 is the origin's first ring
// neighbour; each ring r holds 8r cells. Returns the (x, y) offset of cell
// `n` (counted from 1) through the hidden result pointer.
Point2D __fastcall FUN_0053D8E0(int n)
{
    Point2D out;
    int ring = 1;
    n--;
    if (n >= 8) {
        int step = 8;
        do {
            n -= step;
            step += 8;
            ring++;
        } while (n >= step);
    }
    if (n < ring * 2 + 1) {
        out.X = ring;
        out.Y = n - ring;
        return out;
    }
    if (n < ring * 4 + 1) {
        out.X = ring * 3 - n;
        out.Y = ring;
        return out;
    }
    if (n < ring * 6 + 1) {
        out.X = -ring;
        out.Y = ring * 5 - n;
        return out;
    }
    out.X = n + ring * -7;
    out.Y = -ring;
    return out;
}

// FUNCTION: GAMEMD 0x53D9F0
// Rebuild the ion blast pixel-offset table for a surface pitch: entry 0 is the
// origin, entry i the spiral point i as X + Y * pitch.
void __fastcall FUN_0053D9F0(int pitch)
{
    IonBlastOffsets[0] = 0;
    IonBlastOffsetsPitch = pitch;
    for (int i = 1; i < ION_BLAST_OFFSET_COUNT; i++) {
        Point2D pt = FUN_0053D8E0(i);
        IonBlastOffsets[i] = pt.Y * pitch + pt.X;
    }
}

// Scalar-deleting-destructor shape at 0x4AECA0 (see core/deleting_dtor_sweep.h): it
// tears down the member at +0xC, then the object itself, and frees the block when
// bit 0 of the flag is set. Written longhand because cl would inline the empty
// destructor bodies instead of emitting the two calls.
extern "C" void __cdecl FUN_007C8B3D(void* block);   // GAMEMD 0x7C8B3D operator delete
void __fastcall FUN_0043AE50(void* member);          // GAMEMD 0x43AE50 (decl; reloc)
void __fastcall FUN_00631C80(void* self);            // GAMEMD 0x631C80 (decl; reloc)

struct Obj_004AECA0
{
    char _pad00[0xC];
    void* FUN_004AECA0(unsigned int flags);
};

// FUNCTION: GAMEMD 0x4AECA0
void* Obj_004AECA0::FUN_004AECA0(unsigned int flags)
{
    FUN_0043AE50((char*)this + 0xC);
    FUN_00631C80(this);
    if (flags & 1) {
        FUN_007C8B3D(this);
    }
    return this;
}

// Vector deleting destructor at 0x40B010 of a 4-byte class (a vptr only) whose
// destructor lives out of line at 0x7B46F0. cl emits `??_E` only once the array
// form of `new` is seen, so an unreferenced static helper does that; VC6 drops
// the helper itself and keeps the destructor.
struct Elem_0040B010
{
    virtual ~Elem_0040B010();   // GAMEMD 0x7B46F0 (decl; reloc)
};
static Elem_0040B010* GgNewArray_0040B010(int n)
{
    return new Elem_0040B010[n];
}
// SYNTHETIC: GAMEMD 0x40B010
// Elem_0040B010::`vector deleting destructor'
