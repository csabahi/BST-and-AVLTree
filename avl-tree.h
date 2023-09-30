#ifndef LAB3_AVL_TREE_H
#define LAB3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree : public BinarySearchTree {
public:
    Node** rootAdress = BinarySearchTree::getRootNodeAddress();
//    Node* avlroot_ = (Node*)getRootNodeAddress();
    unsigned int avlsize_;

    // Overriden insert and remove functions
    // Do not modify these definitions

    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need
    bool balance(DataType val);
    bool leftRotation( Node* alpha, Node* parent );
    bool rightRotation( Node* alpha, Node* parent );
    int nodeDepth(Node* n);
};

#endif  // LAB3_AVL_TREE_H
