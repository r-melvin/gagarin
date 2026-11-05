// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembled from retail gamemd.exe v1.001 at the addresses below (offsets read numerically).
//   Destructor of FactoryClass (0x4C9A10, expanded inside the scalar deleting form 0x4CA770), the
//   per-frame production step (slot 23), IPersistStream::Save (slot 6) and the checksum feed (slot 13).

#include <objidl.h>
#include "vector_class_operations.h"
#include "_layout/factory_class.h"
#include "_layout/techno_class.h"
#include "_layout/house_class.h"
#include "_layout/obj_004a1d30.h"

// GLOBAL: GAMEMD 0xA83E30 -- every FactoryClass in the game.
extern DynamicVectorClass<FactoryClass*> DAT_00A83E30;
// GLOBAL: GAMEMD 0xA8E9A0 -- non-zero while the game is in play.
extern char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xB0F720 -- the class-wide list of objects with a per-frame update.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F720;

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log, caller cleans the stack.
void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x4C9A10
FactoryClass::~FactoryClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A83E30.RemoveItem(this);
    if (DAT_00A8E9A0)
        AbandonProduction();
    DAT_00B0F720.RemoveItem(this);
}

// The stage advance of one production tick, expanded in place.
static inline bool AdvanceStage(StageClass* stage)
{
    if (stage->Timer.FUN_00426630() == 0 && stage->Rate) {
        stage->Value += stage->Step;
        stage->HasChanged = true;
        stage->Timer = CDTimerClass(stage->Rate);
        return true;
    }
    stage->HasChanged = false;
    return false;
}

// FUNCTION: GAMEMD 0x4C9B20
void FactoryClass::vf_23()
{
    if (!IsSuspended
        && (Object || SpecialItem)
        && !(Object && Production.Value == 0x36)
        && !(SpecialItem != -1 && Production.Value == 0x36)) {
        if (!AdvanceStage(&Production))
            return;
        IsDifferent = true;
        int cost;
        if (Object) {
            int remaining = 0x36 - Production.Value;
            cost = remaining ? Balance / remaining : Balance;
        } else {
            cost = 0;
        }
        if (cost >= Balance)
            cost = Balance;
        if (cost > Owner->vf_06()) {
            Production.Value--;
            OnHold = true;
        } else {
            Owner->FUN_004F9790(cost);
            OnHold = false;
            Balance -= cost;
        }
        if (Production.Value == 0x36) {
            IsSuspended = true;
            Production.SetRate(0);
            Owner->FUN_004F9790(Balance);
            Balance = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x4CA3C0
HRESULT __stdcall FactoryClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = QueuedObjects.Count;
        hr = pStm->Write(&count, 4, 0);
        if (hr >= 0) {
            for (int i = 0; i < count; i++) {
                hr = pStm->Write(&QueuedObjects.Items[i], 4, 0);
                if (hr < 0)
                    return 0;
            }
            hr = 0;
        }
    }
    return hr;
}

// FUNCTION: GAMEMD 0x4CA430
void FactoryClass::vf_13(Obj_004A1D30* crc)
{
    FUN_004068E0("Frame == %d\n", CurrentFrame);
    FUN_004068E0("QueuedObjects.Count() == %d\n", QueuedObjects.Count);
    FUN_004068E0("Object->RTTI == %d\n", Object->vf_11());
    FUN_004068E0("Object->HeapID == %d\n", Object->vf_16());
    FUN_004068E0("IsSuspended\t= %d\n", IsSuspended);
    FUN_004068E0("IsDifferent\t= %d\n", IsDifferent);
    FUN_004068E0("Balance\t= %d\n", Balance);
    FUN_004068E0("OriginalBalance = %d\n", OriginalBalance);
    FUN_004068E0("SpecialItem\t= %d\n", SpecialItem);
    FUN_004068E0("House->Fetch_ID()\t= %d\n", Owner->vf_rtti_4());
    FUN_004068E0("ID\t= %d\n", vf_rtti_4());
    AbstractClass::vf_13(crc);
    crc->FUN_004A1CA0(IsSuspended);
    crc->FUN_004A1CA0(IsDifferent);
    crc->FUN_004A1D50(Balance);
    crc->FUN_004A1D50(OriginalBalance);
    if (Object)
        crc->FUN_004A1D50(Object->vf_rtti_4());
    crc->FUN_004A1D50(SpecialItem);
    crc->FUN_004A1D50(Owner->vf_rtti_4());
}

// SYNTHETIC: GAMEMD 0x4CA770
// FactoryClass scalar deleting destructor (primary slot 8): the same destructor expanded in place.
