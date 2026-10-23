// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// GX adds allocation exception cleanup absent from native GetInstance.
//   Bodies reconstructed from the user's retail gamemd.exe v1.001 disassembly
//   (Ghidra CLI at 0x726350 + 0x726630), cross-checked against YRpp
//   Every offset reconfirmed numerically in the
//   companion header.
//
//   FUNCTION: GAMEMD 0x726350  TriggerClass::HasGlobalSetOrClearedEvent (__thiscall)
//   FUNCTION: GAMEMD 0x726630  TriggerClass::GetInstance               (__fastcall)
//   GLOBAL:   GAMEMD 0xA8EAE8  TriggerClass::Array (DynamicVectorClass<TriggerClass*>)

#include "trigger_class_more_methods.h"


// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x726350  TriggerClass::HasGlobalSetOrClearedEvent (__thiscall)
//
// True if this trigger's Type — or, when an AttachedTrigger exists, either
// Type — contains the given global-set/cleared event. With no AttachedTrigger
// the lone Type predicate's bool is returned directly.
// ---------------------------------------------------------------------------
bool TriggerClass::HasGlobalSetOrClearedEvent(int idxGlobal) const
{
    if (this->AttachedTrigger)
    {
        return this->Type->HasGlobalSetOrClearedEvent(idxGlobal)
            || this->AttachedTrigger->Type->HasGlobalSetOrClearedEvent(idxGlobal);
    }
    return this->Type->HasGlobalSetOrClearedEvent(idxGlobal);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x726630  TriggerClass::GetInstance (__fastcall — pType in ECX)
//
// The comparison is written with pType on the left. x86 has two encodings for a
// register/memory compare and VC6 picks by operand order: `pType == item->Type`
// gives retail's `3B` (`CMP ESI,[EBX+..]`), the other way round gives `39`
// (`CMP [EBX+..],ESI`). One byte, and the only thing that was keeping this
// function off byte parity.
//
// Returns the existing TriggerClass whose Type matches pType, scanning the
// global Array linearly; if none is found a fresh instance is allocated and
// constructed. A null pType (or a failed allocation) yields null.
// ---------------------------------------------------------------------------
TriggerClass* TriggerClass::GetInstance(TriggerTypeClass* pType)
{
    if (pType)
    {
        for (int i = 0; i < TriggerClass::Array.Count; ++i)
        {
            if (pType == ((TriggerClass**)TriggerClass::Array.Items)[i]->Type)
                return ((TriggerClass**)TriggerClass::Array.Items)[i];
        }

        return new TriggerClass(pType);
    }
    return 0;
}
