// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI at the address in each annotation. FootClass vtable is 0x7E8C94.
//
// Round 17 FootClass slot overrides, ascending by retail address.
// Address index: 0x4D8560 0x4D9C10 0x4DA1D0 0x4DA4E0 0x4DE630
#include "../_layout/foot_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/cell_class.h"
#include "../core/mission_class_methods.h"
#include "loco_com.h"

// FUNCTION: GAMEMD 0x6EC300 (decl; reloc) -- asks the team whether it is enabled.
char FUN_006EC300(int linked);

// FUNCTION: GAMEMD 0x4D8560
// The coordinate this object is heading for: the target of slot 22 on the first
// target, else on the destination, else the TechnoClass default (also when the
// mission is 1).
CoordStruct FootClass::vf_267()
{
    if (vf_97() != 1) {
        if (unknown_5A0 != 0) {
            return ((AbstractClass*)unknown_5A0)->vf_22();
        }
        if (Destination != 0) {
            return ((AbstractClass*)Destination)->vf_22();
        }
    }
    return TechnoClass::vf_267();
}

// FUNCTION: GAMEMD 0x4D9C10
// Asks the locomotor whether it can enter the cell, but only when the caller's flag is set.
// PARTIAL: 92.6% -- retail tests the flag argument as a byte; it is declared int here.
int FootClass::vf_107(CellClass* cell, int a2, int a3, int a4, int a5)
{
    if (Locomotor != 0 && a5 != 0) {
        int coords = *(int*)&cell->MapCoords;
        return (*(ILocomotionPtr*)&Locomotor)->CanEnterCell(coords);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4DA1D0
// Usable when in play and either the type flag, the spawned flag, mission 4, or
// an enabled team says so.
bool FootClass::vf_200()
{
    if (!IsInPlayfield)
        return false;
    if (((TechnoTypeClass*)vf_33())->bools_C8C[8] || Spawned || vf_97() == 4
        || (Team != 0 && FUN_006EC300((int)Team)))
        return true;
    return false;
}

// The TechnoClass body that slot 26 falls back to.
struct TechnoView_004DA4E0 : TechnoClass
{
    // FUNCTION: GAMEMD 0x703860 (decl; reloc)
    int FUN_00703860(int a1, int a2);
};

// FUNCTION: GAMEMD 0x4DA4E0
// The locomotor's visual character for the argument when it has one, else the TechnoClass handling.
int FootClass::vf_26(int a1, int a2)
{
    if (Locomotor != 0) {
        int r = (*(ILocomotionPtr*)&Locomotor)->VisualCharacter(a1);
        if (r != 0)
            return r;
    }
    return ((TechnoView_004DA4E0*)this)->FUN_00703860(a1, a2);
}

// FUNCTION: GAMEMD 0x4DE630
// After the TechnoClass handling, a gunner type with exactly one passenger runs slot 309 as well.
void FootClass::vf_229(FootClass* a1)
{
    TechnoClass::vf_229(a1);
    if (vf_33()->Gunner && Passengers.NumPassengers == 1)
        vf_309((int)a1);
}

// The TechnoClass part of the save, reached by a qualified call.
struct TechnoSaveView_004DB690 : TechnoClass
{
    // FUNCTION: GAMEMD 0x70C250 (decl; reloc)
    HRESULT __stdcall FUN_0070C250(IStream* pStm, BOOL fClearDirty);
};

// FUNCTION: GAMEMD 0x4DB690
// Saves the TechnoClass part, then the two target lists (a count and the entries
// of each) and the locomotor as an OLE persistent stream.
HRESULT __stdcall FootClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ((TechnoSaveView_004DB690*)this)->FUN_0070C250(pStm, fClearDirty);
    if (hr >= 0) {
        int count = unknown_abstract_array_588.Count;
        HRESULT wr = pStm->Write(&count, 4, 0);
        if (wr < 0)
            return wr;
        for (int i = 0; i < count; i++) {
            wr = pStm->Write(&((int*)unknown_abstract_array_588.Items)[i], 4, 0);
            if (wr < 0)
                return wr;
        }
        count = NavQueue.Count;
        wr = pStm->Write(&count, 4, 0);
        if (wr < 0)
            return wr;
        for (int j = 0; j < count; j++) {
            wr = pStm->Write(&((int*)NavQueue.Items)[j], 4, 0);
            if (wr < 0)
                return wr;
        }
        IPersistStreamPtr persist((ILocomotion*)Locomotor);
        OleSaveToStream(persist, pStm);
        hr = 0;
    }
    return hr;
}
