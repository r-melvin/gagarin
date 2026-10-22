// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and globals read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4E12D0. Signature cross-checked against YRpp
//   GadgetClass.h (`static int __fastcall GetColorScheme()`, consult-only, no
//   LICENSE).
//
// Lives in its own TU rather than gadget_class_methods.cpp because it needs
// neither the GadgetClass layout nor its vtable — it only reads two globals.
#ifndef GG_MATCH_UI_GADGET_CLASS_COLOR_METHODS_H
#define GG_MATCH_UI_GADGET_CLASS_COLOR_METHODS_H

// GLOBAL: GAMEMD 0x00822724 — the colour-scheme collection the lookup below
// indexes. Kept opaque: the retail body only passes it straight through.
extern void* ColorSchemeCollection;

// The collection's indexed accessor at 0x0068CA50. Genuinely __fastcall — retail
// loads the collection into ECX and the literal index into EDX rather than
// pushing either — and it returns null when the index is out of range. The name
// is descriptive; nothing in the binary attests a name for this address.
void* __fastcall ColorSchemeCollection_GetItem(void* collection, int index);

// The owning class. Nothing at this address touches an instance, so no layout
// is recovered here; the struct exists so the routine is spelled as the static
// member it is rather than as a free function, and so the next address on this
// class has somewhere to attach.
struct GadgetClass
{
    // The scheme index the UI is currently drawing gadgets with, or 0 when the
    // collection has no entry 1.
    static int __fastcall GetColorScheme();   // GAMEMD 0x4E12D0
};

#endif  // GG_MATCH_UI_GADGET_CLASS_COLOR_METHODS_H
