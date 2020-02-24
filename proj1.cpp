/*****************************************
** File:    proj1.cpp
** Project: CMSC 202 Project 1, Spring 2020
** Author:  Nicholas Perry
** Date:    2/18/20
** Section: 21
** E-mail:  nperry2@umbc.edu
**
** This file contains the main driver program for Project 1.
** This program is the game 'Fifteen' where the user has to 
** slide all the tiles into order from 1 to 15 with zero in
** the last slot.
**
***********************************************/

#include <iostream> 
#include <fstream>
using namespace std;

const int LENGTH = 4;   //length of the 2D array game baord
const int HEIGHT = 4;   //height of the 2D array game board
const int INPUTARRAYLENGTH = 2; //size of the input array for user input

//These are the constants for the directions
const int UP = 1; 
const int LEFT = 2;
const int DOWN = 3;
const int RIGHT = 4;

const int DEFUALTBOARD[LENGTH][HEIGHT] = { {1, 2, 3, 4}, //This is the defualt game board if the user
										   {5, 6, 7, 8}, //does not import a file
										   {9, 10, 11, 12},
										   {13, 14, 0, 15} };

void printBoard(int board[][HEIGHT]); 
int promptUser(); 
int getDirectionOfSwap(int board[][HEIGHT], int arrayOfValues[INPUTARRAYLENGTH]); 
bool checkForGameEnd(int board[][HEIGHT]); 
bool validInput(int values[INPUTARRAYLENGTH]); 

int main() {

	int gameBoard[LENGTH][HEIGHT];
	int inputArray[INPUTARRAYLENGTH] = {};

	int answer, inputValue, direction, placeHolder;
	int selectedRow, selectedColumn;
	int currentIndex = 0;
	
	char playAgain = 'n';
	ifstream inputStream;
	string fileName;

	do {
		cout << "Welcome to the Fifteen Game" << endl;
		answer = promptUser();
		playAgain = 'n';
		//sets up the board
		if (answer == 1) {
			cout << "What is the file name?";
			cin >> fileName;
			inputStream.open(fileName);

			for (int i = 0; i < LENGTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					inputStream >> gameBoard[i][j];
				}
			}
			
		}
		else if (answer == 2) {
			cout << "Loading default" << endl;
			for (int i = 0; i < LENGTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					gameBoard[i][j] = DEFUALTBOARD[i][j];
				}
			}
		}
		printBoard(gameBoard);

		//main game loop
		while (!checkForGameEnd(gameBoard)) {
			currentIndex = 0;
			//get user input
			cout << "What is the row (left) and column (top) to slide?" << endl;
			cin >> inputValue;
			inputArray[currentIndex] = inputValue;

			while (currentIndex < (INPUTARRAYLENGTH - 1)) {
				cin >> inputValue;
				currentIndex++;
				inputArray[currentIndex] = inputValue;
			}

			if (validInput(inputArray)) {
				direction = getDirectionOfSwap(gameBoard, inputArray);
				if (direction == 0) {
					cout << "You chose the blank\nThat tile cannot slide" << endl;
				}
				//swap the tiles and prompts user
				else {
					selectedRow = inputArray[0] - 1;
					selectedColumn = inputArray[1] - 1;

					switch (direction)
					{
					case UP:
						cout << "The tile slid up" << endl;
						//swap tiles
						placeHolder = gameBoard[selectedRow][selectedColumn];
						gameBoard[selectedRow + 1][selectedColumn] = placeHolder;
						gameBoard[selectedRow][selectedColumn] = 0;
						break;

					case LEFT:
						cout << "The tile slid left" << endl;
						//swap tiles
						placeHolder = gameBoard[selectedRow][selectedColumn];
						gameBoard[selectedRow][selectedColumn + 1] = placeHolder;
						gameBoard[selectedRow][selectedColumn] = 0;
						break;

					case DOWN:
						cout << "The tile slid down" << endl;
						//swap tiles
						placeHolder = gameBoard[selectedRow][selectedColumn];
						gameBoard[selectedRow - 1][selectedColumn] = placeHolder;
						gameBoard[selectedRow][selectedColumn] = 0;
						break;

					case RIGHT:
						cout << "The tile slid right" << endl;
						//swap tiles
						placeHolder = gameBoard[selectedRow][selectedColumn];
						gameBoard[selectedRow][selectedColumn - 1] = placeHolder;
						gameBoard[selectedRow][selectedColumn] = 0;
						break;

					default:
						cout << "That tile is not next to a blank" << endl;
					}

					printBoard(gameBoard);
				}
			}
			else {
				cout << "The inputs are not valid" << endl;
			}
			//checks for a win
			if (checkForGameEnd(gameBoard)) {
				cout << "Congrats you've won!" << endl;
				cout << "Play again? (y/n) " << endl;
				cin >> playAgain;

				while (!(playAgain == 'y' || playAgain == 'n')) {
					//asks the user if they want to play again after they won
					cout << "Incorrect input" << endl;
					cout << "Play again? (y/n) " << endl;
					cin >> playAgain;
				}
			}
			else {
				cout << "No winner" << endl;
			}
		}
	} while (playAgain == 'y');

	cout << "Thank you for playing the game of fifteen!" << endl;

	return 0;
}

// printBoard
// Prints the 2D game board 
// PreCondition: A fully filled 2D array
// PostCondition: n/a
void printBoard(int board[][HEIGHT]) {
	cout << "      ";

	for (int i = 0; i < HEIGHT; i++) {
		cout << (i + 1) << "    ";
	}

	cout << endl;

	for (int i = 0; i < LENGTH; i++) {
		cout << " " << (i + 1) << " | ";

		for (int j = 0; j < HEIGHT; j++) {
			if (board[i][j] < 10) {
				cout << " " << board[i][j] << " | ";
			}
			else {
				cout << board[i][j] << " | ";
			}
		}
		cout << endl;
	}
}

// promptUser
// promps the user to select a file or use the defualt baord
// PreCondition: n/a
// PostCondition: returns the answer from the user; either 1 or 2
int promptUser() {
	int answer;
	cout << "Do you want to get a file? \n1. Yes \n2. No" << endl;
	cin >> answer;

	while (cin.fail() || answer < 1 || answer > 2) {
		cout << "Do you want to get a file? \n1. Yes \n2. No" << endl;
		cin.clear();
		cin.ignore();
		cin >> answer;
	}

	return answer;
}

// getDirectionOfSwap
// from the values of the input, returns the direction of a possible swap
// PreCondition: fully filled 2D array game baord, fully filled array of coordinate values 
// PostCondition: returns if the values given are a possible swap, or not an the direction if so by int values
int getDirectionOfSwap(int board[][HEIGHT], int arrayOfValues[INPUTARRAYLENGTH]) {
	int row = arrayOfValues[0] - 1;
	int column = arrayOfValues[1] - 1;

	//up 1
	if (((row - 1) >= 0) && (board[row - 1][column] == 0)) {
		return DOWN;
	}
	//left 2
	else if ((column - 1) >= 0 && board[row][column - 1] == 0) {
		return RIGHT;
	}
	//down 3
	else if ((row + 1) <= 3 && board[row + 1][column] == 0) {
		return UP;
	}
	//right 4
	else if ((column + 1) <= 3 && board[row][column + 1] == 0) {
		return LEFT;
	}
	// value is the blank
	else if (board[row][column] == 0) {
		return 0;
	}
	//0 no swap possible
	else {
		return -1;
	}
}

// validInput
// validates the user input
// PreCondition: a fully filled array of values
// PostCondition: returns a boolean, true if all the values are valid, false if not
bool validInput(int values[INPUTARRAYLENGTH]) {
	for (int i = 0; i < INPUTARRAYLENGTH; i++) {
		if (values[i] < 1 || values[i] > 4) {
			return false;
		}
	}
	return true;
}


// checkForGameEnd
// checks to make sure the board isnt in order
// PreCondition: a fully filled 2D array of values
// PostCondition: returns a boolean, true if the array is in the correct order, false if not
bool checkForGameEnd(int board[][HEIGHT]) {
	int counter = 1;

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			//checks if the value is in accending order
			if (counter != board[i][j]) {
				//exception for 0 in the last slot
				if (i == 3 && j == 3 && board[i][j] == 0) {
					return true;
				}
				else {
					return false;
				}
			}
			counter++;
		}
	}
	return true;
}