// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU076 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x4c5000-0x4c5edf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The EMPulseClass block of retail .text (0x4C5000..0x4C5EDF): three of the
// unit's run-time initialisers, the constructors and destructor, the
// per-frame expiry sweep, the cell-flag clear and the primary-table slots 5,
// 8, 11, 12 and 13, in retail address order. EMPulseClass is declared in
// _layout/empulse_class.h.

#include <new.h>
#include "../_layout/empulse_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../core/header_tuning_globals.h"
#include "../core/frame_counter.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x8A3840
extern double DAT_008A3840;
// GLOBAL: GAMEMD 0x7E8728
const double DAT_007E8728 = 60.0;

// GLOBAL: GAMEMD 0x8A38A8
double DAT_008A38A8 = DAT_008A3840 / DAT_007E8728;

// GLOBAL: GAMEMD 0x8A3890
double DAT_008A3890 = 1.0 / DAT_008A38A8;

// GLOBAL: GAMEMD 0x8A3898
TuningCoordInit DAT_008A3898(128, 128, 0);

// GLOBAL: GAMEMD 0x8A3838 -- this unit's copy of the "no cell" value.
extern CellStruct DAT_008A3838;
// GLOBAL: GAMEMD 0xA8E9A0
extern bool DAT_00A8E9A0;

// GLOBAL: GAMEMD 0x87F7E8 -- the map: 0x5657E0 tests a cell, 0x5657A0 returns it.
struct Map_0087F7E8
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    CellClass* FUN_005657A0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x5657E0 (decl; reloc)
    bool FUN_005657E0(const CellStruct* cell);
};
extern Map_0087F7E8 DAT_0087F7E8;

// The append to EMPulseClass::Array, in the free-function shape of the inlined
// DynamicVectorClass::AddItem (as TagPtrVector_AddItem in tag_class_destroy_methods.h).
static inline bool EMPulse_AddItem(DynamicVectorClass<EMPulseClass*>& v, EMPulseClass* item)
{
    if (v.Count >= v.Capacity)
    {
        if (!v.IsAllocated && v.Capacity != 0)
            return false;
        if (v.CapacityIncrement <= 0)
            return false;
        if (!v.SetCapacity(v.Capacity + v.CapacityIncrement, 0))
            return false;
    }
    int i = v.Count++;
    v.Items[i] = item;
    return true;
}

// A cell displaced by (x, y).
static inline CellStruct EMPulse_Offset(const CellStruct& cell, int x, int y)
{
    CellStruct result;
    result.X = cell.X + x;
    result.Y = cell.Y + y;
    return result;
}

// SYNTHETIC: GAMEMD 0x4C5030

// SYNTHETIC: GAMEMD 0x4C5050

// SYNTHETIC: GAMEMD 0x4C51D0

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C52B0
EMPulseClass::EMPulseClass(CellStruct cell, int radius, int duration, TechnoClass* source)
    : unknown_24(cell), unknown_28(radius), unknown_2C(CurrentFrame), unknown_30(duration)
{
    vf_rtti_5();
    EMPulse_AddItem(Array, this);
    FUN_004C54E0(source);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C5370
EMPulseClass::EMPulseClass()
    : unknown_24(DAT_008A3838), unknown_28(0), unknown_2C(0), unknown_30(0)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C53B0
EMPulseClass::EMPulseClass(const AbstractNoInit& noInit) : AbstractClass(noInit)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C53E0
EMPulseClass::~EMPulseClass()
{
    if (DAT_00A8E9A0) {
        FUN_004C58C0();
    }
    AnnounceExpiredPointer(1);
    Array.RemoveItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C54A0
void __stdcall EMPulseClass::FUN_004C54A0()
{
    for (int i = Array.Count - 1; i >= 0; i--) {
        EMPulseClass* pulse = Array[i];
        if (CurrentFrame >= pulse->unknown_30 + pulse->unknown_2C) {
            delete pulse;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C58C0
// PARTIAL 64.9%: retail clears the flag with one `AND dword ptr [EAX+0x140],imm`; cl loads, masks and stores
// through a separately computed address, which shifts the loop tail. Tried: `&= ~0x80000u`, `&= ~0x80000`,
// `&= 0xFFF7FFFF`, and the cell built field by field instead of through EMPulse_Offset (25.0%).
void EMPulseClass::FUN_004C58C0()
{
    int radius2 = unknown_28 * unknown_28;
    for (int y = -unknown_28; y <= unknown_28; y++) {
        for (int x = -unknown_28; x <= unknown_28; x++) {
            CellStruct cell = EMPulse_Offset(unknown_24, x, y);
            if (cell.X >= 0 && cell.X < 512 && cell.Y >= 0 && cell.Y < 512
                && DAT_0087F7E8.FUN_005657E0(&cell)) {
                int dx = cell.X - unknown_24.X;
                int dy = cell.Y - unknown_24.Y;
                if (dy * dy + dx * dx <= radius2) {
                    DAT_0087F7E8.FUN_005657A0(&cell)->Flags &= ~0x80000u;
                }
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C59A0
void EMPulseClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D30(unknown_24.X);
    crc->FUN_004A1D30(unknown_24.Y);
    crc->FUN_004A1D50(unknown_28);
    crc->FUN_004A1D50(unknown_2C);
    crc->FUN_004A1D50(unknown_30);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C5A30
HRESULT __stdcall EMPulseClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) EMPulseClass(AbstractNoInit());
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C5AA0
int EMPulseClass::vf_12()
{
    return sizeof(EMPulseClass);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C5AB0
int EMPulseClass::vf_11()
{
    return 0x37;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C5AC0
// The scalar deleting destructor the compiler emits for ~EMPulseClass (slot 8).

// FUNCTION: GAMEMD 0x4C5EC0
// An unreferenced empty function at the end of the unit.
void FUN_004C5EC0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C5ED0
// An unreferenced empty function at the end of the unit.
void FUN_004C5ED0()
{
}
