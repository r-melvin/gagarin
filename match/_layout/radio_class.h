// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: RadioClass ctor FUN_0x0065A750 (chains MissionClass ctor
//   FUN_0x005B2DA0 at offset 0). Field offsets read from its init writes:
//   RadioLinks vptr @0xE0 (param[0x38]), RadioLinks.Items @0xE4 (param[0x39],
//   operator_new(4)), RadioLinks.Capacity @0xE8 (param[0x3A]=1),
//   RadioLinks.IsInitialized @0xEC (byte param[0x3B]=1); LastCommands[0..2]
//   @0xD4/0xD8/0xDC (param[0x35..0x37]=0). RadioLinks ends at 0xF0 ->
//   sizeof(RadioClass)==0xF0. Cross-checked vs YRpp.
//
// RadioClass — base of every object that can hold radio links (docked units,
// transports, mind-control, etc.). Derives MissionClass at offset 0 and adds
// the radio command history + the link vector from 0xD4.
#ifndef GG_MATCH_LAYOUT_RADIO_CLASS_H
#define GG_MATCH_LAYOUT_RADIO_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "mission_class.h"
#include "../core/vector_class.h"

class TechnoClass;  // RadioLinks element type (used by-pointer only)

// RadioClass  (0xD4..0xEF, sizeof = 0xF0)
// Retail RTTI 0x817B38 establishes the class key; public access preserves this ABI view.
class RadioClass : public MissionClass
{
public:
    // Native Radio overrides. Declaration-only external bodies remain unclaimed.
    // Declaration: GAMEMD 0x65AB80 -- primary slot5, stdcall this+stream.
    virtual HRESULT __stdcall Load(IStream* pStm);
    // Declaration: GAMEMD 0x65AC40 -- primary slot6, stdcall this+stream+BOOL.
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    // Declaration: GAMEMD 0x65AAC0 -- primary slot10, ECX receiver/RET8.
    virtual void vf_10(void* target, bool removed);
    // Declaration: GAMEMD 0x65AB10 -- primary slot13, ECX receiver/RET4.
    virtual void vf_13(Obj_004A1D30* crc);
    // Declaration: GAMEMD 0x65AA80 -- primary slot53, byte result/RET.
    virtual bool vf_53();
    // Declaration: GAMEMD 0x65A820 -- primary slot101, three DWORD ABI arguments.
    virtual int vf_101(int a1, int event, int a3);

    // Radio-link queries/mutators (defined in core/tu189_radio_class.cpp).
    // Non-virtual; declaring them here does not change the layout.
    TechnoClass* FUN_0065AD30(int index);               // GAMEMD 0x65AD30: RadioLinks item `index` (RET 4)
    TechnoClass* FUN_0065AD40(int index);               // GAMEMD 0x65AD40
    bool ContainsLink(const TechnoClass* pLink) const;  // GAMEMD 0x65AD50
    int  FindLinkIndex(const TechnoClass* pLink) const;  // GAMEMD 0x65AD90
    // FUNCTION: GAMEMD 0x65AD90 (decl; reloc) -- the same entry with the argument of the object slots (BuildingClass 0x447B20).
    int  FindLinkIndex(const AbstractClass* pLink) const;
    bool HasFreeLink() const;                            // GAMEMD 0x65ADC0
    bool HasFreeLinkFor(RadioClass* who) const;          // GAMEMD 0x65ADF0
    bool HasAnyLink() const;                             // GAMEMD 0x65AE30
    void SetLinkCount(int count);                        // GAMEMD 0x65AE60

    // Slots 157-160, introduced by RadioClass (161 slots in all, RTTI
    // ".?AVRadioClass@@" on 0x7F0508). Names are placeholders; argument
    // counts come from RET n, return types provisionally from EAX/AL use.
    virtual int vf_157(int a1);                                    // 157 0x65ACB0
    virtual int vf_158(int command, RadioClass* peer);                            // 158 0x65AAA0
    virtual int vf_159(int command, void* data, RadioClass* peer);                    // 159 0x65A970
    virtual void vf_160(int a1);                                   // 160 0x65ACE0

    // FUNCTION: GAMEMD 0x65A750 (default constructor)
    RadioClass();
    // FUNCTION: GAMEMD 0x65A7E0 (no-init constructor)
    RadioClass(const AbstractNoInit& noInit);

    int         LastCommands[3];   // +0xD4  (RadioCommand enum x3)
    VectorClass<TechnoClass*> RadioLinks;        // +0xE0  (0x10; docked units etc.)
};

GG_STATIC_ASSERT(offsetof(RadioClass, LastCommands) == 0xD4);
GG_STATIC_ASSERT(offsetof(RadioClass, RadioLinks)   == 0xE0);
// Native 0x65A750 installs VectorClass<TechnoClass*> table 0x7E180C at +0xE0.
GG_STATIC_ASSERT(offsetof(RadioClass, RadioLinks) + offsetof(VectorClass<TechnoClass*>, Items) == 0xE4);
GG_STATIC_ASSERT(offsetof(RadioClass, RadioLinks) + offsetof(VectorClass<TechnoClass*>, Capacity) == 0xE8);
GG_STATIC_ASSERT(offsetof(RadioClass, RadioLinks) + offsetof(VectorClass<TechnoClass*>, IsInitialized) == 0xEC);
GG_STATIC_ASSERT(offsetof(RadioClass, RadioLinks) + offsetof(VectorClass<TechnoClass*>, IsAllocated) == 0xED);
GG_STATIC_ASSERT(sizeof(VectorClass<TechnoClass*>) == 0x10);
GG_STATIC_ASSERT(sizeof(RadioClass)                 == 0xF0);

#endif  // GG_MATCH_LAYOUT_RADIO_CLASS_H
