// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 3x4 row-major float affine transform: Row[i][0..2] is the rotation/scale
// 3x3 and Row[i][3] the translation column, flat at offset 0 (no base, no
// vtable). MakeIdentity 0x5AE860 writes 1.0f at +0x00/+0x14/+0x28 and 0.0f in
// the other nine dwords; every by-value copy in retail is a 12-dword REP MOVSD
// (0x55A730, 0x7559B0, 0x646980).
//
// The user-declared constructor makes the type non-POD: retail hands the
// hidden return slot of the __stdcall locomotor matrix methods (0x55A730,
// 0x4CF610) over as the argument after `this` and returns it in EAX, which
// VC6 only does for a non-POD result.
//
// Every member below is out of line in retail: callers outside the matrix
// block CALL 0x5AE860/0x5AE980/0x5AEF60/0x5AF080/0x5AF1A0/0x5AFB80, and
// 0x5AF550 calls RotateX(Sin, Cos) 0x5AF000 and RotateY(Sin, Cos) 0x5AF120.
#ifndef GG_MATCH_LAYOUT_MATRIX3D_H
#define GG_MATCH_LAYOUT_MATRIX3D_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector3d.h"
#include "quaternion.h"

struct Matrix3D
{
    float Row[3][4];   // +0x00, row stride 0x10

    Matrix3D() {}
    // 0x5AE630: out of line in retail.
    Matrix3D(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23);
    // 0x5AE690: rows 0..2 from x/y/z axis vectors, translation column from t.
    Matrix3D(const Vector3D& x, const Vector3D& y, const Vector3D& z, const Vector3D& t);

    // Native 0x5AE5E0 copies the twelve contiguous scalar components.
    // Placeholder avoids asserting constructor versus assignment identity.
    Matrix3D& FUN_005AE5E0(const Matrix3D& source);

    // Native 0x5AE610: copy twelve dwords from source, returning this.
    // A placeholder avoids asserting constructor versus assignment identity.
    Matrix3D& FUN_005AE610(const Matrix3D& source);

    void MakeIdentity();                                  // 0x5AE860
    void Translate(float x, float y, float z);            // 0x5AE890
    void Translate(const Vector3D& vec);                  // 0x5AE8F0
    void TranslateX(float x);                             // 0x5AE980
    void TranslateY(float y);                             // 0x5AE9B0
    void TranslateZ(float z);                             // 0x5AE9E0
    void Scale(float factor);                             // 0x5AEA10
    void ScaleX(float x);                                 // 0x5AEAD0
    void ScaleY(float y);                                 // 0x5AEAF0
    void ScaleZ(float z);                                 // 0x5AEB20
    void RotateX(float angle);                            // 0x5AEF60
    void RotateX(float Sin, float Cos);                   // 0x5AF000
    void RotateY(float angle);                            // 0x5AF080
    void RotateY(float Sin, float Cos);                   // 0x5AF120
    void RotateZ(float angle);                            // 0x5AF1A0
    double GetYRotation() const;                          // 0x5AF410
    void FUN_005AF710(const Vector3D& from, const Vector3D& to, float roll);
    // result = mat * vec; result in ECX, matrix in EDX, vector on the stack.
    static Vector3D* MatrixApply(Vector3D* ret, const Matrix3D* mat,
                                 const Vector3D* vec);    // 0x5AFB80
    static Matrix3D TransposeMatrix(const Matrix3D& mat); // 0x5AFC20
    static Quaternion FromAxis(const Vector3D& axis, float angle); // 0x646480
    static Matrix3D FromQuaternion(const Quaternion& q);  // 0x646980
    void Scale(float x, float y, float z);                // 0x5AEA70
    void Shear0(float a, float b);                        // 0x5AEB50
    void Shear2(float a, float b);                        // 0x5AEBA0
    void Shear1(float a, float b);                        // 0x5AEBF0
    void RotateZ(float Sin, float Cos);                   // 0x5AF240
    float GetTransX();                                    // 0x5AF2C0
    float GetTransY();                                    // 0x5AF310
    float GetTransZ();                                    // 0x5AF360
    double GetAxisHeading();                              // 0x5AF3B0
    double GetAxisHeadingX();                             // 0x5AF470
    Vector3D* RotateVector(Vector3D* out, const Vector3D* in);   // 0x5AF4D0
};
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);
GG_STATIC_ASSERT(sizeof(((Matrix3D*)0)->Row[0]) == 0x10);
GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);

#endif  // GG_MATCH_LAYOUT_MATRIX3D_H
