#include "Vector3.h"

Vector3 Vector3::operator*(FLOAT right)
{
    Vector3 left;
    left.x = this->x * right;
    left.y = this->y * right;
    left.z = this->z * right;
    return left;
}

void Vector3::operator*=(FLOAT right)
{
    this->x += right;
    this->y += right;
    this->z += right;
}

Vector3 Vector3::operator+(Vector3 right)
{
    Vector3 left;
    left.x = this->x + right.x;
    left.y = this->y + right.y;
    left.z = this->z + right.z;
    return left;
}

void Vector3::operator+=(Vector3 right)
{
    this->x += right.x;
    this->y += right.y;
    this->z += right.z;
}

Vector3 Vector3::operator-(Vector3 right)
{
    Vector3 left;
    left.x = this->x - right.x;
    left.y = this->y - right.y;
    left.z = this->z - right.z;
    return left;
}

void Vector3::operator-=(Vector3 right)
{
    this->x -= right.x;
    this->y -= right.y;
    this->z -= right.z;
}

FLOAT Vector3::operator*(Vector3 right)
{        
    return 
        this->x * right.x +
        this->y * right.y +
        this->z * right.z;
}
