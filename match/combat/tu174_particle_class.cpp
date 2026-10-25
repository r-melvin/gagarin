// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU174 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x62b3d0-0x62da3f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// ParticleClass entries (layout and evidence: particle_class.h).

#include <new.h>
#include "../_layout/swizzle_manager_class.h"
#include <stdlib.h>
#include "particles/particle_class.h"

extern "C" const CLSID CLSID_Particle;

// This by-value helper induces the temporary construction sequence used by the
// function-local static initializer. It is a source-level code-generation aid,
// not a claim about a retail standalone helper symbol.
static inline ParticleCellCoord MakeInvalidCell()
{
    ParticleCellCoord c(0x7FFF, 0x7FFF);
    return c;
}

// GLOBAL: GAMEMD 0x7E9700 - CLSID of ParticleClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Particle =
    { 0x0E272DCC, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EF900
extern const double DAT_007EF900;
// GLOBAL: GAMEMD 0xAC49B8
extern double DAT_00AC49B8;

// SYNTHETIC: GAMEMD 0x62B400
// GLOBAL: GAMEMD 0xAC4A10
double DAT_00AC4A10 = DAT_00AC49B8 / DAT_007EF900;

// SYNTHETIC: GAMEMD 0x62B420
// GLOBAL: GAMEMD 0xAC49F8
double DAT_00AC49F8 = DAT_007E1718 / DAT_00AC4A10;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62B5E0
// CAPPED: best variant of several; remaining delta is scheduling/register order (see the report).
ParticleClass::ParticleClass(ParticleTypeClass* type, const ParticleCoord* coord, const ParticleCoord* targetCoord,
                             ParticleSystemClass* owner)
    : Type(type), Color(0, 0, 0), ColorIndex(0), ColorBlend(0), unknown_C0(0), unknown_C4(0),
      unknown_C8(0), unknown_CC(0), unknown_D0(0), unknown_D4(-1.0f), unknown_D8(0), unknown_DC(0),
      unknown_E0(0), Velocity(Type->Velocity), TargetCoord(*targetCoord), Coord(*coord),
      Coord2(ParticleEmptyCoord),
      Direction((float)(targetCoord->X - coord->X), (float)(targetCoord->Y - coord->Y),
                (float)(targetCoord->Z - coord->Z)),
      Position((float)coord->X, (float)coord->Y, (float)coord->Z), Owner(owner),
      unknown_12C(Type->StateAIAdvance), unknown_12D(0), unknown_12E(Type->StartStateAI),
      unknown_12F((unsigned char)Type->Translucency), unknown_130(0), unknown_131(0)
{
    ParticleRttiBase::Create_ID();
    ParticleArray.AddItem(this);

    if (Type->BehavesLike == 1)
        Velocity += (float)(ParticleScenario->Random.Random() % 2);

    unknown_12A = (short)Type->MaxDC;
    if (Type->BehavesLike == 4) {
        int roll = ParticleScenario->Random.Random();
        unknown_128 = (short)(abs(roll % 10) + (short)Type->MaxEC);
    } else {
        int roll = ParticleScenario->Random.Random();
        unknown_128 = (short)(abs(roll % Type->MaxEC) + (short)Type->MaxEC);
    }

    ParticleCoord pos(coord->X, coord->Y, coord->Z);
    if (pos.Z <= ParticleMap.GetHeight(coord))
        pos.Z = ParticleMap.GetHeight(coord);
    vf_109(&pos);

    Direction.Normalize();

    if (Type->Normalized) {
        int dx = coord->X - targetCoord->X;
        int dy = coord->Y - targetCoord->Y;
        float fx = (float)abs((int)(Direction.X * Velocity));
        float fy = (float)abs((int)(Direction.Y * Velocity));
        float ratio = 10000.0f;
        if (fx > 1e-6)
            ratio = abs(dx) / fx;
        if (fy > 1e-6) {
            float t = abs(dy) / fy;
            if (!(ratio < t))
                ratio = t;
        }
        unknown_12C = (unsigned char)(int)(ratio / (Type->FinalDamageState + 1) + 1.0);
    }

    if (Type->ColorList.Count > 0) {
        if (Type->StartColor1.R == 0 && Type->StartColor1.G == 0 && Type->StartColor1.B == 0 &&
            Type->StartColor2.R == 0 && Type->StartColor2.G == 0 && Type->StartColor2.B == 0) {
            Color = Type->ColorList.Items[0];
        } else {
            ParticleColorMixer mixer;
            Color = *mixer.Mix(&Type->StartColor1, &Type->StartColor2,
                               (float)(ParticleScenario->Random.Random(0, 0x7FFFFFFE) * 4.656612873077393e-10));
        }
    }

    Unlimbo(&pos, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62BB20
ParticleClass::ParticleClass()
    : Type(0), Color(0, 0, 0), ColorIndex(0), ColorBlend(0), unknown_C0(0), unknown_C4(0),
      unknown_C8(0), unknown_CC(0), unknown_D0(0), unknown_D4(-1.0f), unknown_D8(0), unknown_DC(0),
      unknown_E0(0), Velocity(0), TargetCoord(ParticleEmptyCoord), Coord(ParticleEmptyCoord),
      Coord2(ParticleEmptyCoord), Direction(0, 0, 0), Position(0, 0, 0), Owner(0), unknown_12C(0),
      unknown_12D(0), unknown_12E(0), unknown_12F(0), unknown_130(0), unknown_131(0)
{
    ParticleArray.AddItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62CEC0
// CAPPED: stack-slot layout and register assignment differ from retail (see the report).
void ParticleClass::vf_69(void* where, ParticleRect* clip)
{
    if (ParticleFrameCounter < ParticleFrameLimit()) {
        if (Type->Damage == 0)
            return;
    }
    if (ParticleDetailMode == 0) {
        if (Type->BehavesLike == 1 || Type->BehavesLike == 3)
            return;
    }
    if (!ParticleSkipShroudTest && ParticleShroudEnabled != 0 && (ParticleScenario->Flags & 0x1000)) {
        ParticleCoord position = Location;
        if (ParticleMap.FUN_005865E0(&position))
            return;
    }

    int behaves = Type->BehavesLike;
    if (behaves != 3 && behaves != 4) {
        int zAdjust = -15 - ParticleHeightScale(vf_116());
        void* object = vf_27();
        if (object == 0)
            return;
        int flags = 0x2800;
        int frame = vf_122();
        if (ParticleDetailMode == 2) {
            if (unknown_12F == 0x19)
                flags = 0x2802;
            else if (unknown_12F == 0x32)
                flags = 0x2804;
            else if (unknown_12F >= 0x4B)
                flags = 0x2806;
        }
        ParticleScreenPoint offset = {0, 0};
        ParticleDrawShape(ParticleSurface, ParticleDrawContext, object, frame, where, clip, flags | 0xE00, 0,
                          zAdjust, 2, 1000, 0, 0, 0, offset);
        return;
    }

    ParticleCoord location = Location;
    ParticleScreenPoint point;
    ParticleTactical->CoordsToClient(&location, &point);
    point.Y += ParticleScreenYOffset;
    if (point.X < clip->X || point.X >= clip->X + clip->Width)
        return;
    if (point.Y < clip->Y || point.Y >= clip->Y + clip->Height)
        return;

    int light = *ParticleLightMap->GetLevel(point.X, point.Y - ParticleLightMap->OriginY);
    if (light == 0)
        return;

    ParticleCoord here = Location;
    int viewY = point.Y - ParticleViewport->OriginY;
    int top = (unsigned short)(ParticleViewport->Height + ParticleViewport->OriginY - point.Y);
    top -= ParticleHeightScale(Location.Z);
    top -= 0x32;
    if (top >= *ParticleViewport->GetLimit(point.X, viewY))
        return;

    const ParticleColor* items = Type->ColorList.Items;
    ParticleColor from = ColorIndex == 0 ? Color : items[ColorIndex];
    ParticleColor to = items[ColorIndex + 1];
    double keep = 1.0 - ColorBlend;
    int r = (int)(to.R * ColorBlend + from.R * keep);
    int g = (int)(to.G * ColorBlend + from.G * keep);
    int b = (int)(to.B * ColorBlend + from.B * keep);
    if (light < 0x7F) {
        r = r * light >> 7;
        g = g * light >> 7;
        b = b * light >> 7;
    }
    unsigned int color = ((b >> gg_b_translucent_pixel_format.loss2 << gg_b_translucent_pixel_format.pos2) & 0xFFFF) |
                         ((g >> gg_b_translucent_pixel_format.loss1 << gg_b_translucent_pixel_format.pos1) & 0xFFFF) |
                         ((r >> gg_b_translucent_pixel_format.loss0 << gg_b_translucent_pixel_format.pos0) & 0xFFFF);
    ParticleSurface->PlotPixel(&point, color);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D6F0
bool ParticleClass::vf_73(int arg)
{
    return ParticleObjectView::vf_73(arg) ? true : false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D710
// The function-local static uses global 0xAC49D0 and guard byte 0xAC4998;
// its atexit callback is the bare RET at 0x62D760.
ParticleCellCoord* ParticleClass::vf_66(void* unused)
{
    static ParticleCellCoord invalidCell = MakeInvalidCell();
    return &invalidCell;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x62D760 (compiler-generated atexit callback for vf_66 local static).

// FUNCTION: GAMEMD 0x62D770
int ParticleClass::InWhichLayer()
{
    return 3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D7A0
HRESULT __stdcall ParticleClass::Load(IStream* pStm)
{
    HRESULT hr = ParticleObjectView::Load(pStm);
    if (hr >= 0) {
        new (this) ParticleClass(ParticleNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);
        hr = 0;
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D810
HRESULT __stdcall ParticleClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ParticleObjectView::Save(pStm, fClearDirty);
    unknown_130 = 1;
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D830
int ParticleClass::vf_122()
{
    switch (Type->BehavesLike) {
    case 0:
    case 1:
        return unknown_12E;
    case 2: {
        ParticleScreenPoint from;
        ParticleScreenPoint to;
        ParticleTactical->CoordsToClient(&Coord, &from);
        ParticleTactical->CoordsToClient(&TargetCoord, &to);
        int facing = ParticleFacingBetween(&from, &to);
        if (facing == 2 || facing == 6)
            return unknown_12E + Type->EndStateAI * 2;
        else if (facing == 4 || facing == 0)
            return unknown_12E;
        else if (facing == 1 || facing == 5)
            return Type->EndStateAI + unknown_12E;
        else if (facing == 3 || facing == 7)
            return Type->EndStateAI * 3 + unknown_12E;
        else
            return 0;
    }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D930
HRESULT __stdcall ParticleClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_Particle;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D970
int ParticleClass::Size()
{
    return 0x138;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D980
int ParticleClass::WhatAmI()
{
    return 0x16;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62D990
ParticleTypeObjectView* ParticleClass::GetType()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x62D9A0 (compiler-generated scalar deleting destructor).
