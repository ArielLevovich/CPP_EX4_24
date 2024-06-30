#ifndef POSTORDER_ITERATOR_HPP
#define POSTORDER_ITERATOR_HPP

#include "Node.hpp"
// Post-order iterator
template<typename T>
class PostOrderIterator {
private:
    std::stack<std::shared_ptr<Node<T>>> stack;
    std::shared_ptr<Node<T>> current;

    void advance() {
        while (!stack.empty() && current == stack.top()) {
            stack.pop();
            if (!stack.empty()) {
                current = stack.top();
                auto children = current->get_children();
                if (!children.empty()) {
                    current = children.back();
                }
            } else {
                current = nullptr;
            }
        }
    }

public:
    explicit PostOrderIterator(std::shared_ptr<Node<T>> root) {
        if (root) {
            stack.push(root);
            while (!stack.empty() && !stack.top()->get_children().empty()) {
                stack.push(stack.top()->get_children().front());
            }
            current = stack.top();
        } else {
            current = nullptr;
        }
    }

    bool operator!=(const PostOrderIterator& other) const {
        return current != other.current;
    }

    T get_value() const {
        return current->get_value();
    }

    PostOrderIterator& operator++() {
        if (!stack.empty()) {
            stack.pop();
            advance();
        }
        return *this;
    }
};

#endif