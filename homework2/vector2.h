#include <cmath>

template <typename T>
class Vector2
{
public:
    T x, y;

    // Konstruktor
    Vector2(T x, T y) : x(x), y(y) {}

    // Vektorok összeadása - vektor módosítással
    Vector2<T> operator+=(const Vector2<T> &other)
    {
        return Vector2<T>(x += other.x, y += other.y);
    }

    // Vektorok kivonása - vektor módosítással
    Vector2<T> operator-=(const Vector2<T> &other)
    {
        return Vector2<T>(x -= other.x, y -= other.y);
    }

    // Vektor szorzása skalárral - vektor  módosítással
    Vector2<T> operator*=(T scalar)
    {
        return Vector2<T>(x *= scalar, y *= scalar);
    }

    // Vektor osztása skalárral
    Vector2<T> operator/=(T scalar)
    {
        return Vector2<T>(x /= scalar, y /= scalar);
    }
};

// A vektor hossza
template <typename T>
double length(const Vector2<T> &v)
{
    double val = sqrt(v.x * v.x + v.y * v.y);
    return val;
}

// A vektor hosszának négyzete
template <typename T>
double sqlength(const Vector2<T> &v)
{
    double val = (v.x * v.x + v.y * v.y);
    return val;
}
// A vektor normálása

template <typename T>
Vector2<double> normalized(const Vector2<T> &v)
{
    double len = length(v);
    if (len != 0)
    {
        return Vector2<double>(v.x / len, v.y / len);
    }
    return Vector2<double>(0, 0);
}

// Skalárszorzat
template <typename T, typename K>
T dot(const Vector2<T> &v1, const Vector2<K> &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

// Vektorok összeadása
template <typename T>
Vector2<T> operator+(Vector2<T> const &a, Vector2<T> const &b)
{
    return Vector2<T>(a.x + b.x, a.y + b.y);
}

// Vektorok kivonása
template <typename T>
Vector2<T> operator-(Vector2<T> const &a, Vector2<T> const &b)
{
    return Vector2<T>(a.x - b.x, a.y - b.y);
}

// Skalárral szorzás - jobbról
template <typename T>
Vector2<T> operator*(Vector2<T> const &v, T const &scalar)
{
    return Vector2<T>(v.x * scalar, v.y * scalar);
}

// Skalárral szorzás - balról
template <typename T>
Vector2<T> operator*(T const &scalar, Vector2<T> const &v)
{
    return Vector2<T>(v.x * scalar, v.y * scalar);
}

// Skalárral osztás
template <typename T>
Vector2<T> operator/(Vector2<T> const &v, T const &scalar)
{
    return Vector2<T>(v.x / scalar, v.y / scalar);
}