// ariel.levovich@msmail.ariel.ac.il 
#ifndef BFS_ITERATOR_HPP
#define BFS_ITERATOR_HPP

#include "Node.hpp"
// BFS iterator
template<typename T, size_t K>
class BFSIterator {
    private:
        std::queue<std::shared_ptr<Node<T,K>>> queue;

    public:
        explicit BFSIterator(std::shared_ptr<Node<T,K>> root) {
            if (root) queue.push(root);
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty() || !other.queue.empty();
        }

        T get_value() const {
            return queue.front()->get_value();
        }

        BFSIterator& operator++() {
            auto node = queue.front();
            queue.pop();
            for (auto& child : node->get_children()) {
                queue.push(child);
            }
            return *this;
        }
};    
#endif