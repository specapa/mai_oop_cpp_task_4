#ifndef TRAPEZOID_HPP
#define TRAPEZOID_HPP

#include "Point.hpp"
#include "Figure.hpp"
#include <vector>
#include <memory>
#include <concepts>

template <Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> vertices;
    bool isTrapezoid() const;
    bool isCyclic() const;

public:
    Trapezoid();

    void Read(std::istream& is) override;
    void Print(std::ostream& os) const override;
    std::pair<T, T> Center() const override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
};

#include "Trapezoid.tpp"
#endif // TRAPEZOID_HPP
