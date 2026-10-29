// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every address, every destructor call target and every byte of the shared
//   body below was read off the user's own retail gamemd.exe v1.001 with the
//   local Ghidra CLI. No YRpp name is bound here.
//
// Scalar deleting destructors, swept as one family.
//
// MSVC emits one of these (`??_G`) for every class with a virtual destructor:
// it runs the real destructor on `this`, frees the object only when bit 0 of
// the caller's flag argument is set, and returns the pointer. Retail's shape is
// exactly thirty bytes:
//
//     PUSH ESI; MOV ESI,ECX; CALL <real dtor>
//     TEST byte ptr [ESP+8],1; JZ +9; PUSH ESI; CALL 0x7C8B3D; ADD ESP,4
//     MOV EAX,ESI; POP ESI; RET 4
//
// All 70 remaining members of this sweep family are byte-identical once the destructor call
// displacement is masked; the free target is 0x7C8B3D in every one. They are
// written longhand, one struct per class, because letting cl generate `??_G`
// from a real virtual destructor inlines a trivial destructor body into the
// thunk and loses the CALL that has to be there.
//
// The flag argument is declared `unsigned int` so the callee pops four bytes
// (`RET 4`), even though retail only ever tests its low byte. The classes are
// opaque: the body touches no member, so no layout is reconstructed and there
// is nothing to assert an offsetof against.
#ifndef GG_MATCH_CORE_DELETING_DTOR_SWEEP_H
#define GG_MATCH_CORE_DELETING_DTOR_SWEEP_H

extern "C" void __cdecl FUN_007C8B3D(void* block);   // GAMEMD 0x7C8B3D operator delete

// The real destructors, declared only so cl emits reloc-normalised calls.
void FUN_0047BB60(void* self);   // GAMEMD 0x47BB60
void FUN_0048B1F0(void* self);   // GAMEMD 0x48B1F0
void FUN_004D1650(void* self);   // GAMEMD 0x4D1650
void FUN_004D3590(void* self);   // GAMEMD 0x4D3590
void FUN_004E1390(void* self);   // GAMEMD 0x4E1390
void FUN_004F21A0(void* self);   // GAMEMD 0x4F21A0
void FUN_00517D90(void* self);   // GAMEMD 0x517D90
void FUN_00544A70(void* self);   // GAMEMD 0x544A70
void FUN_005565A0(void* self);   // GAMEMD 0x5565A0
void FUN_00558790(void* self);   // GAMEMD 0x558790
void FUN_0055A6F0(void* self);   // GAMEMD 0x55A6F0
void FUN_005652C0(void* self);   // GAMEMD 0x5652C0
void FUN_005C1640(void* self);   // GAMEMD 0x5C1640
void FUN_005D1B30(void* self);   // GAMEMD 0x5D1B30
void FUN_005D2E30(void* self);   // GAMEMD 0x5D2E30
void FUN_005D8C80(void* self);   // GAMEMD 0x5D8C80
void FUN_005F3B80(void* self);   // GAMEMD 0x5F3B80
void FUN_005F7400(void* self);   // GAMEMD 0x5F7400
void FUN_0062E070(void* self);   // GAMEMD 0x62E070
void FUN_006406F0(void* self);   // GAMEMD 0x6406F0
void FUN_00652C00(void* self);   // GAMEMD 0x652C00
void FUN_0065B2F0(void* self);   // GAMEMD 0x65B2F0
void FUN_006AF4A0(void* self);   // GAMEMD 0x6AF4A0
void FUN_006B1D00(void* self);   // GAMEMD 0x6B1D00
void FUN_006B7010(void* self);   // GAMEMD 0x6B7010
void FUN_006CB120(void* self);   // GAMEMD 0x6CB120
void FUN_006E5CA0(void* self);   // GAMEMD 0x6E5CA0
void FUN_006F4500(void* self);   // GAMEMD 0x6F4500
void FUN_00711AE0(void* self);   // GAMEMD 0x711AE0
void FUN_0071B7B0(void* self);   // GAMEMD 0x71B7B0
void FUN_00721880(void* self);   // GAMEMD 0x721880
void FUN_007240B0(void* self);   // GAMEMD 0x7240B0
void FUN_00726E00(void* self);   // GAMEMD 0x726E00
void FUN_00735780(void* self);   // GAMEMD 0x735780
void FUN_007499F0(void* self);   // GAMEMD 0x7499F0
void FUN_0074C9F0(void* self);   // GAMEMD 0x74C9F0
void FUN_0076C6E0(void* self);   // GAMEMD 0x76C6E0
void FUN_007B46F0(void* self);   // GAMEMD 0x7B46F0
void FUN_007B6760(void* self);   // GAMEMD 0x7B6760

struct Obj_487E80 { void* FUN_487E80(unsigned int flags); };  // FUNCTION: GAMEMD 0x487E80
struct Obj_5D2700 { void* FUN_5D2700(unsigned int flags); };  // FUNCTION: GAMEMD 0x5D2700 (decl)

#endif  // GG_MATCH_CORE_DELETING_DTOR_SWEEP_H
