// Andrew Lau
// TreeNode.cpp
// November 23, 2018
// Version 1.0

#include "TreeNode.h"

// A useful constructor
TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left =  nullptr;
    right =  nullptr;
}

// the destructor
TreeNode::~TreeNode(){
    if(entryPtr != nullptr){
        delete entryPtr;
    }
    if(left != nullptr){
        delete left;
    }
    if(right != nullptr){
        delete right;
    }
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return right;
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const {
    return entryPtr;
}