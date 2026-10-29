// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: the user's retail gamemd.exe v1.001 through the local Ghidra
//   CLI at 0x5B20F0. The body seats no vtable and has no runtime type
//   information to read, so every type below was recovered from the
//   instruction stream and cross-checked against the leaf helpers it calls.
//
// The run this belongs to is the flight/ballistics helper file that also holds
// the five Dir16 primitives at 0x5B2930..0x5B29C0
// (match/movement/dir16_operator_methods.*) and VelocityClass::SetPitch at
// 0x5B2A30 (match/movement/velocity_class_set_pitch_methods.*).
//
// Layouts, each offset read off a member access in the disassembly:
//
//   CoordStruct    int X +0x00, Y +0x04, Z +0x08          (0x0C bytes)
//       0x41C230 ctor(int,int,int)   `MOV [EAX],ECX / [EAX+4],EDX / [EAX+8],ECX`
//       0x437160 operator-           three dword subtractions into a hidden buffer
//       0x41C380 Length              `FILD [ECX+8] / [ECX+4] / [ECX]` + sqrt + ftol
//
//   Point2D        int X +0x00, Y +0x04                   (0x08 bytes)
//       0x487F20 operator-           two dword subtractions into a hidden buffer
//       0x4C1B50 Length              `FILD [ECX+4] / [ECX]` + sqrt + ftol
//
//   VelocityClass  double X +0x00, Y +0x08, Z +0x10       (0x18 bytes)
//       see velocity_class_set_pitch_methods.h for the same three offsets
//
// The Dir16 read at `MOV ECX, dword ptr [EDI]; SHR ECX,7; INC ECX; SHR ECX,1;
// AND ECX,0xFF` is the 16-to-8 bit binary-angle narrowing; cl widens the load
// to a dword because the trailing mask makes the upper half dead, so this is
// still the two-byte Raw member and not a four-byte one.
#ifndef GG_MATCH_MOVEMENT_FLIGHT_PATH_STEP_METHODS_H
#define GG_MATCH_MOVEMENT_FLIGHT_PATH_STEP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "dir16_operator_methods.h"

// Callees defined outside this translation unit carry a `// CALLEE:` marker
// rather than `// FUNCTION:`. They are declarations, not bodies, and claiming
// their retail addresses here would make two translation units claim one
// address -- 0x5B2A30 really is matched, in
// match/movement/velocity_class_set_pitch_methods.cpp.

// GLOBAL: GAMEMD 0x007E2800
extern const double GG_ZERO;
// GLOBAL: GAMEMD 0x007E2810
extern const double GG_DIR16_TO_RADIANS;
// GLOBAL: GAMEMD 0x007E2818
extern const double GG_RADIANS_TO_DIR16;
// GLOBAL: GAMEMD 0x007E2820
extern const double GG_QUARTER_TURN;

extern "C" {
double __cdecl gamemd_sqrt(double);                // Declaration: GAMEMD 0x004CAC40 (decl; reloc)
double __cdecl gamemd_sin(double);                 // LIBRARY: GAMEMD 0x004CACB0
double __cdecl gamemd_cos(double);                 // LIBRARY: GAMEMD 0x004CAD00
double __cdecl gamemd_atan2(double, double);       // LIBRARY: GAMEMD 0x004CAE30
}

// A Dir16 carrying only its Raw half, the shape retail builds wherever a
// constant or halved angle is handed to one of the Dir16 primitives: the word
// is written and the four-byte object is copied out whole, spare half and all.
inline Dir16 Dir16Raw(short raw)
{
    Dir16 result;

    result.Raw = raw;
    return result;
}

struct CoordStruct
{
    int X;  // +0x00
    int Y;  // +0x04
    int Z;  // +0x08

    // CALLEE: GAMEMD 0x0041C230
    CoordStruct(int x, int y, int z);
    // CALLEE: GAMEMD 0x00437160
    CoordStruct operator-(CoordStruct const& other) const;
    // CALLEE: GAMEMD 0x0041C380
    int Length() const;
};

GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x00 &&
                 offsetof(CoordStruct, Y) == 0x04 &&
                 offsetof(CoordStruct, Z) == 0x08 &&
                 sizeof(CoordStruct) == 0x0C);

#include "../_layout/geometry2d.h"

GG_STATIC_ASSERT(offsetof(Point2D, X) == 0x00 &&
                 offsetof(Point2D, Y) == 0x04 &&
                 sizeof(Point2D) == 0x08);

struct VelocityClass
{
    double X;  // +0x00
    double Y;  // +0x08
    double Z;  // +0x10

    VelocityClass() {}
    VelocityClass(double x, double y, double z) : X(x), Y(y), Z(z) {}

    // CALLEE: GAMEMD 0x0041C350
    double Length2D() const;
    // CALLEE: GAMEMD 0x0041C430  (retail carries a second, byte-identical copy)
    double FlatSpeed() const;
    // CALLEE: GAMEMD 0x0041C3C0
    double Length() const;
    // CALLEE: GAMEMD 0x0041C2E0
    Dir16 GetPitch() const;
    // CALLEE: GAMEMD 0x0041C460
    void ClearDegenerate();
    // CALLEE: GAMEMD 0x005B2A30
    void SetPitch(Dir16 const& pitch);

    // Inlined at every use site in 0x5B20F0: the same elevation angle GetPitch
    // returns, but spelled through the out-of-line Length2D rather than with
    // the square root expanded, which is how the two copies differ.
    Dir16 PitchFromComponents() const;
};

GG_STATIC_ASSERT(offsetof(VelocityClass, X) == 0x00 &&
                 offsetof(VelocityClass, Y) == 0x08 &&
                 offsetof(VelocityClass, Z) == 0x10 &&
                 sizeof(VelocityClass) == 0x18);

inline Dir16 VelocityClass::PitchFromComponents() const
{
    Dir16 result;

    result.Raw = (short)(long)((gamemd_atan2(this->Z, this->Length2D()) - GG_QUARTER_TURN) *
                               GG_RADIANS_TO_DIR16);
    return result;
}

class CellView_005B20F0
{
public:
    char unknown_00[0x140];  // +0x000
    unsigned int Flags;      // +0x140
};

GG_STATIC_ASSERT(offsetof(CellView_005B20F0, Flags) == 0x140);

class MapClass
{
public:
    // CALLEE: GAMEMD 0x00578080
    int GetZPos(CoordStruct const* where) const;
    // CALLEE: GAMEMD 0x00565730
    CellView_005B20F0* GetTargetCell(CoordStruct const* where);
};

// GLOBAL: GAMEMD 0x0087F7E8
extern MapClass MapClass_Instance;
// GLOBAL: GAMEMD 0x00ABEF10
extern CoordStruct GG_UnsetCoord;
// GLOBAL: GAMEMD 0x00ABEF44
extern int GG_BridgeRise;
// GLOBAL: GAMEMD 0x00ABEF50
extern int GG_LevelHeight;

// FUNCTION: GAMEMD 0x005B20F0
int FlightPathStep(CoordStruct* coord, VelocityClass* velocity,
                   CoordStruct const* target, Dir16 const* turnRate,
                   char holdCourse, char isMissile, char isFast,
                   char freezePitch);

#endif  // GG_MATCH_MOVEMENT_FLIGHT_PATH_STEP_METHODS_H
