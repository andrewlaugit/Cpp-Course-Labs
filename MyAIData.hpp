/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 * Supervised by: Tarek Abdelrahman
 */

#ifndef ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#define ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP

struct MyAIData {
    bool debug_on = false;

    //if ship should move in counterclockwise direction or opposite direction
    bool ccw = true;

    //number of rocks with trajectory to hit ship
    int numWillHit = 0;

    //angle last shot at
    int angleRight = 0;

    //number of shots shot at a particular rock
    int numShots = 0;
    
    //the index within the array of the last rock shot at
    int prevIndex = 0;

    //id of the last rock shot at
    int lastId = 0;

    //size of the rock being fired at
    int rockSize = 0;

    /* holds up to 10 different rocks 
    * values stored:
    * ID - unique id of the rock to ensure no duplicates
    * Shots taken at - keeps track of number of shots the rock has been shot at
    * Still on board? - 1 if still in play, 0 if not on board anymore
    * angle right - the angle needed to hit rock
    * size/mass - the value of the mass of the rock 
    */
    int rocksInRange[10][5];
    
    //helper functions described in GameAI.cpp
    AsteroidListItem* findClosest(AsteroidListItem* firstItem);
    void removeDestroyedFromArray(AsteroidListItem* firstItem);
    AsteroidListItem* findWillHit(AsteroidListItem* firstItem);
    int findAngle(AsteroidListItem* fireItem);
};

#endif /* ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP */
