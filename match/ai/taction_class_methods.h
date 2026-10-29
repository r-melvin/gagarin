// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (disasm at 0x6E3EE0 and 0x6E45E0), cross-checked against
//   YRpp (reconfirmed numerically here).
//
// TActionClass — trigger-action logic. The two methods matched here touch NO
// instance members of TActionClass:
//   * GetFlags(actionKind)        — a pure switch over the action id; the single
//     int argument arrives in ECX and the function ends in a plain `ret`, i.e.
//     it is __fastcall (NOT the stack-based __stdcall the YRpp wrapper implies).
//   * FindHouseByIndex(ptr,index) — a free __stdcall(2 args, `ret 8`) helper
//     that dispatches an opaque pointer / house index to four external callees.
// Later work (TAction.cpp, original TU attested by the assert string at 0x842BF8)
// adds the base class, the members it reads and the trigger-action handlers.
#ifndef GG_MATCH_AI_TACTION_CLASS_METHODS_H
#define GG_MATCH_AI_TACTION_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_class.h"

class HouseClass;
class ObjectClass;
class TriggerClass;
class TeamTypeClass;
class TagTypeClass;
class TriggerTypeClass;
struct CellStruct;
struct CoordStruct;

class TActionClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x6DD000 (decl; reloc) -- constructor, as the class factory calls it.
    TActionClass();
    // The stream loader's in-place construction: only the four tables.
    TActionClass(const AbstractNoInit& noInit) : AbstractClass(noInit) {}
    virtual ~TActionClass();                                              // 8   0x6E4660 (scalar deleting form)
    // Overrides of the slots AbstractClass leaves pure (primary table 0x7F443C,
    // slots 3, 5, 6, 11, 12), bodies elsewhere, plus the checksum slot.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6E3D70
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6E3DB0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6E3E30
    virtual int vf_11();                                                  // 11
    virtual int vf_12();                                                  // 12
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6E3E50
    virtual int vf_16();                                                  // 16  0x6E4650
    // FUNCTION: GAMEMD 0x6DD2C0 (slot 10)
    virtual void vf_10(void* target, bool removed);

    // BEGIN GENERATED
    // FUNCTION: GAMEMD 0x6E0050
    bool FUN_006E0050(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0080
    bool FUN_006E0080(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E02B0
    bool FUN_006E02B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0330
    bool FUN_006E0330(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E03B0
    bool FUN_006E03B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0790
    bool FUN_006E0790(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E07F0
    bool FUN_006E07F0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0850
    bool FUN_006E0850(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E08B0
    bool FUN_006E08B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E09A0
    bool FUN_006E09A0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0A20
    bool FUN_006E0A20(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0CA0
    bool FUN_006E0CA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0D00
    bool FUN_006E0D00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0DF0
    bool FUN_006E0DF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0E60
    bool FUN_006E0E60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1180
    bool FUN_006E1180(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E13A0
    bool FUN_006E13A0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E13E0
    bool FUN_006E13E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1440
    bool FUN_006E1440(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1760
    bool FUN_006E1760(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1A40
    bool FUN_006E1A40(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1E40
    bool FUN_006E1E40(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1EA0
    bool FUN_006E1EA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1F00
    bool FUN_006E1F00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2A10
    bool FUN_006E2A10(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2A50
    bool FUN_006E2A50(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2AA0
    bool FUN_006E2AA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2AF0
    bool FUN_006E2AF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2B70
    bool FUN_006E2B70(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2E60
    bool FUN_006E2E60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2EB0
    bool FUN_006E2EB0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2F50
    bool FUN_006E2F50(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2F90
    bool FUN_006E2F90(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E3000
    bool FUN_006E3000(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E3060
    bool FUN_006E3060(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E3380
    bool FUN_006E3380(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E38B0
    bool FUN_006E38B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E3F70
    CoordStruct FUN_006E3F70();
    // FUNCTION: GAMEMD 0x6E3FB0
    void FUN_006E3FB0(const unsigned char* text);
    // FUNCTION: GAMEMD 0x6E4010
    const char* FUN_006E4010();
    // FUNCTION: GAMEMD 0x6E4080
    bool FUN_006E4080(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E4100
    bool FUN_006E4100(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E4150
    bool FUN_006E4150(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E43E0
    bool FUN_006E43E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E4460
    bool FUN_006E4460(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E44E0
    bool FUN_006E44E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // END GENERATED
    // GAMEMD 0x6DD8B0 __thiscall (decl; reloc) -- run the action.
    bool Execute(HouseClass* pHouse, ObjectClass* pObject, TriggerClass* pTrigger,
                 const CellStruct& location);

    // r15 handlers (taction_r15_methods.cpp).
    // FUNCTION: GAMEMD 0x6E01C0
    bool FUN_006E01C0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0930
    bool FUN_006E0930(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0AA0
    bool FUN_006E0AA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E16D0
    bool FUN_006E16D0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2600
    bool FUN_006E2600(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2BB0
    bool FUN_006E2BB0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E4040
    bool FUN_006E4040(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0B60
    bool FUN_006E0B60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E18B0
    bool FUN_006E18B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E1980
    bool FUN_006E1980(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E2970
    bool FUN_006E2970(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x6E0EF0
    bool FUN_006E0EF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);

    // w3 handlers (taction_w3_methods.cpp).
    // FUNCTION: GAMEMD 0x006E0480
    bool FUN_006E0480(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E0F90
    bool FUN_006E0F90(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E2860
    bool FUN_006E2860(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E28E0
    bool FUN_006E28E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E2F00
    bool FUN_006E2F00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E1BD0
    bool FUN_006E1BD0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E1C40
    bool FUN_006E1C40(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E1DC0
    bool FUN_006E1DC0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E1E00
    bool FUN_006E1E00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E1F60
    bool FUN_006E1F60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    // FUNCTION: GAMEMD 0x006E2660
    bool FUN_006E2660(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);

    unsigned char unknown_24[4];     // +0x24
    TActionClass* unknown_28;        // +0x28
    int           unknown_2C;        // +0x2C
    TeamTypeClass* unknown_30;       // +0x30
    unsigned char unknown_34[0x10];  // +0x34
    int           unknown_44;        // +0x44 waypoint index
    unsigned char unknown_48[4];     // +0x48
    TagTypeClass* unknown_4C;        // +0x4C
    TriggerTypeClass* unknown_50;    // +0x50
    char          unknown_54[0x19];  // +0x54
    char          unknown_6D[0x20];  // +0x6D text, NUL at +0x8C
    unsigned char unknown_8D[3];     // +0x8D
    int           unknown_90;        // +0x90 action parameter

    // Pre-existing static members (matched in taction_class_methods.cpp).
    // GAMEMD 0x6E3EE0 — returns a flag bitfield for a given action id.
    // The retail single-arg form is register-passed (ECX) with a plain ret:
    // model it as __fastcall so cl emits the `add ecx,-0xe` / jump-table form.
    static int GetFlags(int actionKind);

    // GAMEMD 0x6E45E0 — resolve a house from (opaque source ptr, house index).
    // Free helper: two stack args, callee-cleaned 8 bytes (__stdcall).
    static int __stdcall FindHouseByIndex(void* pSource, int index);
};

GG_STATIC_ASSERT(offsetof(TActionClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(TActionClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(TActionClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(TActionClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(TActionClass, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(TActionClass, unknown_6D) == 0x6D);
GG_STATIC_ASSERT(offsetof(TActionClass, unknown_90) == 0x90);

GG_STATIC_ASSERT(sizeof(TActionClass) == 0x94);


// VTABLE: GAMEMD 0x007F443C  TActionClass
// VTABLE: GAMEMD 0x007F4420  TActionClass::(+0x04)
// VTABLE: GAMEMD 0x007F4418  TActionClass::(+0x08)
// VTABLE: GAMEMD 0x007F4410  TActionClass::(+0x0C)

#endif // GG_MATCH_AI_TACTION_CLASS_METHODS_H
