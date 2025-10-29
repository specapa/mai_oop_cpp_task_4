#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

template <typename T>
class Figure {
    public:
        // Деструктор для корректного наследования 
        virtual ~Figure() = default;

        // Геометрический центр
        virtual std::pair<T, T> Center() const = 0;

        // Вывод в std::cout
        virtual void Print(std::ostream& os) const = 0;

        // Ввод из std::cin
        virtual void Read(std::istream& is) = 0;

        // Вычисление площади (через приведение в double)
        virtual operator double() const = 0;

        // Операторы
        virtual Figure& operator=(const Figure& other) { return *this; };
        virtual Figure& operator=(Figure&& other) noexcept { return *this; };
        virtual bool operator==(const Figure& other) const = 0;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.Print(os);
    return os;
}

template <typename T>
inline std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.Read(is);
    return is;
}

#endif // FIGURE_HPP