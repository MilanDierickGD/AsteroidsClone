#pragma once
#include <iomanip>
#include <sstream>

template <typename T>
struct Vector2D
{
    static_assert(std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value, "Only int, float or double can be used as template types.");

    // Constructors
    Vector2D();
    explicit Vector2D(T x, T y);
    explicit Vector2D(const Point2D<T>& fromPoint, const Point2D<T>& tillPoint);
    explicit Vector2D(const Point2D<T> point);

    // Member operators
    Vector2D<T> operator-() const;
    Vector2D<T> operator+() const;
    Vector2D<T>& operator*=(Vector2D<T> rhs);
    Vector2D<T>& operator/=(Vector2D<T> rhs);
    Vector2D<T>& operator+=(const Vector2D<T>& rhs);
    Vector2D<T>& operator-=(const Vector2D<T>& rhs);
    explicit operator Point2D<T>();

    // Methods
    Point2D<float> ToPoint2D() const;
    bool Equals(const Vector2D& other, float epsilon = 0.001f) const;
    std::string ToString();
    T DotProduct(const Vector2D& other) const;
    T CrossProduct(const Vector2D& other) const;
    T Norm() const;
    T Length() const;
    T SquaredLength() const;
    T AngleWith(const Vector2D& other) const;
    Vector2D Normalized(float epsilon = 0.001f) const;
    Vector2D Orthogonal() const;
    Vector2D Reflect(const Vector2D& surfaceNormal) const;
    void Set(T newX, T newY);
    void Zero();

    // Data members
    T x;
    T y;
};

#pragma region Constructors

template <typename T>
Vector2D<T>::Vector2D() : Vector2D<T>(0, 0)
{
}

template <typename T>
Vector2D<T>::Vector2D(T x, T y) : x(x), y(y)
{
}

template <typename T>
Vector2D<T>::Vector2D(const Point2D<T>& fromPoint, const Point2D<T>& tillPoint)
    : Vector2D<T>{tillPoint.x - fromPoint.y, tillPoint.y - fromPoint.y}
{
}

template <typename T>
Vector2D<T>::Vector2D(const Point2D<T> point)
    : Vector2D<T>{point.x, point.y}
{
}

#pragma endregion

#pragma region Member operators

template <typename T>
Vector2D<T> Vector2D<T>::operator-() const
{
    return Vector2D{ -x, -y };
}

template <typename T>
Vector2D<T> Vector2D<T>::operator+() const
{
    return Vector2D{ x, y };
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator*=(Vector2D<T> rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator/=(Vector2D<T> rhs)
{
    *this *= 1 / rhs;
    return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator+=(const Vector2D& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator-=(const Vector2D& rhs)
{
    *this += -rhs;
    return *this;
}

template <typename T>
Vector2D<T>::operator Point2D<T>()
{
    return Point2D<T>(x, y);
}

#pragma endregion

#pragma region Methods

template <typename T>
Point2D<float> Vector2D<T>::ToPoint2D() const
{
    return Point2D<T>(x, y);
}

template <typename T>
bool Vector2D<T>::Equals(const Vector2D<T>& other, float epsilon) const
{
    return ( std::abs(x - other.x) < epsilon ) && ( std::abs(y - other.y) < epsilon );
}

template <typename T>
std::string Vector2D<T>::ToString()
{
    std::stringstream buffer;

    buffer << std::fixed;
    buffer << std::setprecision(2);
    buffer << "Vector2D(" << x << ", " << y << ")";
    return buffer.str();
}

template <typename T>
T Vector2D<T>::DotProduct(const Vector2D<T>& other) const
{
    return x * other.x + y * other.y;
}

template <typename T>
T Vector2D<T>::CrossProduct(const Vector2D<T>& other) const
{
    return x * other.y - y * other.x;
}

template <typename T>
T Vector2D<T>::Norm() const
{
    return Length();
}

template <typename T>
T Vector2D<T>::Length() const
{
    return std::sqrt(SquaredLength());
}

template <typename T>
T Vector2D<T>::SquaredLength() const
{
    return x * x + y * y;
}

template <typename T>
T Vector2D<T>::AngleWith(const Vector2D<T>& other) const
{
    return std::atan2(x * other.y - other.x * y, x * other.x + y * other.y);
}

template <typename T>
Vector2D<T> Vector2D<T>::Normalized(const float epsilon) const
{
    const float length = Length();
    if (length < epsilon)
    {
        return Vector2D<T>{0, 0};
    }
    
    return Vector2D<T>{x / length, y / length};
}

template <typename T>
Vector2D<T> Vector2D<T>::Orthogonal() const
{
    return Vector2D<T>{-y, x};
}

template <typename T>
Vector2D<T> Vector2D<T>::Reflect(const Vector2D& surfaceNormal) const
{
    return (*this) - 2 * (this->DotProduct(surfaceNormal) * surfaceNormal);
}

template <typename T>
void Vector2D<T>::Set(T newX, T newY)
{
    x = newX;
    y = newY;
}

template <typename T>
void Vector2D<T>::Zero()
{
    x = 0;
    y = 0;
}

#pragma endregion

#pragma region Non-member operators

template <typename T>
Vector2D<T> operator*(float lhs, Vector2D<T> rhs)
{
    return rhs *= lhs;
}

template <typename T>
Vector2D<T> operator*(Vector2D<T> lhs, float rhs)
{
    return lhs *= rhs;
}

template <typename T>
Vector2D<T> operator/(Vector2D<T> lhs, float rhs)
{
    return lhs *= 1 / rhs;
}

template <typename T>
Vector2D<T> operator+(Vector2D<T> lhs, const Vector2D<T>& rhs)
{
    return lhs += rhs;
}

template <typename T>
Vector2D<T> operator-(Vector2D<T> lhs, const Vector2D<T>& rhs)
{
    return lhs += -rhs;
}

template <typename T>
bool operator==(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
    return lhs.Equals( rhs );
}

template <typename T>
bool operator!=(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
    return !( lhs == rhs );
}

template <typename T>
std::ostream& operator<<(std::ostream& lhs, const Vector2D<T>& rhs)
{
    lhs << rhs.ToString( );
    return lhs;
}

// Translating a point by a vector
template <typename T>
Point2D<T>& operator+=(Point2D<T>& lhs, const Vector2D<T>& rhs)
{
    lhs.X += rhs.X;
    lhs.Y += rhs.Y;
    return lhs;
}

template <typename T>
Point2D<T> operator+(Point2D<T> lhs, const Vector2D<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <typename T>
Point2D<T>& operator-=(Point2D<T>& lhs, const Vector2D<T>& rhs)
{
    lhs.x -= rhs.x;
    lhs.x -= rhs.y;
    return lhs;
}

template <typename T>
Point2D<T> operator-(Point2D<T> lhs, const Vector2D<T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

// The difference vector between 2 points
template <typename T>
Vector2D<T> operator-(const Point2D<T>& lhs, const Point2D<T>& rhs)
{
    Vector2D<T> v{ lhs.x - rhs.x, lhs.y - rhs.y };
    return v;
}

#pragma endregion


