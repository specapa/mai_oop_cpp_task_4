#pragma once
// #include "Trapezoid.hpp"
#include <cmath>
#include <iostream>
#include <concepts>
#include "Helpers.hpp"

template <Scalar T>
Trapezoid<T>::Trapezoid() = default;

template <Scalar T>
void Trapezoid<T>::Read(std::istream& is) {
    std::cout << "Введите координаты 4 вершин трапеции в порядке обхода (x y):\n";
    vertices.clear();
    vertices.reserve(4);

    for (int i = 0; i < 4; ++i) {
        T x, y;
        std::cout << "Вершина " << i + 1 << ": ";
        is >> x >> y;
        vertices.push_back(std::make_unique<Point<T>>(x, y));
    }

    if (!isTrapezoid()) {
        throw std::logic_error("Введённые точки не образуют трапецию!");
    }
    if (!isCyclic()) {
        throw std::logic_error("Трапеция не может быть вписана в окружность!");
    }
}


template <Scalar T>
void Trapezoid<T>::Print(std::ostream& os) const {
    os << "Trapezoid vertices: ";
    for (const auto& v : vertices) os << *v << " ";
    os << "\nCenter: " << Center() << "\nArea: " << static_cast<double>(*this) << "\n";
}

template <Scalar T>
std::pair<T, T> Trapezoid<T>::Center() const {
    T sumX = 0, sumY = 0;
    for (const auto& v : vertices) {
        sumX += v->x;
        sumY += v->y;
    }
    return {sumX / 4, sumY / 4};
}

template <Scalar T>
Trapezoid<T>::operator double() const {
    if (vertices.size() != 4) return 0.0;

    double area = 0.0;
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        area += vertices[i]->x * vertices[j]->y;
        area -= vertices[j]->x * vertices[i]->y;
    }
    return std::abs(area) / 2.0;
}

template <Scalar T>
bool Trapezoid<T>::operator==(const Figure<T>& other) const {
    auto o = dynamic_cast<const Trapezoid*>(&other);
    if (!o) return false;
    return std::abs(static_cast<double>(*this) - static_cast<double>(*o)) < 1e-6;
}

template <Scalar T>
bool Trapezoid<T>::isTrapezoid() const {
    if (vertices.size() != 4) return false;

    const Point<T>& A = *vertices[0];
    const Point<T>& B = *vertices[1];
    const Point<T>& C = *vertices[2];
    const Point<T>& D = *vertices[3];

    auto slope = [](const Point<T>& p1, const Point<T>& p2) -> double {
        if (std::abs(p2.x - p1.x) < 1e-9) return std::numeric_limits<double>::infinity();
        return (p2.y - p1.y) / (p2.x - p1.x);
    };

    double AB = slope(A, B);
    double BC = slope(B, C);
    double CD = slope(C, D);
    double DA = slope(D, A);

    bool ab_cd = std::abs(AB - CD) < 1e-6;
    bool bc_da = std::abs(BC - DA) < 1e-6;

    return (ab_cd ^ bc_da);
}


template <Scalar T>
bool Trapezoid<T>::isCyclic() const {
    if (vertices.size() != 4) return false;

    const Point<T>& A = *vertices[0];
    const Point<T>& B = *vertices[1];
    const Point<T>& C = *vertices[2];
    const Point<T>& D = *vertices[3];

    auto angle = [](const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) -> double {
        double v1x = p1.x - p2.x;
        double v1y = p1.y - p2.y;
        double v2x = p3.x - p2.x;
        double v2y = p3.y - p2.y;

        double dot = v1x * v2x + v1y * v2y;
        double len1 = std::sqrt(v1x*v1x + v1y*v1y);
        double len2 = std::sqrt(v2x*v2x + v2y*v2y);
        return std::acos(dot / (len1 * len2));
    };

    double angleA = angle(D, A, B);
    double angleC = angle(B, C, D);

    return std::abs((angleA + angleC) - M_PI) < 1e-3;
}
