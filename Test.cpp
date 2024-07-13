// ariel.levovich@msmail.ariel.ac.il 
#include <iomanip> // for std::setprecision
#include "doctest.h"
#include "Tree.hpp"
#include "Complex.hpp"

using namespace std;

void createInt2Tree(Tree<int,2>& tree) {
    // The tree should look like:
    /**
     *       root = (8)
     *     /           \
     *    (13)         (5)
     *   /    \        /  \
     *  (6)  (7)     (3)  (2)
     */
    Node<int,2> root2_node = Node<int,2>(8);    
    tree.add_root(root2_node);
    Node<int,2> m1 = Node<int,2>(13);
    Node<int,2> m2 = Node<int,2>(5);
    Node<int,2> m3 = Node<int,2>(6);
    Node<int,2> m4 = Node<int,2>(7);
    Node<int,2> m5 = Node<int,2>(3);
    Node<int,2> m6 = Node<int,2>(2);

    tree.add_sub_node(root2_node, m1);
    tree.add_sub_node(root2_node, m2);
    tree.add_sub_node(m1, m3);
    tree.add_sub_node(m1, m4);
    tree.add_sub_node(m2, m5);
    tree.add_sub_node(m2, m6);
}

TEST_CASE("1. Test add_root")
{
    Tree<int,2> tree;
    Node<int,2> root = Node<int,2>(999);    
    tree.add_root(root);
    CHECK(tree.getRoot()->get_value() == 999);    
}

TEST_CASE("2. Test add_sub_node")
{
    Tree<int,2> tree;
    Node<int,2> root = Node<int,2>(5);    
    tree.add_root(root);
    Node<int,2> node = Node<int,2>(13);

    tree.add_sub_node(root, node);
    CHECK(tree.getRoot()->get_children()[0]->get_value() == 13);       
}

TEST_CASE("3. Test pre order scan tree<int,2>")
{    
    Tree<int,2> tree;
    createInt2Tree(tree);

    std::string output;    
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        output += std::to_string(node.get_value());
        output += " ";        
    }
    CHECK(output == "8 13 6 7 5 3 2 "); 
}

TEST_CASE("4. Test post order scan tree<int,2>")
{
    Tree<int,2> tree;
    createInt2Tree(tree);
    
    std::string output;    
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        output += std::to_string(node.get_value());
        output += " ";        
    }
    CHECK(output == "6 7 13 3 2 5 8 "); 
}

TEST_CASE("5. Test in order scan tree<int,2>")
{
    Tree<int,2> tree;
    createInt2Tree(tree);
    
    std::string output;    
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        output += std::to_string(node.get_value());
        output += " ";        
    }
    CHECK(output == "6 13 7 8 3 5 2 ");  
}

TEST_CASE("6 - Test BFS scan tree<int,2>")
{
    Tree<int,2> tree;
    createInt2Tree(tree);
    
    std::string output;    
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        output += std::to_string(node.get_value());
        output += " ";        
    }
    CHECK(output == "8 13 5 6 7 3 2 ");  
}

TEST_CASE("7 - Test DFS scan tree<int,2>")
{
    Tree<int,2> tree;
    createInt2Tree(tree);
    
    std::string output;    
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        output += std::to_string(node.get_value());
        output += " ";        
    }
    CHECK(output == "8 13 6 7 5 3 2 ");  
}

TEST_CASE("8 - Test Heap scan tree<int,2>")
{
    Tree<int,2> tree;
    createInt2Tree(tree);
    
    std::string output;    
    for (auto node = tree.myHeap(); node.isNotEmpty(); ++node)
    {
        output += std::to_string(node.get_value());
        output += " ";        
    }
    CHECK(output == "2 3 5 6 7 8 13 ");  
}

void createDouble3Tree(Tree<double,3>& tree) {
    // The tree should look like:
    /**
     *           root = (1)
     *     /            |             \
     *    (2)          (3)            (5)
     *   /  |  \      /  \   \        /   \     \
     *(8) (13) (21) (34) (55) (89)  (144) (233) (377)
     *               /  \
     *            (400) (269)
     * 
     */
    Node<double,3> root = Node<double,3>(1);    
    tree.add_root(root);
    Node<double,3> m1 = Node<double,3>(2);
    Node<double,3> m2 = Node<double,3>(3);
    Node<double,3> m3 = Node<double,3>(5);
    Node<double,3> m4 = Node<double,3>(8);
    Node<double,3> m5 = Node<double,3>(13);
    Node<double,3> m6 = Node<double,3>(21);
    Node<double,3> m7 = Node<double,3>(34);
    Node<double,3> m8 = Node<double,3>(55);
    Node<double,3> m9 = Node<double,3>(89);
    Node<double,3> m10 = Node<double,3>(144);
    Node<double,3> m11 = Node<double,3>(233);
    Node<double,3> m12 = Node<double,3>(377);
    Node<double,3> m13 = Node<double,3>(400);
    Node<double,3> m14 = Node<double,3>(269);

    tree.add_sub_node(root, m1);
    tree.add_sub_node(root, m2);
    tree.add_sub_node(root, m3);
    tree.add_sub_node(m1, m4);
    tree.add_sub_node(m1, m5);
    tree.add_sub_node(m1, m6);
    tree.add_sub_node(m2, m7);
    tree.add_sub_node(m2, m8);
    tree.add_sub_node(m2, m9);
    tree.add_sub_node(m3, m10);
    tree.add_sub_node(m3, m11);
    tree.add_sub_node(m3, m12);
    tree.add_sub_node(m7, m13);
    tree.add_sub_node(m7, m14);
}

TEST_CASE("9. Test pre order scan tree<double,3>")
{
    Tree<double,3> tree;
    createDouble3Tree(tree);    
    
    std::string output;

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node.get_value();
        output += oss.str();    
        output += " ";        
    }
    CHECK(output == "1.0 2.0 8.0 13.0 21.0 3.0 34.0 400.0 269.0 55.0 89.0 5.0 144.0 233.0 377.0 ");     
}

TEST_CASE("10. Test post order scan tree<double,3>")
{
    Tree<double,3> tree;
    createDouble3Tree(tree);    
    
    std::string output;

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node.get_value();
        output += oss.str();    
        output += " ";        
    }
    CHECK(output == "8.0 13.0 21.0 2.0 400.0 269.0 34.0 55.0 89.0 3.0 144.0 233.0 377.0 5.0 1.0 "); 
}

TEST_CASE("11. Test in order scan tree<double,3>")
{
    Tree<double,3> tree;
    createDouble3Tree(tree);    
    
    std::string output;

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node.get_value();
        output += oss.str();    
        output += " ";        
    }
    CHECK(output == "8.0 2.0 13.0 21.0 1.0 400.0 34.0 269.0 3.0 55.0 89.0 144.0 5.0 233.0 377.0 ");    
}

TEST_CASE("12 - Test BFS scan tree<double,3>")
{
    Tree<double,3> tree;
    createDouble3Tree(tree);    
    
    std::string output;

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node.get_value();
        output += oss.str();    
        output += " ";        
    }
    CHECK(output == "1.0 2.0 3.0 5.0 8.0 13.0 21.0 34.0 55.0 89.0 144.0 233.0 377.0 400.0 269.0 ");
}

TEST_CASE("13 - Test DFS scan tree<double,3>")
{
    Tree<double,3> tree;
    createDouble3Tree(tree);    
    
    std::string output;

    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node.get_value();
        output += oss.str();    
        output += " ";        
    }
    CHECK(output == "1.0 2.0 8.0 13.0 21.0 3.0 34.0 400.0 269.0 55.0 89.0 5.0 144.0 233.0 377.0 ");
}

TEST_CASE("14 - Test Heap scan tree<double,3>")
{
    Tree<double,3> tree;
    createDouble3Tree(tree);    
    
    std::string output;

    for (auto node = tree.myHeap(); node.isNotEmpty(); ++node)
    {        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node.get_value();
        output += oss.str();    
        output += " ";        
    }
    CHECK(output == "1.0 2.0 3.0 5.0 8.0 13.0 21.0 34.0 55.0 89.0 144.0 233.0 269.0 377.0 400.0 ");
}

void createComplex2Tree(Tree<Complex,2>& tree) {
    // The tree should look like:
    /**
     *       root = (8-i)
     *     /           \
     *    (13-i)         (5-i)
     *   /    \        /  \
     *  (6-i)  (7-i)     (3-i)  (2-i)
     */
    Complex c1(8,-1);
    Complex c2(13,-1);
    Complex c3(5,-1);
    Complex c4(6,-1);
    Complex c5(7,-1);
    Complex c6(3,-1);
    Complex c7(2,-1);
    Node<Complex,2> root = Node<Complex,2>(c1);    
    tree.add_root(root);
    Node<Complex,2> m1 = Node<Complex,2>(c2);
    Node<Complex,2> m2 = Node<Complex,2>(c3);
    Node<Complex,2> m3 = Node<Complex,2>(c4);
    Node<Complex,2> m4 = Node<Complex,2>(c5);
    Node<Complex,2> m5 = Node<Complex,2>(c6);
    Node<Complex,2> m6 = Node<Complex,2>(c7);

    tree.add_sub_node(root, m1);
    tree.add_sub_node(root, m2);
    tree.add_sub_node(m1, m3);
    tree.add_sub_node(m1, m4);
    tree.add_sub_node(m2, m5);
    tree.add_sub_node(m2, m6);
}

TEST_CASE("15. Test pre order scan tree<Complex,2>")
{
    Tree<Complex,2> tree;
    createComplex2Tree(tree);

    std::string output;    
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        output += node.get_value().toString();
        output += " ";        
    }
    CHECK(output == "8-1i 13-1i 6-1i 7-1i 5-1i 3-1i 2-1i "); 
}

TEST_CASE("16. Test post order scan tree<Complex,2>")
{
    Tree<Complex,2> tree;
    createComplex2Tree(tree);

    std::string output;    
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        output += node.get_value().toString();
        output += " ";        
    }
    CHECK(output == "6-1i 7-1i 13-1i 3-1i 2-1i 5-1i 8-1i "); 
}

TEST_CASE("17. Test in order scan tree<Complex,2>")
{
    Tree<Complex,2> tree;
    createComplex2Tree(tree);

    std::string output;    
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        output += node.get_value().toString();
        output += " ";        
    }
    CHECK(output == "6-1i 13-1i 7-1i 8-1i 3-1i 5-1i 2-1i ");   
}

TEST_CASE("18 - Test BFS scan tree<Complex,2>")
{
    Tree<Complex,2> tree;
    createComplex2Tree(tree);

    std::string output;    
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        output += node.get_value().toString();
        output += " ";        
    }
    CHECK(output == "8-1i 13-1i 5-1i 6-1i 7-1i 3-1i 2-1i "); 
}

TEST_CASE("19 - Test DFS scan tree<Complex,2>")
{
    Tree<Complex,2> tree;
    createComplex2Tree(tree);

    std::string output;    
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        output += node.get_value().toString();
        output += " ";        
    }
    CHECK(output == "8-1i 13-1i 6-1i 7-1i 5-1i 3-1i 2-1i "); 
}

TEST_CASE("20 - Test Heap scan tree<Complex,2>")
{
    Tree<Complex,2> tree;
    createComplex2Tree(tree);

    std::string output;    
    for (auto node = tree.myHeap(); node.isNotEmpty(); ++node)
    {
        output += node.get_value().toString();
        output += " ";        
    }
    CHECK(output == "2-1i 3-1i 5-1i 6-1i 7-1i 8-1i 13-1i ");
}
