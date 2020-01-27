#include <iostream>
#include <string>

int currentPlayer = 0;
char board[3][3] = {{'-', '-', '-'},
                    {'-', '-', '-'},
                    {'-', '-', '-'}};
std::string playerOneName;
std::string playerTwoName;
bool playerWin = false;

void getPlayerNames() {
    std::cout << "Please enter a name: " << std::endl;
    std::cin >> playerOneName;
    std::cout << "Please enter a name for player two: " << std::endl;
    std::cin >> playerTwoName;
}

bool checkLine() {
    char playerChar;
    if (currentPlayer == 0) {
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

bool validatePos(int xPos, int yPos) {
    if (xPos >= 0 && xPos < 3 && yPos >= 0 && yPos < 3) {
        if (board[xPos][yPos] != '-') {
            std::cout << "Sorry the other player has already used this spot!" << std::endl;
        } else {
            return true;
        }
    } else {
        std::cout << "Sorry those co-ordinates aren't valid" << std::endl;
    }
    return false;
}

void boardChoice() {
    while (true) {
        int xPos;
        int yPos;
        while (true) {
            for (auto &x : board) {
                for (char y : x) {
                    std::cout << y;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            if (currentPlayer == 0) {
                std::cout << "It's Player One's turn!" << std::endl;
                std::cout << "Please enter the x you want: " << std::endl;
                std::cin >> xPos;
                std::cout << "Please enter the y you want: " << std::endl;
                std::cin >> yPos;
                if (!validatePos(xPos, yPos)) {
                    continue;
                } else {
                    board[xPos][yPos] = 'X';
                    if (checkLine()) {
                        playerWin = true;
                    }
                    currentPlayer++;
                    break;
                }
            } else {
                std::cout << "It's Player Twos's turn!" << std::endl;
                std::cout << "Please enter the x you want: " << std::endl;
                std::cin >> xPos;
                std::cout << "Please enter the y you want: " << std::endl;
                std::cin >> yPos;
                if (!validatePos(xPos, yPos)) {
                    continue;
                } else {
                    board[xPos][yPos] = 'O';
                    if (checkLine()) {
                        playerWin = true;
                    }
                    currentPlayer--;
                    break;
                }
            }
        }
        if (playerWin) {
          for (auto &x : board) {
                for (char y : x) {
                    std::cout << y;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
          if(currentPlayer-1 == 0) {
            std::cout << "Player 1 Wins!" << std::endl;
          } else {
            std::cout << "Player 2 Wins!" << std::endl;
          }
          
            break;
        }
    }
}

int main() {
    boardChoice();
    return 0;
}