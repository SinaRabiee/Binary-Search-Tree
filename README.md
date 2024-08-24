# Binary-Search-Tree

## Outline

A *binary tree* is a tree graph in which nodes can only have upto 2 children. A *Binary Search Tree* is a binary tree in which the right child of each node have a greater value than the left one.

We are going to implement 2 classes one of them is called `Node` which represents each node in the graph, and the other one is `BST` which is responsible to conncet nodes in a  way to construct a binary search tree. Since the `Node` class is a direct property of the `BST` class; It should be defined inside the BST class.


# BST Class
This class is responsible to construct a BST graph by connceting the nodes in a proper manner. `root` is the only member variable of this class which points to the first node of the binary search tree.

- **get_root**
returnts the private member variable `root`.

- **bfs**
*Breadth-first search (BFS)* is an algorithm for searching a tree by iterating through each and every node; Implement this algorithm! </br> This function has a input of `std::function`, this type behaves like a pointer to function and can wrapp any callable objects in c++ like ordinary or lambda functions. you are going to use lambda functions in this homework so feel free to search and learn about them. </br> The user should be able to use this argument and apply any functions on the nodes of the tree i.e. call the object `func` on every node found by BFS algorithm.

- **length**
returnts the number of nodes exist in bst.

- **add_node**
adds a new node to BST in the proper place. **note.** the user should not be able to add a value that already exists in the tree.

- **find_node**
finds the node in tree with the specified value and returns a pointer to the pointer of the node. </br> **note.** do not use bfs algorithm to find the nod, instead use the property of binary search trees: *that is why we use them in the first place*.

- **find_parrent**
finds the parrent node of a node with specified value and returns a pointer to the pointer of that parrent. </br> **note.** do not use bfs algorithm to find the node.

- **find_successor**
finds a successor of a node with specified value.

- **delete_node**
deletes a node with the specified value. if there is no such node with that value return false.
