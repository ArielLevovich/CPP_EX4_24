#ifndef INORDER_ITERATOR_HPP
#define INORDER_ITERATOR_HPP

#include "Node.hpp"
// In-order iterator (only for binary trees)
template<typename T, size_t K>
class InOrderIterator {
private:
    std::stack<std::shared_ptr<Node<T,K>>> stack;
    std::shared_ptr<Node<T,K>> current;

    void push_left(std::shared_ptr<Node<T,K>> node) {
        while (node) {
            stack.push(node);
            auto children = node->get_children();
            node = (children.empty()) ? nullptr : children.front();
        }
    }

public:
    explicit InOrderIterator(std::shared_ptr<Node<T,K>> root) {
        push_left(root);
        current = (stack.empty()) ? nullptr : stack.top();
    }

    bool operator!=(const InOrderIterator& other) const {
        return current != other.current;
    }

    T get_value() const {
        return current->get_value();
    }

    InOrderIterator& operator++() {
        if (!stack.empty()) {
            auto node = stack.top();
            stack.pop();
            auto children = node->get_children();
            if (!children.empty()) {
                if (children.size() == 1) {
                    push_left(nullptr);
                } else {
                    for (unsigned int i = children.size()-1; i >= 1; i--) {
                        push_left(children[i]);
                    }
                }
            }
            current = (stack.empty()) ? nullptr : stack.top();
        }
        return *this;
    }
};

#endif