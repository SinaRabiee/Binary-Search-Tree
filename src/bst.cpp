#include "bst.h"

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