#include "binary-search-tree.h"
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == nullptr){
        return 0;
    }

    else if ( n->right == nullptr && n->left == nullptr ){
        return 0;
    }

    else {
        return ( 1 + std::max(getNodeDepth(n->left ), getNodeDepth( n->right ) ) );
    }
}

BinarySearchTree::BinarySearchTree() {
    size_ = 0;
    root_ = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    if(root_ == nullptr) {
        std::cout<<"Empty tree" << std::endl;
        return;
    }

    std::queue <Node*> q;
    q.push(root_);
    while(!q.empty()){
        Node *point = q.front();
        if ( point ->left != nullptr ) q.push(point->left);
        if ( point->right != nullptr ) q.push(point->right);
        q.pop();
        delete point;
    }
    std::cout << std::endl;
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    if (root_ == nullptr){
        return -99999;
    }

    Node* temp = root_;

    while( temp->right != nullptr){
        temp = temp->right;
    }

    return temp->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    if (root_ == nullptr){
        return -99999;
    }

    Node* temp = root_;

    while( temp->left != nullptr){
        temp = temp->left;
    }

    return temp->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}


void BinarySearchTree::print() const {
    // Keep track of the nodes, to print in a
    // breadth first (level order) traversal.
    std::queue<Node*> q;

    // Seed the jobs with the root.
    if (root_ != nullptr)
        q.push(root_);

    // Walk through the tree, adding nodes to the
    // queue level-by-level.
    std::cout << "(";
    while (!q.empty()) {

        // Get the current node from the queue, and remove it.
        Node* cur = q.front();
        q.pop();

        // Print out the nodes value.
        std::cout << cur->val << " ";

        // Check to see if the current node has left or right children,
        // if they exist, add them to the queue.
        if (cur->left != nullptr)
            q.push(cur->left);
        if (cur->right != nullptr)
            q.push(cur->right);
    }
    std::cout << ")" << std::endl;
}

//}
//    if(root_ == nullptr){
//        return;
//    }
//    std:: queue <Node*> Q;
//    Q.push(root_);
//    while (!Q.empty()) {
//        Node *P = Q.front();
//        Q.pop();
//        std::cout << P->val << ", ";
//        if (P->left != nullptr) Q.push(P->left);
//        if (P->right != nullptr) Q.push(P->right);
//    }
//    std::cout<< std::endl;
//}

bool BinarySearchTree::exists(DataType val) const {
    if (size_ == 0) return false;
    Node *temp = root_;
    bool found = false ;
    while( !found && temp != nullptr ){
        if( temp->val == val ) found = true;
        else if( temp->val > val ) temp = temp-> left;
        else if( temp->val < val ) temp = temp->right;
    }

    return found;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return (root_);
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return (&root_);
}

bool BinarySearchTree::insert(DataType val) {

    if(exists(val)) return false;

    Node* newNode = new Node(val);

    if( root_ == nullptr ){
      root_= newNode;
      size_++;
      return true;
    }

    Node* temp = root_;

    while( temp != nullptr ){
        if ( temp->val < val ){
            if ( temp->right == nullptr ){
                temp->right = newNode;
                size_++;
                return true;
            }
            temp = temp->right;

        } else {
            if ( temp->left == nullptr ){
                temp->left = newNode;
                size_++;
                return true;
            }
            temp = temp->left;
        }
    }

    return false;
}

bool BinarySearchTree::remove(DataType val) {

    if (!exists(val)) return false;

    Node* current = root_;
    Node* parent = nullptr;
    bool isRight = false;

    while(current!=nullptr) {
        if(current->val == val) {
            break;
        } else if (val < current->val) {
            parent = current;
            current = current->left;
            isRight = false;
        }
        else {
            parent = current;
            current = current->right;
            isRight = true;
        }
    }

    //removing leaf node
    if (current->left == nullptr && current->right == nullptr) {
        if(current == root_) {
            delete root_;
            root_ = nullptr;
            size_--;
            return true;
        }

        delete current;
        current = nullptr;
        if(isRight) {
            parent->right = nullptr;
        } else {
            parent->left = nullptr;
        }
        size_--;
        return true;
    }

    // removing node with only a left child
    if ( current->left != nullptr && current->right == nullptr){
        if ( current->val == root_->val ) {
            root_ = current->left;
        }
        else if (isRight){
            parent->right = current->left;
        } else {
            parent->left = current->left;
        }
        delete current;
        current = nullptr;
        size_--;
        return true;
    }

    //removing node with only right child
    if ( current->left == nullptr && current->right != nullptr){
        if ( current->val == root_->val ){
            root_ = current->right;
        }
        else if (isRight){
            parent->right = current->right;
        }else{
            parent->left = current->right;
        }
        delete current;
        current = nullptr;
        size_--;
        return true;
    }

    //removing when node has 2 children
    if ( current->left != nullptr && current->right != nullptr){
        Node* predecessor = current->left;
        Node* pred_parent = current;
        isRight = false;

        while ( predecessor->right != nullptr ){
            pred_parent = predecessor;
            predecessor = predecessor->right;
            isRight = true;
        }

        current->val = predecessor->val;


        if (predecessor->left == nullptr && isRight) {
            pred_parent->right = nullptr;
        }
        else if (predecessor->left == nullptr ){
            pred_parent->left = nullptr;
        }
        else if ( predecessor->left != nullptr && isRight ){
            pred_parent->right = predecessor->left;
        }
        else {
            pred_parent->left = predecessor->left;
        }

        delete predecessor;
        predecessor = nullptr;
        size_--;
        return true;
    }
    return true;
}
