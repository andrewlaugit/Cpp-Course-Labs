#include <galaxy-explorer/AsteroidList.hpp>

//default constructor for AsteroidListItem
AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

//copy constructor for AsteroidListItem
AsteroidListItem::AsteroidListItem(Asteroid a) {
	Asteroid* id = new Asteroid(a);
	this->next = nullptr;
	this->data = id;
}

//destructor for AsteroidListItem
AsteroidListItem::~AsteroidListItem() {
	delete this->data;
	this->data = nullptr;
	this->next = nullptr;
	//pointers will be automatically deallocated
}

//default constructor for AsteroidList
AsteroidList::AsteroidList() {
	// head <AsteroidListItem> will already have default constructor
}

//copy constructor for AsteroidList
AsteroidList::AsteroidList(const AsteroidList& src) {

	//start from item after head
	const AsteroidListItem* srcPtr = src.head.getNext();
	AsteroidListItem* currentItemPtr = &head;

	while(srcPtr != nullptr){ //check if srcPtr is item
            AsteroidListItem* newItemPtr = new AsteroidListItem(srcPtr->getData());
            currentItemPtr->setNext(newItemPtr);
            srcPtr = srcPtr->getNext();
            currentItemPtr = currentItemPtr->getNext();
	}
}

//destructor for AsteroidList
AsteroidList::~AsteroidList() {
	AsteroidListItem* currentPtr = head.getNext();
	AsteroidListItem* delPtr;
	while(currentPtr != nullptr){
		delPtr = currentPtr;
		currentPtr = currentPtr->getNext(); 
		delete delPtr;
	}
	head.setNext(nullptr);
}

//inserts Asteroid e at beginning of list
void AsteroidList::pushFront(Asteroid e) {
	AsteroidListItem* newHeadPtr = new AsteroidListItem(e);
	newHeadPtr->setNext(head.getNext());
	head.setNext(newHeadPtr);
}

Asteroid& AsteroidList::front() {
	if(head.getNext() == nullptr)
            return head.getData();
	else
            return head.getNext()->getData();
}

const Asteroid& AsteroidList::front() const {
	if(head.getNext() == nullptr)
            return head.getData();
	else
            return head.getNext()->getData();
}

//returns true if list contains only the head
bool AsteroidList::isEmpty() const {
	if (head.getNext() == nullptr)
		return true;
	else
		return false;
}

//returns the number of items in the list excluding the head
int AsteroidList::size() const {
	int count = 0;
	const  AsteroidListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
		count=count+1;
	}
	return count;
}

AsteroidListItem* AsteroidList::beforeBegin() {
	return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return &head;
}

AsteroidListItem* AsteroidList::begin() {
	return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
	return head.getNext();
}

//returns the position of the last asteroid
AsteroidListItem* AsteroidList::beforeEnd() {
	AsteroidListItem* tempNextPtr = head.getNext();
	AsteroidListItem* tempPtr = &head;
	while (tempNextPtr != nullptr){
		tempPtr = tempNextPtr;
		tempNextPtr = tempNextPtr->getNext();
	}
	return tempPtr;
}

//returns the position of the last asteroid
const AsteroidListItem* AsteroidList::beforeEnd() const {
	const AsteroidListItem* tempNextPtr = head.getNext();
	const AsteroidListItem* tempPtr = &head;
	while (tempNextPtr != nullptr){
		tempPtr = tempNextPtr;
		tempNextPtr = tempNextPtr->getNext();
	}
	return tempPtr;
}

//returns the position after last asteroid
AsteroidListItem* AsteroidList::end() {
	AsteroidListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
	}
	return tempPtr;
}

//returns the position of the last asteroid
const AsteroidListItem* AsteroidList::end() const {
	const AsteroidListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
	}
	return tempPtr;
}

//adds single asteroid to this list in position after prev, returns item inserted
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
	AsteroidListItem* tempPtr = new AsteroidListItem(e);
	tempPtr->setNext(prev->getNext());
	prev->setNext(tempPtr);
	return tempPtr;
}

//inserts copies of others after prev, returns last item inserted
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
	const AsteroidListItem* copyItemPtr = others.head.getNext();
	AsteroidListItem* lastPtr = prev;

	while(copyItemPtr != nullptr){
		AsteroidListItem* newItemPtr = new AsteroidListItem(copyItemPtr->getData());
		lastPtr->setNext(newItemPtr);
		newItemPtr = newItemPtr->getNext();
		lastPtr = lastPtr->getNext();
	}
	return lastPtr;
}

//deletes the asteroid after prev, returns item erased
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
	AsteroidListItem* tempPtr = prev->getNext();
	if (tempPtr != nullptr) {
		prev->setNext(tempPtr->getNext());
		delete tempPtr;
	}
	return tempPtr;
}

//empty the list
void AsteroidList::clear() {
	AsteroidListItem* tempPtr = head.getNext();
	AsteroidListItem* delItemPtr;
	while (tempPtr != nullptr) {
		delItemPtr = tempPtr;
		tempPtr = tempPtr->getNext();
		delete delItemPtr;
	}
	head.setNext(nullptr);
}

//makes copy of src
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
	//first check to ensure not same list
	if(&src == this) {
		return *this;
	}

	//delete existing list items
	AsteroidListItem* currentPtr = head.getNext();
	AsteroidListItem* delPtr;
	while(currentPtr != nullptr){
		delPtr = currentPtr;
		currentPtr = currentPtr->getNext(); 
		delete delPtr;
	}
	head.setNext(nullptr);

	//start from item after head
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
