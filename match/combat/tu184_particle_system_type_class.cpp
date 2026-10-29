// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU184 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x643eb0-0x6449ef,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
//   Provenance note: an outside reference-cross-check (names only)
// No /GX: no retail body of this class has an exception frame.
//
// ParticleSystemTypeClass (cluster "system" of the particle module). Layout and tables are in
// particle_system_type_class.h / particle_common_views.h. The INI key names below are the strings the retail
// ReadINI body references (0x8370B0 ... 0x836F40). Addresses in this TU, ascending:
//   constructor 0x6440A0; ReadINI 0x6442D0; ComputeCRC 0x644700; GetClassID 0x6447A0;
//   Load 0x6447E0; Save 0x644830; Size 0x644920; WhatAmI 0x644930; vf_32 0x644940;
//   vf_35 0x644950; scalar deleting destructor 0x644960 (synthetic; the destructor body is
//   inlined into it).
//
// Cluster methods use the existing 0x644890 and 0x645820 function bodies as
// source hypotheses; row identity and relocations require the current raw oracle.
//
// Linear name lookups over a fixed table of string pointers (CRT case-insensitive
// compare at 0x7C8D20): the index of the first entry equal to the name, with each
// owner's own table and miss value. The tables are named by retail address; the
// entry count is the distance to the loop end in the body. Each address is
// verified separately.

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
#include "particles/particle_system_type_class.h"

// GLOBAL: GAMEMD 0x7E96D0 - CLSID of this class, copied by GetClassID.
extern "C" const CLSID CLSID_ParticleSystemType =
    { 0x703E044A, 0x0FB1, 0x11D2, { 0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// GLOBAL: GAMEMD 0x836EE0 - the five BehavesLike names (Smoke, Gas, Fire, Spark, Railgun).
extern const char* const DAT_00836EE0[5];

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0068
extern const double DAT_007F0068;
// GLOBAL: GAMEMD 0xAC5028
extern double DAT_00AC5028;

// SYNTHETIC: GAMEMD 0x00643EE0
// dynamic initializer for DAT_00AC5078

// GLOBAL: GAMEMD 0x00AC5078
double DAT_00AC5078 = DAT_00AC5028 / DAT_007F0068;

// SYNTHETIC: GAMEMD 0x00643F00
// dynamic initializer for DAT_00AC5060

// GLOBAL: GAMEMD 0x00AC5060
double DAT_00AC5060 = DAT_007E1718 / DAT_00AC5078;

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

// Binary-backed string references (retail bytes including the terminating NUL):
// STRING: GAMEMD 0x817474 "<none>"
// STRING: GAMEMD 0x817694 "none"

#include <string.h>
#include "particles/particle_system_type_class.h"
#include "particles/particle_type_class.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT case-insensitive string compare (cdecl, two pointers).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

extern const char* const DAT_00836EE0[5];

extern const char* const DAT_008370BC[5];

extern const char* const DAT_007F0248[12];

extern const char* const DAT_008449F8[3];

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644250
// Announces the expiring pointer and leaves the class-wide list; 0x644960 expands this body.
ParticleSystemTypeClass::~ParticleSystemTypeClass()
{
    ParticleAnnouncePointerExpired(this, true);
    DAT_00A83D68.RemoveItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6446E0
// Name of the system type at this index; "<none>" when the index is out of range.
const char* FUN_006446E0(unsigned int index)
{
    if (index < (unsigned int)DAT_00A83D68.Count)
        return ((ParticleSystemTypeClass**)DAT_00A83D68.Items)[index]->ID;
    return "<none>";
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6447A0
HRESULT __stdcall ParticleSystemTypeClass::GetClassID(CLSID* pClassID)
{
    if (!pClassID)
        return E_POINTER;
    *pClassID = CLSID_ParticleSystemType;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6447E0
HRESULT __stdcall ParticleSystemTypeClass::Load(IStream* pStm)
{
    if (ParticleTypeObjectView::Load(pStm) >= 0) {
        new (this) ParticleSystemTypeClass(ParticleNoInit());
    }
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644830
HRESULT __stdcall ParticleSystemTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    ParticleTypeObjectView::Save(pStm, fClearDirty);
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00644850
int FUN_00644850(const char* name)
{
    for (int i = 0; i < 5; ++i) {
        if (strcmpi(name, DAT_00836EE0[i]) == 0)
            return i;
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644890
ParticleSystemTypeClass* ParticleSystemTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;
    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < DAT_00A83D68.Count; i++) {
        if (_stricmp(((ParticleSystemTypeClass**)DAT_00A83D68.Items)[i]->ID, id) == 0)
            return ((ParticleSystemTypeClass**)DAT_00A83D68.Items)[i];
    }

    return new ParticleSystemTypeClass(id);
}

// Position of this exact object in the system-type array, -1 when absent.
static inline int IndexOfSystemType(ParticleSystemTypeClass* item)
{
    int count = DAT_00A83D68.Count;
    for (int k = 0; k < count; k++) {
        if (((ParticleSystemTypeClass**)DAT_00A83D68.Items)[k] == item)
            return k;
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644630
// Index of the system type with this name; unknown names are created first. Returns -1 for
// "<none>" and for an empty name.
int FUN_00644630(const char* name)
{
    if (_stricmp(name, "<none>") != 0 && strlen(name) != 0) {
        int i;
        for (i = 0; i < DAT_00A83D68.Count; i++) {
            if (_stricmp(name, ((ParticleSystemTypeClass**)DAT_00A83D68.Items)[i]->ID) == 0)
                return i;
        }
        return IndexOfSystemType(new ParticleSystemTypeClass(name));
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644920
int ParticleSystemTypeClass::Size()
{
    return sizeof(ParticleSystemTypeClass);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644930
int ParticleSystemTypeClass::WhatAmI()
{
    return 0x19;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644940
bool ParticleSystemTypeClass::vf_32(int a, int b)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644950
int ParticleSystemTypeClass::vf_35(int a)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x644960
// Scalar deleting destructor emitted from the inline ParticleSystemTypeClass destructor.
