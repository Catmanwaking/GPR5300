#include "Vector2.h"


Vector2 Vector2::operator*(FLOAT right)
{
    Vector2 left;
    left.x = this->x * right;
    left.y = this->y * right;
    return left;
}

void Vector2::operator*=(FLOAT right)
{
    this->x *= right;
    this->y *= right;
}

Vector2 Vector2::operator+(Vector2 right)
{
    Vector2 left;
    left.x = this->x + right.x;
    left.y = this->y + right.y;
    return left;
}

void Vector2::operator+=(Vector2 right)
{
    this->x += right.x;
    this->y += right.y;
}

Vector2 Vector2::operator-(Vector2 right)
{
    Vector2 left;
    left.x = this->x - right.x;
    left.y = this->y - right.y;
    return left;
}

void Vector2::operator-=(Vector2 right)
{
    this->x -= right.x;
    this->y -= right.y;
}

FLOAT Vector2::operator*(Vector2 right)
{
    return
        this->x * right.x +
        this->y * right.y;
}
