// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU185 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6449f0-0x646a7f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// ParticleTypeClass entries (layout and evidence: particle_type_class.h).
//
// Negation of the first three components of a four-float record into a
// destination record (destination in ECX, source in EDX, returns the
// destination; the fourth component is copied). Two copies at different
// addresses; each is verified separately.
//
// Linear name lookups over a fixed table of string pointers (CRT case-insensitive
// compare at 0x7C8D20): the index of the first entry equal to the name, with each
// owner's own table and miss value. The tables are named by retail address; the
// entry count is the distance to the loop end in the body. Each address is
// verified separately.
//
// Cluster methods use the existing 0x644890 and 0x645820 function bodies as
// source hypotheses; row identity and relocations require the current raw oracle.
//
// Field reads and bounded record lookups whose body repeats at two or more
// retail addresses. Each address is compiled and checked on its own; the
// copies differ in the field offset or in the global table they index. Owners
// that are not modelled elsewhere are placeholders `Obj_<ADDR>` / `Rec_<ADDR>`
// declaring only what the body touches, with offset asserts.
//
// Small stand-alone bodies (field readers, zero-initialisers, interface
// forwarders and the like) found at one address each, in ascending retail
// address order. Owners that no other file models are placeholders
// `Obj_<ADDR>` declaring only the members the body touches, with offset
// asserts; interface objects reached through COM slots use the objbase types.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.
//
// Retail RTTI names VectorClass/DynamicVectorClass over RGBClass (3-byte elements, user-declared
// default constructor that zeroes the three bytes). The body is the DynamicVectorClass constructor
// taking a capacity and optional storage, with the VectorClass constructor expanded inline.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

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
#include "../_layout/swizzle_manager_class.h"
#include <string.h>
#include "particles/particle_type_class.h"

extern const char* const ParticleBehavesLikeNames[5];

// GLOBAL: GAMEMD 0x7E9710 - CLSID of ParticleTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_ParticleType =
    { 0x703E044B, 0x0FB1, 0x11D2, { 0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// This vector cleanup is defined here, after the INI reader. Retail address 0x478440 is also matched
// as VectorClass<RGBClass>::Clear; the original source call form is unestablished. The deleting
// destructor 0x645950 expands the cleanup in this translation unit.
template <class T> ParticleVector<T>::~ParticleVector()
{
    if (Items != 0 && IsAllocated) {
        ::operator delete(Items);
        Items = 0;
    }
    IsAllocated = false;
    Capacity = 0;
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

#include "../renderer/quaternion_matrix_methods.h"

// Scale each component; the divisor is taken by value.
static inline Vector3D Divide(const Vector3D& a, double d)
{
    return Vector3D(a.X / d, a.Y / d, a.Z / d);
}

static inline float Element(const float* f, int n)
{
    return f[n];
}

struct FloatQuad_006460C0 {
    float unknown_00;
    float unknown_04;
    float unknown_08;
    float unknown_0C;
    FloatQuad_006460C0(float a, float b, float c, float d)
    {
        unknown_00 = a;
        unknown_04 = b;
        unknown_08 = c;
        unknown_0C = d;
    }
};

// LIBRARY: GAMEMD 0x7C8D20 -- CRT case-insensitive string compare (cdecl, two pointers).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

extern const char* const DAT_00836EE0[5];

extern const char* const DAT_008370BC[5];

extern const char* const DAT_007F0248[12];

extern const char* const DAT_008449F8[3];

// Binary-backed string references (retail bytes including the terminating NUL):
// STRING: GAMEMD 0x817474 "<none>"
// STRING: GAMEMD 0x817694 "none"

#include <string.h>
#include "particles/particle_system_type_class.h"
#include "particles/particle_type_class.h"

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00645C50;

struct Obj_00645C50
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x645C50
    void FUN_00645C50(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_00645C50, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00645C50, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00645C50, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_00645C50, unknown_0C) == 0xC);


#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/obj_00426a70.h"

#include "../_layout/obj_00426a80.h"

#include "../_layout/rec_0046c4d0.h"

extern int DAT_00889F64;
extern Rec_0046C4D0** DAT_008B4154;
extern unsigned int DAT_008B4160;

extern Rec_0046C4D0** DAT_00A83C84;
extern unsigned int DAT_00A83C90;

extern Rec_0046C4D0** DAT_00A83D9C;
extern unsigned int DAT_00A83DA8;

extern Rec_0046C4D0** DAT_00A8EB2C;
extern unsigned int DAT_00A8EB38;

#include <stddef.h>
#include <objbase.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/guid_007e36c0.h"
// GLOBAL: GAMEMD 0x7E36C0
extern const Guid_007E36C0 DAT_007E36C0;

// COM error raiser (COMSUPP library, 0x7DC720).
void __stdcall FUN_007DC720(unsigned int hr);

// Slot 0 of the object's own interface table, called on the object with the
// interface id at 0x7E36C0 and the caller's out pointer.
#include "../_layout/iface_00429400.h"

// Write one dword through 0x4A1DE0.
#include "../_layout/obj_004a1d70.h"

#include "../_layout/obj_004a31f0.h"

// A four-integer record built from its four arguments.
#include "../_layout/quad_0054a120.h"

// The index of an element pointer within a vector of 36-byte records.
#include "../_layout/obj_00589a30.h"

// Read one float of an inline array by index.
#include "../_layout/obj_00645d10.h"


// Run a handler over every entry of a global table of objects.
#include "../_layout/obj_0065fe00.h"
// GLOBAL: GAMEMD 0xB04DAC
extern Obj_0065FE00** DAT_00B04DAC;
// GLOBAL: GAMEMD 0xB04DB8
extern int DAT_00B04DB8;

// Store the argument in the first dword.
#include "../_layout/obj_00681080.h"

// The held interface pointer, raising E_POINTER when there is none.
#include "../_layout/obj_00683030.h"

#include "../_layout/map_00578ad0.h"
// GLOBAL: GAMEMD 0x87F7E8 -- the map instance.
extern Map_00578AD0 DAT_0087F7E8;
#include "../_layout/obj_006a3e30.h"

// The multimedia timer in sixteenths of a unit.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Clear the two dwords after the header.
#include "../_layout/obj_006c9d20.h"

// A value inside the half-open range [low, high).
// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748;
// GLOBAL: GAMEMD 0x7E2AC8
extern const float DAT_007E2AC8;
#include "../_layout/obj_0074ffc0.h"

// Three-component equality.
#include "../_layout/obj_00769510.h"

// The character at an index of a wide string, or zero past its end.
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) -- wcslen.
unsigned int __cdecl FUN_007CA405(const unsigned short* text);
#include "../_layout/obj_007b7150.h"

// Forward a by-value rectangle to the held surface's fill slot (slot 5).
#include "../_layout/rect_007bcf90.h"
#include "../_layout/surface_007bcf90.h"
#include "../_layout/obj_007bcf90.h"

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
#include "../_layout/cell_0050def0.h"

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A8EF98
extern "C" Cell_0050DEF0 DAT_00A8EF98;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

#include "../_layout/team_005095d0.h"

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

#include "../_layout/obj_005095d0.h"


#include "../_layout/obj_0050da10.h"

#include "../_layout/obj_0053ecb0.h"

#include "../_layout/triple_0053eda0.h"

#include "../_layout/obj_0053eda0.h"

#include "../_layout/obj_005402b0.h"

#include "../_layout/obj_00542fc0.h"

#include "../_layout/entry_005657a0.h"

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

#include "../_layout/obj_005657a0.h"


#include "../_layout/iface_005bf500.h"

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

#include "../_layout/vector_005c6120.h"


#include "../_layout/obj_005f9710.h"

#include "../_layout/quad_00645c30.h"

#include "../_layout/record_00656580.h"

#include "../_layout/key_00656580.h"

#include "../_layout/obj_00656580.h"



#include "../_layout/pair_0065c890.h"

#include "../_layout/obj_0068bcb0.h"


#include "../_layout/obj_0068c030.h"


#include "../_layout/owner_006915d0.h"

#include "../_layout/cursor_006915d0.h"

#include "../_layout/obj_00696f10.h"


#include "../_layout/obj_0069b540.h"


#include "../_layout/obj_0069bbe0.h"


#include "../_layout/type_006a46d0.h"

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

#include "../core/vector_class_operations.h"
#include "../core/vector_add_item_free.h"


// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0148
extern const double DAT_007F0148;
// GLOBAL: GAMEMD 0xAC5098
extern double DAT_00AC5098;

// SYNTHETIC: GAMEMD 0x644A20
// GLOBAL: GAMEMD 0xAC50E8
double DAT_00AC50E8 = DAT_00AC5098 / DAT_007F0148;

// SYNTHETIC: GAMEMD 0x644A40
// GLOBAL: GAMEMD 0xAC50D0
double DAT_00AC50D0 = DAT_007E1718 / DAT_00AC50E8;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x644BE0
// MATCHED 100%: the registry appends are the free DynamicVectorAddItemFree form.
ParticleTypeClass::ParticleTypeClass(const char* id)
    : ParticleTypeObjectView(id), NextParticleOffset(0, 0, 0), XVelocity(1), YVelocity(1), MinZVelocity(0),
      ZVelocityRange(1), ColorSpeed(0), StartColor1(0, 0, 0), StartColor2(0, 0, 0), MaxDC(0), MaxEC(1),
      Warhead(0), Damage(0), StartFrame(0), NumLoopFrames(1), Translucency(0), WindEffect(0), Velocity(0),
      Deacc(0), Radius(0), DeleteOnStateLimit(false), EndStateAI(0), StartStateAI(0), StateAIAdvance(4),
      FinalDamageState(0), Translucent25State(0xFF), Translucent50State(0xFF), Normalized(false),
      NextParticle(-1), BehavesLike(-1)
{
    DynamicVectorAddItemFree(&ParticleTypeArray, this);
    DynamicVectorAddItemFree(&ParticleAbstractTypeArray, this);
    unknown_234 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// Position of this exact object in the particle-type array, -1 when absent.
static inline int IndexOfType(ParticleTypeClass* item)
{
    int count = ParticleTypeArray.Count;
    for (int k = 0; k < count; k++) {
        if (ParticleTypeArray.Items[k] == item)
            return k;
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645430
// Index of the particle type with this name; unknown names are created first. -1 for "<none>".
int FUN_00645430(const char* name)
{
    if (stricmp(name, "<none>") != 0) {
        int i;
        for (i = 0; i < ParticleTypeArray.Count; i++) {
            if (stricmp(name, ParticleTypeArray.Items[i]->ID) == 0)
                return i;
        }
        return IndexOfType(new ParticleTypeClass(name));
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006454C0
int* FUN_006454C0(unsigned int index)
{
    if (index < DAT_00A83DA8)
        return &DAT_00A83D9C[index]->unknown_24;
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645620
HRESULT __stdcall ParticleTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_ParticleType;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645660
HRESULT __stdcall ParticleTypeClass::Load(IStream* pStm)
{
    HRESULT hr = ParticleTypeObjectView::Load(pStm);
    if (hr < 0)
        return hr;

    new (this) ParticleTypeClass(ParticleNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Warhead);

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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645820
ParticleTypeClass* ParticleTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;
    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < ParticleTypeArray.Count; i++) {
        if (_stricmp(((ParticleTypeClass**)ParticleTypeArray.Items)[i]->ID, id) == 0)
            return ((ParticleTypeClass**)ParticleTypeArray.Items)[i];
    }

    return new ParticleTypeClass(id);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6458B0
void ParticleTypeClass::PointerExpired(void* ptr, bool removed)
{
    if (Warhead == ptr)
        Warhead = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006458D0
int FUN_006458D0(const char* name)
{
    for (int i = 0; i < 5; ++i) {
        if (strcmpi(name, DAT_008370BC[i]) == 0)
            return i;
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645910
int ParticleTypeClass::Size()
{
    return 0x318;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645920
int ParticleTypeClass::WhatAmI()
{
    return 0x17;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645930
bool ParticleTypeClass::vf_32(int a, int b)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645940
int ParticleTypeClass::vf_35(int a)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x645950
// Scalar deleting destructor emitted from the inline ParticleTypeClass destructor.

// RGB vector providers are owned by vector_color_slot_methods.cpp.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00645B60
int FUN_00645B60(const char* name)
{
    for (int i = 0; i < 12; ++i) {
        if (strcmpi(name, DAT_007F0248[i]) == 0)
            return i;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00645C30
Quad_00645C30::Quad_00645C30(int a, int b, int c, int d)
{
    unknown_0 = a;
    unknown_4 = b;
    unknown_8 = c;
    unknown_C = d;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x645C50
// Stores several members; pops its stack arguments.
void Obj_00645C50::FUN_00645C50(int a1, int a2, int a3, int a4)
{
    unknown_00 = a1;
    unknown_04 = a2;
    unknown_08 = a3;
    unknown_0C = a4;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00645D10
float Obj_00645D10::FUN_00645D10(int index) const
{
    return unknown_00[index];
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006460C0
FloatQuad_006460C0* FUN_006460C0(FloatQuad_006460C0* dest, const FloatQuad_006460C0* src)
{
    *dest = FloatQuad_006460C0(-src->unknown_00, -src->unknown_04, -src->unknown_08, src->unknown_0C);
    return dest;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00646110
FloatQuad_006460C0* FUN_00646110(FloatQuad_006460C0* dest, const FloatQuad_006460C0* src)
{
    *dest = FloatQuad_006460C0(-src->unknown_00, -src->unknown_04, -src->unknown_08, src->unknown_0C);
    return dest;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x646590
// Spherical interpolation from a to b by t. Nearly-parallel inputs fall back
// to linear weights; opposite inputs use quarter-turn sine weights.
Quaternion FUN_00646590(const Quaternion& a, const Quaternion& b, float t)
{
    Quaternion r;
    r.X = 0.0f;
    r.Y = 0.0f;
    r.Z = 0.0f;
    r.W = 1.0f;

    double cosAngle = a.W * b.W + a.Z * b.Z + a.Y * b.Y + a.X * b.X;
    double weightA;
    double weightB;
    int i;
    if (1.0 + cosAngle > 1e-5) {
        double rc = 1.0 - cosAngle;
        if (rc > 1e-5) {
            double angle = FUN_004CADB0(cosAngle);
            double sinAngle = FUN_004CACB0(angle);
            weightA = FUN_004CACB0((1.0f - t) * angle) / sinAngle;
            weightB = FUN_004CACB0(t * angle) / sinAngle;
        } else {
            weightA = 1.0f - t;
            weightB = t;
        }
        for (i = 0; i < 4; i++) {
            r[i] = b[i] * weightB + a[i] * weightA;
        }
    } else {
        weightA = FUN_004CACB0((1.0f - t) * 1.570796326794895);
        weightB = FUN_004CACB0(t * 1.570796326794895);
        for (i = 0; i < 4; i++) {
            r[i] = b[i] * weightB + a[i] * weightA;
        }
    }
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x646730
// Rotation matrix to quaternion via the trace, or via the largest diagonal
// element when the trace is not positive. A zero trace returns identity.
Quaternion FUN_00646730(const Matrix3D& m)
{
    Quaternion q(0.0f, 0.0f, 0.0f, 1.0f);
    int diag[3] = {0, 5, 10};
    int idx[3][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};
    const float* f = &m.Row[0][0];

    double tr = f[0] + f[5] + f[10];
    if (tr == 0.0) {
        return q;
    }
    if (tr > 0.0) {
        double s = FUN_004CAC40(tr + 1.0);
        q.W = (float)(s * 0.5);
        s = 0.5 / s;
        q.X = (float)((m.Row[2][1] - m.Row[1][2]) * s);
        q.Y = (float)((m.Row[0][2] - m.Row[2][0]) * s);
        q.Z = (float)((m.Row[1][0] - m.Row[0][1]) * s);
    } else {
        int i = 0;
        if (Element(f, diag[1]) > Element(f, diag[0])) {
            i = 1;
        }
        if (Element(f, diag[2]) > Element(f, diag[i])) {
            i = 2;
        }
        int j;
        int k;
        switch (i) {
        case 1:
            j = 2;
            k = 0;
            break;
        case 2:
            j = 0;
            k = 1;
            break;
        default:
            j = 1;
            k = 2;
            break;
        }
        double s = FUN_004CAC40(Element(f, diag[i]) - (Element(f, diag[j]) + Element(f, diag[k])) + 1.0);
        q[i] = (float)(s * 0.5);
        s = 0.5 / s;
        q.W = (float)((f[idx[k][j]] - f[idx[j][k]]) * s);
        q[j] = (float)((f[idx[j][i]] + f[idx[i][j]]) * s);
        q[k] = (float)((f[idx[k][i]] + f[idx[i][k]]) * s);
    }
    return q;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x646980
// Rotation matrix of a unit quaternion; the fourth column is zero.
Matrix3D Matrix3D::FromQuaternion(const Quaternion& q)
{
    return Matrix3D(
        1.0f - 2.0f * (q.Y * q.Y + q.Z * q.Z),
        2.0f * (q.X * q.Y - q.W * q.Z),
        2.0f * (q.X * q.Z + q.W * q.Y),
        0.0f,
        2.0f * (q.X * q.Y + q.W * q.Z),
        1.0f - 2.0f * (q.X * q.X + q.Z * q.Z),
        2.0f * (q.Y * q.Z - q.W * q.X),
        0.0f,
        2.0f * (q.X * q.Z - q.W * q.Y),
        2.0f * (q.Y * q.Z + q.W * q.X),
        1.0f - 2.0f * (q.X * q.X + q.Y * q.Y),
        0.0f);
}
