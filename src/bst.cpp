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

bool BST::delete_node(int value)
{
    auto removing { this->find_node(value) };

    if (removing == nullptr)
        return false;

    auto removingSuc { this->find_successor(value) };
    size_t flag {};
    if ((*removing)->right == nullptr)
        flag++;
    if ((*removing)->left == nullptr)
        flag++;

    if (flag == 2) {
        auto removingPar { this->find_parrent(value) };
        if ((*removingPar)->right != nullptr && (*removingPar)->right->value == value) {
            delete *removing;
            (*removingPar)->right = nullptr;
            return true;
        } else if ((*removingPar)->left != nullptr && (*removingPar)->left->value == value) {
            delete *removing;
            (*removingPar)->left = nullptr;
            return true;
        }
    } else if (flag == 1) {
        if (*removing == this->get_root()) {
            if ((*removing)->right != nullptr) {
                (*removing)->value = (*removing)->right->value;
                auto tempR { (*removing)->right->right };
                auto tempL { (*removing)->right->left };
                delete (*removing)->right;
                (*removing)->right = tempR;
                (*removing)->left = tempL;
                return true;
            } else if ((*removing)->left != nullptr) {
                (*removing)->value = (*removing)->left->value;
                auto tempR { (*removing)->left->right };
                auto tempL { (*removing)->left->left };
                delete (*removing)->left;
                (*removing)->right = tempR;
                (*removing)->left = tempL;
                return true;
            }
        } else {
            auto removingPar { this->find_parrent(value) };
            if ((*removingPar)->right != nullptr && (*removingPar)->right->value == value) {
                if ((*removing)->right != nullptr) {
                    auto temp { (*removing)->right };
                    delete *removing;
                    (*removingPar)->right = temp;
                    return true;
                }
            } else if ((*removingPar)->left != nullptr && (*removingPar)->left->value == value) {
                if ((*removing)->left != nullptr) {
                    auto temp { (*removing)->left };
                    delete *removing;
                    (*removingPar)->left = temp;
                    return true;
                }
            }
        }
    } else if (flag == 0) {
        auto removingSP { this->find_parrent((*removingSuc)->value) };
        (*removing)->value = (*removingSuc)->value;
        delete *removingSuc;
        if ((*removingSP)->right != nullptr && (*removingSP)->right->value == (*removingSuc)->value) {
            (*removingSP)->right = nullptr;
            return true;
        } else if ((*removingSP)->left != nullptr && (*removingSP)->left->value == (*removingSuc)->value) {
            (*removingSP)->left = nullptr;
            return true;
        }
    }
    return false;
}

BST::BST(std::initializer_list<int> nodes)
    : root { nullptr }
{
    for (int i : nodes) {
        this->add_node(i);
    }
}

BST::BST(const BST& bst)
    : root { nullptr }
{
    std::vector<int> values;
    bst.bfs([&](BST::Node*& node) { values.push_back(node->value); });
    for (auto i = (values.begin()); i != values.end(); ++i)
        this->add_node(*i);
    values.clear();
}

BST::BST(BST&& bst)
{
    root = bst.get_root();
    bst.root = nullptr;
}

BST& BST::operator=(const BST& bst)
{
    if (this == &bst)
        return *this;
    delete this->root;
    std::vector<int> values;
    bst.bfs([&values](BST::Node*& node) { values.push_back(node->value); });
    for (auto i = (values.begin()); i != values.end(); ++i)
        this->add_node(*i);
    return *this;
}

BST& BST::operator=(BST&& bst)
{
    delete root;
    root = bst.root;
    bst.root = nullptr;
    return *this;
}

BST::~BST()
{
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes)
        delete node;
}

const BST& BST::operator++() const
{
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes)
        node->value++;
    return *this;
}

const BST BST::operator++(int) const
{
    BST B { *this };
    ++(*this);
    return B;
}

std::ostream& operator<<(std::ostream& os, const BST& B)
{
    std::vector<BST::Node*> nodes;
    B.bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    size_t count { B.length() };
    os << std::string(30, '*') << std::endl;
    for (auto i = nodes.begin(); i != nodes.end(); ++i)
        os << **i << std::endl;
    os << std::string(30, '*') << std::endl;
    os << "Binary Search tree size: " << count << std::endl;
    return os;
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

std::partial_ordering BST::Node::operator<=>(int V) const
{
    return this->value <=> V;
}

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