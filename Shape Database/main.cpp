// Andrew Lau
// Lab 3 - Database for shapes
//
//  Skeleton created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

shape** createDatabase(int size);
bool goodInput(stringstream& lstream);
bool goodForLastInput(stringstream & lstream);
bool inputIsDone(stringstream& lstream);
bool validName(string name);
int findNameLocation(string name);
bool validType(string type);
bool validNum(int numInput, int numType);
void createShape(string n, string t, int xLoc, int yLoc, int xSize, int ySize);
void moveShape(string nameInput,int xLocInput,int yLocInput);
void rotateShape(string nameInput,int rotateInput);
void drawShape(string nameInput);
void deleteShape(string nameInput);

//error messages
void printInvalidCommand();
void printInvalidArgument();
void printInvalidName();
void printDuplicate(string nameInput);
void printNotFound(string nameInput);
void printArrayFull();
void printInvalidType();
void printInvalidValue();
void printTooManyArguments();
void printTooFewArguments();



int main() {

    string line;
    string command;

    string nameInput, typeInput;
    int xLocInput, yLocInput, xSizeInput, ySizeInput,rotateInput;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if(command == "maxShapes"){
            lineStream >> max_shapes;
            if(lineStream.fail())
                printInvalidArgument();
            else if (validNum(max_shapes,1)){
                shapesArray = createDatabase(max_shapes);
            }
        } else if (command == "create"){

            lineStream >> nameInput;
            if(goodInput(lineStream)){
                lineStream >> typeInput;
                if(goodInput(lineStream)){
                    lineStream >> xLocInput;
                    if(goodInput(lineStream)){
                        lineStream >> yLocInput; 
                        if(goodInput(lineStream)){
                            lineStream >> xSizeInput;
                            if(goodInput(lineStream) && goodForLastInput(lineStream)){
                                lineStream >> ySizeInput;
                                if(inputIsDone(lineStream)){
                                    createShape(nameInput,typeInput,xLocInput,yLocInput,xSizeInput,ySizeInput);
                                }
                            }
                        }
                    }
                }
            }
        } else if (command == "move"){
            lineStream >> nameInput;
            if(goodInput(lineStream)){
                lineStream >> xLocInput;
                if(goodInput(lineStream) && goodForLastInput(lineStream)){
                    lineStream >> yLocInput;
                        if(inputIsDone(lineStream)){
                            moveShape(nameInput,xLocInput,yLocInput);
                        }
                }
            }
        } else if (command == "rotate"){
            lineStream >> nameInput;
            if(goodInput(lineStream) && goodForLastInput(lineStream)){
                lineStream >> rotateInput;
                if(inputIsDone(lineStream)){
                    rotateShape(nameInput,rotateInput);
                }
            }
        } else if (command == "draw"){
            lineStream >> nameInput;
            if(inputIsDone(lineStream)){
                drawShape(nameInput);
            }
        } else if (command == "delete"){
            lineStream >> nameInput;
            if(inputIsDone(lineStream)){
                deleteShape(nameInput);
            }
        } else {
            printInvalidCommand();
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

//create database dynamically
shape** createDatabase(int size){
    shape** shapeDB = new shape*[size];
    cout << "New database: max shapes is " << size << endl;
    return shapeDB;
}

void createShape(string n, string t, int xLoc, int yLoc, int xSize, int ySize){
    if(!validName(n)){
        printInvalidName();
    } else if(findNameLocation(n) >= 0){
        printDuplicate(n);
    } else if(!validType(t)){
        printInvalidType();
    } else if(!(validNum(xLoc,1) && validNum(yLoc,1) && validNum(xSize,1) && validNum(ySize,1))){
        printInvalidValue();
    } else if(shapeCount >= max_shapes){
        printArrayFull();
    } else {
        shapesArray[shapeCount] = new shape(n,t,xLoc,yLoc,xSize,ySize);
        cout << "Created ";
        shapesArray[shapeCount]->draw();
        shapeCount=shapeCount+1;
    }
}

void moveShape(string nameInput,int xLocInput,int yLocInput){
    int index = findNameLocation(nameInput);

    if(index == -1){
        printNotFound(nameInput);
    } else if(!(validNum(xLocInput,1) && validNum(yLocInput,1))){
        printInvalidValue();
    } else {
        shapesArray[index]->setXlocation(xLocInput);
        shapesArray[index]->setYlocation(yLocInput);
        cout << "Moved " << nameInput << " to " << shapesArray[index]->getXlocation() << " " << shapesArray[index]->getYlocation() << endl;
    }
}

void rotateShape(string nameInput,int rotateInput){
    int index = findNameLocation(nameInput);

    if(index == -1){
        printNotFound(nameInput);
    } else if(!validNum(rotateInput,0)){
        printInvalidValue();
    } else {
        shapesArray[index]->setRotate(rotateInput);
        cout << "Rotated " << nameInput << " by " << rotateInput << " degrees" << endl;
    }
}

void drawShape(string nameInput){
    if(nameInput == "all"){
        cout << "Drew all shapes" << endl;
        for (int i=0;i<shapeCount;i++){
            if(shapesArray[i]!=NULL){
                shapesArray[i]->draw();
            }
        }
    } else {
        int index = findNameLocation(nameInput);
        if(index == -1){
            printNotFound(nameInput);
        } else {
            cout << "Drew " << nameInput << endl;
            shapesArray[index]->draw();
        }
    }
}

void deleteShape(string nameInput){
    if(nameInput == "all"){
        cout << "Deleted: all shapes" << endl;
        for (int i=0;i<shapeCount;i++){
            if(shapesArray[i]!=NULL){
                delete shapesArray[i];
                shapesArray[i]=NULL;
            }
        }
        shapeCount=0;
    } else {
        int index = findNameLocation(nameInput);
        if(index == -1){
            printNotFound(nameInput);
        } else {
            cout << "Deleted shape " << nameInput << endl;
            delete shapesArray[index];
            shapesArray[index] = NULL;
        }
    }
}




//======================================================================================================================
//functions for error prevention and notification
//======================================================================================================================

//recieves string types from main and returns if input is non-empty or reserved for commands
bool goodInput(stringstream& lstream){
    if(lstream.eof()){
        printTooFewArguments();
        return false;
    } else if (lstream.fail()){
        printInvalidArgument();
        return false;
    }
    return true;
}
bool goodForLastInput(stringstream & lstream){
    while(lstream.peek() == ' ')
        lstream.ignore(1,' ');
    if(lstream.eof()){
        printTooFewArguments();
        return false;
    }
    return true;
}
bool inputIsDone(stringstream& lstream){
    if (lstream.fail()){
        printInvalidArgument();
        return false;
    }
    while(lstream.peek() == ' ')
        lstream.ignore(1,' ');
    if(lstream.eof()){
        return true;
    }else{
        printTooManyArguments();
        return false;
    }
}
bool validName(string name){
     for (int i=0; i<NUM_KEYWORDS; i++){
        if(name == keyWordsList[i])
            return false;
    }
    if (validType(name) || name == "")
        return false;
    return true;
}
int findNameLocation(string name){
    for(int i=0;i<shapeCount;i++){
       if(shapesArray[i]->getName() == name){
            return i;
       }
    }
    return -1;
}
bool validType(string type){
    for (int i=0; i<NUM_TYPES; i++){
        if(type == shapeTypesList[i])
            return true;
    }
    return false;
}

//recieves numerical inputs from main and returns if input is of correct type and in range
bool validNum(int numInput, int numType){
    switch(numType){
        case 0: //angle
            if(numInput > 360){
                return false;
                break;
            }
        case 1: //location, size, value
            if(numInput >= 0)
                return true;
            else 
                return false;
            break;
        default:
            return false;
            break;
    }
}

//functions for displaying error messages listed in order of hierarchy
void printInvalidCommand(){
    cout << "Error: invalid command" << endl;
}
void printInvalidArgument(){
    cout << "Error: invalid argument" << endl;
}
void printInvalidName(){
    cout << "Error: invalid shape name" << endl;
}
void printDuplicate(string nameInput){
    cout << "Error: shape " << nameInput << " exists" << endl;
}
void printNotFound(string nameInput){
    cout << "Error: shape " << nameInput << " not found" << endl;
}
void printInvalidType(){
    cout << "Error: invalid shape name" << endl;
}
void printInvalidValue(){
    cout << "Error: invalid value" << endl;
}
void printTooManyArguments(){
    cout << "Error: too many arguments" << endl;
}
void printTooFewArguments(){
    cout << "Error: too few arguments" << endl;
}
void printArrayFull(){
    cout << "Error: shape array is full" << endl;
}