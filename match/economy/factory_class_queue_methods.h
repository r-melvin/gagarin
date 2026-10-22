// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4CA620 / 0x4CA670), cross-checked
//   against YRpp
//   (every offset reconfirmed numerically below).
//
// Translation unit: FactoryClass production-queue mutators.
//   RemoveOneFromQueue  -> locates pItem in QueuedObjects (virtual FindItemIndex
//                          via [vtbl+0x10]) and shifts the tail down (inlined
//                          RemoveItem), returning whether anything was removed.
//   CountTotal          -> 1 if the in-production Object's type matches, plus
//                          every QueuedObjects entry that matches pType.
//
// Self-contained model (separate TU from factory_class_methods.h): the queue
// vector here carries the retail VectorClass vtable order so the genuine virtual
// FindItemIndex call lands at [vtbl+0x10]; the in-production Object's type
// getter is a genuine virtual at [vtbl+0x84].
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_QUEUE_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_QUEUE_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

class TechnoTypeClass;

// ---------------------------------------------------------------------------
// TechnoClass -- only the vtable shape CountTotal reaches.  GetTechnoType is a
// genuine virtual at byte offset 0x84 (slot 33); CountTotal does
// `Object->GetTechnoType() == pType` => MOV EAX,[ECX]; CALL [EAX+0x84].
// ---------------------------------------------------------------------------
class TechnoClass
{
public:
    virtual void _vt_00();  virtual void _vt_01();  virtual void _vt_02();
    virtual void _vt_03();  virtual void _vt_04();  virtual void _vt_05();
    virtual void _vt_06();  virtual void _vt_07();  virtual void _vt_08();
    virtual void _vt_09();  virtual void _vt_10();  virtual void _vt_11();
    virtual void _vt_12();  virtual void _vt_13();  virtual void _vt_14();
    virtual void _vt_15();  virtual void _vt_16();  virtual void _vt_17();
    virtual void _vt_18();  virtual void _vt_19();  virtual void _vt_20();
    virtual void _vt_21();  virtual void _vt_22();  virtual void _vt_23();
    virtual void _vt_24();  virtual void _vt_25();  virtual void _vt_26();
    virtual void _vt_27();  virtual void _vt_28();  virtual void _vt_29();
    virtual void _vt_30();  virtual void _vt_31();  virtual void _vt_32();
    virtual TechnoTypeClass* GetTechnoType() const;  // slot 33 == [vtbl+0x84]
};

// ---------------------------------------------------------------------------
// QueuedVectorClass -- concrete model of DynamicVectorClass<TechnoTypeClass*>.
//   sizeof = 0x18.  vptr@0x00, Items@0x04, Capacity@0x08, IsInitialized@0x0C,
//   IsAllocated@0x0D, Count@0x10, CapacityIncrement@0x14.
// Retail VectorClass vtable order (Remove issues FindItemIndex via [vtbl+0x10]):
//   0x00 ~VectorClass  0x04 operator==  0x08 SetCapacity  0x0C Clear
//   0x10 FindItemIndex 0x14 GetItemIndex 0x18 GetItem
// The virtuals are declared (no body) so cl emits the indirect vtable call;
// only the non-virtual RemoveItem is inlined to match.
// ---------------------------------------------------------------------------
class QueuedVectorClass
{
public:
    virtual ~QueuedVectorClass();                                          // 0x00
    virtual bool operator==(const QueuedVectorClass& other) const;        // 0x04
    virtual bool SetCapacity(int capacity, TechnoTypeClass const** pMem);  // 0x08
    virtual void Clear();                                                  // 0x0C
    virtual int  FindItemIndex(TechnoTypeClass const* const& item) const;  // 0x10
    virtual int  GetItemIndex(TechnoTypeClass const* const* pItem) const;  // 0x14
    virtual TechnoTypeClass const* GetItem(int index) const;              // 0x18

    bool RemoveItem(int index)
    {
        if (index < this->Count)
        {
            --this->Count;
            for (int i = index; i < this->Count; ++i)
                this->Items[i] = this->Items[i + 1];
            return true;
        }
        return false;
    }

    TechnoTypeClass const** Items;     // +0x04
    int           Capacity;            // +0x08
    bool          IsInitialized;       // +0x0C
    bool          IsAllocated;         // +0x0D
    int           Count;               // +0x10
    int           CapacityIncrement;   // +0x14
};

GG_STATIC_ASSERT(offsetof(QueuedVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(QueuedVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(QueuedVectorClass)          == 0x18);

// ---------------------------------------------------------------------------
// FactoryClass -- only the layout these two methods reach.  Base (AbstractClass
// + StageClass Production) occupies 0x00..0x40; QueuedObjects @0x40, the
// in-production Object pointer @0x58.
// ---------------------------------------------------------------------------
class FactoryClass
{
public:
    char              _base[0x40];     // +0x00  AbstractClass + Production
    QueuedVectorClass QueuedObjects;   // +0x40
    TechnoClass*      Object;          // +0x58

    bool RemoveOneFromQueue(TechnoTypeClass const* pItem);  // GAMEMD 0x4CA620 __thiscall
    int  CountTotal(TechnoTypeClass const* pType) const;    // GAMEMD 0x4CA670 __thiscall
};

GG_STATIC_ASSERT(offsetof(FactoryClass, QueuedObjects) == 0x40);
GG_STATIC_ASSERT(offsetof(FactoryClass, Object)        == 0x58);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_QUEUE_METHODS_H
