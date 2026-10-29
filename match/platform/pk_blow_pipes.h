// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// RTTI type names from the pinned image: 0x7EFDC8 .?AVBlowPipe@@,
// 0x7EDF40 .?AVBlowStraw@@, 0x7EFDAC .?AVPKPipe@@, 0x7EFDE0 .?AVPKStraw@@.
// Slot words are listed beside each VTABLE marker.
//
// Member evidence:
//   BlowPipe/BlowStraw: the embedded copies are built inline by 0x632CB0 and
//   0x633050 (+0x0C cipher pointer = 0, +0x18 count = 0, +0x1C control);
//   0x4380A0 reads +0x0C, stages bytes at +0x10 (8 bytes) and counts in +0x18,
//   and compares +0x1C with 1.
//   PKPipe/PKStraw: 0x632CB0 and 0x633050 store byte 1 at +0x0C, the second
//   argument at +0x10, the cipher object at +0x14, the first argument at
//   +0x34, and zero +0x38, +0x13C and +0x140; 0x632F30/0x633110 read the key
//   pointer at +0x38 and the key's dword at +0x200.
//   sizeof(PKStraw) == 0x144: the stack instance at [ESP+0xA4] in 0x5B3C20 is
//   the last object of its 0x1DC-byte frame (three saved registers above), so
//   it ends at +0x144, and +0x140 is written as a dword.
// Names of members and of the non-virtual helpers are descriptive.
#ifndef GG_MATCH_PLATFORM_PK_BLOW_PIPES_H
#define GG_MATCH_PLATFORM_PK_BLOW_PIPES_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"
#include "../core/pkey_layout.h"

// The block cipher object reached through BlowPipe/BlowStraw +0x0C. Both
// helpers are __thiscall with three stack words (RET 0xC).
struct IFace;
class BlockCipherView
{
public:
    IFace* Interface;
    // FUNCTION: GAMEMD 0x437F50
    BlockCipherView();
    // FUNCTION: GAMEMD 0x437FD0
    void Key(const void* key, int length);
    // FUNCTION: GAMEMD 0x438000 (decl; reloc) -- used when control != 1.
    int Forward(const void* in, int length, void* out);
    // FUNCTION: GAMEMD 0x438030 (decl; reloc) -- used when control == 1.
    int Reverse(const void* in, int length, void* out);
    // FUNCTION: GAMEMD 0x437FC0 (decl; reloc) -- non-virtual, out of line.
    ~BlockCipherView();

};
GG_STATIC_ASSERT(offsetof(BlockCipherView, Interface) == 0);
GG_STATIC_ASSERT(sizeof(BlockCipherView) == 4);

class BlowPipe : public Pipe
{
public:
    enum PipeDirection { PIPE_DIR_0 = 0, PIPE_DIR_1 = 1 };

    BlowPipe(PipeDirection control) : Cipher(0), Counter(0), Control(control) {}
    // Inline: the deleting entry 0x632F90 carries the whole body (reseat the
    // vtable, delete the cipher through 0x437FC0 and clear it, then ~Pipe
    // 0x631C80), and PKPipe's deleting entry inlines it again for +0x14.
    virtual ~BlowPipe() { delete Cipher; Cipher = 0; } // slot 0 via 0x632F90
    virtual int FUN_00631D30();                         // slot 1 = 0x438060
    // FUNCTION: GAMEMD 0x4380A0
    virtual int FUN_00631D10(int first, int second);    // slot 4

    // FUNCTION: GAMEMD 0x4381D0
    void Key(const void* key, int length);

    BlockCipherView* Cipher;      // +0x0C
    char             Buffer[8];   // +0x10
    int              Counter;     // +0x18
    PipeDirection     Control;     // +0x1C
};
GG_STATIC_ASSERT(sizeof(BlowPipe) == 0x20);
GG_STATIC_ASSERT(offsetof(BlowPipe, Cipher)  == 0x0C);
GG_STATIC_ASSERT(offsetof(BlowPipe, Buffer)  == 0x10);
GG_STATIC_ASSERT(offsetof(BlowPipe, Counter) == 0x18);
GG_STATIC_ASSERT(offsetof(BlowPipe, Control) == 0x1C);
// VTABLE: GAMEMD 0x7EFDC8 -- [0x632F90, 0x438060, 0x477740, 0x631CC0, 0x4380A0]

class BlowStraw : public Straw
{
public:
    enum PipeDirection { PIPE_DIR_0 = 0, PIPE_DIR_1 = 1 };

    BlowStraw(PipeDirection control) : Cipher(0), Counter(0), Control(control) {}
    // Inline, as for BlowPipe: deleting entry 0x5B45C0, base ~Straw 0x6C9850.
    virtual ~BlowStraw() { delete Cipher; Cipher = 0; } // slot 0 via 0x5B45C0
    virtual int FUN_006C98E0(void* first, int second);    // slot 2 = 0x438210

    // FUNCTION: GAMEMD 0x438300
    void Key(const void* key, int length);

    BlockCipherView* Cipher;      // +0x0C
    char             Buffer[8];   // +0x10
    int              Counter;     // +0x18
    PipeDirection     Control;     // +0x1C
};
GG_STATIC_ASSERT(sizeof(BlowStraw) == 0x20);
GG_STATIC_ASSERT(offsetof(BlowStraw, Cipher)  == 0x0C);
GG_STATIC_ASSERT(offsetof(BlowStraw, Buffer)  == 0x10);
GG_STATIC_ASSERT(offsetof(BlowStraw, Counter) == 0x18);
GG_STATIC_ASSERT(offsetof(BlowStraw, Control) == 0x1C);
// VTABLE: GAMEMD 0x7EDF40 -- [0x5B45C0, 0x6C9890, 0x438210]

// PKPipe and PKStraw declare no destructor. Their deleting entries 0x632FF0
// and 0x633370 store no vtable of their own: they run the member BlowPipe /
// BlowStraw destructor at +0x14 inline and then the base destructor, which is
// the implicitly defined virtual destructor's shape.
enum { PK_SESSION_KEY_BYTES = 56 };

class PKPipe : public Pipe
{
public:
    enum PipeDirection { PIPE_DIR_0 = 0, PIPE_DIR_1 = 1 };

    // FUNCTION: GAMEMD 0x632CB0
    PKPipe(PipeDirection control, Straw* random);
    virtual void SetChainTo(Pipe* next);                // slot 3 = 0x632D10
    virtual int FUN_00631D10(int first, int second);    // slot 4 = 0x632DC0
    // FUNCTION: GAMEMD 0x632FE0
    virtual void FUN_00632FE0(Pipe* next);              // slot 5

    // FUNCTION: GAMEMD 0x632F30
    int FUN_00632F30() const;
    // FUNCTION: GAMEMD 0x632F60
    int FUN_00632F60() const;

    int SessionKeyCipherBytes() const { if (Key == NULL) return 0; return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->CipherBlockBytes(); }
    int SessionKeyPlainBytes() const { if (Key == NULL) return 0; return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->PlainBlockBytes(); }

    bool         unknown_C;      // +0x0C
    Straw*       unknown_10;    // +0x10
    BlowPipe     Cipher;          // +0x14
    PipeDirection Control;         // +0x34
    PKey_00632740*   Key;             // +0x38
    char         Buffer[256];     // +0x3C
    int          Counter;         // +0x13C
    int          unknown_140;       // +0x140
};
GG_STATIC_ASSERT(offsetof(PKPipe, unknown_C)   == 0x0C);
GG_STATIC_ASSERT(offsetof(PKPipe, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(PKPipe, Cipher)       == 0x14);
GG_STATIC_ASSERT(offsetof(PKPipe, Control)      == 0x34);
GG_STATIC_ASSERT(offsetof(PKPipe, Key)          == 0x38);
GG_STATIC_ASSERT(offsetof(PKPipe, Buffer)       == 0x3C);
GG_STATIC_ASSERT(offsetof(PKPipe, Counter)      == 0x13C);
GG_STATIC_ASSERT(offsetof(PKPipe, unknown_140)    == 0x140);
// VTABLE: GAMEMD 0x7EFDAC -- [0x632FF0, 0x631D30, 0x477740, 0x632D10, 0x632DC0, 0x632FE0]

class PKStraw : public Straw
{
public:
    enum PipeDirection { PIPE_DIR_0 = 0, PIPE_DIR_1 = 1 };

    // FUNCTION: GAMEMD 0x633050
    PKStraw(PipeDirection control, Straw* random);
    virtual void SetChainTo(Straw* next);               // slot 1 = 0x6330C0
    virtual int FUN_006C98E0(void* first, int second);    // slot 2 = 0x633130
    // FUNCTION: GAMEMD 0x633360
    virtual void FUN_00633360(Straw* next);             // slot 3

    // FUNCTION: GAMEMD 0x633110
    void FUN_00633110(PKey_00632740* key);
    // FUNCTION: GAMEMD 0x633300
    int FUN_00633300() const;
    // FUNCTION: GAMEMD 0x633330
    int FUN_00633330() const;

    int SessionKeyCipherBytes() const { if (Key == NULL) return 0; return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->CipherBlockBytes(); }
    int SessionKeyPlainBytes() const { if (Key == NULL) return 0; return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->PlainBlockBytes(); }

    bool         unknown_C;      // +0x0C
    Straw*       unknown_10;    // +0x10
    BlowStraw    Cipher;          // +0x14
    PipeDirection Control;         // +0x34
    PKey_00632740*   Key;             // +0x38
    char         Buffer[256];     // +0x3C
    int          Counter;         // +0x13C
    int          unknown_140;       // +0x140
};
GG_STATIC_ASSERT(offsetof(PKStraw, unknown_C)   == 0x0C);
GG_STATIC_ASSERT(offsetof(PKStraw, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(PKStraw, Cipher)       == 0x14);
GG_STATIC_ASSERT(offsetof(PKStraw, Control)      == 0x34);
GG_STATIC_ASSERT(offsetof(PKStraw, Key)          == 0x38);
GG_STATIC_ASSERT(offsetof(PKStraw, Buffer)       == 0x3C);
GG_STATIC_ASSERT(offsetof(PKStraw, Counter)      == 0x13C);
GG_STATIC_ASSERT(offsetof(PKStraw, unknown_140)    == 0x140);
GG_STATIC_ASSERT(sizeof(PKStraw) == 0x144);
// VTABLE: GAMEMD 0x7EFDE0 -- [0x633370, 0x6330C0, 0x633130, 0x633360]

#endif // GG_MATCH_PLATFORM_PK_BLOW_PIPES_H
