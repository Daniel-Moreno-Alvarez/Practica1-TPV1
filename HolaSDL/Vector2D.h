#pragma once
#include <iostream>
#include <cmath>

template <typename T>
class Vector2D {
private:
    T x;
    T y;

public:
    Vector2D() : x(0), y(0){}
    Vector2D(T _x, T _y) : x(_x), y(_y) {}

    T getX() const { return x; }
    T getY() const { return y; }

    void setX(T _x) { x = _x; }
    void setY(T _y) { y = _y; }

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    float operator*(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }

    Vector2D operator*(const float other) const {
        return Vector2D(x * other, y * other);
    }

    Vector2D operator+=(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    bool operator==(const Vector2D& other) {
        return x == other.x && y == other.y;
    }

    friend std::istream& operator>>(std::istream& is, Vector2D<T>& other) {
        T x, y;
        is >> x >> y;
        other.setX(x);
        other.setY(y);
        return is;
    }
};

using Point2D = Vector2D<float>;