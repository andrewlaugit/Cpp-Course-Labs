//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

//check if the move is valid by making sure space is not filled
bool checkIfValid(int board[3][3], int row, int col){
    
    //check dimension to prevent out of bounds array
    if(row<0 || row>2){
        return false;
    } else if(col<0 || col>2){
        return false;
    } else if (board[row][col]==0){
        return true;
    } else {
        return false;
    }
}

//implement the move into the board
void makeMove(int board[3][3], int row, int col, bool turn){
    if (turn){
        board[row][col]=X;
    } else {
        board[row][col]=O;
    }
}

//determine if input line are filled by X/O and are same
bool checkIfSame(int box1, int box2, int box3){
    if (box1!=0 && box1==box2 && box2==box3){
        return true;
    } else {
        return false;
    }
}

//run through all rows and columns and print each space
void printBoard(int board[3][3]){
    for (int i=0; i<3; i++){
        for (int j=0;j<3;j++){
            cout << board[i][j] << " ";
        }
    }
}

//determines the predetermined win codes
//if multiple, only largest is returned

int findWinCode(int board[3][3]){
    int winCode=0;

    //check diagonals for line
    if (checkIfSame(board[0][2],board[1][1],board[2][0])){
        winCode=8;
    } else if (checkIfSame(board[0][0],board[1][1],board[2][2])){
        winCode=7;
    } else {
    // check rows and columns for line
        for (int i=0; i<3;i++){
            if (checkIfSame(board[0][i],board[1][i],board[2][i])){ //columns
                winCode=4+i; //4-6
            } else if (checkIfSame(board[i][0],board[i][1],board[i][2])){ //rows
                winCode=1+i; //1-3
            }
        }
    }
    return winCode;
}

bool switchTurn(bool turn){
    if (turn){
        return false;
    } else {
        return true;
    }
}

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    validMove = checkIfValid(board, row, col);

    //implement the move and switch turns
    if (validMove) {
        makeMove(board, row, col, turn);
        turn = switchTurn(turn);
    }

    winCode = findWinCode(board);

    if ((winCode)!=0)
        gameOver = true;
    
    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output

    // Insert code to print the output below
    printBoard(board);
    cout << row << " " << col << " " << turn << " " << validMove << " " << gameOver << " " << winCode <<endl;
    
}



