// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI-confirmed-inheritance
// Retail method contracts, member accesses, and callees were read from the
// pinned v1.001 image; native call contracts are noted at the relevant sites.
#include "../_layout/bullet_class.h"
#include "bullet_type_class.h"
#include "weapon_type_class.h"
#include "../_layout/capture_manager_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/temporal_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/voxel_anim_class.h"
#include "../_layout/rad_site_class.h"
#include "../_layout/tag_class.h"
#include "../core/object_class_uninit_methods.h"
#include "temporal_cell.h"
#include "../_layout/techno_class.h"
#include "../_layout/house_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/warhead_type_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/matrix3d.h"
#include "../_layout/tactical.h"
#include "../movement/matrix3d_native_helpers.h"
#include "../ui/input_controls/ui_display_chain.h"
#include "../core/randomizer.h"
#include "../core/scenario_class_methods.h"
#include "../core/vec3d_layout.h"
#include "../core/vector_class_operations.h"
#include "../renderer/color_scheme_find_methods.h"
#include "airstrike_class_methods.h"
#include "parasite_class_infect_methods.h"
#include "../core/small_misc35_methods.h"
#include <new>
#include <windows.h>
#include <string.h>

// These are engine functions, not recovered CRT implementations.
// Declaration: GAMEMD 0x4CAC40
extern "C" double __cdecl FUN_004CAC40(double value);
// Declaration: GAMEMD 0x4CACB0
extern "C" double __cdecl FUN_004CACB0(double angle);
// Declaration: GAMEMD 0x4CAD00
extern "C" double __cdecl FUN_004CAD00(double angle);
struct VelocityClass;
struct Dir16;
// Declaration: GAMEMD 0x5B20F0, ABI-compatible velocity/angle views are proven
// by the native member operands; do not import that TU's legacy map view.
int FlightPathStep(CoordStruct* coord, VelocityClass* velocity,
                   const CoordStruct* target, const Dir16* turnRate,
                   char holdCourse, char isMissile, char isFast,
                   char freezePitch);
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

// GLOBAL: GAMEMD 0x7E96E0 -- CLSID requested by the native spawn path.
extern const CLSID DAT_007E96E0;
// GLOBAL: GAMEMD 0x7ED3D0 -- signed DWORD ring-bound table; extent not asserted here.
extern int DAT_007ED3D0[];
GG_STATIC_ASSERT(sizeof(DAT_007ED3D0[0]) == 4);
// GLOBAL: GAMEMD 0x7F4890
extern int DAT_007F4890[32];
// GLOBAL: GAMEMD 0x7F7C90 -- IID requested by the native spawn path.
extern const IID DAT_007F7C90;
#include "../_layout/scenario_ptr_00a8b230.h"
#include "../_layout/player_ptr_00a83d4c.h"
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
// GLOBAL: GAMEMD 0xABD490 -- four-byte CellStruct offset records; extent not asserted here.
extern CellStruct DAT_00ABD490[];
GG_STATIC_ASSERT(sizeof(DAT_00ABD490[0]) == 4);
// GLOBAL: GAMEMD 0xA8ED84
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x89DE70
extern int DAT_0089DE70;
// GLOBAL: GAMEMD 0x7E48F8
extern const double DAT_007E48F8;
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E48F0
extern const double DAT_007E48F0;
// Native writes at 0x4690FA and 0x46912B; each is a four-byte EAX store.
// GLOBAL: GAMEMD 0x87F7EC
extern int DAT_0087F7EC;
// GLOBAL: GAMEMD 0x87F7F0
extern int DAT_0087F7F0;
// GLOBAL: GAMEMD 0x87F5D8
extern Obj_00439110 DAT_0087F5D8;
// GLOBAL: GAMEMD 0x7E48E0
extern const double DAT_007E48E0;
// GLOBAL: GAMEMD 0x7E1738
extern const double DAT_007E1738;
// GLOBAL: GAMEMD 0x7E2800
extern const double DAT_007E2800;
// GLOBAL: GAMEMD 0x8B4154
extern AnimTypeClass** DAT_008B4154;
// Declaration: GAMEMD 0x48ACE0 (decl; reloc), three stack ints, RET 0xC.
int __stdcall FUN_0048ACE0(int x, int y, int z);
// Declaration: GAMEMD 0x48ACF0 (decl; reloc), no arguments, double result.
extern "C" double __cdecl FUN_0048ACF0();
// Declaration: GAMEMD 0x53AB70 (decl; reloc), no arguments at the caller.
extern "C" void __fastcall FUN_0053AB70();
// Declaration: GAMEMD 0x65FA70 (decl; reloc), type in ECX and cell on stack.
bool FUN_0065FA70(int type, TemporalCell cell);
// Declaration: GAMEMD 0x427CB0 (decl; reloc), string pointer in ECX.
int FUN_00427CB0(const char* name);
// Declaration: GAMEMD 0x6D6AD0 (decl; reloc), Point2D pointer, stdcall.
int __stdcall FUN_006D6AD0(Point2D* location);
struct BulletDir16Storage { short Raw; short Spare; };
// Address: GAMEMD 0x81AF8C
extern const char DAT_0081AF8C[];
// Address: GAMEMD 0x81AF98
extern const char DAT_0081AF98[];

// CALLEE: GAMEMD 0x4CC360 (decl; source/target in ECX/EDX; remaining
// native arguments occupy 0x18 stack bytes.
CellClass* __fastcall FUN_004CC360(CellClass* source, CellClass* target,
    CellClass* last, CoordStruct where, BulletTypeClass* type,
    HouseClass* house);
// CALLEE: GAMEMD 0x49F420 (decl; output/base in ECX/EDX, then two stack DWORDs.
CoordStruct* __fastcall FUN_0049F420(CoordStruct* output,
    const CoordStruct* base, int spread, int mode);
// CALLEE: GAMEMD 0x4690B0 (decl; Bullet receiver, coordinate pointer on stack).


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

// SYNTHETIC: readable 3x3 transform used by native BulletClass::vf_23.
static Vector3D BulletTransformDirection(const Matrix3D& matrix,
                                         const Vector3D& vector)
{
    Vector3D result;
    result.X = matrix.Row[0][0] * vector.X + matrix.Row[0][1] * vector.Y + matrix.Row[0][2] * vector.Z;
    result.Y = matrix.Row[1][0] * vector.X + matrix.Row[1][1] * vector.Y + matrix.Row[1][2] * vector.Z;
    result.Z = matrix.Row[2][0] * vector.X + matrix.Row[2][1] * vector.Y + matrix.Row[2][2] * vector.Z;
    return result;
}

// FUNCTION: GAMEMD 0x466380
BulletClass::BulletClass()
    : ObjectClass(), Data()
{
    // The native entry calls BulletData at +0xB8 before these three stores.
    Type = 0;
    Owner = 0;
    unknown_B4 = 0;

    Bright = 0;
    unknown_100 = 0;
    unknown_104 = 1;
    CourseLock = 1;
    CourseLockCounter = 0;
    Target = 0;
    Speed = 0;
    InheritedColor = -1;
    unknown_118 = 0;
    unknown_120 = 0.0;
    WH = 0;
    AnimFrame = 0;
    AnimRateCounter = 0;
    WeaponType = 0;
    LastMapCoords.X = -1;
    LastMapCoords.Y = -1;
    NextAnim = 0;
    SpawnNextAnim = 0;

    AbstractClass::vf_rtti_5();

    SourceCoords.X = 0;
    SourceCoords.Y = 0;
    SourceCoords.Z = 0;
    TargetCoords.X = 0;
    TargetCoords.Y = 0;
    TargetCoords.Z = 0;

    DAT_00A8ED40.AddItem(this);
}

// FUNCTION: GAMEMD 0x4664C0
void BulletClass::FUN_004664C0(BulletTypeClass* type, AbstractClass* target,
                                TechnoClass* owner, int health,
                                WarheadTypeClass* warhead,
                                int speed, unsigned char bright)
{
    Target = target;
    Speed = speed;
    WH = warhead;
    Bright = bright;
    Health = health;
    Type = type;
    Owner = owner;
    AnimFrame = 0;
    AnimRateCounter = Type->unknown_2F6;
    if (Type->unknown_2A9 && Owner)
        InheritedColor = Owner->Owner->ColorSchemeIndex;
    else
        InheritedColor = -1;
    DamageMultiplier = 0x100;
    NextAnim = 0;
    SpawnNextAnim = 0;
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

// FUNCTION: GAMEMD 0x4666C0
bool BulletClass::vf_73(int mode)
{
    return ObjectClass::vf_73(mode) != false;
}

// FUNCTION: GAMEMD 0x004666E0
void BulletClass::vf_23()

{

  bool nearbyWithin127;
  char cVar3;
  short sVar4;
  int iVar5;
  short sVar16;
  short sVar19;
  short sVar21;
  long double fVar24;
  int targetDistance;
  bool ownerRelationAccepted;
  bool targetResolutionGate;
  unsigned char impactCandidate; // end/impact path has been selected
  int resolutionMode; // 0: continue; 1: resolve at final point; 2: alternate resolution
  int local_18c;
  int local_188;
  int local_184;
  int local_16c;
  int local_168;
  int local_164;
  double local_160;
  int effectMode;
  double local_148;
  double local_140;
  double local_138;
  double local_120;
  double local_118;
  double local_110;
  
  ObjectClass::vf_23();
  if (!IsAlive) {
    return;
  }
  if (SpawnNextAnim) {
    if (NextAnim != 0) {
      return;
    }
    DAT_00B0F5B8.RemoveItem(this);
    SpawnNextAnim = false;
    FUN_00468D80(0);
    vf_62();
    return;
  }

  targetResolutionGate = false;
  impactCandidate = Type->unknown_29C && !IsFallingDown;
  if (Type->unknown_2F4 || Type->unknown_2F5) {
    --AnimRateCounter;
    if (AnimRateCounter == 0) {
      const unsigned char nextFrame = static_cast<unsigned char>(AnimFrame + 1);
      AnimRateCounter = Type->unknown_2F6;
      AnimFrame = nextFrame;
      if (nextFrame > Type->unknown_2F5) {
        AnimFrame = Type->unknown_2F4;
      }
    }
  }

  local_18c = Location.X;
  local_188 = Location.Y;
  local_184 = Location.Z;

  // The two native timing modes converge at the same 0x421EA0 constructor.
  // Keep allocation failure explicit and invoke the constructor only on success.
  if (Type->unknown_2D8 != 0) {
    const int animationPeriod = Type->ScaledSpawnDelay != 0
        ? Type->ScaledSpawnDelay : Type->unknown_2E4;
    if (DAT_00A8ED84 % animationPeriod == 0) {
      void* storage = ::operator new(sizeof(AnimClass));
      if (storage != 0) {
        CoordStruct position;
        position.X = local_18c;
        position.Y = local_188;
        position.Z = local_184;
        new (storage) AnimClass(Type->unknown_2D8, position, 1, 1, 0x600, 0, false);
      }
    }
  }
  resolutionMode = 0;
  if (Type->unknown_2DC > 0) {
    local_110 = Velocity.Z;
    local_120 = Velocity.X;
    local_148 = Velocity.X;
    local_118 = Velocity.Y;
    local_140 = Velocity.Y;
    local_138 = local_110;
    fVar24 = FUN_004CAC40(local_110 * local_110 +
                            local_148 * local_148 + local_140 * local_140);
    if (fVar24 < (long double)8.0) {
      resolutionMode = 1;
    }

    // Course-lock hysteresis and guided-flight speed normalization.  The
    // branch/field widths here follow native 0x466925..0x466B0B: Type+0x2E0
    // is a dword threshold, CourseLockCounter is incremented only below it,
    // Speed is the dword at Bullet+0x110, and Type+0x2D0 is a dword delta.
    if (Type->unknown_2E0 == 0) {
      if (Speed >= 0x28 ||
          static_cast<double>(Speed) <= static_cast<double>(fVar24) + DAT_007E1738) {
        CourseLock = 0;
      }
    } else if (CourseLockCounter < Type->unknown_2E0) {
      ++CourseLockCounter;
      if (CourseLockCounter >= Type->unknown_2E0) {
        CourseLock = 0;
      }
    }

    int speedAdjustment = Type->unknown_2D0;
    if (CourseLock && Type->unknown_2E0 == 0) {
      // Native ANDs the timer with 0x80000001, then reduces it to 1 for an
      // even low bit and 0 for an odd low bit. The sign-bit steps are only
      // the compiler's branch-free boolean conversion.
      speedAdjustment = (DAT_00A8ED84 & 1) == 0 ? 1 : 0;
    }

    double adjustedMagnitude = static_cast<double>(fVar24);
    if (static_cast<double>(Speed) < adjustedMagnitude) {
      adjustedMagnitude -= static_cast<double>(speedAdjustment / 2);
      if (adjustedMagnitude < DAT_007E2800) {
        adjustedMagnitude = 0.0;
      }
    } else if (static_cast<double>(Speed) > adjustedMagnitude) {
      adjustedMagnitude += static_cast<double>(speedAdjustment);
      if (adjustedMagnitude > static_cast<double>(Speed)) {
        adjustedMagnitude = static_cast<double>(Speed);
      }
    }

    // The three native FCOMP checks accept either signed zero.  If all
    // components are zero, the original body seeds X to 100 before dividing
    // by its norm; this avoids a zero denominator and is observable state.
    if (Velocity.X == DAT_007E2800 && Velocity.Y == DAT_007E2800 &&
        Velocity.Z == DAT_007E2800) {
      Velocity.X = 100.0;
    }
    const double velocityMagnitude = FUN_004CAC40(
        Velocity.X * Velocity.X + Velocity.Y * Velocity.Y +
        Velocity.Z * Velocity.Z);
    const double velocityScale = adjustedMagnitude / velocityMagnitude;
    Velocity.X *= velocityScale;
    Velocity.Y *= velocityScale;
    Velocity.Z *= velocityScale;

    local_148 = (double)local_18c;
    local_140 = (double)local_188;
    local_138 = (double)local_184;
      const int secondaryValue = vf_rtti_4();
      const int animationPhase = (secondaryValue + DAT_00A8ED84) % 15;
      const double phaseAngle = animationPhase * DAT_007E48F8 * DAT_007E3CC0;
      const double phaseSin = FUN_004CACB0(phaseAngle);
      const double phaseScale = RulesInstance->MissileROTVar;
      const int phaseDirection = static_cast<int>(
          (phaseSin * phaseScale + phaseScale + DAT_007E1718) * Type->unknown_2DC);

      CoordStruct targetPosition;
      if (Target != 0) {
        targetPosition = Target->vf_22();
        if (Target->Flags.unknown_14_1) {
          targetPosition = static_cast<ObjectClass*>(Target)->vf_41();
        }
      } else {
        targetPosition = DAT_0089DE30;
      }

      const CoordStruct currentPosition = vf_18();
      CoordStruct targetDelta;
      targetDelta.FUN_0041C230(
          currentPosition.X - targetPosition.X,
          currentPosition.Y - targetPosition.Y,
          currentPosition.Z - targetPosition.Z);
      const double targetDistance = FUN_004CAC40(
          static_cast<double>(targetDelta.X) * targetDelta.X +
          static_cast<double>(targetDelta.Y) * targetDelta.Y +
          static_cast<double>(targetDelta.Z) * targetDelta.Z);
      int encodedDirection = phaseDirection;
      const int integerDistance = static_cast<int>(targetDistance);
      if (integerDistance < 0x100) {
        encodedDirection = static_cast<int>(integerDistance * DAT_007E48F0);
      }

      const bool targetHasClassTwo = Target != 0 && Target->vf_11() == 2;
      BulletDir16Storage turnRate;
      turnRate.Raw = static_cast<short>(
          CourseLock ? 0U : static_cast<unsigned int>(encodedDirection) << 8);

      CoordStruct flightPosition;
      flightPosition.X = local_18c;
      flightPosition.Y = local_188;
      flightPosition.Z = local_184;
      local_16c = flightPosition.X;
      local_168 = flightPosition.Y;
      local_164 = flightPosition.Z;
      BulletVelocity flightVelocity = Velocity;
      const int flightDistance = FlightPathStep(&flightPosition,
          reinterpret_cast<VelocityClass*>(&flightVelocity), &targetPosition,
          reinterpret_cast<const Dir16*>(&turnRate),
          targetHasClassTwo, Type->unknown_294, Type->unknown_299,
          Type->unknown_29D);
      Velocity = flightVelocity;
      local_18c = flightPosition.X;
      local_188 = flightPosition.Y;
      local_184 = flightPosition.Z;
      local_160 = static_cast<double>(flightDistance);
      CellClass* flightCell = Map_0087F7E8.FUN_00565730(flightPosition);

      const double currentVelocityLength = FUN_004CAC40(
          Velocity.X * Velocity.X + Velocity.Y * Velocity.Y +
          Velocity.Z * Velocity.Z);
      if (local_160 <= currentVelocityLength * 0.5 || vf_114() < 1) {
        impactCandidate = true;
        resolutionMode = 1;
        if (vf_114() > 0 && Type->unknown_294 == 0 &&
            (targetPosition.X != DAT_0089DE30.X ||
             targetPosition.Y != DAT_0089DE30.Y ||
             targetPosition.Z != DAT_0089DE30.Z)) {
          flightPosition = targetPosition;
          local_18c = flightPosition.X;
          local_188 = flightPosition.Y;
          local_184 = flightPosition.Z;
        }
      }
      if (targetPosition.X == DAT_0089DE30.X &&
          targetPosition.Y == DAT_0089DE30.Y &&
          targetPosition.Z == DAT_0089DE30.Z &&
          vf_114() >= RulesInstance->MissileSafetyAltitude) {
        impactCandidate = true;
        resolutionMode = 1;
      }

      CoordStruct originalDelta;
      originalDelta.FUN_0041C230(
          local_16c - targetPosition.X,
          local_168 - targetPosition.Y,
          local_164 - targetPosition.Z);
      const int originalDistance = static_cast<int>(FUN_004CAC40(
          static_cast<double>(originalDelta.X) * originalDelta.X +
          static_cast<double>(originalDelta.Y) * originalDelta.Y +
          static_cast<double>(originalDelta.Z) * originalDelta.Z));
      CoordStruct updatedDelta;
      updatedDelta.FUN_0041C230(
          local_18c - targetPosition.X,
          local_188 - targetPosition.Y,
          local_184 - targetPosition.Z);
      const int updatedDistance = static_cast<int>(FUN_004CAC40(
          static_cast<double>(updatedDelta.X) * updatedDelta.X +
          static_cast<double>(updatedDelta.Y) * updatedDelta.Y +
          static_cast<double>(updatedDelta.Z) * updatedDelta.Z));
      const int distanceProgress = originalDistance - updatedDistance;
      if (!CourseLock) {
        if (CourseLockCounter < 0x3C) {
          ++CourseLockCounter;
          unknown_120 += distanceProgress;
        } else {
          unknown_120 = unknown_120 * 0.9833333333333333 + distanceProgress;
          if (unknown_120 >= 0.0 && unknown_120 < 60.0 &&
              Type->unknown_294 == 0 && Type->unknown_299 == 0) {
            impactCandidate = true;
            resolutionMode = 1;
            goto LAB_00467b7a;
          }
        }
      }

      if (resolutionMode == 0) {
        CoordStruct previousPosition;
        previousPosition.X = local_16c;
        previousPosition.Y = local_168;
        previousPosition.Z = local_164;
        bool bridgeOnEitherSide = (flightCell->Flags & 0x100) != 0;
        if (!bridgeOnEitherSide) {
          CellClass* previousCell =
              Map_0087F7E8.FUN_00565730(previousPosition);
          bridgeOnEitherSide = (previousCell->Flags & 0x100) != 0;
        }
        if (bridgeOnEitherSide) {
          const int floorHeight =
              Map_0087F7E8.FUN_00578080(&flightPosition) + DAT_0089DE64;
          const int previousZ = previousPosition.Z;
          const int updatedZ = flightPosition.Z;
          if ((updatedZ > floorHeight && previousZ < floorHeight) ||
              (updatedZ <= floorHeight && previousZ > floorHeight)) {
            resolutionMode = 1;
            impactCandidate = true;
            flightPosition.Z = floorHeight;
            local_184 = floorHeight;
          }
        }
      }
    }
    else {
      if (Type->unknown_2C0 == 0) {
        const double gravity = Type->unknown_295
            ? FUN_0048ACF0() : static_cast<double>(RulesInstance->Gravity);
        const double stepX = Velocity.X;
        const double stepY = Velocity.Y;
        const double stepZ = Velocity.Z - gravity;
        local_120 = stepX;
        local_118 = stepY;
        local_110 = stepZ;
        const double speedSquared = Velocity.X * Velocity.X +
                                    Velocity.Y * Velocity.Y +
                                    Velocity.Z * Velocity.Z;
        const double speedLength = FUN_004CAC40(speedSquared);
        if (speedLength < DAT_007E48E0) {
          resolutionMode = 1;
        }

        // Native initializes the pre-step point as three doubles at ESP+68,
        // +70, and +78. The delta vector is at +90/+98/+A0; its Z term has
        // gravity removed before FUN_0046B960 adds it into the point.
        CoordStruct previousPosition;
        previousPosition.FUN_0041C230(Location.X, Location.Y, Location.Z);
        double positionX = static_cast<double>(previousPosition.X);
        double positionY = static_cast<double>(previousPosition.Y);
        double positionZ = static_cast<double>(previousPosition.Z);
        positionX += stepX;
        positionY += stepY;
        positionZ += stepZ;
        CoordStruct updatedPosition;
        updatedPosition.FUN_00437090(static_cast<int>(positionX),
                                     static_cast<int>(positionY),
                                     static_cast<int>(positionZ));

        const int baseFloor = Map_0087F7E8.FUN_00578080(&updatedPosition);
        const int bridgeHeight = baseFloor + DAT_0089DE64;
        CellClass* updatedCell =
            Map_0087F7E8.FUN_00565730(updatedPosition);
        bool bridgeOnEitherSide = (updatedCell->Flags & 0x100) != 0;
        if (!bridgeOnEitherSide) {
          CellClass* priorCell =
              Map_0087F7E8.FUN_00565730(previousPosition);
          bridgeOnEitherSide = (priorCell->Flags & 0x100) != 0;
        }
        bool crossedUp = false;
        bool crossedDown = false;
        if (bridgeOnEitherSide) {
          crossedUp = previousPosition.Z < bridgeHeight &&
                      bridgeHeight <= updatedPosition.Z;
          crossedDown = updatedPosition.Z < bridgeHeight &&
                        previousPosition.Z >= bridgeHeight;
        }

        bool buildingCollision = false;
        BuildingClass* collisionBuilding = 0;
        if (!crossedUp && !crossedDown &&
            static_cast<double>(baseFloor) <= Type->unknown_2C8 &&
            Type->unknown_2C8 - 150.0 < static_cast<double>(baseFloor)) {
          collisionBuilding = updatedCell->GetBuilding();
          bool connectsToOverlay = false;
          if (collisionBuilding == 0) {
            connectsToOverlay = updatedCell->ConnectsToOverlay(-1, -1);
          }
          if ((collisionBuilding != 0 || connectsToOverlay) &&
              collisionBuilding != 0) {
            buildingCollision = true;
            if (collisionBuilding == Owner ||
                (collisionBuilding->Type->bools_16A4[0x16BF - 0x16A4] &&
                 collisionBuilding->LaserFenceFrame > 7)) {
              buildingCollision = false;
            }
            if (collisionBuilding->vf_32()) {
              buildingCollision = false;
            }
            if (Owner != 0 && Owner->Owner != 0 &&
                Owner->Owner->IsAlliedWith(collisionBuilding->Owner)) {
              buildingCollision = false;
            }
          }
        }

        if (Type->unknown_2C8 < static_cast<double>(baseFloor) ||
            crossedUp || crossedDown || buildingCollision) {
          if (Owner == 0) {
            if (crossedDown) {
              positionZ = static_cast<double>(bridgeHeight);
            } else if (crossedUp &&
                       static_cast<double>(bridgeHeight - 100) < positionZ) {
              positionZ = static_cast<double>(baseFloor);
            }

            Point2D mapPosition(updatedPosition.X, updatedPosition.Y);
            const int slopeIndex = FUN_006D6AD0(&mapPosition);
            const Matrix3D terrainTransform = FUN_007559B0(slopeIndex);
            const Matrix3D inverseTerrainTransform =
                Matrix3D::TransposeMatrix(terrainTransform);
            Vector3D velocityDirection(static_cast<float>(stepX),
                                       -static_cast<float>(stepY),
                                       static_cast<float>(stepZ));
            Vector3D transformed = BulletTransformDirection(
                inverseTerrainTransform, velocityDirection);
            const float terrainScale = static_cast<float>(Type->unknown_2C8);
            transformed.X *= terrainScale;
            transformed.Y *= terrainScale;
            transformed.Z *= -terrainScale;
            const Vector3D adjustedDirection = BulletTransformDirection(
                terrainTransform, transformed);
            local_120 = adjustedDirection.X;
            local_118 = -adjustedDirection.Y;
            local_110 = adjustedDirection.Z;
          }
          resolutionMode = 1;
          impactCandidate = true;
        }

        local_18c = static_cast<int>(positionX);
        local_188 = static_cast<int>(positionY);
        local_184 = static_cast<int>(positionZ);
      } else {
      const double velocityLength = FUN_004CAC40(
          Velocity.X * Velocity.X + Velocity.Y * Velocity.Y +
          Velocity.Z * Velocity.Z);
      int measuredSpeed = static_cast<int>(velocityLength);
      if (measuredSpeed < Speed) {
        const int adjustedSpeed = Type->unknown_2D0 + measuredSpeed;
        local_160 = static_cast<double>(adjustedSpeed);
        if (Velocity.X == 0.0 && Velocity.Y == 0.0 && Velocity.Z == 0.0) {
          Velocity.X = 100.0;
        }
        const double nonzeroLength = FUN_004CAC40(
            Velocity.X * Velocity.X + Velocity.Y * Velocity.Y +
            Velocity.Z * Velocity.Z);
        const double scale = local_160 / nonzeroLength;
        Velocity.X *= scale;
        Velocity.Y *= scale;
        Velocity.Z *= scale;
      }

      const int stepX = static_cast<int>(Velocity.X);
      const int stepY = static_cast<int>(Velocity.Y);
      const int stepZ = static_cast<int>(Velocity.Z);
      const int oldX = local_18c;
      const int oldY = local_188;
      const int oldZ = local_184;
      local_16c = oldX;
      local_168 = oldY;
      local_164 = oldZ;
      local_18c = oldX + stepX;
      local_188 = oldY + stepY;
      local_184 = oldZ + stepZ;

      if (Type->unknown_2BC < local_184) {
        resolutionMode = 1;
        impactCandidate = 1;
      } else {
        if (vf_114() < 0) {
          resolutionMode = 1;
          impactCandidate = 1;
        } else {
          CoordStruct nextPosition;
          nextPosition.X = local_18c;
          nextPosition.Y = local_188;
          nextPosition.Z = local_184;
          CoordStruct priorPosition;
          priorPosition.X = local_16c;
          priorPosition.Y = local_168;
          priorPosition.Z = local_164;
          const int floorHeight = Map_0087F7E8.FUN_00578080(&nextPosition) +
                                  DAT_0089DE64;
          CellClass* nextCell = Map_0087F7E8.FUN_00565730(nextPosition);
          bool bridgeOnEitherSide = (nextCell->Flags & 0x100) != 0;
          if (!bridgeOnEitherSide) {
            CellClass* priorCell =
                Map_0087F7E8.FUN_00565730(priorPosition);
            bridgeOnEitherSide = (priorCell->Flags & 0x100) != 0;
          }
          if (bridgeOnEitherSide) {
            if (nextPosition.Z <= floorHeight &&
                floorHeight < priorPosition.Z) {
              resolutionMode = 1;
              impactCandidate = 1;
              local_184 = floorHeight;
            } else if (priorPosition.Z < floorHeight &&
                       floorHeight < nextPosition.Z) {
              resolutionMode = 1;
              impactCandidate = 1;
              local_184 = floorHeight;
            }
          }
        }
      }
    }
    }
    sVar16 = static_cast<short>(
        (local_18c + ((local_18c >> 31) & 0xFF)) >> 8);
    sVar21 = static_cast<short>(
        (local_188 + ((local_188 >> 31) & 0xFF)) >> 8);
    CellStruct bulletCellCoords;
    bulletCellCoords.X = sVar16;
    bulletCellCoords.Y = sVar21;
    sVar19 = static_cast<short>(
        (TargetCoords.X + ((TargetCoords.X >> 31) & 0xFF)) >> 8);
    sVar4 = static_cast<short>(
        (TargetCoords.Y + ((TargetCoords.Y >> 31) & 0xFF)) >> 8);
    CellStruct targetCellCoords;
    targetCellCoords.X = sVar19;
    targetCellCoords.Y = sVar4;
    if ((((sVar16 == sVar19) && (sVar21 == sVar4)) && (Type->unknown_2C0 == '\0')) &&
       (iVar5 = vf_114(), iVar5 < DAT_0089DE70 * 2)) {
LAB_00467879:
      resolutionMode = 1;
      impactCandidate = 1;
      targetResolutionGate = true;
    }
    else {
      CellClass* bulletCell = reinterpret_cast<CellClass*>(
          Map_0087F7E8.FUN_005657A0(&bulletCellCoords));
      CellClass* targetCell = reinterpret_cast<CellClass*>(
          Map_0087F7E8.FUN_005657A0(&targetCellCoords));
      BuildingClass* bulletCellBuilding = bulletCell->GetBuilding();
      BuildingClass* targetCellBuilding = targetCell->GetBuilding();
      if ((bulletCellBuilding != 0 && Type->unknown_2C0 == '\0') &&
         (bulletCellBuilding == targetCellBuilding &&
          (iVar5 = vf_114(), iVar5 < DAT_0089DE70 * 2))
         ) goto LAB_00467879;
      CoordStruct searchPosition;
      searchPosition.X = local_18c;
      searchPosition.Y = local_188;
      searchPosition.Z = local_184;
      Point2D searchOffset(0, 0);
      CellClass* searchCell = Map_0087F7E8.FUN_00565730(searchPosition);
      ObjectClass* nearbyObject =
          searchCell->FindTechnoNearestTo(&searchOffset, false, 0);
      targetResolutionGate = Owner != 0 && nearbyObject == Owner;
      if (nearbyObject == 0 || Owner == 0) {
LAB_00467960:
        ownerRelationAccepted = '\0';
      }
      else {
        TechnoClass* nearbyTechno = static_cast<TechnoClass*>(nearbyObject);
        cVar3 = nearbyTechno->Owner->FUN_004F9A90(nearbyTechno);
        ownerRelationAccepted = '\x01';
        if (cVar3 == '\0') goto LAB_00467960;
      }
      if (nearbyObject == 0) {
LAB_004679d5:
        nearbyWithin127 = false;
      }
      else {
        // Native loads all three dwords at occupant+0x9C/+0xA0/+0xA4;
        // these are the canonical ObjectClass::Location fields.
        local_16c = local_18c - nearbyObject->Location.X;
        local_168 = local_188 - nearbyObject->Location.Y;
        local_164 = local_184 - nearbyObject->Location.Z;
        iVar5 = static_cast<int>(FUN_004CAC40(
            (double)local_168 * (double)local_168 +
            (double)local_164 * (double)local_164 +
            (double)local_16c * (double)local_16c));
        if (0x7f < iVar5) goto LAB_004679d5;
        nearbyWithin127 = true;
      }
      if ((!targetResolutionGate) && (ownerRelationAccepted == '\0') && nearbyWithin127) {
        resolutionMode = 1;
        impactCandidate = 1;
        if (Type->unknown_2A2 == '\0') {
          local_18c = nearbyObject->Location.X;
          local_188 = nearbyObject->Location.Y;
          local_184 = nearbyObject->Location.Z;
        }
        goto LAB_00467b7a;
      }
      CoordStruct candidatePosition;
      candidatePosition.X = local_18c;
      candidatePosition.Y = local_188;
      candidatePosition.Z = local_184;
      cVar3 = Map_0087F7E8.FUN_00568350(candidatePosition);
      if (cVar3 == '\0') {
        resolutionMode = 2;
        impactCandidate = 1;
        local_18c = Location.X;
        local_188 = Location.Y;
        local_184 = Location.Z;
        goto LAB_00467b7a;
      }
      if (Type->unknown_2C0 == '\0') {
        Velocity.X = local_120;
        Velocity.Y = local_118;
        Velocity.Z = local_110;
      }
      fVar24 = FUN_004CAC40(Velocity.X * Velocity.X +
                            Velocity.Y * Velocity.Y +
                            Velocity.Z * Velocity.Z);
      if (((long double)10.0 <= fVar24) || (iVar5 = vf_114(), 9 < iVar5))
        goto LAB_00467b7a;
      resolutionMode = 1;
      impactCandidate = 1;
    }

LAB_00467b7a:
  if (resolutionMode == 2) {
    vf_73(2);
  }
  else {
    vf_73(2);
    CoordStruct resolutionCoords;
    resolutionCoords.X = local_18c;
    resolutionCoords.Y = local_188;
    resolutionCoords.Z = local_184;
    vf_109(resolutionCoords);
    if (!impactCandidate) {
      CoordStruct sourceCoords = Location;
      cVar3 = FUN_00468BB0(&sourceCoords);
      vf_109(sourceCoords);
      if (cVar3 != '\0') goto LAB_00467bf0;
    }
    else {
LAB_00467bf0:
      iVar5 = vf_114();
      if (iVar5 < 0) {
        vf_115(0);
      }
    }
    if ((Type->unknown_2DC < 1) && (Type->unknown_2A0 == '\0')) {
      iVar5 = 0;
    }
    else {
      CoordStruct effectPosition;
      effectPosition.X = local_18c;
      effectPosition.Y = local_188;
      effectPosition.Z = local_184;
      iVar5 = Data.FUN_004E11F0(effectPosition);
    }
    effectMode = iVar5;
    if (Owner != 0 && Owner->vf_33()->bools_D94[0] && iVar5 == 2) {
      iVar5 = 1;
      effectMode = 1;
    }
    if ((!impactCandidate) && ((Type->unknown_29C != '\0' || (iVar5 == 0)))) {
      if ((Type->unknown_2A6 != '\0') && (5 < Health)) {
        Health = Health + -1;
      }
      goto LAB_00467fba;
    }
    if (Target != 0 &&
       (((effectMode == 1 || targetResolutionGate) &&
        ((Type->unknown_294 == '\0' && (Type->unknown_2A2 == '\0'))))))
    {
      CoordStruct targetCenter = Target->vf_22();
      const int currentX = local_18c;
      const int currentY = local_188;
      const int currentZ = local_184;
      const int deltaX = currentX - targetCenter.X;
      const int deltaY = currentY - targetCenter.Y;
      const int midpointZ = (targetCenter.Z + currentZ) / 2;
      const int deltaZ = midpointZ - targetCenter.Z;
      targetDistance = static_cast<int>(FUN_004CAC40(
          (double)deltaX * (double)deltaX +
          (double)deltaY * (double)deltaY +
          (double)deltaZ * (double)deltaZ));
      if (targetResolutionGate) {
        targetDistance = targetDistance / 3;
      }
      if (effectMode != 1) {
        fVar24 = FUN_004CAC40(Velocity.X * Velocity.X +
                              Velocity.Y * Velocity.Y +
                              Velocity.Z * Velocity.Z);
        if ((long double)128.0 <= fVar24 + fVar24) {
          fVar24 = FUN_004CAC40(Velocity.X * Velocity.X +
                                Velocity.Y * Velocity.Y +
                                Velocity.Z * Velocity.Z);
          fVar24 = fVar24 + fVar24;
        }
        else {
          fVar24 = (long double)128.0;
        }
        if (fVar24 < (long double)targetDistance) goto LAB_00467e53;
      }
      CoordStruct destination = Target->vf_18();
      vf_109(destination);
    }
LAB_00467e53:
    // At 0x467E53 ECX is BulletClass::WH (+0x128), and 0x410A40 compares
    // the receiver's bytes at +0x24 with the supplied string. For a
    // WarheadTypeClass that is AbstractTypeClass::ID; 0x0081AF98 is the
    // separate NUKE string following the adjacent NUKEBALL string.
    if (strcmp(static_cast<WarheadTypeClass*>(WH)->ID, DAT_0081AF98) == 0) {
      iVar5 = vf_114();
      if (iVar5 < 0) {
        vf_115(0);
      }
      FUN_0053AB70();
      const CellStruct nukeCell = vf_110();
      TemporalCell packedCell;
      packedCell.X = nukeCell.X;
      packedCell.Y = nukeCell.Y;
      FUN_0065FA70(0xD, packedCell);
      int animationIndex = FUN_00427CB0(DAT_0081AF8C);
      if (animationIndex != -1 && DAT_008B4154[animationIndex] != 0) {
        // Native 0x467ED0..0x467F36: allocate first, then copy Location,
        // call FUN_0048ACE0, and invoke the constructor. A failed allocation
        // skips all of those steps and stores null in NextAnim.
        void* animationStorage = ::operator new(sizeof(AnimClass));
        AnimClass* nextAnimation = 0;
        if (animationStorage != 0) {
          CoordStruct animationLocation = Location;
          int forceZ = FUN_0048ACE0(animationLocation.X,
                                    animationLocation.Y,
                                    animationLocation.Z);
          AnimTypeClass* animationType = DAT_008B4154[animationIndex];
          nextAnimation = new (animationStorage) AnimClass(
              animationType, animationLocation, 0, 1, 0x2600, forceZ, false);
        }
        NextAnim = nextAnimation;
        iVar5 = (int)nextAnimation;
        SpawnNextAnim = true;
        DAT_00B0F5B8.AddItem(this);
        goto LAB_00467fba;
      }
    }
    FUN_00468D80(impactCandidate);
  }
  vf_62();
LAB_00467fba:
  // Native 0x467FBA..0x467FE8 converts the final X/Y lepton coordinates
  // from [ESP+0x24] and [ESP+0x28] to signed cell shorts using floor division.
  LastMapCoords.X = static_cast<short>(
      (local_18c + ((local_18c >> 31) & 0xFF)) >> 8);
  LastMapCoords.Y = static_cast<short>(
      (local_188 + ((local_188 >> 31) & 0xFF)) >> 8);
  return;
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
            RulesInstance->BallisticScatter * 2);
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

// FUNCTION: GAMEMD 0x468BB0
bool BulletClass::FUN_00468BB0(CoordStruct* where)
{
    *where = Location;

    CellClass* currentCell = Map_0087F7E8.FUN_00565730(*where);
    if (Type->unknown_296 || Type->unknown_298) {
        CellClass* sourceCell = Map_0087F7E8.FUN_00565730(SourceCoords);
        CellClass* targetCell = Map_0087F7E8.FUN_00565730(TargetCoords);
        // Native 0x5657A0 returns the actual zero-offset CellClass object;
        // this UI declaration retains its legacy DisplayScCellObject view.
        CellClass* lastCell = reinterpret_cast<CellClass*>(
            Map_0087F7E8.FUN_005657A0(&LastMapCoords));
        HouseClass* owner = Owner != 0 ? Owner->Owner : 0;

        // ECX/EDX carry sourceCell/targetCell; stack carries lastCell,
        // CoordStruct (three dwords), Type, and owner. EAX is a cell pointer
        // or null; the caller tests it as a boolean.
        if (FUN_004CC360(sourceCell, targetCell, lastCell, *where, Type, owner) != 0) {
            return true;
        }
    }

    if (vf_114() <= -4 * DAT_0089DE70) {
        return true;
    }

    if (Target != 0 && Type->unknown_2A3) {
        const int sourceZ = Location.Z;
        CoordStruct targetCoords = Target->vf_22();
        if (sourceZ < targetCoords.Z && vf_114() < 0) {
            return true;
        }
    }

    if (Type->unknown_29D && currentCell->IsOnFloor()) {
        return true;
    }

    if (Type->unknown_2A4 && Target != 0 && Target->IsInAir() &&
        this->FUN_005F6360(Target) < 0x80) {
        return true;
    }

    return false;
}


// FUNCTION: GAMEMD 0x468D80
void BulletClass::FUN_00468D80(int mode)
{
    CoordStruct effectPosition = Location;
    AbstractClass* airborneTarget = 0;

    if (Target != 0 && Target->IsInAir())
        airborneTarget = Target;
    ObjectClass* airborneObject = static_cast<ObjectClass*>(airborneTarget);

    // Native branches directly to final emission when Type+0x2A2 is set.
    if (!Type->unknown_2A2) {
        if (Target != 0) {
            const CoordStruct targetCoords = Target->vf_18();
            CoordStruct difference;
            difference.FUN_0041C230(Location.X - targetCoords.X,
                                    Location.Y - targetCoords.Y,
                                    Location.Z - targetCoords.Z);
            const double squaredDistance =
                static_cast<double>(difference.X) * difference.X +
                static_cast<double>(difference.Z) * difference.Z +
                static_cast<double>(difference.Y) * difference.Y;
            // Native 0x468E4F returns sqrt in ST(0), immediately consumed by
            // the __ftol call at 0x468E57.
            const int distance = static_cast<int>(FUN_004CAC40(squaredDistance));

            if (distance < 0x20 && !Type->unknown_294 && !Type->unknown_2A2)
                effectPosition = Target->vf_18();
        }

        WarheadTypeClass* warhead = static_cast<WarheadTypeClass*>(WH);
        if (!warhead->EMEffect && !Type->unknown_294 &&
            static_cast<unsigned char>(mode) == 0 && !Type->unknown_29B &&
            Type->unknown_2DC <= 0 &&
            (Data.unknown_18 != DAT_0089DE30.X ||
             Data.unknown_1C != DAT_0089DE30.Y ||
             Data.unknown_20 != DAT_0089DE30.Z)) {
            effectPosition.X = Data.unknown_18;
            effectPosition.Y = Data.unknown_1C;
            effectPosition.Z = Data.unknown_20;
        }

        if (!warhead->EMEffect && !Type->unknown_294) {
            if (airborneTarget == 0 || airborneObject->vf_30() == 2) {
                if (Target != 0 && this->FUN_005F6360(Target) < 0x2A) {
                    effectPosition = Target->vf_22();
                    if (Target->vf_11() == 6) {
                        BuildingClass* building = static_cast<BuildingClass*>(Target);
                        const CoordStruct& offset = building->Type->TargetCoordOffset;
                        if (offset.X != 0 || offset.Y != 0 || offset.Z != 0)
                            effectPosition = static_cast<ObjectClass*>(Target)->vf_41();
                    }
                }
            } else if (this->FUN_005F6360(Target) < 0x80) {
                effectPosition = airborneObject->vf_41();
            }
        }
    }

    if (Type->unknown_294) {
        this->FUN_004690B0(&effectPosition);
    } else {
        const CoordStruct emissionOrigin = effectPosition;
        int emitted = 0;
        while (emitted < Type->unknown_2AC) {
            this->FUN_004690B0(&effectPosition);
            if (!IsAlive)
                break;

            // The native code randomizes and computes the next coordinate
            // after every live emission, even when this was the last one.
            const int spread = DAT_00A8B230->unknown_0218.RandomRanged(0x100, 0x200);
            CoordStruct nextPosition;
            FUN_0049F420(&nextPosition, &emissionOrigin, spread, 0);
            effectPosition = nextPosition;
            ++emitted;
        }
    }
}

// Native 46A310 member accesses and the canonical ABI views used by this caller.
GG_STATIC_ASSERT(offsetof(BulletClass, Type) == 0xAC);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Type) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, Owner) == 0xB0);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Owner) == 4);
GG_STATIC_ASSERT(offsetof(ObjectClass, Location) == 0x9C);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->Location) == 0x0C);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ShrapnelWeapon) == 0x2B4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ShrapnelWeapon) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ShrapnelCount) == 0x2B8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ShrapnelCount) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Projectile) == 0xA0);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Projectile) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Damage) == 0xA4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Damage) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Speed) == 0xA8);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Speed) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Range) == 0xB4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Range) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Warhead) == 0xAC);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Warhead) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_12F) == 0x12F);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_12F) == 1);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_149) == 0x149);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_149) == 1);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_151) == 0x151);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_151) == 1);
GG_STATIC_ASSERT(offsetof(CellClass, FirstObject) == 0xE4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FirstObject) == 4);
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0x00);
GG_STATIC_ASSERT(sizeof(((CellStruct*)0)->X) == 2);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(((CellStruct*)0)->Y) == 2);
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x00);
GG_STATIC_ASSERT(sizeof(((CoordStruct*)0)->X) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 0x04);
GG_STATIC_ASSERT(sizeof(((CoordStruct*)0)->Y) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x08);
GG_STATIC_ASSERT(sizeof(((CoordStruct*)0)->Z) == 4);
GG_STATIC_ASSERT(offsetof(BulletVelocity, X) == 0x00);
GG_STATIC_ASSERT(sizeof(((BulletVelocity*)0)->X) == 8);
GG_STATIC_ASSERT(offsetof(BulletVelocity, Y) == 0x08);
GG_STATIC_ASSERT(sizeof(((BulletVelocity*)0)->Y) == 8);
GG_STATIC_ASSERT(offsetof(BulletVelocity, Z) == 0x10);
GG_STATIC_ASSERT(sizeof(((BulletVelocity*)0)->Z) == 8);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner) == 0x21C);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->Owner) == 4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0218) == 0x218);
GG_STATIC_ASSERT(sizeof(((ScenarioClass*)0)->unknown_0218) == 0x3F4);
GG_STATIC_ASSERT(sizeof(DAT_007ED3D0[0]) == 4);
GG_STATIC_ASSERT(sizeof(DAT_00ABD490[0]) == 4);

// Native caller APIs used by BulletClass::FUN_004690B0. These declarations
// describe observed transports; original source-level spellings remain unknown.
int FUN_00489280(const CoordStruct* where, int damage, TechnoClass* owner,
    WarheadTypeClass* warhead, int unknown_arg4, HouseClass* house);
AnimTypeClass* FUN_0048A4F0(int health, WarheadTypeClass* warhead,
    int selected, const CoordStruct* location);
void FUN_0048A620(int health, WarheadTypeClass* warhead,
    CoordStruct location, char unknown_arg3, unsigned int mask);
void FUN_007509E0(int sound, CoordStruct* location, void* unknown_arg2);
// Existing native helper at 0x4251F0; use the mapped provider signature.
void FUN_004251F0(int unused, const short* cell);

// GLOBAL: GAMEMD 0x87F7EC; native EAX store at 0x4690FA.
extern int DAT_0087F7EC;
// GLOBAL: GAMEMD 0x87F7F0; native EAX store at 0x46912B.
extern int DAT_0087F7F0;
// GLOBAL: GAMEMD 0x87F5D8; native fixed receiver at 0x46936B.
extern Obj_00439110 DAT_0087F5D8;
// Existing globals bound at the same native addresses.
extern const char rclsid_007E96E0[16];
extern const char riid_007F7C90[16];

// Provenance: own-binary-via-Ghidra, entry assembly and slice reviews.
namespace {
// Nested list contracts: native 469D40/469E02 reads +19C,
// 469D62 reads +1AC, and 469DB9 reads +190. Warhead ctor RTTI
// proves TypeList<const VoxelAnimTypeClass*> and TypeList<int>.
typedef TypeList<const VoxelAnimTypeClass*> BulletDebrisTypeList;
typedef TypeList<int> BulletDebrisMaximumList;
GG_STATIC_ASSERT(sizeof(BulletDebrisTypeList) == 0x1C);
GG_STATIC_ASSERT(offsetof(BulletDebrisTypeList, Items) == 4);
GG_STATIC_ASSERT(sizeof(((BulletDebrisTypeList*)0)->Items) == 4);
GG_STATIC_ASSERT(sizeof(*((BulletDebrisTypeList*)0)->Items) == 4);
GG_STATIC_ASSERT(offsetof(BulletDebrisTypeList, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(((BulletDebrisTypeList*)0)->Count) == 4);
GG_STATIC_ASSERT(sizeof(BulletDebrisMaximumList) == 0x1C);
GG_STATIC_ASSERT(offsetof(BulletDebrisMaximumList, Items) == 4);
GG_STATIC_ASSERT(sizeof(((BulletDebrisMaximumList*)0)->Items) == 4);
GG_STATIC_ASSERT(sizeof(*((BulletDebrisMaximumList*)0)->Items) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, CellSpread) == 0x124);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->CellSpread) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, DirectRocker) == 0x14f);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->DirectRocker) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, CLDisableRed) == 0x151);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->CLDisableRed) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, CLDisableGreen) == 0x152);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->CLDisableGreen) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, CLDisableBlue) == 0x153);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->CLDisableBlue) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, MindControl) == 0x155);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->MindControl) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, IvanBomb) == 0x157);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->IvanBomb) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ElectricAssault) == 0x158);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ElectricAssault) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Parasite) == 0x159);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Parasite) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Temporal) == 0x15a);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Temporal) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, IsLocomotor) == 0x15b);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->IsLocomotor) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Locomotor) == 0x15c);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Locomotor) == 16);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Airstrike) == 0x16c);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Airstrike) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, BombDisarm) == 0x16e);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->BombDisarm) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, MakesDisguise) == 0x175);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->MakesDisguise) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, NukeMaker) == 0x176);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->NukeMaker) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeXlo) == 0x17c);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeXlo) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeXhi) == 0x180);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeXhi) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeYlo) == 0x184);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeYlo) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeYhi) == 0x188);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeYhi) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, DebrisTypes) == 0x18c);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->DebrisTypes) == 28);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, DebrisMaximums) == 0x1a8);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->DebrisMaximums) == 28);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, MaxDebris) == 0x1c4);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->MaxDebris) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, MinDebris) == 0x1c8);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->MinDebris) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner) == 0x21c);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->Owner) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, TemporalImUsing) == 0x274);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->TemporalImUsing) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, Airstrike) == 0x294);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->Airstrike) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, DirectRockerLinkedUnit) == 0x2a8);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->DirectRockerLinkedUnit) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, LocomotorTarget) == 0x2ac);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->LocomotorTarget) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, LocomotorSource) == 0x2b0);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->LocomotorSource) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, CaptureManager) == 0x2bc);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->CaptureManager) == 4);
GG_STATIC_ASSERT(offsetof(TechnoClass, BunkerLinkedItem) == 0x2e4);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->BunkerLinkedItem) == 4);
GG_STATIC_ASSERT(offsetof(FootClass, ParasiteImUsing) == 0x69c);
GG_STATIC_ASSERT(sizeof(((FootClass*)0)->ParasiteImUsing) == 4);
GG_STATIC_ASSERT(offsetof(FootClass, IsAttackedByLocomotor) == 0x6ad);
GG_STATIC_ASSERT(sizeof(((FootClass*)0)->IsAttackedByLocomotor) == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, Type) == 0xac);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Type) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, Owner) == 0xb0);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Owner) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, Bright) == 0xe0);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Bright) == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, Target) == 0x10c);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Target) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, WH) == 0x128);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->WH) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, WeaponType) == 0x130);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->WeaponType) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, DamageMultiplier) == 0x150);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->DamageMultiplier) == 4);
GG_STATIC_ASSERT(offsetof(ObjectClass, AttachedTag) == 0x34);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->AttachedTag) == 4);
GG_STATIC_ASSERT(offsetof(ObjectClass, AttachedBomb) == 0x38);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->AttachedBomb) == 4);
GG_STATIC_ASSERT(offsetof(ObjectClass, Health) == 0x6c);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->Health) == 4);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsAlive) == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->IsAlive) == 1);
GG_STATIC_ASSERT(offsetof(ObjectClass, Location) == 0x9c);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->Location) == 12);
GG_STATIC_ASSERT(offsetof(AbstractClass, Flags) == 0x14);
GG_STATIC_ASSERT(sizeof(((AbstractClass*)0)->Flags) == 1);
GG_STATIC_ASSERT(offsetof(CellClass, FirstObject) == 0xe4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FirstObject) == 4);
GG_STATIC_ASSERT(offsetof(CellClass, LandType) == 0xec);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->LandType) == 4);
GG_STATIC_ASSERT(offsetof(CellClass, RadSite) == 0xf8);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->RadSite) == 4);
GG_STATIC_ASSERT(offsetof(HouseClass, Type) == 0x34);
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->Type) == 4);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex2) == 0xb8);
GG_STATIC_ASSERT(sizeof(((HouseTypeClass*)0)->ArrayIndex2) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Projectile) == 0xa0);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Projectile) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Damage) == 0xa4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Damage) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Speed) == 0xa8);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Speed) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Warhead) == 0xac);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Warhead) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_158) == 0x158);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_158) == 4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Size) == 0x380);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Size) == 8);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Naval) == 0xcce);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Naval) == 1);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Underwater) == 0xd69);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Underwater) == 1);
GG_STATIC_ASSERT(offsetof(UnitClass, Type) == 0x6c4);
GG_STATIC_ASSERT(sizeof(((UnitClass*)0)->Type) == 4);
GG_STATIC_ASSERT(offsetof(BuildingClass, Type) == 0x520);
GG_STATIC_ASSERT(sizeof(((BuildingClass*)0)->Type) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, YuriMindControlSound) == 0x214);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->YuriMindControlSound) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, WeaponNullifyAnim) == 0x350);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->WeaponNullifyAnim) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, NukeWarhead) == 0xf8c);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->NukeWarhead) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, DirectRockingCoefficient) == 0x18b4);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->DirectRockingCoefficient) == 4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0218) == 0x218);
GG_STATIC_ASSERT(sizeof(((ScenarioClass*)0)->unknown_0218) == 1012);
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x0);
GG_STATIC_ASSERT(sizeof(((CoordStruct*)0)->X) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 0x4);
GG_STATIC_ASSERT(sizeof(((CoordStruct*)0)->Y) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x8);
GG_STATIC_ASSERT(sizeof(((CoordStruct*)0)->Z) == 4);
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0x0);
GG_STATIC_ASSERT(sizeof(((CellStruct*)0)->X) == 2);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 0x2);
GG_STATIC_ASSERT(sizeof(((CellStruct*)0)->Y) == 2);
GG_STATIC_ASSERT(offsetof(BulletVelocity, X) == 0x0);
GG_STATIC_ASSERT(sizeof(((BulletVelocity*)0)->X) == 8);
GG_STATIC_ASSERT(offsetof(BulletVelocity, Y) == 0x8);
GG_STATIC_ASSERT(sizeof(((BulletVelocity*)0)->Y) == 8);
GG_STATIC_ASSERT(offsetof(BulletVelocity, Z) == 0x10);
GG_STATIC_ASSERT(sizeof(((BulletVelocity*)0)->Z) == 8);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_294) == 0x294);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_294) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29E) == 0x29e);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29E) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AirburstWeapon) == 0x2b0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AirburstWeapon) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ShrapnelWeapon) == 0x2b4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ShrapnelWeapon) == 4);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_16A4) + 25 == 0x16BD);
GG_STATIC_ASSERT(sizeof(((BuildingTypeClass*)0)->bools_16A4[25]) == 1);
}

// FUNCTION: GAMEMD 0x4690B0
void BulletClass::FUN_004690B0(const CoordStruct* impact)
{
    int areaDamageResult = 1; // native stack dword initialized at 0x4690C1
    bool impactSpecialResult = false; // native stack byte initialized false
    // Dispatch locals end before the shared impact continuation. Forward
    // branches leave this scope instead of bypassing local initializations.
    {
    WarheadTypeClass* warhead = static_cast<WarheadTypeClass*>(WH);

    if (warhead->ShakeXlo != 0 || warhead->ShakeXhi != 0) {
        DAT_0087F7EC = DAT_00886B88.RandomRanged(
            warhead->ShakeXlo, warhead->ShakeXhi);
    }
    // Native 4690FF reloads WH after the preceding random callback.
    warhead = static_cast<WarheadTypeClass*>(WH);
    if (warhead->ShakeYlo != 0 || warhead->ShakeYhi != 0) {
        DAT_0087F7F0 = DAT_00886B88.RandomRanged(
            warhead->ShakeYlo, warhead->ShakeYhi);
    }

    // The native signed DWORD at WeaponType+0x158 is tested with JLE.
    if (WeaponType != 0) {
      // Native 46913E/469146 saves this value across the calls below.
      const int radLevel = WeaponType->unknown_158;
      if (radLevel > 0) {
        CellStruct impactCell;
        impactCell.X = static_cast<short>(impact->X / 0x100);
        impactCell.Y = static_cast<short>(impact->Y / 0x100);

        const int spread = static_cast<int>(WeaponType->Warhead->CellSpread);
        CellClass* cell = reinterpret_cast<CellClass*>(
            Map_0087F7E8.FUN_005657A0(&impactCell));
        RadSiteClass* site = static_cast<RadSiteClass*>(cell->RadSite);

        if (site == 0) {
            site = new RadSiteClass();
            site->SetBaseCell(&impactCell);
            site->SetSpread(spread);
            site->SetRadLevel(radLevel);
            site->Activate();
            cell->RadSite = site;
        } else {
            site->Add(radLevel);
        }
      }
    }


// Feature predicates and call transports follow the pinned entry instructions.
// Forward branches join the shared impact continuation at 0x469AA4.
// AbstractClass.Flags bit 1 remains intentionally unnamed.

    // Native 46920B reloads WH after radiation-site callbacks.
    warhead = static_cast<WarheadTypeClass*>(WH);
    // Native 0x469211 tests WarheadTypeClass+0x155 (MindControl).
    if (warhead->MindControl) {
        if (Owner == 0)
            goto common_impact_tail;
        if (Owner->CaptureManager == 0)
            goto common_impact_tail;

        AbstractClass* targetWithFlag1 =
            Target != 0 && Target->Flags.unknown_14_1 ? Target : 0;

        // Independent target-owner predicate: only when AbstractClass flag
        // bit 0 is set, load TechnoClass::Owner and call 0x50B6F0.
        bool targetHousePredicate = false;
        if (Target != 0 && Target->Flags.IsTechno) {
            TechnoClass* targetTechno = static_cast<TechnoClass*>(Target);
            targetHousePredicate =
                targetTechno->Owner->IsControlledByCurrentPlayer();
        }

        // Native checks normalized target, ObjectClass::IsAlive (+0x90),
        // and ObjectClass::AttachedTag (+0x34), then invokes two tag events.
        if (targetWithFlag1 != 0) {
            ObjectClass* targetObject =
                static_cast<ObjectClass*>(targetWithFlag1);
            if (targetObject->IsAlive && targetObject->AttachedTag != 0) {
                targetObject->AttachedTag->FUN_006E53A0(
                    6, targetObject, DAT_0089DDF0, false,
                    reinterpret_cast<int>(Owner));
                targetObject->AttachedTag->FUN_006E53A0(
                    0x2C, targetObject, DAT_0089DDF0, false,
                    reinterpret_cast<int>(Owner));
            }
        }

        // FUN_00471D40 is CaptureManagerClass::thiscall with one target
        // pointer and RET 4. Pass the original Target, including null.
        // Native 4692BD..4692D0 reloads Owner and its manager after tag callbacks.
        if (!static_cast<CaptureManagerClass*>(Owner->CaptureManager)
                 ->FUN_00471D40(Target))
            goto common_impact_tail;
        if (Rules->YuriMindControlSound == -1)
            goto common_impact_tail;

        const bool ownerHousePredicate = Owner->Owner->IsControlledByCurrentPlayer();
        if (!ownerHousePredicate && !targetHousePredicate)
            goto common_impact_tail;

        // Native 0x46930D passes Rules+0x214 in ECX, &target.Location in EDX,
        // and one zero stack argument to 0x7509E0. This is reached only if
        // targetWithFlag1 survived the original native pointer normalization.
        // Native 46930D unconditionally advances the saved normalized
        // pointer to Location and reads it; no extra null guard is present.
        CoordStruct soundLocation =
            static_cast<ObjectClass*>(targetWithFlag1)->Location;
        FUN_007509E0(Rules->YuriMindControlSound, &soundLocation, 0);
        goto common_impact_tail;
    }

    // No test of WarheadTypeClass+0x156 occurs in this function range.
    // Native 0x469343 tests +0x157 (IvanBomb).
    if (warhead->IvanBomb) {
        TechnoClass* targetTechno =
            Target != 0 && Target->Flags.IsTechno
                ? static_cast<TechnoClass*>(Target) : 0;
        // Native ECX is the fixed object address 0x87F5D8. It pushes Owner
        // then targetTechno, so stack arguments are (Owner,targetTechno),
        // callee cleanup is RET 8; precise C++ receiver type is unresolved.
        DAT_0087F5D8.FUN_00438E70(Owner, targetTechno);
        goto common_impact_tail;
    }

    // Native 0x46937A tests +0x158 (ElectricAssault). The virtual call at
    // +0x2C is AbstractClass slot 11; the full EAX values are compared.
    if (warhead->ElectricAssault) {
        if (Target == 0 || Target->vf_11() != 6 || Owner == 0 ||
            Owner->vf_11() != 0xF)
            goto common_impact_tail;
        // Native ECX=Target, one stack arg=Owner, callee RET 4.
        static_cast<BuildingClass*>(Target)->FUN_00452820(Owner);
        goto common_impact_tail;
    }

    // Native 0x4693D3 tests +0x159. Keep this flag as its numeric field;
    // the call contract is the evidence here, not a guessed feature label.
    if (warhead->Parasite) {
        if (Owner == 0)
            goto common_impact_tail;
        AbstractClass* normalizedTarget =
            Target != 0 && Target->Flags.IsFoot ? Target : 0;
        // Native receiver is dword [Owner+0x69C], one stack argument is the
        // normalized pointer, callee cleanup RET 4.
        static_cast<ParasiteClass_0062A8E0*>(
            static_cast<FootClass*>(Owner)->ParasiteImUsing)
                ->FUN_0062A980(normalizedTarget);
        goto common_impact_tail;
    }

// ABI/call-site ledger:
// 469267: ECX=Target->Owner; CALL 50B6F0; no args, RET 0 (member-like leaf).
// 4692A2 / 4692B8: ECX=Target->AttachedTag; stack args (event, target,
//   CellStruct-by-value, false, Owner-as-dword); callee RET 0x14. Existing
//   TagClass::FUN_006E53A0 declaration matches this exact five-argument form.
// 4692D0: ECX=Owner->CaptureManager; stack arg Target; CALL 471D40; RET 4.
// 4692FC: ECX=Owner->Owner; CALL 50B6F0; no args, RET 0.
// 469339: ECX=Rules+214, EDX=&target.Location, stack arg 0; CALL 7509E0,
//   RET 4. Existing fastcall form is int, CoordStruct*, void*.
// 469370: ECX=absolute receiver 0x87F5D8; stack args Owner,targetTechno;
//   CALL 438E70, RET 8. Receiver's C++ class/API association is not yet proven.
// 4693C9: ECX=Target, stack arg Owner; CALL 452820, RET 4. Exact concrete
//   receiver class association is not yet proven (Target WhatAmI()==6).
// 469401/419: ECX=dword [Owner+69C], stack arg normalizedTarget; CALL 62A980,
//   RET 4. Exact concrete receiver class association remains open.

// The range contains the +0x15A Temporal branch, then (when it is false) the
// +0x15B IsLocomotor branch. Both branches rejoin at common_impact_tail,
// native 0x469AA4.
//
// Narrow prerequisites for a future canonical integration:
//   * BuildingTypeClass::bools_16A4[25] byte at +0x16BD (native TEST byte).
//   * TechnoClass::FUN_0070FEE0(int) (ECX Owner, stack int, RET 4).
//   * TechnoClass::FUN_00710000(RawBlock10, AbstractClass*) (ECX Owner,
//     16-byte by-value value then target pointer, RET 0x14).
// Other fields and vslots used below are already present in canonical headers.

    // Native +0x15A (Temporal), 0x469423.
    if (warhead->Temporal) {
        if (Owner == 0 || Target == 0)
            goto common_impact_tail;

        FootClass* targetFoot =
            Target->Flags.IsFoot ? static_cast<FootClass*>(Target) : 0;
        if (targetFoot != 0 && targetFoot->vf_30() != 2)
            goto common_impact_tail;

        // EDI starts as Target when AbstractClass bit 0 is set, otherwise 0.
        TechnoClass* temporalTarget =
            Target->Flags.IsTechno ? static_cast<TechnoClass*>(Target) : 0;
        if (temporalTarget != 0) {
            if (temporalTarget->BunkerLinkedItem != 0 &&
                temporalTarget->vf_11() == 1) {
                // Native reloads +0x2E4 after the virtual callback, then
                // passes that reloaded pointer to Owner's slot 242 and the
                // TemporalClass call. Preserve the callback mutation point.
                temporalTarget = temporalTarget->BunkerLinkedItem;
                Owner->vf_242(temporalTarget);
            }
        }
        Owner->TemporalImUsing->FUN_0071AF20(
            reinterpret_cast<TemporalTechnoView*>(temporalTarget));
        goto common_impact_tail;
    }

    // Native +0x15B (IsLocomotor), 0x4694CB. This branch checks and updates
    // locomotor linkage, then re-loads BulletClass::Target after its callback.
    if (warhead->IsLocomotor) {
        if (Owner == 0)
            goto common_impact_tail;
        if (Owner->LocomotorTarget == Target ||
            Owner->LocomotorSource != 0)
            goto common_impact_tail;

        // Native checks the owner (ECX's saved this), not Target, at +0x14
        // bit 2 and then Owner+0x6AD.
        FootClass* ownerFoot =
            Owner->Flags.IsFoot ? static_cast<FootClass*>(Owner) : 0;
        if (ownerFoot != 0 && ownerFoot->IsAttackedByLocomotor)
            goto common_impact_tail;

        AbstractClass* initialTarget = Target;
        bool sameCellBuilding = false;
        if (initialTarget != 0 && initialTarget->vf_11() == 1) {
            // Native reloads Target and repeats slot 11 before normalizing the
            // receiver passed to FUN_0065AD30.
            AbstractClass* lookupTarget = Target;
            TechnoClass* lookupTechno = lookupTarget != 0 &&
                lookupTarget->vf_11() == 1
                    ? static_cast<TechnoClass*>(lookupTarget) : 0;
            // Native calls even when this normalized ECX value is zero:
            // PUSH 0; MOV ECX,normalizedTarget; CALL 0x65AD30.
            AbstractClass* candidate = lookupTechno->FUN_0065AD30(0);
            if (candidate != 0 && candidate->vf_11() == 6 &&
                static_cast<BuildingClass*>(candidate)->Type->bools_16A4[25]) {
                AbstractClass* currentTarget = Target; // reload at 0x469595
                TechnoClass* currentTechno = currentTarget != 0 &&
                    currentTarget->vf_11() == 1
                        ? static_cast<TechnoClass*>(currentTarget) : 0;
                const CoordStruct currentLocation =
                    static_cast<ObjectClass*>(currentTechno)->Location;
                CellClass* cell =
                    Map_0087F7E8.FUN_00565730(currentLocation);
                if (cell->GetBuilding() == candidate)
                    sameCellBuilding = true;
            }
        }

        // Native calls on Owner with one stack zero only when
        // Owner::LocomotorTarget was non-null.
        if (Owner->LocomotorTarget != 0)
            Owner->FUN_0070FEE0(0);

        AbstractClass* currentTarget = Target; // reload at 0x469602
        if (currentTarget == 0 || sameCellBuilding)
            goto common_impact_tail;
        FootClass* currentFoot =
            currentTarget->Flags.IsFoot
                ? static_cast<FootClass*>(currentTarget) : 0;
        if (currentFoot != 0 && currentFoot->vf_30() != 2)
            goto common_impact_tail;

        currentTarget = Target; // reload at 0x469648
        if (currentTarget == 0 || !currentTarget->Flags.IsFoot)
            goto common_impact_tail;
        currentFoot = static_cast<FootClass*>(currentTarget);
        if (currentFoot->vf_88())
            goto common_impact_tail;

        // Native performs two fresh Target loads/tests: first accept kind 1;
        // only otherwise reload and accept kind 2. EDI/currentFoot remains
        // the earlier normalized receiver for the following fields/call.
        AbstractClass* kindTarget = Target;
        bool supportedKind = kindTarget != 0 && kindTarget->vf_11() == 1;
        if (!supportedKind) {
            kindTarget = Target;
            supportedKind = kindTarget != 0 && kindTarget->vf_11() == 2;
        }
        if (!supportedKind)
            goto common_impact_tail;
        if (currentFoot->IsAttackedByLocomotor)
            goto common_impact_tail;

        TechnoTypeClass* targetType = currentFoot->vf_33();
        if (!(static_cast<double>(Health) > targetType->Size))
            goto common_impact_tail;

        // Native 0x4696D4 reserves/copies the 16-byte Warhead Locomotor value,
        // pushes current Target, sets ECX=Owner, then calls 0x710000.
        Owner->FUN_00710000(
            static_cast<WarheadTypeClass*>(WH)->Locomotor, currentTarget);
        goto common_impact_tail;
    }

    // When +0x15B is false, native control continues at 0x46978E; otherwise
    // this branch joins at 0x469700.


// Branch order is Airstrike (+16C), DirectRocker (+14F), BombDisarm (+16E),
// MakesDisguise (+175), NukeMaker (+176), then the default damage path.
// common_impact_tail is native 0x469AA4. The dead-after-damage edge reaches
// the native epilogue at 0x46A290.

    // The preceding IsLocomotor test branches here only when +0x15B is false.
    // Airstrike path: require Techno flag and Airstrike helper; reload Target
    // after its first callback before the second helper call.
    if (warhead->Airstrike) {
        if (Owner == 0)
            goto common_impact_tail;
        AbstractClass* firstTarget = Target;
        if (firstTarget == 0 || !firstTarget->Flags.IsTechno)
            goto common_impact_tail;

        TechnoClass* airstrikeTarget =
            static_cast<TechnoClass*>(firstTarget);
        AirstrikeClass* airstrike =
            static_cast<AirstrikeClass*>(Owner->Airstrike);
        if (airstrike == 0 ||
            !airstrike->FUN_0041D7E0(airstrikeTarget))
            goto common_impact_tail;

        AbstractClass* secondTarget = Target; // native reload @0x469761
        TechnoClass* secondTechno =
            secondTarget != 0 && secondTarget->Flags.IsTechno
                ? static_cast<TechnoClass*>(secondTarget) : 0;
        static_cast<AirstrikeClass*>(Owner->Airstrike)
            ->StartMission(secondTechno);
        goto common_impact_tail;
    }

    // DirectRocker (+0x14F): the native type check is WhatAmI()==1, then a
    // normalized Techno pointer must exist. vslot +0x160 (slot 88) vetoes.
    if (warhead->DirectRocker) {
        AbstractClass* firstTarget = Target;
        if (firstTarget != 0 && firstTarget->vf_11() == 1) {
            AbstractClass* currentTarget = Target; // native reload @0x4697B8
            TechnoClass* targetTechno =
                currentTarget != 0 && currentTarget->Flags.IsTechno
                    ? static_cast<TechnoClass*>(currentTarget) : 0;
            if (Owner != 0 && targetTechno != 0 &&
                !targetTechno->vf_88()) {
                const int scaledDamage =
                    (DamageMultiplier * Health) >> 8;
                double movementSpeed =
                    static_cast<double>(scaledDamage) *
                    static_cast<double>(Rules->DirectRockingCoefficient) / 100.0;
                if (movementSpeed >= 4.0)
                    movementSpeed = 4.0;

                // Native subtracts Target.Location from Owner.Location,
                // converts each signed dword to float, and sums squared
                // float components before calling the x87 sqrt helper.
                const CoordStruct targetLocation = targetTechno->Location;
                const CoordStruct ownerLocation = Owner->Location;
                float directionX = static_cast<float>(
                    ownerLocation.X - targetLocation.X);
                float directionY = static_cast<float>(
                    ownerLocation.Y - targetLocation.Y);
                float directionZ = static_cast<float>(
                    ownerLocation.Z - targetLocation.Z);
                const double squaredDistance =
                    directionX * directionX +
                    directionY * directionY +
                    directionZ * directionZ;
                const double distance = FUN_004CAC40(squaredDistance);

                if (distance != 0.0) {
                    directionX = static_cast<float>(directionX / distance);
                    directionY = static_cast<float>(directionY / distance);
                    directionZ = static_cast<float>(directionZ / distance);
                }

                // Three native 0x7C5F00 conversions consume, in order, x,
                // y, then z after multiplication by the float constant 10.0.
                const int offsetX = static_cast<int>(directionX * 10.0f);
                const int offsetY = static_cast<int>(directionY * 10.0f);
                const int offsetZ = static_cast<int>(directionZ * 10.0f);
                CoordStruct destination = targetLocation;
                destination.X += offsetX;
                destination.Y += offsetY;
                destination.Z += offsetZ;

                // Native slot 246 (+0x3D8), ECX target, stack args
                // (CoordStruct*, float, bool), callee RET 0xC.
                targetTechno->vf_246(
                    &destination, static_cast<float>(movementSpeed), true);

                // Both owner reads occur after the virtual callback in retail.
                targetTechno->DirectRockerLinkedUnit = Owner;
                Owner->DirectRockerLinkedUnit = targetTechno;
                goto common_impact_tail;
            }
        }
    }

    // BombDisarm (+0x16E): test target flag bit 1, then the ObjectClass
    // AttachedBomb pointer at +0x38 and call its existing Disarm method.
    // Native 4699C4 reloads WH at this dispatch continuation.
    warhead = static_cast<WarheadTypeClass*>(WH);
    if (warhead->BombDisarm) {
        AbstractClass* target = Target;
        if (target != 0 && target->Flags.unknown_14_1) {
            UnInitBomb* bomb =
                static_cast<UnInitBomb*>(
                    static_cast<ObjectClass*>(target)->AttachedBomb);
            if (bomb != 0)
                bomb->Disarm();
        }
        goto common_impact_tail;
    }

    // MakesDisguise (+0x175): Owner slot 283, DisguiseAs(Target). Target is
    // passed as-is, including null; the return value is ignored.
    if (warhead->MakesDisguise) {
        if (Owner != 0)
            Owner->DisguiseAs(Target);
        goto common_impact_tail;
    }

    if (warhead->NukeMaker) {
        FUN_0046B310(); // BulletClass receiver, no stack arguments
        goto common_impact_tail;
    }

    if (Type->ShrapnelWeapon != 0)
        FUN_0046A310(); // BulletClass receiver, no stack arguments

    const int damage = (DamageMultiplier * Health) >> 8;
    HouseClass* ownerHouse = Owner != 0 ? Owner->Owner : 0;

    // Native /Gr fastcall transport: ECX=impact, EDX=damage, then stack args
    // Owner, Warhead, 1, House. This call reads the integer status in EAX.
    const int result = FUN_00489280(
        impact, damage, Owner, static_cast<WarheadTypeClass*>(WH), 1,
        ownerHouse);
    areaDamageResult = result;
    if (!IsAlive)
        return; // native 0x46A290 epilogue; RET 4 caller cleanup.
    if (result == 2)
        impactSpecialResult = true;
    goto common_impact_tail;


// Shared impact continuation beginning at native 0x469AA4.
    } // feature dispatch
common_impact_tail:
    const CoordStruct impactBase = *impact;
    CoordStruct impactPosition = impactBase;
    if (Type->unknown_29E) {
        // 0x49F420: output in ECX, base in EDX, stack args (0x20, 0).
        FUN_0049F420(&impactPosition, &impactBase, 0x20, 0);
    }

    int impactCellKind = -1;
    if (vf_114() < DAT_0089DE70 * 2) {
        CellClass* impactCell = Map_0087F7E8.FUN_00565730(Location);
        impactCellKind = impactCell->LandType;
        if (impactCellKind == 2 && areaDamageResult == 0) {
            CellClass* sameImpactCell =
                Map_0087F7E8.FUN_00565730(Location);
            AbstractClass* firstObject =
                static_cast<AbstractClass*>(sameImpactCell->FirstObject);
            if (firstObject != 0 && firstObject->vf_11() == 1) {
                // Unit RTTI is primary table 0x7F5C70; its slot 11 target
                // 0x746E20 returns 1. AircraftClass's corresponding slot
                // returns 2, so the native comparison justifies this cast.
                UnitClass* unit = static_cast<UnitClass*>(firstObject);
                UnitTypeClass* unitType =
                    static_cast<UnitTypeClass*>(unit->Type);
                if (unitType->Naval && !unitType->Underwater)
                    impactCellKind = -1;
            }
        }
    }

    // Native copies Bullet.Location into a separate, by-reference local for
    // the selector call. The selector's native call ABI is ECX=Health,
    // EDX=Warhead, stack (selected index, CoordStruct*), RET 8.
    const CoordStruct bulletLocation = Location;
    WarheadTypeClass* impactWarhead =
        static_cast<WarheadTypeClass*>(WH); // native reload @0x469BC4
    AnimTypeClass* selectedImpactAnimation =
        FUN_0048A4F0(Health, impactWarhead, impactCellKind, &bulletLocation);

    // Special area-damage result branches to 0x46A2A1 regardless of Bright.
    // It creates Rules+0x350's animation and returns before ordinary weapon
    // effects, selected-impact allocation, or the debris tail.
    if (impactSpecialResult) {
        AnimTypeClass* specialAnimation = Rules->WeaponNullifyAnim;
        if (specialAnimation == 0)
            return;
        new AnimClass(specialAnimation, impactPosition, 0, 1, 0x2600,
            FUN_0048ACE0(impactPosition.X, impactPosition.Y,
                         impactPosition.Z), false);
        return;
    }

    // The weapon effect is only emitted when Bright is set and the preceding
    // area-damage result was not 2. CoordStruct is passed by value (three
    // DWORDs) to 0x48A620; the remaining stack args are 1 and the three-bit
    // warhead disable mask.
    if (Bright) {
        WarheadTypeClass* effectWarhead =
            static_cast<WarheadTypeClass*>(WH); // native reload @0x469BF0
        unsigned int disableMask = 0;
        if (effectWarhead->CLDisableRed)
            disableMask |= 2;
        if (effectWarhead->CLDisableGreen)
            disableMask |= 4;
        if (effectWarhead->CLDisableBlue)
            disableMask |= 8;
        FUN_0048A620(Health, effectWarhead, impactPosition, 1, disableMask);
    }

    if (selectedImpactAnimation != 0) {
        // The native heap-failure branch is observable: when the 0x1C8-byte
        // AnimClass allocation fails, it conditionally emits the cell-center
        // fallback only for the Rules Warhead at +0xF8C.
        AnimClass* animation = new AnimClass(
            selectedImpactAnimation,
            impactPosition, 0, 1, 0x2600,
            FUN_0048ACE0(impactPosition.X, impactPosition.Y,
                         impactPosition.Z), false);
        if (animation == 0 &&
            static_cast<WarheadTypeClass*>(WH) == Rules->NukeWarhead) {
            int color = -1;
            if (Owner != 0)
                color = Owner->Owner->Type->ArrayIndex2;

            // Native signed rounding to cell coordinates is (v + 255 when
            // negative) >> 8, then truncation to a 16-bit cell component.
            CellStruct fallbackCell;
            fallbackCell.X = static_cast<short>(
                (impactPosition.X + (impactPosition.X < 0 ? 255 : 0)) >> 8);
            fallbackCell.Y = static_cast<short>(
                (impactPosition.Y + (impactPosition.Y < 0 ? 255 : 0)) >> 8);
            // 0x4251F0 is a /Gr free function: color in ECX and CellStruct*
            // in EDX. The retained canonical API spells these two arguments.
            FUN_004251F0(color, &fallbackCell.X);
        }
    }

    // Native fall-through boundary: 0x469D06 loads Type+0x1C4 and begins the
    // debris-count loop. That complete remainder is the next source slice.

// Exact native range 0x469D06..0x46A302; all returns clean the one caller
// coordinate argument with RET 4 at 0x46A296 or 0x46A301.
debris_phase_469d06:
    WarheadTypeClass* debrisWarhead =
        static_cast<WarheadTypeClass*>(WH); // native reload at 0x469D06
    if (debrisWarhead->MaxDebris > 0) {
        int remainingDebris = DAT_00A8B230->unknown_0218.RandomRanged(
            debrisWarhead->MinDebris, debrisWarhead->MaxDebris - 1);
        debrisWarhead = static_cast<WarheadTypeClass*>(WH);
        int debrisTypeCount = debrisWarhead->DebrisTypes.Count;

        if (debrisTypeCount > 0 && remainingDebris > 0) {
            int debrisTypeIndex = 0;
            while (remainingDebris > 0) {
                int* maximums = debrisWarhead->DebrisMaximums.Items;
                const int randomValue = DAT_00A8B230->unknown_0218.Random();
                const int perTypeMaximum = maximums[debrisTypeIndex];
                const unsigned int randomBits =
                    static_cast<unsigned int>(randomValue);
                const int absoluteRandom = randomValue < 0
                    ? static_cast<int>(0u - randomBits) : randomValue;
                int selectedCount = absoluteRandom % (perTypeMaximum + 1);
                if (selectedCount >= remainingDebris)
                    selectedCount = remainingDebris;

                int allocationsLeft = selectedCount;
                while (allocationsLeft > 0) {
                    // Native 469D99..469DAA allocates before touching WH's
                    // list. Only success captures the element ADDRESS at
                    // 469DAC..469DC1; its VALUE is read after vf_18 at469DCF.
                    // Keeping that address across the callback is observable
                    // if the callback changes either the list or its entry.
                    void* debrisStorage = ::operator new(sizeof(VoxelAnimClass));
                    if (debrisStorage != 0) {
                        const VoxelAnimTypeClass* const* debrisSlot =
                            &static_cast<WarheadTypeClass*>(WH)->
                                DebrisTypes.Items[debrisTypeIndex];
                        const CoordStruct debrisPosition = vf_18();
                        new (debrisStorage) VoxelAnimClass(
                            *debrisSlot, debrisPosition, 0);
                    }
                    --allocationsLeft;
                }

                remainingDebris -= selectedCount;
                debrisWarhead = static_cast<WarheadTypeClass*>(WH);
                debrisTypeCount = debrisWarhead->DebrisTypes.Count;
                ++debrisTypeIndex;
                if (debrisTypeIndex >= debrisTypeCount)
                    debrisTypeIndex = 0;
            }
        }

        // If there are no typed debris entries, fill the remaining count with
        // one of Rules+0x140's animation types. Native allocates before asking
        // for the coordinate or advancing the randomizer.
        debrisWarhead = static_cast<WarheadTypeClass*>(WH);
        debrisTypeCount = debrisWarhead->DebrisTypes.Count;
        if (debrisTypeCount == 0 && remainingDebris > 0) {
            do {
                void* storage = ::operator new(sizeof(AnimClass));
                if (storage != 0) {
                    CoordStruct animationPosition = vf_18();
                    animationPosition.Z += 0x14;
                    const int animationIndex =
                        DAT_00A8B230->unknown_0218.RandomRanged(
                            0, Rules->list_013C.Count - 1);
                    new (storage) AnimClass(
                        const_cast<AnimTypeClass*>(Rules->list_013C.Items[animationIndex]),
                        animationPosition, 0, 1, 0x600, 0, false);
                }
                --remainingDebris;
            } while (remainingDebris != 0);
        }
    }

    // Native 469ECE captures the INI AirburstWeapon pointer once. Its
    // WeaponTypeClass identity is proved by the loader/factory/RTTI chain.
    if (Type->unknown_294) {
        WeaponTypeClass* effectConfig = Type->AirburstWeapon;
        BulletTypeClass* extraType = effectConfig->Projectile;
        CellClass* originalCell = vf_111();

        // The native loop advances an independent 3-bit phase and performs
        // eight CoCreateInstance attempts. A successful HRESULT is followed
        // by the setter unconditionally; the pointer null check occurs only
        // after that call in the retail instruction stream.
        int attemptsLeft = 8;
        int phase = 0;
        do {
            // Native 469EF6..469F43 selects the next neighbor and snapshots
            // setter arguments before each COM callback, not before the loop.
            CellClass* neighboringCell = originalCell->FUN_00481810(phase);
            const int originalHealth = effectConfig->Damage;
            WarheadTypeClass* originalWarhead = effectConfig->Warhead;
            TechnoClass* originalOwner = Owner;
            phase = (phase + 1) & 7;
            BulletClass* createdBullet = 0;
            const HRESULT createResult = CoCreateInstance(
                *reinterpret_cast<const CLSID*>(rclsid_007E96E0), 0, 7,
                *reinterpret_cast<const IID*>(riid_007F7C90),
                reinterpret_cast<void**>(&createdBullet));
            if (createResult >= 0) {
                createdBullet->FUN_004664C0(
                    extraType, neighboringCell, originalOwner, originalHealth,
                    originalWarhead, 0x32, 0);

                if (createdBullet != 0) {
                    const int randomDirection =
                        DAT_00A8B230->unknown_0218.RandomRanged(0, 0x20);
                    const int magnitude =
                        effectConfig->Speed / 10;
                    const short phaseWord = static_cast<short>(
                        static_cast<unsigned short>(randomDirection) << 8);
                    const double azimuth =
                        (static_cast<int>(phaseWord) - 0x3FFF) *
                        DAT_007E2810;
                    const double elevation = 4.712436918747274;

                    // Native components are assembled in this order:
                    // sin(azimuth), cos(elevation), cos(azimuth),
                    // cos(elevation), sin(elevation). BulletVelocity is the
                    // canonical three-double value passed by reference.
                    const double sinAzimuth = FUN_004CACB0(azimuth);
                    const double y = FUN_004CAD00(elevation) *
                        sinAzimuth * magnitude;
                    const double cosAzimuth = FUN_004CAD00(azimuth);
                    const double x = FUN_004CAD00(elevation) *
                        cosAzimuth * magnitude;
                    const double z = FUN_004CACB0(elevation) * magnitude;
                    BulletVelocity velocity;
                    velocity.X = x;
                    velocity.Y = y;
                    velocity.Z = z;
                    const CoordStruct launchPosition = Location;
                    createdBullet->vf_124(launchPosition, velocity);
                }
            }

            --attemptsLeft;
        } while (attemptsLeft != 0);

        // The ninth object targets the original cell, not its neighbor. These
        // config/owner values are reloaded after the eight COM callbacks as in
        // the native sequence at 0x46A0EE..0x46A150.
        // Native 46A0EE..46A117 snapshots these before CoCreateInstance.
        const int finalHealth = effectConfig->Damage;
        WarheadTypeClass* finalWarhead = effectConfig->Warhead;
        TechnoClass* finalOwner = Owner;
        BulletClass* finalBullet = 0;
        const HRESULT finalCreateResult = CoCreateInstance(
            *reinterpret_cast<const CLSID*>(rclsid_007E96E0), 0, 7,
            *reinterpret_cast<const IID*>(riid_007F7C90),
            reinterpret_cast<void**>(&finalBullet));
        if (finalCreateResult >= 0) {
            finalBullet->FUN_004664C0(
                extraType, originalCell, finalOwner, finalHealth,
                finalWarhead, 0x32, 0);

            if (finalBullet != 0) {
                const int randomDirection =
                    DAT_00A8B230->unknown_0218.RandomRanged(0, 0x20);
                const int magnitude =
                    effectConfig->Speed / 10;
                const short phaseWord = static_cast<short>(
                    static_cast<unsigned short>(randomDirection) << 8);
                const double azimuth =
                    (static_cast<int>(phaseWord) - 0x3FFF) * DAT_007E2810;
                const double elevation = 4.712436918747274;
                const double sinAzimuth = FUN_004CACB0(azimuth);
                const double y = FUN_004CAD00(elevation) *
                    sinAzimuth * magnitude;
                const double cosAzimuth = FUN_004CAD00(azimuth);
                const double x = FUN_004CAD00(elevation) *
                    cosAzimuth * magnitude;
                const double z = FUN_004CACB0(elevation) * magnitude;
                BulletVelocity velocity;
                velocity.X = x;
                velocity.Y = y;
                velocity.Z = z;
                const CoordStruct launchPosition = Location;
                finalBullet->vf_124(launchPosition, velocity);
            }
        }
    }

    return; // native epilogue 0x46A290..0x46A301; caller cleanup is RET 4.
}

// FUNCTION: GAMEMD 0x46A310
// The entry and all call contracts are documented in the private binary review.
//
// Address blocks are noted inline.  Global and byte fields still need the
// canonical declarations/asserts listed in full-body-review.md.
void BulletClass::FUN_0046A310()
{
    // 46A320-46A3D2: negative ShrapnelCount is reduced by the range to Owner.
    int requested = Type->ShrapnelCount;
    if (requested < 0) {
        if (Owner == 0) {
            requested = 3;
        } else {
            // Native captures this Location before calling Owner's slot18.
            const CoordStruct origin = Location;
            CoordStruct ownerPosition = Owner->vf_18();
            CoordStruct difference;
            difference.FUN_0041C230(ownerPosition.X - origin.X,
                                   ownerPosition.Y - origin.Y,
                                   ownerPosition.Z - origin.Z);
            int distance = difference.FUN_0041C380();
            // Native CDQ / AND 0xff / ADD / SAR sequence rounds signed
            // distance/256 toward zero; it is not an x87 conversion.
            int cellDistance = (distance + (distance < 0 ? 0xFF : 0)) >> 8;
            requested = -requested - cellDistance;
            if (requested <= 0)
                return;
        }
    }

    // 46A3D6-46A406: abort when the bullet's current cell has no object, or
    // its FirstObject reports abstract kind 6.
    CellClass* initialCell = vf_111();
    if (initialCell->FirstObject == 0)
        return;
    // Native 46A3F2 calls slot111 again; it does not repeat the null guard.
    AbstractClass* initialObject =
        static_cast<AbstractClass*>(vf_111()->FirstObject);
    if (initialObject->vf_11() == 6)
        return;

    // 46A40C-46A47E: compute the WeaponType's cell range and initialize the
    // first-pass ring scan.  Range bounds are half-open pairs at 0x7ED3D0.
    WeaponTypeClass* weapon = Type->ShrapnelWeapon;
    // 46A41F snapshots Projectile once before either scan loop.
    BulletTypeClass* projectile = weapon->Projectile;
    CellStruct baseCell = vf_110();
    int rangeInCells = (weapon->Range + (weapon->Range < 0 ? 0xFF : 0)) >> 8;
    int attempted = 0;

    // 46A473-46A914: scan each ring's [begin,end) cell-offset records at
    // 0xABD490.  Eligibility is checked before CoCreateInstance.  An eligible
    // cell consumes one requested attempt even if COM creation fails.
    for (int ring = 1; ring <= rangeInCells; ++ring) {
        int begin = DAT_007ED3D0[ring - 1];
        int end = DAT_007ED3D0[ring];
        for (int offsetIndex = begin; offsetIndex < end; ++offsetIndex) {
            CellStruct offset = DAT_00ABD490[offsetIndex];
            CellStruct candidateCell;
            candidateCell.X = static_cast<short>(baseCell.X + offset.X);
            candidateCell.Y = static_cast<short>(baseCell.Y + offset.Y);
            // Native 0x5657A0 returns a CellClass*; the shared header's
            // existing pointer overload retains a display-cell alias.  This
            // zero-offset ABI conversion is the same native object pointer.
            CellClass* candidate = reinterpret_cast<CellClass*>(
                Map_0087F7E8.FUN_005657A0(&candidateCell));

            AbstractClass* target =
                static_cast<AbstractClass*>(candidate->FirstObject);
            TechnoClass* owner = Owner;
            if (target == 0 || target == owner || owner == 0)
                continue;
            if (owner->Owner->FUN_004F9A90(target))
                continue;

            // 46A50F-46A555 snapshots these fields before CoCreateInstance;
            // keep the pre-call values if COM invokes code that mutates them.
            WarheadTypeClass* spawnWarhead = weapon->Warhead;
            unsigned char spawnFlag = weapon->unknown_12F;
            int spawnDamage = weapon->Damage;
            int spawnSpeed = weapon->Speed;
            TechnoClass* spawnOwner = Owner;

            // 46A50F-46A5AC: the COM output is cleared before the call.  On
            // success, initialize the new bullet from the selected weapon's
            // Projectile, Damage, Warhead and Speed plus this target/owner.
            BulletClass* created = 0;
            HRESULT result = CoCreateInstance(
                (REFCLSID)DAT_007E96E0, 0, 7,
                (REFIID)DAT_007F7C90,
                reinterpret_cast<void**>(&created));
            if (result >= 0) {
                created->FUN_004664C0(projectile, target, spawnOwner,
                                      spawnDamage, spawnWarhead, spawnSpeed,
                                      spawnFlag);

                // 46A5AC-46A875: aim the new bullet from this Bullet's current
                // Location at the target object's returned CoordStruct, then
                // pass the source coordinate and three-double velocity to
                // Bullet slot 124.  Native uses atan2/table trig and x87
                // conversions. The native 100.0 fallback, cosine rescaling,
                // and fixed-angle component sequence are represented below.
                if (created != 0) {
                    CoordStruct sourcePosition = Location;
                    CoordStruct targetPosition = target->vf_18();
                    double dx = static_cast<double>(targetPosition.X) - sourcePosition.X;
                    double dy = static_cast<double>(targetPosition.Y) - sourcePosition.Y;
                    short yaw = static_cast<short>(static_cast<int>(
                        (FUN_004CAE30(-dy, dx) - DAT_007E2820) * DAT_007E2818));
                    BulletVelocity velocity;
                    velocity.X = 0.0;
                    velocity.Y = 0.0;
                    velocity.Z = 0.0;
                    if (velocity.X == 0.0 && velocity.Y == 0.0)
                        velocity.X = 100.0;
                    // ABI view only: BulletVelocity and Vec3d are both three
                    // adjacent doubles (0/8/10, size 18); the native helpers
                    // receive this exact local address and read those offsets.
                    Vec3d& vectorView = reinterpret_cast<Vec3d&>(velocity);
                    double yawLength = vectorView.FUN_0041C430();
                    double yawRadians = (yaw - 0x3FFF) * DAT_007E2810;
                    velocity.X = FUN_004CAD00(yawRadians) * yawLength;
                    velocity.Y = -FUN_004CACB0(yawRadians) * yawLength;
                    // Native's second atan2 uses the third vector component
                    // and planar length after the yaw results. Z remains the
                    // zeroed input through this first direction stage.
                    double planarLength = vectorView.FUN_0041C350();
                    short pitch = static_cast<short>(static_cast<int>(
                        (FUN_004CAE30(velocity.Z, planarLength) - DAT_007E2820) *
                         DAT_007E2818));
                    double pitchRadians = (pitch - 0x3FFF) * DAT_007E2810;
                    double preSpreadLength = vectorView.FUN_0041C3C0();
                    if (pitchRadians != 0.0) {
                        velocity.X /= FUN_004CAD00(pitchRadians);
                        velocity.Y /= FUN_004CAD00(pitchRadians);
                    }
                    // Native stack constants at 46A787..46A7BF encode this
                    // angle as the exact double 0.7853262558535721.
                    const double spreadAngle = 0.7853262558535721;
                    velocity.X *= FUN_004CAD00(spreadAngle);
                    velocity.Y *= FUN_004CAD00(spreadAngle);
                    velocity.Z = FUN_004CACB0(spreadAngle) * preSpreadLength;
                    if (velocity.X == 0.0 && velocity.Y == 0.0 && velocity.Z == 0.0)
                        velocity.X = 100.0;
                    double finalLength = vectorView.FUN_0041C3C0();
                    double velocityScale = weapon->Speed / finalLength;
                    velocity.X *= velocityScale;
                    velocity.Y *= velocityScale;
                    velocity.Z *= velocityScale;
                    CoordStruct launchPosition = Location;
                    created->vf_124(launchPosition, velocity);
                    CoordStruct callbackPosition = Location;

                    // 46A887-46A8CC: read the flags at WeaponType+149/+151 at
                    // their respective use sites and reload Bullet.Owner for
                    // each call.  The first callback receives FirstObject,
                    // zero, WeaponType, and the cell coordinate; the second
                    // receives FirstObject, WeaponType, and the coordinate.
                    if (weapon->unknown_149 != 0 && Owner != 0)
                        Owner->FUN_006FD210(target, 0, weapon, &callbackPosition);
                    if (weapon->unknown_151 != 0 && Owner != 0)
                        Owner->FUN_006FD460(target, weapon, &callbackPosition);
                }
            }

            ++attempted;
            if (attempted == requested)
                return;
        }
    }

    // 46A92C-46A942: remaining requests use randomized cells around this
    // Bullet's virtual CellStruct position.
    int remaining = requested - attempted;
    while (remaining > 0) {
        CellStruct randomCell = vf_110();
        randomCell.X = static_cast<short>(
            randomCell.X + DAT_00A8B230->unknown_0218.RandomRanged(-2, 2));
        randomCell.Y = static_cast<short>(
            randomCell.Y + DAT_00A8B230->unknown_0218.RandomRanged(-2, 2));
        // Native 46A985-46A9B0 snapshots the setter inputs and Owner before
        // the Map lookup and CoCreateInstance calls.
        unsigned char spawnFlag = weapon->unknown_12F;
        TechnoClass* spawnOwner = Owner;
        int spawnDamage = weapon->Damage;
        int spawnSpeed = weapon->Speed;
        WarheadTypeClass* spawnWarhead = weapon->Warhead;
        CellClass* candidate = reinterpret_cast<CellClass*>(
            Map_0087F7E8.FUN_005657A0(&randomCell));

        // 46A985-46AA21: unlike the first pass, the random branch does not
        // filter an occupant or alliance.  COM failure still consumes one
        // remaining attempt.
        BulletClass* created = 0;
        HRESULT result = CoCreateInstance(
            (REFCLSID)DAT_007E96E0, 0, 7,
            (REFIID)DAT_007F7C90,
            reinterpret_cast<void**>(&created));
        if (result >= 0) {
            AbstractClass* target = candidate;
            created->FUN_004664C0(projectile, target, spawnOwner,
                                  spawnDamage, spawnWarhead, spawnSpeed,
                                  spawnFlag);

            // 46AA27-46AD29: the randomized-cell aim path uses the same
            // zero-vector yaw construction, then applies Speed normalization
            // before pitch correction and the fixed-angle transform.
            if (created != 0) {
                // Native 46AA61 repeats the cell lookup after the setter.
                CellClass* aimCell = reinterpret_cast<CellClass*>(
                    Map_0087F7E8.FUN_005657A0(&randomCell));
                CoordStruct sourcePosition = Location;
                CoordStruct targetPosition = aimCell->vf_18();
                double dx = static_cast<double>(targetPosition.X) - sourcePosition.X;
                double dy = static_cast<double>(targetPosition.Y) - sourcePosition.Y;
                short yaw = static_cast<short>(static_cast<int>(
                    (FUN_004CAE30(-dy, dx) - DAT_007E2820) * DAT_007E2818));
                BulletVelocity velocity;
                velocity.X = 0.0;
                velocity.Y = 0.0;
                velocity.Z = 0.0;
                if (velocity.X == 0.0 && velocity.Y == 0.0)
                    velocity.X = 100.0;
                double yawLength = FUN_004CAC40(
                    velocity.X * velocity.X + velocity.Y * velocity.Y);
                double yawRadians = (yaw - 0x3FFF) * DAT_007E2810;
                velocity.X = FUN_004CAD00(yawRadians) * yawLength;
                velocity.Y = -FUN_004CACB0(yawRadians) * yawLength;
                if (velocity.X == 0.0 && velocity.Y == 0.0 && velocity.Z == 0.0)
                    velocity.X = 100.0;
                double preScaleLength = FUN_004CAC40(
                    velocity.X * velocity.X + velocity.Y * velocity.Y +
                    velocity.Z * velocity.Z);
                double velocityScale = weapon->Speed / preScaleLength;
                velocity.X *= velocityScale;
                velocity.Y *= velocityScale;
                velocity.Z *= velocityScale;
                double planarLength =
                    reinterpret_cast<Vec3d&>(velocity).FUN_0041C350();
                short pitch = static_cast<short>(static_cast<int>(
                    (FUN_004CAE30(velocity.Z, planarLength) - DAT_007E2820) *
                     DAT_007E2818));
                double pitchRadians = (pitch - 0x3FFF) * DAT_007E2810;
                double preSpreadLength = FUN_004CAC40(
                    velocity.X * velocity.X + velocity.Y * velocity.Y +
                    velocity.Z * velocity.Z);
                if (pitchRadians != 0.0) {
                    velocity.X /= FUN_004CAD00(pitchRadians);
                    velocity.Y /= FUN_004CAD00(pitchRadians);
                }
                const double spreadAngle = 0.7853262558535721;
                velocity.X *= FUN_004CAD00(spreadAngle);
                velocity.Y *= FUN_004CAD00(spreadAngle);
                velocity.Z = FUN_004CACB0(spreadAngle) * preSpreadLength;
                CoordStruct launchPosition = Location;
                    created->vf_124(launchPosition, velocity);
                    CoordStruct callbackPosition = Location;

                // 46AD37-46ADB9: both callbacks are conditional on the
                // corresponding WeaponType byte and a non-null reloaded
                // Bullet.Owner.  The first Map lookup's returned CellClass*
                // is argument 1 at 46AD81; the second is argument 1 at
                // 46ADB9.  Neither argument is an assumed FirstObject.
                if (weapon->unknown_149 != 0 && Owner != 0) {
                    CellClass* callbackCell = reinterpret_cast<CellClass*>(
                        Map_0087F7E8.FUN_005657A0(&randomCell));
                    Owner->FUN_006FD210(callbackCell, 0, weapon, &callbackPosition);
                }
                if (weapon->unknown_151 != 0 && Owner != 0) {
                    CellClass* callbackCell = reinterpret_cast<CellClass*>(
                        Map_0087F7E8.FUN_005657A0(&randomCell));
                    Owner->FUN_006FD460(callbackCell, weapon, &callbackPosition);
                }
            }
        }
        --remaining;
    }
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
    if (count == 0)
        delete this;
    return count;
}

// SYNTHETIC: GAMEMD 0x46B990 -- compiler-generated BulletClass AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x46B9A0 -- compiler-generated BulletClass Release adjustor thunk.

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
