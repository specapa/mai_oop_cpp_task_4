#pragma once
// #include "Square.hpp"
#include <cmath>
#include <iostream>
#include <concepts>
#include "Helpers.hpp"

template <Scalar T>
Square<T>::Square() = default;

template <Scalar T>
void Square<T>::Read(std::istream& is) {
    std::cout << "Введите 4 вершины квадрата (x1 y1 x2 y2 x3 y3 x4 y4) в порядке обхода: ";

    vertices.clear();
    vertices.reserve(4);

    for (int i = 0; i < 4; ++i) {
        T x, y;
        is >> x >> y;
        vertices.push_back(std::make_unique<Point<T>>(x, y));
    }

    if (!isSquare()) {
        throw std::logic_error("Введённые точки не образуют квадрат!");
    }
}


template <Scalar T>
void Square<T>::Print(std::ostream& os) const {
    os << "Square vertices: ";
    for (const auto& v : vertices) os << *v << " ";
    os << "\nCenter: " << Center() << "\nArea: " << static_cast<double>(*this) << "\n";
}

template <Scalar T>
std::pair<T, T> Square<T>::Center() const {
    T sumX = 0, sumY = 0;
    for (const auto& v : vertices) {
        sumX += v->x;
        sumY += v->y;
    }
    return {sumX / 4, sumY / 4};
}

template <Scalar T>
Square<T>::operator double() const {
    if (vertices.size() < 4) return 0.0;
    T side = std::abs(vertices[0]->x - vertices[2]->x);
    return static_cast<double>(side * side);
}

template <Scalar T>
bool Square<T>::operator==(const Figure<T>& other) const {
    auto o = dynamic_cast<const Square*>(&other);
    if (!o) return false;
    return std::abs(static_cast<double>(*this) - static_cast<double>(*o)) < 1e-6;
}

template <Scalar T>
bool Square<T>::isSquare() const {
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

    bool sidesEqual = std::abs(AB - BC) < 1e-6 &&
                      std::abs(BC - CD) < 1e-6 &&
                      std::abs(CD - DA) < 1e-6;

    bool diagonalsEqual = std::abs(AC - BD) < 1e-6;

    auto dot = [](const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        double v1x = p1.x - p2.x;
        double v1y = p1.y - p2.y;
        double v2x = p3.x - p2.x;
        double v2y = p3.y - p2.y;
        return v1x * v2x + v1y * v2y;
    };

    bool rightAngles = std::abs(dot(A, B, C)) < 1e-6 &&
                       std::abs(dot(B, C, D)) < 1e-6 &&
                       std::abs(dot(C, D, A)) < 1e-6 &&
                       std::abs(dot(D, A, B)) < 1e-6;

    return sidesEqual && diagonalsEqual && rightAngles;
}
