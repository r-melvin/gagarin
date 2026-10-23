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


static inline float Element(const float* f, int n)
{
    return f[n];
}

