/** Andrew Lau
 *  Nov 09, 2018
 *  Lab 4 - Galaxy Explorer Asteroid List
 *  Last Updated - Nov 05, 2018 
 **/

#include <galaxy-explorer/AsteroidList.hpp>

//******************* Asteroid List Item functions ************************

// AsteroidListItem - default constructor
// set next and data pointers to null
AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

// AsteroidListItem - copy constructor
// point data to dynamic copy of asteroid a
AsteroidListItem::AsteroidListItem(Asteroid a) {
	Asteroid* id = new Asteroid(a);
	this->next = nullptr;
	this->data = id;
}

// AsteroidListItem - destructor
// delete dynamically allocated asteroid and set pointers to null
AsteroidListItem::~AsteroidListItem() {
	delete this->data;
	this->data = nullptr;
	this->next = nullptr;
	//pointers will be automatically deallocated
}

//********************* Asteroid List functions **************************

// AsteroidList - default constructor
AsteroidList::AsteroidList() {
	// head <AsteroidListItem> will already have default constructor
}

// Asteroid List - copy constructor
AsteroidList::AsteroidList(const AsteroidList& src) {

	//start from list items after head in source
	const AsteroidListItem* srcPtr = src.head.getNext();
	AsteroidListItem* currentItemPtr = &head;

        //************ repeat until end of src reached **********
        //create dynamic copy of list item and allocate pointers
        //traverse to next list item
	while(srcPtr != nullptr){ //check if srcPtr is item
            AsteroidListItem* newItemPtr = new AsteroidListItem(srcPtr->getData());
            currentItemPtr->setNext(newItemPtr);
            srcPtr = srcPtr->getNext();
            currentItemPtr = currentItemPtr->getNext();
	}
}

// Asteroid List - destructor
AsteroidList::~AsteroidList() {
    
        //start from first item after head
	AsteroidListItem* currentPtr = head.getNext();
	AsteroidListItem* delPtr;
        
        //*********** repeat until end of list reached **********
        //deallocate current item and traverse to next item in list
	while(currentPtr != nullptr){ //check if currentPtr is item
		delPtr = currentPtr;
		currentPtr = currentPtr->getNext(); 
		delete delPtr;
	}
        
        //remove pointer to deallocated memory, set first item = null
	head.setNext(nullptr);
}

/* Asteroid List - pushFront
 * inserts item as first in list
*/
void AsteroidList::pushFront(Asteroid e) {
	AsteroidListItem* newHeadPtr = new AsteroidListItem(e);
	newHeadPtr->setNext(head.getNext()); //add pointer to old first node
	head.setNext(newHeadPtr);
}

/* Asteroid List - front
 * returns first asteroid in list, if list empty returns nullptr
*/
Asteroid& AsteroidList::front() {
	if(head.getNext() == nullptr)
            return head.getData();
	else
            return head.getNext()->getData();
}

/* Asteroid List - front <const>
 * returns first asteroid in list, if list empty returns nullptr
*/
const Asteroid& AsteroidList::front() const {
	if(head.getNext() == nullptr)
            return head.getData();
	else
            return head.getNext()->getData();
}

/* Asteroid List - isEmpty
 * returns true if list is empty, false is list has 1+ items
*/
bool AsteroidList::isEmpty() const {
	if (head.getNext() == nullptr)
		return true;
	else
		return false;
}

/* Asteroid List - size
 * returns the number of items in the list (excluding head)
*/
int AsteroidList::size() const {
	int count = 0;
        
        //start from first item
	const  AsteroidListItem* tempPtr = head.getNext();
        
        //traverse list until end, increment count each time
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
		count++;
	}
        
	return count;
}

/* Asteroid List - beforeBegin
 * returns pointer to head, which is always item before first item
*/
AsteroidListItem* AsteroidList::beforeBegin() {
	return &head;
}

/* Asteroid List - beforeBegin <const>
 * returns pointer to head, which is always item before first item
*/
const AsteroidListItem* AsteroidList::beforeBegin() const {
	return &head;
}

/* Asteroid List - begin
 * returns pointer to first item
*/
AsteroidListItem* AsteroidList::begin() {
	return head.getNext();
}

/* Asteroid List - begin <const>
 * returns pointer to first item
*/
const AsteroidListItem* AsteroidList::begin() const {
	return head.getNext();
}

/* Asteroid List - beforeEnd
 * returns pointer to last item in list
*/
AsteroidListItem* AsteroidList::beforeEnd() {
    
        //start from first item
        //tempPtr will always to point to item before tempNextPtr
	AsteroidListItem* tempNextPtr = head.getNext();
	AsteroidListItem* tempPtr = &head;
        
        //repeat until end of list reached
	while (tempNextPtr != nullptr){
		tempPtr = tempNextPtr;
		tempNextPtr = tempNextPtr->getNext();
	}
        
	return tempPtr;
}

/* Asteroid List - beforeEnd <const>
 * returns pointer to last item in list
*/
const AsteroidListItem* AsteroidList::beforeEnd() const {
    
        //start from first item
        //tempPtr will always to point to item before tempNextPtr
	const AsteroidListItem* tempNextPtr = head.getNext();
	const AsteroidListItem* tempPtr = &head;
        
         //repeat until end of list reached
	while (tempNextPtr != nullptr){
		tempPtr = tempNextPtr;
		tempNextPtr = tempNextPtr->getNext();
	}
        
	return tempPtr;
}

/* Asteroid List - end
 * returns next pointer from last item in list, should always be nullptr
*/
AsteroidListItem* AsteroidList::end() {
	AsteroidListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
	}
	return tempPtr;
}

/* Asteroid List - end <const>
 * returns next pointer from last item in list, should always be nullptr
*/
const AsteroidListItem* AsteroidList::end() const {
	const AsteroidListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
	}
	return tempPtr;
}

/* Asteroid List - insertAfter (single item)
 * adds single asteroid to list after prev item, returns pointer to item inserted
*/
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    
        //dynamically create new item
	AsteroidListItem* tempPtr = new AsteroidListItem(e);
        
        //add item to list and add list of items after prev
	tempPtr->setNext(prev->getNext());
	prev->setNext(tempPtr);
        
	return tempPtr;
}

/* Asteroid List - insertAfter (list of items)
 * inserts copies of items in other and adds to list after prev item
 * returns last item inserted
*/
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    
        //start from first item in others list
	const AsteroidListItem* copyItemPtr = others.head.getNext();
        AsteroidListItem* temp = prev->getNext();
	AsteroidListItem* lastPtr = prev;

        //repeat until end of 'others' list reached
	while(copyItemPtr != nullptr){
                //create copy of item and add to list, then traverse to next item
		AsteroidListItem* newItemPtr = new AsteroidListItem(copyItemPtr->getData());
		lastPtr->setNext(newItemPtr);
		copyItemPtr = copyItemPtr->getNext();
		lastPtr = lastPtr->getNext();
	}
        
        //connect items after prev back to into list
        lastPtr->setNext(temp);
        
	return lastPtr;
}

/* Asteroid List - eraseAfter
 * deletes the asteroid after prev, returns address of item erased
*/
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
	AsteroidListItem* tempPtr = prev->getNext();
        
        //check if item exists after prev
	if (tempPtr != nullptr) {
		prev->setNext(tempPtr->getNext());
		delete tempPtr;
	}
        
	return tempPtr;
}

/* Asteroid List - clear
 * deletes all items in list, resets head's next to nullptr
*/
void AsteroidList::clear() {
    
        //starts from start of list
	AsteroidListItem* tempPtr = head.getNext();
	AsteroidListItem* delItemPtr;
        
        //repeat till end of list
	while (tempPtr != nullptr) {
		delItemPtr = tempPtr;
		tempPtr = tempPtr->getNext();
		delete delItemPtr;
	}
        
        //remove pointer to previous first item
	head.setNext(nullptr);
}

/* Asteroid List - operator=
 * replaces current list with src list
*/
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
	//first check to ensure not same list
	if(&src == this) {
		return *this;
	}

	//delete all existing items in current list
	AsteroidListItem* currentPtr = head.getNext();
	AsteroidListItem* delPtr;
        
	while(currentPtr != nullptr){
		delPtr = currentPtr;
		currentPtr = currentPtr->getNext(); 
		delete delPtr;
	}
	head.setNext(nullptr);

	//start from item after head
        //add copies of items in src to list
	const AsteroidListItem* srcPtr = src.head.getNext();
	AsteroidListItem* currentItemPtr = &head;
        
	while(srcPtr != nullptr){ //check if srcPtr is item
		AsteroidListItem* newItemPtr = new AsteroidListItem(srcPtr->getData());
		currentItemPtr->setNext(newItemPtr);
		srcPtr = srcPtr->getNext();
                currentItemPtr = currentItemPtr->getNext();
	}

	//return list
	return *this;
}
