// Provenance: own-binary-via-Ghidra
//   Shapes read off retail gamemd.exe v1.001 at 0x646480..0x646A75: every
//   function is __fastcall with the hidden result pointer in ECX and the first
//   reference argument in EDX. Quaternion is four floats {X, Y, Z, W}
//   (0x646730 / 0x646590 seed a local at +0/+4/+8/+0xC with 0,0,0,1.0f and
//   copy it out with four dword moves); Matrix3D is the 3x4 row-major float
//   block (0x646730 reads +0x00/+0x14/+0x28 as its diagonal).
#ifndef GG_MATCH_RENDERER_QUATERNION_MATRIX_METHODS_H
#define GG_MATCH_RENDERER_QUATERNION_MATRIX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt(double).
extern "C" double __cdecl FUN_004CAC40(double v);
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) -- sin(double).
extern "C" double __cdecl FUN_004CACB0(double angle);
// FUNCTION: GAMEMD 0x4CAD00 (decl; reloc) -- cos(double).
extern "C" double __cdecl FUN_004CAD00(double angle);
// FUNCTION: GAMEMD 0x4CADB0 (decl; reloc) -- acos(double).
extern "C" double __cdecl FUN_004CADB0(double v);
// FUNCTION: GAMEMD 0x4CAE30 (decl; reloc) -- atan2(double y, double x).
extern "C" double __cdecl FUN_004CAE30(double y, double x);

struct Vector3
{
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08

    Vector3() {}
    Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
};
GG_STATIC_ASSERT(offsetof(Vector3, Z) == 0x8);

struct Quaternion
{
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08
    float W;   // +0x0C

    Quaternion() {}
    Quaternion(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
    float& operator[](int i) { return (&X)[i]; }
    const float& operator[](int i) const { return (&X)[i]; }
};
GG_STATIC_ASSERT(offsetof(Quaternion, W) == 0xC);

struct Matrix3D
{
    float Row[3][4];   // +0x0000

    Matrix3D() {}
    Matrix3D(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23)
    {
        Row[0][0] = m00; Row[0][1] = m01; Row[0][2] = m02; Row[0][3] = m03;
        Row[1][0] = m10; Row[1][1] = m11; Row[1][2] = m12; Row[1][3] = m13;
        Row[2][0] = m20; Row[2][1] = m21; Row[2][2] = m22; Row[2][3] = m23;
    }

    void FUN_005AF710(const Vector3& from, const Vector3& to, float roll);
    static Quaternion __fastcall FromAxis(const Vector3& axis, float angle);
    static Matrix3D __fastcall FromQuaternion(const Quaternion& q);
};
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);

Quaternion __fastcall FUN_00646590(const Quaternion& a, const Quaternion& b, float t);
Quaternion __fastcall FUN_00646730(const Matrix3D& m);

#endif
