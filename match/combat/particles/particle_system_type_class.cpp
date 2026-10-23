// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// No /GX: no retail body of this class has an exception frame.
//
// ParticleSystemTypeClass (cluster "system" of the particle module). Layout and tables are in
// particle_system_type_class.h / particle_common_views.h. The INI key names below are the strings the retail
// ReadINI body references (0x8370B0 ... 0x836F40). Addresses in this TU, ascending:
//   constructor 0x6440A0; ReadINI 0x6442D0; ComputeCRC 0x644700; GetClassID 0x6447A0;
//   Load 0x6447E0; Save 0x644830; Size 0x644920; WhatAmI 0x644930; vf_32 0x644940;
//   vf_35 0x644950; scalar deleting destructor 0x644960 (synthetic; the destructor body is
//   inlined into it).


// Binary-backed string references (retail bytes including the terminating NUL):
// STRING: GAMEMD 0x8184C8 "Spawns"
// STRING: GAMEMD 0x836F40 "SpawnSparkPercentage"
// STRING: GAMEMD 0x836F58 "OneFrameLight"
// STRING: GAMEMD 0x836F68 "LightSize"
// STRING: GAMEMD 0x836F74 "SparkSpawnFrames"
// STRING: GAMEMD 0x836F88 "LaserColor"
// STRING: GAMEMD 0x836F94 "Laser"
// STRING: GAMEMD 0x836F9C "VelocityPerturbationCoefficient"
// STRING: GAMEMD 0x836FBC "MovementPerturbationCoefficient"
// STRING: GAMEMD 0x836FDC "PositionPerturbationCoefficient"
// STRING: GAMEMD 0x836FFC "SpiralRadius"
// STRING: GAMEMD 0x83700C "SpiralDeltaPerCoord"
// STRING: GAMEMD 0x837020 "ParticlesPerCoord"
// STRING: GAMEMD 0x837034 "SpawnDirection"
// STRING: GAMEMD 0x837044 "BehavesLike"
// STRING: GAMEMD 0x837050 "Lifetime"
// STRING: GAMEMD 0x83705C "SpawnTranslucencyCutoff"
// STRING: GAMEMD 0x837074 "SpawnCutoff"
// STRING: GAMEMD 0x837080 "Slowdown"
// STRING: GAMEMD 0x83708C "SpawnRadius"
// STRING: GAMEMD 0x837098 "ParticleCap"
// STRING: GAMEMD 0x8370A4 "SpawnFrames"
// STRING: GAMEMD 0x8370B0 "HoldsWhat"
// STRING: GAMEMD 0x889F64 ""

#include <string.h>
#include "particle_system_type_class.h"

// GLOBAL: GAMEMD 0x7E96D0 - CLSID of this class, copied by GetClassID.
extern "C" const CLSID CLSID_ParticleSystemType =
    { 0x703E044A, 0x0FB1, 0x11D2, { 0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// GLOBAL: GAMEMD 0x836EE0 - the five BehavesLike names (Smoke, Gas, Fire, Spark, Railgun).
extern const char* const DAT_00836EE0[5];

// FUNCTION: GAMEMD 0x645430 (decl; reloc) - looks a ParticleType name up (ECX = name).
int FUN_00645430(const char* name);

// Index of the BehavesLike name in the table, -1 when absent.
static inline int Inline_006442D0(const char* name)
{
    for (int i = 0; i < 5; ++i) {
        if (_stricmp(name, DAT_00836EE0[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x6440A0
ParticleSystemTypeClass::ParticleSystemTypeClass(const char* id)
    : ParticleTypeObjectView(id), HoldsWhat(-1), Spawns(false), SpawnFrames(1),
      Slowdown(0), ParticleCap(50), SpawnRadius(0), SpawnCutoff(0),
      SpawnTranslucencyCutoff(0), BehavesLike(-1), Lifetime(-1), SpawnDirection(0, 0, 0),
      ParticlesPerCoord(0.1),
      SpiralDeltaPerCoord(0.025), SpiralRadius(25.0), PositionPerturbationCoefficient(0),
      MovementPerturbationCoefficient(0), VelocityPerturbationCoefficient(0),
      SpawnSparkPercentage(0), SparkSpawnFrames(0), LightSize(0), LaserColor(0, 0, 0),
      Laser(false), OneFrameLight(false)
{
    ParticleRttiBase::Create_ID();
    DAT_00A83D68.AddItem(this);
    unknown_234 = true;
}

// FUNCTION: GAMEMD 0x6442D0
bool ParticleSystemTypeClass::ReadINI(ParticleIniView* ini)
{
    ini->ClearCache();
    if (ParticleTypeObjectView::ReadINI(ini)) {
        char buffer[0x40];
        ini->ReadString(ID, "HoldsWhat", "", buffer, sizeof(buffer));
        HoldsWhat = FUN_00645430(buffer);
        Spawns = ini->ReadBool(ID, "Spawns", Spawns);
        SpawnFrames = ini->ReadInt(ID, "SpawnFrames", SpawnFrames);
        ParticleCap = ini->ReadInt(ID, "ParticleCap", ParticleCap);
        SpawnRadius = ini->ReadInt(ID, "SpawnRadius", SpawnRadius);
        Slowdown = (float)ini->ReadDouble(ID, "Slowdown", Slowdown);
        SpawnCutoff = (float)ini->ReadDouble(ID, "SpawnCutoff", SpawnCutoff);
        SpawnTranslucencyCutoff =
            (float)ini->ReadDouble(ID, "SpawnTranslucencyCutoff", SpawnTranslucencyCutoff);
        Lifetime = ini->ReadInt(ID, "Lifetime", Lifetime);
        ini->ReadString(ID, "BehavesLike", "", buffer, sizeof(buffer));
        BehavesLike = Inline_006442D0(buffer);
        SpawnDirection = ini->ReadPoint3D(ID, "SpawnDirection", SpawnDirection);
        ParticlesPerCoord = ini->ReadDouble(ID, "ParticlesPerCoord", ParticlesPerCoord);
        SpiralDeltaPerCoord = ini->ReadDouble(ID, "SpiralDeltaPerCoord", SpiralDeltaPerCoord);
        SpiralRadius = ini->ReadDouble(ID, "SpiralRadius", SpiralRadius);
        PositionPerturbationCoefficient = ini->ReadDouble(
            ID, "PositionPerturbationCoefficient", PositionPerturbationCoefficient);
        MovementPerturbationCoefficient = ini->ReadDouble(
            ID, "MovementPerturbationCoefficient", MovementPerturbationCoefficient);
        VelocityPerturbationCoefficient = ini->ReadDouble(
            ID, "VelocityPerturbationCoefficient", VelocityPerturbationCoefficient);
        Laser = ini->ReadBool(ID, "Laser", Laser);
        LaserColor = ini->ReadColor(ID, "LaserColor", LaserColor);
        SparkSpawnFrames = ini->ReadInt(ID, "SparkSpawnFrames", SparkSpawnFrames);
        LightSize = ini->ReadInt(ID, "LightSize", LightSize);
        OneFrameLight = ini->ReadBool(ID, "OneFrameLight", OneFrameLight);
        SpawnSparkPercentage =
            ini->ReadDouble(ID, "SpawnSparkPercentage", SpawnSparkPercentage);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x644700
void ParticleSystemTypeClass::ComputeCRC(ParticleCrcView& crc)
{
    ParticleTypeObjectView::ComputeCRC(crc);
    crc.AddInt(HoldsWhat);
    crc.AddBool(Spawns);
    crc.AddInt(SpawnFrames);
    crc.AddFloat(Slowdown);
    crc.AddInt(ParticleCap);
    crc.AddInt(SpawnRadius);
    crc.AddFloat(SpawnCutoff);
    crc.AddFloat(SpawnTranslucencyCutoff);
    crc.AddInt(BehavesLike);
    crc.AddInt(Lifetime);
}

// FUNCTION: GAMEMD 0x6447A0
HRESULT __stdcall ParticleSystemTypeClass::GetClassID(CLSID* pClassID)
{
    if (!pClassID)
        return E_POINTER;
    *pClassID = CLSID_ParticleSystemType;
    return S_OK;
}

// FUNCTION: GAMEMD 0x6447E0
HRESULT __stdcall ParticleSystemTypeClass::Load(IStream* pStm)
{
    if (ParticleTypeObjectView::Load(pStm) >= 0) {
        new (this) ParticleSystemTypeClass(ParticleNoInit());
    }
    return S_OK;
}

// FUNCTION: GAMEMD 0x644830
HRESULT __stdcall ParticleSystemTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    ParticleTypeObjectView::Save(pStm, fClearDirty);
    return S_OK;
}

// FUNCTION: GAMEMD 0x644920
int ParticleSystemTypeClass::Size()
{
    return sizeof(ParticleSystemTypeClass);
}

// FUNCTION: GAMEMD 0x644930
int ParticleSystemTypeClass::WhatAmI()
{
    return 0x19;
}

// FUNCTION: GAMEMD 0x644940
bool ParticleSystemTypeClass::vf_32(int a, int b)
{
    return false;
}

// FUNCTION: GAMEMD 0x644950
int ParticleSystemTypeClass::vf_35(int a)
{
    return 0;
}

// SYNTHETIC: GAMEMD 0x644960
// Scalar deleting destructor emitted from the inline ParticleSystemTypeClass destructor.
