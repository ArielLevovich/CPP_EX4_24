#ifndef POSTORDER_ITERATOR_HPP
#define POSTORDER_ITERATOR_HPP

#include "Node.hpp"
// Post-order iterator
template<typename T, size_t K>
class PostOrderIterator {
private:
    std::stack<std::shared_ptr<Node<T,K>>> stack;
    std::shared_ptr<Node<T,K>> current;

    void advance() {
        if (stack.empty()) {
            current = nullptr;
            return;
        }

        auto node = stack.top();
        stack.pop();                

        bool lastChildWasProcessed = false;
        if (!stack.empty()) {
            auto parent = stack.top();
            auto& siblings = parent->get_children();
            auto it = std::find(siblings.begin(), siblings.end(), node);

            if (it != siblings.end() && ++it != siblings.end()) {
                node = *it;
                while (!node->get_children().empty()) {
                    stack.push(node);
                    node = node->get_children().front();
                }
                stack.push(node);
            } else {
                lastChildWasProcessed = true;    
            }
        } else {
            current = nullptr;
            return;
        }

        if (lastChildWasProcessed) {
            // if the last child was processed, process the parent.
            current = stack.top();
        } else {
            current = node;
        }
    }

public:
    explicit PostOrderIterator(std::shared_ptr<Node<T,K>> root) {
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
        advance();        
        return *this;
    }
};

#endif