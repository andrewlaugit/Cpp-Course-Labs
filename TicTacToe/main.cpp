//
//  main.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>

#include <tic-tac-toe/playMove.h>

using namespace std;
using namespace sf;


int main() {

    /************************************************************************************************************/
    /* The following variables define the state of the game                                                     */
    /************************************************************************************************************/

    // You should complete the following declarations
    // Make sure to initalize the variables

    // The game board array
    int gameBoard[3][3] = {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty};

    // An boolean that represents the turn in the game
    bool turn=true; //true = X , false = O

    // A boolean to represent if the move is valid
    bool validMove=false; //true if valid, false if invalid
    
    // A boolean to represent if the game is over
    bool is_game_over = false;

    // An integer that represents the win code
    int winCode=0;
    
    //2 integers that represent the row and column input
    int row, col;


    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* The loading of the X image is shown. Repeat for the rest of the images                                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("X.jpg")) {
        return EXIT_FAILURE;
    }

    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("O.jpg")) {
        return EXIT_FAILURE;
    }
    
    // Get the blank image
    sf::Texture blank_texture;
    if (!blank_texture.loadFromFile("blank.jpg")) {
        return EXIT_FAILURE;
    }
    
    //creates an array of sprites for each square on board
    sf::Sprite spriteArray[3][3];

    /************************************************************************************************************/
    /* Insert code that creates the window and displays it                                                      */
    /************************************************************************************************************/

    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Black) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them

    // The tile size is the size of the images
    const int tileSize = X_texture.getSize().x;

    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 cell sizes plus 2 barWidth's
    const int barWidth = tileSize/20;
    const int barHeight = boardSize*tileSize + (boardSize-1)*barWidth;

    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize*tileSize + (boardSize-1)*barWidth;

    // Create the main window: it has a title bar and a close button, but is not resizable
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "ECE244 Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);
    
    // Set the Icon that appears in the task bar when the window is minimized
    // Insert you code here, see the lab handout
    sf::Image windowIcon;
    if (!windowIcon.loadFromFile("icon.jpg")){
        return EXIT_FAILURE;
    }
    window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
    
    /************************************************************************************************************/
    /* This sets up the settings/positions for border lines and sprites                                                              */
    /************************************************************************************************************/    
    
    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (berHeight and barWidth)
    // Insert your code here
    sf::RectangleShape gridBarsArray[4];
    
    for(int i=0;i<4;i++){
        gridBarsArray[i].setSize(sf::Vector2f(barWidth,barHeight));
        gridBarsArray[i].setFillColor(sf::Color::Black);
        if(i%2==0){
            //index 0 and 2 are horizontal grid bars
            gridBarsArray[i].setPosition(sf::Vector2f(0,tileSize*(i/2+1)+barWidth*(i/2+1)));
            gridBarsArray[i].setRotation(270);
        } else {
            //index 1 and 3 are vertical grid bars
            gridBarsArray[i].setPosition(sf::Vector2f(tileSize*(i/2+1)+barWidth*(i/2),0));
        }
    }
    
    //Set position and texture to blank sprite as default
    for(int i=0; i<3;i++){
        for(int j=0; j<3;j++){
            spriteArray[i][j].setTexture(blank_texture);
            spriteArray[i][j].setPosition(sf::Vector2f((tileSize*j)+barWidth*j,(tileSize*i)+barWidth*i));
        }   
    }  
    
    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/

    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        // The event
        sf::Event event;

        // Process the events
        while (window.pollEvent(event)) {

            // This is the handling of the close window event
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Left mouse button pressed: get the click position and play the move
            // is_game_over is a variable you should define above
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // left mouse button is pressed: get the coordinates in pixels
                // Insert your code to get the coordinates here
                sf::Vector2i clickPosition = Mouse::getPosition(window);

                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // Insert your code below
                row = clickPosition.y/tileSize;
                col = clickPosition.x/tileSize;


                // Play the move by calling the playMove function
                // Insert your code below
                playMove(gameBoard,row,col,turn,validMove,is_game_over,winCode);
            }
        }

        // Insert code to draw the tiles using the sprites created earlier
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white

        // Insert your code here
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                switch (gameBoard[i][j]){
                    case 0:
                        spriteArray[i][j].setTexture(blank_texture);
                        break;
                    case X:
                        spriteArray[i][j].setTexture(X_texture);
                        break;
                    case O:
                        spriteArray[i][j].setTexture(O_texture);
                        break;
                }
                window.draw(spriteArray[i][j]);
            }
        }
        for(int i=0;i<4;i++){
            window.draw(gridBarsArray[i]);
        }
        
        //create rectangle for line showing win
        if(winCode!=0){
            sf::RectangleShape winLine(sf::Vector2f(windowSize,10));
            winLine.setFillColor(sf::Color::White);
            switch (winCode){
                case 1:
                    winLine.setPosition(sf::Vector2f(0, tileSize/2));
                    break;
                case 2:
                    winLine.setPosition(sf::Vector2f(0, tileSize*3/2+barWidth));
                    break;
                case 3:
                    winLine.setPosition(sf::Vector2f(0, tileSize*5/2+barWidth*2));
                    break;
                case 4:
                    winLine.setPosition(sf::Vector2f(tileSize/2, 0));
                    winLine.setRotation(90);
                    break;
                case 5:
                    winLine.setPosition(sf::Vector2f(tileSize*3/2+barWidth, 0));
                    winLine.setRotation(90);
                    break;
                case 6:
                    winLine.setPosition(sf::Vector2f(tileSize*5/2+barWidth*2, 0));
                    winLine.setRotation(90);
                    break;
                case 7:
                    winLine.setSize(sf::Vector2f(2*windowSize, 10));
                    winLine.setPosition(sf::Vector2f(0,0));
                    winLine.setRotation(45);
                    break;
                case 8:
                    winLine.setSize(sf::Vector2f(2*windowSize, 10));
                    winLine.setPosition(sf::Vector2f(tileSize*3+2*barWidth,0));
                    winLine.setRotation(135);
                    break;
            }
            window.draw(winLine);
        }
        
        // Display to the window
        window.display();
    }

    return EXIT_SUCCESS;
}
