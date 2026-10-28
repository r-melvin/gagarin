// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below.

#include "../_layout/matrix3d.h"

// FUNCTION: GAMEMD 0x5AE630
// Build the matrix from twelve components in row-major order.
Matrix3D::Matrix3D(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23)
{
    Row[0][0] = m00; Row[0][1] = m01; Row[0][2] = m02; Row[0][3] = m03;
    Row[1][0] = m10; Row[1][1] = m11; Row[1][2] = m12; Row[1][3] = m13;
    Row[2][0] = m20; Row[2][1] = m21; Row[2][2] = m22; Row[2][3] = m23;
}

// FUNCTION: GAMEMD 0x5AE690
// Build the matrix from three axis vectors (one per row) and a translation.
Matrix3D::Matrix3D(const Vector3D& x, const Vector3D& y, const Vector3D& z, const Vector3D& t)
{
    Row[0][0] = x.X; Row[0][1] = x.Y; Row[0][2] = x.Z; Row[0][3] = t.X;
    Row[1][0] = y.X; Row[1][1] = y.Y; Row[1][2] = y.Z; Row[1][3] = t.Y;
    Row[2][0] = z.X; Row[2][1] = z.Y; Row[2][2] = z.Z; Row[2][3] = t.Z;
}

// FUNCTION: GAMEMD 0x5AEA70
// Scale the three columns of the rotation block by x, y and z.
void Matrix3D::Scale(float x, float y, float z)
{
    Row[0][0] *= x;
    Row[1][0] *= x;
    Row[2][0] *= x;
    Row[0][1] *= y;
    Row[1][1] *= y;
    Row[2][1] *= y;
    Row[0][2] *= z;
    Row[1][2] *= z;
    Row[2][2] *= z;
}

// FUNCTION: GAMEMD 0x5AEB50
void Matrix3D::Shear0(float a, float b)
{
    Row[0][0] += a * Row[0][1] + b * Row[0][2];
    Row[1][0] += a * Row[1][1] + b * Row[1][2];
    Row[2][0] += a * Row[2][1] + b * Row[2][2];
}

// FUNCTION: GAMEMD 0x5AEBA0
void Matrix3D::Shear2(float a, float b)
{
    Row[0][2] += b * Row[0][1] + a * Row[0][0];
    Row[1][2] += a * Row[1][0] + b * Row[1][1];
    Row[2][2] += a * Row[2][0] + b * Row[2][1];
}

// FUNCTION: GAMEMD 0x5AEBF0
void Matrix3D::Shear1(float a, float b)
{
    Row[0][1] += b * Row[0][2] + a * Row[0][0];
    Row[1][1] += a * Row[1][0] + b * Row[1][2];
    Row[2][1] += a * Row[2][0] + b * Row[2][2];
}

// FUNCTION: GAMEMD 0x5AF240
// Rotate about the local Z axis with a precomputed sine and cosine.
void Matrix3D::RotateZ(float Sin, float Cos)
{
    float a, b;

    a = Row[0][0];
    b = Row[0][1];
    Row[0][0] = b * Sin + a * Cos;
    Row[0][1] = b * Cos - a * Sin;

    a = Row[1][0];
    b = Row[1][1];
    Row[1][0] = b * Sin + a * Cos;
    Row[1][1] = b * Cos - a * Sin;

    a = Row[2][0];
    b = Row[2][1];
    Row[2][0] = b * Sin + a * Cos;
    Row[2][1] = b * Cos - a * Sin;
}

// FUNCTION: GAMEMD 0x5AF2C0
// X of the matrix applied to the origin (the translation column).
float Matrix3D::GetTransX()
{
    Vector3D origin(0.0f, 0.0f, 0.0f);
    Vector3D tmp;
    Vector3D r = *MatrixApply(&tmp, this, &origin);
    return r.X;
}

// FUNCTION: GAMEMD 0x5AF310
float Matrix3D::GetTransY()
{
    Vector3D origin(0.0f, 0.0f, 0.0f);
    Vector3D tmp;
    Vector3D r = *MatrixApply(&tmp, this, &origin);
    return r.Y;
}

// FUNCTION: GAMEMD 0x5AF360
float Matrix3D::GetTransZ()
{
    Vector3D origin(0.0f, 0.0f, 0.0f);
    Vector3D tmp;
    Vector3D r = *MatrixApply(&tmp, this, &origin);
    return r.Z;
}

extern "C" double __cdecl FUN_004CAE30(double y, double x);

// FUNCTION: GAMEMD 0x5AF3B0
// Heading of the matrix's local Y axis: arctangent of the transformed
// (0, 1, 0) direction's Z over its Y.
double Matrix3D::GetAxisHeading()
{
    Vector3D unitY(0.0f, 1.0f, 0.0f);
    Vector3D tmp;
    Vector3D r = *MatrixApply(&tmp, this, &unitY);
    return FUN_004CAE30(r.Z, r.Y);
}

// FUNCTION: GAMEMD 0x5AF470
// Heading of the matrix's local X axis: arctangent of the transformed
// (1, 0, 0) direction's Y over its X.
double Matrix3D::GetAxisHeadingX()
{
    Vector3D unitX(1.0f, 0.0f, 0.0f);
    Vector3D tmp;
    Vector3D r = *MatrixApply(&tmp, this, &unitX);
    return FUN_004CAE30(r.Y, r.X);
}

// FUNCTION: GAMEMD 0x5AF4D0
// Rotate a vector by the 3x3 block alone (no translation).
Vector3D* Matrix3D::RotateVector(Vector3D* out, const Vector3D* in)
{
    Vector3D r;
    r.X = Row[0][1] * in->Y + Row[0][2] * in->Z + in->X * Row[0][0];
    r.Y = Row[1][1] * in->Y + Row[1][0] * in->X + Row[1][2] * in->Z;
    r.Z = Row[2][1] * in->Y + Row[2][0] * in->X + Row[2][2] * in->Z;
    *out = r;
    return out;
}
