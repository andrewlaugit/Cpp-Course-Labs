#include <galaxy-explorer/AsteroidList.hpp>

//default constructor for AsteroidListItem
AsteroidListItem::AsteroidListItem() {
	Asteroid* id = new Asteroid;
	this->next = nullptr;
	this->data = id;
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
	AsteroidListItem* srcPtr = src.head.getNext();
	AsteroidListItem* currentItemPtr = &head;

	while(srcPtr != nullptr){ //check if srcPtr is item
		AsteroidListItem* newItemPtr = new AsteroidListItem( *(srcPtr->getData()) );
		currentItemPtr->setNext(newItemPtr);
		srcPtr = srcPtr->getNext();
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
	AsteriodListItem* newHeadPtr = new AsteroidListItem(e);
	newHeadPtr->setNext(head.getNext());
	head.setNext(newHeadPtr);
}

Asteroid& AsteroidList::front() {
	if(head.getNext() == nullptr)
		return nullptr;
	else
		return *(head.getNext().getData());
}

const Asteroid& AsteroidList::front() const {
	if(head.getNext() == nullptr)
		return nullptr;
	else
		return const *(head.getNext().getData());
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
	AsteriodListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
		count++;
	}
	return count;
}

AsteroidListItem* AsteroidList::beforeBegin() {
	return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return const &head;
}

AsteroidListItem* AsteroidList::begin() {
	return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
	return const head.getNext();
}

//returns the position of the last asteroid
AsteroidListItem* AsteroidList::beforeEnd() {
	AsteriodListItem* tempNextPtr = head.getNext();
	AsteriodListItem* tempPtr = &head;
	while (tempNextPtr != nullptr){
		tempPtr = tempNextPtr;
		tempNextPtr = tempNextPtr->getNext();
	}
	return tempPtr;
}

//returns the position of the last asteroid
const AsteroidListItem* AsteroidList::beforeEnd() const {
	AsteriodListItem* tempNextPtr = head.getNext();
	AsteriodListItem* tempPtr = &head;
	while (tempNextPtr != nullptr){
		tempPtr = tempNextPtr;
		tempNextPtr = tempNextPtr->getNext();
	}
	return const tempPtr;
}

//returns the position after last asteroid
AsteroidListItem* AsteroidList::end() {
	AsteriodListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
	}
	return tempPtr;
}

//returns the position of the last asteroid
const AsteroidListItem* AsteroidList::end() const {
	AsteriodListItem* tempPtr = head.getNext();
	while (tempPtr != nullptr){
		tempPtr = tempPtr->getNext();
	}
	return const tempPtr;
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
	AsteroidListItem* nextItemPtr = others.head.getNext();
	AsteroidListItem* lastPtr = prev;

	while(newItemPtr != nullptr){
		AsteroidListItem* newItemPtr = new AsteroidListItem( *(nextItem->getData()) );
		lastPtr.setNext(newItemPtr);
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
	AsteroidListItem* srcPtr = src.head.getNext();
	AsteroidListItem* currentItemPtr = &head;
	while(srcPtr != nullptr){ //check if srcPtr is item
		AsteroidListItem* newItemPtr = new AsteroidListItem( *(srcPtr->getData()) );
		currentItemPtr->setNext(newItemPtr);
		srcPtr = srcPtr->getNext();
	}

	//return list
	return *this;
}
