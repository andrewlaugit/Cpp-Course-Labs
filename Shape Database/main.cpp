// Andrew Lau
// Lab 3 - Database for shapes
// version 1.1
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
bool goodLastInput(stringstream& lstream);
bool inputIsDone(stringstream& lstream);
bool validName(string name);
int findNameLocation(string name);
bool validType(string type);
bool validNum(int numInput, int numType);
void createShape(stringstream& lstream);
void moveShape(stringstream& lstream);
void rotateShape(stringstream& lstream);
void drawShape(stringstream& lstream);
void deleteShape(stringstream& lstream);

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
        if(lineStream.eof() && command == "") {
            printInvalidCommand();
        }

        if(command == "maxShapes"){
            lineStream >> max_shapes;
            if(lineStream.fail())
                printInvalidArgument();
            else if (validNum(max_shapes,1))
                shapesArray = createDatabase(max_shapes);
        } else if (command == "create"){
            createShape(lineStream);
        } else if (command == "move"){                
            moveShape(lineStream);
        } else if (command == "rotate"){
            rotateShape(lineStream);
        } else if (command == "draw"){
            drawShape(lineStream);
        } else if (command == "delete"){
            deleteShape(lineStream);
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

void createShape(stringstream& lstream){ //string n, string t, int xLoc, int yLoc, int xSize, int ySize){
    string n,t;
    int shapeParams[4];

    //attempt to extract shape name
    lstream >> n;
    if(goodInput(lstream)){
        if(!validName(n)){
            printInvalidName();
            return;
        }
        if(findNameLocation(n) >= 0){
            printDuplicate(n);
            return;
        }
    } else {
        return;
    }

    //attempt to extract shape type
    lstream >> t;
    if(goodInput(lstream)){
        if(!validType(t)){
            printInvalidType();
            return;
        }
    } else {
        return;
    }

    //attempt to extract xLoc,yLoc,xSize,ySize
    for(int i=0;i<3;i++){
        lstream >> shapeParams[i];
        if(goodInput(lstream)){
            if(!validNum(shapeParams[i],1)){
                printInvalidValue();
                return;
            }
            if(i==2){ //for last input of the set, eof flag must not be true already
                if(!goodForLastInput(lstream))
                    return;
                else
                    lstream >> shapeParams[3];
            }
        } else {
            return;
        }
    }

    if(!goodLastInput(lstream))
        return;
    if(!validNum(shapeParams[3],1)){
        printInvalidValue();
        return;
    }

    if(!inputIsDone(lstream))
        return;
    if(shapeCount >= max_shapes){
        printArrayFull();
    } else {
        shapesArray[shapeCount] = new shape(n,t,shapeParams[0],shapeParams[1],shapeParams[2],shapeParams[3]);
        cout << "Created ";
        shapesArray[shapeCount]->draw();
        shapeCount=shapeCount+1;
    }
}

void moveShape(stringstream& lstream){
    int index;
    int loc[2];
    string n;

     //attempt to extract shape name
    lstream >> n;
    if(goodInput(lstream)){
        if(!validName(n)){
            printInvalidName();
            return;
        }
        index = findNameLocation(n);
        if(index == -1){
            printNotFound(n);
        }
    } else {
        return;
    }

    //attempt to extract xLoc
    lstream >> loc[0];
    if(goodInput(lstream)){            
        if(!validNum(loc[0],1)){
            printInvalidValue();
            return;
        }
        if(!goodForLastInput(lstream))
            return;
    } else {
        return;
    }
    
    lstream >> loc[1];
    //check ySize inputs for validity
    if(!goodLastInput(lstream))
        return;
    if(!validNum(loc[1],1)){
        printInvalidValue();
        return;
    }

    //checks if input stream has reached eof
    if(!inputIsDone(lstream))
        return;

    //mutate the location of the shape
    shapesArray[index]->setXlocation(loc[0]);
    shapesArray[index]->setYlocation(loc[1]);
    cout << "Moved " << n << " to " << shapesArray[index]->getXlocation() << " " << shapesArray[index]->getYlocation() << endl;
}

void rotateShape(stringstream& lstream){
    int index,r;
    string n;

     //attempt to extract shape name
    lstream >> n;
    if(goodInput(lstream)){
        if(!validName(n)){
            printInvalidName();
            return;
        }
        index = findNameLocation(n);
        if(index == -1){
            printNotFound(n);
        }
    } else {
        return;
    }

    //ensure eof flag has not already been set
    if(!goodForLastInput(lstream))
        return;

    //attempt to extract rotate angle
    lstream >> r;
    if(goodLastInput(lstream)){
        if(!validNum(r,0)){
            printInvalidValue();
            return;
        }
    } else {
        return;
    } 

    //ensure input stream is empty / reached eof
    if(!inputIsDone(lstream))
        return;

    //rotate shape
    shapesArray[index]->setRotate(r);
    cout << "Rotated " << n << " by " << r << " degrees" << endl;
}

void drawShape(stringstream& lstream){
    int index;
    string n;

    //attempt to extract shape name
    if (!goodForLastInput(lstream))
        return;
    lstream >> n;
    if(goodLastInput(lstream) && inputIsDone(lstream)){
        if(n=="all"){
            cout << "Drew all shapes" << endl;
            for (int i=0;i<shapeCount;i++){
                if(shapesArray[i]!=NULL){
                    shapesArray[i]->draw();
                }
            }
            return;
        }
        if(!validName(n)){
            printInvalidName();
            return;
        }
        index = findNameLocation(n);
        if(index == -1){
            printNotFound(n);
        } else {
            cout << "Drew " << n << endl;
            shapesArray[index]->draw();
        }
        if(!inputIsDone(lstream))
            return;
    }
}

void deleteShape(stringstream& lstream){
    int index;
    string n;

    //attempt to extract shape name
    if (!goodForLastInput(lstream))
        return;
    lstream >> n;
    if(goodLastInput(lstream)){
        if(n =="all"){
            cout << "Deleted: all shapes" << endl;
            for (int i=0;i<shapeCount;i++){
                if(shapesArray[i]!=NULL){
                    delete shapesArray[i];
                    shapesArray[i]=NULL;
                }
            }
            shapeCount=0;
        } else {
            index = findNameLocation(n);
            if(index == -1){
                printNotFound(n);
            } else {
                cout << "Deleted shape " << n << endl;
                delete shapesArray[index];
                shapesArray[index] = NULL;
            }
        }
        if(!inputIsDone(lstream))
            return;
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
bool goodForLastInput(stringstream& lstream){
    while(lstream.peek() == ' ')
        lstream.ignore(1,' ');
    if(lstream.eof()){
        printTooFewArguments();
        return false;
    }
    return true;
}
bool goodLastInput(stringstream& lstream){;
    if (lstream.fail()){
        printInvalidArgument();
        return false;
    }
    return true;
}
bool inputIsDone(stringstream& lstream){
    while(lstream.peek() == ' ' || lstream.peek() == '\n')
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