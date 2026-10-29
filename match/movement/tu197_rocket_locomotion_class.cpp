// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | original | YRpp-cross-check
//   Original translation unit TU197 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x661cb0-0x6635ef,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI.
//
// The rocket locomotor's file-scope dynamic initialisers, ascending by address.
// Each body is what cl emits for one file-scope variable's initialiser, so each
// is a plain `void __cdecl` with the assignment as its whole content.

#include "rocket_locomotion_globals.h"

#include "rocket_locomotion.h"

// GLOBAL: GAMEMD 0x7E9AD0
extern "C" const CLSID CLSID_RocketLocomotion =
    { 0xB7B49766, 0xE576, 0x11D3, { 0x9B, 0xD9, 0x00, 0x10, 0x4B, 0x97, 0x2F, 0xE8 } };

// The diagonal of a 256x256-lepton cell. The two squares are the same
// expression, so cl computes the power once and doubles it with `FADD ST,ST`.
// SYNTHETIC: GAMEMD 0x00661CB0
// GLOBAL: GAMEMD 0x00B04E20
double DAT_00B04E20 = FUN_004CAC40(pow(256.0, 2.0) + pow(256.0, 2.0));

// The cell diagonal cut into sixtieths.
// SYNTHETIC: GAMEMD 0x00661CE0
// GLOBAL: GAMEMD 0x00B04E70
double DAT_00B04E70 = DAT_00B04E20 / DAT_007F0B08;

// Its reciprocal, so the hot path multiplies instead of dividing.
// SYNTHETIC: GAMEMD 0x00661D00
// GLOBAL: GAMEMD 0x00B04E58
double DAT_00B04E58 = 1.0 / DAT_00B04E70;

// Forty-five degrees in radians.
// SYNTHETIC: GAMEMD 0x00661D20
// GLOBAL: GAMEMD 0x00B04E50
double DAT_00B04E50 = DAT_007F0B10 * 45.0;

// Sixty degrees in radians.
// SYNTHETIC: GAMEMD 0x00661D40
// GLOBAL: GAMEMD 0x00B04E28
double DAT_00B04E28 = DAT_007F0B10 * 60.0;

// Ninety degrees in radians.
// SYNTHETIC: GAMEMD 0x00661D60
// GLOBAL: GAMEMD 0x00B04E00
double DAT_00B04E00 = DAT_007F0B10 * 90.0;

// Half the cell diagonal projected through the thirty degrees between the first
// two angles, truncated to an integer number of leptons.
// SYNTHETIC: GAMEMD 0x00661D80
// GLOBAL: GAMEMD 0x00B04E78
int DAT_00B04E78 = (int)(FUN_004CAD50(DAT_00B04E00 - DAT_00B04E28) * DAT_00B04E20 * 0.5);

// The angle that projection subtends across one cell.
// SYNTHETIC: GAMEMD 0x00661DC0
// GLOBAL: GAMEMD 0x00B04E30
double DAT_00B04E30 = FUN_004CADE0(DAT_00B04E78 * 0.00390625);

// The angle twice that projection subtends across the cell diagonal.
// SYNTHETIC: GAMEMD 0x00661DF0
// GLOBAL: GAMEMD 0x00B04E48
double DAT_00B04E48 = FUN_004CADE0((DAT_00B04E78 * 2) / DAT_00B04E20);

// Four times the projection, rounded rather than truncated.
// SYNTHETIC: GAMEMD 0x00661E20
// GLOBAL: GAMEMD 0x00B04E6C
int DAT_00B04E6C = (int)(DAT_00B04E78 * 4 + 0.5);

// The word pair starts cleared.
// SYNTHETIC: GAMEMD 0x661E50
// GLOBAL: GAMEMD 0xB04E18
GgPairShort DAT_00B04E18;

// So does the triple the rocket locomotor seeds itself from.
// SYNTHETIC: GAMEMD 0x661E60
// GLOBAL: GAMEMD 0xB04E38
GgTripleInt DAT_00B04E38(0, 0, 0);

// The second triple starts at 0x80, 0x80, 0.
// SYNTHETIC: GAMEMD 0x661E80
// GLOBAL: GAMEMD 0xB04E60
GgTripleInt DAT_00B04E60(0x80, 0x80, 0);

// And the four-dword block starts cleared.
// SYNTHETIC: GAMEMD 0x661EA0
// GLOBAL: GAMEMD 0xB04E08
GgQuadInt DAT_00B04E08;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x661EC0
// PARTIAL: diff_retail 13.3%. The sentinel coordinate is copied field by field;
// retail's copy order differs and no cast is used to force it.
RocketLocomotionClass::RocketLocomotionClass()
    : State(0), Elevation(0), Armed(true),
      Flag(false), Pitch(0), unknown_58(0)
{
    Destination_.X = DAT_00B04E38.A;
    Destination_.Y = DAT_00B04E38.B;
    Destination_.Z = DAT_00B04E38.C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x661F50
bool __stdcall RocketLocomotionClass::IsMoving()
{
    return Destination_.X != DAT_00B04E38.A || Destination_.Y != DAT_00B04E38.B
        || Destination_.Z != DAT_00B04E38.C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x661F90
bool __stdcall RocketLocomotionClass::IsMovingNow()
{
    if (State >= 3 && State <= 5)
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x661FB0
LocoCoord __stdcall RocketLocomotionClass::Destination()
{
    LocoCoord c;
    c.X = Destination_.X;
    c.Y = Destination_.Y;
    c.Z = Destination_.Z;
    return c;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6622C0
// PARTIAL: diff_retail 3.7% over the 0xD4F-byte code prefix. The full retail
// span is 0xD68: an alignment byte and the six-entry jump table at 0x663010
// follow the code, and diff_retail cannot decode table bytes.
// The emitted section is 0xCC0 bytes, so this is not a full-span match. The
// state labels below are a readable interpretation of branch behavior; original
// state names and the wider Foot/Rules layouts are not claimed.
bool __stdcall RocketLocomotionClass::Process()
{
    RocketRulesView* rules = DAT_008871E0;
    RocketMissileSpec* spec = ((RocketFootView*)LinkedTo)->Type == rules->SpecA.Type ? &rules->SpecA
        : ((RocketFootView*)LinkedTo)->Type == rules->SpecC.Type ? &rules->SpecC : &rules->SpecB;

    switch (State) {
    case 1:
        unknown_44 = 0;
        Elevation = 0;
        Flag = ((RocketFootView*)LinkedTo)->Attachment != 0 && ((RocketFootView*)LinkedTo)->Attachment->inner.Check();
        if (spec->Type == DAT_008871E0->SpecC.Type) {
            if (SmokeTimer.Expired()) {
                RocketAnimView* anim = new RocketAnimView(DAT_008B4150.Items[LocoAnimTypeFindIndex(DAT_008399AC)],
                    &((RocketFootView*)LinkedTo)->Location, 2, 1, 0x600, -10, 0);
                RocketTimer restart;
                restart.TimeLeft = 0x18;
                SmokeTimer = restart;
            }
            if (Armed) {
                ((RocketFootView*)LinkedTo)->vf_124(0);
                Armed = false;
                ((RocketMapView*)&DAT_0087F7E8)->Submit(LinkedTo);
                ((RocketFootView*)LinkedTo)->vf_124(1);
            }
        } else {
            Armed = true;
        }
        if (PhaseTimer.Rate != 0) {
            int length = PhaseTimer.Rate;
            if ((double)(length - PhaseTimer.RemainingSubtract()) / (double)length != 1.0)
                break;
        }
        State = spec->Type == DAT_008871E0->SpecC.Type ? 6 : 2;
        {
            RocketRateTimer ramp;
            ramp.TimeLeft = spec->unknown_04;
            ramp.Rate = spec->unknown_04;
            PhaseTimer = ramp;
        }
        break;

    case 2:
        unknown_44 = 0;
        Elevation = 0;
        Flag = ((RocketFootView*)LinkedTo)->Attachment != 0 && ((RocketFootView*)LinkedTo)->Attachment->inner.Check();
        if (PhaseTimer.Rate != 0) {
            int length = PhaseTimer.Rate;
            if ((double)(length - PhaseTimer.RemainingSubtract()) / (double)length != 1.0) {
                double low = spec->unknown_08 * 1.5707963267948966;
                double ratio;
                if (PhaseTimer.Rate == 0)
                    ratio = 1.0;
                else
                    ratio = (double)(PhaseTimer.Rate - PhaseTimer.RemainingSubtract()) / (double)PhaseTimer.Rate;
                Pitch = low + (spec->unknown_0C * 1.5707963267948966 - low) * ratio;
                break;
            }
        }
        Pitch = spec->unknown_0C * 1.5707963267948966;
        State = 3;
        {
            RocketCellCoord cell = ((RocketFootView*)LinkedTo)->vf_2F4();
            if (cell.X == DAT_00B04E18.A && cell.Y == DAT_00B04E18.B)
                ((AircraftTrackerClass*)DAT_00887888)->Add((TechnoClass*)LinkedTo);
        }
        {
            RocketAnimView* anim = new RocketAnimView(DAT_008B4150.Items[LocoAnimTypeFindIndex(DAT_008399AC)],
                &((RocketFootView*)LinkedTo)->Location, 2, 1, 0x600, -10, 0);
        }
        {
            LocoCoord at = ((RocketFootView*)LinkedTo)->Location;
            LocoPlaySample(((RocketFootView*)LinkedTo)->vf_084()->unknown_52C, &at, 0);
        }
        break;

    case 3:
        if (!Armed) {
            ((RocketFootView*)LinkedTo)->vf_124(0);
            Armed = true;
            ((RocketMapView*)&DAT_0087F7E8)->Submit(LinkedTo);
            ((RocketFootView*)LinkedTo)->vf_124(1);
        }
        Elevation = spec->unknown_18 + Elevation;
        if ((double)((RocketFootView*)LinkedTo)->vf_084()->unknown_678 < Elevation)
            Elevation = ((RocketFootView*)LinkedTo)->vf_084()->unknown_678;
        if (((RocketFootView*)LinkedTo)->vf_1C8() >= spec->unknown_1C) {
            State = 4;
            int destX = Destination_.X;
            int destY = Destination_.Y;
            LocoCoord pos = ((RocketFootView*)LinkedTo)->vf_048();
            double dx = pos.X - destX;
            double dy = pos.Y - destY;
            unknown_58 = (int)LocoSqrt(dx * dx + dy * dy);
        }
        break;

    case 4:
        if (((RocketFootView*)LinkedTo)->vf_1C8() <= 0) {
            FUN_00663030();
            return false;
        }
        Elevation = spec->unknown_18 + Elevation;
        if ((double)((RocketFootView*)LinkedTo)->vf_084()->unknown_678 < Elevation)
            Elevation = ((RocketFootView*)LinkedTo)->vf_084()->unknown_678;
        if (spec->unknown_2C == 0 || unknown_58 == 0) {
            if (0.0f < Pitch) {
                Pitch = Pitch - spec->unknown_10;
                if (Pitch < 0.0f)
                    Pitch = 0;
            }
            LocoCoord dest = Destination_;
            LocoCoord loc = ((RocketFootView*)LinkedTo)->Location;
            int zdiff = loc.Z - dest.Z;
            LocoCoord pos = ((RocketFootView*)LinkedTo)->vf_048();
            double dx = pos.X - dest.X;
            double dy = pos.Y - dest.Y;
            double dz = pos.Z - loc.Z;
            if ((int)LocoSqrt(dx * dx + dy * dy + dz * dz) <= zdiff)
                State = 5;
        } else {
            if (FUN_006620F0(spec)) {
                FUN_00663030();
                return false;
            }
            int destY = Destination_.Y;
            int destX = Destination_.X;
            LocoCoord pos = ((RocketFootView*)LinkedTo)->vf_048();
            double dx = pos.X - destX;
            double dy = pos.Y - destY;
            int dist = (int)LocoSqrt(dx * dx + dy * dy);
            double ratio = (double)dist / (double)unknown_58;
            int ox = Destination_.X - ((RocketFootView*)LinkedTo)->Location.X;
            int oy = Destination_.Y - ((RocketFootView*)LinkedTo)->Location.Y;
            int oz = Destination_.Z - ((RocketFootView*)LinkedTo)->Location.Z;
            double inv = 1.0 - ratio;
            double h = LocoSqrt((double)(ox * ox + oy * oy));
            double angle;
            if (h <= 0.0)
                angle = -1.5707963267948966;
            else
                angle = RocketAtan(oz / h);
            Pitch = angle * inv + spec->unknown_0C * ratio * 1.5707963267948966;
        }
        {
            LocoCoord pos = ((RocketFootView*)LinkedTo)->vf_048();
            short dir[2];
            dir[0] = (short)(int)((LocoAtan2((double)pos.Y - Destination_.Y, (double)Destination_.X - pos.X)
                                   - 1.5707963267948966) * -10430.060040584269);
            ((RocketFootView*)LinkedTo)->PrimaryFacing.SetDesired(dir);
        }
        break;

    case 5:
        if (FUN_006620F0(spec)) {
            FUN_00663030();
            return false;
        }
        {
            int ox = Destination_.X - ((RocketFootView*)LinkedTo)->Location.X;
            int oy = Destination_.Y - ((RocketFootView*)LinkedTo)->Location.Y;
            int oz = Destination_.Z - ((RocketFootView*)LinkedTo)->Location.Z;
            double h = LocoSqrt((double)(oy * oy + ox * ox));
            double angle;
            if (h <= 0.0)
                angle = -1.5707963267948966;
            else
                angle = RocketAtan(oz / h);
            double delta = angle - Pitch;
            double mag = delta;
            if (delta < 0.0)
                mag = -delta;
            if (mag <= spec->unknown_10) {
                Pitch = Pitch + delta;
            } else if (0.0 <= delta) {
                Pitch = spec->unknown_10 + Pitch;
            } else {
                Pitch = Pitch - spec->unknown_10;
            }
        }
        break;

    case 6:
        Flag = ((RocketFootView*)LinkedTo)->Attachment != 0 && ((RocketFootView*)LinkedTo)->Attachment->inner.Check();
        if (SmokeTimer.Expired()) {
            RocketAnimView* anim = new RocketAnimView(DAT_008B4150.Items[LocoAnimTypeFindIndex(DAT_008399AC)],
                &((RocketFootView*)LinkedTo)->Location, 2, 1, 0x600, -10, 0);
            RocketTimer restart;
            restart.TimeLeft = 0x18;
            SmokeTimer = restart;
        }
        {
            LocoCoord loc = ((RocketFootView*)LinkedTo)->Location;
            if (PhaseTimer.Rate != 0) {
                int length = PhaseTimer.Rate;
                if ((double)(length - PhaseTimer.RemainingSubtract()) / (double)length != 1.0) {
                    loc.Z = spec->unknown_14 + loc.Z;
                    RocketCellCoord cell;
                    cell.X = (short)((loc.X + ((loc.X >> 31) & 0xFF)) >> 8);
                    cell.Y = (short)((loc.Y + ((loc.Y >> 31) & 0xFF)) >> 8);
                    if (((RocketMapView*)&DAT_0087F7E8)->FUN_00568300(&cell))
                        ((RocketFootView*)LinkedTo)->vf_1B4(&loc);
                    break;
                }
            }
        }
        Pitch = spec->unknown_0C * 1.5707963267948966;
        {
            RocketCellCoord cell = ((RocketFootView*)LinkedTo)->vf_2F4();
            if (cell.X == DAT_00B04E18.A && cell.Y == DAT_00B04E18.B) {
                LocoCoord at = ((RocketFootView*)LinkedTo)->Location;
                LocoPlaySample(((RocketFootView*)LinkedTo)->vf_084()->unknown_52C, &at, 0);
                ((AircraftTrackerClass*)DAT_00887888)->Add((TechnoClass*)LinkedTo);
            }
        }
        {
            RocketTimer reset;
            SmokeTimer = reset;
        }
        State = 3;
        break;
    }

    if (IsMovingNow() && SmokeTimer.Expired()) {
        RocketAnimView* anim = new RocketAnimView(DAT_008B4150.Items[LocoAnimTypeFindIndex(DAT_008399B0)],
            &((RocketFootView*)LinkedTo)->Location, 0, 1, 0x600, 0, 0);
        RocketTimer restart;
        restart.TimeLeft = 3;
        SmokeTimer = restart;
    }

    if (0.0 < Elevation) {
        int elev = (int)Elevation;
        LocoCoord loc = ((RocketFootView*)LinkedTo)->Location;
        int h = (int)(LocoCos(Pitch) * (double)elev);
        double a = (double)((short)((RocketFootView*)LinkedTo)->PrimaryFacing.Current().Raw - 0x3FFF) * -9.58737992428526e-5;
        int y = (int)((double)loc.Y - LocoSin(a) * (double)h);
        int x = (int)(LocoCos(a) * (double)h + (double)loc.X);
        int z = (int)(LocoSin(Pitch) * (double)elev + (double)loc.Z);
        LocoCoord p;
        p.X = x;
        p.Y = y;
        p.Z = z;
        RocketCellCoord cell;
        cell.X = (short)((x + ((x >> 31) & 0xFF)) >> 8);
        cell.Y = (short)((y + ((y >> 31) & 0xFF)) >> 8);
        if (((RocketMapView*)&DAT_0087F7E8)->FUN_00568300(&cell))
            ((RocketFootView*)LinkedTo)->vf_1B4(&p);
        RocketCellCoord now = ((RocketFootView*)LinkedTo)->vf_1B8();
        if ((now.X != ((RocketFootView*)LinkedTo)->unknown_560.X || now.Y != ((RocketFootView*)LinkedTo)->unknown_560.Y)
            && ((RocketFootView*)LinkedTo)->unknown_090) {
            CellStruct_004138C0 oldCell;
            oldCell.X = ((RocketFootView*)LinkedTo)->unknown_560.X;
            oldCell.Y = ((RocketFootView*)LinkedTo)->unknown_560.Y;
            CellStruct_004138C0 newCell;
            newCell.X = now.X;
            newCell.Y = now.Y;
            ((AircraftTracker_004138C0*)DAT_00887888)->Update((Techno_004138C0*)LinkedTo, oldCell, newCell);
        }
        if (((RocketFootView*)LinkedTo)->unknown_06C <= 0)
            FUN_00663030();
    }
    return IsMoving();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6632E0
// PARTIAL: diff_retail 30.2% over the requested 0xDA-byte span.
// The emitted section is 0xD0 bytes, so this is not a full-span match.
void __stdcall RocketLocomotionClass::MoveTo(LocoCoord to)
{
    void* type = ((RocketFootView*)LinkedTo)->Type;
    RocketRulesView* rules = DAT_008871E0;
    RocketMissileSpec* spec = type == rules->SpecA.Type ? &rules->SpecA
        : type == rules->SpecC.Type ? &rules->SpecC : &rules->SpecB;

    if (Destination_.X == DAT_00B04E38.A && Destination_.Y == DAT_00B04E38.B
        && Destination_.Z == DAT_00B04E38.C) {
        int duration;
        if (spec->unknown_00 != 0) {
            State = 1;
            duration = spec->unknown_00;
        } else {
            State = 2;
            duration = spec->unknown_04;
        }
        RocketRateTimer ramp;
        ramp.TimeLeft = duration;
        ramp.Rate = duration;
        PhaseTimer = ramp;
        Pitch = spec->unknown_08 * 1.5707963267948966;
        Destination_ = to;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6633C0
void __stdcall RocketLocomotionClass::StopMoving()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6633D0
HRESULT __stdcall RocketLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_RocketLocomotion;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x663410
HRESULT __stdcall RocketLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0)
        new (this) RocketLocomotionClass(0);
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x663460
int __stdcall RocketLocomotionClass::InWhichLayer()
{
    return 3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x663470
Matrix3D __stdcall RocketLocomotionClass::DrawMatrix(unsigned int* key)
{
    Matrix3D m;
    m.MakeIdentity();

    m.RotateZ((float)(((int)((((((RocketFootView*)LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                      * -0.19634954084936207));

    if (Pitch != 0.0f) {
        m.RotateY(-Pitch);
        RocketRulesView* rules = DAT_008871E0;
        RocketMissileSpec* spec = ((RocketFootView*)LinkedTo)->Type == rules->SpecA.Type ? &rules->SpecA
            : ((RocketFootView*)LinkedTo)->Type == rules->SpecC.Type ? &rules->SpecC : &rules->SpecB;
        float high;
        high = spec->unknown_0C * 1.5707963267948966;
        if (key != 0) {
            if ((float)(spec->unknown_08 * 1.5707963267948966) == Pitch)
                *key |= 0x20;
            else if (Pitch == high)
                *key |= 0x40;
            else
                *key = 0xFFFFFFFF;
        }
    }

    if (key != 0)
        *key |= (((((RocketFootView*)LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F;

    return m;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6635B0
int RocketLocomotionClass::Size()
{
    return sizeof(RocketLocomotionClass);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x6635C0 -- compiler-generated scalar deleting wrapper.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0B08
extern const double DAT_007F0B08 = 60.0;
// GLOBAL: GAMEMD 0x7F0B10
extern const double DAT_007F0B10 = 0.017453292519943295;
// END defined globals
