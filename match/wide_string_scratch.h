// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Helpers for the string-building functions that follow Obj_007B66D0's members in retail gamemd.exe v1.001
//   (0x7B6BE0..0x7B83E0): the temporary string objects whose construction and destruction retail expands inline,
//   and the library entry points those functions call. Layout, conventions and addresses were read from the
//   retail disassembly of those functions.
#ifndef GG_MATCH_CORE_WIDE_STRING_SCRATCH_H
#define GG_MATCH_CORE_WIDE_STRING_SCRATCH_H

#include "wide_string_class.h"
#include "string_class.h"

// LIBRARY: GAMEMD 0x7CA564 (decl; reloc) -- swprintf.
extern "C" int __cdecl FUN_007CA564(wchar_t* buffer, const wchar_t* format, ...);

// The temporary string object of the original bodies: a heap buffer that its
// destructor frees when the function leaves (retail expands that inline).
struct WideScratch
{
    wchar_t* Buffer;
    WideScratch() : Buffer(0) {}
    ~WideScratch()
    {
        if (Buffer != 0) {
            ::operator delete(Buffer);
        }
    }
    void Store(const wchar_t* text)
    {
        int len = (text != 0) ? (int)wcslen(text) + 1 : 1;
        Buffer = (wchar_t*)::operator new(len * 2);
        *Buffer = 0;
        if (text != 0) {
            wcscpy(Buffer, text);
        }
    }
    // FUNCTION: GAMEMD 0x7B6970 (decl; reloc) -- Obj_007B66D0::Concat, __thiscall.
    bool FUN_007B6970(const wchar_t* text);
    void Copy(const wchar_t* text)
    {
        if (text != 0) {
            Buffer = (wchar_t*)::operator new(wcslen(text) * 2 + 2);
            wcscpy(Buffer, text);
        }
    }
    void Append(const wchar_t* text)
    {
        wchar_t* old = Buffer;
        int len = (int)wcslen(text) + 1;
        if (old != 0) {
            len += (int)wcslen(old);
        }
        Buffer = (wchar_t*)::operator new(len * 4);
        if (old != 0) {
            wcscpy(Buffer, old);
        } else {
            *Buffer = 0;
        }
        wcscat(Buffer, text);
        if (old != 0) {
            ::operator delete(old);
        }
    }
};

// STRING: GAMEMD 0x889F64 -- the shared empty narrow string.
extern const char STR_00889F64[];

// LIBRARY: GAMEMD 0x735060 (decl; reloc) -- __fastcall, wide output in ECX, narrow input in EDX, RET 4.
void __fastcall FUN_00735060(wchar_t* output, const char* input, int maximum);
// LIBRARY: GAMEMD 0x735090 (decl; reloc) -- __fastcall, narrow output in ECX, wide input in EDX, RET 4.
void __fastcall FUN_00735090(char* output, const wchar_t* input, int maximum);

// LIBRARY: GAMEMD 0x4335E0 (decl; reloc) -- __fastcall, packs the wide text in ECX into the bytes at EDX; the bit count is on the stack, RET 4.
void __fastcall FUN_004335E0(const wchar_t* input, char* output, int bits);
// LIBRARY: GAMEMD 0x433770 (decl; reloc) -- __fastcall, unpacks the packed bytes in ECX into the wide text at EDX; the count is on the stack, RET 4.
void __fastcall FUN_00433770(const char* input, wchar_t* output, int count);

// The narrow counterpart of WideScratch.
struct NarrowScratch
{
    char* Buffer;
    NarrowScratch() : Buffer(0) {}
    ~NarrowScratch()
    {
        if (Buffer != 0) {
            ::operator delete(Buffer);
        }
    }
};

// The measured length, zero when there is no text; an early return on the
// null case, the shape retail's inline expansions show.
static inline int WideLength(const wchar_t* p)
{
    if (p == 0) {
        return 0;
    }
    return (int)wcslen(p);
}

#endif  // GG_MATCH_CORE_WIDE_STRING_SCRATCH_H
