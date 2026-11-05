// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x7B6BE0..0x7B7440 (members and string builders that sit
//   before the proven start of wwmous.cpp, 0x7B7831, and follow Obj_007B66D0's own members).
//   Layout, conventions and CRT addresses come from the retail disassembly.
#include "wide_string_scratch.h"

// FUNCTION: GAMEMD 0x7B6BE0
// A new string made of this string followed by `text`. Retail expands the
// copy, the append and the result construction inline around a temporary
// buffer that is freed once the result owns its own copy.
Obj_007B66D0 Obj_007B66D0::FUN_007B6BE0(const wchar_t* text) const
{
    WideScratch work;
    if (Buffer != 0) {
        work.Buffer = (wchar_t*)::operator new(wcslen(Buffer) * 2 + 2);
        wcscpy(work.Buffer, Buffer);
    }
    if (text != 0) {
        work.Append(text);
    }
    return Obj_007B66D0(Obj_007B66D0::InlineCopy(), work.Buffer);
}

// FUNCTION: GAMEMD 0x7B6CB0
// A new string made of this string followed by `other` (unset reads as the
// shared empty string); the same inline expansion as 0x7B6BE0.
Obj_007B66D0 Obj_007B66D0::FUN_007B6CB0(const Obj_007B66D0& other) const
{
    WideScratch work;
    if (Buffer != 0) {
        work.Buffer = (wchar_t*)::operator new(wcslen(Buffer) * 2 + 2);
        wcscpy(work.Buffer, Buffer);
    }
    const wchar_t* text = other.Peek();
    if (text != 0) {
        work.Append(text);
    }
    return Obj_007B66D0(Obj_007B66D0::InlineCopy(), work.Buffer);
}

// FUNCTION: GAMEMD 0x7B71D0
// Inserts `text` at `pos` (clamped to the current length); an unset string
// simply takes a copy of the text.
bool Obj_007B66D0::FUN_007B71D0(const wchar_t* text, unsigned int pos)
{
    if (Buffer == 0) {
        Buffer = 0;
        Store(text);
        return true;
    }
    if (pos > wcslen(Buffer)) {
        pos = wcslen(Buffer);
    }
    wchar_t* grown = (wchar_t*)::operator new((wcslen(Buffer) + wcslen(text)) * 2 + 2);
    memset(grown, 0, (wcslen(Buffer) + wcslen(text)) * 2 + 2);
    wcscpy(grown, Buffer);
    unsigned int tail = 1 - pos + wcslen(Buffer);
    memmove(grown + pos + wcslen(text), grown + pos, tail * 2);
    memmove(grown + pos, text, wcslen(text) * 2);
    ::operator delete(Buffer);
    Buffer = grown;
    return true;
}

// FUNCTION: GAMEMD 0x7B72F0
// Inserts the single character `ch` at `pos` (clamped to the current length);
// an unset string simply becomes that character.
bool Obj_007B66D0::FUN_007B72F0(wchar_t ch, unsigned int pos)
{
    wchar_t cut[2];
    if (Buffer == 0) {
        cut[0] = ch;
        cut[1] = 0;
        Buffer = 0;
        Store(cut);
        return true;
    }
    unsigned int length = wcslen(Buffer);
    if (pos > length) {
        pos = length;
    }
    wchar_t* grown = (wchar_t*)::operator new(length * 2 + 4);
    cut[0] = Buffer[pos];
    Buffer[pos] = 0;
    cut[1] = 0;
    wcscpy(grown, Buffer);
    Buffer[pos] = cut[0];
    cut[0] = ch;
    wcscat(grown, cut);
    wcscat(grown, Buffer + pos);
    ::operator delete(Buffer);
    Buffer = grown;
    return true;
}
