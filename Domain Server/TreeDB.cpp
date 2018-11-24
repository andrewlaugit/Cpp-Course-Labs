// Andrew Lau
// November 24, 2018
// Version 1.0

//implementation file for TreeDB.h functions
#include "TreeDB.h"
#include <iostream>

//***************** all functions implemented in order as listed in header file ***************************

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root = nullptr;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    if(root != nullptr){
        delete root; //will invoke TreeNode destructor
    }
}

/* finds the number of active entries in db
 * used as a helper funciton to countActive function
 * recursively implemented by adding up active entries in parent, leftchild and right child
 */ 
int TreeDB::findNumActive(TreeNode* root) const {
    if(root == nullptr){ //base case when nullptr reached
        return 0;
    } else if(root->getEntry()->getActive()){
        return 1 + findNumActive(root->getLeft()) + findNumActive(root->getRight());
    } else {
        return 0 + findNumActive(root->getLeft()) + findNumActive(root->getRight());
    }
} 

/* inserts the entry pointed to by newEntry into the database. 
 * If an entry with the same key as newEntry's exists 
 * in the database, it returns false. Otherwise, it returns true.
 */
bool TreeDB::insert(DBentry* newEntry){
    TreeNode* currentNode = root;
    TreeNode* newEntryNode = new TreeNode(newEntry);

    if(root == nullptr){
        root = newEntryNode;
        return true;
    }
    
    while(currentNode != nullptr){
        if(newEntry->getName() == currentNode->getEntry()->getName()){ //already in tree
            delete newEntryNode; //prevent memory leaks
            return false;
        } else { //not yet found
            if(newEntry->getName() < currentNode->getEntry()->getName()){ //item less than tree item
                if(currentNode->getLeft() == nullptr){ //no more children to check
                    currentNode->setLeft(newEntryNode);
                    return true;
                } else {
                    currentNode = currentNode->getLeft(); //check left children
                }               
            } else if(newEntry->getName() > currentNode->getEntry()->getName()){ //item greater than tree item
                if(currentNode->getRight() == nullptr){ //no more children to check
                    currentNode->setRight(newEntryNode);
                    return true;
                } else {
                    currentNode = currentNode->getRight(); //check right children
                } 
            }
        } 
    }
}

/* searches the database for an entry with a key equal to name.
 * If the entry is found, a pointer to it is returned.
 * If the entry is not found, the NULL pointer is returned.
 * Also sets probesCount
 */
DBentry* TreeDB::find(string name){
    TreeNode* currentNode = root;
    
    probesCount = 0; //reset probeCount

    while(currentNode != nullptr){
        probesCount++;
        if(name == currentNode->getEntry()->getName()){ //found in tree
            return currentNode->getEntry();
        } else {
            // not yet found >> must traverse tree either left or right to find item
            // left if name comes before currentNode's name
            // right if name comes after currentNode's name
            if(name < currentNode->getEntry()->getName()){
                currentNode = currentNode->getLeft();          
            } else if(name > currentNode->getEntry()->getName()){
                currentNode = currentNode->getRight();
            }
        } 
    }

    return nullptr; //not found
}

/* deletes the entry with the specified name (key)  from the database.
 * If the entry was indeed in the database, it returns true.
 * Returns false otherwise.
 * See section 6 of the lab handout for the *required* removal method.
 * If you do not use that removal method (replace deleted node by
 * maximum node in the left subtree when the deleted node has two children)
 * you will not match exercise's output.
 */
bool TreeDB::remove(string name){
    TreeNode* deleteNode = root;
    TreeNode* parentNode = deleteNode;
    TreeNode* replacementNode;
    TreeNode* replacementParentNode;
    bool found = false;
     
    while(deleteNode != nullptr){
        if(name == deleteNode->getEntry()->getName()){ //found in tree
            found = true;
            break;
        } else {
            // not yet found >> must traverse tree either left or right to find item
            // left if name comes before currentNode's name
            // right if name comes after currentNode's name
            parentNode = deleteNode;
            if(name < deleteNode->getEntry()->getName()){
                deleteNode = deleteNode->getLeft();          
            } else if(name > deleteNode->getEntry()->getName()){
                deleteNode = deleteNode->getRight();
            }
        } 
    }

    if(!found){ //not found and done with remove
        return false;
    }
 
    // lab specifies to replace deleted node with greatest key on left subtree
    // after finding replacement node, temporarily remove node from tree and
    // preserve tree structure
    if(deleteNode->getLeft() != nullptr) {
        replacementNode = deleteNode->getLeft();
        replacementParentNode = replacementNode;

        while(replacementNode != nullptr){
            if(replacementNode->getRight() == nullptr) {
                if(replacementParentNode != replacementNode){
                    replacementParentNode->setRight(replacementNode->getLeft());
                }
                break;
            } else {
                replacementParentNode = replacementNode;
                replacementNode = replacementNode->getRight();
            }
        }

    } else { //left subtree of delete node is empty, use smallest key on right subtree
        replacementNode = deleteNode->getRight();
        replacementParentNode = replacementNode;

        while(replacementNode != nullptr){
            if(replacementNode->getLeft() == nullptr) {
                if(replacementParentNode != replacementNode){
                    replacementParentNode->setLeft(replacementNode->getRight());
                }
                break;
            } else {
                replacementParentNode = replacementNode;
                replacementNode = replacementNode->getLeft();
            }
        }
    }

    //***** if replacementNode is nullptr after checking left and right *******
    //***** the delete node has no children, and thus can simply be deleted *******
    
    if(parentNode == deleteNode){ //when deleting the root
        root = replacementNode;
    } else if(parentNode->getLeft() == deleteNode){ //deleting left child of parent
        parentNode->setLeft(replacementNode);
    } else { //parentNode->getRight() == deleteNode) >> deleting right child of parent
        parentNode->setRight(replacementNode);
    }

    //reconnect deleteNode's children with tree
    replacementNode->setLeft(deleteNode->getLeft());
    replacementNode->setRight(deleteNode->getRight());
    delete deleteNode;
    return true;
}
	
// deletes all the entries in the database.
// delete the whole tree
void TreeDB::clear(){
    if(root != nullptr){
        delete root;
    }
}
    
// prints the number of probes stored in probesCount
void TreeDB::printProbes() const {
    cout << probesCount;
}
   
/* computes and prints out the total number of active entries
 * in the database (i.e. entries with active==true)
 * calls helper function to recursively count active entries
 */
void TreeDB::countActive () const {
    cout << findNumActive(root);
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs) {
    return out << rhs.root;
}

/* recursively adds entries to the output stream, starting from 
 * leftmost to rightmost entries
 * helper function to operator<<TreeDB
 */
ostream& operator<< (ostream& out, TreeNode* rhs){
    if(rhs == nullptr){
        return out;
    } else {
        return out << rhs->getLeft() << rhs->getEntry() << rhs->getRight(); 
    }
}
