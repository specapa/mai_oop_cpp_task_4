#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <utility>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

#endif // UTILS_HPP
