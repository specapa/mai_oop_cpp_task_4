#pragma once
// #include "Point.hpp"
#include <concepts>
#include <cmath>

template <Scalar T>
Point<T>::Point() : x(0), y(0) {}

template <Scalar T>
Point<T>::Point(T x_val, T y_val) : x(x_val), y(y_val) {}

template <Scalar T>
Point<T>::Point(const Point& other) = default;

template <Scalar T>
Point<T>& Point<T>::operator=(const Point& other) = default;

template <Scalar T>
bool Point<T>::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

template <Scalar T>
Point<T> Point<T>::operator+(const Point& other) const {
    return {x + other.x, y + other.y};
}

template <Scalar T>
Point<T> Point<T>::operator-(const Point& other) const {
    return {x - other.x, y - other.y};
}

template <Scalar T>
Point<T> Point<T>::operator/(T value) const {
    return {x / value, y / value};
}

template <Scalar T>
double Point<T>::distance(const Point& other) const {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
};