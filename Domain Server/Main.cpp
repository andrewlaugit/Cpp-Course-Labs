// Andrew Lau
// Main.cpp
// November 24, 2018
// Version 1.0

#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//forward declarations

//
void insertEntry(stringstream& lstream, TreeDB* serverPtr);
void findEntry(stringstream& lstream, TreeDB* serverPtr);
void removeEntry(stringstream& lstream, TreeDB* serverPtr);
void printAllEntries(TreeDB* serverPtr);
void printProbe(stringstream& lstream, TreeDB* serverPtr);
void removeAllEntries(TreeDB* serverPtr);
void countActiveEntries(TreeDB* serverPtr);
void updateStatus(stringstream& lstream, TreeDB* serverPtr);
bool statusFromStream(stringstream& lstream);
//status messages
void printSuccess();
void printEntryDNE();
void printEntryExists();

int main(){
    string line;
    string command;
    TreeDB server;
    TreeDB* serverPtr = &server;

    cout << "> ";
    getline(cin, line);

    while(!cin.eof()){
        stringstream linestream(line);
        linestream >> command;
        if(!linestream.fail()){
            if(command == "insert"){
                insertEntry(linestream, serverPtr);
            } else if (command == "find"){
                findEntry(linestream, serverPtr);
            } else if (command == "remove"){
                removeEntry(linestream, serverPtr);
            } else if (command == "printall"){
                printAllEntries(serverPtr);
            } else if (command == "printprobes"){
                printProbe(linestream, serverPtr);
            } else if (command == "removeall"){
                removeAllEntries(serverPtr);
            } else if (command == "countactive"){
                countActiveEntries(serverPtr);
            } else if (command == "updatestatus"){
                updateStatus(linestream, serverPtr);    
            }
        }
    }
    return 0;
}

void insertEntry(stringstream& lstream, TreeDB* serverPtr){
    DBentry* entryPtr;
    string name;
	unsigned int IPaddress;
    bool active;
    bool inserted;

    lstream >> name;
    lstream >> IPaddress;
    active = statusFromStream(lstream);

    entryPtr = new DBentry(name,IPaddress,active);
    inserted = serverPtr->insert(entryPtr);
    
    if(inserted){
        printSuccess();
    } else { //not inserted
        printEntryExists();
    }
}

void findEntry(stringstream& lstream, TreeDB* serverPtr){
    DBentry* entryPtr;
    string name;

    lstream >> name;
    entryPtr = serverPtr->find(name);

    if(entryPtr != nullptr){
        cout << entryPtr;
    } else {
        printEntryDNE();
    }
}

void removeEntry(stringstream& lstream, TreeDB* serverPtr){
    string name;

    lstream >> name;
    
    if(serverPtr->remove(name)){
        printSuccess();
    } else {
        printEntryDNE();
    }
}

void printAllEntries(TreeDB* serverPtr){
    cout << *serverPtr;
}

void printProbe(stringstream& lstream, TreeDB* serverPtr){
    DBentry* entryPtr;
    string name;

    lstream >> name;
    entryPtr = serverPtr->find(name);

    if(entryPtr == nullptr){
        printEntryDNE();
    } else {
        serverPtr->printProbes();
    }
}

void removeAllEntries(TreeDB* serverPtr){
    serverPtr->clear();
    printSuccess();
}

void countActiveEntries(TreeDB* serverPtr){
    serverPtr->countActive();
}

void updateStatus(stringstream& lstream, TreeDB* serverPtr){
    DBentry* entryPtr;
    bool active;
    string name;

    lstream >> name;
    
    entryPtr = serverPtr->find(name);
    if(entryPtr = nullptr){
        printEntryDNE();
    } else {
        active = statusFromStream(lstream);
        entryPtr->setActive(active);
        printSuccess();
    }
}

bool statusFromStream(stringstream& lstream){
    string statusString;
    lstream >> statusString;
    if(statusString == "active"){
        return true;
    } else if(statusString == "inactive"){
        return false;
    }
}

void printSuccess(){
    cout << "Success" << endl;
}

void printEntryDNE(){
    cout << "Error: entry does not exist" << endl;
}

void printEntryExists(){
    cout << "Error: entry already exists" << endl;
}