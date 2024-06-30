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

// Tree class with k-ary tree implementation
template<typename T>
class Tree {
private:
    std::shared_ptr<Node<T>> root;
    int max_children;

public:
    // Constructor for the Tree class
    explicit Tree(int k = 2) : root(nullptr), max_children(k) {}

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
    void add_root(const Node<T>& node) {
        root = std::make_shared<Node<T>>(node);
    }

    // Function to add a child node to a given parent node
    void add_sub_node(Node<T>& parent_node, const Node<T>& child_node) {        
        auto children = parent_node.get_children();
        if ((int)children.size() < max_children) {
            children.push_back(std::make_shared<Node<T>>(child_node));
        }
    }    
    
    PreOrderIterator<T> begin_pre_order() {
        return PreOrderIterator<T>(root);
    }

    PreOrderIterator<T> end_pre_order() {
        return PreOrderIterator<T>(nullptr);
    }    

    PostOrderIterator<T> begin_post_order() {
        return PostOrderIterator<T>(root);
    }

    PostOrderIterator<T> end_post_order() {
        return PostOrderIterator<T>(nullptr);
    }    

    InOrderIterator<T> begin_in_order() {
        return InOrderIterator<T>(root);
    }

    InOrderIterator<T> end_in_order() {
        return InOrderIterator<T>(nullptr);
    }

    // BFS iterator
    /*
    class BFSIterator {
    private:
        std::queue<std::shared_ptr<Node<T>>> queue;

    public:
        explicit BFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) queue.push(root);
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty() || !other.queue.empty();
        }

        T& operator*() const {
            return queue.front()->value;
        }

        BFSIterator& operator++() {
            auto node = queue.front();
            queue.pop();
            for (auto& child : node->children) {
                queue.push(child);
            }
            return *this;
        }
    };

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // DFS iterator
    class DFSIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;

    public:
        explicit DFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) stack.push(root);
        }

        bool operator!=(const DFSIterator& other) const {
            return !stack.empty() || !other.stack.empty();
        }

        T& operator*() const {
            return stack.top()->value;
        }

        DFSIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }
    };

    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() {
        return DFSIterator(nullptr);
    }

    // Heap iterator
    class HeapIterator {
    private:
        std::vector<T> heap;

    public:
        explicit HeapIterator(std::shared_ptr<Node<T>> root) {
            build_heap(root);
            std::make_heap(heap.begin(), heap.end(), std::greater<>());
        }

        bool operator!=(const HeapIterator& other) const {
            return !heap.empty();
        }

        T& operator*() const {
            return heap.front();
        }

        HeapIterator& operator++() {
            std::pop_heap(heap.begin(), heap.end(), std::greater<>());
            heap.pop_back();
            return *this;
        }

    private:
        void build_heap(std::shared_ptr<Node<T>> node) {
            if (node) {
                heap.push_back(node->value);
                for (const auto& child : node->children) {
                    build_heap(child);
                }
            }
        }
    };

    HeapIterator myHeap() {
        return HeapIterator(root);
    }    
*/    
private:
    // Helper function to find a node by value
    // std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> node, const T& value) {
    //     if (!node) return nullptr;
    //     if (node->get_value() == value) return node;
    //     for (auto& child : node->get_children()) {
    //         auto result = find_node(child, value);
    //         if (result) return result;
    //     }
    //     return nullptr;
    // }    
};

#endif
