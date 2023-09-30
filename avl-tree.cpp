#include "avl-tree.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

bool AVLTree::insert(DataType val) {

    bool result = BinarySearchTree::insert(val);
    if ( result == false ) return false;
    balance(val);
    return true;
}

bool AVLTree::remove(DataType val) {

    bool result = BinarySearchTree::remove(val);
    if ( result == false ) return false;
    balance(val);
    return true;
}


bool AVLTree::rightRotation(Node *alpha, Node *parent ) {
    Node* A = nullptr;
    if (nodeDepth(alpha->left) > nodeDepth(alpha->right)){
        A = alpha->left;
    } else {
        A = alpha->right;
    }

    alpha->left = A->right;
    A->right = alpha;

    if (parent == nullptr) {
        *rootAdress = A;
    } else if (parent->right == alpha ){
        parent->right = A;
    } else{
        parent->left = A;
    }
    return true;
}

bool AVLTree::leftRotation(Node* alpha, Node* parent ) {
    Node* A = nullptr;

    if (nodeDepth(alpha->left) > nodeDepth(alpha->right)){
        A = alpha->left;
    } else {
        A = alpha->right;
    }

    alpha->right = A->left;
    A->left = alpha;

    if ( parent == nullptr ){
        *rootAdress = A;
    } else if ( parent->left == alpha ){
        parent->left = A;
    } else {
        parent->right=A;
    }
    return true;
}

bool AVLTree::balance( DataType val ) {
    Node * alphaParent = nullptr;
    Node* A = nullptr;
    Node* Akid = nullptr;
    Node* alpha = nullptr;
    Node* current = *rootAdress;
    Node* previous = nullptr;

    //iterate through Tree to find the closest alpha and parent to the unbalanced node
    while ( current != nullptr){

        if ( abs(nodeDepth(current->right) - nodeDepth(current->left)) == 2 ){
            alpha = current;
            alphaParent = previous;
        }
        previous = current;

        if ( current->val > val ){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    if (alpha == nullptr ){
        return true;
    }


    if (nodeDepth(alpha->left) > nodeDepth(alpha->right)){
        A = alpha->left;
    } else {
        A = alpha->right;
    }

    if (nodeDepth(A->left) > nodeDepth(A->right)){
        Akid = A->left;
    } else {
        Akid = A->right;
    }

    //LL Rotation
    if( Akid->val > alpha->val && Akid->val > A->val ) {
        leftRotation( alpha, alphaParent );
    }

    //RR Rotation
    else if( Akid->val < alpha->val && Akid->val < A->val ){
        rightRotation( alpha, alphaParent );
    }

        //LR Rotation
    else if( Akid->val < alpha->val && Akid->val > A->val ) {
        leftRotation( A, alpha );
        rightRotation( alpha, alphaParent );
    }
        //RL Rotation
    else if ( Akid->val > alpha->val && val < A->val ) {
        rightRotation( A, alpha);
        leftRotation( alpha, alphaParent );
    }
    return true;
}

int AVLTree::nodeDepth(Node *n) {
    if (n == nullptr){
        return 0;
    }
    else if ( n->right == nullptr && n->left == nullptr ){
        return 1;
    }
    else {
        return ( 1 + std::max(nodeDepth(n->left ), nodeDepth(n->right ) ) );
    }
}

