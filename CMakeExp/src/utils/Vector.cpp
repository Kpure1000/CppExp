#include "Vector.hpp"

template <typename T>
static Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b)
{
    return {a.x + b.x, a.y + b.y};
}

template <typename T>
static Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b)
{
    return {a.x - b.x, a.y - b.y};
}

template <typename T>
static Vector2<T> operator*(const Vector2<T> &a, const Vector2<T> &b)
{
    return {a.x * b.x, a.y * b.y};
}

template <typename T>
static T dot(const Vector2<T> &a, const Vector2<T> &b)
{
    return a.x * b.x + a.y * b.y;
}
