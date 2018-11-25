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

//******************** forward declarations ******************************
//command functions
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

/* main function
 * repetitively prompts for input until eof inputted <CTRL+D>
 * reads the command from the input and calls the appropriate function
 */
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
        
        cout << "> ";
        getline(cin, line);
    }

    return 0;
}

/* insertEntry function
 * reads the name, IP adress, and status of the entry
 * adds the entry to the database tree and prints success message
 * if entry already exists, print error message
 */
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

/* findEntry function
 * reads the name of the entry and attempts to find it
 * if entry is found, its details are printed
 * if not found, error message printed
 */
void findEntry(stringstream& lstream, TreeDB* serverPtr){
    DBentry* entryPtr;
    string name;

    lstream >> name;
    entryPtr = serverPtr->find(name);

    if(entryPtr != nullptr){
        cout << *entryPtr;
    } else {
        printEntryDNE();
    }
}

/* removeEntry function
 * reads the name of the entry and attempts to remove it
 * if entry is found, it is deleted and success printed
 * if not found, error message is printed
 */
void removeEntry(stringstream& lstream, TreeDB* serverPtr){
    string name;

    lstream >> name;
    
    if(serverPtr->remove(name)){
        printSuccess();
    } else {
        printEntryDNE();
    }
}

/* printAllEntries function
 * prints all the entries in the database tree in alpha order
 */
void printAllEntries(TreeDB* serverPtr){
    cout << *serverPtr;
}

/* printProbe function
 * reads the name of the entry and attempts to find it
 * if found, number of nodes visited to reach entry is printed
 * if not found, error message printed
 */
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

/* removeAllEntries function
 * clears the database tree of all entries, prints success once done
 */
void removeAllEntries(TreeDB* serverPtr){
    serverPtr->clear();
    printSuccess();
}

/* countActiveEntries function
 * prints out the total number of active entries in the database tree
 */
void countActiveEntries(TreeDB* serverPtr){
    serverPtr->countActive();
}

/* updateStatus function
 * reads the name from the input and attempts to find it,
 * if found, the status of the entry is updated as inputted
 * if not found, error message printed
 */
void updateStatus(stringstream& lstream, TreeDB* serverPtr){
    DBentry* entryPtr;
    bool active;
    string name;

    lstream >> name;
    
    entryPtr = serverPtr->find(name);
    if(entryPtr == nullptr){
        printEntryDNE();
    } else {
        active = statusFromStream(lstream);
        entryPtr->setActive(active);
        printSuccess();
    }
}

/* statusFromStream function
 * takes in a stringstream and reads status
 * if active inputted, returns true
 * if inactive inputted, returns false
 */
bool statusFromStream(stringstream& lstream){
    string statusString;
    lstream >> statusString;
    if(statusString == "active"){
        return true;
    } else if(statusString == "inactive"){
        return false;
    }
}

//prints success message
void printSuccess(){
    cout << "Success" << endl;
}

//prints entry does not exist error message
void printEntryDNE(){
    cout << "Error: entry does not exist" << endl;
}

//prints entry already exists error message
void printEntryExists(){
    cout << "Error: entry already exists" << endl;
}