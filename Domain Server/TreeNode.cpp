// Andrew Lau
// TreeNode.cpp
// November 23, 2018
// Version 1.0

#include "TreeNode.h"

/* constructor for TreeNode
 * sets left and right children to nullptr
 * sets data pointer to paramter _entryPtr
 */
TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left =  nullptr;
    right =  nullptr;
}

/* destructor for TreeNode
 * implements a recursive destructor
 * attempts to deallocate all memory in current node's data
 * then attempts to deallocate all memory in left and right children
 */
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

// sets the left child of the TreeNode to newLeft
void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

// sets the right child of the TreeNode to newRight
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