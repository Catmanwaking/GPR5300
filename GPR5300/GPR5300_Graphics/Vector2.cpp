#include "Vector2.h"


Vector2 Vector2::operator*(FLOAT right)
{
    Vector2 left;
    left.x = x * right;
    left.y = y * right;
    return left;
}

void Vector2::operator*=(FLOAT right)
{
    x *= right;
    y *= right;
}

Vector2 Vector2::operator+(Vector2 right)
{
    Vector2 left;
    left.x = x + right.x;
    left.y = y + right.y;
    return left;
}

void Vector2::operator+=(Vector2 right)
{
    x += right.x;
    y += right.y;
}

Vector2 Vector2::operator-(Vector2 right)
{
    Vector2 left;
    left.x = x - right.x;
    left.y = y - right.y;
    return left;
}

void Vector2::operator-=(Vector2 right)
{
    x -= right.x;
    y -= right.y;
}

FLOAT Vector2::operator*(Vector2 right)
{
    return
        x * right.x +
        y * right.y;
}
