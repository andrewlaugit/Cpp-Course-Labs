//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//


#include <iostream>
#include "playMove.h"
//#include <tic-tac-toe/playMove.h>

using namespace std;

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here

    validMove = checkIfValid(board, row, col);

    if (validMove)
        makeMove(board, row, col, turn);

    winCode = findWinCode(board);

    if ((winCode)!=0)
        gameOver = true;

    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output

    // Insert code to print the output below
    printBoard(board);
    cout << row << " " << col << " " << turn << " " << validMove << " " << gameOver << " " << winCode;
}

bool checkIfValid(int board[][], int row, int col){
    if (board[row][col]==0){
        return true;
    } else {
        return false;
    }
}

void makeMove(int board[][], int row, int col, bool turn){
    if (turn){
        board[row][col]=X;
    } else {
        board[row][col]=O;
    }
}

//determine if input line are filled by X/O and are same
bool checkIfSame(int box1, int box2, int box3){
    if (box1!=0 && box1==box2 && box2&&box3){
        return true;
    } else {
        return false;
    }
}

void printBoard(int board[][]){
    for (int i=0; i<3; i++){
        for (int j=0;j<3;j++){
            cout << board[i][j] << " ";
        }
    }
}

int findWinCode(int board[][]){
    int winCode=0;
    
    //check diagonals for line
    if (checkIfSame(board[0][0],board[1][1],board[2][2])){
        winCode=7;
    } else if (checkIfSame(board[0][2],board[1][1],board[2][0])){
        winCode=8;
    } else {
    // check rows and columns for line
        for (int i=0; i<3;i++){
            if (checkIfSame(board[i][0],board[i][1],board[i][2]){ //rows
                winCode=1+i;
            } else if (checkIfSame(board[0][i],board[1][i],board[2][i]){ //columns
                winCode=4+i;
            }
        }
    }
    return winCode;
}
