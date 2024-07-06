// ariel.levovich@msmail.ariel.ac.il 
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

// Node class representing each node in the tree
template<typename T, size_t K>
class Node {

private:
    T value;
    std::vector<std::shared_ptr<Node<T,K>>> children;

public:
    Node(const T& value) : value(value) {}
    
    T get_value() const {
        return value;
    }

    std::vector<std::shared_ptr<Node<T,K>>>& get_children() {
        return children;
    }

    void add_child(std::shared_ptr<Node<T,K>> child) {
        if (children.size() < K) {
            children.push_back(child);
        }
    }
};

#endif