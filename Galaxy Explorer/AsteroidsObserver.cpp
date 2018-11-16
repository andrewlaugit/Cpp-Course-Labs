/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

/* AsteroidsObserver onAsteroidInRange
 * adds an asteroid item to the end of the asteroid list
*/
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.insertAfter(asteroid_list.beforeEnd(),asteroid);
}

/* AsteroidsObserver onAsteroidUpdate
 * update the asteroid item in the asteroid list
*/
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    AsteroidListItem* temp;
    temp = asteroid_list.beforeBegin(); //= new AsteroidListItem(asteroid); 
    
    while (temp->getNext() != nullptr && temp->getNext()->getData().getID() != asteroid.getID()){
        temp = temp->getNext();
    }
    asteroid_list.eraseAfter(temp);
    asteroid_list.insertAfter(temp, asteroid);

}

/* AsteroidsObserver onAsteroidOutOfRange
 * removes the asteroid item from the asteroid list
*/
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    
    AsteroidListItem* temp;
    temp = asteroid_list.beforeBegin(); //= new AsteroidListItem(asteroid); 
    
    while (temp->getNext() != nullptr && temp->getNext()->getData().getID() != asteroid.getID()){
        temp = temp->getNext();
    }
    asteroid_list.eraseAfter(temp);
     
}

/* AsteroidsObserver onAsteroidDestroy
 * removes the asteroid item from the asteroid list
*/
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem* temp;
    temp = asteroid_list.beforeBegin(); //= new AsteroidListItem(asteroid); 
    
    while (temp->getNext() != nullptr && temp->getNext()->getData().getID() != asteroid.getID()){
        temp = temp->getNext();
    }
    asteroid_list.eraseAfter(temp);
}
