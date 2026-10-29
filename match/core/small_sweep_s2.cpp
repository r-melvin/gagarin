// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small functions read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. Receivers are placeholder views named after their address.
//   Address index: 0x727D60, 0x72EC30, 0x730720, 0x74BEA0, 0x7535D0, 0x7589F0, 0x759850, 0x759880, 0x759900, 0x759E10, 0x759F30, 0x759F90, 0x75A2D0, 0x7ACE30, 0x7B39D0, 0x7B5360, 0x7B70B0, 0x7B7D90.

#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"
#include "../renderer/screen_palette_mgr_methods.h"
#include "../audio/vox_class_play_index_methods.h"

void FUN_00730530();
void __fastcall FUN_0072FC60(int a, int b);

// FUNCTION: GAMEMD 0x730720
// Runs two helpers on the same pair of register arguments.
void __fastcall FUN_00730720(int a, int b)
{
    FUN_00730530();
    FUN_0072FC60(a, b);
}

struct Obj_00759F90
{
    char unknown_00[0x540];
    void (Obj_00759F90::*Handler)();   // +0x540

    // FUNCTION: GAMEMD 0x759F90 (__thiscall)
    void FUN_00759F90();
};
GG_STATIC_ASSERT(offsetof(Obj_00759F90, Handler) == 0x540);

// FUNCTION: GAMEMD 0x759F90
// Tail-calls the handler stored at +0x540.
void Obj_00759F90::FUN_00759F90()
{
    (this->*Handler)();
}

// ---------------------------------------------------------------------------
// 0x75A2D0: forwards to a helper on the object stored at +0xAC.
struct Inner_0075A120
{
    bool FUN_0075A120(int a, int b, int c);
    bool FUN_00759670(int a, int b, int c);
};

struct Obj_0075A2B0
{
    char unknown_00[0xAC];
    Inner_0075A120* Inner;   // +0xAC
};
GG_STATIC_ASSERT(offsetof(Obj_0075A2B0, Inner) == 0xAC);

// FUNCTION: GAMEMD 0x75A2D0
// Same forwarding through the helper at 0x759670, with the first argument in EDX.
bool __fastcall FUN_0075A2D0(Obj_0075A2B0* self, int a, int b, int c)
{
    return self->Inner->FUN_00759670(a, b, c);
}

// ---------------------------------------------------------------------------
// 0x759850 / 0x759880 / 0x759900 / 0x759E10 / 0x759F30: movie player wrappers.
struct MovieHandle_s2;
int __fastcall FUN_007C3430(MovieHandle_s2* h, int start, int end, int mode);
int __fastcall FUN_007C34B0(MovieHandle_s2* h, int start, int end, int a, int b);
int __fastcall FUN_007C30D0(MovieHandle_s2* h, int frame, int arg);
int __fastcall FUN_007C2D00(MovieHandle_s2* h, int mode, int flags);
void __fastcall FUN_00748380(int p, int count);

struct MoviePlayer_s2
{
    char unknown_000[0x200];
    MovieHandle_s2* Handle;   // +0x200
    char unknown_204[0x300];
    int Position;             // +0x504
    int FrameCount;           // +0x508
    char unknown_50C[4];
    int Field510;             // +0x510
    bool Active;              // +0x514
    char unknown_515[0x37];
    int Pending;              // +0x54C
    bool Started;             // +0x550

    // FUNCTION: GAMEMD 0x759850 (__thiscall)
    bool FUN_00759850(int start, int end);
    // FUNCTION: GAMEMD 0x759880 (__thiscall)
    bool FUN_00759880(int start, int end, int frame);
    // FUNCTION: GAMEMD 0x759900 (__thiscall)
    bool FUN_00759900();
    // FUNCTION: GAMEMD 0x759E10 (__thiscall)
    void FUN_00759E10();
    // FUNCTION: GAMEMD 0x759F30 (__thiscall)
    void FUN_00759F30(int a, int count);
};
GG_STATIC_ASSERT(offsetof(MoviePlayer_s2, Handle) == 0x200);
GG_STATIC_ASSERT(offsetof(MoviePlayer_s2, Position) == 0x504);
GG_STATIC_ASSERT(offsetof(MoviePlayer_s2, FrameCount) == 0x508);
GG_STATIC_ASSERT(offsetof(MoviePlayer_s2, Field510) == 0x510);
GG_STATIC_ASSERT(offsetof(MoviePlayer_s2, Active) == 0x514);
GG_STATIC_ASSERT(offsetof(MoviePlayer_s2, Pending) == 0x54C);
GG_STATIC_ASSERT(offsetof(MoviePlayer_s2, Started) == 0x550);

// FUNCTION: GAMEMD 0x759850
// Seeks the handle to a position (negative becomes -1); true when the seek reports -1.
bool MoviePlayer_s2::FUN_00759850(int start, int end)
{
    if (end < 0)
    {
        end = -1;
    }
    bool r = FUN_007C3430(Handle, start, end, 1) == -1;
    return r;
}

// FUNCTION: GAMEMD 0x759880
// Clamps a start/end frame pair into range, then runs the frame-range call on the handle.
bool MoviePlayer_s2::FUN_00759880(int start, int end, int frame)
{
    if (start < 0 || start >= FrameCount)
    {
        start = 0;
    }
    if (end < 0 || end >= FrameCount)
    {
        end = FrameCount - 1;
    }
    if (frame < 0)
    {
        frame = -1;
    }
    bool r = FUN_007C34B0(Handle, start, end, frame, 0) == -1;
    return r;
}

// FUNCTION: GAMEMD 0x759900
// When active, applies the pending frame to the handle and commits it as the position.
bool MoviePlayer_s2::FUN_00759900()
{
    if (Active)
    {
        if (FUN_007C30D0(Handle, Pending, 0) != -6)
        {
            Position = Pending;
            return true;
        }
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x759E10
// Starts the handle once, when active and not yet started, then marks it started.
void MoviePlayer_s2::FUN_00759E10()
{
    if (Active && !Started)
    {
        FUN_007C2D00(Handle, 2, 0);
    }
    Started = true;
}

// FUNCTION: GAMEMD 0x759F30
// Passes a halved count to the helper when slot 0x510 is set, then latches the position.
void MoviePlayer_s2::FUN_00759F30(int a, int count)
{
    if (Field510 != -1)
    {
        FUN_00748380(a, (unsigned int)count >> 1);
    }
    Pending = Position;
}

// ---------------------------------------------------------------------------
// 0x72EC30: loads the three audio/timer palette sets from their file names.
// GLOBAL: GAMEMD 0x844BE4
extern const char* DAT_00844BE4;
// GLOBAL: GAMEMD 0x844BE8
extern const char* DAT_00844BE8;
// GLOBAL: GAMEMD 0x844BEC
extern const char* DAT_00844BEC;

// FUNCTION: GAMEMD 0x72EC30
void __fastcall FUN_0072EC30()
{
    ConvertClass_CreateFromFile(DAT_00844BE4, DAT_00B0FBC8.Palette, DAT_00B0FBC8.Convert);
    ConvertClass_CreateFromFile(DAT_00844BE8, DAT_00B0FBD0.Palette, DAT_00B0FBD0.Convert);
    ConvertClass_CreateFromFile(DAT_00844BEC, DAT_00B0FBD8.Palette, DAT_00B0FBD8.Convert);
}

// ---------------------------------------------------------------------------
// 0x7535D0: stops the speech engine and clears the speaking entry.
// GLOBAL: GAMEMD 0xB1D428
extern int DAT_00B1D428;
// FUNCTION: GAMEMD 0x7535D0
void __fastcall FUN_007535D0()
{
    if (DAT_00B1D4C4 != 0)
    {
        DAT_00B1D4C4->State = 2;
        DAT_00B1D4C4 = 0;
    }
    if (DAT_00B1D4CC != 0)
    {
        DAT_00B1D4CC->FUN_00407F40();
    }
    FUN_00752370();
    DAT_00B1D428 = 0;
    DAT_00B1D3D8 = 0;
}

// ---------------------------------------------------------------------------
// 0x7B5360: owns a zero-filled byte buffer.
struct ByteBuffer_007B5360
{
    unsigned char* Data;   // +0x00

    // FUNCTION: GAMEMD 0x7B5360 (__thiscall)
    void FUN_007B5360(int size);
};

// FUNCTION: GAMEMD 0x7B5360
// Frees the buffer, then allocates and clears a new one of the given size.
void ByteBuffer_007B5360::FUN_007B5360(int size)
{
    if (Data != 0)
    {
        delete[] Data;
    }
    Data = 0;
    if (size >= 0)
    {
        Data = new unsigned char[size];
        memset(Data, 0, size);
    }
}

// ---------------------------------------------------------------------------
// 0x7B70B0: copies a wide string into a buffer and pads it with spaces to a length.
struct WideText_007B70B0
{
    wchar_t* Text;   // +0x00

    // FUNCTION: GAMEMD 0x7B70B0 (__thiscall)
    void FUN_007B70B0(wchar_t* dst, unsigned int length);
};

// FUNCTION: GAMEMD 0x7B70B0
void WideText_007B70B0::FUN_007B70B0(wchar_t* dst, unsigned int length)
{
    wcsncpy(dst, Text, length);
    unsigned int n = wcslen(Text);
    for (; n < length; n++)
    {
        dst[n] = L' ';
    }
    dst[length] = 0;
}

// ---------------------------------------------------------------------------
// 0x7B39D0: true when no (word, dword) pair in the table matches.
struct PairTable_007B39D0
{
    char unknown_00[0x3F568];
    int Count;                       // +0x3F568
    unsigned int Keys[16];           // +0x3F56C
    unsigned short Words[16];        // +0x3F5AC

    // FUNCTION: GAMEMD 0x7B39D0 (__thiscall)
    bool FUN_007B39D0(const unsigned int* key, unsigned short word);
};
GG_STATIC_ASSERT(offsetof(PairTable_007B39D0, Count) == 0x3F568);
GG_STATIC_ASSERT(offsetof(PairTable_007B39D0, Keys) == 0x3F56C);
GG_STATIC_ASSERT(offsetof(PairTable_007B39D0, Words) == 0x3F5AC);

// FUNCTION: GAMEMD 0x7B39D0
bool PairTable_007B39D0::FUN_007B39D0(const unsigned int* key, unsigned short word)
{
    for (int i = 0; i < Count; i++)
    {
        if (word == Words[i] && *key == Keys[i])
        {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x7ACE30: copies one string out of a counted table.
#include "string_class.h"

struct WstringList_007ACE30
{
    int Count;          // +0x00
    int unknown_04;
    Wstring* Items;     // +0x08

    // FUNCTION: GAMEMD 0x7ACE30 (__thiscall)
    bool FUN_007ACE30(Wstring* out, int index);
};
GG_STATIC_ASSERT(offsetof(WstringList_007ACE30, Items) == 0x8);

// FUNCTION: GAMEMD 0x7ACE30
bool WstringList_007ACE30::FUN_007ACE30(Wstring* out, int index)
{
    if (index >= 0 && index < Count)
    {
        *out = Items[index];
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x7B7D90: true when every character of the wide string fits in one byte.
struct WideText_007B7D90
{
    wchar_t* Text;   // +0x00

    // FUNCTION: GAMEMD 0x7B7D90 (__thiscall)
    bool FUN_007B7D90();
};

// FUNCTION: GAMEMD 0x7B7D90
bool WideText_007B7D90::FUN_007B7D90()
{
    if (Text != 0)
    {
        int length = wcslen(Text);
        for (int i = 0; i < length; i++)
        {
            if (Text[i] >= 0x100)
            {
                return false;
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x74BEA0: a bit-set selection that owns a byte vector.
#include "vector_class.h"

void __fastcall FUN_0054A900(unsigned char* bits, int index, int value);

struct Selection_0074BEA0
{
    int Mode;                          // +0x00
    unsigned char Value;               // +0x04
    unsigned char unknown_05[3];
    int Index;                         // +0x08
    VectorClass<unsigned char> Bytes;  // +0x0C

    // FUNCTION: GAMEMD 0x74BEA0 (__thiscall)
    void FUN_0074BEA0();
};
GG_STATIC_ASSERT(offsetof(Selection_0074BEA0, Value) == 0x4);
GG_STATIC_ASSERT(offsetof(Selection_0074BEA0, Index) == 0x8);
GG_STATIC_ASSERT(offsetof(Selection_0074BEA0, Bytes) == 0xC);

// FUNCTION: GAMEMD 0x74BEA0
// Writes the pending value back to its slot, resets the state and clears the byte vector.
void Selection_0074BEA0::FUN_0074BEA0()
{
    if (Index != -1)
    {
        FUN_0054A900(Bytes.Items, Index, Value);
        Index = -1;
    }
    Mode = 0;
    Bytes.Clear();
}

// ---------------------------------------------------------------------------
// 0x7589F0: reads a 0x300-byte block from an opened file.
#include "../platform/ccfile_class.h"

struct Palette_007589F0
{
    char unknown_00[0x10];
    void* Buffer;   // +0x10

    // FUNCTION: GAMEMD 0x7589F0 (__thiscall)
    int FUN_007589F0(FileClass* file);
};
GG_STATIC_ASSERT(offsetof(Palette_007589F0, Buffer) == 0x10);

// FUNCTION: GAMEMD 0x7589F0
// Opens the file, reads 0x300 bytes into the buffer and closes it; 1 when the read came up short.
int Palette_007589F0::FUN_007589F0(FileClass* file)
{
    int failed = 0;
    file->Open(1);
    if (file->ReadBytes(Buffer, 0x300) != 0x300)
    {
        failed = 1;
    }
    file->Close();
    return failed;
}

// ---------------------------------------------------------------------------
// 0x727D60: trims leading and trailing control/space characters from a wide string in place.
// FUNCTION: GAMEMD 0x727D60
wchar_t* __fastcall FUN_00727D60(wchar_t* text)
{
    if (text != 0)
    {
        wchar_t* start = text;
        while (*start != 0 && *start <= 0x20)
        {
            start++;
        }
        if (start != text)
        {
            wcscpy(text, start);
        }
        for (int i = wcslen(text) - 1; i >= 0 && *start != 0 && text[i] <= 0x20; i--)
        {
            text[i] = 0;
        }
    }
    return text;
}
