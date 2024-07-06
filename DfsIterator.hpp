// ariel.levovich@msmail.ariel.ac.il 
#ifndef DFS_ITERATOR_HPP
#define DFS_ITERATOR_HPP

#include "Node.hpp"
// DFS iterator
template<typename T, size_t K>
class DFSIterator {
private:
    std::stack<std::shared_ptr<Node<T,K>>> stack;

public:
    explicit DFSIterator(std::shared_ptr<Node<T,K>> root) {
        if (root) stack.push(root);
    }

    bool operator!=(const DFSIterator& other) const {
        return !stack.empty() || !other.stack.empty();
    }
    
    T get_value() const {
        return stack.top()->get_value();
    }

    DFSIterator& operator++() {
        auto node = stack.top();
        stack.pop();
        for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) {
            stack.push(*it);
        }
        return *this;
    }
};
#endif