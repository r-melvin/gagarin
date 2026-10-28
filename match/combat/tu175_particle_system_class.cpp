// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name | YRpp-cross-check
//   Original translation unit TU175 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x62da40-0x63099f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
//   Provenance note: an outside reference-cross-check (names only)
// No /GX: no retail body of this class has an exception frame.
//
// ParticleSystemClass (cluster "system" of the particle module). Layout and tables are in
// system_class.h / particle_common_views.h. Addresses in this TU, ascending:
//   constructor 0x62DF20; vf_69 0x62E280; Update 0x62FD60; IsFinished 0x62FE60;
//   InWhichLayer 0x62FE80; PointerExpired 0x62FE90; Load 0x62FF20; Save 0x630090;
//   ComputeCRC 0x630100; GetClassID 0x6301A0; MarkFinished 0x6301E0; Size 0x630200;
//   WhatAmI 0x630210; GetType 0x630220; scalar deleting destructor 0x630230 (synthetic).
//
// migrated from match/core/deleting_dtor_sweep.cpp; integrator retires the old row (0x630230)
//
//   cross-checked against an outside reference.
//
//   The call at 0x62B5E0 targets ParticleClass::ParticleClass, whose reconstruction remains capped elsewhere.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include "particles/system_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "particles/particle_system_type_class.h"
#include "particles/particle_class.h"

// GLOBAL: GAMEMD 0x7E96C0 - CLSID of this class, copied by GetClassID.
extern "C" const CLSID CLSID_ParticleSystem =
    { 0x0E272DC8, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// GLOBAL: GAMEMD 0xAC4A58 - the empty coordinate (three dwords).
extern ParticleCoord DAT_00AC4A58;

// GLOBAL: GAMEMD 0xA80208 - the class-wide array of particle systems.
extern ParticleInlineDynVector<ParticleSystemClass*> DAT_00A80208;
// GLOBAL: GAMEMD 0xB0F720 - a second class-wide array the constructor appends to (element
// type unconfirmed).
extern ParticleInlineDynVector<ParticleSystemClass*> DAT_00B0F720;
// GLOBAL: GAMEMD 0xB0F698 - canonical storage from abstract_registry.h, viewed as this vector here.
#define ParticleFinishedSystemArray (*((ParticleInlineDynVector<ParticleSystemClass*>*)(void*)&DAT_00B0F698))

// The temporary light vf_69 builds, runs and deletes (0x18 bytes).
class PSysLightView
{
public:
    PSysLightView(ParticleCoord where, int intensity);     // 0x5FF250 (read-only)
    ~PSysLightView();                                  // 0x5FF2D0 (read-only)
    void __fastcall Activate();                        // 0x5FF850 (read-only)

    unsigned char unknown_00[0xC];
    int           unknown_0C;
    unsigned char unknown_10[0x8];
};
GG_STATIC_ASSERT(offsetof(PSysLightView, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(PSysLightView) == 0x18);

// GLOBAL: GAMEMD 0xAC4A8C - height added to the coordinate when the owner is over a flagged cell.
extern int DAT_00AC4A8C;

#include "particle_system_class.h"
#include "particles/particle_class.h"
#include "particles/particle_type_class.h"

// A static all-zero ParticleCoord at GAMEMD 0x00AC4A58, passed as the second
// coordinate by the (type, coord) overload (push 0xAC4A58). Reloc-normalised.
extern ParticleCoord DAT_00AC4A58;

#include "../core/member_setter_family_methods.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EFB58
extern const double DAT_007EFB58;
// GLOBAL: GAMEMD 0xAC4A40
extern double DAT_00AC4A40;

// SYNTHETIC: GAMEMD 0x62DA70
// GLOBAL: GAMEMD 0xAC4A90
double DAT_00AC4A90 = DAT_00AC4A40 / DAT_007EFB58;

// SYNTHETIC: GAMEMD 0x62DA90
// GLOBAL: GAMEMD 0xAC4A78
double DAT_00AC4A78 = DAT_007E1718 / DAT_00AC4A90;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62DC50
ParticleSystemClass::ParticleSystemClass(ParticleSystemTypeClass* type, const ParticleCoord& coord,
                                         ParticleObjectView* owner,
                                         ParticleObjectView* target,
                                         const ParticleCoord& ownerCoord, int unknownFC)
    : Type(type), unknown_B0(0, 0, 0), Particles(), unknown_D4(DAT_00AC4A58), unknown_E0(0),
      unknown_E4(0), unknown_E8((float)Type->SpawnFrames), FrameCountdown(Type->Lifetime),
      unknown_F0(Type->SparkSpawnFrames), unknown_F4(0x1D), unknown_F8(false),
      unknown_F9(false), unknown_FC(0)
{
    ParticleRttiBase::Create_ID();
    DAT_00A80208.AddItem(this);
    Particles.Clear();
    unknown_FC = unknownFC;
    if (owner) {
        unknown_D4 = owner->GetCoords();
        if (ParticleMap.GetCellAt(owner->GetCoords())->Flags & 0x100) {
            if (owner->WhatAmI() == 0xB) {
                unknown_D4.Z += DAT_00AC4A8C;
            }
        }
    } else {
        unknown_D4 = ownerCoord;
    }
    ParticleCoord where = coord;
    if (target) {
        unknown_E0 = target;
        ParticleHouseView* house = target->GetOwnerHouse();
        if (house) {
            unknown_E4 = (ParticleObjectView*)house->unknown_2B4;
        }
    } else {
        unknown_E0 = 0;
        unknown_E4 = owner;
    }
    ParticleObjectView::Unlimbo(&where, 0);
    if (unknown_E0) {
        unknown_B0 = Location - unknown_E0->GetCoords();
    }
    DAT_00B0F720.AddItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62DF20
ParticleSystemClass::ParticleSystemClass()
    : Type(0), Particles(), unknown_D4(DAT_00AC4A58), unknown_E0(0), unknown_E4(0),
      unknown_E8(0), FrameCountdown(0), unknown_F0(0), unknown_F4(0), unknown_F8(false),
      unknown_F9(false)
{
    Particles.Clear();
    DAT_00A80208.AddItem(this);
    DAT_00B0F720.AddItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62E280
void ParticleSystemClass::vf_69(void* where, ParticleRect* clip)
{
    if (Type->OneFrameLight && Type->LightSize > 0 && Particles.Count > 0) {
        float ratio = (float)Particles.Count / Type->ParticleCap;
        int intensity = (int)(((0.4 > (1.0f < ratio ? 1.0f : ratio)) ? 0.4
                                                                    : (1.0f < ratio ? 1.0f : ratio))
                              * Type->LightSize);
        PSysLightView* light = new PSysLightView(Location, intensity);
        light->unknown_0C = unknown_F4;
        light->Activate();
        delete light;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62E380  (__thiscall)
// Spawn a particle of the system's own configured type between two coordinates.
ParticleClass* ParticleSystemClass::SpawnParticle(const ParticleCoord& coords1,
                                                  const ParticleCoord& coords2)
{
    ParticleClass* particle;

    if (this->Type->HoldsWhat == -1) {
        goto fail;
    }

    particle = new ParticleClass(
        ParticleTypeArray.Items[this->Type->HoldsWhat],
        &coords1, &coords2, this);

    if (particle) {
        this->Particles.AddItem(particle);
        return particle;
    }

fail:
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62E430  (__thiscall)
// Spawn a particle of an explicitly supplied type at the given coordinate.
ParticleClass* ParticleSystemClass::SpawnParticle(ParticleTypeClass* pType,
                                                  const ParticleCoord& coords)
{
    ParticleClass* particle = new ParticleClass(
        pType, &coords, &DAT_00AC4A58, this);

    if (particle) {
        this->Particles.AddItem(particle);
        return particle;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62E5D0
// Marks the particle at this index finished and removes it from the system's list.
bool ParticleSystemClass::FUN_0062E5D0(int index)
{
    if (index < Particles.Count) {
        Particles.Items[index]->MarkFinished();
        Particles.RemoveItem(Particles.Items[index]);
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62E650
// Finishes and removes every particle of the system, last first.
void ParticleSystemClass::FUN_0062E650()
{
    for (int i = Particles.Count - 1; i >= 0; i--) {
        if (i < Particles.Count) {
            Particles.Items[i]->MarkFinished();
            Particles.RemoveItem(Particles.Items[i]);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62FD60
void ParticleSystemClass::Update()
{
    switch (Type->BehavesLike) {
    case 0: UpdateBehavior0(); break;
    case 1: UpdateBehavior1(); break;
    case 2: UpdateBehavior2(); break;
    case 3: UpdateBehavior3(); break;
    case 4: UpdateBehavior4(); break;
    }
    if (--FrameCountdown == 0) {
        MarkFinished();
    }
    if (IsAlive && unknown_F8 && Particles.Count == 0) {
        vf_53();
        IsAlive = false;
        ParticleFinishedSystemArray.AddItem(this);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62FE60
bool ParticleSystemClass::IsFinished()
{
    return unknown_F8 && Particles.Count == 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62FE80
int ParticleSystemClass::InWhichLayer()
{
    return 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62FE90
void ParticleSystemClass::PointerExpired(void* target, bool removed)
{
    ParticleObjectView::PointerExpired(target, removed);
    Particles.RemoveItem((ParticleClass*)target);
    if (target == Type) {
        Type = 0;
    }
    if (target == unknown_E4) {
        unknown_E4 = 0;
    }
    if (target == unknown_E0) {
        unknown_F8 = true;
        unknown_E0 = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62FF20
HRESULT __stdcall ParticleSystemClass::Load(IStream* pStm)
{
    HRESULT hr = ParticleObjectView::Load(pStm);
    if (hr >= 0) {
        new (this) ParticleSystemClass(ParticleNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_E4);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_E0);
        int count = 0;
        hr = pStm->Read(&count, 4, 0);
        if (hr >= 0) {
            while (count--) {
                ParticleClass* particle = 0;
                ULONG bytesRead;
                hr = pStm->Read(&particle, 4, &bytesRead);
                if (hr < 0) {
                    return hr;
                }
                Particles.AddItem(particle);
            }
            for (int i = 0; i < Particles.Count; ++i) {
                DAT_00B0C110.SwizzleManagerClass::vf_4(&Particles.Items[i]);
            }
            hr = 0;
        }
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x630090
HRESULT __stdcall ParticleSystemClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ParticleObjectView::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = Particles.Count;
        hr = pStm->Write(&count, 4, 0);
        if (hr >= 0) {
            for (int i = 0; i < count; ++i) {
                hr = pStm->Write(&Particles.Items[i], 4, 0);
                if (hr < 0) {
                    break;
                }
            }
        }
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x630100
void ParticleSystemClass::ComputeCRC(ParticleCrcView& crc)
{
    ParticleObjectView::ComputeCRC(crc);
    for (int i = 0; i < Particles.Count; ++i) {
        crc.AddInt(Particles.Items[i]->Fetch_ID());
    }
    if (unknown_E0) {
        crc.AddInt(unknown_E0->Fetch_ID());
    }
    if (unknown_E4) {
        crc.AddInt(unknown_E4->Fetch_ID());
    }
    crc.AddFloat(unknown_E8);
    crc.AddInt(FrameCountdown);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6301A0
HRESULT __stdcall ParticleSystemClass::GetClassID(CLSID* pClassID)
{
    if (!pClassID)
        return E_POINTER;
    *pClassID = CLSID_ParticleSystem;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6301E0
void ParticleSystemClass::MarkFinished()
{
    unknown_F8 = true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006301F0
//
// Store the argument into the member at +0xEC.
void Setter_00487C70::FUN_006301F0(int value)
{
    *(int*)(Bytes + 0xEC) = value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x630200
int ParticleSystemClass::Size()
{
    return sizeof(ParticleSystemClass);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x630210
int ParticleSystemClass::WhatAmI()
{
    return 0x18;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x630220
ParticleTypeObjectView* ParticleSystemClass::GetType()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x630230 (compiler-generated scalar deleting destructor; ordinary dtor is an external declaration view at 0x62E070).
