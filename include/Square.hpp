#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Point.hpp"
#include "Figure.hpp"
#include <vector>
#include <memory>
#include <concepts>

template <Scalar T>
class Square : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> vertices;
    bool isSquare() const;

public:
    Square();

    void Read(std::istream& is) override;
    void Print(std::ostream& os) const override;
    std::pair<T, T> Center() const override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
};

#include "Square.tpp"
#endif // SQUARE_HPP
