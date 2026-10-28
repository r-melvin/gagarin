// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x629390 (ParasiteClass no-init constructor): AbstractClass no-init
//   constructor, two timers restarted at +0x2C and +0x38, a zero at +0x40 and the four vtable pointers.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Address index: 0x629210 / 0x6292B0 constructors, 0x62AF70 scalar deleting destructor, 0x629390 ParasiteClass::ParasiteClass(AbstractNoInit const&), 0x6294D0 ParasiteClass::vf_13.
//   The class is declared locally with only the members these bodies touch.

#include <stddef.h>
#include "../_layout/abstract_class.h"
#include "../_layout/frame_timer.h"
#include "../_layout/obj_004a1d30.h"
#include "../_layout/object_class.h"
#include "vector_class_operations.h"
#include <new.h>
#include "../_layout/swizzle_manager_class.h"

class ParasiteClass : public AbstractClass
{
public:
    ParasiteClass();
    ParasiteClass(void* owner);
    ParasiteClass(const AbstractNoInit& noInit);
    virtual ~ParasiteClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    virtual void vf_13(Obj_004A1D30* crc);

    void* Owner;          // +0x24
    int unknown_28;       // +0x28
    CDTimerClass TimerA;  // +0x2C
    CDTimerClass TimerB;  // +0x38
    ObjectClass* Subject;     // +0x44
    int unknown_48;       // +0x48
    int unknown_4C;       // +0x4C
    int unknown_50;       // +0x50
    bool unknown_54;      // +0x54
};
GG_STATIC_ASSERT(offsetof(ParasiteClass, Owner) == 0x24);
GG_STATIC_ASSERT(offsetof(ParasiteClass, TimerA) == 0x2C);
GG_STATIC_ASSERT(offsetof(ParasiteClass, TimerB) == 0x38);
GG_STATIC_ASSERT(offsetof(ParasiteClass, Subject) == 0x44);
GG_STATIC_ASSERT(offsetof(ParasiteClass, unknown_54) == 0x54);

// FUNCTION: GAMEMD 0x629390
ParasiteClass::ParasiteClass(const AbstractNoInit& noInit) : AbstractClass(noInit), TimerA(0), TimerB(0)
{
}

// FUNCTION: GAMEMD 0x6294D0
// Feeds the base checksum, the subject's runtime type id and the parasite's own state words into the checksum.
void ParasiteClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    if (Subject) {
        crc->FUN_004A1D50(Subject->vf_rtti_4());
    }
    crc->FUN_004A1D50(unknown_48);
    crc->FUN_004A1D50(unknown_4C);
    crc->FUN_004A1D50(unknown_50);
    crc->FUN_004A1CA0(unknown_54);
}

// GLOBAL: GAMEMD 0xAC4910 -- the parasite registry.
extern DynamicVectorClass<ParasiteClass*> DAT_00AC4910;
// GLOBAL: GAMEMD 0xB0F5B8 -- the registry of parasites that hold a victim.
extern DynamicVectorClass<ParasiteClass*> DAT_00B0F5B8;

// FUNCTION: GAMEMD 0x629210
// Default constructor: both timers restarted, then registered.
ParasiteClass::ParasiteClass() : TimerA(0), TimerB(0)
{
    DynamicVectorClass<ParasiteClass*>& v = DAT_00AC4910;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = this;
}

// FUNCTION: GAMEMD 0x6292B0
// Constructor taking the owner: clears the state words and registers the parasite.
ParasiteClass::ParasiteClass(void* owner) : TimerA(0), TimerB(0)
{
    Owner = owner;
    unknown_28 = 0;
    TimerB = CDTimerClass(0);
    CDTimerClass restart(0);
    unknown_54 = false;
    TimerA = restart;
    unknown_4C = 0;
    unknown_50 = 0;
    Subject = 0;
    unknown_48 = 0;
    DynamicVectorClass<ParasiteClass*>& v = DAT_00AC4910;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = this;
}

// SYNTHETIC: GAMEMD 0x62AF70 -- the scalar deleting destructor (??_G) with this body expanded into it
// Releases the subject and leaves both registries; the base destructor runs last. Retail also keeps an
// unreferenced out-of-line copy at 0x6293E0 that this build does not reproduce.
__forceinline ParasiteClass::~ParasiteClass()
{
    unknown_4C = 0;
    unknown_50 = 0;
    unknown_48 = 0;
    if (Subject) {
        Subject->vf_62();
        Subject = 0;
    }
    if (unknown_54) {
        DAT_00B0F5B8.RemoveItem(this);
        unknown_54 = false;
    }
    DAT_00AC4910.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6295B0
// Loads the base state, rebuilds the object in place, re-registers it when it holds a victim and queues
// its three pointers for swizzling.
HRESULT __stdcall ParasiteClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr >= 0) {
        new (this) ParasiteClass(AbstractNoInit());
        if (Subject) {
            DynamicVectorClass<ParasiteClass*>& v = DAT_00B0F5B8;
            bool room = true;
            if (v.Count >= v.Capacity) {
                room = false;
                if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
                    room = v.SetCapacity(v.CapacityIncrement + v.Capacity, 0);
                }
            }
            if (room) {
                int index = v.Count++;
                v.Items[index] = this;
            }
        }
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_28);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Subject);
    }
    return hr;
}
