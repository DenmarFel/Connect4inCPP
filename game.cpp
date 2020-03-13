#include <iostream>

class Game {
private:
    int turn = 0;
    bool gameFinished = false;

    std::string players[2];
    char p1symbol = 'o';
    char p2symbol = 'x';

    char board[6][7] = {' '};
    int boardRowLengths[7] = {0};
    int boardPiecesEntered = 0;
    int lastUpdated[2];

public:
    void run() {
        std::cout << "########## Welcome to Connect 4! ###########\n";
        setupGame();

        while (gameFinished != true) {
            displayBoard();
            playerTurn();
            if (detectWinner() == true) {
                break;
            };
            if (turn == 0) {
                turn++;
            } else {
                turn--;
            }
        }
        displayBoard();
        std::cout << "Congratulations! " << players[turn] << " wins!" << std::endl;
    }

    void setupGame() {
        std::cout << "Enter name of Player 1:";
        std::getline(std::cin, players[0]);

        std::cout << "Enter name of Player 2:";
        std::getline(std::cin, players[1]);
    }

    void displayBoard() {
        std::string gameInfo = "##############################\n";
        gameInfo = gameInfo + "Match: " + players[0] + "(" + p1symbol + ")" + " vs. " + players[1] + "(" + p2symbol + ")\n";
        gameInfo = gameInfo + "Current turn: " + players[turn] + "\n\n";
        std::cout << gameInfo;

        std::string boardRep;
        for (int row = 5; row > -1; row--) {
            boardRep = boardRep + '|';
            for (int column = 0; column < 7; column++) {
                boardRep = boardRep + board[row][column] + '|';
            }
            boardRep = boardRep + '\n';
        }
        boardRep = boardRep + "=1=2=3=4=5=6=7=\n\n";

        std::cout << boardRep;
    }

    bool detectWinner() {
        int row = lastUpdated[0];
        int column = lastUpdated[1];

        int down = getDownChips(row, column);
        int left = getLeftChips(row, column);
        int right = getRightChips(row, column);
        int leftUpDiag = getLeftUpDiag(row, column);
        int rightUpDiag = getRightUpDiag(row, column);
        int leftDownDiag = getLeftDownDiag(row, column);
        int rightDownDiag = getRightDownDiag(row, column);

        if (down > 2 || left + right > 2 || leftUpDiag + rightDownDiag > 2 || rightUpDiag + leftDownDiag > 2 ) {
            return true;
        } else {
            return false;
        }
    }

    int getDownChips(int row, int column) {
        int total = 0;
        if (row > 2) {
            if (board[row-1][column] == getPlayerChip()) { total++; }
            if (board[row-2][column] == getPlayerChip()) { total++; }
            if (board[row-3][column] == getPlayerChip()) { total++; }
        }
        return total;
    }

    int getLeftChips(int row, int column) {
        int scans = 0;
        int total = 0;
        column--;
        while (scans < 3 && column > -1) {
            if (board[row][column] == getPlayerChip()) {
                total++;
                scans++;
                column--;
            } else {
                break;
            }
        }
        return total;
    }

    int getRightChips(int row, int column) {
        int scans = 0;
        int total = 0;
        column++;
        while (scans < 3 && column < 7) {
            if (board[row][column] == getPlayerChip()) {
                total++;
                scans++;
                column++;
            } else {
                break;
            }
        }
        return total;
    }

    int getLeftUpDiag(int row, int column) {
        int scans = 0;
        int total = 0;
        row++;
        column--;
        while (scans < 3 && row < 6 && column > -1) {
            if (board[row][column] == getPlayerChip()) {
                total++;
                scans++;
                row++;
                column--;
            } else {
                break;
            }
        }
        return total;
    }

    int getRightUpDiag(int row, int column) {
        int scans = 0;
        int total = 0;
        row++;
        column++;
        while (scans < 3 && row < 6 && column < 7) {
            if (board[row][column] == getPlayerChip()) {
                total++;
                scans++;
                row++;
                column++;
            } else {
                break;
            }
        }
        return total;
    }

    int getLeftDownDiag(int row, int column) {
        int scans = 0;
        int total = 0;
        row--;
        column--;
        while (scans < 3 && row > -1 && column > -1) {
            if (board[row][column] == getPlayerChip()) {
                total++;
                scans++;
                row--;
                column--;
            } else {
                break;
            }
        }
        return total;
    }

    int getRightDownDiag(int row, int column) {
        int scans = 0;
        int total = 0;
        row--;
        column++;
        while (scans < 3 && row > -1 && column < 7) {
            if (board[row][column] == getPlayerChip()) {
                total++;
                scans++;
                row--;
                column++;
            } else {
                break;
            }
        }
        return total;
     }

    char getPlayerChip() {
        if (turn == 0) { return p1symbol; }
        return p2symbol;
    }

    void playerTurn() {
        bool validColumn = false;
        int chosenColumn;

        while (validColumn != true) {
            std::cout << "Enter a column to place your chip (1-7):";
            std::cin >> chosenColumn;

            if (chosenColumn < 1 || chosenColumn > 7) {
                std::cout << "[ERROR] Not a valid column! Please try again.\n";
            } else if (boardRowLengths[chosenColumn-1] > 5) {
                std::cout << "[ERROR] Column is full! Please try again.\n";
            } else {
                validColumn = true;
            }
        }
        board[boardRowLengths[chosenColumn-1]][chosenColumn-1] = getPlayerChip();
        lastUpdated[0] = boardRowLengths[chosenColumn-1];
        lastUpdated[1] = chosenColumn-1;

        boardRowLengths[chosenColumn-1]++;
        boardPiecesEntered++;;
    }
};