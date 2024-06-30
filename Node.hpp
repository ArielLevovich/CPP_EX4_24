#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

// Node class representing each node in the tree
template<typename T>
class Node {

private:
    T value;
    std::vector<std::shared_ptr<Node<T>>> children;

public:
    Node(const T& value) : value(value) {}
    
    T get_value() const {
        return value;
    }

    std::vector<std::shared_ptr<Node<T>>>& get_children() {
        return children;
    }
};

#endif