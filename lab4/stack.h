#pragma once

#include <stdexcept>

// Maximum capacity for the stack
static const unsigned MAX_SIZE = 20;

// Template stack class
template<typename T>
class stack {
private:
    T data[MAX_SIZE];   // storage array
    unsigned size = 0;   // current number of elements

public:
    // Constructs an empty stack(setting it as default)
    stack() = default;

    // Destructor
    ~stack() = default;

    // Copy constructor
    stack(const stack& other) = default;

    // Copy assignment operator
    stack& operator=(const stack& other) = default;

    // Adds a new value to the top of the stack.
    // Inserts a new element and throws overflow_error if full
    void push(const T &value) {
        if (size >= MAX_SIZE) {
            throw std::overflow_error("Called push on full stack.");
        }
        data[size++] = value;
    }

    // Returns true if the stack is empty
    bool empty() const {
        return size == 0;
    }

    // Removes the top element; throws out_of_range if empty
    void pop() {
        if (size == 0) {
            throw std::out_of_range("Called pop on empty stack.");
        }
        --size;
    }

    // Removes the top two elements; throws out_of_range on error
    void pop_two() {
        if (size == 0) {
            throw std::out_of_range("Called pop_two on empty stack.");
        }
        if (size == 1) {
            throw std::out_of_range("Called pop_two on a stack of size 1.");
        }
        size -= 2;
    }

    // Returns the top element; throws underflow_error if empty
    T &top() {
        if (size == 0) {
            throw std::underflow_error("Called top on empty stack.");
        }
        return data[size - 1];
    }

    const T &top() const {
        if (size == 0) {
            throw std::underflow_error("Called top on empty stack.");
        }
        return data[size - 1];
    }
};
