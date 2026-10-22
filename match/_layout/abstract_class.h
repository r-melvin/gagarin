// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: retail constructor 0x00410170, the RTTI descriptors and the four
//   AbstractClass vtables below. YRpp AbstractClass.h was consulted for naming
//   hypotheses only.
//
//   RTTI: COL of vtable 0x7E1F50 -> TypeDescriptor ".?AVAbstractClass@@",
//   class hierarchy descriptor (attributes 1 = multiple inheritance), base
//   array in declaration order:
//     AbstractClass        (7 bases)  +0x00
//     IPersistStream (AU)  (2 bases)  +0x00  -> IPersist -> IUnknown
//     IRTTITypeInfo  (AU)  (1 base)   +0x04  -> IUnknown
//     INoticeSink    (AV)  (0 bases)  +0x08
//     INoticeSource  (AV)  (0 bases)  +0x0C
//   The COLs of 0x7E1F34 / 0x7E1F2C / 0x7E1F24 carry offsets 4 / 8 / 0xC.
//
// AbstractClass — the root of every game object and, via AbstractTypeClass,
// every INI type. It derives four COM-style interfaces (abstract_interfaces.h).
// The constructor stores the INoticeSink / INoticeSource interface tables
// first (their implicit constructors), then the four AbstractClass tables.
#ifndef GG_MATCH_LAYOUT_ABSTRACT_CLASS_H
#define GG_MATCH_LAYOUT_ABSTRACT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_interfaces.h"

// Returned by value from slots 18, 19 and 22 (defined in object_class.h).
struct CoordStruct;
// The checksum sink slot 13 feeds (0x4A1CA0 / 0x4A1D50; _layout/obj_004a1d30.h).
struct Obj_004A1D30;

// The argument of the no-initialisation constructor 0x4101C0 (RET 4, the
// argument is never read). Placeholder name.
struct AbstractNoInit { };

// The AbstractClass flag byte at +0x14. Bit 0 marks a TechnoClass and bit 2 a
// FootClass (readers test the bit before a checked downcast); bit 1's meaning
// is not recovered.
struct AbstractFlagBits
{
    bool IsTechno     : 1;          // bit 0
    bool unknown_14_1 : 1;          // bit 1
    bool IsFoot       : 1;          // bit 2
};
GG_STATIC_ASSERT(sizeof(AbstractFlagBits) == 1);

// AbstractClass base  (0x00..0x23, sizeof = 0x24)
// VTABLE: GAMEMD 0x7E1F50 (IPersistStream side, slots 0-23)
// VTABLE: GAMEMD 0x7E1F34 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E1F2C (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E1F24 (INoticeSource side, +0x0C)
class AbstractClass : public IPersistStream, public IRTTITypeInfo,
                      public INoticeSink, public INoticeSource
{
public:
    // FUNCTION: GAMEMD 0x410170 (declaration; native base constructor)
    AbstractClass();
    // FUNCTION: GAMEMD 0x4101C0 (declaration; no-initialisation constructor)
    AbstractClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x7258D0 (declaration; ECX receiver, DL flag)
    void __fastcall AnnounceExpiredPointer(unsigned char removed);

    // IUnknown (slots 0-2 of the primary table; the IRTTITypeInfo side reaches
    // them through the adjustor thunks 0x4105E0 / 0x4105F0 / 0x410600).
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0  0x410260
    virtual ULONG __stdcall AddRef();                                     // 1  0x410300
    virtual ULONG __stdcall Release();                                    // 2  0x410310
    // IPersist::GetClassID (slot 3) stays pure here.
    virtual HRESULT __stdcall IsDirty();                                  // 4  0x410450
    virtual HRESULT __stdcall Load(IStream* pStm) = 0;                    // 5  pure (body 0x410380)
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) = 0;  // 6  pure (body 0x410320)
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);       // 7  0x4103E0

    // IRTTITypeInfo overrides (slots 3-5 of 0x7E1F34), compiled with the +0x04
    // subobject as `this`.
    virtual int __stdcall vf_rtti_3();    // 0x410210: returns slot 11
    virtual int __stdcall vf_rtti_4();    // 0x410220: returns UniqueID
    virtual void __stdcall vf_rtti_5();   // 0x410230: assigns UniqueID

    // INoticeSink / INoticeSource overrides (0x7E1F2C / 0x7E1F24 slot 0).
    virtual bool Notice(int id, int arg); // 0x410580: returns false, RET 8
    virtual void vf_0(int arg);           // 0x410590: bare RET 4

    // FUNCTION: GAMEMD 0x4101F0 (declaration; native base destructor; slot 8
    // holds the scalar deleting destructor 0x4105A0)
    virtual ~AbstractClass();
    // Slots 9-23. Names are placeholders unless noted; argument counts come
    // from each body's RET n (thiscall) and return types from its EAX/AL use.
    virtual void vf_9();                                  // 9   0x410470: bare RET
    virtual void vf_10(void* target, bool removed);       // 10  0x410480: RET 8
    virtual int vf_11() = 0;                              // 11  pure (called by 0x410210)
    virtual int vf_12() = 0;                              // 12  pure
    virtual void vf_13(Obj_004A1D30* crc);                // 13  0x410410: RET 4, feeds the checksum sink
    virtual int vf_14();                                  // 14  0x410490: returns -1
    virtual int vf_15();                                  // 15  0x4104A0: returns 0
    virtual int vf_16();                                  // 16  0x4104B0: returns 0
    virtual bool vf_17();                                 // 17  0x410440: returns true
    virtual CoordStruct vf_18();                          // 18  0x4104C0: a coordinate by value
    virtual CoordStruct vf_19(int a1);                    // 19  0x4104F0: returns vf_18()
    virtual bool IsOnFloor() const;                       // 20  0x410520: returns false
    virtual bool IsInAir() const;                         // 21  0x410530: returns false
    virtual CoordStruct vf_22();                          // 22  0x410540: returns vf_18()
    virtual void vf_23();                                 // 23  0x410570: bare RET

    // The primary (IPersistStream-side) vtable pointer at +0x00, for code that
    // dispatches through slot views not yet modelled as virtuals.
    void* const& PrimaryVTable() const { return *reinterpret_cast<void* const*>(this); }

    int   UniqueID;                 // +0x10
    // +0x14: the flag byte. Retail only ever touches it with byte operations:
    // the constructor clears bits 0-2 with MOV CL,[EAX+0x14]; AND CL,0xF8
    // (0x41018B), readers test it with TEST byte ptr [reg+0x14],1 / 4, and the
    // passenger walk extracts bit 2 with MOV CL,[EAX+0x14]; SHR CL,2; AND CL,1.
    // That is bool bit-field code, so the flags are modelled as bit-fields.
    AbstractFlagBits Flags;         // +0x14
    int   unknown_18;               // +0x18
    long  RefCount;                 // +0x1C
    unsigned char Dirty;            // +0x20  (bool)
    unsigned char _pad_21[3];       // +0x21
};

// Subobject offsets (RTTI base array; constructor stores at +0/+4/+8/+0xC):
// VC6 cannot fold a base-pointer conversion into a constant expression, so the
// four bases are pinned by their 4-byte sizes (abstract_interfaces.h), their
// declaration order and the first data member at +0x10.
GG_STATIC_ASSERT(offsetof(AbstractClass, UniqueID)      == 0x10);
GG_STATIC_ASSERT(offsetof(AbstractClass, Flags)         == 0x14);
GG_STATIC_ASSERT(offsetof(AbstractClass, unknown_18)    == 0x18);
GG_STATIC_ASSERT(offsetof(AbstractClass, RefCount)      == 0x1C);
GG_STATIC_ASSERT(offsetof(AbstractClass, Dirty)         == 0x20);
GG_STATIC_ASSERT(sizeof(AbstractClass)                  == 0x24);

#endif  // GG_MATCH_LAYOUT_ABSTRACT_CLASS_H
