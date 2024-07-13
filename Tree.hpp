// ariel.levovich@msmail.ariel.ac.il 
#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <memory>
#include "Node.hpp"
#include "PreOrderIterator.hpp"
#include "PostOrderIterator.hpp"
#include "InOrderIterator.hpp"
#include "BfsIterator.hpp"
#include "DfsIterator.hpp"
#include "HeapIterator.hpp"

// Tree class with k-ary tree implementation
template<typename T, size_t K>
class Tree {
private:
    std::shared_ptr<Node<T,K>> root;    

public:
    // Constructor for the Tree class
    explicit Tree() : root(nullptr) {}

    std::shared_ptr<Node<T,K>> getRoot() const {
        return root;
    }

    // Destructor
    ~Tree() {
        clear();        
    }

    // Clear the tree
    void clear() {
        // No need to delete node explicitly, shared_ptr will handle it
        root = nullptr;
    }    

    // Function to add the root node
    void add_root(const Node<T,K>& node) {
        root = std::make_shared<Node<T,K>>(node);
    }

    // Function to add a child node to a given parent node
    void add_sub_node(Node<T,K>& parent_node, const Node<T,K>& child_node) {    
        auto tree_node = find_node(root, parent_node.get_value());            
        if (tree_node) {
            tree_node->add_child(std::make_shared<Node<T,K>>(child_node));
        }
    }    
    
    PreOrderIterator<T,K> begin_pre_order() {
        return PreOrderIterator<T,K>(root);
    }

    PreOrderIterator<T,K> end_pre_order() {
        return PreOrderIterator<T,K>(nullptr);
    }    

    PostOrderIterator<T,K> begin_post_order() {
        return PostOrderIterator<T,K>(root);
    }

    PostOrderIterator<T,K> end_post_order() {
        return PostOrderIterator<T,K>(nullptr);
    }    

    InOrderIterator<T,K> begin_in_order() {
        return InOrderIterator<T,K>(root);
    }

    InOrderIterator<T,K> end_in_order() {
        return InOrderIterator<T,K>(nullptr);
    }

    BFSIterator<T,K> begin_bfs_scan() {
        return BFSIterator<T,K>(root);
    }

    BFSIterator<T,K> end_bfs_scan() {
        return BFSIterator<T,K>(nullptr);
    }

    DFSIterator<T,K> begin_dfs_scan() {
        return DFSIterator<T,K>(root);
    }

    DFSIterator<T,K> end_dfs_scan() {
        return DFSIterator<T,K>(nullptr);
    }
    
    HeapIterator<T,K> myHeap() {
        return HeapIterator<T,K>(root);
    }    

    HeapIterator<T,K> emptyHeap() {
        std::shared_ptr<Node<T,K>> empty;
        return HeapIterator<T,K>(empty);
    }
          
private:
    // Helper function to find a node by value
    std::shared_ptr<Node<T,K>> find_node(std::shared_ptr<Node<T,K>> node, const T& value) {
        if (!node) return nullptr;
        if (node->get_value() == value) return node;
        for (auto& child : node->get_children()) {
            auto result = find_node(child, value);
            if (result) return result;
        }
        return nullptr;
    }    
};

#endif
