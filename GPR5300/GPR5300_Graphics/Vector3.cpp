#include "Vector3.h"

FLOAT Vector3::Length()
{
    return sqrtf(LengthSqr());
}

FLOAT Vector3::LengthSqr()
{
    return x * x + y * y + z * z;
}

void Vector3::Normalize()
{
    FLOAT length = Length();
    if (length == 0.0f) return;
    (*this) *= (1 / length);
}

Vector3 Vector3::operator*(FLOAT scalar)
{
    Vector3 left;
    left.x = x * scalar;
    left.y = y * scalar;
    left.z = z * scalar;
    return left;
}

void Vector3::operator*=(FLOAT scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

Vector3 Vector3::operator+(Vector3 v)
{
    Vector3 left;
    left.x = x + v.x;
    left.y = y + v.y;
    left.z = z + v.z;
    return left;
}

void Vector3::operator+=(Vector3 v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector3 Vector3::operator-(Vector3 v)
{
    Vector3 left;
    left.x = x - v.x;
    left.y = y - v.y;
    left.z = z - v.z;
    return left;
}

void Vector3::operator-=(Vector3 v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

FLOAT Vector3::operator*(Vector3 v)
{        
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::Cross(Vector3 v1, Vector3 v2)
{
    Vector3 cross;
    cross.x = v1.y * v2.z - v1.z * v2.y;
    cross.y = v1.z * v2.x - v1.x * v2.z;
    cross.z = v1.x * v2.y - v1.y * v2.x;
    return cross;
}
