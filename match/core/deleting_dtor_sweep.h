// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every address, every destructor call target and every byte of the shared
//   body below was read off the user's own retail gamemd.exe v1.001 with the
//   local Ghidra CLI. No YRpp or seed-map name is bound here.
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
void __fastcall FUN_00437FC0(void* self);   // GAMEMD 0x437FC0
void __fastcall FUN_0047BB60(void* self);   // GAMEMD 0x47BB60
void __fastcall FUN_0048B1F0(void* self);   // GAMEMD 0x48B1F0
void __fastcall FUN_004C30B0(void* self);   // GAMEMD 0x4C30B0
void __fastcall FUN_004D1650(void* self);   // GAMEMD 0x4D1650
void __fastcall FUN_004D3590(void* self);   // GAMEMD 0x4D3590
void __fastcall FUN_004E1390(void* self);   // GAMEMD 0x4E1390
void __fastcall FUN_004F21A0(void* self);   // GAMEMD 0x4F21A0
void __fastcall FUN_00517D90(void* self);   // GAMEMD 0x517D90
void __fastcall FUN_0052AB80(void* self);   // GAMEMD 0x52AB80
void __fastcall FUN_00544A70(void* self);   // GAMEMD 0x544A70
void __fastcall FUN_005565A0(void* self);   // GAMEMD 0x5565A0
void __fastcall FUN_00558790(void* self);   // GAMEMD 0x558790
void __fastcall FUN_0055A6F0(void* self);   // GAMEMD 0x55A6F0
void __fastcall FUN_005652C0(void* self);   // GAMEMD 0x5652C0
void __fastcall FUN_005C1640(void* self);   // GAMEMD 0x5C1640
void __fastcall FUN_005D1B30(void* self);   // GAMEMD 0x5D1B30
void __fastcall FUN_005D2E30(void* self);   // GAMEMD 0x5D2E30
void __fastcall FUN_005D8C80(void* self);   // GAMEMD 0x5D8C80
void __fastcall FUN_005F3B80(void* self);   // GAMEMD 0x5F3B80
void __fastcall FUN_005F7400(void* self);   // GAMEMD 0x5F7400
void __fastcall FUN_0062E070(void* self);   // GAMEMD 0x62E070
void __fastcall FUN_006406F0(void* self);   // GAMEMD 0x6406F0
void __fastcall FUN_00652C00(void* self);   // GAMEMD 0x652C00
void __fastcall FUN_0065B2F0(void* self);   // GAMEMD 0x65B2F0
void __fastcall FUN_006AF4A0(void* self);   // GAMEMD 0x6AF4A0
void __fastcall FUN_006B1D00(void* self);   // GAMEMD 0x6B1D00
void __fastcall FUN_006B7010(void* self);   // GAMEMD 0x6B7010
void __fastcall FUN_006CB120(void* self);   // GAMEMD 0x6CB120
void __fastcall FUN_006E5CA0(void* self);   // GAMEMD 0x6E5CA0
void __fastcall FUN_006E8DE0(void* self);   // GAMEMD 0x6E8DE0
void __fastcall FUN_006F4500(void* self);   // GAMEMD 0x6F4500
void __fastcall FUN_00711AE0(void* self);   // GAMEMD 0x711AE0
void __fastcall FUN_0071B7B0(void* self);   // GAMEMD 0x71B7B0
void __fastcall FUN_00721880(void* self);   // GAMEMD 0x721880
void __fastcall FUN_007240B0(void* self);   // GAMEMD 0x7240B0
void __fastcall FUN_00726E00(void* self);   // GAMEMD 0x726E00
void __fastcall FUN_00735780(void* self);   // GAMEMD 0x735780
void __fastcall FUN_007499F0(void* self);   // GAMEMD 0x7499F0
void __fastcall FUN_0074C9F0(void* self);   // GAMEMD 0x74C9F0
void __fastcall FUN_00767300(void* self);   // GAMEMD 0x767300
void __fastcall FUN_007680C0(void* self);   // GAMEMD 0x7680C0
void __fastcall FUN_0076AFC0(void* self);   // GAMEMD 0x76AFC0
void __fastcall FUN_0076C6E0(void* self);   // GAMEMD 0x76C6E0
void __fastcall FUN_007B46F0(void* self);   // GAMEMD 0x7B46F0
void __fastcall FUN_007B6760(void* self);   // GAMEMD 0x7B6760
void __fastcall FUN_007B88D0(void* self);   // GAMEMD 0x7B88D0

struct Obj_477750 { void* FUN_477750(unsigned int flags); };  // FUNCTION: GAMEMD 0x477750
struct Obj_487E80 { void* FUN_487E80(unsigned int flags); };  // FUNCTION: GAMEMD 0x487E80
struct Obj_48BB00 { void* FUN_48BB00(unsigned int flags); };  // FUNCTION: GAMEMD 0x48BB00
struct Obj_48E660 { void* FUN_48E660(unsigned int flags); };  // FUNCTION: GAMEMD 0x48E660
struct Obj_4A59A0 { void* FUN_4A59A0(unsigned int flags); };  // FUNCTION: GAMEMD 0x4A59A0
struct Obj_4AEBB0 { void* FUN_4AEBB0(unsigned int flags); };  // FUNCTION: GAMEMD 0x4AEBB0
struct Obj_4AEBF0 { void* FUN_4AEBF0(unsigned int flags); };  // FUNCTION: GAMEMD 0x4AEBF0
// RTTI-confirmed (Tier 1, re-verified independently against the binary):
// vtable 0x7E81A4 (this function's own address at slot 0, the usual
// self-referential deleting-destructor slot) -> complete object locator
// @0x7E81A0 -> type descriptor 0x820280 -> name `.?AVEditClass@@`. See
// docs/naming_proposals.md #5.
struct EditClass { void* ScalarDeletingDestructor(unsigned int flags); };  // FUNCTION: GAMEMD 0x4B57D0
struct Obj_4B5810 { void* FUN_4B5810(unsigned int flags); };  // FUNCTION: GAMEMD 0x4B5810
struct Obj_4D2910 { void* FUN_4D2910(unsigned int flags); };  // FUNCTION: GAMEMD 0x4D2910
// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). FootClass's own vtable is 0x7E8C94.
//   0x4E0170 -> FootClass slot 8 (byte-off 0x20).
// That table is the only table in the image that holds it, so the slot is
// declared on FootClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct FootClass_4E0170 { void* FUN_4E0170(unsigned int flags); };  // FUNCTION: GAMEMD 0x4E0170
struct Obj_4E1AD0 { void* FUN_4E1AD0(unsigned int flags); };  // FUNCTION: GAMEMD 0x4E1AD0
struct Obj_4E30D0 { void* FUN_4E30D0(unsigned int flags); };  // FUNCTION: GAMEMD 0x4E30D0
struct Obj_4E30F0 { void* FUN_4E30F0(unsigned int flags); };  // FUNCTION: GAMEMD 0x4E30F0
struct Obj_4F2830 { void* FUN_4F2830(unsigned int flags); };  // FUNCTION: GAMEMD 0x4F2830
struct Obj_5172F0 { void* FUN_5172F0(unsigned int flags); };  // FUNCTION: GAMEMD 0x5172F0
struct Obj_523350 { void* FUN_523350(unsigned int flags); };  // FUNCTION: GAMEMD 0x523350
struct Obj_52AE00 { void* FUN_52AE00(unsigned int flags); };  // FUNCTION: GAMEMD 0x52AE00
struct Obj_52AEA0 { void* FUN_52AEA0(unsigned int flags); };  // FUNCTION: GAMEMD 0x52AEA0
struct Obj_52AEE0 { void* FUN_52AEE0(unsigned int flags); };  // FUNCTION: GAMEMD 0x52AEE0
struct Obj_54A170 { void* FUN_54A170(unsigned int flags); };  // FUNCTION: GAMEMD 0x54A170
struct Obj_558180 { void* FUN_558180(unsigned int flags); };  // FUNCTION: GAMEMD 0x558180
struct Obj_588BF0 { void* FUN_588BF0(unsigned int flags); };  // FUNCTION: GAMEMD 0x588BF0
struct Obj_5AC270 { void* FUN_5AC270(unsigned int flags); };  // FUNCTION: GAMEMD 0x5AC270
struct Obj_5B4610 { void* FUN_5B4610(unsigned int flags); };  // FUNCTION: GAMEMD 0x5B4610
struct Obj_5BB560 { void* FUN_5BB560(unsigned int flags); };  // FUNCTION: GAMEMD 0x5BB560
struct Obj_5C10D0 { void* FUN_5C10D0(unsigned int flags); };  // FUNCTION: GAMEMD 0x5C10D0
struct Obj_5C4F10 { void* FUN_5C4F10(unsigned int flags); };  // FUNCTION: GAMEMD 0x5C4F10
struct Obj_5C94D0 { void* FUN_5C94D0(unsigned int flags); };  // FUNCTION: GAMEMD 0x5C94D0
struct Obj_5D2700 { void* FUN_5D2700(unsigned int flags); };  // FUNCTION: GAMEMD 0x5D2700
struct Obj_5D3450 { void* FUN_5D3450(unsigned int flags); };  // FUNCTION: GAMEMD 0x5D3450
struct Obj_5F6DC0 { void* FUN_5F6DC0(unsigned int flags); };  // FUNCTION: GAMEMD 0x5F6DC0
struct Obj_5F9AE0 { void* FUN_5F9AE0(unsigned int flags); };  // FUNCTION: GAMEMD 0x5F9AE0
struct Obj_624480 { void* FUN_624480(unsigned int flags); };  // FUNCTION: GAMEMD 0x624480
struct Obj_6404B0 { void* FUN_6404B0(unsigned int flags); };  // FUNCTION: GAMEMD 0x6404B0
struct Obj_658780 { void* FUN_658780(unsigned int flags); };  // FUNCTION: GAMEMD 0x658780
struct Obj_65BED0 { void* FUN_65BED0(unsigned int flags); };  // FUNCTION: GAMEMD 0x65BED0
struct Obj_6AC780 { void* FUN_6AC780(unsigned int flags); };  // FUNCTION: GAMEMD 0x6AC780
struct Obj_6AC7A0 { void* FUN_6AC7A0(unsigned int flags); };  // FUNCTION: GAMEMD 0x6AC7A0
struct Obj_6B1390 { void* FUN_6B1390(unsigned int flags); };  // FUNCTION: GAMEMD 0x6B1390
struct Obj_6B8140 { void* FUN_6B8140(unsigned int flags); };  // FUNCTION: GAMEMD 0x6B8140
struct Obj_6CE220 { void* FUN_6CE220(unsigned int flags); };  // FUNCTION: GAMEMD 0x6CE220
struct Obj_6E64C0 { void* FUN_6E64C0(unsigned int flags); };  // FUNCTION: GAMEMD 0x6E64C0
struct Obj_6F0450 { void* FUN_6F0450(unsigned int flags); };  // FUNCTION: GAMEMD 0x6F0450
struct Obj_7106E0 { void* FUN_7106E0(unsigned int flags); };  // FUNCTION: GAMEMD 0x7106E0
struct Obj_7179A0 { void* FUN_7179A0(unsigned int flags); };  // FUNCTION: GAMEMD 0x7179A0
struct Obj_720210 { void* FUN_720210(unsigned int flags); };  // FUNCTION: GAMEMD 0x720210
struct Obj_723710 { void* FUN_723710(unsigned int flags); };  // FUNCTION: GAMEMD 0x723710
struct Obj_724C10 { void* FUN_724C10(unsigned int flags); };  // FUNCTION: GAMEMD 0x724C10
struct Obj_727CD0 { void* FUN_727CD0(unsigned int flags); };  // FUNCTION: GAMEMD 0x727CD0
struct Obj_72A210 { void* FUN_72A210(unsigned int flags); };  // FUNCTION: GAMEMD 0x72A210
struct Obj_72A670 { void* FUN_72A670(unsigned int flags); };  // FUNCTION: GAMEMD 0x72A670
struct Obj_746E80 { void* FUN_746E80(unsigned int flags); };  // FUNCTION: GAMEMD 0x746E80
struct Obj_74AB50 { void* FUN_74AB50(unsigned int flags); };  // FUNCTION: GAMEMD 0x74AB50
struct Obj_74F340 { void* FUN_74F340(unsigned int flags); };  // FUNCTION: GAMEMD 0x74F340
struct Obj_766A60 { void* FUN_766A60(unsigned int flags); };  // FUNCTION: GAMEMD 0x766A60
struct Obj_769C00 { void* FUN_769C00(unsigned int flags); };  // FUNCTION: GAMEMD 0x769C00
struct Obj_76B6F0 { void* FUN_76B6F0(unsigned int flags); };  // FUNCTION: GAMEMD 0x76B6F0
struct Obj_76EFE0 { void* FUN_76EFE0(unsigned int flags); };  // FUNCTION: GAMEMD 0x76EFE0
struct Obj_7AD2F0 { void* FUN_7AD2F0(unsigned int flags); };  // FUNCTION: GAMEMD 0x7AD2F0
struct Obj_7AD310 { void* FUN_7AD310(unsigned int flags); };  // FUNCTION: GAMEMD 0x7AD310
struct Obj_7AD330 { void* FUN_7AD330(unsigned int flags); };  // FUNCTION: GAMEMD 0x7AD330
struct Obj_7AD350 { void* FUN_7AD350(unsigned int flags); };  // FUNCTION: GAMEMD 0x7AD350
struct Obj_7AED20 { void* FUN_7AED20(unsigned int flags); };  // FUNCTION: GAMEMD 0x7AED20
struct Obj_7B1790 { void* FUN_7B1790(unsigned int flags); };  // FUNCTION: GAMEMD 0x7B1790
struct Obj_7BA3A0 { void* FUN_7BA3A0(unsigned int flags); };  // FUNCTION: GAMEMD 0x7BA3A0

#endif  // GG_MATCH_CORE_DELETING_DTOR_SWEEP_H
