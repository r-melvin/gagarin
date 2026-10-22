// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Layout and conventions read numerically off the user's retail gamemd.exe
//   v1.001 through the local Ghidra CLI. The private reference's `core/wide_string_class.cpp`
//   supplied only the semantic names for this family (what each entry point
//   does); every offset, width, calling convention and CRT helper address below
//   was re-derived from the retail disassembly at 0x7B66D0..0x7B7834.
//
// WideStringClass is Westwood's heap-owning wide-character string. The retail
// object is a single 4-byte member: a `wchar_t*` at +0x00, allocated with the
// global `operator new` and released with the global `operator delete`. There
// is no allocation header, no length cache and no reference count -- every
// operation in this family re-measures with `wcslen` and reallocates, which is
// exactly what the disassembly shows (e.g. 0x7B6880 frees, zeroes +0x00,
// re-measures, allocates and copies).
//
// Evidence for the layout:
//   * `MOV ESI,ECX` / `MOV EAX,dword ptr [ESI]` at 0x7B6884, 0x7B7063,
//     0x7B7604 -- the only member ever touched is at displacement 0.
//   * `MOV dword ptr [ESI],EAX` at 0x7B68BD stores the `operator new` result
//     straight into that same slot, so the member IS the buffer pointer.
//   * `RET 4` / `RET 8` throughout with `this` in ECX: MSVC6 `__thiscall`.
#ifndef GG_MATCH_CORE_WIDE_STRING_CLASS_H
#define GG_MATCH_CORE_WIDE_STRING_CLASS_H

#include "../_rt/gg_static_assert.h"

// MSVC6 has no native `wchar_t`; the CRT headers typedef it. The translation
// unit is standalone, so it declares the same typedef here.
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
#ifndef offsetof
#define offsetof(s, m) ((unsigned int)(unsigned long) & (((s*)0)->m))
#endif

// CRT and allocator helpers, addresses confirmed from the call sites in this
// family. They are declared here rather than included so the translation unit
// compiles standalone under the period toolchain; the diff harness normalises
// the relocation, so only the convention and the argument shape matter.
extern "C" {
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) — wcslen.
unsigned int __cdecl wcslen(const wchar_t* s);
// FUNCTION: GAMEMD 0x7CA489 (decl; reloc) — wcscpy.
wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
// FUNCTION: GAMEMD 0x7CA422 (decl; reloc) — wcsncpy.
wchar_t* __cdecl wcsncpy(wchar_t* dst, const wchar_t* src, unsigned int n);
// LIBRARY: GAMEMD 0x7CA45F (decl; reloc) — wcscat.
wchar_t* __cdecl wcscat(wchar_t* dst, const wchar_t* src);
// FUNCTION: GAMEMD 0x7CA5D3 (decl; reloc) — wcscmp.
int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
// LIBRARY: GAMEMD 0x7CAFF4 (decl; reloc) — CRT tolower.
//   The callee is the narrow CRT tolower (LIBCMT tolower.obj), not towlower:
//   retail zero-extends the wide character with `AND EAX,0xFFFF` before the
//   push (0x7B771B), the widening a wchar_t argument to an `int` costs.
int __cdecl tolower(int c);
// LIBRARY: GAMEMD 0x7C97D3 (decl; reloc) — CRT toupper (LIBCMT toupper.obj).
int __cdecl toupper(int c);
// The allocator pair is the global operator new / operator delete at
// GAMEMD 0x7C8E17 and 0x7C8B3D (decl; reloc), reached through the ordinary
// `::operator new` / `::operator delete` spellings below.
void* __cdecl memset(void* d, int c, unsigned int n);
}
#pragma intrinsic(memset)

// GLOBAL: GAMEMD 0x887734
//   The shared empty wide string. `MOV EDI,0x887734` at 0x7B6911 and
//   `MOV EBP,0x887734` at 0x7B6B6F substitute it for a null buffer.
extern wchar_t WideEmptyString[];

class WideStringClass
{
public:
    // The only member. Offset 0 and size 4 are pinned below.
    wchar_t* Buffer;

    // ---- inline helpers -------------------------------------------------
    //
    // These four never appear as out-of-line retail functions in this family;
    // they are the shapes the retail bodies share, and every scored function
    // below expands them. `__forceinline` sits on the declaration because a
    // marker on the definition alone leaves cl free to emit a call for some
    // of the expansions.

    // Retail 0x7B6760 in its out-of-line form: free the buffer if any and
    // null the slot unconditionally.
    __forceinline void Release();

    // The allocate-and-copy half that 0x7B66D0, 0x7B6880, 0x7B68E0 and
    // 0x7B7600 all share verbatim.
    __forceinline void Store(const wchar_t* src);

    // Retail 0x7B7100 in its out-of-line form: the buffer, or the shared
    // empty string when there is none.
    __forceinline const wchar_t* Peek() const;

    // The append half shared by 0x7B6970, 0x7B6AE0 and 0x7B6B60.
    __forceinline void Append(const wchar_t* src);

    // The measured length, zero when there is no buffer. Retail folds the
    // null case into the loop test at 0x7B76F8 / 0x7B77E8.
    __forceinline unsigned int Length() const;

    // ---- scored entry points, ascending by retail address ----------------
    WideStringClass(const wchar_t* src);                       // 0x7B66D0
    WideStringClass& operator=(const wchar_t* src);            // 0x7B6880
    WideStringClass& operator=(const WideStringClass& other);  // 0x7B68E0
    bool Concat(const wchar_t* src);                           // 0x7B6970
    WideStringClass& operator+=(const wchar_t* src);           // 0x7B6AE0
    WideStringClass& operator+=(const WideStringClass& other); // 0x7B6B60
    short Erase(int pos, int count);                           // 0x7B6D90
    // FUNCTION: GAMEMD 0x7B6E20 (decl; reloc) -- remove every occurrence of
    // one character (__thiscall, one stack word).
    bool FUN_007B6E20(wchar_t ch);
    void FUN_007B6EC0();                                       // 0x7B6EC0
    void Resize(int count);                                    // 0x7B7060
    short Set(const wchar_t* src);                             // 0x7B7600
    short Set(int count, const wchar_t* src);                  // 0x7B7690
    void MakeLower();                                          // 0x7B76F0
    WideStringClass* AsLower(WideStringClass* out) const;      // 0x7B7740
    void MakeUpper();                                          // 0x7B77E0
    WideStringClass* AsUpper(WideStringClass* out) const;      // 0x7B7830
};

// Offsets confirmed numerically from the disassembly cited in the file header.
GG_STATIC_ASSERT(sizeof(WideStringClass) == 4
              && offsetof(WideStringClass, Buffer) == 0x00);

__forceinline void WideStringClass::Release()
{
    if (Buffer != 0) {
        ::operator delete(Buffer);
    }
    Buffer = 0;
}

__forceinline void WideStringClass::Store(const wchar_t* src)
{
    int len = (src != 0) ? (int)wcslen(src) + 1 : 1;
    Buffer = (wchar_t*)::operator new(len * 2);
    *Buffer = 0;
    if (src != 0) {
        wcscpy(Buffer, src);
    }
}

__forceinline const wchar_t* WideStringClass::Peek() const
{
    if (Buffer != 0) {
        return Buffer;
    }
    return WideEmptyString;
}

__forceinline unsigned int WideStringClass::Length() const
{
    return (Buffer != 0) ? wcslen(Buffer) : 0;
}

__forceinline void WideStringClass::Append(const wchar_t* src)
{
    wchar_t* old = Buffer;
    int len = (int)wcslen(src) + 1;
    if (old != 0) {
        len += (int)wcslen(old);
    }
    Buffer = (wchar_t*)::operator new(len * 4);
    if (old != 0) {
        wcscpy(Buffer, old);
    } else {
        *Buffer = 0;
    }
    wcscat(Buffer, src);
    if (old != 0) {
        ::operator delete(old);
    }
}

#endif  // GG_MATCH_CORE_WIDE_STRING_CLASS_H
