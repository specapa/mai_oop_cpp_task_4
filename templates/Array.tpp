#pragma once
// #include "Array.hpp"
#include <cmath>

template <typename T>
Array<T>::Array() : capacity(4), count(0), data(std::make_unique<std::shared_ptr<T>[]>(4)) {}

template <typename T>
Array<T>::Array(size_t initialCapacity)
    : capacity(initialCapacity), count(0), data(std::make_unique<std::shared_ptr<T>[]>(initialCapacity)) {}

template <typename T>
Array<T>::Array(const Array& other)
    : capacity(other.capacity), count(other.count), data(std::make_unique<std::shared_ptr<T>[]>(other.capacity)) {
    for (size_t i = 0; i < count; ++i)
        data[i] = other.data[i];
}

template <typename T>
Array<T>::Array(Array&& other) noexcept
    : capacity(other.capacity), count(other.count), data(std::move(other.data)) {
    other.count = 0;
    other.capacity = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        capacity = other.capacity;
        count = other.count;
        data = std::make_unique<std::shared_ptr<T>[]>(capacity);
        for (size_t i = 0; i < count; ++i)
            data[i] = other.data[i];
    }
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        capacity = other.capacity;
        count = other.count;
        data = std::move(other.data);
        other.count = 0;
        other.capacity = 0;
    }
    return *this;
}

template <typename T>
Array<T>::~Array() = default;

template <typename T>
void Array<T>::resize(size_t new_capacity) {
    auto new_data = std::make_unique<std::shared_ptr<T>[]>(new_capacity);
    for (size_t i = 0; i < count; ++i)
        new_data[i] = std::move(data[i]);
    data = std::move(new_data);
    capacity = new_capacity;
}

template <typename T>
void Array<T>::validateIndex(size_t index) const {
    if (index >= count)
        throw std::out_of_range("Index out of range");
}

template <typename T>
void Array<T>::Add(std::shared_ptr<T> element) {
    if (count >= capacity)
        resize(capacity * 2);
    data[count++] = std::move(element);
}

template <typename T>
void Array<T>::Remove(size_t index) {
    validateIndex(index);
    for (size_t i = index; i < count - 1; ++i)
        data[i] = std::move(data[i + 1]);
    --count;
}

template <typename T>
std::shared_ptr<T> Array<T>::Get(size_t index) const {
    validateIndex(index);
    return data[index];
}

template <typename T>
std::shared_ptr<T> Array<T>::operator[](size_t index) const {
    return Get(index);
}

template <typename T>
size_t Array<T>::Size() const noexcept {
    return count;
}

template <typename T>
bool Array<T>::Empty() const noexcept {
    return count == 0;
}

template <typename T>
void Array<T>::Clear() {
    count = 0;
}

template <typename T>
double Array<T>::TotalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < count; ++i)
        total += static_cast<double>(*data[i]);
    return total;
}

template <typename T>
void Array<T>::PrintAll(std::ostream& os) const {
    if (count == 0) {
        os << "Array is empty.\n";
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        os << "Фигура #" << i + 1 << ":\n";
        data[i]->Print(os);
        os << "-----------------\n";
    }
    os << "Totak Area: " << TotalArea() << "\n";
}

template <typename T>
std::pair<double, double> Array<T>::CenterAll() const {
    if (count == 0)
        return {0.0, 0.0};

    double cx = 0.0, cy = 0.0;
    for (size_t i = 0; i < count; ++i) {
        auto center = data[i]->Center();
        cx += center.first;
        cy += center.second;
    }
    return {cx / count, cy / count};
}
