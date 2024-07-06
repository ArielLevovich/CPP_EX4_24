// ariel.levovich@msmail.ariel.ac.il 
#ifndef PREORDER_ITERATOR_HPP
#define PREORDER_ITERATOR_HPP

#include "Node.hpp"

// Pre-order iterator
template<typename T, size_t K>
class PreOrderIterator {
private:
    std::stack<std::shared_ptr<Node<T,K>>> stack;

public:
    explicit PreOrderIterator(std::shared_ptr<Node<T,K>> root) {
        if (root != nullptr) {
            stack.push(root);
        }
    }

    bool operator!=(const PreOrderIterator& other) const {
        return !stack.empty() || !other.stack.empty();                
    }

    T get_value() const {
        return stack.top()->get_value();
    }

    PreOrderIterator& operator++() {
        if (stack.empty()) {
            return *this;
        }

        auto node = stack.top();
        stack.pop();
        auto children = node->get_children();
        
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            stack.push(*it);
        }
        return *this;        
    }
};
#endif