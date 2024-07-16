# README

## Project: k-ary Tree Implementation with Iterators and GUI
**Author:** Ariel Levovich  
**Email:** ariel.levovich@msmail.ariel.ac.il

### Overview
This project implements a generic k-ary tree container that can hold keys of any type (e.g., numbers, strings, classes). The default tree is a binary tree (k=2). The implementation includes various tree traversal iterators, a function to convert the tree to a min-heap, and a graphical user interface (GUI) to visualize the tree using Qt.

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
The `BFSIterator` traverses the tree

 level-by-level from left to right (Breadth-First Search).

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

#### TreeWidget Class
The `TreeWidget` class visualizes the tree structure using Qt's `QWidget`. It handles rendering the tree on a window.

```cpp
#include <QPainter>
#include <QApplication>
#include <QEventLoop>
#include "TreeWidget.hpp"

TreeWidget::TreeWidget(std::shared_ptr<Node<double,2>> rootNode, QWidget* parent)
    : QWidget(parent), root(rootNode) {
	    renderConnection = connect(this, &TreeWidget::renderTree, this, &TreeWidget::handleRenderTree);
    }

TreeWidget::~TreeWidget() {
    disconnect(renderConnection); // Explicitly disconnect the signal
}

void TreeWidget::setRoot(std::shared_ptr<Node<double,2>> rootNode) {
    root = rootNode;
}

void TreeWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawTree(painter, root, width() / 2, 30, width() / 4, 50);
}

void TreeWidget::drawTree(QPainter& painter, std::shared_ptr<Node<double,2>> node, int x, int y, int hSpacing, int vSpacing) {
    if (!node) return;
    
    painter.drawEllipse(x - 15, y - 15, 30, 30);
    painter.drawText(x - 10, y + 5, QString::number(node->get_value()));

    int numChildren = node->get_children().size();
    int newX, newY;
    for (int i = 0; i < numChildren; ++i) {
        newX = x - (numChildren - 1) * hSpacing / 2 + i * hSpacing;
        newY = y + vSpacing;
        painter.drawLine(x, y + 15, newX, newY - 15);
        drawTree(painter, node->get_children()[i], newX, newY, hSpacing / 2, vSpacing);
    }
}

void TreeWidget::handleRenderTree() {
    show();
    repaint();
}

#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include "Node.hpp"

class TreeWidget : public QWidget {
    Q_OBJECT

public:
    explicit TreeWidget(std::shared_ptr<Node<double,2>> rootNode, QWidget* parent = nullptr);    

    ~TreeWidget(); // Destructor

    void setRoot(std::shared_ptr<Node<double,2>> rootNode);
    
signals:
    void renderTree(); // Signal to trigger rendering

public slots:
    void handleRenderTree(); // Slot to handle rendering

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<Node<double,2>> root;
    QMetaObject::Connection renderConnection; // Store the connection
    static void drawTree(QPainter& painter, std::shared_ptr<Node<double,2>> node, int x, int y, int hSpacing, int vSpacing);
};

#endif // TREEWIDGET_H
```

- **Constructor:** Initializes the widget with the root node of the tree.
- **Destructor:** Explicitly disconnects the render signal.
- **setRoot(std::shared_ptr<Node<double,2>> rootNode):** Sets the root node for rendering.
- **paintEvent(QPaintEvent*):** Handles the painting event to draw the tree.
- **drawTree(QPainter& painter, std::shared_ptr<Node<double,2>> node, int x, int y, int hSpacing, int vSpacing):** Recursively draws the tree nodes and edges.
- **handleRenderTree():** Slot to handle the render signal and trigger painting.

#### TreeWidgetComplex2 Class
The `TreeWidgetComplex2` class visualizes a binary tree with `Complex` values using Qt's `QWidget`.

```cpp
#include <QPainter>
#include <QApplication>
#include <QEventLoop>
#include "TreeWidgetComplex2.hpp"

TreeWidgetComplex2::TreeWidgetComplex2(std::shared_ptr<Node<Complex,2>> rootNode, QWidget* parent)
    : QWidget(parent), root(rootNode) {
	    renderConnection = connect(this, &TreeWidgetComplex2::renderTree, this, &TreeWidgetComplex2::handleRenderTree);
    }

TreeWidgetComplex2::~TreeWidgetComplex2() {
    disconnect(renderConnection); // Explicitly disconnect the signal
}

void TreeWidgetComplex2::setRoot(std::shared_ptr<Node<Complex,2>> rootNode) {
    root = rootNode;
}

void TreeWidgetComplex2::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawTree(painter, root, width() / 2, 30, width() / 4, 50);
}

void TreeWidgetComplex2::drawTree(QPainter& painter, std::shared_ptr<Node<Complex,2>> node, int x, int y, int hSpacing, int vSpacing) {
    if (!node) return;
    
    painter.drawEllipse(x - 20, y - 20, 40, 

40);
    Complex c = node->get_value();       
    
    painter.drawText(x - 10, y + 5, QString(c.toString().c_str()));

    int numChildren = node->get_children().size();
    int newX, newY;
    for (int i = 0; i < numChildren; ++i) {
        newX = x - (numChildren - 1) * hSpacing / 2 + i * hSpacing;
        newY = y + vSpacing;
        painter.drawLine(x, y + 20, newX, newY - 20);
        drawTree(painter, node->get_children()[i], newX, newY, hSpacing / 2, vSpacing);
    }
}

void TreeWidgetComplex2::handleRenderTree() {
    show();
    repaint();
}

#ifndef TREEWIDGET_COMPLEX2_H
#define TREEWIDGET_COMPLEX2_H

#include <QWidget>
#include "Node.hpp"
#include "Complex.hpp"

class TreeWidgetComplex2 : public QWidget {
    Q_OBJECT

public:
    explicit TreeWidgetComplex2(std::shared_ptr<Node<Complex,2>> rootNode, QWidget* parent = nullptr);    
    ~TreeWidgetComplex2(); // Destructor
    void setRoot(std::shared_ptr<Node<Complex,2>> rootNode);
    
signals:
    void renderTree(); // Signal to trigger rendering

public slots:
    void handleRenderTree(); // Slot to handle rendering

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<Node<Complex,2>> root;
    QMetaObject::Connection renderConnection; // Store the connection
    static void drawTree(QPainter& painter, std::shared_ptr<Node<Complex,2>> node, int x, int y, int hSpacing, int vSpacing);
};

#endif // TREEWIDGET_COMPLEX2_H
```

- **Constructor:** Initializes the widget with the root node of the tree.
- **Destructor:** Explicitly disconnects the render signal.
- **setRoot(std::shared_ptr<Node<Complex,2>> rootNode):** Sets the root node for rendering.
- **paintEvent(QPaintEvent*):** Handles the painting event to draw the tree.
- **drawTree(QPainter& painter, std::shared_ptr<Node<Complex,2>> node, int x, int y, int hSpacing, int vSpacing):** Recursively draws the tree nodes and edges.
- **handleRenderTree():** Slot to handle the render signal and trigger painting.

#### TreeWidgetDouble3 Class
The `TreeWidgetDouble3` class visualizes a ternary tree with `double` values using Qt's `QWidget`.

```cpp
#include <QPainter>
#include <QApplication>
#include <QEventLoop>
#include "TreeWidgetDouble3.hpp"

TreeWidgetDouble3::TreeWidgetDouble3(std::shared_ptr<Node<double,3>> rootNode, QWidget* parent)
    : QWidget(parent), root(rootNode) {
	    renderConnection = connect(this, &TreeWidgetDouble3::renderTree, this, &TreeWidgetDouble3::handleRenderTree);
    }

TreeWidgetDouble3::~TreeWidgetDouble3() {
    disconnect(renderConnection); // Explicitly disconnect the signal
}

void TreeWidgetDouble3::setRoot(std::shared_ptr<Node<double,3>> rootNode) {
    root = rootNode;
}

void TreeWidgetDouble3::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawTree(painter, root, width() / 2, 30, width() / 4, 50);
}

void TreeWidgetDouble3::drawTree(QPainter& painter, std::shared_ptr<Node<double,3>> node, int x, int y, int hSpacing, int vSpacing) {
    if (!node) return;
    
    painter.drawEllipse(x - 20, y - 20, 40, 40);
    painter.drawText(x - 10, y + 5, QString::number(node->get_value()));

    int numChildren = node->get_children().size();
    int newX, newY;
    for (int i = 0; i < numChildren; ++i) {
        newX = x - (numChildren - 1) * hSpacing / 2 + i * hSpacing;
        newY = y + vSpacing;
        painter.drawLine(x, y + 20, newX, newY - 20);
        drawTree(painter, node->get_children()[i], newX, newY, hSpacing / 2, vSpacing);
    }
}

void TreeWidgetDouble3::handleRenderTree() {
    show();
    repaint();
}

#ifndef TREEWIDGET_DOUBLE3_H
#define TREEWIDGET_DOUBLE3_H

#include <QWidget>
#include "Node.hpp"

class TreeWidgetDouble3 : public QWidget {
    Q_OBJECT

public:
    explicit TreeWidgetDouble3(std::shared_ptr<Node<double,3>> rootNode, QWidget* parent = nullptr);    
    ~TreeWidgetDouble3(); // Destructor
    void setRoot(std::shared_ptr<Node<double,3>> rootNode);
    
signals:
    void renderTree(); // Signal to trigger rendering

public slots:
    void handleRenderTree(); // Slot to handle rendering

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<Node<double,3>> root;
    QMetaObject::Connection renderConnection; // Store the connection
    static void drawTree(QPainter& painter, std::shared_ptr<Node<double,3>> node, int x, int y, int hSpacing, int vSpacing);
};

#endif // TREEWIDGET_DOUBLE3_H
```

- **Constructor:** Initializes the widget with the root node of the tree.
- **Destructor:** Explicitly disconnects the render signal.
- **setRoot(std::shared_ptr<Node<double,3>> rootNode):** Sets the root node for rendering.
- **paintEvent(QPaintEvent*):** Handles the painting event to draw the tree.
- **drawTree(QPainter& painter, std::shared_ptr<Node<double,3>> node, int x, int y, int hSpacing, int vSpacing):** Recursively draws the tree nodes and edges.
- **handleRenderTree():** Slot to handle the render signal and trigger painting.

### Shared Pointer Usage
In this project, `std::shared_ptr` is used extensively to manage the nodes of the tree. Shared pointers provide automatic memory management and ensure that nodes are deallocated properly when they are no longer needed. This approach helps prevent memory leaks and makes the code more robust and easier to maintain.

### Testing
Unit tests are written using the Doctest framework to ensure the correctness of the tree implementation and iterators. These tests cover various scenarios, including adding nodes, traversing the tree using different iterators, and converting the tree to a heap.

### Qt GUI Integration
The project includes a graphical user interface (GUI) to visualize the tree structure. The GUI is implemented using Qt and provides a visual representation of the tree with nodes and edges. The `TreeWidget`, `TreeWidgetComplex2`, and `TreeWidgetDouble3` classes handle the rendering of different types of trees.

### Compilation and Execution
The project includes a `Makefile` to build the application. The main class (`Demo.cpp`) demonstrates the functionality of the tree implementation and integrates the GUI for visualization.

To compile and run the project:
1. Run `make` to build the application.
2. Execute the application using `./cpp_ex4_24`.

The application will display the tree structures in a window, allowing you to visualize the nodes and their connections.

### Explanation of Using Only Header Files (`.hpp`) for Template Classes (Iterators)

In this project, you will notice that the template classes, particularly the iterators, are defined entirely within header files (`.hpp`). This is a common practice in C++ programming, and here's why:

#### Templates and Compilation
Templates in C++ are a powerful feature that allows for generic programming. However, templates are only instantiated when they are used. This means that the compiler needs to see the entire template definition when it compiles each translation unit that uses the template. By defining the template classes in header files, we ensure that the compiler has access to the full definition whenever it needs to instantiate the template.

#### Header Files (.hpp) for Template Classes
1. **Visibility:** When a template is used in multiple source files, defining the template in a header file ensures that the template's definition is available in each source file that includes the header. This allows the compiler to instantiate the template with the specific types used in those files.
  
2. **Avoiding Linker Errors:** If a template class is defined in a separate source file (.cpp) and only its declaration is in the header file, the compiler won't be able to instantiate the template correctly, leading to linker errors. By defining the template entirely in the header file, we avoid these issues.

3. **Ease of Use:** Keeping the template class definition in the header file makes the code easier to manage and understand. Users of the template class only need to include the header file to use the template, without worrying about linking with additional source files.

#### Example: Iterator Classes
In this project, all iterator classes (`PreOrderIterator`, `PostOrderIterator`, `InOrderIterator`, `BFSIterator`, `DFSIterator`, `HeapIterator`) are template classes defined within their respective header files. This ensures that any source file including these headers can instantiate the iterators with specific types as needed.
## README

### Overview of Tests

This project includes a comprehensive suite of tests for the `Tree`, `Node`, and `Complex` classes. The tests verify the correctness of various tree operations, including adding nodes and different tree traversal methods.

### Test Cases

#### Test Case 1: `Test add_root`
- **Description:** Verifies that a root node can be added to the tree.
- **Check:** Ensures the root node's value is correctly set.

#### Test Case 2: `Test add_sub_node`
- **Description:** Verifies that a child node can be added to a parent node.
- **Check:** Ensures the child node's value is correctly set in the parent node's children.

#### Test Case 3: `Test pre order scan tree<int,2>`
- **Description:** Verifies the pre-order traversal of a binary tree with integer values.
- **Check:** Ensures the nodes are visited in the correct pre-order sequence.

#### Test Case 4: `Test post order scan tree<int,2>`
- **Description:** Verifies the post-order traversal of a binary tree with integer values.
- **Check:** Ensures the nodes are visited in the correct post-order sequence.

#### Test Case 5: `Test in order scan tree<int,2>`
- **Description:** Verifies the in-order traversal of a binary tree with integer values.
- **Check:** Ensures the nodes are visited in the correct in-order sequence.

#### Test Case 6: `Test BFS scan tree<int,2>`
- **Description:** Verifies the BFS traversal of a binary tree with integer values.
- **Check:** Ensures the nodes are visited in the correct BFS sequence.

#### Test Case 7: `Test DFS scan tree<int,2>`
- **Description:** Verifies the DFS traversal of a binary tree with integer values.
- **Check:** Ensures the nodes are visited in the correct DFS sequence.

#### Test Case 8: `Test Heap scan tree<int,2>`
- **Description:** Verifies the heap traversal of a binary tree with integer values.
- **Check:** Ensures the nodes are visited in the correct min-heap sequence.

#### Test Case 9: `Test pre order scan tree<double,3>`
- **Description:** Verifies the pre-order traversal of a ternary tree with double values.
- **Check:** Ensures the nodes are visited in the correct pre-order sequence.

#### Test Case 10: `Test post order scan tree<double,3>`
- **Description:** Verifies the post-order traversal of a ternary tree with double values.
- **Check:** Ensures the nodes are visited in the correct post-order sequence.

#### Test Case 11: `Test in order scan tree<double,3>`
- **Description:** Verifies the in-order traversal of a ternary tree with double values.
- **Check:** Ensures the nodes are visited in the correct in-order sequence.

#### Test Case 12: `Test BFS scan tree<double,3>`
- **Description:** Verifies the BFS traversal of a ternary tree with double values.
- **Check:** Ensures the nodes are visited in the correct BFS sequence.

#### Test Case 13: `Test DFS scan tree<double,3>`
- **Description:** Verifies the DFS traversal of a ternary tree with double values.
- **Check:** Ensures the nodes are visited in the correct DFS sequence.

#### Test Case 14: `Test Heap scan tree<double,3>`
- **Description:** Verifies the heap traversal of a ternary tree with double values.
- **Check:** Ensures the nodes are visited in the correct min-heap sequence.

#### Test Case 15: `Test pre order scan tree<Complex,2>`
- **Description:** Verifies the pre-order traversal of a binary tree with complex number values.
- **Check:** Ensures the nodes are visited in the correct pre-order sequence.

#### Test Case 16: `Test post order scan tree<Complex,2>`
- **Description:** Verifies the post-order traversal of a binary tree with complex number values.
- **Check:** Ensures the nodes are visited in the correct post-order sequence.

#### Test Case 17: `Test in order scan tree<Complex,2>`
- **Description:** Verifies the in-order traversal of a binary tree with complex number values.
- **Check:** Ensures the nodes are visited in the correct in-order sequence.

#### Test Case 18: `Test BFS scan tree<Complex,2>`
- **Description:** Verifies the BFS traversal of a binary tree with complex number values.
- **Check:** Ensures the nodes are visited in the correct BFS sequence.

#### Test Case 19: `Test DFS scan tree<Complex,2>`
- **Description:** Verifies the DFS traversal of a binary tree with complex number values.
- **Check:** Ensures the nodes are visited in the correct DFS sequence.

#### Test Case 20: `Test Heap scan tree<Complex,2>`
- **Description:** Verifies the heap traversal of a binary tree with complex number values.
- **Check:** Ensures the nodes are visited in the correct min-heap sequence.

### Memory Leak Analysis

When running the tests with `valgrind` using the command `make valgrind`, we encountered several memory leaks. These leaks are mainly related to `realloc` and `malloc` calls. The errors were found in various parts of the program, especially related to the usage of Qt:

```
==3118961==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==3118961==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
...
==3118961==    definitely lost: 256 bytes in 1 blocks
==3118961==    indirectly lost: 32 bytes in 1 blocks
==3118961==      possibly lost: 1,152 bytes in 3 blocks
```

These memory leaks are attributed to Qt and not to the logic of our implementation. This was verified by running the demo without using Qt, which resulted in no memory leaks. Attempts to explicitly disconnect signals using `disconnect(renderConnection)` did not resolve the memory leaks.

Summary of memory leaks without Qt:
```
==2444108==    definitely lost: 0 bytes in 0 blocks
==2444108==    indirectly lost: 0 bytes in 0 blocks
==2444108==      possibly lost: 0 bytes in 0 blocks
```

### Conclusion

The test suite comprehensively covers the functionality of the `Tree` and `Node` classes. While the `valgrind` analysis highlighted some memory issues, they are related to Qt and not the implementation itself. Future work should consider further optimization and potential fixes for Qt-related memory management.

This explanation highlights why using header files for template classes is essential in C++ and how it benefits the project by simplifying compilation and avoiding common issues.
This README provides an overview of the project's structure and functionality. For detailed implementation and usage instructions, refer to the source code and comments within the code files.
