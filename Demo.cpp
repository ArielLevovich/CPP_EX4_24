// ariel.levovich@msmail.ariel.ac.il 
/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include <memory>
#include <QApplication>
#include "Tree.hpp"
#include "Complex.hpp"
#include "TreeWidget.hpp"
#include "TreeWidgetDouble3.hpp"
#include "TreeWidgetComplex2.hpp"
using namespace std;

// Global pointer to QApplication
QApplication* app = nullptr;
TreeWidget* treeWidget = nullptr;
TreeWidgetDouble3* treeWidgetDouble3 = nullptr;
TreeWidgetComplex2* treeWidgetComplex2 = nullptr;

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.toString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tree<double,2>& tree) {    
    auto node = tree.getRoot();
    if (!node) {
        os << "Empty tree" << endl;
        return os;
    }
    os << node->get_value();
    if (!node->get_children().empty()) {
        os << " [";
        for (size_t i = 0; i < node->get_children().size(); ++i) {
            if (i > 0) os << ", ";
            
            Tree<double,2> recursiveTree; 
            recursiveTree.add_root(*(node->get_children()[i]));
            os << recursiveTree;
        }
        os << "]";
    }
    
    if (treeWidget) {
        // Set the root node for rendering and trigger the render signal
        treeWidget->setRoot(node);
        emit treeWidget->renderTree();
    } 
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tree<double,3>& tree) {    
    auto node = tree.getRoot();
    if (!node) {
        os << "Empty tree" << endl;
        return os;
    }
    os << node->get_value();
    if (!node->get_children().empty()) {
        os << " [";
        for (size_t i = 0; i < node->get_children().size(); ++i) {
            if (i > 0) os << ", ";
            
            Tree<double,3> recursiveTree; 
            recursiveTree.add_root(*(node->get_children()[i]));
            os << recursiveTree;
        }
        os << "]";
    }
    
    if (treeWidgetDouble3) {
        // Set the root node for rendering and trigger the render signal
        treeWidgetDouble3->setRoot(node);
        emit treeWidgetDouble3->renderTree();
    } 
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tree<Complex,2>& tree) {    
    auto node = tree.getRoot();    
    if (!node) {
        os << "Empty tree" << endl;
        return os;
    }    
    os << node->get_value();
    
    if (!node->get_children().empty()) {
        os << " [";
        for (size_t i = 0; i < node->get_children().size(); ++i) {
            if (i > 0) os << ", ";
            
            Tree<Complex,2> recursiveTree; 
            recursiveTree.add_root(*(node->get_children()[i]));
            os << recursiveTree;
        }
        os << "]";
    }
    
    if (treeWidgetComplex2) {
        // Set the root node for rendering and trigger the render signal
        treeWidgetComplex2->setRoot(node);
        emit treeWidgetComplex2->renderTree();
    } 
    
    return os;
}

void createBinaryTreeWithDoubleValuesAndTraverseTheTree(Tree<double,2>& tree) {
    Node<double,2> root2_node = Node<double,2>(1.1);    
    tree.add_root(root2_node);
    Node<double,2> m1 = Node<double,2>(1.2);
    Node<double,2> m2 = Node<double,2>(1.3);
    Node<double,2> m3 = Node<double,2>(1.4);
    Node<double,2> m4 = Node<double,2>(1.5);
    Node<double,2> m5 = Node<double,2>(1.6);

    tree.add_sub_node(root2_node, m1);
    tree.add_sub_node(root2_node, m2);
    tree.add_sub_node(m1, m3);
    tree.add_sub_node(m1, m4);
    tree.add_sub_node(m2, m5);
   
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */
    
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1    
    cout << endl;
    
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;
    
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    // min heap
    for (auto node = tree.myHeap(); node.isNotEmpty(); ++node)
    {
        cout << node.get_value() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;        
}

void createTrinaryTreeWithDoubleValuesAndTraverseTheTree(Tree<double,3>& three_ary_tree) {
    Node<double,3> root3_node = Node<double,3>(1.1);
    Node<double,3> n1 = Node<double,3>(1.2);
    Node<double,3> n2 = Node<double,3>(1.3);
    Node<double,3> n3 = Node<double,3>(1.4);
    Node<double,3> n4 = Node<double,3>(1.5);
    Node<double,3> n5 = Node<double,3>(1.6);
    Node<double,3> n6 = Node<double,3>(1.7);
    Node<double,3> n7 = Node<double,3>(1.8);
    Node<double,3> n8 = Node<double,3>(1.9);
    Node<double,3> n9 = Node<double,3>(1.27);
    Node<double,3> n10 = Node<double,3>(1.11);
    Node<double,3> n11 = Node<double,3>(1.12);
    Node<double,3> n12 = Node<double,3>(1.13);
    Node<double,3> n13 = Node<double,3>(1.14);
    Node<double,3> n14 = Node<double,3>(1.15);
    Node<double,3> n15 = Node<double,3>(1.16);
    Node<double,3> n16 = Node<double,3>(1.17);
    Node<double,3> n17 = Node<double,3>(1.18);
    Node<double,3> n18 = Node<double,3>(1.19);
    Node<double,3> n19 = Node<double,3>(1.28);
    Node<double,3> n20 = Node<double,3>(1.21);
    Node<double,3> n21 = Node<double,3>(1.22);
    Node<double,3> n22 = Node<double,3>(1.23);
    Node<double,3> n23 = Node<double,3>(1.24);
    Node<double,3> n24 = Node<double,3>(1.25);
    Node<double,3> n25 = Node<double,3>(1.26);
    
    three_ary_tree.add_root(root3_node);
    three_ary_tree.add_sub_node(root3_node, n1);
    three_ary_tree.add_sub_node(root3_node, n2);
    three_ary_tree.add_sub_node(root3_node, n6);
    three_ary_tree.add_sub_node(n1, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n1, n10);
    
    three_ary_tree.add_sub_node(n2, n5);
    three_ary_tree.add_sub_node(n2, n14);
    
    three_ary_tree.add_sub_node(n6, n22);
    three_ary_tree.add_sub_node(n6, n23);
    three_ary_tree.add_sub_node(n6, n24);
    three_ary_tree.add_sub_node(n24, n25);

    three_ary_tree.add_sub_node(n3, n7);
    three_ary_tree.add_sub_node(n3, n8);
    three_ary_tree.add_sub_node(n3, n9);
    
    three_ary_tree.add_sub_node(n4, n11);
    three_ary_tree.add_sub_node(n4, n12);
    three_ary_tree.add_sub_node(n10, n13);

    three_ary_tree.add_sub_node(n5, n15);
    three_ary_tree.add_sub_node(n5, n16);

    three_ary_tree.add_sub_node(n14, n17);
    three_ary_tree.add_sub_node(n14, n18);
    three_ary_tree.add_sub_node(n14, n19);

    three_ary_tree.add_sub_node(n19, n20);
    three_ary_tree.add_sub_node(n19, n21);

    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.8, 1.9, 1.105, 1.5, 1.12, 1.13, 1.11, 1.14, 1.3, 1.6, 1.16, 1.17, 1.15, 1.18, 1.19, 1.205, 1.21, 1.22, 1.7, 1.23, 1.24, 1.25, 1.26
    cout << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.8, 1.9, 1.105, 1.4, 1.12, 1.13, 1.5, 1.14, 1.11, 1.2, 1.16, 1.17, 1.6, 1.18, 1.19, 1.21, 1.22, 1.205, 1.15, 1.3, 1.23, 1.24, 1.26, 1.25, 1.7, 1.1
    cout << endl;
    
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.8, 1.4, 1.9, 1.105, 1.2, 1.12, 1.5, 1.13, 1.14, 1.11, 1.1, 1.16, 1.6, 1.17, 1.3, 1.18, 1.15, 1.19, 1.21, 1.205, 1.22, 1.23, 1.7, 1.24, 1.26, 1.25
    cout << endl;     
    
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.7, 1.4, 1.5, 1.11, 1.6, 1.15, 1.23, 1.24, 1.25, 1.8, 1.9, 1.105, 1.12, 1.13, 1.14, 1.16, 1.17, 1.18, 1.19, 1.205, 1.26, 1.21, 1.22
    cout << endl;  
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.8, 1.9, 1.105, 1.5, 1.12, 1.13, 1.11, 1.14, 1.3, 1.6, 1.16, 1.17, 1.15, 1.18, 1.19, 1.205, 1.21, 1.22, 1.7, 1.23, 1.24, 1.25, 1.26
    cout << endl;
    for (auto node = three_ary_tree.myHeap(); node.isNotEmpty(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.105, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.2, 1.205, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9
    cout << endl;             
}

void createBinaryTreeWithComplexValuesAndTraverseTheTree(Tree<Complex,2>& tree) {
    Complex c11(1,1);
    Complex c12(1,2);
    Complex c13(1,3);
    Complex c14(1,4);
    Complex c15(1,5);
    Complex c16(1,6);

    Node<Complex,2> root2_node = Node<Complex,2>(c11);
    tree.add_root(root2_node);
    
    Node<Complex,2> m1 = Node<Complex,2>(c12);
    Node<Complex,2> m2 = Node<Complex,2>(c13);
    Node<Complex,2> m3 = Node<Complex,2>(c14);
    Node<Complex,2> m4 = Node<Complex,2>(c15);
    Node<Complex,2> m5 = Node<Complex,2>(c16);

    tree.add_sub_node(root2_node, m1);
    tree.add_sub_node(root2_node, m2);
    tree.add_sub_node(m1, m3);
    tree.add_sub_node(m1, m4);
    tree.add_sub_node(m2, m5);
   
    // The tree should look like:
    /**
     *       root = (1,1)
     *     /           \
     *    (1,2)         (1,3)
     *   /    \          /
     *  (1,4)  (1,5)   (1,6)
     */
    
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1    
    cout << endl;
    
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;
    
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    // min heap
    for (auto node = tree.myHeap(); node.isNotEmpty(); ++node)
    {
        cout << node.get_value() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;      
}

int main(int argc, char* argv[])
{
    // Create the QApplication object
    QApplication appInstance(argc, argv);
    app = &appInstance;

    Tree<double,2> tree;
    createBinaryTreeWithDoubleValuesAndTraverseTheTree(tree);    
    
    // Create the TreeWidget object
    TreeWidget treeWidgetInstance(tree.getRoot());
    treeWidget = &treeWidgetInstance;
    treeWidget->resize(400, 200);

    cout << tree << endl; // Should print the graph using GUI. 

    // Start the Qt event loop
    app->exec();    

    Tree<double,3> treeDouble3;
    createTrinaryTreeWithDoubleValuesAndTraverseTheTree(treeDouble3);    

    // Create the TreeWidget object
    TreeWidgetDouble3 treeWidgetDouble3Instance(treeDouble3.getRoot());
    treeWidgetDouble3 = &treeWidgetDouble3Instance;
    treeWidgetDouble3->resize(1200, 400);

    cout << treeDouble3 << endl; // Should print the graph using GUI.

    // Start the Qt event loop
    app->exec();  
    
    Tree<Complex,2> treeComplex2;
    createBinaryTreeWithComplexValuesAndTraverseTheTree(treeComplex2);      

    // Create the TreeWidget object
    TreeWidgetComplex2 treeWidgetComplex2Instance(treeComplex2.getRoot());
    treeWidgetComplex2 = &treeWidgetComplex2Instance;
    treeWidgetComplex2->resize(400, 200);

    cout << treeComplex2 << endl; // Should print the graph using GUI.  

    // Start the Qt event loop
    int result = app->exec(); 
    return result;	    
}
