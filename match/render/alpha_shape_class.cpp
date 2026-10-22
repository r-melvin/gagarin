// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The AlphaShapeClass block of retail .text (0x420720..0x421800): the unit's
// run-time initialisers, the constructors and destructor, the expiry sweep
// and the primary-table slots 5, 8, 10, 11, 12 and 13, in retail address
// order. AlphaShapeClass is declared in _layout/alpha_shape_class.h.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
//   /Ob2: the scalar deleting destructor 0x421730 expands the destructor.

#include <new.h>
#include "../_layout/alpha_shape_class.h"
#include "../_layout/object_class.h"
#include "../_layout/object_type_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../movement/locomotion_load_support.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x88A0C0
extern double DAT_0088A0C0;
// GLOBAL: GAMEMD 0x7E2B10
const double DAT_007E2B10 = 60.0;

// SYNTHETIC: GAMEMD 0x420720
// GLOBAL: GAMEMD 0x89A128
double DAT_0089A128 = DAT_0088A0C0 / DAT_007E2B10;
// SYNTHETIC: GAMEMD 0x420740
// GLOBAL: GAMEMD 0x88A110
double DAT_0088A110 = 1.0 / DAT_0089A128;
// SYNTHETIC: GAMEMD 0x4208C0
// GLOBAL: GAMEMD 0x89A118
TuningCoordInit DAT_0089A118(128, 128, 0);

// GLOBAL: GAMEMD 0xB0F720 -- the class-wide list of objects with a per-frame update.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F720;

// The append to a class-wide list, in the free-function shape of the inlined
// DynamicVectorClass::AddItem (as EMPulse_AddItem in combat/empulse_class.cpp).
template<class T>
static inline bool AlphaShape_AddItem(DynamicVectorClass<T>& v, T item)
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

// FUNCTION: GAMEMD 0x420960
//
// PARTIAL (76.0%, aligned 90.9%). Exact through both list appends; the
// residual is the expanded table build (AlphaShape_BuildTable): retail
// computes the product into EAX and moves it to ECX for the /127, and tests
// >255 once before the 0..255 clamp. Seven clamp/min/bound forms and both
// operand orders were tried; VC6 here folds the clamp to two compares.
AlphaShapeClass::AlphaShapeClass(ObjectClass* object, int x, int y)
    : unknown_24(object), unknown_38(0), unknown_3C(false)
{
    AlphaShapeImage* image = (AlphaShapeImage*)object->vf_34()->AlphaImage;
    unknown_38 = image;
    unknown_28 = AlphaShapeRect(x, y, image->unknown_02, image->unknown_04);
    AlphaShape_AddItem(Array, this);
    AlphaShape_AddItem(DAT_00B0F720, (AbstractClass*)this);
    AlphaShape_BuildTable();
}

// FUNCTION: GAMEMD 0x420AF0
// PARTIAL (71.4%, aligned 91.1%): the table-build residual of 0x420960.
AlphaShapeClass::AlphaShapeClass()
    : unknown_24(0), unknown_28(0, 0, 0, 0), unknown_38(0), unknown_3C(false)
{
    AlphaShape_AddItem(Array, this);
    AlphaShape_AddItem(DAT_00B0F720, (AbstractClass*)this);
    AlphaShape_BuildTable();
}

// FUNCTION: GAMEMD 0x420C50
AlphaShapeClass::AlphaShapeClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit)
{
}

// FUNCTION: GAMEMD 0x420C80
AlphaShapeClass::~AlphaShapeClass()
{
    Array.RemoveItem(this);
    DAT_00B0F720.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x420D80
int AlphaShapeClass::vf_11()
{
    return 0x3E;
}

// FUNCTION: GAMEMD 0x420D90
int AlphaShapeClass::vf_12()
{
    return sizeof(AlphaShapeClass);
}

// FUNCTION: GAMEMD 0x420DA0
void AlphaShapeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_28.X);
    crc->FUN_004A1D50(unknown_28.Y);
    crc->FUN_004A1D50(unknown_28.Width);
    crc->FUN_004A1D50(unknown_28.Height);
}

// FUNCTION: GAMEMD 0x420DE0
HRESULT __stdcall AlphaShapeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr >= 0) {
        new (this) AlphaShapeClass(AbstractNoInit());
        DAT_00B0C110.FUN_006CF240((void**)&unknown_24);
        unknown_38 = 0;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x420E70
void AlphaShapeClass::vf_10(void* target, bool removed)
{
    if (target == unknown_24) {
        unknown_3C = true;
    }
}

// FUNCTION: GAMEMD 0x420E90
// Delete every shape whose object has expired, after building the table.
// PARTIAL (27.1%, aligned 83.1%): the sweep loop is exact; the residual is
// the table build of 0x420960.
void __fastcall AlphaShapeClass::FUN_00420E90()
{
    AlphaShape_BuildTable();
    for (int i = Array.Count - 1; i >= 0; i--) {
        if (Array[i]->unknown_3C) {
            delete Array[i];
        }
    }
}


// FUNCTION: GAMEMD 0x421730
// The scalar deleting destructor the compiler emits for ~AlphaShapeClass (slot 8).