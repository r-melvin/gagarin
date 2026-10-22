// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// BuildingClass entries 0x458A80..0x459F20 of the "building-b" cluster (views: building_b_views.h).

#include <new.h>
#include "building_b_views.h"

// The local list of cleared objects: a DynamicVectorClass with a growth step of ten.
class BuildingBClearedList : public BuildingBVector<BuildingBObjectView>
{
public:
    BuildingBClearedList() : BuildingBVector<BuildingBObjectView>(0, 0)
    {
        CapacityIncrement = 10;
        Count = 0;
    }
};

// FUNCTION: GAMEMD 0x458A80
// CAPPED at 10.4% (28 of 268 instructions; 267 retail vs 268 compiled; retail-only 2 `xor`, `jmp`, `jne`;
// compiled-only 2 `cmp`, 3 `je`). The frame is 0x38 against retail 0x34, which shifts every stack offset, and retail
// tests the object and cell pointers with `cmp reg,ebx` against its zero register where cl emits `test`.
// Variants tried: base + offset copy (kept), base + *footprint++ and *footprint++ + base direct sums.
bool BuildingBView::vf_292(HBCoord* where, int dir)
{
    HBCell* footprint = vf_66(0);
    HBCell base = BuildingBCellOf(*where);
    BuildingBClearedList cleared;
    while (!(footprint->X == 0x7FFF && footprint->Y == 0x7FFF)) {
        HBCell offset = *footprint++;
        HBCell at = base + offset;
        BuildingBCellView* cell = BuildingBMap.Func_5657A0(&at);
        if (cell->SmudgeIndex != -1) {
            cell->SmudgeIndex = -1;
            cell->unknown_11E = 0;
            cell->unknown_40 = 0;
        }
        for (BuildingBObjectView* object = cell->FirstObject; object; object = cell->FirstObject) {
            if (!(object->unknown_14 & 1) || object->vf_11() == 6) {
                for (int i = cleared.Count - 1; i >= 0; i--) {
                    BuildingBObjectView* item = cleared.Items[i];
                    HBCoord home = item->Location;
                    if (!item->vf_54(&home, 0))
                        item->vf_62();
                }
                return false;
            }
            cleared.AddItem(object);
            object->vf_53();
        }
    }
    if (vf_54(where, dir)) {
        for (int i = cleared.Count - 1; i >= 0; i--) {
            BuildingBObjectView* item = cleared.Items[i];
            HBCell itemCell;
            HBCell zero(0, 0);
            HBCell start = *item->vf_110(&itemCell);
            HBCell found = *BuildingBMap.Func_56DC20(&itemCell, &start, item->vf_33()->unknown_67C, -1, 0, 0, 1, 1, 0,
                                                            0, 0, 1, &zero, 0, 0);
            HBCoord landing;
            if (!item->vf_54(BuildingBMap.Func_5657A0(&found)->vf_18(&landing), 0))
                item->vf_62();
        }
        return true;
    }
    vf_62();
    for (int i = cleared.Count - 1; i >= 0; i--) {
        BuildingBObjectView* item = cleared.Items[i];
        HBCoord home = item->Location;
        if (!item->vf_54(&home, 0))
            item->vf_62();
    }
    return false;
}

// FUNCTION: GAMEMD 0x458DB0
bool BuildingBView::vf_171()
{
    if (vf_256())
        return true;
    return Func_701120();
}

// FUNCTION: GAMEMD 0x458DD0
bool BuildingBView::vf_256()
{
    return Type->unknown_157B && Type->unknown_157C && vf_258() > 0;
}

// FUNCTION: GAMEMD 0x458E00
int BuildingBView::vf_257()
{
    int limit = Type->Func_45ECA0(0);
    if (Type->Func_45EC90() < limit)
        return Type->Func_45EC90() / 2;
    return Type->Func_45ECA0(0) / 2;
}

// FUNCTION: GAMEMD 0x459870
int BuildingBView::vf_181()
{
    return Type->unknown_1524;
}

// FUNCTION: GAMEMD 0x459880
int BuildingBView::vf_182()
{
    return Type->unknown_1528;
}

// FUNCTION: GAMEMD 0x459890
int BuildingBView::vf_183()
{
    return Type->unknown_152C;
}

// FUNCTION: GAMEMD 0x459900
// CAPPED at 4.2% (239 retail vs 229 compiled instructions; retail-only 6 `mov`, 4 `lea`). Retail keeps the
// particle-system type in ebp and the empty-coordinate X in edi and spills the arg at [esp+0x10]; cl puts the
// type in edi and the arg in ebx. Variants tried: a 4-iteration loop (71 instructions, not unrolled), four
// expanded blocks kept here, the argument re-read per block, swapped operand order of the position sum.
// The four offsets of the type are handled by four expanded copies of the same block in retail.
void BuildingBView::vf_282()
{
    BuildingBParticleSystemTypeView* systemType = Type->unknown_774;
    if (systemType) {
        int arg = Type->unknown_156C;
        {
            HBCoord offset = Type->unknown_coords_7CC[0];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
        {
            HBCoord offset = Type->unknown_coords_7CC[1];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
        {
            HBCoord offset = Type->unknown_coords_7CC[2];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
        {
            HBCoord offset = Type->unknown_coords_7CC[3];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x459C20
void BuildingBView::vf_219()
{
    if (unknown_218 && unknown_218->vf_11() == 0xB) {
        if (BuildingBCastAbstract(unknown_218)->unknown_EC == 5 && Type->unknown_5ED && Type->unknown_5EC && Type->unknown_57C != -1) {
            vf_213(Type->unknown_57C);
            return;
        }
    }
    Func_708E00();
}

// GLOBAL: GAMEMD 0x7E96A0 - CLSID of BuildingClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Building =
    { 0x0E272DC6, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// FUNCTION: GAMEMD 0x459E70
int BuildingBView::vf_12()
{
    return 0x720;
}

// FUNCTION: GAMEMD 0x459E80
HRESULT __stdcall BuildingBView::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_Building;
    return S_OK;
}

// FUNCTION: GAMEMD 0x459EC0
int BuildingBView::vf_11()
{
    return 6;
}

// FUNCTION: GAMEMD 0x459ED0
int BuildingBView::vf_36()
{
    return Type->unknown_60;
}

// FUNCTION: GAMEMD 0x459EE0
BuildingBTypeView* BuildingBView::vf_34()
{
    return Type;
}

// FUNCTION: GAMEMD 0x459EF0
// CAPPED at 41.2% (7 of 17 instructions; retail-only: `add ecx,-0x80`, `lea esi,[eax-0x80]`; cl-only: two
// `sub reg,0x80`). Retail adds the negative constant (an `add` of 0xFFFFFF80 and an `lea` with a -0x80
// displacement) where cl always canonicalises a constant add of a negative immediate to `sub`. Variants
// tried: direct field subtraction, a struct copy with -=, operator- / operator+ with a named offset
// coordinate, and `+ -0x80`.
HBCoord* BuildingBView::vf_43(HBCoord* out)
{
    HBCoord c = Location;
    c.X -= 0x80;
    c.Y -= 0x80;
    *out = c;
    return out;
}

// FUNCTION: GAMEMD 0x459F20
void* BuildingBView::vf_8(unsigned int flags)
{
    Func_43BCF0();
    if (flags & 1)
        operator delete(this);
    return this;
}
