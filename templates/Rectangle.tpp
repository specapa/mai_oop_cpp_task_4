#pragma once
// #include "Rectangle.hpp"
#include <cmath>
#include <iostream>
#include <concepts>
#include "Helpers.hpp"

template <Scalar T>
Rectangle<T>::Rectangle() = default;

template <Scalar T>
void Rectangle<T>::Read(std::istream& is) {
    std::cout << "Введите 4 вершины прямоугольника (x1 y1 x2 y2 x3 y3 x4 y4) в порядке обхода: ";

    vertices.clear();
    vertices.reserve(4);

    for (int i = 0; i < 4; ++i) {
        T x, y;
        is >> x >> y;
        vertices.push_back(std::make_unique<Point<T>>(x, y));
    }

    if (!isRectangle()) {
        throw std::logic_error("Введённые точки не образуют прямоугольник!");
    }
}

template <Scalar T>
void Rectangle<T>::Print(std::ostream& os) const {
    os << "Rectangle vertices: ";
    for (const auto& v : vertices) os << *v << " ";
    os << "\nCenter: " << Center() << "\nArea: " << static_cast<double>(*this) << "\n";
}

template <Scalar T>
std::pair<T, T> Rectangle<T>::Center() const {
    T sumX = 0, sumY = 0;
    for (const auto& v : vertices) {
        sumX += v->x;
        sumY += v->y;
    }
    return {sumX / 4, sumY / 4};
}

template <Scalar T>
Rectangle<T>::operator double() const {
    if (vertices.size() < 4) return 0.0;
    T width = std::abs(vertices[0]->x - vertices[2]->x);
    T height = std::abs(vertices[0]->y - vertices[2]->y);
    return static_cast<double>(width * height);
}

template <Scalar T>
bool Rectangle<T>::operator==(const Figure<T>& other) const {
    auto o = dynamic_cast<const Rectangle*>(&other);
    if (!o) return false;
    return std::abs(static_cast<double>(*this) - static_cast<double>(*o)) < 1e-6;
}

template <Scalar T>
bool Rectangle<T>::isRectangle() const {
    if (vertices.size() != 4) return false;

    const Point<T>& A = *vertices[0];
    const Point<T>& B = *vertices[1];
    const Point<T>& C = *vertices[2];
    const Point<T>& D = *vertices[3];

    double AB = A.distance(B);
    double BC = B.distance(C);
    double CD = C.distance(D);
    double DA = D.distance(A);

    double AC = A.distance(C);
    double BD = B.distance(D);

    return (std::abs(AB - CD) < 1e-6) &&
           (std::abs(BC - DA) < 1e-6) &&
           (std::abs(AC - BD) < 1e-6) &&
           ((pow(AB, 2) + pow(BC, 2) + pow(CD, 2) + pow(DA, 2)) > 1e-6);
}
