#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <iomanip>
#include <vector>

template <typename T>
class Array {
private:
    std::unique_ptr<std::shared_ptr<T>[]> data;
    size_t capacity;
    size_t count;

    void resize(size_t new_capacity);
    void validateIndex(size_t index) const;

public:
    Array();
    explicit Array(size_t initialCapacity);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    ~Array();

    void Add(std::shared_ptr<T> element);
    void Remove(size_t index);
    std::shared_ptr<T> Get(size_t index) const;
    std::shared_ptr<T> operator[](size_t index) const;

    size_t Size() const noexcept;
    bool Empty() const noexcept;
    void Clear();

    double TotalArea() const;
    void PrintAll(std::ostream& os) const;
    std::pair<double, double> CenterAll() const;
};

#include "Array.tpp"
#endif // ARRAY_HPP
