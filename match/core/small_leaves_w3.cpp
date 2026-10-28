// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: small leaf functions in the 0x5EF000-0x5F2000 range of the user's gamemd.exe v1.001,
//   each disassembled from its entry point; the receiver types are placeholder views that declare
//   only the fields the bodies touch.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005F33A0
{
    char unknown_00[0x0C];
    char* Text;            // +0x0C
    int unknown_10;
    int Length;            // +0x14

    // FUNCTION: GAMEMD 0x5F33A0 (__thiscall)
    void Clear();
};
GG_STATIC_ASSERT(offsetof(Obj_005F33A0, Text) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_005F33A0, Length) == 0x14);

// FUNCTION: GAMEMD 0x5F33A0
// Empties the text and resets the length.
void Obj_005F33A0::Clear()
{
    *Text = 0;
    Length = 0;
}

struct Timer_005F1390
{
    // FUNCTION: GAMEMD 0x6C8C40 (decl; reloc)
    int FUN_006C8C40();
};

struct Obj_005F1390
{
    int Base;              // +0x00
    Timer_005F1390 Sub;    // +0x04
    int Value;             // +0x08

    // FUNCTION: GAMEMD 0x5F1390 (__thiscall)
    int Elapsed();
};
GG_STATIC_ASSERT(offsetof(Obj_005F1390, Value) == 0x08);

// FUNCTION: GAMEMD 0x5F1390
// The stored value, plus the time elapsed since Base when Base is set (-1 means unset).
int Obj_005F1390::Elapsed()
{
    int result = Value;
    if (Base != -1) {
        result += Sub.FUN_006C8C40() - Base;
    }
    return result;
}

// A length-prefixed byte record: id, length (at most 0x8000) and the bytes.
struct Obj_006C6B00
{
    int Id;                 // +0x00
    int Length;             // +0x04
    char Data[0x8000];      // +0x08

    // FUNCTION: GAMEMD 0x6C6B00 (__thiscall, RET 0x4)
    Obj_006C6B00(const Obj_006C6B00& other);
};
GG_STATIC_ASSERT(offsetof(Obj_006C6B00, Length) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_006C6B00, Data) == 0x08);

// FUNCTION: GAMEMD 0x6C6B00
// Copies the header; an over-long record is emptied instead of copied.
Obj_006C6B00::Obj_006C6B00(const Obj_006C6B00& other)
{
    Id = other.Id;
    Length = other.Length;
    if (Length > 0x8000) {
        Length = 0;
        return;
    }
    memcpy(Data, other.Data, Length);
}

struct ByteStream_006C9EC0
{
    virtual void vf_0();
    virtual void vf_1();
    virtual int Read(void* buffer, int count);   // slot 2
};

// STRING: GAMEMD 0x84226C
extern const char STR_0084226C[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc)
void __cdecl FUN_004068E0(const char* message);

struct Reader_006C9EC0
{
    ByteStream_006C9EC0* Stream;   // +0x00
    char unknown_04[0x800];        // +0x04
    int unknown_804;               // +0x804

    // FUNCTION: GAMEMD 0x6C9EC0 (__thiscall, RET 0x4)
    Reader_006C9EC0(ByteStream_006C9EC0* stream);
};
GG_STATIC_ASSERT(offsetof(Reader_006C9EC0, unknown_804) == 0x804);

// FUNCTION: GAMEMD 0x6C9EC0
// Binds the stream and checks that it starts with the 0xFEFF byte-order mark.
Reader_006C9EC0::Reader_006C9EC0(ByteStream_006C9EC0* stream)
{
    Stream = stream;
    unknown_804 = 0;
    int mark = 0;
    stream->Read(&mark, 2);
    if ((unsigned short)mark != 0xFEFF) {
        FUN_004068E0(STR_0084226C);
    }
}

struct Child_006E85B0
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual int vf_11();   // slot 11 (+0x2C)
};

struct ChildSlot_006E85B0
{
    Child_006E85B0* Item;  // +0x00
    int unknown_04;        // +0x04
};

struct Obj_006E85B0
{
    char unknown_00[0x9C];
    int Count;                       // +0x9C
    int unknown_A0;
    int unknown_A4;
    ChildSlot_006E85B0 Slots[1];     // +0xA8, stride 8

    // FUNCTION: GAMEMD 0x6E85B0 (__thiscall)
    bool AllChildrenReady();
};
GG_STATIC_ASSERT(offsetof(Obj_006E85B0, Count) == 0x9C);
GG_STATIC_ASSERT(offsetof(Obj_006E85B0, Slots) == 0xA8);

// FUNCTION: GAMEMD 0x6E85B0
// True when every child reports state 0x10.
bool Obj_006E85B0::AllChildrenReady()
{
    for (int i = 0; i < Count; i++) {
        if (Slots[i].Item->vf_11() != 0x10) {
            return false;
        }
    }
    return true;
}
