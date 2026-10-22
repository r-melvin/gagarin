// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//
// ParticleTypeClass entries (layout and evidence: particle_type_class.h).


// Binary-backed string references (retail bytes including the terminating NUL):
// STRING: GAMEMD 0x817474 "<none>"
// STRING: GAMEMD 0x8183B4 "Warhead"
// STRING: GAMEMD 0x818524 "Translucency"
// STRING: GAMEMD 0x81859C "Damage"
// STRING: GAMEMD 0x818610 "Normalized"
// STRING: GAMEMD 0x81D990 "Gas"
// STRING: GAMEMD 0x836EF4 "Railgun"
// STRING: GAMEMD 0x836EFC "Spark"
// STRING: GAMEMD 0x836F04 "Fire"
// STRING: GAMEMD 0x836F0C "Smoke"
// STRING: GAMEMD 0x837044 "BehavesLike"
// STRING: GAMEMD 0x8370F0 "NextParticle"
// STRING: GAMEMD 0x837100 "FinalDamageState"
// STRING: GAMEMD 0x837114 "StartColor2"
// STRING: GAMEMD 0x837120 "StartColor1"
// STRING: GAMEMD 0x83712C "NextParticleOffset"
// STRING: GAMEMD 0x837140 "ZVelocityRange"
// STRING: GAMEMD 0x837150 "MinZVelocity"
// STRING: GAMEMD 0x837160 "YVelocity"
// STRING: GAMEMD 0x83716C "XVelocity"
// STRING: GAMEMD 0x837178 "ColorSpeed"
// STRING: GAMEMD 0x837184 "Translucent25State"
// STRING: GAMEMD 0x837198 "Translucent50State"
// STRING: GAMEMD 0x8371AC "StateAIAdvance"
// STRING: GAMEMD 0x8371BC "StartStateAI"
// STRING: GAMEMD 0x8371CC "EndStateAI"
// STRING: GAMEMD 0x8371D8 "DeleteOnStateLimit"
// STRING: GAMEMD 0x8371EC "Radius"
// STRING: GAMEMD 0x8371F4 "Deacc"
// STRING: GAMEMD 0x8371FC "Velocity"
// STRING: GAMEMD 0x837208 "WindEffect"
// STRING: GAMEMD 0x837214 "NumLoopFrames"
// STRING: GAMEMD 0x837224 "StartFrame"
// STRING: GAMEMD 0x837230 "MaxEC"
// STRING: GAMEMD 0x837238 "MaxDC"
// STRING: GAMEMD 0x837240 "ColorList"

#include <new.h>
#include <string.h>
#include "particle_type_class.h"

extern const char* const ParticleBehavesLikeNames[5];

// GLOBAL: GAMEMD 0x7E9710 - CLSID of ParticleTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_ParticleType =
    { 0x703E044B, 0x0FB1, 0x11D2, { 0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// FUNCTION: GAMEMD 0x644BE0
// CAPPED: the frozen candidate remains partial at the recorded 96.6% instruction score.
ParticleTypeClass::ParticleTypeClass(const char* id)
    : ParticleTypeObjectView(id), NextParticleOffset(0, 0, 0), XVelocity(1), YVelocity(1), MinZVelocity(0),
      ZVelocityRange(1), ColorSpeed(0), StartColor1(0, 0, 0), StartColor2(0, 0, 0), MaxDC(0), MaxEC(1),
      Warhead(0), Damage(0), StartFrame(0), NumLoopFrames(1), Translucency(0), WindEffect(0), Velocity(0),
      Deacc(0), Radius(0), DeleteOnStateLimit(false), EndStateAI(0), StartStateAI(0), StateAIAdvance(4),
      FinalDamageState(0), Translucent25State(0xFF), Translucent50State(0xFF), Normalized(false),
      NextParticle(-1), BehavesLike(-1)
{
    ParticleTypeArray.AddItem(this);
    ParticleAbstractTypeArray.AddItem(this);
    unknown_234 = 0;
}

// FUNCTION: GAMEMD 0x644F50
// CAPPED: the frozen candidate remains partial at the recorded 22.4% positional instruction score.
// Its current source is preserved; this annotation does not assert that all other instructions align.
bool ParticleTypeClass::ReadINI(ParticleIniView* ini)
{
    ini->ClearCache();
    if (ParticleTypeObjectView::ReadINI(ini)) {
        ColorList = ini->ReadColors(ParticleNameOf(ID), "ColorList", ParticleColorList(0, 0));
        MaxDC = ini->ReadInt(ID, "MaxDC", MaxDC);
        MaxEC = ini->ReadInt(ID, "MaxEC", MaxEC);
        Damage = ini->ReadInt(ID, "Damage", Damage);
        char warheadName[0x80];
        ParticleWarheadView* warhead = Warhead;
        Warhead = ini->ReadString(ID, "Warhead", ParticleEmptyText, warheadName, 0x80)
                      ? ParticleFindWarhead(warheadName) : warhead;
        StartFrame = ini->ReadInt(ID, "StartFrame", StartFrame);
        NumLoopFrames = ini->ReadInt(ID, "NumLoopFrames", NumLoopFrames);
        Translucency = ini->ReadInt(ID, "Translucency", Translucency);
        WindEffect = ini->ReadInt(ID, "WindEffect", WindEffect);
        Velocity = (float)ini->ReadDouble(ID, "Velocity", Velocity);
        Deacc = (float)ini->ReadDouble(ID, "Deacc", Deacc);
        Radius = ini->ReadInt(ID, "Radius", Radius);
        DeleteOnStateLimit = ini->ReadBool(ID, "DeleteOnStateLimit", DeleteOnStateLimit);
        EndStateAI = (signed char)ini->ReadInt(ID, "EndStateAI", EndStateAI);
        StartStateAI = (signed char)ini->ReadInt(ID, "StartStateAI", StartStateAI);
        StateAIAdvance = (signed char)ini->ReadInt(ID, "StateAIAdvance", StateAIAdvance);
        Translucent50State = (unsigned char)ini->ReadInt(ID, "Translucent50State", Translucent50State);
        Translucent25State = (unsigned char)ini->ReadInt(ID, "Translucent25State", Translucent25State);
        Normalized = ini->ReadBool(ID, "Normalized", Normalized);
        ColorSpeed = ini->ReadDouble(ID, "ColorSpeed", ColorSpeed);
        XVelocity = ini->ReadInt(ID, "XVelocity", XVelocity);
        YVelocity = ini->ReadInt(ID, "YVelocity", YVelocity);
        MinZVelocity = ini->ReadInt(ID, "MinZVelocity", MinZVelocity);
        ZVelocityRange = ini->ReadInt(ID, "ZVelocityRange", ZVelocityRange);
        NextParticleOffset = ini->ReadCoord(ID, "NextParticleOffset", NextParticleOffset);
        StartColor1 = ini->ReadColor(ID, "StartColor1", StartColor1);
        StartColor2 = ini->ReadColor(ID, "StartColor2", StartColor2);
        FinalDamageState = (signed char)ini->ReadInt(ID, "FinalDamageState", EndStateAI);

        char name[0x20];
        if (ini->ReadString(ID, "NextParticle", 0, name, 0x20)) {
            int index = -1;
            if (stricmp(name, "<none>") != 0) {
                int i;
                for (i = 0; i < ParticleTypeArray.Count; i++) {
                    if (stricmp(name, ParticleTypeArray.Items[i]->ID) == 0)
                        goto found;
                }
                {
                    ParticleTypeClass* created = new ParticleTypeClass(name);
                    i = ParticleTypeArray.FindIndex(created);
                }
            found:
                index = i;
            }
            NextParticle = index;
        }

        name[0] = 0;
        ini->ReadString(ID, "BehavesLike", 0, name, 0x20);
        int behaves;
        for (behaves = 0; behaves < 5; behaves++) {
            if (stricmp(name, ParticleBehavesLikeNames[behaves]) == 0)
                goto foundBehaves;
        }
        behaves = -1;
    foundBehaves:
        BehavesLike = behaves;
        return true;
    }
    return false;
}

// This vector cleanup is defined here, after the INI reader. Retail address 0x478440 is also matched
// as VectorClass<RGBClass>::Clear; the original source call form is unestablished. The deleting
// destructor 0x645950 expands the cleanup in this translation unit.
template <class T> ParticleVector<T>::~ParticleVector()
{
    if (Items != 0 && IsAllocated) {
        free(Items);
        Items = 0;
    }
    IsAllocated = false;
    Capacity = 0;
}

// FUNCTION: GAMEMD 0x6454E0
void ParticleTypeClass::ComputeCRC(ParticleCrcView& crc)
{
    ParticleTypeObjectView::ComputeCRC(crc);
    crc.AddInt(MaxDC);
    crc.AddInt(MaxEC);
    crc.AddInt(Damage);
    crc.AddInt(StartFrame);
    crc.AddInt(NumLoopFrames);
    crc.AddInt(Translucency);
    crc.AddInt(WindEffect);
    crc.AddFloat(Velocity);
    crc.AddFloat(Deacc);
    crc.AddInt(Radius);
    crc.AddBool(DeleteOnStateLimit);
    crc.AddByte(EndStateAI);
    crc.AddByte(StartStateAI);
    crc.AddByte(StateAIAdvance);
    crc.AddInt(Translucent25State);
    crc.AddInt(Translucent50State);
    crc.AddBool(Normalized);
    crc.AddInt(NextParticle);
    crc.AddInt(BehavesLike);
    crc.AddDouble(ColorSpeed);
}

// FUNCTION: GAMEMD 0x645620
HRESULT __stdcall ParticleTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_ParticleType;
    return S_OK;
}

// FUNCTION: GAMEMD 0x645660
HRESULT __stdcall ParticleTypeClass::Load(IStream* pStm)
{
    HRESULT hr = ParticleTypeObjectView::Load(pStm);
    if (hr < 0)
        return hr;

    new (this) ParticleTypeClass(ParticleNoInit());
    ParticleSwizzle.Swizzle((void**)&Warhead);

    int count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;

    for (int i = 0; i < count; i++) {
        ParticleColor color(0, 0, 0);
        hr = pStm->Read(&color, 3, 0);
        if (hr < 0)
            return hr;
        ColorList.AddItem(color);
    }
    PostLoad();
    return 0;
}

// FUNCTION: GAMEMD 0x6457A0
HRESULT __stdcall ParticleTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ParticleTypeObjectView::Save(pStm, fClearDirty);
    if (hr < 0)
        return hr;

    int count = ColorList.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;

    for (int i = 0; i < count; i++) {
        hr = pStm->Write(&ColorList.Items[i], 3, 0);
        if (hr < 0)
            return 0;
    }
    return 0;
}
// FUNCTION: GAMEMD 0x6458B0
void ParticleTypeClass::PointerExpired(void* ptr, bool removed)
{
    if (Warhead == ptr)
        Warhead = 0;
}

// FUNCTION: GAMEMD 0x645910
int ParticleTypeClass::Size()
{
    return 0x318;
}

// FUNCTION: GAMEMD 0x645920
int ParticleTypeClass::WhatAmI()
{
    return 0x17;
}

// FUNCTION: GAMEMD 0x645930
bool ParticleTypeClass::vf_32(int a, int b)
{
    return false;
}

// FUNCTION: GAMEMD 0x645940
int ParticleTypeClass::vf_35(int a)
{
    return 0;
}

// GLOBAL: GAMEMD 0x8370BC - the BehavesLike names, indexed by the BehavesLike value (five pointers).
extern const char* const ParticleBehavesLikeNames[5] = { "Gas", "Smoke", "Fire", "Spark", "Railgun" };

static int FindBehavesLike(const char* name)
{
    for (int i = 0; i < 5; i++) {
        if (stricmp(name, ParticleBehavesLikeNames[i]) == 0)
            return i;
    }
    return -1;
}

// SYNTHETIC: GAMEMD 0x645950
// Scalar deleting destructor emitted from the inline ParticleTypeClass destructor.
