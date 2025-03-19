#ifndef CUSTOMSTACK_H
#define CUSTOMSTACK_H

#include <vector>
#include <stdexcept>

// Template class for a stack
template <typename T>
class CustomStack {
public:
    void push(T item);
    T pop();
    size_t size() const;
    bool isEmpty() const;
    T peek() const;

private:
    std::vector<T> dataset;
};

// Template function implementations (must be in the header file)
template <typename T>
void CustomStack<T>::push(T item) {
    dataset.push_back(item);
}

template <typename T>
T CustomStack<T>::pop() {
    if (dataset.empty()) {
        throw std::out_of_range("Stack is empty. Cannot pop.");
    }
    T item = dataset.back();
    dataset.pop_back();
    return item;
}

template <typename T>
size_t CustomStack<T>::size() const {
    return dataset.size();
}

template <typename T>
bool CustomStack<T>::isEmpty() const {
    return dataset.empty();
}

template <typename T>
T CustomStack<T>::peek() const {
    if (dataset.empty()) {
        throw std::out_of_range("Stack is empty. Cannot peek.");
    }
    return dataset.back();
}

#endif  // CUSTOMSTACK_H
