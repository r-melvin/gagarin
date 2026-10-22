// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x7B66D0..0x7B7834.
//   The private reference's `core/wide_string_class.cpp` named the entry points; the
//   layout, the `__thiscall` conventions, the CRT helper addresses and every
//   constant below come from the retail disassembly.

#include "wide_string_class.h"

// FUNCTION: GAMEMD 0x7B66D0
//
// Construct from a raw wide string. The buffer slot is nulled first, then the
// source is measured (one extra for the terminator, or a bare one when there
// is no source), a fresh block of that many wide characters is allocated, the
// terminator is written straight away and the source, if any, is copied in.
WideStringClass::WideStringClass(const wchar_t* src)
{
    Buffer = 0;
    Store(src);
}

// FUNCTION: GAMEMD 0x7B6720
//
// Copy-construct: null the slot, then, when the other instance holds a
// buffer, allocate room for its characters plus the terminator and copy them.
WideStringClass::WideStringClass(const WideStringClass& other)
{
    Buffer = 0;
    if (other.Buffer != 0) {
        Buffer = (wchar_t*)::operator new(wcslen(other.Buffer) * 2 + 2);
        wcscpy(Buffer, other.Buffer);
    }
}

// FUNCTION: GAMEMD 0x7B6780
//
// Compare with a raw wide string: two nulls are equal, one null is not, and
// otherwise the CRT comparison decides.
bool WideStringClass::FUN_007B6780(const wchar_t* text) const
{
    if (Buffer == 0 && text == 0) {
        return true;
    }
    if (Buffer != 0 && text != 0) {
        return wcscmp(Buffer, text) == 0;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7B6880
//
// Assign a raw wide string. The old buffer is released and the slot nulled,
// then the same allocate-measure-copy body the constructor uses runs again.
WideStringClass& WideStringClass::operator=(const wchar_t* src)
{
    Release();
    Store(src);
    return *this;
}

// FUNCTION: GAMEMD 0x7B68E0
//
// Assign from another instance. Assigning an equal string is a no-op -- two
// null buffers compare equal, and two live buffers go through wcscmp -- so the
// release and reallocation only happen when the contents actually differ. A
// null source buffer is substituted with the shared empty string.
WideStringClass& WideStringClass::operator=(const WideStringClass& other)
{
    if (Buffer == 0 && other.Buffer == 0) {
        return *this;
    }
    if (Buffer != 0 && other.Buffer != 0 && wcscmp(Buffer, other.Buffer) == 0) {
        return *this;
    }

    const wchar_t* src = other.Peek();
    Release();
    Store(src);
    return *this;
}

// FUNCTION: GAMEMD 0x7B6970
//
// Append a raw wide string, reporting success. A null source is accepted and
// does nothing. The append reallocates: it measures both halves, takes a new
// block, seeds it with the old contents (or just a terminator), concatenates
// and frees the old block.
bool WideStringClass::Concat(const wchar_t* src)
{
    if (src == 0) {
        return true;
    }
    Append(src);
    return true;
}

// FUNCTION: GAMEMD 0x7B6AE0
//
// The operator form of the same append, returning the string itself.
WideStringClass& WideStringClass::operator+=(const wchar_t* src)
{
    if (src != 0) {
        Append(src);
    }
    return *this;
}

// FUNCTION: GAMEMD 0x7B6B60
//
// Append another instance. The source is taken through the empty-string
// substitution first, and the raw append's own null guard is then emitted
// against that already-substituted pointer -- the second test retail shows is
// the inlined guard, not a second source-level check.
WideStringClass& WideStringClass::operator+=(const WideStringClass& other)
{
    const wchar_t* src = other.Peek();
    if (src != 0) {
        Append(src);
    }
    return *this;
}

// FUNCTION: GAMEMD 0x7B6D90
//
// Erase `count` characters starting at `pos`. The range is clipped against the
// current length at both ends: a run overhanging the end slides back, a start
// that has gone negative gives its overshoot back to the count. An empty run
// after clipping fails. The removal itself is done by terminating the string
// at the cut, copying the head into a fresh block and concatenating the tail
// that begins just past the run.
short WideStringClass::Erase(int pos, int count)
{
    int len = (int)wcslen(Buffer);
    if (pos + count > len) {
        pos = len - count;
    }
    if (pos < 0) {
        count += pos;
        pos = 0;
    }
    if (count <= 0) {
        return 0;
    }

    wchar_t* fresh = (wchar_t*)::operator new((len - count + 1) * sizeof(wchar_t));
    Buffer[pos] = 0;
    Buffer[pos + count - 1] = 0;
    wcscpy(fresh, Buffer);
    wcscat(fresh, Buffer + pos + count);
    ::operator delete(Buffer);
    Buffer = fresh;
    return 1;
}

// FUNCTION: GAMEMD 0x7B6EC0
//
// Strip spaces and then tabs through the single-character remover 0x7B6E20.
void WideStringClass::FUN_007B6EC0()
{
    FUN_007B6E20(' ');
    FUN_007B6E20('\t');
}

// FUNCTION: GAMEMD 0x7B7060
//
// Discard the contents and reserve a zeroed block of `count` wide characters.
// A negative count leaves the string released and empty.
void WideStringClass::Resize(int count)
{
    Release();
    if (count >= 0) {
        int bytes = count * 2;
        Buffer = (wchar_t*)::operator new(bytes);
        memset(Buffer, 0, bytes);
    }
}

// FUNCTION: GAMEMD 0x7B7110
//
// The character at `index`, or 0 past the end.
wchar_t WideStringClass::FUN_007B7110(unsigned int index) const
{
    if (index < wcslen(Buffer)) {
        return Buffer[index];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7B7180
//
// A second copy of 0x7B7110.
wchar_t WideStringClass::FUN_007B7180(unsigned int index) const
{
    if (index < wcslen(Buffer)) {
        return Buffer[index];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7B7600
//
// Replace the contents with a raw wide string, reporting success. Same body as
// the assignment operator with a constant result in place of the object.
short WideStringClass::Set(const wchar_t* src)
{
    Release();
    Store(src);
    return 1;
}

// FUNCTION: GAMEMD 0x7B7660
//
// Store `ch` at `index` if it lies inside the string.
bool WideStringClass::FUN_007B7660(wchar_t ch, unsigned int index)
{
    if (index >= wcslen(Buffer)) {
        return false;
    }
    Buffer[index] = ch;
    return true;
}

// FUNCTION: GAMEMD 0x7B7690
//
// Replace the contents with at most `count` characters of `src`, always
// terminated at `count`. The block is one wide character larger than the run,
// the terminator is written before the copy so a null source leaves an empty
// string, and the bounded copy is wcsncpy rather than wcscpy.
short WideStringClass::Set(int count, const wchar_t* src)
{
    Release();
    Buffer = (wchar_t*)::operator new(count * 2 + 2);
    *Buffer = 0;
    if (src != 0) {
        wcsncpy(Buffer, src, count);
    }
    Buffer[count] = 0;
    return 1;
}

// FUNCTION: GAMEMD 0x7B76F0
//
// Lower-case the string in place. Only the plain ASCII upper-case range is
// touched; the length is re-measured on every iteration, so the loop is the
// un-rotated form retail shows.
void WideStringClass::MakeLower()
{
    for (unsigned int i = 0; i < Length(); ++i) {
        wchar_t ch = Buffer[i];
        if (ch >= L'A' && ch <= L'Z') {
            Buffer[i] = (wchar_t)tolower(ch);
        }
    }
}

// FUNCTION: GAMEMD 0x7B7740
//
// Build a lower-cased copy without touching this string. The contents are
// duplicated into a bare block first, the ASCII upper-case range is folded in
// place over that block through a walking cursor, the caller's object takes a
// second copy and the working block is freed. The result object is returned,
// which is how the caller's out-parameter reaches EAX.
WideStringClass* WideStringClass::AsLower(WideStringClass* out) const
{
    wchar_t* work = 0;
    if (Buffer != 0) {
        work = (wchar_t*)::operator new((wcslen(Buffer) + 1) * sizeof(wchar_t));
        wcscpy(work, Buffer);
    }

    unsigned int i = 0;
    wchar_t* cursor = work;
    for (; i < (work != 0 ? wcslen(work) : 0); ++i, ++cursor) {
        wchar_t ch = *cursor;
        if (ch >= L'A' && ch <= L'Z') {
            *cursor = (wchar_t)tolower(ch);
        }
    }

    out->Buffer = 0;
    if (work != 0) {
        out->Buffer = (wchar_t*)::operator new((wcslen(work) + 1) * sizeof(wchar_t));
        wcscpy(out->Buffer, work);
        ::operator delete(work);
    }
    return out;
}

// FUNCTION: GAMEMD 0x7B77E0
//
// Upper-case the string in place, the mirror of MakeLower over the ASCII
// lower-case range.
void WideStringClass::MakeUpper()
{
    for (unsigned int i = 0; i < Length(); ++i) {
        wchar_t ch = Buffer[i];
        if (ch >= L'a' && ch <= L'z') {
            Buffer[i] = (wchar_t)toupper(ch);
        }
    }
}

// FUNCTION: GAMEMD 0x7B7830
//
// The upper-casing mirror of AsLower over the ASCII lower-case range.
WideStringClass* WideStringClass::AsUpper(WideStringClass* out) const
{
    wchar_t* work = 0;
    if (Buffer != 0) {
        work = (wchar_t*)::operator new((wcslen(Buffer) + 1) * sizeof(wchar_t));
        wcscpy(work, Buffer);
    }

    unsigned int i = 0;
    wchar_t* cursor = work;
    for (; i < (work != 0 ? wcslen(work) : 0); ++i, ++cursor) {
        wchar_t ch = *cursor;
        if (ch >= L'a' && ch <= L'z') {
            *cursor = (wchar_t)toupper(ch);
        }
    }

    out->Buffer = 0;
    if (work != 0) {
        out->Buffer = (wchar_t*)::operator new((wcslen(work) + 1) * sizeof(wchar_t));
        wcscpy(out->Buffer, work);
        ::operator delete(work);
    }
    return out;
}
