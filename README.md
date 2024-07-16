# README

## Project: k-ary Tree Implementation with Iterators
**Author:** Ariel Levovich  
**Email:** ariel.levovich@msmail.ariel.ac.il

### Overview
This project implements a generic k-ary tree container that can hold keys of any type (e.g., numbers, strings, classes). The default tree is a binary tree (k=2). The implementation includes various tree traversal iterators and a function to convert the tree to a min-heap.

### Class Hierarchy and Description

#### Tree Class
The `Tree` class manages the tree structure and provides methods to add nodes and traverse the tree using various iterators.

```cpp
template<typename T, size_t K>
class Tree {
private:
    std::shared_ptr<Node<T,K>> root;    

public:
    explicit Tree() : root(nullptr) {}
    ~Tree() { clear(); }

    std::shared_ptr<Node<T,K>> getRoot() const { return root; }
    void clear() { root = nullptr; }
    
    void add_root(const Node<T,K>& node) {
        root = std::make_shared<Node<T,K>>(node);
    }

    void add_sub_node(Node<T,K>& parent_node, const Node<T,K>& child_node) {    
        auto tree_node = find_node(root, parent_node.get_value());            
        if (tree_node) {
            tree_node->add_child(std::make_shared<Node<T,K>>(child_node));
        }
    }
    
    PreOrderIterator<T,K> begin_pre_order() { return PreOrderIterator<T,K>(root); }
    PreOrderIterator<T,K> end_pre_order() { return PreOrderIterator<T,K>(nullptr); }
    PostOrderIterator<T,K> begin_post_order() { return PostOrderIterator<T,K>(root); }
    PostOrderIterator<T,K> end_post_order() { return PostOrderIterator<T,K>(nullptr); }
    InOrderIterator<T,K> begin_in_order() { return InOrderIterator<T,K>(root); }
    InOrderIterator<T,K> end_in_order() { return InOrderIterator<T,K>(nullptr); }
    BFSIterator<T,K> begin_bfs_scan() { return BFSIterator<T,K>(root); }
    BFSIterator<T,K> end_bfs_scan() { return BFSIterator<T,K>(nullptr); }
    DFSIterator<T,K> begin_dfs_scan() { return DFSIterator<T,K>(root); }
    DFSIterator<T,K> end_dfs_scan() { return DFSIterator<T,K>(nullptr); }
    HeapIterator<T,K> myHeap() { return HeapIterator<T,K>(root); }
    HeapIterator<T,K> emptyHeap() { std::shared_ptr<Node<T,K>> empty; return HeapIterator<T,K>(empty); }
    
private:
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
```

- **Constructor:** Initializes an empty tree.
- **Destructor:** Clears the tree.
- **add_root(Node<T, K> node):** Adds a root node to the tree.
- **add_sub_node(Node<T, K>& parent_node, const Node<T, K>& child_node):** Adds a child node to a given parent node.
- **Traversal Methods:** Provides iterators for different traversal methods (pre-order, post-order, in-order, BFS, DFS).
- **myHeap():** Converts the tree to a min-heap and returns an iterator to traverse the heap.

#### Node Class
The `Node` class represents each node in the tree, holding a value and pointers to child nodes.

```cpp
template<typename T, size_t K>
class Node {
private:
    T value;
    std::vector<std::shared_ptr<Node<T,K>>> children;

public:
    Node(const T& value) : value(value) {}
    
    T get_value() const { return value; }
    std::vector<std::shared_ptr<Node<T,K>>>& get_children() { return children; }

    void add_child(std::shared_ptr<Node<T,K>> child) {
        if (children.size() < K) {
            children.push_back(child);
        }
    }
};
```

- **Constructor:** Initializes a node with a value.
- **get_value():** Returns the node's value.
- **get_children():** Returns the node's children.
- **add_child(std::shared_ptr<Node<T, K>> child):** Adds a child to the node.

#### PreOrderIterator Class
The `PreOrderIterator` traverses the tree in pre-order: current node -> left subtree -> right subtree.

```cpp
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
```

- **Constructor:** Initializes the iterator with the root node.
- **Traversal Logic:** Uses a stack to manage traversal in pre-order.

#### PostOrderIterator Class
The `PostOrderIterator` traverses the tree in post-order: left subtree -> right subtree -> current node.

```cpp
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
```

- **Constructor:** Initializes the iterator with the root node.
- **Traversal Logic:** Uses a stack to manage traversal in post-order.

#### InOrderIterator Class
The `InOrderIterator` traverses the tree in in-order: left subtree -> current node -> right subtree.

```cpp
template<typename T, size_t K>
class InOrderIterator {
private:
    std::stack<std::shared_ptr<Node<T,K>>> stack;
    std::shared_ptr<Node<T,K>> current;

    void push_left(std::shared_ptr<Node<T,K>> node) {
        while (node) {
            stack.push(node);
            auto children = node->get_children();
            node = (children.empty()) ? nullptr : children.front();
        }
    }

public:
    explicit InOrderIterator(std::shared_ptr<Node<T,K>> root) {
        push_left(root);
        current = (stack.empty()) ? nullptr : stack.top();
    }

    bool operator!=(const InOrderIterator& other) const {
        return current != other.current;
    }

    T get_value() const {
        return current->get_value();
    }

    InOrderIterator& operator++() {
        if (!stack.empty()) {
            auto node = stack.top();
            stack.pop();
            auto children = node->get_children();
            if (!children.empty()) {
                if (children.size() == 1) {
                    push_left(nullptr);
                } else {
                    for (unsigned int i = children.size()-1; i >= 1; i--) {
                        push_left(children[i]);
                    }
                }
            }
            current = (stack.empty()) ? nullptr : stack.top();
        }
        return *this;
    }
};
```

- **Constructor:** Initializes the iterator with the root node.
- **Traversal Logic:** Uses a stack to manage traversal in in-order.

#### BFSIterator Class
The `BFSIterator` traverses the tree level

-by-level from left to right (Breadth-First Search).

```cpp
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
```

- **Constructor:** Initializes the iterator with the root node.
- **Traversal Logic:** Uses a queue to manage traversal in BFS order.

#### DFSIterator Class
The `DFSIterator` traverses the tree using Depth-First Search.

```cpp
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
```

- **Constructor:** Initializes the iterator with the root node.
- **Traversal Logic:** Uses a stack to manage traversal in DFS order.

#### HeapIterator Class
The `HeapIterator` converts the tree to a min-heap and provides traversal over the heap.

```cpp
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
```

- **Constructor:** Initializes the iterator with the root node and builds a min-heap.
- **Traversal Logic:** Uses a vector to manage the heap and standard heap operations for traversal.

#### Complex Class
The `Complex` class represents complex numbers and is used to demonstrate the functionality of the tree with a custom class.

```cpp
class Complex {
private:
    double real;    
    double imag;    

public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}
    Complex(const Complex& c) : real(c.real), imag(c.imag) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }    

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    bool operator>(const Complex& other) const {
        return (std::sqrt(real * real + imag * imag) > std::sqrt(other.real * other.real + other.imag * other.imag));
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << real;
        if (imag >= 0) {
            oss << "+" << imag << "i";
        } else {
            oss << "-" << -imag << "i";
        }
        return oss.str();        
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};
```

- **Constructor:** Initializes a complex number with real and imaginary parts.
- **Operator Overloads:** Provides comparison operators and stream insertion for complex numbers.
- **toString():** Returns the string representation of the complex number.

### Shared Pointer Usage
The `std::shared_ptr` is used to manage the nodes in the tree. This choice ensures that memory management is handled automatically, preventing memory leaks and dangling pointers. When a `shared_ptr` goes out of scope or is reassigned, the memory it points to is automatically deallocated if no other `shared_ptr` instances are pointing to it. This approach simplifies memory management, especially in complex structures like trees where nodes can have multiple parents and children.

### Example Usage
```cpp
#include "Tree.hpp"
#include "Complex.hpp"

int main() {
    Tree<int, 2> binary_tree;
    Node<int, 2> root(1);
    Node<int, 2> left_child(2);
    Node<int, 2> right_child(3);
    
    binary_tree.add_root(root);
    binary_tree.add_sub_node(root, left_child);
    binary_tree.add_sub_node(root, right_child);
    
    for (auto it = binary_tree.begin_pre_order(); it != binary_tree.end_pre_order(); ++it) {
        std::cout << it.get_value() << " ";
    }
    std::cout << std::endl;
    
    // Complex number demonstration
    Complex c1(1, 2);
    Complex c2(3, 4);
    
    std::cout << "Complex number c1: " << c1 << std::endl;
    std::cout << "Complex number c2: " << c2 << std::endl;

    return 0;
}
```

### Makefile
The Makefile should compile the project and run the main program:
```makefile
all: tree

tree: main.o
    g++ -o tree main.o

main.o: main.cpp Tree.hpp Complex.hpp
    g++ -c main.cpp

clean:
    rm -f *.o tree
```

### GUI
For the GUI part of the project, refer to the [Qt for Beginners](https://wiki.qt.io/Qt_for_Beginners) and the [YouTube tutorial](https://www.youtube.com/watch?v=cXojtB8vS2E). The GUI should provide a visual representation of the tree structure.

### Testing
Comprehensive tests should be written to ensure all functionalities of the tree and iterators work correctly. Use various data types and complex structures to test the robustness of the implementation. 

### Conclusion
This project demonstrates the implementation of a flexible k-ary tree structure with various traversal methods, utilizing modern C++ features like templates and smart pointers to ensure safe and efficient memory management. The example usage and provided GUI guidelines aim to help users visualize and understand the tree's structure and operations.
