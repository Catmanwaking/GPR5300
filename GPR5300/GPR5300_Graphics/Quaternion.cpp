#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion(Vector3 euler)
{
    FLOAT rollCos = cosf(euler.z * 0.5f);
    FLOAT rollSin = sinf(euler.z * 0.5f);

    FLOAT pitchCos = cosf(euler.x * 0.5f);
    FLOAT pitchSin = sinf(euler.x * 0.5f);

    FLOAT yawCos = cosf(euler.y * 0.5f);
    FLOAT yawSin = sinf(euler.y * 0.5f);

    w = pitchCos * yawCos * rollCos + pitchSin * yawSin * rollSin;
    x = pitchSin * yawCos * rollCos - pitchCos * yawSin * rollSin;
    y = pitchCos * yawSin * rollCos + pitchSin * yawCos * rollSin;
    z = pitchCos * yawCos * rollSin - pitchSin * yawSin * rollCos;
}

FLOAT Quaternion::Magnitude() const
{
    return sqrtf(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::Conjugation() const
{     
    return Quaternion(w,-x,-y,-z);
}

void Quaternion::Conjugate()
{
    x *= -1.0f;
    y *= -1.0f;
    z *= -1.0f;
}

Quaternion Quaternion::Normalized() const
{
    Quaternion q = {w,x,y,z};
    q.Normalize();
    return q;
}

void Quaternion::Normalize()
{
    (*this) *= 1 / Magnitude();
}

void Quaternion::RotateAround(Vector3 axis, FLOAT angle)
{
    float factor = sinf(angle * 0.5f);

    Quaternion rotation;
    rotation.x = axis.x * factor;
    rotation.y = axis.y * factor;
    rotation.z = axis.z * factor;
    rotation.w = cos(angle * 0.5f);

    (*this) = rotation.Normalized() * (*this);
    Normalize();
}

Quaternion Quaternion::operator*(FLOAT scalar)
{
    Quaternion q;
    q.w = w * scalar;
    q.x = x * scalar;
    q.y = y * scalar;
    q.z = z * scalar;
    return q;
}

void Quaternion::operator*=(FLOAT scalar)
{
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

Quaternion Quaternion::operator*(const Quaternion q)
{
    Quaternion rotation;
    rotation.w = w * q.w - x * q.x - y * q.y - z * q.z; //TODO check validity of function
    rotation.x = w * q.x + x * q.w + y * q.z - z * q.y;
    rotation.y = w * q.y - x * q.z + y * q.w + z * q.x;
    rotation.z = w * q.z + x * q.y - y * q.x + z * q.w;
    return rotation;
}

void Quaternion::operator*=(const Quaternion q)
{
    w = w * q.w - x * q.x - y * q.y - z * q.z;
    x = w * q.x + x * q.w + y * q.z - z * q.y;
    y = w * q.y - x * q.z + y * q.w + z * q.x;
    z = w * q.z + x * q.y - y * q.x + z * q.w;
}

Vector3 Quaternion::operator*(const Vector3 v)
{
    Quaternion vector = { 0.0f, v.x, v.y, v.z };
    Quaternion eq = (*this) * vector * Conjugation();
    return Vector3(eq.x, eq.y, eq.z);
}
