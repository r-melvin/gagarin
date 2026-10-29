// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x7B66D0..0x7B7834.
//   The layout, the `__thiscall` conventions, the CRT helper addresses and every
//   constant below come from the retail disassembly.


#include "wide_string_class.h"

// FUNCTION: GAMEMD 0x7B66C0
// Default construction stores the null buffer and returns this.
Obj_007B66D0::Obj_007B66D0() : Buffer(0)
{
}

// FUNCTION: GAMEMD 0x7B66D0
//
// Construct from a raw wide string. The buffer slot is nulled first, then the
// source is measured (one extra for the terminator, or a bare one when there
// is no source), a fresh block of that many wide characters is allocated, the
// terminator is written straight away and the source, if any, is copied in.
Obj_007B66D0::Obj_007B66D0(const wchar_t* src)
{
    Buffer = 0;
    Store(src);
}

// FUNCTION: GAMEMD 0x7B6720
//
// Copy-construct: null the slot, then, when the other instance holds a
// buffer, allocate room for its characters plus the terminator and copy them.
Obj_007B66D0::Obj_007B66D0(const Obj_007B66D0& other)
{
    Buffer = 0;
    if (other.Buffer != 0) {
        Buffer = (wchar_t*)::operator new(wcslen(other.Buffer) * 2 + 2);
        wcscpy(Buffer, other.Buffer);
    }
}

// FUNCTION: GAMEMD 0x7B6760
// Ordinary wide-owner destruction releases its buffer and clears the member.
Obj_007B66D0::~Obj_007B66D0()
{
    Release();
}

// FUNCTION: GAMEMD 0x7B6780
//
// Compare with a raw wide string: two nulls are equal, one null is not, and
// otherwise the CRT comparison decides. Retail tests the wcscmp result and
// SETZ's it straight into AL (`test eax,eax; sete al`), the selection form of
// the result; the `== 0` comparison form gives cl's `neg/sbb/inc` instead.
bool Obj_007B66D0::FUN_007B6780(const wchar_t* text) const
{
    if (Buffer == 0 && text == 0) {
        return true;
    }
    if (Buffer != 0 && text != 0) {
        return wcscmp(Buffer, text) ? false : true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7B6880
//
// Assign a raw wide string. The old buffer is released and the slot nulled,
// then the same allocate-measure-copy body the constructor uses runs again.
Obj_007B66D0& Obj_007B66D0::operator=(const wchar_t* src)
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
Obj_007B66D0& Obj_007B66D0::operator=(const Obj_007B66D0& other)
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
bool Obj_007B66D0::Concat(const wchar_t* src)
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
Obj_007B66D0& Obj_007B66D0::operator+=(const wchar_t* src)
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
Obj_007B66D0& Obj_007B66D0::operator+=(const Obj_007B66D0& other)
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
short Obj_007B66D0::Erase(int pos, int count)
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
void Obj_007B66D0::FUN_007B6EC0()
{
    FUN_007B6E20(' ');
    FUN_007B6E20('\t');
}

// FUNCTION: GAMEMD 0x7B7040
// Clear a live wide owner without ending its lifetime.
void Obj_007B66D0::FUN_007B7040()
{
    Release();
}

// FUNCTION: GAMEMD 0x7B7060
//
// Discard the contents and reserve a zeroed block of `count` wide characters.
// A negative count leaves the string released and empty.
void Obj_007B66D0::Resize(int count)
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
wchar_t Obj_007B66D0::FUN_007B7110(unsigned int index) const
{
    if (index < wcslen(Buffer)) {
        return Buffer[index];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7B7180
//
// A second copy of 0x7B7110.
wchar_t Obj_007B66D0::FUN_007B7180(unsigned int index) const
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
short Obj_007B66D0::Set(const wchar_t* src)
{
    Release();
    Store(src);
    return 1;
}

// FUNCTION: GAMEMD 0x7B7660
//
// Store `ch` at `index` if it lies inside the string.
bool Obj_007B66D0::FUN_007B7660(wchar_t ch, unsigned int index)
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
short Obj_007B66D0::Set(int count, const wchar_t* src)
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
void Obj_007B66D0::FUN_007B76F0()
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
// Return an independently owned lower-case value. Native caller 0x77EBE5
// supplies temporary result storage and destroys it at 0x77EC0E.
Obj_007B66D0 Obj_007B66D0::AsLower() const
{
    Obj_007B66D0 work(*this);
    work.FUN_007B76F0();
    return work;
}

// FUNCTION: GAMEMD 0x7B77E0
//
// Upper-case the string in place, the mirror of FUN_007B76F0 over the ASCII
// lower-case range.
void Obj_007B66D0::FUN_007B77E0()
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
Obj_007B66D0 Obj_007B66D0::AsUpper() const
{
    Obj_007B66D0 work(*this);
    work.FUN_007B77E0();
    return work;
}

// FUNCTION: GAMEMD 0x7B69F0
// Appends at most `count` characters of `src`, reallocating the buffer.
bool Obj_007B66D0::FUN_007B69F0(int count, const wchar_t* src)
{
    wchar_t* old = Buffer;
    int len = count + 1;
    if (old != 0) {
        len += (int)wcslen(old);
    }
    Buffer = (wchar_t*)::operator new(len * 4);
    if (old != 0) {
        wcscpy(Buffer, old);
    } else {
        *Buffer = 0;
    }
    if (src != 0) {
        wcsncat(Buffer, src, count);
    }
    if (old != 0) {
        ::operator delete(old);
    }
    return true;
}

// FUNCTION: GAMEMD 0x7B6E20
// Removes every occurrence of `ch`; reports whether any was found.
// PARTIAL: 98.6% -- one store operand order ([edx+edi] against retail [edi+edx]).
bool Obj_007B66D0::FUN_007B6E20(wchar_t ch)
{
    bool removed = false;
    if (Buffer == 0) {
        return false;
    }
    int bytes = wcslen(Buffer);
    wchar_t* found = wcschr(Buffer, ch);
    if (found != 0) {
        removed = true;
        bytes = bytes * 2;
        do {
            memmove(found, found + 1, (bytes - (found - Buffer)) - 2);
            bytes -= 2;
            *(wchar_t*)((char*)Buffer + bytes) = 0;
            found = wcschr(Buffer, ch);
        } while (found != 0);
        wchar_t* copy = (wchar_t*)::operator new(wcslen(Buffer) * 2 + 2);
        wcscpy(copy, Buffer);
        ::operator delete(Buffer);
        Buffer = copy;
    }
    return removed;
}

// FUNCTION: GAMEMD 0x7B6EE0
// Removes the leading run of characters that all appear in `set`.
void Obj_007B66D0::FUN_007B6EE0(const Obj_007B66D0* set)
{
    unsigned int count = 0;
    while (count < Length()) {
        const wchar_t* chars = set->Buffer;
        if (chars == 0) {
            chars = WideEmptyString;
        }
        if (wcschr(chars, Buffer[count]) == 0) {
            break;
        }
        count++;
    }
    if (count > 0) {
        Erase(0, count);
    }
}

// FUNCTION: GAMEMD 0x7B6F40
// Removes the trailing run of characters that all appear in `set`.
// PARTIAL: 97.9% -- one `pop ebx` scheduled after the empty-string load instead of before it.
void Obj_007B66D0::FUN_007B6F40(const Obj_007B66D0* set)
{
    unsigned int i;
    if (Buffer == 0) {
        i = 0;
    } else {
        i = wcslen(Buffer);
    }
    while (i-- != 0) {
        const wchar_t* chars = set->Buffer;
        if (chars == 0) {
            chars = WideEmptyString;
        }
        if (wcschr(chars, Buffer[i]) == 0) {
            break;
        }
    }
    int count = i + 1;
    const wchar_t* source = WideEmptyString;
    if (Buffer != 0) {
        source = Buffer;
    }
    wchar_t* head = (wchar_t*)::operator new(count * 2 + 2);
    head[0] = 0;
    if (source) {
        wcsncpy(head, source, count);
    }
    head[count] = 0;
    const wchar_t* text = WideEmptyString;
    if (head != 0) {
        text = head;
    }
    Release();
    Store(text);
    if (head != 0) {
        ::operator delete(head);
    }
}
