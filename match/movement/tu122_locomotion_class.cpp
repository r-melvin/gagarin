// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU122 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x55a4d0-0x55ad4f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
//   Provenance note: own-binary-via-Ghidra; behavioral names remain hypotheses where noted.
// No /GX: none of these bodies unwinds, and the deleting destructor needs no
// handler; this candidate was compiled with and without /GX.
//
// LocomotionClass (foundation of the locomotion module): the shared COM
// plumbing, the base ILocomotion defaults and the compiler-generated entries
// that every concrete locomotor reaches through its tables. Layout, slot order
// and evidence are in loco_base.h / loco_interfaces.h and the adjacent candidate report.
//
// This candidate defines only the base method bodies listed in its row file.
// Constructor/destructor expansion, vtables and thunks remain in their shared
// owners. Load has a qualified base body for derived stream loaders; Save is
// consolidated below from its prior standalone source.
//
//   Class and slot identities follow the native tables recorded in the shared headers.

#include "loco_base.h"
#include "locomotion_load_support.h"
#include "loco_foot.h"
#include "locomotion_rotation_step.h"

// Win32 imports bound by address: `CALL [0x7E11C8]` / `CALL [0x7E11CC]`.
// InterlockedIncrement / InterlockedDecrement come from <windows.h> (objidl.h).

// GLOBAL: GAMEMD 0x7ED358
extern "C" const IID IID_ILocomotion =
    { 0x070F3290, 0x9841, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// GLOBAL: GAMEMD 0x7E9B10
extern "C" const IID IID_IPiggyback =
    { 0x92FEA800, 0xA184, 0x11D1, { 0xB7, 0x0A, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

#include "locomotion_class_save_methods.h"

// FUNCTION: GAMEMD 0x55A6C0
LocomotionClass::LocomotionClass()
    : Owner(0), LinkedTo(0), Powered(true), Dirty(true), RefCount(0)
{
}

// FUNCTION: GAMEMD 0x55A6F0
// Destructor body: reseats the base vptrs and drops the linked object.
LocomotionClass::~LocomotionClass()
{
    LinkedTo = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A710
// migrated from match/movement/locomotion_class_iloco_methods.cpp; integrator retires the old row
HRESULT __stdcall LocomotionClass::LinkToObject(FootClass* object)
{
    LinkedTo = object;
    Owner = object;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A730
// migrated from match/movement/locomotion_class_draw_matrix_methods.cpp; integrator retires the old row
// Identity rotated about Z by the linked object's current facing, reduced to 32
// steps and re-based so that facing 8 is zero. When a voxel index key is given
// (and is not the "none" marker) the 32-step facing is folded into its low five
// bits.
Matrix3D __stdcall LocomotionClass::DrawMatrix(unsigned int* key)
{
    Matrix3D m;
    m.MakeIdentity();

    m.RotateZ((float)(((int)((((reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                      * gg_locomotion_facing_step));

    if (key != 0 && *key != 0xFFFFFFFF) {
        *key <<= 5;
        *key |= (((reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F;
    }

    return m;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A7D0
// migrated from match/movement/locomotion_class_shadow_matrix_methods.cpp; integrator retires the old row
Matrix3D __stdcall LocomotionClass::ShadowMatrix(unsigned int* key)
{
    LocoCoord coord = reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->Location;
    int slope = DAT_0087F7E8.GetCellAt(coord)->SlopeIndex;
    Matrix3D m = FUN_007559B0(slope);

    m.RotateZ((float)(((int)((((reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                      * gg_locomotion_facing_step));

    if (key != 0 && *key != 0xFFFFFFFF) {
        *key = ((*key << 6) + slope) << 5;
        *key |= (((reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F;
    }

    return m;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A8C0
LocoPoint2D __stdcall LocomotionClass::ShadowPoint()
{
    return LocoPoint2D(0, FUN_006D20E0(reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->Vtbl->At_1C8(LinkedTo)));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A8F0
bool __stdcall LocomotionClass::PowerOn()
{
    Powered = true;
    return IsPowered();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A910
bool __stdcall LocomotionClass::PowerOff()
{
    Powered = false;
    return IsPowered();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A930
// migrated from match/movement/locomotion_class_iloco_methods.cpp; integrator retires the old row
bool __stdcall LocomotionClass::IsPowered()
{
    return Powered;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A940
// migrated from match/movement/locomotion_class_iloco_methods.cpp; integrator retires the old row
bool __stdcall LocomotionClass::IsIonSensitive()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A950
// migrated from match/movement/locomotion_class_methods.cpp; integrator retires the old row
ULONG __stdcall LocomotionClass::AddRef()
{
    ++DAT_00ABCD3C;
    return InterlockedIncrement(&RefCount);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A970
// migrated from match/movement/locomotion_class_methods.cpp; integrator retires the old row
ULONG __stdcall LocomotionClass::Release()
{
    --DAT_00ABCD3C;
    LONG count = InterlockedDecrement(&RefCount);
    if (count == 0)
        delete this;
    return count;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A9B0
// Native class implementation replaces the former address-local free-function view.
// All four interface ids are tested one after another (a later match overwrites
// an earlier one), then the result is checked once and AddRef'd through the
// primary vptr. IID_IUnknown resolves to the ILocomotion side.
HRESULT __stdcall LocomotionClass::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == 0)
        return E_POINTER;

    *ppv = 0;

    if (riid == IID_IUnknown)
        *ppv = static_cast<ILocomotion*>(this);
    if (riid == IID_IPersistStream)
        *ppv = static_cast<IPersistStream*>(this);
    if (riid == IID_ILocomotion)
        *ppv = static_cast<ILocomotion*>(this);
    if (riid == IID_IPersist)
        *ppv = static_cast<IPersistStream*>(this);

    if (*ppv == 0)
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AA60  (__stdcall)
//
// PARTIAL (67.5%): the instruction multiset agrees, but register assignment
// and scheduling differ. Retail holds pStm in ESI and this in EDI; this build
// swaps those registers. The shared done epilogue keeps the early null exit
// and common cleanup shape. Earlier byte-exact/92.5% comments were not
// reproduced by the second-look verification and have been removed.
HRESULT __stdcall SaveView_0055AA60::Save(Gg_IStream* pStm, LONG fClearDirty)
{
    HRESULT hr;
    void* self;
    if (pStm == 0)
    {
        hr = (HRESULT)0x80004003;          // E_POINTER
        goto done;
    }

    // Serialise the raw `this` pointer (4 bytes) as the load swizzle key.
    self = this;
    hr = pStm->Write(&self, 4, 0);
    if (hr >= 0)
    {
        // Serialise the object body: Size() bytes starting at `this`.
        hr = pStm->Write(this, this->Size(), 0);
        if (hr >= 0 && fClearDirty)
            *((char*)this + 0x11) = 0;     // clear dirty flag
    }
done:
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AAC0
HRESULT __stdcall LocomotionClass::Load(IStream* pStm)
{
    if (pStm == 0) {
        return 0x80004003;
    }

    int id;
    HRESULT hr = pStm->Read(&id, 4, 0);
    if (hr < 0) {
        return hr;
    }

    DAT_00B0C110.SwizzleManagerClass::vf_6(id, this);

    LONG keep = RefCount;
    hr = pStm->Read(this, (unsigned long)Size(), 0);
    RefCount = keep;

    DAT_00B0C110.SwizzleManagerClass::vf_4(&LinkedTo);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);

    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AB40
// migrated from match/movement/locomotion_class_methods.cpp; integrator retires the old row
HRESULT __stdcall LocomotionClass::GetSizeMax(ULARGE_INTEGER* pcbSize)
{
    if (pcbSize == 0)
        return E_POINTER;

    pcbSize->QuadPart = (unsigned long)(Size() + 4);
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AB70
bool __stdcall LocomotionClass::Push(unsigned long)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AB80
bool __stdcall LocomotionClass::Shove(unsigned long)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AB90
void __stdcall LocomotionClass::TiltPitchAI()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ABA0
// migrated from match/movement/locomotion_class_iloco_methods.cpp; integrator retires the old row
int __stdcall LocomotionClass::ZAdjust()
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ABB0
// migrated from match/movement/locomotion_class_iloco_methods.cpp; integrator retires the old row
int __stdcall LocomotionClass::ZGradient()
{
    return 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ABC0
int __stdcall LocomotionClass::VisualCharacter(int)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ABD0
LocoPoint2D __stdcall LocomotionClass::DrawPoint()
{
    return LocoPoint2D(0, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ABE0
bool __stdcall LocomotionClass::IsToHaveShadow()
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ABF0
int __stdcall LocomotionClass::CanEnterCell(int)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC00
void __stdcall LocomotionClass::ForceImmediateDestination(LocoCoord)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC10
void __stdcall LocomotionClass::ForceTrack(int, LocoCoord)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC20
void __stdcall LocomotionClass::Unlimbo()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC30
void __stdcall LocomotionClass::DoTurn(unsigned long)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC40
void __stdcall LocomotionClass::StopMoving()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC50
void __stdcall LocomotionClass::MoveTo(LocoCoord)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC60
bool __stdcall LocomotionClass::Process()
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AC70
LocoCoord __stdcall LocomotionClass::Destination()
{
    LocoCoord coord = DAT_00ABCC78;
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ACA0
LocoCoord __stdcall LocomotionClass::HeadToCoord()
{
    LocoCoord coord = reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->Location;
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ACD0
bool __stdcall LocomotionClass::IsMoving()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ACE0
void __stdcall LocomotionClass::ForceNewSlope(int)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55ACF0
int __stdcall LocomotionClass::DrawingCode()
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AD00
// migrated from match/movement/locomotion_class_iloco_methods.cpp; integrator retires the old row
int __stdcall LocomotionClass::CanFire()
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55AD10
int __stdcall LocomotionClass::ApparentSpeed()
{
    return reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->Vtbl->At_538(LinkedTo);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABCC78
LocoCoord DAT_00ABCC78;
// END defined globals
