#ifndef BST_H
#define BST_H

//#include <compare>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class BST {

public:
    class Node;
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value) const;
    Node** find_parrent(int value) const;
    Node** find_successor(int value) const;
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, const BST& B);

private:
    Node* root;
};

class BST::Node {
public:
    Node(int value, Node* left, Node* right);
    Node();
    Node(const Node& node);
    //std::partial_ordering operator<=>(int V) const;
    bool operator==(int V) const;
    friend std::ostream& operator<<(std::ostream& os, const BST::Node& N);

    int value;
    Node* left;
    Node* right;
};

#endif //BST_H