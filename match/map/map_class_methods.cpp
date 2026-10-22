// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Names/signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x48DC90  MapClass::UnselectAll          (__fastcall)
//   FUNCTION: GAMEMD 0x48DF80  MapClass::GetLandTypeFromName  (__fastcall)

#include "map_class_methods.h"

// ---------------------------------------------------------------------------
// Externs reconfirmed numerically from the disasm at the listed addresses.
// ---------------------------------------------------------------------------

// ObjectClass::CurrentObjects @ 0x00A8ECB8.  Disasm touches Items (+0x04 =>
// 0x00A8ECBC) and Count (+0x10 => 0x00A8ECC8).
extern DynamicVectorClassLayout CurrentObjects;

// Case-insensitive string compare (retail __cdecl helper @ 0x007C8D20).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

// Trailing helpers invoked by UnselectAll (not matched here — declared so cl
// emits reloc-normalised calls):
//   0x00731D00  __fastcall(arg in ECX)   — clears a selection-drag latch pair.
//   0x00431060  __fastcall(this in ECX)  — clears the per-cell select flags of
//                                          the global selection grid @ 0x0089C3B0.
void __fastcall sub_731D00(void* a);
void __fastcall sub_431060(void* self);
extern int DAT_0089C3B0;  // selection grid base @ 0x0089C3B0

// __thiscall (ECX=this), no explicit args, vtable slot at +0x150 — the per-object
// "remove from CurrentObjects" virtual driving the drain loop.
typedef void (__fastcall* UnselectFn)(void* self);


// LandType name table @ 0x0081DA28 .. 0x0081DA58 (12 const char* entries:
// "Clear","Road","Water","Rock","Wall","Tiberium",...). Loop bound is the
// one-past pointer 0x0081DA58.
extern const char* const LandTypeName[12];


// FUNCTION: GAMEMD 0x5865E0  MapClass::IsLocationFogged (__thiscall)
// Retail stub: always false. The argument is accepted and ignored (RET 0x4).
bool MapClass::IsLocationFogged(CoordStruct const* coords) const
{
    return false;
}
