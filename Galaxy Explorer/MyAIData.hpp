/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 * Supervised by: Tarek Abdelrahman
 */

#ifndef ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#define ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP


/**
 * Student editable struct for storing their ai state
 * Yes, you may change this header.
 * Maybe you want to remember the last asteroid Id you shot at?
 */


struct MyAIData {
    bool debug_on = true;
    bool ccw = true;
    int numWillHit = 0;
    int angleRight = 0;
    int numShots = 0;
    int prevIndex = 0;
    int lastId = 0;
    int rockSize = 0;
    int numSmallRocks= 0;

    //holds up to 10 different rock ids
    //holds id, number of shots fired at, still exists, angle right, size/mass
    int rocksInRange[10][5];
    
    AsteroidListItem* findClosest(AsteroidListItem* firstItem);
    void removeDestroyedFromArray(AsteroidListItem* firstItem);
    AsteroidListItem* findWillHit(AsteroidListItem* firstItem);
    int findAngle(AsteroidListItem* fireItem);
};

#endif /* ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP */
