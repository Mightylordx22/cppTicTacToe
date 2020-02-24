// <- Includes ->

#include <pch.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

// <- Global Variables ->

int currentPlayer = 0;
std::string playerOneName;
bool playerWin = false;

// <- Functions ->

/**
 * Asks for the player's name and stores it in the global variable playerOneName.
 */
void getPlayerName() {
	std::cout << "Welcome to my game of Tic Tac Toe! (You are 'X') " << std::endl << "Please enter your name: " << std::endl;
	std::cin >> playerOneName;
}

/**
 * Checks all the possible combinations on the board to see if either the player or the computer has won.
 * @return true if any combinations are met else return false
 */
bool checkLine(char board[][3]) {
	char playerChar;
	if (currentPlayer % 2 == 0) {
		playerChar = 'X';
	} else {
		playerChar = 'O';
	}
	if (board[0][0] == playerChar && board[0][1] == playerChar && board[0][2] == playerChar) return true;
	else if (board[1][0] == playerChar && board[1][1] == playerChar && board[1][2] == playerChar) return true;
	else if (board[2][0] == playerChar && board[2][1] == playerChar && board[2][2] == playerChar) return true;
	else if (board[0][0] == playerChar && board[1][0] == playerChar && board[2][0] == playerChar) return true;
	else if (board[0][1] == playerChar && board[1][1] == playerChar && board[2][1] == playerChar) return true;
	else if (board[0][2] == playerChar && board[2][1] == playerChar && board[2][2] == playerChar) return true;
	else if (board[0][0] == playerChar && board[1][1] == playerChar && board[2][2] == playerChar) return true;
	else return board[0][2] == playerChar && board[1][1] == playerChar && board[2][0] == playerChar;
}

/**
 * Validate the position the player wants to play by checking the character in the position passed in.
 * @param xPos The X position the current player has chosen.
 * @param yPos The Y position the current player has chosen.
 * @return true if the user's co-ordinates are valid otherwise return false
 */
bool validatePos(int xPos, int yPos, char board[][3]) {
	if (xPos >= 0 && xPos < 3 && yPos >= 0 && yPos < 3) {
		if (board[xPos][yPos] != '-') {
			std::cout << "Sorry the other player has already used this spot!" << std::endl;
		} else {
			return true;
		}
	} else {
		std::cout << "Sorry those co-ordinates aren't valid! Please try again!" << std::endl;
	}
	return false;
}

/**
 * Prints the board to the console and formats it so that it looks nice.
 * The board should look like the following by default:
 * +---+---+---+
 * | - | - | - |
 * +---+---+---+
 * | - | - | - |
 * +---+---+---+
 * | - | - | - |
 * +---+---+---+
 */
void printBoard(char board[][3]) {
	std::cout << "      [0]   [1]   [2]\n    +-----+-----+-----+" << std::endl;
	for (int x = 0; x < 3; x++) {
		std::cout << "[" << x << "] |  ";
		for (int y = 0; y < 3; y++) {
			std::cout << board[x][y] << "  |  ";
		}
		std::cout << "\n    +-----+-----+-----+" << std::endl;
	}
}

/**
 * A countdown that starts a 5 second timer before the game starts.
 */
void countdown() {
	std::cout << std::endl << "The game will start in 5 seconds" << std::endl;
	for (int i = 5; i > 0; i--) {
		std::cout << std::endl << i << std::endl;
		Sleep(1000);
	}
	std::cout << std::endl << "The game will now start!" << std::endl << std::endl;
}

/**
 * Clears the board
 */
char clearBoard(char board[][3]) {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			board[x][y] = '-';
		}
	}
	return board[3][3];
}

/**
 * The main function that gets the input from the user and then calls the other functions to validate and update the board.
 * If the currentPlayer variable is even then it's the users's turn otherwise it's the computer's turn.
 */
void playGame() {
	char board[3][3] = { {'-', '-', '-'},
						 {'-', '-', '-'},
						 {'-', '-', '-'} };
	getPlayerName();
	countdown();
	while (true) {
		if (currentPlayer > 8) {
			char retry;
			std::cout << "The game is a draw would you like to play again: ( [Y] / [N] )" << std::endl;
			std::cin >> retry;
			if (retry == 'Y') {
				currentPlayer = 0;
				board[3][3] = clearBoard(board);
				playGame();
			} else {
				std::cout << "You didn't choose 'Y', thank you for playing my game" << std::endl;
				break;
			}
		}
		int xPos;
		int yPos;
		while (true) {
			printBoard(board);
			if (currentPlayer % 2 == 0) {
				std::cout << "\nIt's " << playerOneName << "'s turn!" << std::endl;
				std::cout << "Please enter the x coord you want: " << std::endl;
				std::cin >> xPos;
				std::cout << "Please enter the y coord you want: " << std::endl;
				std::cin >> yPos;
				if (!validatePos(xPos, yPos, board)) {
					continue;
				} else {
					board[xPos][yPos] = 'X';
					if (checkLine(board)) {
						playerWin = true;
					}
					break;
				}
			} else {
				xPos = rand() % 3;
				yPos = rand() % 3;
				std::cout << "\nIt's the computer's turn now and they chose position: [" << xPos << " , " << yPos
					<< "]" << std::endl << std::endl;
				if (!validatePos(xPos, yPos, board)) {
					continue;
				} else {
					board[xPos][yPos] = 'O';
					if (checkLine(board)) {
						playerWin = true;
					}
					break;
				}
			}
		}
		if (playerWin) {
			printBoard(board);
			if (currentPlayer % 2 == 0) {
				std::cout << "\nThe game is now Over! " << playerOneName << " Wins!" << std::endl;
			} else {
				std::cout << "\nThe computer has won! Better luck next time :(" << std::endl;
			}
			break;
		}
		currentPlayer++;
	}
}

// <- Main Program ->

/**
 * Prints the board to the console and formats it so that it looks nice.
 * The board should look like the following by default:
 */
int main() {
	srand(time(0));
	playGame();
	return 0;
}