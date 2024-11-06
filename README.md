# AVL-Tree
Overview
This repository contains the implementation of an AVL (Adelson-Velsky and Landis) Tree in C++. An AVL tree is a self-balancing binary search tree, ensuring that the tree remains balanced at all times for efficient operations. The goal of this assignment is to deepen understanding of tree data structures, particularly in how they manage balance and handle insertions and deletions.

Key Features
Node Class: Represents individual nodes in the AVL tree. Each node includes its value, height, heights of left and right child branches, pointers to parent and children nodes, and a boolean flag indicating if it's a left child.

AVL Tree Class: Manages the overall AVL tree structure. It includes the root node and functions for adding and deleting nodes, in-order traversal, height update, and rotations.

Core Functions:

add_node(int): Adds a new node with the given value to the tree. In case of a tie in choosing a branch, it favors the branch with the lower height, defaulting to the left if heights are equal.

delete_node(int): Removes a node with the specified value. In case of multiple nodes with the same value, it deletes the first node encountered. The deletion strategy varies based on the node's children.

in_order_traversal(node*): Performs an in-order traversal of the tree, printing node details.

height_update(node*): Updates the heights of nodes after addition or deletion and checks for balance violations. Returns details for any needed rotations.

Rotation Functions:

L_Rotate(node*) and R_Rotate(node*): Perform left and right rotations on the tree to maintain balance after insertions or deletions.
Assignment Constraints

No additional functions are allowed outside of those specified.

No extra members should be added to the node or AVLtree classes.


Usage

cpp

Copy code

int main() {
   
    AVLtree t1;
   
    t1.add_node(45);
  
    t1.add_node(50);
   
    // ... further operations ...
   
    return 0;

}

Testing

Test cases will vary to cover different scenarios of adding and deleting nodes, as well as ensuring the tree remains balanced and correctly structured.
