// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Existing matched Matrix3D members, consolidated without body rewrites.
// Native entry addresses remain annotated below; original TU attribution is unknown.

#include "../_layout/matrix3d.h"
#include "../renderer/matrix3d_rotate_methods.h"
#include <math.h>

// Existing runtime call used by the heading methods; source body unchanged.
extern "C" double __cdecl FUN_004CAE30(double y, double x);

GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 0 == 0x00);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 1 == 0x04);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 2 == 0x08);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 3 == 0x0C);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 0 == 0x10);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 1 == 0x14);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 2 == 0x18);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 3 == 0x1C);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 0 == 0x20);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 1 == 0x24);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 2 == 0x28);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 3 == 0x2C);

static inline void RotateRowsX(Matrix3D* m, float Sin, float Cos)
{
    float b, c;

    b = m->Row[0][1];
    c = m->Row[0][2];
    m->Row[0][1] = b * Cos + c * Sin;
    m->Row[0][2] = c * Cos - b * Sin;

    b = m->Row[1][1];
    c = m->Row[1][2];
    m->Row[1][1] = b * Cos + c * Sin;
    m->Row[1][2] = c * Cos - b * Sin;

    b = m->Row[2][1];
    c = m->Row[2][2];
    m->Row[2][1] = b * Cos + c * Sin;
    m->Row[2][2] = c * Cos - b * Sin;
}

static inline void RotateRowsY(Matrix3D* m, float Sin, float Cos)
{
    float a, c;

    a = m->Row[0][0];
    c = m->Row[0][2];
    m->Row[0][0] = a * Cos - c * Sin;
    m->Row[0][2] = c * Cos + a * Sin;

    a = m->Row[1][0];
    c = m->Row[1][2];
    m->Row[1][0] = a * Cos - c * Sin;
    m->Row[1][2] = c * Cos + a * Sin;

    a = m->Row[2][0];
    c = m->Row[2][2];
    m->Row[2][0] = a * Cos - c * Sin;
    m->Row[2][2] = c * Cos + a * Sin;
}

static inline void RotateRowsZ(Matrix3D* m, float Sin, float Cos)
{
    float a, b;

    a = m->Row[0][0];
    b = m->Row[0][1];
    m->Row[0][0] = b * Sin + a * Cos;
    m->Row[0][1] = b * Cos - a * Sin;

    a = m->Row[1][0];
    b = m->Row[1][1];
    m->Row[1][0] = b * Sin + a * Cos;
    m->Row[1][1] = b * Cos - a * Sin;

    a = m->Row[2][0];
    b = m->Row[2][1];
    m->Row[2][0] = b * Sin + a * Cos;
    m->Row[2][1] = b * Cos - a * Sin;
}

static inline void TranslateRowsX(Matrix3D* m, float x)
{
    m->Row[0][3] += x * m->Row[0][0];
    m->Row[1][3] += x * m->Row[1][0];
    m->Row[2][3] += x * m->Row[2][0];
}

static inline void TranslateRowsY(Matrix3D* m, float y)
{
    m->Row[0][3] += y * m->Row[0][1];
    m->Row[1][3] += y * m->Row[1][1];
    m->Row[2][3] += y * m->Row[2][1];
}

static inline void TranslateRowsZ(Matrix3D* m, float z)
{
    m->Row[0][3] += z * m->Row[0][2];
    m->Row[1][3] += z * m->Row[1][2];
    m->Row[2][3] += z * m->Row[2][2];
}

// Native 0x5AE610 copies twelve dwords from the stack source to ECX,
// returns ECX in EAX and uses RET 4. The placeholder does not assert
// constructor versus assignment identity.
// FUNCTION: GAMEMD 0x5AE610
Matrix3D& Matrix3D::FUN_005AE610(const Matrix3D& source)
{
    *this = source;
    return *this;
}

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

// FUNCTION: GAMEMD 0x5AE8F0
//
// Post-multiplies the affine transform by a translation: the translation column
// Row[i][3] gains vec.X * Row[i][0] + vec.Y * Row[i][1] + vec.Z * Row[i][2].
// Phrased as the three per-axis translations in sequence, which is what the
// retail bytes are: each axis loads its component once, and the running
// Row[i][3] values are kept in two spill slots plus the x87 stack between axes.
void Matrix3D::Translate(const Vector3D& vec)
{
    TranslateRowsX(this, vec.X);
    TranslateRowsY(this, vec.Y);
    TranslateRowsZ(this, vec.Z);
}

// FUNCTION: GAMEMD 0x5AE980  (__thiscall)
// Post-translate along local X: each row's translation gains x * its col0.
void Matrix3D::TranslateX(float x)
{
    Row[0][3] += x * Row[0][0];
    Row[1][3] += x * Row[1][0];
    Row[2][3] += x * Row[2][0];
}

// FUNCTION: GAMEMD 0x5AE9B0  (__thiscall)
void Matrix3D::TranslateY(float y)
{
    Row[0][3] += y * Row[0][1];
    Row[1][3] += y * Row[1][1];
    Row[2][3] += y * Row[2][1];
}

// FUNCTION: GAMEMD 0x5AE9E0  (__thiscall)
void Matrix3D::TranslateZ(float z)
{
    Row[0][3] += z * Row[0][2];
    Row[1][3] += z * Row[1][2];
    Row[2][3] += z * Row[2][2];
}

// FUNCTION: GAMEMD 0x5AEA10  (__thiscall)
// Uniform scale of the 3x3 rotation block, evaluated column-major
// (col0 rows 0..2, col1 rows 0..2, col2 rows 0..2). Translation untouched.
void Matrix3D::Scale(float factor)
{
    Row[0][0] *= factor;
    Row[1][0] *= factor;
    Row[2][0] *= factor;
    Row[0][1] *= factor;
    Row[1][1] *= factor;
    Row[2][1] *= factor;
    Row[0][2] *= factor;
    Row[1][2] *= factor;
    Row[2][2] *= factor;
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

// FUNCTION: GAMEMD 0x5AEAD0  (__thiscall)
// Scale the local X axis: multiply column 0 of every row by x in place.
// Retail is fully unrolled x87: FLD x / FMUL [col0] / FSTP [col0] x3.
void Matrix3D::ScaleX(float x)
{
    Row[0][0] *= x;
    Row[1][0] *= x;
    Row[2][0] *= x;
}

// FUNCTION: GAMEMD 0x5AEAF0  (__thiscall)
// Scale the local Y axis: multiply column 1 of every row by y in place.
void Matrix3D::ScaleY(float y)
{
    Row[0][1] *= y;
    Row[1][1] *= y;
    Row[2][1] *= y;
}

// FUNCTION: GAMEMD 0x5AEB20  (__thiscall)
// Scale the local Z axis: multiply column 2 of every row by z in place.
void Matrix3D::ScaleZ(float z)
{
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

// FUNCTION: GAMEMD 0x5AEC40
// Rotate the Y and Z rows into each other by an angle in radians.
void Matrix3D::PreRotateX(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);

    float ns = -s;
    float a0 = Row[1][0];
    float a1 = Row[1][1];
    float a2 = Row[1][2];
    float a3 = Row[1][3];
    float b0 = Row[2][0];
    float b1 = Row[2][1];
    float b2 = Row[2][2];
    float b3 = Row[2][3];
    Row[1][0] = a0 * c + b0 * ns;
    Row[1][1] = a1 * c + b1 * ns;
    Row[1][2] = a2 * c + b2 * ns;
    Row[1][3] = a3 * c + b3 * ns;
    Row[2][0] = a0 * s + b0 * c;
    Row[2][1] = a1 * s + b1 * c;
    Row[2][2] = a2 * s + b2 * c;
    Row[2][3] = a3 * s + b3 * c;
}

// FUNCTION: GAMEMD 0x5AEE50
// Rotate the X and Y rows into each other by an angle in radians.
void Matrix3D::PreRotateZ(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    float ns = -s;

    float a0 = Row[0][0];
    float a1 = Row[0][1];
    float a2 = Row[0][2];
    float a3 = Row[0][3];
    float b0 = Row[1][0];
    float b1 = Row[1][1];
    float b2 = Row[1][2];
    float b3 = Row[1][3];
    Row[0][0] = a0 * c + b0 * ns;
    Row[0][1] = a1 * c + b1 * ns;
    Row[0][2] = a2 * c + b2 * ns;
    Row[0][3] = a3 * c + b3 * ns;
    Row[1][0] = a0 * s + b0 * c;
    Row[1][1] = a1 * s + b1 * c;
    Row[1][2] = a2 * s + b2 * c;
    Row[1][3] = a3 * s + b3 * c;
}

// FUNCTION: GAMEMD 0x5AEF60
//
// Rotate about the local X axis by an angle in radians. The angle is widened
// to double once, both table-trig helpers are called on it, and the (Sin, Cos)
// body is expanded in place. The sine is spilled to a stack slot while the
// cosine, computed last, stays on the x87 stack.
void Matrix3D::RotateX(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    RotateRowsX(this, s, c);
}

// FUNCTION: GAMEMD 0x5AF000  (__thiscall)
// In-place rotation about the local X axis given pre-computed Sin/Cos, and the
// exact counterpart of RotateY below: it mixes the col1 (byte 0x04) and col2
// (byte 0x08) entries of each row, leaving col0 and the translation column
// alone. Retail is fully unrolled x87, three identical blocks.
//
// The parameter order was taken from the x87 trace, not assumed: the first
// argument is the one multiplied into the cross term, i.e. Sin, matching
// RotateY's (Sin, Cos) convention.
void Matrix3D::RotateX(float Sin, float Cos)
{
    float b, c;

    b = Row[0][1];
    c = Row[0][2];
    Row[0][1] = c * Sin + b * Cos;
    Row[0][2] = c * Cos - b * Sin;

    b = Row[1][1];
    c = Row[1][2];
    Row[1][1] = c * Sin + b * Cos;
    Row[1][2] = c * Cos - b * Sin;

    b = Row[2][1];
    c = Row[2][2];
    Row[2][1] = c * Sin + b * Cos;
    Row[2][2] = c * Cos - b * Sin;
}

// FUNCTION: GAMEMD 0x5AF080
//
// Rotate about the local Y axis by an angle in radians; same shape as RotateX.
void Matrix3D::RotateY(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    RotateRowsY(this, s, c);
}

// FUNCTION: GAMEMD 0x5AF120  (__thiscall)
// In-place rotation about the local Y axis given pre-computed Sin/Cos.
// For each of the 3 rows, mix the col0 (byte 0x00) and col2 (byte 0x08)
// entries; col1 and the translation column are untouched. Retail is fully
// unrolled x87 (FLD col0 / FLD col2 / dup-mul-subtract -> col0,
// dup-mul-add -> col2) three times.
void Matrix3D::RotateY(float Sin, float Cos)
{
    float a, c;

    a = Row[0][0];
    c = Row[0][2];
    Row[0][0] = a * Cos - c * Sin;
    Row[0][2] = c * Cos + a * Sin;

    a = Row[1][0];
    c = Row[1][2];
    Row[1][0] = a * Cos - c * Sin;
    Row[1][2] = c * Cos + a * Sin;

    a = Row[2][0];
    c = Row[2][2];
    Row[2][0] = a * Cos - c * Sin;
    Row[2][2] = c * Cos + a * Sin;
}

// FUNCTION: GAMEMD 0x5AF1A0
//
// Rotate about the local Z axis by an angle in radians. Unlike X and Y the
// cosine is fetched first here, so it is the sine that stays on the x87 stack.
void Matrix3D::RotateZ(float angle)
{
    float c = FUN_004CAD00(angle);
    float s = FUN_004CACB0(angle);
    RotateRowsZ(this, s, c);
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

// FUNCTION: GAMEMD 0x5AF410  (__thiscall)
// Transform the unit +Z axis (0,0,1) by this matrix, then return the heading
// angle about the local Y axis as atan2(result.X, result.Z). This mirrors the
// inlined operator*(Vector3D): { Vector3D ret; MatrixApply(&ret,this,&pt);
// return ret; }. Retail builds the {0,0,1} input on the stack, calls MatrixApply
// (0x5AFB80) into a temp, copies all three result components (the non-elided
// `return ret`), and tail-passes X then Z (promoted to double) to atan2
// (0x4CAE30), leaving the angle in ST0.
//
// MATCHED 100% (24/24 by diff_retail; raw bytes exact apart from the two
// relocated calls) with the plain copy `Vector3D res = *MatrixApply(...)`.
//
// FLOAT-CONSISTENCY FLAG (/Op): measured this pass and REFUTED for this
// function. /Op rounds every double-typed intermediate through memory, which
// is the shape retail sometimes shows, but adding it to this TU's flag line
// makes the score collapse rather than close: the five float-heavy partials
// were swept together under `/nologo /c /O2 /DNDEBUG /Gy /GX /Op` (the flags
// then in force, before /Gr and the removal of /GX) and scored
// GetYRotation 58.3%->8.0%, MatrixApply 72.1%->72.1%, FromAxis 85.9%->3.3%,
// FromQuaternion 19.8%->1.1% and DistanceFrom3D 92.9%->67.9%. Retail's x87
// code in this family is *not* /Op code; do not re-test the flag here.
double Matrix3D::GetYRotation() const
{
    Vector3D axis(0.0f, 0.0f, 1.0f);
    Vector3D tmp;
    Vector3D res = *MatrixApply(&tmp, this, &axis);
    return FUN_004CAE30(res.X, res.Z);
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

// FUNCTION: GAMEMD 0x5AFC20
//
// Inverse of a rigid transform: the 3x3 rotation block is transposed and the
// translation column becomes minus the transposed rotation applied to the
// original translation. The result is assembled in a stack local and block-
// copied into the caller's return buffer.
Matrix3D Matrix3D::TransposeMatrix(const Matrix3D& mat)
{
    Matrix3D t;

    t.Row[0][0] = mat.Row[0][0];
    t.Row[0][1] = mat.Row[1][0];
    t.Row[0][2] = mat.Row[2][0];
    t.Row[1][0] = mat.Row[0][1];
    t.Row[1][1] = mat.Row[1][1];
    t.Row[1][2] = mat.Row[2][1];
    t.Row[2][0] = mat.Row[0][2];
    t.Row[2][1] = mat.Row[1][2];
    t.Row[2][2] = mat.Row[2][2];

    t.Row[0][3] = -(t.Row[0][0] * mat.Row[0][3] + t.Row[0][2] * mat.Row[2][3] + t.Row[0][1] * mat.Row[1][3]);
    t.Row[1][3] = -(t.Row[1][0] * mat.Row[0][3] + t.Row[1][2] * mat.Row[2][3] + t.Row[1][1] * mat.Row[1][3]);
    t.Row[2][3] = -(t.Row[2][0] * mat.Row[0][3] + t.Row[2][2] * mat.Row[2][3] + t.Row[2][1] * mat.Row[1][3]);

    return t;
}
