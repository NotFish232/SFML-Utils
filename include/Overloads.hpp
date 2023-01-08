#ifndef OVERLOADS_HPP
#define OVERLOADS_HPP

#include <SFML/Graphics.hpp>

namespace sf {

template <class T, class U>
inline Vector2<T> operator*(T num, const Vector2<U> &v) {
    return {num * v.x, num * v.y};
}

template <class T, class U>
inline Vector2<T> operator/(const Vector2<T> &v, U num) {
    return {v.x / num, v.y / num};
}

template <class T, class U>
inline Vector2<T> operator+(const Vector2<T> &left, const Vector2<U> &right) {
    return {left.x + right.x, left.y + right.y};
}

template <class T, class U>
inline Vector2<T> operator-(const Vector2<T> &left, const Vector2<U> &right) {
    return {left.x - right.x, left.y - right.y};
}

template <class T>
inline std::ostream &operator<<(std::ostream &os, const Vector2<T> &vec) {
    os << "{" << vec.x << ", " << vec.y << "}";
    return os;
}

}

#endif