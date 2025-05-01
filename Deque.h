//
// Created by Leonid on 21.04.2025.
//

#ifndef DEQUE_H
#define DEQUE_H


#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
    char* buffer;
    int capacity;
    int frontIdx;
    int currentSize;

    T* get_element_ptr(int index) const {
        return reinterpret_cast<T*>(buffer + index * sizeof(T));
    }

    void resize(int new_capacity) {
        char* new_buffer = static_cast<char*>(operator new[](new_capacity * sizeof(T)));


        for (int i = 0; i < currentSize; i++) {
            int old_pos = (frontIdx + i) % capacity;
            new (new_buffer + i * sizeof(T)) T(std::move(*get_element_ptr(old_pos)));
            get_element_ptr(old_pos)->~T();
        }

        operator delete[](buffer);
        buffer = new_buffer;
        capacity = new_capacity;
        frontIdx = 0;
    }

public:
    Deque() : capacity(4), frontIdx(0), currentSize(0) {
        buffer = static_cast<char*>(operator new[](capacity * sizeof(T)));
    }

    ~Deque() {
        for (int i = 0; i < currentSize; i++) {
            get_element_ptr((frontIdx + i) % capacity)->~T();
        }
        operator delete[](buffer);
    }

    void push_back(const T& value) {
        if (currentSize == capacity) resize(capacity * 2);
        new (get_element_ptr((frontIdx + currentSize) % capacity)) T(value);
        currentSize++;
    }

    void push_front(const T& value) {
        if (currentSize == capacity) resize(capacity * 2);
        frontIdx = (frontIdx - 1 + capacity) % capacity;
        new (get_element_ptr(frontIdx)) T(value);
        currentSize++;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("Deque is empty");
        get_element_ptr((frontIdx + currentSize - 1) % capacity)->~T();
        currentSize--;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("Deque is empty");
        get_element_ptr(frontIdx)->~T();
        frontIdx = (frontIdx + 1) % capacity;
        currentSize--;
    }

    T& front() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return *get_element_ptr(frontIdx);
    }

    T& back() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return *get_element_ptr((frontIdx + currentSize - 1) % capacity);
    }

    bool empty() const { return currentSize == 0; }
    int size() const { return currentSize; }
};


#endif //DEQUE_H
