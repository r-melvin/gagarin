// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI-confirmed-inheritance
// Retail method contracts, member accesses, and callees were read from the
// pinned v1.001 image; see the associated private source-recovery evidence.
#include "../_layout/bullet_class.h"
#include "bullet_type_class.h"
#include "../_layout/techno_class.h"
#include "../_layout/house_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/matrix3d.h"
#include "../_layout/tactical.h"
#include "../movement/matrix3d_native_helpers.h"
#include "../ui/input_controls/ui_display_chain.h"
#include "../core/randomizer.h"
#include "../core/vector_class_operations.h"
#include "../renderer/color_scheme_find_methods.h"
#include <new>
#include <windows.h>

// These are engine functions, not recovered CRT implementations.
// Declaration: GAMEMD 0x4CAC40
extern "C" double __cdecl FUN_004CAC40(double value);
// Declaration: GAMEMD 0x4CACB0
extern "C" double __cdecl FUN_004CACB0(double angle);
// Declaration: GAMEMD 0x4CAD00
extern "C" double __cdecl FUN_004CAD00(double angle);
// Declaration: GAMEMD 0x4CAE30
extern "C" double __cdecl FUN_004CAE30(double y, double x);
// Declaration: GAMEMD 0x754BE0 -- ECX result, EAX same result; twelve DWORD copy.
Matrix3D FUN_00754BE0();
// Declaration: GAMEMD 0x5AF980 -- ECX result, EDX left, right on stack, RET4.
// Existing canonical returned-value declaration is included above.
// Do not introduce an explicit-result-pointer alias for this native function.
// Declaration: GAMEMD 0x4CC100 -- ECX from, EDX to, type/house on stack, RET8.
ObjectClass* __fastcall FUN_004CC100(const CoordStruct* from,
    const CoordStruct* to, BulletTypeClass* type, HouseClass* house);
// Existing canonical Tactical::AdjustForZ declaration is used (6D20E0).
// Declaration: GAMEMD 0x4AED70 -- ECX surface, EDX conversion, RET56.
void __fastcall FUN_004AED70(void* surface, void* conversion, void* shape,
    int frame, const Point2D* point, RectangleStruct* clip, int flags,
    int a8, int z, int a10, int intensity, int a12, int a13, int a14,
    Point2D offset);

// GLOBAL: GAMEMD 0x7F4890
extern int DAT_007F4890[32];
struct ScenarioClass;
// GLOBAL: GAMEMD 0xA8B230
extern ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0xA83D4C -- native reads House color-scheme index at16054.
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0x89DE18
extern DynamicVectorClass<BulletClass*> ScalableBullets;
// GLOBAL: GAMEMD 0xB0F5B8 -- actual existing storage is AbstractClass* vector.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F5B8;
// GLOBAL: GAMEMD 0xA8ED40 -- vector removed from by the Bullet destructor.
extern DynamicVectorClass<BulletClass*> DAT_00A8ED40;
// GLOBAL: GAMEMD 0xA8E9A0 -- destruction-time virtual cleanup guard.
extern bool DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0x89DDF0
extern CellStruct DAT_0089DDF0;
// GLOBAL: GAMEMD 0x89DE30
extern CoordStruct DAT_0089DE30;
// GLOBAL: GAMEMD 0x89DE64
extern int DAT_0089DE64;
// GLOBAL: GAMEMD 0x87F6C0
extern void* DAT_0087F6C0;
// GLOBAL: GAMEMD 0x87F6C4
extern void* DAT_0087F6C4;
// GLOBAL: GAMEMD 0x887314
extern void* DAT_00887314;
// GLOBAL: GAMEMD 0xABCD3C
extern int DAT_00ABCD3C;

// Pinned native readonly operands; declarations only, no invented storage.
// GLOBAL: GAMEMD 0x7E2820
extern const double DAT_007E2820;
// GLOBAL: GAMEMD 0x7E2818
extern const double DAT_007E2818;
// GLOBAL: GAMEMD 0x7E2810
extern const double DAT_007E2810;
// GLOBAL: GAMEMD 0x7E4408
extern const double DAT_007E4408;
// GLOBAL: GAMEMD 0x7E3570
extern const double DAT_007E3570;
// GLOBAL: GAMEMD 0x7E3CC0
extern const double DAT_007E3CC0;

// Native writes the low WORD, then reads a DWORD. The final &31 removes all
// influence of the uninitialized high WORD. No stack-padding assumption.
static inline unsigned int BulletDirectionIndex(double y, double x)
{
    unsigned short raw = (unsigned short)(int)((FUN_004CAE30(y, x)
        - DAT_007E2820) * DAT_007E2818);
    return ((raw >> 10) + 1 >> 1) & 31;
}

static inline CellStruct BulletCell(const CoordStruct& coord)
{
    CellStruct result;
    result.X = (short)(coord.X / 256);
    result.Y = (short)(coord.Y / 256);
    return result;
}

// Native FCOMP; FNSTSW; TEST AH,40 checks C3 without C2: unordered also
// passes the zero test. Preserve this rather than silently treating NaN as
// unequal, even though ordinary finite velocities are the expected inputs.
static inline bool BulletUnorderedOrZero(double value)
{
    return !(value < 0.0) && !(value > 0.0);
}

// FUNCTION: GAMEMD 0x466560
BulletClass::~BulletClass()
{
    AnnounceExpiredPointer(1);
    if (SpawnNextAnim)
        DAT_00B0F5B8.RemoveItem(this);
    if (DAT_00A8E9A0)
        ObjectClass::vf_53();
    Type = 0;
    Owner = 0;
    NextAnim = 0;
    DAT_00A8ED40.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x468000
int BulletClass::vf_122()
{
    int frame = 0;
    if (!Type->unknown_2A1) {
        unsigned short raw = (unsigned short)(int)((FUN_004CAE30(
            -Velocity.Y, Velocity.X) - DAT_007E2820) * DAT_007E2818);
        frame = DAT_007F4890[((raw >> 10) + 1 >> 1) & 31];
    }
    if (Type->unknown_2F4 || Type->unknown_2F5)
        frame = AnimFrame;
    return frame;
}

// FUNCTION: GAMEMD 0x468090
void BulletClass::vf_69(Point2D* point, RectangleStruct* clip)
{
    if ((*reinterpret_cast<unsigned int*>(DAT_00A8B230) & 0x1000) != 0) {
        CoordStruct where = Location;
        if (Map_0087F7E8.IsLocationFogged(&where))
            return;
    }
    if (Type->unknown_29E || SpawnNextAnim)
        return;

    if (Type->Voxel) {
        Matrix3D rotation;
        rotation.MakeIdentity();
        rotation.RotateZ((float)((int(BulletDirectionIndex(-Velocity.Y,
            Velocity.X)) - 8) * DAT_007E4408));
        double horizontal = FUN_004CAC40(Velocity.Y * Velocity.Y
                                         + Velocity.X * Velocity.X);
        rotation.RotateY((float)(-(int(BulletDirectionIndex(Velocity.Z,
            horizontal)) - 8) * DAT_007E4408));
        Matrix3D world = FUN_00754BE0();
        Matrix3D combined = FUN_005AF980(world, rotation);
        FUN_0046B0C0(&Type->MainVoxel, combined, point, clip, 0, 0x800, 1000);
        return;
    }

    void* shape = vf_27();
    if (!shape)
        return;
    int frame = vf_122();
    int height = vf_114();
    CoordStruct where = Location;
    int floorHeight = Map_0087F7E8.FUN_00578080(&where);
    if (!OnBridge) {
        where = Location;
        if ((Map_0087F7E8.FUN_00565730(where)->Flags & 0x100)
            && height >= DAT_0089DE64) {
            height -= DAT_0089DE64;
            floorHeight += DAT_0089DE64;
        }
    }
    Point2D zero(0, 0);
    if (height > 0 && Type->unknown_29A) {
        Point2D shadow(point->X, point->Y + Tactical::AdjustForZ(height));
        FUN_004AED70(DAT_00887314, DAT_0087F6C4, shape, frame, &shadow,
            clip, 0x2601, 0, -10 - Tactical::AdjustForZ(floorHeight), 0,
            1000, 0, 0, 0, zero);
    }
    void* conversion = DAT_0087F6C4;
    if (Type->unknown_2A8)
        conversion = DAT_0087F6C0;
    else if (Type->unknown_2A9) {
        int index = InheritedColor;
        if (index == -1)
            index = DAT_00A83D4C->ColorSchemeIndex;
        conversion = ColorSchemeArray.Items[index]->unknown_30C;
    }
    FUN_004AED70(DAT_00887314, conversion, shape, frame, point, clip,
        0x2E00, 0, -30 - Tactical::AdjustForZ(FUN_005F5F30()), 0,
        1000, 0, 0, 0, zero);
}

// FUNCTION: GAMEMD 0x4684E0
void BulletClass::vf_10(void* pointer, bool removed)
{
    ObjectClass::vf_10(pointer, removed); // Native direct5F5230; not dispatch.
    if (Owner == pointer)
        Owner = 0;
    if (Target == pointer) {
        CoordStruct where = Target->vf_18();
        Obj_0042D400 cell((short)(where.X / 256), (short)(where.Y / 256));
        if (!DAT_00A8E7AC && !Target->IsInAir()
            && (cell.unknown_00 != DAT_0089DDF0.X
                || cell.unknown_02 != DAT_0089DDF0.Y))
            // The hidden-result ctor writes exactly the two CellStruct words;
            // the lookup consumes that same binary-verified four-byte value.
            Target = reinterpret_cast<CellClass*>(
                Map_0087F7E8.FUN_005657A0(
                    reinterpret_cast<const CellStruct*>(&cell)));
        else
            Target = 0;
    }
    if (Type == pointer) Type = 0;
    if (WeaponType == pointer) WeaponType = 0;
    if (NextAnim == pointer) NextAnim = 0;
    // Native calls Abstract primary slot11, compares8; RTTI/base0 and
    // native Bullet slot11 returning8 justify this checked downcast.
    AbstractClass* object = static_cast<AbstractClass*>(pointer);
    if (removed && object->vf_11() == 8) {
        BulletClass* bullet = static_cast<BulletClass*>(object);
        if (bullet->Type->unknown_2EC) {
            for (int i = 0; i < ScalableBullets.Count; ++i) {
                if (ScalableBullets.Items[i] == bullet) {
                    ScalableBullets.RemoveItem(bullet);
                    break;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x468670
bool BulletClass::vf_124(const CoordStruct& source,
                         const BulletVelocity& velocity)
{
    if (!ObjectClass::vf_54(source, 0)) // Native direct5F4EC0.
        return false;
    Velocity = velocity;
    SourceCoords = source;
    LastMapCoords = BulletCell(SourceCoords);
    Map_0087F7E8.Remove(this);
    CoordStruct destination = Target->vf_22();
    TargetCoords = destination;

    if (Type->unknown_2A3 && Type->unknown_29E) {
        float dx = (float)(source.X - destination.X);
        float dy = (float)(destination.Y - source.Y);
        int dz = source.Z - destination.Z;
        float distance = (float)FUN_004CAC40((double)dx*dx
            + (double)dy*dy + (double)dz*dz);
        // ScenarioClass::unknown_0218 has asserted offset 0x218 and size 0x3F4
        // in scenario_class_methods.h; use that evidence for the call ABI.
        int draw = reinterpret_cast<Randomizer*>(reinterpret_cast<char*>(DAT_00A8B230) + 0x218)->RandomRanged(0,
            RulesInstance->unknown_1734 * 2);
        int truncatedDistance = (int)distance;
        int product = (int)((unsigned int)draw * (unsigned int)truncatedDistance);
        // WeaponTypeClass::Range is pinned at +0xB4 (and 4 bytes) in
        // weapon_type_class.h. That header's legacy BulletTypeClass view
        // conflicts with the canonical BulletTypeClass, so retain the proven
        // ABI access here without importing the competing class definition.
        int range = *reinterpret_cast<int*>(reinterpret_cast<char*>(WeaponType) + 0xB4);
        int radius = product / range;
        int direction = reinterpret_cast<Randomizer*>(reinterpret_cast<char*>(DAT_00A8B230) + 0x218)->RandomRanged(0, 0x7FFFFFFE);
        short raw = (short)(int)((direction * DAT_007E3570 * DAT_007E3CC0
                                 - DAT_007E2820) * DAT_007E2818);
        double angle = (raw - 0x3FFF) * DAT_007E2810;
        int oldZ = destination.Z;
        int newY = (int)(destination.Y - FUN_004CACB0(angle) * radius);
        int newX = (int)(FUN_004CAD00(angle) * radius + destination.X);
        destination.X = newX;
        destination.Y = newY;
        destination.Z = oldZ;
    }

    if (Type->unknown_29E) {
        HouseClass* house = Owner ? Owner->Owner : 0;
        CoordStruct intermediate = Map_0087F7E8.FUN_005880A0(
            source, destination, house);
        if (intermediate.X != DAT_0089DE30.X
            || intermediate.Y != DAT_0089DE30.Y
            || intermediate.Z != DAT_0089DE30.Z) {
            intermediate.Z = Map_0087F7E8.FUN_00578080(&intermediate);
            vf_109(intermediate);
        } else {
            ObjectClass* obstacle = FUN_004CC100(&source, &destination, Type, house);
            if (obstacle) {
                CoordStruct obstacleCoords = obstacle->vf_18();
                vf_109(obstacleCoords);
            } else {
                vf_109(destination);
            }
            vf_109(destination); // Native468986: intentional second invocation.
            Speed = 0;
            if (BulletUnorderedOrZero(Velocity.X)
                && BulletUnorderedOrZero(Velocity.Y)
                && BulletUnorderedOrZero(Velocity.Z))
                Velocity.X = 100.0;
            double scale = 1.0 / FUN_004CAC40(Velocity.X*Velocity.X
                + Velocity.Y*Velocity.Y + Velocity.Z*Velocity.Z);
            Velocity.X *= scale;
            Velocity.Y *= scale;
            Velocity.Z *= scale;
        }
    }
    int value = Type->unknown_2F0;
    if (Target && Target->vf_11() == 2)
        value = 0;
    CoordStruct where = Location;
    Data.FUN_004E1130(where, destination, value, 0x7FFFFFFF);
    if (Type->unknown_2DC > 0) {
        if (BulletUnorderedOrZero(Velocity.X)
            && BulletUnorderedOrZero(Velocity.Y)
            && BulletUnorderedOrZero(Velocity.Z))
            Velocity.X = 100.0;
        double scale = 1.0 / FUN_004CAC40(Velocity.X*Velocity.X
            + Velocity.Y*Velocity.Y + Velocity.Z*Velocity.Z);
        Velocity.X *= scale;
        Velocity.Y *= scale;
        Velocity.Z *= scale;
    }
    if (IsAlive)
        Map_0087F7E8.Submit(this);
    return true;
}

// FUNCTION: GAMEMD 0x468B90
int BulletClass::vf_30()
{
    return Type->unknown_2F7 ? 1 : 3;
}

// FUNCTION: GAMEMD 0x46AE70
HRESULT __stdcall BulletClass::Load(IStream* stream)
{
    HRESULT result = ObjectClass::Load(stream); // Native direct5F5E80.
    if (result < 0)
        return result;
    if (this != 0)
        new (this) BulletClass(AbstractNoInit());
    if (NextAnim)
        DAT_00B0F5B8.AddItem(this);
    // Qualified calls are native direct6CF240, not interface dispatch.
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&WH);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Target);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&WeaponType);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NextAnim);
    return result;
}

// FUNCTION: GAMEMD 0x46AFF0
ULONG __stdcall BulletClass::Release()
{
    --DAT_00ABCD3C;
    ULONG count = InterlockedDecrement(&RefCount);
    if (count == 0 && this)
        delete this;
    return count;
}

// FUNCTION: GAMEMD 0x46B540
int BulletClass::vf_12()
{
    return 0x160;
}

// FUNCTION: GAMEMD 0x46B550
int BulletClass::vf_11()
{
    return 8;
}
