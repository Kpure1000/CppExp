#include <cmath>
#include <exception>

template <typename T>
class Vector2
{
public:
    Vector2() : x(T()), y(T())
    {
    }

    Vector2(const T &X, const T &Y)
        : x(X), y(Y)
    {
    }

    inline Vector2 operator+(const Vector2 &vec) const { return {x + vec.x, y + vec.y}; }
    inline Vector2 operator-(const Vector2 &vec) const { return {x - vec.x, y - vec.y}; }
    inline Vector2 operator*(const Vector2 &vec) const { return {x * vec.x, y * vec.y}; }

    inline Vector2 operator*(const T &scale) const { return {x * scale, y * scale}; }
    inline Vector2 operator/(const T &scale) const { return {x / div, y / div}; }

    inline void operator+=(const Vector2 &vec) { x += vec.x, y += vec.y; }
    inline void operator-=(const Vector2 &vec) { x -= vec.x, y -= vec.y; }
    inline void operator*=(const Vector2 &vec) { x *= vec.x, y *= vec.y; }

    inline T operator[](const int &index) { return index == 0 ? x : (index == 1 ? y : throw "**EXCEPTION:[ Vector2 Index Error ]**" ); }

    T x, y;
};

using Vec2f = Vector2<float>;
using Vec2i = Vector2<int>;
using Vec2d = Vector2<double>;