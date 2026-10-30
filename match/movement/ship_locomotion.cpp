// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /Ob2
//
// ShipLocomotionClass (layout and tables in _layout/ship_locomotion_class.h).
// The constructor and the COM / IPiggyback bodies below are the same shapes as
// DriveLocomotionClass's (movement/drive_locomotion.cpp), compiled against
// Ship's own file-scope empty coordinate and tables. Defining the constructor
// makes VC6 emit Ship's three tables here, and with them the ILocomotion (+4)
// and IPiggyback (+0x18) adjustor thunks.
//
// The destructor body 0x69ECF0 stays scored by ComRel_0069ECF0
// (match/core/multi_vtable_dtor_family_methods.cpp).

#include <new.h>
#include <math.h>
#include <stdlib.h>
#include "../_layout/ship_locomotion_class.h"
#include "drive_support_views.h"

GG_STATIC_ASSERT(sizeof(((ShipLocomotionClass*)0)->SpeedAccum) == 4);
GG_STATIC_ASSERT(sizeof(((ShipLocomotionClass*)0)->Piggybackee) == 4);

// Ship's foot is the same FootClass prefix the Drive bodies read.
static inline DriveFootView* ShipFoot(ShipLocomotionClass* self)
{
    return (DriveFootView*)self->LinkedTo;
}

// GLOBAL: GAMEMD 0xB077F8 - the empty coordinate this TU compares against
// (three dwords, read by the constructor at 0x69EC72..0x69EC83).
extern "C" LocoCoord DAT_00B077F8;

// GLOBAL: GAMEMD 0xB0782C - height added to a bridge-cell destination (MoveTo 0x69F450).
extern "C" int DAT_00B0782C;

// GLOBAL: GAMEMD 0x7F2A40 - 12-byte track entries indexed by TrackNumber (WillJumpTracks 0x6A4130).
extern DriveTrackEntry ShipTrackEntries_007F2A40[];
// GLOBAL: GAMEMD 0x7F2960 - 16-byte track controls (`SHL ESI,4; [ESI+0x7F2964]` at 0x6A41B0).
extern DriveTrackControl ShipTrackControls_007F2960[];

// GLOBAL: GAMEMD 0xB07838 - height tolerance read by IsMovingHere 0x6A3F50.
extern "C" int DAT_00B07838;

// LIBRARY: OLE32!OleLoadFromStream, IAT 0x7E15F8 (declared by <ole2.h>).

// A 16-bit binary angle stored in a dword slot: the heading byte is placed in
// the high byte of the word (`MOV BH,[ECX+4]; MOV [ESP+0x10],BX`) and the whole
// slot is read back (`MOV EBX,[ESP+0x10]`) before the shift at 0x6A4191.
union ShipAngle
{
    unsigned short Raw;
    unsigned int   Whole;
};

static inline int ShipTrackFacing8(unsigned char heading)
{
    ShipAngle angle;
    angle.Raw = (unsigned short)(heading << 8);
    return ((angle.Whole >> 12) + 1) >> 1 & 7;
}

// Frames left on a timer (the CDTimerClass value inlined by its readers).
static inline int ShipTimeLeft(const CDTimerClass& timer)
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
static inline double ShipSlopeFraction(const RateTimer& timer)
{
    return timer.Rate != 0 ? (double)(timer.Rate - ShipTimeLeft(timer)) / timer.Rate : 1.0;
}

// FUNCTION: GAMEMD 0x69EC50
ShipLocomotionClass::ShipLocomotionClass()
    : unknown_1C(0), unknown_20(0), SlopeTimer(0),
      DestCoord(DAT_00B077F8), HeadTo(DAT_00B077F8),
      SpeedAccum(0), unknown_50(0.0), TrackNumber(-1), TrackIndex(-1),
      unknown_60(false), unknown_61(false), unknown_62(false),
      unknown_63(false), unknown_64(false), UnLocked(true), Piggybackee(0)
{
}

// FUNCTION: GAMEMD 0x69ED20
HRESULT __stdcall ShipLocomotionClass::PiggybackCLSID(CLSID* out)
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

// FUNCTION: GAMEMD 0x69EE30
HRESULT __stdcall ShipLocomotionClass::QueryInterface(REFIID riid, void** ppv)
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

// FUNCTION: GAMEMD 0x69EE90
HRESULT __stdcall ShipLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) ShipLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x69EF10
HRESULT __stdcall ShipLocomotionClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = LocomotionClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        bool hasPiggyback;
        if (Piggybackee != 0) {
            hasPiggyback = true;
            pStm->Write(&hasPiggyback, 1, 0);
            IPersistStreamPtr persist(Piggybackee);
            hr = OleSaveToStream(persist, pStm);
        } else {
            hasPiggyback = false;
            pStm->Write(&hasPiggyback, 1, 0);
        }
    }
    return hr;
}

// FUNCTION: GAMEMD 0x69EFF0
HRESULT __stdcall ShipLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x69F040
HRESULT __stdcall ShipLocomotionClass::EndPiggyback(ILocomotion** out)
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

static inline bool ShipIsSet(const LocoCoord& c)
{
    return c.X != DAT_00B077F8.X || c.Y != DAT_00B077F8.Y || c.Z != DAT_00B077F8.Z;
}

static inline bool ShipIsEmpty(const LocoCoord& c)
{
    return c.X == DAT_00B077F8.X && c.Y == DAT_00B077F8.Y && c.Z == DAT_00B077F8.Z;
}

// FUNCTION: GAMEMD 0x69F080
bool __stdcall ShipLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0 && UnLocked && !ShipFoot(this)->unknown_6AD)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x69F1B0
double ShipLocomotionClass::FUN_0069F1B0()
{
    return SlopeTimer.Rate == 0 ? 1.0 : (double)(SlopeTimer.Rate - ShipTimeLeft(SlopeTimer)) / SlopeTimer.Rate;
}

// FUNCTION: GAMEMD 0x69F210
// Starts a slope transition to a new ramp when it differs from the current one.
void ShipLocomotionClass::FUN_0069F210(int ramp)
{
    if (ramp != unknown_1C) {
        unknown_20 = unknown_1C;
        unknown_1C = ramp;
        SlopeTimer = RateTimer(3);
    }
}

// FUNCTION: GAMEMD 0x69F250
void __stdcall ShipLocomotionClass::ForceNewSlope(int ramp)
{
    unknown_20 = ramp;
    unknown_1C = ramp;
    SlopeTimer = RateTimer(0);
}

// FUNCTION: GAMEMD 0x69F290
bool __stdcall ShipLocomotionClass::IsMoving()
{
    if (ShipIsSet(DestCoord))
        return true;
    if (ShipIsSet(HeadTo)) {
        if (HeadTo.X != ShipFoot(this)->GetLocation().X || HeadTo.Y != ShipFoot(this)->GetLocation().Y)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x69F330
bool __stdcall ShipLocomotionClass::IsMovingNow()
{
    if (((DriveFootView*)LinkedTo)->PrimaryFacing.FUN_004C9480() != 0)
        return true;
    if (IsMoving() && ShipIsSet(HeadTo) && ShipFoot(this)->vf_538() > 0)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x69F3A0
LocoCoord __stdcall ShipLocomotionClass::Destination()
{
    LocoCoord c;
    c.X = DestCoord.X;
    c.Y = DestCoord.Y;
    c.Z = DestCoord.Z;
    return c;
}

// FUNCTION: GAMEMD 0x69F3D0
LocoCoord __stdcall ShipLocomotionClass::HeadToCoord()
{
    LocoCoord c;
    if (ShipIsSet(HeadTo)) {
        c.X = HeadTo.X;
        c.Y = HeadTo.Y;
        c.Z = HeadTo.Z;
        return c;
    }
    LocoCoord here = ShipFoot(this)->GetLocation();
    c.X = here.X;
    c.Y = here.Y;
    c.Z = here.Z;
    return c;
}

// FUNCTION: GAMEMD 0x69F450 (partial: retail pushes EDI up front and addresses DestCoord through it)
void __stdcall ShipLocomotionClass::MoveTo(LocoCoord to)
{
    if (ShipFoot(this)->vf_37C() || ShipFoot(this)->vf_380() || ShipFoot(this)->vf_1D4() || ShipFoot(this)->vf_1D8())
        return;
    DestCoord = to;
    if (ShipIsSet(to)) {
        if (DriveMap().FUN_00565730(&to)->Flags & 0x100)
            DestCoord.Z += DAT_00B0782C;
    }
}

// FUNCTION: GAMEMD 0x69F510
void __stdcall ShipLocomotionClass::StopMoving()
{
    if (ShipIsSet(HeadTo) && ShipFoot(this)->vf_084()->unknown_C94 && !ShipFoot(this)->unknown_6D0) {
        DriveFootView* foot = ShipFoot(this)->unknown_6C8;
        if (foot) {
            do {
                foot->Locomotor->StopMoving();
                foot = foot->unknown_6C8;
            } while (foot && foot != foot->unknown_6C8);
        }
    }
    unknown_50 = unknown_50 < 0.3f ? unknown_50 : 0.3f;
    DestCoord = DAT_00B077F8;
}

// FUNCTION: GAMEMD 0x69FB20 (partial: retail branches on Rate != 0 into the compute block and loads key after the FPU test)
Matrix3D __stdcall ShipLocomotionClass::ShadowMatrix(unsigned int* key)
{
    bool settled = ShipSlopeFraction(SlopeTimer) == 1.0
        && fabs(ShipFoot(this)->unknown_328) < 0.005
        && fabs(ShipFoot(this)->unknown_32C) < 0.005;
    if (!settled && key)
        *key = (unsigned int)-1;
    return LocomotionClass::ShadowMatrix(key);
}

// FUNCTION: GAMEMD 0x69FBE0
void __stdcall ShipLocomotionClass::Unlimbo()
{
    ForceNewSlope(ShipFoot(this)->vf_1BC()->SlopeIndex);
}

// FUNCTION: GAMEMD 0x6A0310 (partial: inlines 0x6A04C0, same register-choice diffs)
void __stdcall ShipLocomotionClass::ForceTrack(int track, LocoCoord coord)
{
    TrackNumber = track;
    TrackIndex = 0;
    if (ShipIsSet(coord)) {
        LocoCoord where = coord;
        if (FUN_006A04C0(&where)) {
            DestCoord = coord;
            unknown_50 = 1.0;
        }
    }
}

// FUNCTION: GAMEMD 0x6A0470
bool ShipLocomotionClass::FUN_006A0470()
{
    if (ShipIsSet(HeadTo)) {
        HeadTo = DAT_00B077F8;
        unknown_63 = false;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6A04C0 (partial 83%: retail loads the foot into ECX for the push, compiled uses EAX)
bool ShipLocomotionClass::FUN_006A04C0(const LocoCoord* coord)
{
    FUN_006A0470();
    if (ShipIsSet(*coord)) {
        HeadTo = *coord;
        unknown_63 = true;
        if (DriveMap().FUN_00565730(coord)->FUN_00481A00(ShipFoot(this)) && !ShipFoot(this)->unknown_081) {
            FUN_006A01A0(coord, 1);
            return true;
        }
        if (ShipFoot(this)->unknown_090) {
            HeadTo = DAT_00B077F8;
            unknown_63 = false;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6A05C0
void __stdcall ShipLocomotionClass::DoTurn(unsigned long dir)
{
    unsigned long desired = dir;
    ShipFoot(this)->PrimaryFacing.FUN_004C9220(&desired);
}

// FUNCTION: GAMEMD 0x6A3DB0
// Place a track-local point in the world: the point is mirrored or swapped as the current
// track's flag bits ask (turning the facing the same way), then offset by the head-to coordinate.
LocoPoint2D ShipLocomotionClass::FUN_006A3DB0(const LocoPoint2D* point, int* facing)
{
    int dir = *facing;
    unsigned int flags = ShipTrackEntries_007F2A40[TrackNumber].unknown_8;
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

// FUNCTION: GAMEMD 0x6A3EA0
int __stdcall ShipLocomotionClass::ZAdjust()
{
    return 0;
}

// FUNCTION: GAMEMD 0x6A3EB0
int __stdcall ShipLocomotionClass::ZGradient()
{
    return LocomotionClass::ZGradient();
}

// FUNCTION: GAMEMD 0x6A3EC0
bool ShipLocomotionClass::FUN_006A3EC0()
{
    if (ShipFoot(this)->unknown_598 == 0) {
        ShipFoot(this)->vf_480(0, 1);
        return false;
    }
    ShipFoot(this)->FUN_004DF0D0();
    return ShipFoot(this)->vf_484(0, 1);
}

// FUNCTION: GAMEMD 0x6A3F00
void __stdcall ShipLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (ShipIsSet(HeadTo))
        FUN_006A01A0(&HeadTo, mark);
}

// FUNCTION: GAMEMD 0x6A3F50 (partial: 159 vs 160 instructions; LocoPoint2D argument store scheduling differs)
bool __stdcall ShipLocomotionClass::IsMovingHere(LocoCoord to)
{
    LocoCoord head = HeadToCoord();
    if (ShipIsEmpty(head))
        return false;
    if (!unknown_60 && TrackNumber != -1) {
        int control = ShipTrackEntries_007F2A40[TrackNumber].unknown_0;
        if (control) {
            DriveTrackPoint* points = ShipTrackControls_007F2960[control].Points;
            int jump = ShipTrackControls_007F2960[control].unknown_C;
            if (jump > -1) {
                DriveTrackPoint& at_jump = points[jump];
                int facing = at_jump.Facing;
                if (TrackIndex < jump) {
                    LocoPoint2D point(at_jump.X, at_jump.Y);
                    LocoPoint2D at = FUN_006A3DB0(&point, &facing);
                    LocoCoord here = ShipFoot(this)->GetLocation();
                    if (DriveCellCoord(at.X, at.Y) == DriveCellCoord(to.X, to.Y)
                        && abs(here.Z - to.Z) <= DAT_00B07838)
                        return true;
                }
            }
        }
    }
    if (DriveCellCoord(head.X, head.Y) == DriveCellCoord(to.X, to.Y)
        && abs(head.Z - to.Z) <= DAT_00B07838)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x6A4130 (partial: retail holds the track entry as a pointer in ECX; compiled keeps a scaled offset)
bool __stdcall ShipLocomotionClass::WillJumpTracks()
{
    int dir = ShipFoot(this)->unknown_5E0;
    if (dir >= -1 && dir <= 8) {
        bool shortTrack = unknown_60;
        DriveTrackEntry* entry = &ShipTrackEntries_007F2A40[TrackNumber];
        int control = shortTrack ? entry->unknown_1 : entry->unknown_0;
        bool turning = false;
        if (dir != 8 && dir != -1 && ShipTrackFacing8(entry->unknown_4) != dir)
            turning = true;
        if (dir != -1 && turning
            && ShipTrackControls_007F2960[control].unknown_4 == TrackIndex && TrackIndex != 0) {
            char next = ShipTrackEntries_007F2A40[dir + ShipTrackFacing8(entry->unknown_4) * 8].unknown_0;
            if (next && ShipTrackControls_007F2960[next].unknown_8)
                return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6A4210
void __stdcall ShipLocomotionClass::Lock()
{
    UnLocked = false;
}

// FUNCTION: GAMEMD 0x6A4220
void __stdcall ShipLocomotionClass::Unlock()
{
    UnLocked = true;
}

// FUNCTION: GAMEMD 0x6A4230
int __stdcall ShipLocomotionClass::GetTrackNumber()
{
    return TrackNumber;
}

// FUNCTION: GAMEMD 0x6A4240
int __stdcall ShipLocomotionClass::GetTrackIndex()
{
    return TrackIndex;
}

// FUNCTION: GAMEMD 0x6A4250
int __stdcall ShipLocomotionClass::GetSpeedAccum()
{
    return SpeedAccum;
}

// FUNCTION: GAMEMD 0x006A4260
ULONG __stdcall ShipLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x006A4270
ULONG __stdcall ShipLocomotionClass::Release()
{
    return LocomotionClass::Release();
}

// FUNCTION: GAMEMD 0x6A4280
bool __stdcall ShipLocomotionClass::IsPiggybacking()
{
    return Piggybackee != 0;
}

// FUNCTION: GAMEMD 0x6A42A0
int ShipLocomotionClass::Size()
{
    return 0x70;
}

// SYNTHETIC: GAMEMD 0x6A42B0 -- compiler-generated scalar deleting destructor.
// The destructor body (releases Piggybackee) is the same code as 0x69ECF0,
// which stays scored by ComRel_0069ECF0 (match/core/multi_vtable_dtor_family_methods.cpp).
ShipLocomotionClass::~ShipLocomotionClass() {}

// SYNTHETIC: GAMEMD 0x6A4300 -- compiler-generated ILocomotion QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x6A4310 -- compiler-generated ILocomotion AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x6A4320 -- compiler-generated ILocomotion Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x6A4330 -- compiler-generated IPiggyback QI adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x6A4340 -- compiler-generated IPiggyback AddRef adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x6A4350 -- compiler-generated IPiggyback Release adjustor thunk (this -= 0x18).
