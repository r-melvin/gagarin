// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Each offset
//   and vtable slot reconfirmed below from the member-access disassembly; names
//   cross-checked against YRpp BitFont.h (consult-only, no LICENSE).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4346C0   BitFont::GetCharacterBitmap  (__thiscall)
//   FUNCTION: GAMEMD 0x434990   BitFont::UnLock              (__thiscall)

#include "bit_font.h"

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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
