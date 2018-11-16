#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;


/* GameAI default constructor
 * initializes the game ai data structures
*/
GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	customState().debug_on = true;
}


/* GameAI destructor
 * deletes dynamically allocated data
*/
GameAI::~GameAI() {
	delete my_game_ai;
}


/* MyAIData findClosest
 * determines the asteroid which is closest to the ship
 * - returns the pointer to list item of closest rock
*/
AsteroidListItem* MyAIData::findClosest(AsteroidListItem* firstItem){
    int dx = 0;
    int dy = 0;
    int dxy = 0;
    int smallest=20000;
    AsteroidListItem* currentItem = firstItem;
    AsteroidListItem* closestItem = nullptr;
    
    while(currentItem != nullptr){
        dx = (currentItem->getData().getCurrentHitbox().left+ currentItem->getData().getCurrentHitbox().width/2) - 10000;
        dy = (17999) - (currentItem->getData().getCurrentHitbox().top + currentItem->getData().getCurrentHitbox().height/2);
        dxy = sqrt( pow(dx,2) + pow(dy,2));
        if(dxy < smallest){
            smallest = dxy;
            closestItem = currentItem;
        }
        currentItem = currentItem->getNext();
    }
    return closestItem;
}


/* MyAIData removeDestroyedFromArray
 * clears rock data in array from rocks that are no longer on the screen
*/
void MyAIData::removeDestroyedFromArray(AsteroidListItem* firstItem){
    AsteroidListItem* currentItem = firstItem;

    //reset all 'found' indicators
    for(int i=0;i<10;i++){
        rocksInRange[i][2] = 0;
    }

    //check if item in array still exists on screen
    while(currentItem != nullptr){
        for(int i=0;i<10;i++){
            if(currentItem->getData().getID() == rocksInRange[i][0]){
                rocksInRange[i][2] = 1;
                //rocksInRange[i][3] = findAngle(currentItem);
            }
        }
        currentItem = currentItem->getNext();
    }

    //if not 'found', reset all values to 0
    for(int i=0;i<10;i++){
        if(rocksInRange[i][2] == 0){
            for(int j=0;j<5;j++){
                rocksInRange[i][j] = 0;
            }
        }
    }
}


/* MyAIData findWillHit
 * determines all rocks which will hit the ship
 * - stores the first ten rocks (which will hit) in an array
 * - determines the number of rocks which will hit the ship
 * - returns the pointer to closest rock which will hit ship
*/
AsteroidListItem* MyAIData::findWillHit(AsteroidListItem* firstItem){
    int dx, dy, dxy;
    int smallest = 20000;
    int boxL, boxH;
    bool outOfBoard = false;

    AsteroidListItem* currentItem = firstItem;
    AsteroidListItem* nearestHitItem = nullptr;
    
    //reset all values
    numWillHit = 0;
    removeDestroyedFromArray(firstItem);

    //check all items appearing on the screen
    while(currentItem != nullptr){

        //determine distance in x,y,hypotenuse
        dx = currentItem->getData().getCurrentHitbox().left;
        dy = currentItem->getData().getCurrentHitbox().top;
        dxy = sqrt( pow(dx,2) + pow(dy,2));
        boxL = 1.3* currentItem->getData().getCurrentHitbox().width;
        boxH = 1.3* currentItem->getData().getCurrentHitbox().height;
        
        //repeat frame by frame until rock 'hits' ship or exits board dimensions
        outOfBoard =false;
        while(!outOfBoard){
            dx = dx + currentItem->getData().getVelocity().x;
            dy = dy + currentItem->getData().getVelocity().y;
            
            //conditions for when the rock will hit ship
            if(dx <= 11000+boxL && dx >= 9000-boxL && dy <= 20000 && dy >= 18000-boxH ){
                numWillHit++;

                //
                if(numWillHit <= 10){
                    for(int i=0;i<10;i++){
                        if(rocksInRange[i][0] == currentItem->getData().getID()) //already exists
                            break;
                        if(rocksInRange[i][0] == 0){ //save key information in empty array position
                            rocksInRange[i][0] = currentItem->getData().getID();
                            rocksInRange[i][3] = findAngle(currentItem);
                            rocksInRange[i][4] = currentItem->getData().getMass();
                            break;
                        }
                    }
                }

                //determine if smallest, save if so
                //else move onto next rock in screen
                if (dxy < smallest){
                    smallest = dxy; 
                    nearestHitItem = currentItem;
                } else {
                    currentItem = currentItem->getNext();
                }
                outOfBoard= true;
            }
            
            //rock will exit screen without hitting ship
            if(dx >= 20000 || dx <= 0 || dy >= 20000 || dy <= 0){
                currentItem = currentItem->getNext();
                outOfBoard = true;
            }
        }
    }

    return nearestHitItem;
}


/* MyAIData findAngle
 * determines the angle the ship must shoot at to hit fireItem
 * returns angle in millidegrees
*/
int MyAIData::findAngle(AsteroidListItem* fireItem){
    int dx = 0;
    int dy = 0;
    int dRock = 0;
    int numFrames = 0;
    int angleRight = 0;
    
    //determine distance in x,y, and hypotenuse
    dx = (fireItem->getData().getCurrentHitbox().left+ fireItem->getData().getCurrentHitbox().width/2) - 10000;
    dy = 20000 - (fireItem->getData().getCurrentHitbox().top + fireItem->getData().getCurrentHitbox().height/2);
    dRock = sqrt( pow(dx,2) + pow(dy,2));

    //calculate approx number of frames needed to hit target
    numFrames = dRock / 100;
    
    //adjustment factor for rocks far away
    if (dRock > 5000) {
        numFrames = 2* numFrames/3;
    }
    
    //determine the position of the rock when it should be hit
    dx = dx + fireItem->getData().getVelocity().x * numFrames;
    dy = dy - fireItem->getData().getVelocity().y * numFrames;

    //calculates angle needed to hit rock        
    if(dx != 0) {
        angleRight = atan((double)dx / dy) * 57 * 1000; //converts rad into millidegrees
    } else if (angleRight > 40000 || angleRight < -40000) {
        angleRight = 2 * angleRight; //adjustment factor for large angles
    } else {
        angleRight = 0;
    }

    return angleRight;
}


/* GameAI suggestAction
 * determines the action the ship should take (rotate, fire)
 * - uses play data to determine move to make
*/
SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
        bool usingSaved = false;
        bool aim = false;
        int angleLeft = 0;
        int leastNumShots = 1000;
        int numShotsPerRock = 0;
        int buffer = 1500;

        AsteroidListItem* currentItem = asteroidsObserver().asteroids().begin();
        AsteroidListItem* closestItem = nullptr;
        AsteroidListItem* willHitItem = nullptr;
        AsteroidListItem* fireItem = nullptr;
        
        //find closest item that will hit ship and the closest item to the ship
        willHitItem = my_game_ai->findWillHit(currentItem);
        closestItem = my_game_ai->findClosest(currentItem);

        //clears the debug window
	    debug_rt->clear(sf::Color::Transparent);
        
        //when there exists 3 or more rocks that are bound to hit ship, use data from array
        if(my_game_ai->numWillHit > 2){
            usingSaved = true;
        } else {
            //priority of items to fire at as follows
            // 1. shoot at item that will hit ship, if not existent,
            // 2. shoot at item that is closest to ship
            if (willHitItem != nullptr){
                fireItem = willHitItem;
                aim=true;
            } else if (closestItem != nullptr){
                fireItem = closestItem;
                aim=true;
            }             
        }

        //when using the data from array to determine move
        if(usingSaved){

            //allows each rock to be shot at 3 times before moving onto next
            numShotsPerRock = 3; 
            if(my_game_ai->rockSize == 300) {
               // if(my_game_ai->numSmallRocks > 3){
              //      numShotsPerRock = 2;
              //  }
                if(my_game_ai->numShots == numShotsPerRock){
                    my_game_ai->numShots = 0;
                    buffer = 1000;
                }
            } else {
               // cout << my_game_ai->rockSize << endl;
                if(my_game_ai->numShots == numShotsPerRock){
                    my_game_ai->numShots = 0;
                }
            }

            //determines the index within array storing rocks that will hit ship
            //finds the rock which has been shot at the least
            my_game_ai->numSmallRocks = 0; 
            if(my_game_ai->numShots == 0){                
                for(int i=0;i<10;i++){
                    if(my_game_ai->rocksInRange[i][4] == 300)
                        my_game_ai->numSmallRocks++;
                   // cout << my_game_ai->rocksInRange[i][0] << ":" << my_game_ai->rocksInRange[i][1]<<":" << my_game_ai->rocksInRange[i][3]<<":" << my_game_ai->rocksInRange[i][4]<< "..." <<endl; 
                    if(my_game_ai->rocksInRange[i][0] != 0  
                            && my_game_ai->rocksInRange[i][0] != my_game_ai->lastId 
                            && my_game_ai->rocksInRange[i][1] < leastNumShots){
                        
                        my_game_ai->prevIndex = i;
                        leastNumShots = my_game_ai->rocksInRange[i][1];
                    }
                }
              //  cout << "fire at " <<  my_game_ai->rocksInRange[my_game_ai->prevIndex][0] << endl;
            }
            
            //update the angleRight (used in current round) and rockSize (used in next round)
            my_game_ai->angleRight = my_game_ai->rocksInRange[my_game_ai->prevIndex][3];
            my_game_ai->rockSize = my_game_ai->rocksInRange[my_game_ai->prevIndex][4];
            
            //increments 'times shot at' when ship actually fires a rock towards the intended target
            if(ship_state.frames_until_phaser_is_ready == 1 
                    && ship_state.millidegree_rotation >= my_game_ai->angleRight-1500 
                    && ship_state.millidegree_rotation <= my_game_ai->angleRight+1500){
                my_game_ai->numShots++;
                my_game_ai->lastId = my_game_ai->rocksInRange[my_game_ai->prevIndex][0];
                my_game_ai->rocksInRange[my_game_ai->prevIndex][1]++;
            }
            
        //when array not being used (less than 3 rocks going towards ship)
        } else if (aim) {
            my_game_ai->angleRight = my_game_ai->findAngle(fireItem);
            my_game_ai->rockSize = fireItem->getData().getMass();
        }

        //determine shooting angle range (alowing for juttering)
        if(aim || usingSaved){
            angleLeft = my_game_ai->angleRight - buffer;
            my_game_ai->angleRight = my_game_ai->angleRight + buffer;
        } else {
            angleLeft = -45000;
            my_game_ai->angleRight = 45000;
        }

        // allows for spraying pattern to go around targeted angle range
        if (ship_state.millidegree_rotation <= angleLeft) {
            my_game_ai->ccw=false;
        } else if (ship_state.millidegree_rotation >= my_game_ai->angleRight) {
            my_game_ai->ccw=true;
        }
       
        if(my_game_ai->ccw) {
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        } else {
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        }
}