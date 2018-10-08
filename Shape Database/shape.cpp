//
//  shape.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#include "shape.h"

// ECE244 Student: 
// Write the implementation (and only the implementation) of the shape
// class below

shape::shape(string n, string t, int x_loc, int y_loc, int x_sz, int y_sz){
    name = n;
    type = t;
    x_location = x_loc;
    y_location = y_loc;
    x_size = x_sz;
    y_size = y_sz;
}

string shape::getType(){
    return type;
}
string shape::getName(){
    return name;
}
int shape::getXlocation(){
    return x_location;
}
int shape::getYlocation(){
    return y_location;
}
int shape::getXsize(){
    return x_size;
}
int shape::getYsize(){
    return y_size;
}
void shape::setType(string t){
    type = t;
}
void shape::setName(string n){
    name = n;
}
void shape::setXlocation(int x_loc){
    x_location = x_loc;
}
void shape::setYlocation(int y_loc){
    y_location = y_loc;
}
void shape::setXSize(int x_sz){
    x_size = x_sz;
}
void shape::setYSize(int y_sz){
    y_size = y_sz;
}
void shape::setRotate(int angle){
    rotation = angle;
}   
void shape::draw(){
    cout << name << ": " << type + " " << x_location << " " << y_location << " " << x_size << " " << y_size << endl; 
}