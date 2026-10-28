// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// File-scope objects with user constructors and destructors, defined as real
// globals so the compiler emits both the combined initialiser (constructor
// call or inlined constructor, then atexit of the destructor stub) and the
// exit-time stub itself. Each belongs to a retail translation unit whose
// source is not in the tree, so they are collected here; the class names are
// address placeholders.

#include <unknwn.h>

// Heap-owning five-field record: the constructor zeroes the fields and the
// destructor frees the block, then zeroes them again (the exit-time stub at
// 0x40BDA0 is the inlined destructor).
struct Obj_0087F680
{
    int* Block;
    int Count;
    int Capacity;
    unsigned char Owned;
    int Extra;
    Obj_0087F680() : Block(0), Count(0), Capacity(0), Owned(0), Extra(0) {}
    ~Obj_0087F680()
    {
        delete Block;
        Block = 0;
        Count = 0;
        Capacity = 0;
        Owned = 0;
        Extra = 0;
    }
};

// SYNTHETIC: GAMEMD 0x40BD70
// SYNTHETIC: GAMEMD 0x40BDA0 -- exit-time destructor stub
// GLOBAL: GAMEMD 0x87F680
Obj_0087F680 DAT_0087F680;

// A screen rectangle {0, 0, 640, 400} built by its constructor.
struct Rect_00886FA0
{
    int X;
    int Y;
    int Width;
    int Height;
    Rect_00886FA0(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h) {}
};

// SYNTHETIC: GAMEMD 0x40DA20
// GLOBAL: GAMEMD 0x886FA0
Rect_00886FA0 DAT_00886FA0(0, 0, 640, 400);

// SYNTHETIC: GAMEMD 0x40DA50
// GLOBAL: GAMEMD 0x886FB0
Rect_00886FA0 DAT_00886FB0(0, 0, 640, 400);

// Two 64-entry tables cleared by the helper at 0x5C6940 (zero the dwords, then
// store the second argument in the first), followed by one more int. The
// helper takes the table in ECX, the value in EDX and the count on the stack.
struct Tbl_005C6940
{
    int Entries[0x40];
};
// FUNCTION: GAMEMD 0x5C6940 (decl; reloc)
void __fastcall FUN_005C6940(Tbl_005C6940* table, int value, int count);

struct Obj_00886980
{
    Tbl_005C6940 First;
    Tbl_005C6940 Second;
    int Tail;
    Obj_00886980()
    {
        FUN_005C6940(&First, 0, 0x40);
        FUN_005C6940(&Second, 0, 0x40);
        Tail = 0;
    }
};

// SYNTHETIC: GAMEMD 0x40D9C0
// GLOBAL: GAMEMD 0x886980
Obj_00886980 DAT_00886980;

// An eight-byte value (a double that starts as 1.0) whose constructor
// (0x5B1D90) and destructor (0x5B1E20, a consistency check) are defined out of
// line; the exit-time stub at 0x40D330 tail-jumps to the destructor.
class Obj_00884D88
{
public:
    double Value;
    // FUNCTION: GAMEMD 0x5B1D90 (decl; reloc)
    Obj_00884D88();
    // FUNCTION: GAMEMD 0x5B1E20 (decl; reloc)
    ~Obj_00884D88();
};

// SYNTHETIC: GAMEMD 0x40D310
// SYNTHETIC: GAMEMD 0x40D330 -- exit-time destructor stub
// GLOBAL: GAMEMD 0x884D88
Obj_00884D88 DAT_00884D88;

// A 0x90-byte object (ends at the next global, 0x887628) with an out-of-line
// constructor (0x776EB0) and an empty destructor, so its exit-time stub at
// 0x40FF30 is a bare RET.
class Obj_00887598
{
public:
    char unknown_00[0x90];
    // FUNCTION: GAMEMD 0x776EB0 (decl; reloc)
    Obj_00887598();
    ~Obj_00887598() {}
};

// SYNTHETIC: GAMEMD 0x40FF10
// SYNTHETIC: GAMEMD 0x40FF30 -- exit-time destructor stub
// GLOBAL: GAMEMD 0x887598
Obj_00887598 DAT_00887598;

// An owning COM interface pointer: starts null and releases the interface at
// exit (the stub at 0x40D220 is the inlined Release call through slot 2).
class Obj_0087F7B8
{
public:
    IUnknown* Interface;
    Obj_0087F7B8() : Interface(0) {}
    ~Obj_0087F7B8()
    {
        if (Interface)
            Interface->Release();
    }
};

// SYNTHETIC: GAMEMD 0x40D200
// SYNTHETIC: GAMEMD 0x40D220 -- exit-time destructor stub
// GLOBAL: GAMEMD 0x87F7B8
Obj_0087F7B8 DAT_0087F7B8;
