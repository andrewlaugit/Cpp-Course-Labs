#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;

GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	customState().debug_on = true;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

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
void MyAIData::removeDestroyedFromArray(AsteroidListItem* firstItem){
    AsteroidListItem* currentItem = firstItem;
    for(int i=0;i<10;i++){
        rocksInRange[i][2] = 0;
    }
    while(currentItem != nullptr){
        for(int i=0;i<10;i++){
            if(currentItem->getData().getID() == rocksInRange[i][0]){
                rocksInRange[i][2] = 1;
               // rocksInRange[i][3] = findAngle(currentItem);
            }
        }
        currentItem = currentItem->getNext();
    }
    for(int i=0;i<10;i++){
        if(rocksInRange[i][2] == 0){
            for(int j=0;j<5;j++){
                rocksInRange[i][j] = 0;
            }
        }
    }
}


AsteroidListItem* MyAIData::findWillHit(AsteroidListItem* firstItem){
    int dx = 0;
    int dy = 0;
    int dxy = 0;
    int smallest = 20000;
    int boxL = 0;
    int boxH = 0;
    bool outOfBoard = false;
    AsteroidListItem* currentItem = firstItem;
    AsteroidListItem* nearestHitItem = nullptr;
    
    
    numWillHit = 0;
    removeDestroyedFromArray(firstItem);

    while(currentItem != nullptr){
        dx = currentItem->getData().getCurrentHitbox().left;
        dy = currentItem->getData().getCurrentHitbox().top;
        dxy = sqrt( pow(dx,2) + pow(dy,2));
        boxL = 1.3* currentItem->getData().getCurrentHitbox().width;
        boxH = 1.3* currentItem->getData().getCurrentHitbox().height;
        
        outOfBoard =false;
        while(!outOfBoard){
            dx = dx + currentItem->getData().getVelocity().x;
            dy = dy + currentItem->getData().getVelocity().y;
            
            
            if(dx <= 11000+boxL && dx >= 9000-boxL && dy <= 20000 && dy >= 18000-boxH ){
                numWillHit++;
                if(numWillHit <= 10){
                    for(int i=0;i<10;i++){
                        if(rocksInRange[i][0] == currentItem->getData().getID())
                            break;
                        if(rocksInRange[i][0] == 0){
                            rocksInRange[i][0] = currentItem->getData().getID();
                            rocksInRange[i][3] = findAngle(currentItem);
                            rocksInRange[i][4] = currentItem->getData().getMass();
                            break;
                        }
                    }
                }
                if (dxy < smallest){
                    smallest = dxy; 
                    nearestHitItem = currentItem;
                } else {
                    currentItem = currentItem->getNext();
                }
                outOfBoard= true;
            }
            if(dx >= 20000 || dx <= 0 || dy >= 20000 || dy <= 0){
                currentItem = currentItem->getNext();
                outOfBoard = true;
            }
        }
    }
    return nearestHitItem;
}
int MyAIData::findAngle(AsteroidListItem* fireItem){
    int dx = 0;
    int dy = 0;
    int dRock = 0;
    int numFrames = 0;
    int angleRight = 0;
    
    dx = (fireItem->getData().getCurrentHitbox().left+ fireItem->getData().getCurrentHitbox().width/2) - 10000;
    dy = 20000 - (fireItem->getData().getCurrentHitbox().top + fireItem->getData().getCurrentHitbox().height/2);
    dRock = sqrt( pow(dx,2) + pow(dy,2));

    numFrames = dRock / 100;
    
    if (dRock > 5000) {
        numFrames = 2* numFrames/3;
    }
    
    dx = dx + fireItem->getData().getVelocity().x * numFrames;
    dy = dy - fireItem->getData().getVelocity().y * numFrames;
            
    if(dx != 0) {
        angleRight = atan((double)dx / dy) * 57 * 1000; //converts rad into millidegrees
    } else if (angleRight > 40000 || angleRight < -40000) {
        angleRight = 2 * angleRight;
    } else {
        angleRight = 0;
    }

    return angleRight;
}


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
        
        willHitItem = my_game_ai->findWillHit(currentItem);
        closestItem = my_game_ai->findClosest(currentItem);

	debug_rt->clear(sf::Color::Transparent);
        
        if(my_game_ai->numWillHit > 2){
            usingSaved = true;
        } else {
            if (willHitItem != nullptr){
                fireItem = willHitItem;
                aim=true;
            } else if (closestItem != nullptr){
                fireItem = closestItem;
                aim=true;
            } else if (currentItem != nullptr){
                fireItem = currentItem;
                aim=true;
            }
            
        }

        if(usingSaved){
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

        //draws debugging boxes
        if (customState().debug_on) {
		if ( currentItem != nullptr ) {
			const sf::IntRect first_ast_hb = currentItem->getData().getCurrentHitbox();
			sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
			ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
			ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect.setOutlineColor(sf::Color::Yellow);
			ast_rect.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect);
                }
                if ( willHitItem != nullptr ) {        
                        const sf::IntRect hit_ast_hb = willHitItem->getData().getCurrentHitbox();
			sf::RectangleShape ast_rect1(sf::Vector2f(hit_ast_hb.width, hit_ast_hb.height));
			ast_rect1.setPosition(hit_ast_hb.left, hit_ast_hb.top);
			ast_rect1.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect1.setOutlineColor(sf::Color::Red);
			ast_rect1.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect1);
                }
                if ( closestItem != nullptr ) {        
                        const sf::IntRect close_ast_hb = closestItem->getData().getCurrentHitbox();
			sf::RectangleShape ast_rect2(sf::Vector2f(close_ast_hb.width, close_ast_hb.height));
			ast_rect2.setPosition(close_ast_hb.left, close_ast_hb.top);
			ast_rect2.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect2.setOutlineColor(sf::Color::Blue);
			ast_rect2.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect2);
		}
                if ( fireItem != nullptr ) {        
                        const sf::IntRect fire_ast_hb = fireItem->getData().getCurrentHitbox();
			sf::RectangleShape ast_rect3(sf::Vector2f(fire_ast_hb.width, fire_ast_hb.height));
			ast_rect3.setPosition(fire_ast_hb.left, fire_ast_hb.top);
			ast_rect3.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect3.setOutlineColor(sf::Color::Green);
			ast_rect3.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect3);
		}
	}  

        //determine shooting angle range
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