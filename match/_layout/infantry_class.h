// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: InfantryClass ctor FUN_0x00517A50 (chains FootClass ctor
//   FUN_0x004D31E0 at offset 0, CALL @0x00517A5B). Every member below is read
//   from a field-init store in that ctor. Argument identification: after the
//   four register pushes and the __thiscall FootClass call (which pops its own
//   stack argument), [ESP+0x14] is arg1 = pType, so the store
//   `MOV [ESI+0x6C0],ECX` @0x00517A6E installs Type at 0x6C0 — not 0x6C4.
//   sizeof is read from the allocation sites: `PUSH 0x6F0` before the ctor call
//   at 8 of the 8 call sites found by `ghidra x-ref to 0x517A50`.
//
//   RTTI (read from the binary): all four vptr targets resolve to
//   ".?AVInfantryClass@@" with COL base-offset 0 / 4 / 8 / 12.
//
//   Cross-read against YRpp: 11 named members claimed, 11
//   confirmed. No disagreement found.
//
// InfantryClass — a foot soldier. Derives FootClass at offset 0
// (sizeof(FootClass) == 0x6C0) and adds its own block from 0x6C0.
#ifndef GG_MATCH_LAYOUT_INFANTRY_CLASS_H
#define GG_MATCH_LAYOUT_INFANTRY_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "foot_class.h"
#include "infantry_type_class.h"

class InfantryClass : public FootClass
{
public:
    // CALLEE: GAMEMD 0x00517A50 (decl; reloc) -- constructor as the class factory calls it.
    InfantryClass(int unknown_arg0 = 0, int unknown_arg1 = 0);
    virtual HRESULT __stdcall Load(IStream* pStm);   // 5   0x521960
    virtual int vf_11();   // 11  0x523340
    virtual int vf_12();   // 12  0x5232F0
    // FUNCTION: GAMEMD 0x005224E0 (decl; reloc)
    // InfantryClass::FUN_005224E0
    bool FUN_005224E0();
    // FUNCTION: GAMEMD 0x00522100 -- jumpjet type whose locomotor has the jumpjet class ID.
    bool FUN_00522100();
    // FUNCTION: GAMEMD 0x00522550 -- start deploying; returns the delay in frames.
    int FUN_00522550();
    // IPersist::GetClassID (slot 3), 0x523300: copies InfantryClass's CLSID 0x7E9680.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    // IPersistStream::Save (slot 6), 0x521B00: chains FootClass::Save.
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);

    // Slots 341-342, introduced by InfantryClass (343 slots in all; retail table 0x7EB058).
    // Names are placeholders; argument counts come from RET n, return types are not recovered.
    virtual int vf_341();                                          // 341 0x5228D0
    virtual void vf_342(int a1, int a2, int a3);                   // 342 0x51D6F0

    // Overrides of base slots (primary table 0x7EB058, 343 slots).
    virtual void vf_10(void* a1, bool a2);                         // 10  0x51AA10
    virtual void vf_13(Obj_004A1D30* crc);                         // 13  0x521C90
    virtual const wchar_t* vf_36();                                // 36  0x51F2C0
    virtual bool vf_53();                                          // 53  0x51DF10
    virtual bool vf_58(const CoordStruct& coord);                  // 58  0x521760
    virtual void vf_60(CoordStruct* coord);                        // 60  0x5217C0
    virtual void vf_61(CoordStruct* coord);                        // 61  0x521850
    virtual int vf_185(AbstractClass* target);                     // 185 0x5218E0
    // Native primary slot 242: one stack dword.
    virtual void vf_242(AbstractClass* target);                                  // 242 0x51B1F0
    virtual int vf_243(AbstractClass* target, int a2);            // 243 0x51DF60
    virtual ObjectTypeClass* vf_51(bool a1);                       // 51  0x522640
    virtual HouseClass* vf_52(bool a1);                            // 52  0x5226C0
    virtual bool vf_80(int a1, CellStruct* a2, int a3, int a4);            // 80  0x51F250
    virtual void vf_85(int a1, int a2, bool a3);                   // 85  0x522600
    virtual int vf_138();                                          // 138 0x51F540
    virtual void vf_226(int a1);                                   // 226 0x522C00
    virtual int vf_139();                                          // 139 0x51F660
    virtual bool vf_225();                                         // 225 0x522BC0
    virtual void vf_284();                                         // 284 0x522780
    // Native primary slot 288: two stack dwords, target pointer and flag.
    virtual void SetDestination(AbstractClass* target, bool a2);   // 288 0x51AA40
    virtual void vf_326();                                         // 326 0x521C10
    virtual void vf_328(int a1);                                   // 328 0x521C60
    virtual CoordStruct vf_192(int a1);                            // 192 0x521D30
    virtual unsigned long DisguiseAs(AbstractClass* target);       // 283 0x522700
    virtual bool vf_81(int a1, int a2, int a3);                    // 81  0x51F190
    virtual CoordStruct vf_44(int a1, CoordStruct a2);             // 44  0x523250
    virtual bool vf_128();                                         // 128 0x521B60
    virtual void vf_266();                                         // 266 0x51F330

    // Non-virtual members (bodies in match/combat/Infantry.cpp).
    // FUNCTION: GAMEMD 0x522510 -- true for the four SequenceAnim values 0x1B-0x1E.
    int FUN_00522510();
    // FUNCTION: GAMEMD 0x522C30 -- no use of this; the stack argument is a sequence index.
    bool FUN_00522C30(int sequence);
    // FUNCTION: GAMEMD 0x522C60 -- no use of this; the stack argument is a sequence index.
    int FUN_00522C60(int sequence);
    // FUNCTION: GAMEMD 0x522CB0 -- true for the sequence values SequenceAnim currently holds in that set.
    int FUN_00522CB0();
    // FUNCTION: GAMEMD 0x522D30 -- true when vf_173() equals the 1.0 constant.
    bool FUN_00522D30();
    // FUNCTION: GAMEMD 0x522FC0 -- slot 97 reports 10.
    bool FUN_00522FC0();

    InfantryTypeClass* Type;            // +0x6C0  InfantryTypeClass*; ctor: MOV [ESI+0x6C0],ECX(=pType) @0x00517A6E
    int           SequenceAnim;         // +0x6C4  Sequence enum; ctor: MOV [ESI+0x6C4],0xFFFFFFFF @0x00517A64
    CDTimerClass  unknown_Timer_6C8;    // +0x6C8  (0xC) ctor: StartTime MOV [ESI+0x6C8],EDX(=[0x00A8ED84], the
                                        //         frame clock) @0x00517A7F; TimeLeft MOV [ESI+0x6D0],EBX(0)
                                        //         @0x00517A85. 0x6CC is the CDTimerClass clock slot the ctor
                                        //         does not store, exactly as in every other CDTimerClass here.
    unsigned int  PanicDurationLeft;    // +0x6D4  ctor: MOV [ESI+0x6D4],EBX(0) @0x00517A8C
    bool          PermanentBerzerk;     // +0x6D8  ctor: MOV byte [ESI+0x6D8],BL @0x00517A92
    bool          Technician;           // +0x6D9  ctor: MOV byte [ESI+0x6D9],BL @0x00517A98
    bool          unknown_bool_6DA;     // +0x6DA  ctor: MOV byte [ESI+0x6DA],BL @0x00517A9E
    bool          Crawling;             // +0x6DB  ctor: MOV byte [ESI+0x6DB],BL @0x00517AA4
    bool          unknown_bool_6DC;     // +0x6DC  ctor: MOV byte [ESI+0x6DC],BL @0x00517AAA
    bool          unknown_bool_6DD;     // +0x6DD  ctor: MOV byte [ESI+0x6DD],BL @0x00517AB0
    unsigned char align_6DE[2];         // +0x6DE
    unsigned int  unknown_6E0;          // +0x6E0  ctor: MOV [ESI+0x6E0],EBX(0) @0x00517AB6
    bool          ShouldDeploy;         // +0x6E4  ctor: MOV byte [ESI+0x6E4],BL @0x00517ABC
    unsigned char align_6E5[3];         // +0x6E5
    int           unknown_int_6E8;      // +0x6E8  ctor: MOV [ESI+0x6E8],2 @0x00517AC2
    unsigned int  unused_6EC;           // +0x6EC  (PROTECTED_PROPERTY; closes the object at 0x6F0)
};

GG_STATIC_ASSERT(offsetof(InfantryClass, Type)              == 0x6C0);
GG_STATIC_ASSERT(offsetof(InfantryClass, SequenceAnim)      == 0x6C4);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_Timer_6C8) == 0x6C8);
GG_STATIC_ASSERT(offsetof(InfantryClass, PanicDurationLeft) == 0x6D4);
GG_STATIC_ASSERT(offsetof(InfantryClass, PermanentBerzerk)  == 0x6D8);
GG_STATIC_ASSERT(offsetof(InfantryClass, Technician)        == 0x6D9);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_bool_6DA)  == 0x6DA);
GG_STATIC_ASSERT(offsetof(InfantryClass, Crawling)          == 0x6DB);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_bool_6DC)  == 0x6DC);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_bool_6DD)  == 0x6DD);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_6E0)       == 0x6E0);
GG_STATIC_ASSERT(offsetof(InfantryClass, ShouldDeploy)      == 0x6E4);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_int_6E8)   == 0x6E8);
GG_STATIC_ASSERT(offsetof(InfantryClass, unused_6EC)        == 0x6EC);
GG_STATIC_ASSERT(sizeof(InfantryClass)                      == 0x6F0);

// VTABLE: GAMEMD 0x007EB058  InfantryClass          (COL @0x007EB054, base 0)
// VTABLE: GAMEMD 0x007EB03C  InfantryClass::(+0x04) (base 4)
// VTABLE: GAMEMD 0x007EB034  InfantryClass::(+0x08) (base 8)
// VTABLE: GAMEMD 0x007EB02C  InfantryClass::(+0x0C) (base 12)

#endif  // GG_MATCH_LAYOUT_INFANTRY_CLASS_H
