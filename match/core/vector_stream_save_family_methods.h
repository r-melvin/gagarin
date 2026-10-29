// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x67A3C0 and its nine duplicates. Offsets come straight off
//   the instructions: the vector's Count at `[EBX+0x10]` (`MOV EAX,[EBX+0x10]`
//   into the frame slot whose address is then handed to the stream) and its
//   Items at `[EBX+4]` (`LEA EDX,[ECX+ESI*4]`, so a four-byte element). The
//   called slot is `[ECX+0x10]` with four stack arguments and the receiver
//   pushed first — IStream::Write, three IUnknown slots plus ISequentialStream
//   ::Read at +0x0C ahead of it — so the convention is the __stdcall COM
//   virtual, not __thiscall. The count and every element are written with a
//   length of 4 and a null pcbWritten.
//
//   All ten instances are byte-for-byte identical, relocations included: the
//   element type never reaches the code because every write goes through the
//   same COM slot with the same literal length. These entry points carry no
//   name in the binary or in the YRpp map and keep their placeholder names.
#ifndef GG_MATCH_CORE_VECTOR_STREAM_SAVE_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_STREAM_SAVE_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <objidl.h>
#include "type_list.h"

class AnimTypeClass;
class ParticleSystemTypeClass;
class VoxelAnimTypeClass;
class SmudgeTypeClass;
class BuildingTypeClass;
class UnitTypeClass;
class AircraftTypeClass;
class InfantryTypeClass;
class TerrainTypeClass;

// The native callsites pass a typed list as ECX and an IStream* on the stack.
// These are declarations only; the provider TU defines the bodies as explicit TypeList specializations.
// Declaration: GAMEMD 0x0067A4A0, TypeList<const AnimTypeClass*> helper.
template<> int TypeList<const AnimTypeClass*>::FUN_0067A4A0(IStream* stream);
// Declaration: GAMEMD 0x0067A520, TypeList<int> helper.
template<> int TypeList<int>::FUN_0067A520(IStream* stream);
// Declaration: GAMEMD 0x0067A3C0, TypeList<const VoxelAnimTypeClass*> helper.
template<> int TypeList<const VoxelAnimTypeClass*>::FUN_0067A3C0(IStream* stream);
// Declaration: GAMEMD 0x0067A630, TypeList<const SmudgeTypeClass*> helper.
template<> int TypeList<const SmudgeTypeClass*>::FUN_0067A630(IStream* stream);
// Declaration: GAMEMD 0x0067A6E0, TypeList<const BuildingTypeClass*> helper.
template<> int TypeList<const BuildingTypeClass*>::FUN_0067A6E0(IStream* stream);
// Declaration: GAMEMD 0x0067A770, TypeList<const UnitTypeClass*> helper.
template<> int TypeList<const UnitTypeClass*>::FUN_0067A770(IStream* stream);
// Declaration: GAMEMD 0x0067A7D0, TypeList<const AircraftTypeClass*> helper.
template<> int TypeList<const AircraftTypeClass*>::FUN_0067A7D0(IStream* stream);
// Declaration: GAMEMD 0x0067A850, TypeList<const InfantryTypeClass*> helper.
template<> int TypeList<const InfantryTypeClass*>::FUN_0067A850(IStream* stream);
// Declaration: GAMEMD 0x0067A8E0, TypeList<const TerrainTypeClass*> helper.
template<> int TypeList<const TerrainTypeClass*>::FUN_0067A8E0(IStream* stream);
// Declaration: GAMEMD 0x00717B20, TypeList<const ParticleSystemTypeClass*> helper.
template<> int TypeList<const ParticleSystemTypeClass*>::FUN_00717B20(IStream* stream);

#endif  // GG_MATCH_CORE_VECTOR_STREAM_SAVE_FAMILY_METHODS_H
