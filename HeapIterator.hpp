// ariel.levovich@msmail.ariel.ac.il 
#ifndef HEAP_ITERATOR_HPP
#define HEAP_ITERATOR_HPP

#include "Node.hpp"
// Heap iterator
template<typename T, size_t K>
class HeapIterator {
private:
    std::vector<T> heap;

public:
    explicit HeapIterator(std::shared_ptr<Node<T,K>> root) {
        build_heap(root);
        std::make_heap(heap.begin(), heap.end(), std::greater<T>());
    }

    bool isNotEmpty() const {
        return !heap.empty();
    }

    T get_value() const {
        return heap.front();
    }

    HeapIterator& operator++() {
        std::pop_heap(heap.begin(), heap.end(), std::greater<T>());
        heap.pop_back();
        return *this;
    }

private:
    void build_heap(std::shared_ptr<Node<T,K>> node) {
        if (node) {
            heap.push_back(node->get_value());
            for (const auto& child : node->get_children()) {
                build_heap(child);
            }
        }
    }
};
#endif