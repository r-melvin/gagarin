// Provenance: own-binary-via-Ghidra | YRpp-cross-check

#include "quaternion_matrix_methods.h"

// Scale each component; the divisor is taken by value.
static inline Vector3D Divide(const Vector3D& a, double d)
{
    return Vector3D(a.X / d, a.Y / d, a.Z / d);
}

// FUNCTION: GAMEMD 0x5AF710
// Orient the matrix at `from` looking toward `to`, rolled by `roll`: the
// yaw/pitch of the direction and the roll give the second column, the unit
// direction is the third, their cross product the first, `from` the fourth.
void Matrix3D::FUN_005AF710(const Vector3D& from, const Vector3D& to, float roll)
{
    Vector3D d(to.X - from.X, to.Y - from.Y, to.Z - from.Z);
    float yaw;
    if (d.Y == 0.0f && d.X == 0.0f) {
        yaw = 0.0f;
    } else {
        yaw = (float)FUN_004CAE30(d.Y, d.X);
    }
    float pitch = (float)FUN_004CAE30(-d.Z, FUN_004CAC40(d.Y * d.Y + d.X * d.X));

    float cy = (float)FUN_004CAD00(yaw);
    float sy = (float)FUN_004CACB0(yaw);
    float cp = (float)FUN_004CAD00(pitch);
    float sp = (float)FUN_004CACB0(pitch);
    float cr = (float)FUN_004CAD00(roll);
    float sr = (float)FUN_004CACB0(roll);

    Vector3D up(cr * sp * cy + sr * sy, cr * sp * sy - sr * cy, cr * cp);

    double len = FUN_004CAC40(d.X * d.X + d.Y * d.Y + d.Z * d.Z);
    Vector3D n;
    if (len != 0.0) {
        n = Divide(d, len);
    } else {
        n = d;
    }

    Vector3D x(n.Y * up.Z - up.Y * n.Z, up.X * n.Z - n.X * up.Z, up.Y * n.X - up.X * n.Y);
    Row[0][0] = x.X;
    Row[0][1] = up.X;
    Row[0][2] = n.X;
    Row[0][3] = from.X;
    Row[1][0] = x.Y;
    Row[1][1] = up.Y;
    Row[1][2] = n.Y;
    Row[1][3] = from.Y;
    Row[2][0] = x.Z;
    Row[2][1] = up.Z;
    Row[2][2] = n.Z;
    Row[2][3] = from.Z;
}

// FUNCTION: GAMEMD 0x646590
// Spherical interpolation from a to b by t. Nearly-parallel inputs fall back
// to linear weights; opposite inputs use quarter-turn sine weights.
Quaternion FUN_00646590(const Quaternion& a, const Quaternion& b, float t)
{
    Quaternion r;
    r.X = 0.0f;
    r.Y = 0.0f;
    r.Z = 0.0f;
    r.W = 1.0f;

    double cosAngle = a.W * b.W + a.Z * b.Z + a.Y * b.Y + a.X * b.X;
    double weightA;
    double weightB;
    int i;
    if (1.0 + cosAngle > 1e-5) {
        double rc = 1.0 - cosAngle;
        if (rc > 1e-5) {
            double angle = FUN_004CADB0(cosAngle);
            double sinAngle = FUN_004CACB0(angle);
            weightA = FUN_004CACB0((1.0f - t) * angle) / sinAngle;
            weightB = FUN_004CACB0(t * angle) / sinAngle;
        } else {
            weightA = 1.0f - t;
            weightB = t;
        }
        for (i = 0; i < 4; i++) {
            r[i] = b[i] * weightB + a[i] * weightA;
        }
    } else {
        weightA = FUN_004CACB0((1.0f - t) * 1.570796326794895);
        weightB = FUN_004CACB0(t * 1.570796326794895);
        for (i = 0; i < 4; i++) {
            r[i] = b[i] * weightB + a[i] * weightA;
        }
    }
    return r;
}

static inline float Element(const float* f, int n)
{
    return f[n];
}

// FUNCTION: GAMEMD 0x646730
// Rotation matrix to quaternion via the trace, or via the largest diagonal
// element when the trace is not positive. A zero trace returns identity.
Quaternion FUN_00646730(const Matrix3D& m)
{
    Quaternion q(0.0f, 0.0f, 0.0f, 1.0f);
    int diag[3] = {0, 5, 10};
    int idx[3][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};
    const float* f = &m.Row[0][0];

    double tr = f[0] + f[5] + f[10];
    if (tr == 0.0) {
        return q;
    }
    if (tr > 0.0) {
        double s = FUN_004CAC40(tr + 1.0);
        q.W = (float)(s * 0.5);
        s = 0.5 / s;
        q.X = (float)((m.Row[2][1] - m.Row[1][2]) * s);
        q.Y = (float)((m.Row[0][2] - m.Row[2][0]) * s);
        q.Z = (float)((m.Row[1][0] - m.Row[0][1]) * s);
    } else {
        int i = 0;
        if (Element(f, diag[1]) > Element(f, diag[0])) {
            i = 1;
        }
        if (Element(f, diag[2]) > Element(f, diag[i])) {
            i = 2;
        }
        int j;
        int k;
        switch (i) {
        case 1:
            j = 2;
            k = 0;
            break;
        case 2:
            j = 0;
            k = 1;
            break;
        default:
            j = 1;
            k = 2;
            break;
        }
        double s = FUN_004CAC40(Element(f, diag[i]) - (Element(f, diag[j]) + Element(f, diag[k])) + 1.0);
        q[i] = (float)(s * 0.5);
        s = 0.5 / s;
        q.W = (float)((f[idx[k][j]] - f[idx[j][k]]) * s);
        q[j] = (float)((f[idx[j][i]] + f[idx[i][j]]) * s);
        q[k] = (float)((f[idx[k][i]] + f[idx[i][k]]) * s);
    }
    return q;
}

// FUNCTION: GAMEMD 0x646980
// Rotation matrix of a unit quaternion; the fourth column is zero.
Matrix3D Matrix3D::FromQuaternion(const Quaternion& q)
{
    return Matrix3D(
        1.0f - 2.0f * (q.Y * q.Y + q.Z * q.Z),
        2.0f * (q.X * q.Y - q.W * q.Z),
        2.0f * (q.X * q.Z + q.W * q.Y),
        0.0f,
        2.0f * (q.X * q.Y + q.W * q.Z),
        1.0f - 2.0f * (q.X * q.X + q.Z * q.Z),
        2.0f * (q.Y * q.Z - q.W * q.X),
        0.0f,
        2.0f * (q.X * q.Z - q.W * q.Y),
        2.0f * (q.Y * q.Z + q.W * q.X),
        1.0f - 2.0f * (q.X * q.X + q.Y * q.Y),
        0.0f);
}
