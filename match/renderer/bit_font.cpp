// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Each offset
//   and vtable slot reconfirmed below from the member-access disassembly; names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x433880   BitFont::BitFont              (__thiscall)
//   FUNCTION: GAMEMD 0x433940   BitFont::~BitFont            (__thiscall)
//   FUNCTION: GAMEMD 0x433CA0   BitFont::FUN_00433CA0        (__thiscall)
//   FUNCTION: GAMEMD 0x433CE0   BitFont::SwapFlag             (__thiscall)
//   FUNCTION: GAMEMD 0x434100   BitFont::SwapTabWidth         (__thiscall)
//   FUNCTION: GAMEMD 0x4346C0   BitFont::GetCharacterBitmap  (__thiscall)
//   FUNCTION: GAMEMD 0x434700   BitFont::FUN_00434700         (__thiscall)
//   FUNCTION: GAMEMD 0x434840   BitFont::Intersect             (__thiscall)
//   FUNCTION: GAMEMD 0x4348F0   BitFont::Lock                  (__thiscall)
//   SYNTHETIC: GAMEMD 0x434A40   BitFont scalar deleting destructor
//   FUNCTION: GAMEMD 0x434990   BitFont::UnLock                (__thiscall)

#include "bit_font.h"
#include "../ui/surface_desc_ctor_methods.h"
#include <stddef.h>
#include <stdlib.h>

// FUNCTION: GAMEMD 0x433880
//
// Construct the descriptor from a key: reset it to the empty 1x1 state, look the
// key up, and adopt the width and height it reports. If the lookup fails the
// reset runs again, which puts the object back to empty after the failed
// assignment to +0x4.
//
// The success path returns early rather than skipping the second reset with an
// else; retail has two epilogues (0x4338F2 and the tail), so the early return is
// the shape.
BitFont::BitFont(const char* key) throw()
{
    this->Reset();

    this->InternalPTR = FUN_00433990(key);
    if (this->InternalPTR != 0) {
        this->Width = this->InternalPTR->Width;
        this->unknown_1C = this->InternalPTR->Height;
        this->FUN_00434700();
        return;
    }

    this->Reset();
    return;
}

// LIBRARY: GAMEMD 0x7C93E8 — CRT free.
// LIBRARY: GAMEMD 0x7C8B3D — operator delete used by the destructor.
extern "C" void __cdecl FUN_007C93E8(void* block);
// FUNCTION: GAMEMD 0x433940
BitFont::~BitFont()
{
    void* block = Pointer_8;
    if (block) FUN_007C93E8(block);
    BitFontInternalData* data = InternalPTR;
    if (data) {
        if (data->SymbolTable) ::operator delete(data->SymbolTable);
        if (data->Bitmaps) ::operator delete(data->Bitmaps);
        ::operator delete(data);
    }
}

// FUNCTION: GAMEMD 0x433CA0
void BitFont::FUN_00433CA0(const BitFontBounds* src)
{
    if (src != 0) {
        Bounds.Left = src->Left;
        Bounds.Top = src->Top;
        Bounds.Right = src->Right;
        Bounds.Bottom = src->Bottom;
        return;
    }
    Bounds.Bottom = 0;
    Bounds.Right = 0;
    Bounds.Top = 0;
    Bounds.Left = 0;
}

// FUNCTION: GAMEMD 0x433CE0
unsigned char BitFont::SwapFlag(unsigned char value)
{
    unsigned char previous = unknown_40;
    unknown_40 = value;
    return previous;
}

// FUNCTION: GAMEMD 0x434100
int BitFont::SwapTabWidth(int value)
{
    int previous = unknown_28;
    unknown_28 = value;
    return previous;
}

// FUNCTION: GAMEMD 0x4346C0  BitFont::GetCharacterBitmap  (__thiscall)
// Look up the glyph index for wch in the font's symbol table; return a pointer
// into the packed bitmap data, or null when the font/glyph is absent.
//   MOV ECX,[ECX+0x4]   -> InternalPTR
//   MOV DX,[EDI+ESI*2]  -> SymbolTable[(unsigned short)wch]  (zero-extended)
//   IMUL SymbolDataSize, (symbol-1); ADD Bitmaps
// ---------------------------------------------------------------------------
unsigned char* BitFont::GetCharacterBitmap(wchar_t wch)
{
    unsigned char* result = 0;
    BitFontInternalData* data = this->InternalPTR;
    if (data)
    {
        int symbol = data->SymbolTable[wch];
        if (symbol)
            result = (unsigned char*)(data->SymbolDataSize * (symbol - 1) + data->Bitmaps);
    }
    return result;
}

// LIBRARY: GAMEMD 0x7C9430
// The retail call targets the CRT allocator; its body is out of scope.
extern "C" void* __cdecl malloc(size_t size);
// FUNCTION: GAMEMD 0x434700
void BitFont::FUN_00434700()
{
    unsigned char* output = (unsigned char*)malloc(this->InternalPTR->unknown_08 * this->InternalPTR->Width + 2);
    this->Pointer_8 = output;

    if (this->InternalPTR != 0) {
        unsigned int glyph = this->InternalPTR->SymbolTable[0x58];
        if (glyph != 0) {
            unsigned char* source = reinterpret_cast<unsigned char*>(this->InternalPTR->Bitmaps) + this->InternalPTR->SymbolDataSize * (glyph - 1);
            if (source != 0) {
                unsigned char* sourceRow = source + 1;
                *output = *source;
                output = (unsigned char*)this->Pointer_8;
                output++;

                int y = 0;
                if ((unsigned int)this->InternalPTR->unknown_08 > 0) {
                    do {
                        int x = 0;
                        if ((unsigned int)this->InternalPTR->Width > 0) {
                            do {
                                *output = (unsigned char)~*sourceRow;
                                ++output;
                                ++sourceRow;
                                ++x;
                            } while ((unsigned int)x < (unsigned int)this->InternalPTR->Width);
                        }
                        ++y;
                    } while ((unsigned int)y < (unsigned int)this->InternalPTR->unknown_08);
                }
            }
        }
    }
}

GG_STATIC_ASSERT(offsetof(BitFont, InternalPTR) == 0x04);
GG_STATIC_ASSERT(offsetof(BitFont, Pointer_8) == 0x08);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Left) == 0x00);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Right) == 0x08);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Bottom) == 0x0C);
GG_STATIC_ASSERT(sizeof(LTRBStruct) == 0x10);
// FUNCTION: GAMEMD 0x434840
bool BitFont::Intersect(LTRBStruct* out, LTRBStruct* a, LTRBStruct* b)
{
    if (a->Top > b->Bottom || b->Top > a->Bottom ||
        a->Left > b->Right || b->Left > a->Right) {
        out->Left = 0;
        out->Top = 0;
        out->Right = -1;
        out->Bottom = -1;
        return false;
    }

    *out = *a;
    if (out->Top < b->Top) {
        out->Top = b->Top;
    }
    if (out->Left < b->Left) {
        out->Left = b->Left;
    }
    if (out->Bottom > b->Bottom) {
        out->Bottom = b->Bottom;
    }
    if (out->Right > b->Right) {
        out->Right = b->Right;
    }
    return true;
}

// FUNCTION: GAMEMD 0x4348F0
//
// Bind the font to a surface for drawing: lock the surface's pixels at the
// origin, note its stride in 16-bit words, and settle the clip rectangle. With
// no clip set (all four edges zero) the whole surface becomes the clip;
// otherwise the existing clip is intersected with the surface rectangle.
//
// Two phrasing facts carry the match. The origin is a by-value Point2D built
// member by member, which is what puts each zero in its own register for the
// two pushes; the rectangle's zero edges are assigned after the pitch call so
// they stay immediate stores placed before the width call. The clip copy is
// member-wise: a whole-struct assignment moves the same dwords but addresses
// them through the LEA'd pointer instead of `this`.
void BitFont::Lock(Surface* surface)
{
    LTRBStruct rect;
    Point2D origin;

    origin.X = 0;
    origin.Y = 0;
    pGraphBuffer = static_cast<short*>(surface->Lock(origin));
    PitchDiv2 = surface->GetPitch() >> 1;

    rect.Left = 0;
    rect.Top = 0;
    rect.Right = surface->GetWidth() - 1;
    rect.Bottom = surface->GetHeight() - 1;

    if ((Bounds.Right | Bounds.Bottom | Bounds.Top | Bounds.Left) == 0) {
        Bounds.Left = rect.Left;
        Bounds.Top = rect.Top;
        Bounds.Right = rect.Right;
        Bounds.Bottom = rect.Bottom;
    } else {
        Intersect(&Bounds, &Bounds, &rect);
    }
}

// SYNTHETIC: GAMEMD 0x434A40

// FUNCTION: GAMEMD 0x434990  BitFont::UnLock  (__thiscall)
// Unlock the backing surface (virtual slot 0x60) and clear the cached glyph
// buffer pointer + pitch. Returns false unconditionally (EAX zeroed after the
// call, reused for both member stores and the return).
// ---------------------------------------------------------------------------
int BitFont::UnLock(Surface* pSurface)
{
    pSurface->Unlock();
    this->pGraphBuffer = 0;
    this->PitchDiv2 = 0;
    return 0;
}
