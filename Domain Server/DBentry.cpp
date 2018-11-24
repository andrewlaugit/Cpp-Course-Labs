// Andrew Lau
// November 23, 2018
// Version 1.0

//implements DBentry.h functions
#include "DBentry.h"

//include C++ libraries
#include <string>
#include <iostream>
using namespace std;

//default constructor
DBentry::DBentry(){
    name = "";
    IPaddress = 0;
    active = false;
}

//constructor
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name){
    name = _name;
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}
    
// sets whether or not this entry is active.
void DBentry::setActive (bool _active){
    active = _active;
}

// returns the name.
string DBentry::getName() const {
    return name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const {
    return IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const {
    return active;
}

// prints the entry in the format 
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs){
    if(rhs.active){
        return out << rhs.name << " : " << rhs.IPaddress << " : active " << endl;
    } else { //rhs.active == false
        return out << rhs.name << " : " << rhs.IPaddress << " : inactive " << endl;
    }
}