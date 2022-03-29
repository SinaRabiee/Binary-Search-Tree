#include "bst.h"

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) const
{
    std::vector<BST::Node*> nodes;
    BST::Node* movingNode { root };
    std::vector<int> val;
    if (movingNode == nullptr)
        std::cout << "BST is empty" << std::endl;
    else {
        nodes.push_back(movingNode);
        while (!nodes.empty()) {
            val.push_back(nodes[0]->value);
            func(nodes[0]);
            nodes.erase(nodes.begin());
            if (movingNode->left != nullptr) {
                nodes.push_back(movingNode->left);
            }
            if (movingNode->right != nullptr) {
                nodes.push_back(movingNode->right);
            }
            movingNode = nodes[0];
        }
    }
}

size_t BST::length() const
{
    size_t count {};
    this->bfs([&](BST::Node*& node) { count++; });
    return count;
}

bool BST::add_node(int value)
{
    BST::Node* newNode { new BST::Node(value, nullptr, nullptr) };
    BST::Node* changingNode { root };

    if (root == nullptr) {
        root = newNode;
        return true;
    } else {
        while (true) {
            if (value > (changingNode->value)) {
                if (changingNode->right == nullptr) {
                    changingNode->right = newNode;
                    return true;
                } else
                    changingNode = changingNode->right;
            }

            if (value < (changingNode->value)) {
                if (changingNode->left == nullptr) {
                    changingNode->left = newNode;
                    return true;
                } else
                    changingNode = changingNode->left;
            }

            if (value == (changingNode->value))
                return false;
        }
    }
}

BST::Node** BST::find_node(int value) const
{
    BST::Node** movingNode { new BST::Node* };
    (*movingNode) = root;
    while (true) {
        if ((*movingNode) == nullptr)
            return nullptr;
        else {
            if ((*movingNode)->value == value)
                return movingNode;
            else if (value > (*movingNode)->value)
                (*movingNode) = (*movingNode)->right;
            else if (value < (*movingNode)->value)
                (*movingNode) = (*movingNode)->left;
        }
    }
}

BST::Node** BST::find_parrent(int value) const
{

    if (BST::find_node(value) == nullptr) {
        std::cout << "The value does not exist in the Tree" << std::endl;
        return nullptr;
    }

    BST::Node** movingNode { new BST::Node* };
    (*movingNode) = root;
    while (true) {
        if ((*movingNode)->right->value == value || (*movingNode)->left->value == value)
            return movingNode;
        else if ((*movingNode) == nullptr)
            return nullptr;
        else if (value > (*movingNode)->value)
            (*movingNode) = (*movingNode)->right;
        else if (value < (*movingNode)->value)
            (*movingNode) = (*movingNode)->left;
    }
}

BST::Node** BST::find_successor(int value) const
{
    BST::Node** movingNode { new BST::Node* };
    if (BST::find_node(value) == nullptr) {
        std::cout << "The value does not exist in the Tree" << std::endl;
        return nullptr;
    } else {
        (*movingNode) = *this->find_node(value);
        if ((*movingNode)->left == nullptr) {
            return movingNode;
        } else {
            (*movingNode) = (*movingNode)->left;
            while ((*movingNode)->right != nullptr) {
                (*movingNode) = (*movingNode)->right;
            }
            return movingNode;
        }
    }
}

BST::Node::Node(int value, Node* left, Node* right)
    : value { value }
    , left { left }
    , right { right }
{
}

BST::Node::Node()
    : value { 0 }
    , left { nullptr }
    , right { nullptr }
{
}
BST::Node::Node(const Node& node)
    : value { node.value }
    , left { node.left }
    , right { node.right }
{
}
/*
std::partial_ordering BST::Node::operator<=>(int V) const
{
    return this->value <=> V;
}
*/
bool BST::Node::operator==(int V) const
{
    return this->value ==  V;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& N)
{
    os.width(3);
    os << &N << "    => value:" << std::left;
    os.width(3);
    os << N.value << "  left:" << std::left;
    os.width(15);
    os << N.left << "  right:" << N.right << std::left;
    return os;
}