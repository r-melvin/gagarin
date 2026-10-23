// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
// /Ob2: retail keeps out-of-line copies of helpers that have no direct
// callers (0x4AFAA0, 0x4AFED0, 0x4B0DA0) while inlining the same bodies into
// their users (0x4AF9B0, 0x4B0410, 0x4B0DF0 into 0x4B0C40).
//
// DriveLocomotionClass (leaf of the locomotion module). Layout, tables and
// evidence are in drive_locomotion.h; the address-local views of the linked
// foot, cells and track tables are in drive_support_views.h.
//
// Declared here but not defined (other batches): Save 0x4AF800, InWhichLayer
// 0x4B4820, GetClassID 0x4B4830, ZGradient 0x4B4880, Lock 0x4B4BE0, Unlock
// 0x4B4BF0, the large track bodies DrawMatrix 0x4AFF60 and Process 0x4B0500.
// The destructor body 0x4AF5E0 stays scored by ComRel_004AF5E0
// (match/core/multi_vtable_dtor_family_methods.cpp).

#include <new.h>
#include <math.h>
#include <stdlib.h>
#include "drive_locomotion.h"

// LIBRARY: OLE32!OleLoadFromStream, IAT 0x7E15F8 (declared by <ole2.h>).

static inline bool DriveIsEmpty(const LocoCoord& c)
{
    return c.X == DAT_008A0790.X && c.Y == DAT_008A0790.Y && c.Z == DAT_008A0790.Z;
}

static inline bool DriveIsSet(const LocoCoord& c)
{
    return c.X != DAT_008A0790.X || c.Y != DAT_008A0790.Y || c.Z != DAT_008A0790.Z;
}

// Frames left on a timer (the CDTimerClass value inlined by every reader).
static inline int DriveTimeLeft(const CDTimerClass& timer)
{
    int startTime = timer.StartTime;
    int timeLeft = timer.TimeLeft;
    if (startTime != -1) {
        int elapsed = CurrentFrame - startTime;
        if (elapsed < timeLeft)
            return timeLeft - elapsed;
        return 0;
    }
    return timeLeft;
}

// Fraction of the slope timer that has run (1.0 when the timer has no rate).
static inline double DriveSlopeFraction(const RateTimer& timer)
{
    return timer.Rate == 0 ? 1.0 : (double)(timer.Rate - DriveTimeLeft(timer)) / timer.Rate;
}

// FUNCTION: GAMEMD 0x4AF540
DriveLocomotionClass::DriveLocomotionClass()
    : unknown_1C(0), unknown_20(0), SlopeTimer(0),
      DestCoord(DAT_008A0790), HeadTo(DAT_008A0790),
      SpeedAccum(0), unknown_50(0.0), TrackNumber(-1), TrackIndex(-1),
      IsOnShortTrack(false), unknown_61(false), unknown_62(false),
      unknown_63(false), unknown_64(false), UnLocked(true), Piggybackee(0)
{
}

// FUNCTION: GAMEMD 0x4AF610
HRESULT __stdcall DriveLocomotionClass::PiggybackCLSID(CLSID* out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        IPersistPtr persist(Piggybackee);
        if (persist == 0)
            return E_FAIL;
        return persist->GetClassID(out);
    }
    IPersistPtr persist(static_cast<LocomotionClass*>(this));
    if (persist == 0)
        return E_FAIL;
    return persist->GetClassID(out);
}

// FUNCTION: GAMEMD 0x4AF720
HRESULT __stdcall DriveLocomotionClass::QueryInterface(REFIID riid, void** ppv)
{
    HRESULT hr = LocomotionClass::QueryInterface(riid, ppv);
    if (hr == E_NOINTERFACE) {
        if (riid == IID_IPiggyback)
            *ppv = static_cast<IPiggyback*>(this);
        if (*ppv == 0)
            return E_NOINTERFACE;
        AddRef();
        hr = S_OK;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x4AF780
HRESULT __stdcall DriveLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) DriveLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x4AF8E0
HRESULT __stdcall DriveLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x4AF930
HRESULT __stdcall DriveLocomotionClass::EndPiggyback(ILocomotion** out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        *out = Piggybackee;
        Piggybackee.Detach();
        return S_OK;
    }
    return S_FALSE;
}

// FUNCTION: GAMEMD 0x4AF970
bool __stdcall DriveLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0 && UnLocked && !Foot()->unknown_6AD)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x4AFAA0
double DriveLocomotionClass::FUN_004AFAA0()
{
    return DriveSlopeFraction(SlopeTimer);
}

// FUNCTION: GAMEMD 0x4AF9B0
LocoMatrix3D DriveLocomotionClass::FUN_004AF9B0()
{
    LocoMatrix3D matrix;
    matrix.MakeIdentity();
    if (FUN_004AFAA0() < 1.0) {
        matrix = FUN_00755A40(unknown_20, unknown_1C, FUN_004AFAA0());
    } else if (unknown_1C) {
        matrix = FUN_007559B0(unknown_1C);
    }
    return matrix;
}

// FUNCTION: GAMEMD 0x4AFB00
void DriveLocomotionClass::FUN_004AFB00(int ramp)
{
    if (ramp != unknown_1C) {
        unknown_20 = unknown_1C;
        unknown_1C = ramp;
        SlopeTimer = RateTimer(3);
    }
}

// FUNCTION: GAMEMD 0x4AFB40
void __stdcall DriveLocomotionClass::ForceNewSlope(int ramp)
{
    unknown_20 = ramp;
    unknown_1C = ramp;
    SlopeTimer = RateTimer(0);
}

// FUNCTION: GAMEMD 0x4AFB80
bool __stdcall DriveLocomotionClass::IsMoving()
{
    if (DriveIsSet(DestCoord))
        return true;
    if (DriveIsSet(HeadTo)) {
        if (HeadTo.X != Foot()->GetLocation().X || HeadTo.Y != Foot()->GetLocation().Y)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4AFC20
bool __stdcall DriveLocomotionClass::IsMovingNow()
{
    if (Foot()->PrimaryFacing.FUN_004C9480())
        return true;
    if (IsMoving() && DriveIsSet(HeadTo) && Foot()->vf_538() > 0)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x4AFC90
LocoCoord __stdcall DriveLocomotionClass::Destination()
{
    LocoCoord c;
    c.X = DestCoord.X;
    c.Y = DestCoord.Y;
    c.Z = DestCoord.Z;
    return c;
}

// FUNCTION: GAMEMD 0x4AFCC0
LocoCoord __stdcall DriveLocomotionClass::HeadToCoord()
{
    LocoCoord c;
    if (DriveIsSet(HeadTo)) {
        c.X = HeadTo.X;
        c.Y = HeadTo.Y;
        c.Z = HeadTo.Z;
        return c;
    }
    LocoCoord here = Foot()->GetLocation();
    c.X = here.X;
    c.Y = here.Y;
    c.Z = here.Z;
    return c;
}

// FUNCTION: GAMEMD 0x4AFD40
void __stdcall DriveLocomotionClass::MoveTo(LocoCoord to)
{
    if (Foot()->vf_37C() || Foot()->vf_380() || Foot()->vf_1D4() || Foot()->vf_1D8())
        return;
    DestCoord = to;
    if (DriveIsSet(to)) {
        LocoCoord where = to;
        if (DriveMap().FUN_00565730(&where)->Flags & 0x100)
            DestCoord.Z += DAT_008A07C4;
    }
}

// FUNCTION: GAMEMD 0x4AFE00
void __stdcall DriveLocomotionClass::StopMoving()
{
    if (DriveIsSet(HeadTo) && Foot()->vf_084()->unknown_C94 && !Foot()->unknown_6D0) {
        DriveFootView* foot = Foot()->unknown_6C8;
        if (foot) {
            do {
                foot->Locomotor->StopMoving();
                foot = foot->unknown_6C8;
            } while (foot && foot != foot->unknown_6C8);
        }
    }
    unknown_50 = unknown_50 < 0.3f ? unknown_50 : 0.3f;
    DestCoord = DAT_008A0790;
}

// FUNCTION: GAMEMD 0x4AFED0
int DriveLocomotionClass::FUN_004AFED0()
{
    if (FUN_004AFAA0() == 1.0
        && fabs(Foot()->unknown_328) < 0.005
        && fabs(Foot()->unknown_32C) < 0.005)
        return 1;
    return 0;
}

// FUNCTION: GAMEMD 0x4B0410
LocoMatrix3D __stdcall DriveLocomotionClass::ShadowMatrix(unsigned int* key)
{
    if (!FUN_004AFED0() && key)
        *key = (unsigned int)-1;
    return LocomotionClass::ShadowMatrix(key);
}

// FUNCTION: GAMEMD 0x4B04D0
void __stdcall DriveLocomotionClass::Unlimbo()
{
    ForceNewSlope(Foot()->vf_1BC()->SlopeIndex);
}

// FUNCTION: GAMEMD 0x4B0AD0
void DriveLocomotionClass::FUN_004B0AD0(const LocoCoord* coord, int mode)
{
    if (DriveIsEmpty(*coord))
        return;
    if (!IsOnShortTrack && TrackNumber != -1) {
        int control = DriveTrackEntries_007E7B28[TrackNumber].unknown_0;
        if (control) {
            DriveTrackPoint* points = DriveTrackControls_007E7A28[control].Points;
            int jump = DriveTrackControls_007E7A28[control].unknown_C;
            if (jump > -1) {
                DriveTrackPoint& at_jump = points[jump];
                int facing = at_jump.Facing;
                if (TrackIndex < jump) {
                    LocoPoint2D point(at_jump.X, at_jump.Y);
                    LocoPoint2D at = FUN_004B4780(&point, &facing);
                    if (mode == 0) {
                        LocoCoord c;
                        c.Z = Foot()->vf_1D0();
                        c.X = at.X;
                        c.Y = at.Y;
                        Foot()->vf_0F4(&c);
                    } else if (mode == 1 || mode == 3) {
                        LocoCoord c;
                        c.Z = Foot()->vf_1D0();
                        c.X = at.X;
                        c.Y = at.Y;
                        Foot()->vf_0F0(&c);
                    }
                }
            }
        }
    }
    if (mode == 0)
        Foot()->vf_0F4(coord);
    else if (mode == 1 || mode == 3)
        Foot()->vf_0F0((LocoCoord*)coord);
}

// FUNCTION: GAMEMD 0x4B0C40
void __stdcall DriveLocomotionClass::ForceTrack(int track, LocoCoord coord)
{
    TrackNumber = track;
    TrackIndex = 0;
    if (DriveIsSet(coord)) {
        LocoCoord where = coord;
        if (FUN_004B0DF0(&where)) {
            DestCoord = coord;
            unknown_50 = 1.0;
        }
    }
}

// FUNCTION: GAMEMD 0x4B0DA0
bool DriveLocomotionClass::FUN_004B0DA0()
{
    if (DriveIsSet(HeadTo)) {
        HeadTo = DAT_008A0790;
        unknown_63 = false;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4B0DF0
bool DriveLocomotionClass::FUN_004B0DF0(const LocoCoord* coord)
{
    FUN_004B0DA0();
    if (DriveIsSet(*coord)) {
        HeadTo = *coord;
        unknown_63 = true;
        if (DriveMap().FUN_00565730(coord)->FUN_00481A00(Foot()) && !Foot()->unknown_081) {
            FUN_004B0AD0(coord, 1);
            return true;
        }
        if (Foot()->unknown_090) {
            HeadTo = DAT_008A0790;
            unknown_63 = false;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x4B0EF0
void __stdcall DriveLocomotionClass::DoTurn(unsigned long dir)
{
    unsigned long desired = dir;
    Foot()->PrimaryFacing.FUN_004C9220(&desired);
}

// FUNCTION: GAMEMD 0x4B4770
void __cdecl FUN_004B4770()
{
}

// FUNCTION: GAMEMD 0x4B4780
LocoPoint2D DriveLocomotionClass::FUN_004B4780(const LocoPoint2D* point, int* facing)
{
    int dir = *facing;
    unsigned int flags = DriveTrackEntries_007E7B28[TrackNumber].unknown_8;
    int x = point->X;
    int y = point->Y;
    if (flags & 1) {
        int t = x;
        x = y;
        y = t;
        dir = (-dir - 0x40) & 0xFF;
    }
    if (flags & 2) {
        x = -x;
        dir = -dir & 0xFF;
    }
    if (flags & 4) {
        y = -y;
        dir = (-dir - 0x80) & 0xFF;
    }
    *facing = dir;
    return LocoPoint2D(HeadTo.X + x, HeadTo.Y + y);
}

// FUNCTION: GAMEMD 0x4B4800
void DriveLocomotionClass::FUN_004B4800(int arg)
{
    DriveMap().FUN_00578AD0(Foot(), &arg);
}

// FUNCTION: GAMEMD 0x4B4870
int __stdcall DriveLocomotionClass::ZAdjust()
{
    return 0;
}

// FUNCTION: GAMEMD 0x4B4890
bool DriveLocomotionClass::FUN_004B4890()
{
    if (Foot()->unknown_598 == 0) {
        Foot()->vf_480(0, 1);
        return false;
    }
    Foot()->FUN_004DF0D0();
    return Foot()->vf_484(0, 1);
}

// FUNCTION: GAMEMD 0x4B48D0
void __stdcall DriveLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (DriveIsSet(HeadTo))
        FUN_004B0AD0(&HeadTo, mark);
}

// FUNCTION: GAMEMD 0x4B4920
bool __stdcall DriveLocomotionClass::IsMovingHere(LocoCoord to)
{
    LocoCoord head = HeadToCoord();
    if (DriveIsEmpty(head))
        return false;
    if (!IsOnShortTrack && TrackNumber != -1) {
        int control = DriveTrackEntries_007E7B28[TrackNumber].unknown_0;
        if (control) {
            DriveTrackPoint* points = DriveTrackControls_007E7A28[control].Points;
            int jump = DriveTrackControls_007E7A28[control].unknown_C;
            if (jump > -1) {
                DriveTrackPoint& at_jump = points[jump];
                int facing = at_jump.Facing;
                if (TrackIndex < jump) {
                    LocoPoint2D point(at_jump.X, at_jump.Y);
                    LocoPoint2D at = FUN_004B4780(&point, &facing);
                    LocoCoord here = Foot()->GetLocation();
                    if (DriveCellCoord(at.X, at.Y) == DriveCellCoord(to.X, to.Y)
                        && abs(here.Z - to.Z) <= DAT_008A07D0)
                        return true;
                }
            }
        }
    }
    if (DriveCellCoord(head.X, head.Y) == DriveCellCoord(to.X, to.Y)
        && abs(head.Z - to.Z) <= DAT_008A07D0)
        return true;
    return false;
}

// Eight-way facing of a track entry's heading byte (high byte of a 16-bit
// direction): `SHR 0xC; INC; SHR 1; AND 7` at 0x4B4B61.
static inline int DriveTrackFacing8(unsigned char heading)
{
    unsigned short raw = (unsigned short)(heading << 8);
    return ((raw >> 12) + 1) >> 1 & 7;
}

// FUNCTION: GAMEMD 0x4B4B00
bool __stdcall DriveLocomotionClass::WillJumpTracks()
{
    int dir = Foot()->unknown_5E0;
    if (dir >= -1 && dir <= 8) {
        DriveTrackEntry& entry = DriveTrackEntries_007E7B28[TrackNumber];
        int control = IsOnShortTrack ? entry.unknown_1 : entry.unknown_0;
        bool turning = false;
        if (dir != 8 && dir != -1 && DriveTrackFacing8(entry.unknown_4) != dir)
            turning = true;
        if (dir != -1 && turning
            && DriveTrackControls_007E7A28[control].unknown_4 == TrackIndex && TrackIndex != 0) {
            int next = DriveTrackEntries_007E7B28[dir + DriveTrackFacing8(entry.unknown_4) * 8].unknown_0;
            if (next && DriveTrackControls_007E7A28[next].unknown_8)
                return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x4B4BE0
void __stdcall DriveLocomotionClass::Lock()
{
    UnLocked = false;
}

// FUNCTION: GAMEMD 0x4B4BF0
void __stdcall DriveLocomotionClass::Unlock()
{
    UnLocked = true;
}

// FUNCTION: GAMEMD 0x4B4C00
int __stdcall DriveLocomotionClass::GetTrackNumber()
{
    return TrackNumber;
}

// FUNCTION: GAMEMD 0x4B4C10
int __stdcall DriveLocomotionClass::GetTrackIndex()
{
    return TrackIndex;
}

// FUNCTION: GAMEMD 0x4B4C20
int __stdcall DriveLocomotionClass::GetSpeedAccum()
{
    return SpeedAccum;
}

// FUNCTION: GAMEMD 0x4B4C30
// (LocomotionClass::IsDirty, inline primary slot 4; see loco_base.h.)

// FUNCTION: GAMEMD 0x4B4C60
// FUNCTION: GAMEMD 0x4B4C70
// FUNCTION: GAMEMD 0x4B4C80
// FUNCTION: GAMEMD 0x4B4C90
// FUNCTION: GAMEMD 0x4B4CA0
// (LocomotionClass inline slots 36/37/38/43/44, emitted here through this
// class's ILocomotion table; see loco_base.h.)

// FUNCTION: GAMEMD 0x4B4CB0
ULONG __stdcall DriveLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x4B4CC0
ULONG __stdcall DriveLocomotionClass::Release()
{
    return LocomotionClass::Release();
}

// FUNCTION: GAMEMD 0x4B4CD0
bool __stdcall DriveLocomotionClass::IsPiggybacking()
{
    return Piggybackee != 0;
}

// FUNCTION: GAMEMD 0x4B4CF0
int DriveLocomotionClass::Size()
{
    return sizeof(DriveLocomotionClass);
}

// SYNTHETIC: GAMEMD 0x4B4D00 -- compiler-generated scalar deleting destructor.
