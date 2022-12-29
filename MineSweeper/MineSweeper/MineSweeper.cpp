#include<iostream>
using namespace std;
#define FIRST   "\033[37m"      /* First */
#define SECOND     "\033[31m"      /* Second */
#define THIRD   "\033[32m"      /* Third */
#define FOUR  "\033[33m"      /* Four */

#define row 9
#define coloum 9

class Board
{
private:
    char board[row][coloum];
    char myBoard[row][coloum];
    char emptySpace = '?';
    char mine = '*';
    char flag = '$';
    int flagCount = 0;
    int maxFlag = 10;
    bool isGameOver = false;
public:
    Board(int i, int j) {
        initBoard();
        placeBomb(i, j);
        countNoOfMines();
    }
    void initBoard() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < coloum; j++) {
                board[i][j] = emptySpace;
                myBoard[i][j] = emptySpace;
            }
        }
    }
    void placeBomb(int m, int n) {
        srand(time(0));
        int noOfBomb = 10;
        for (int k = 0; k < noOfBomb; k++) {
            int i = rand() % 9;
            int j = rand() % 9;
            if (board[i][j] == emptySpace && i != m && j != n) {
                board[i][j] = mine;
            }
            else {
                k--;
            }
        }
    }
    bool insideBoard(int i, int j) {
        return i >= 0 && i < row&& j >= 0 && j < coloum;
    }

    bool isMine(int i, int j) {
        if (!insideBoard(i, j)) {
            return false;
        }
        if (board[i][j] == mine) {
            return true;
        }
        return false;
    }

    int getMinesCount(int i, int j) {
        int minesCount = 0;
        if (isMine(i, j - 1)) { minesCount++; }
        if (isMine(i, j + 1)) { minesCount++; }
        if (isMine(i + 1, j)) { minesCount++; }
        if (isMine(i - 1, j)) { minesCount++; }
        if (isMine(i - 1, j - 1)) { minesCount++; }
        if (isMine(i - 1, j + 1)) { minesCount++; }
        if (isMine(i + 1, j - 1)) { minesCount++; }
        if (isMine(i + 1, j + 1)) { minesCount++; }
        return minesCount;
    }
    void countNoOfMines() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < coloum; j++) {
                if (board[i][j] != mine) {
                    int minesCount = getMinesCount(i, j);
                    board[i][j] = '0' + minesCount;
                }
            }
        }
    }
    void reveledAdjecentCell(int i, int j) {
        if (!insideBoard(i, j) || board[i][j] == mine || myBoard[i][j] != emptySpace) {
            return;
        }

        myBoard[i][j] = board[i][j];
        if (insideBoard(i, j) && board[i][j] == '1' || board[i][j] == '2' || board[i][j] == '3') {
            myBoard[i][j] = board[i][j];
            return;
        }

        reveledAdjecentCell(i, j - 1);
        reveledAdjecentCell(i, j + 1);
        reveledAdjecentCell(i + 1, j);
        reveledAdjecentCell(i - 1, j);
        reveledAdjecentCell(i - 1, j - 1);
        reveledAdjecentCell(i - 1, j + 1);
        reveledAdjecentCell(i + 1, j - 1);
        reveledAdjecentCell(i + 1, j + 1);
    }
    void openSelectedCell(int i, int j) {
        if (myBoard[i][j] == emptySpace) {
            if (board[i][j] == mine) {
                myBoard[i][j] = board[i][j];
                isGameOver = true;
            }
            else if (board[i][j] == '0') {
                reveledAdjecentCell(i, j);
            }
            else {
                myBoard[i][j] = board[i][j];
            }
        }
        else {
            cout << SECOND << "\nCan't Open (Cell already Open) " << endl;
        }
    }
    void insertFlag(int i, int j) {
        if (insideBoard(i, j) && myBoard[i][j] == emptySpace) {
            flagCount++;
            myBoard[i][j] = flag;
            if (board[i][j] == mine) {
                board[i][j] = flag;
            }
        }
        else {
            cout << SECOND << "\nCan't insert (Cell already Open) " << endl;
        }
    }
    bool checkIfWon() {
        if (flagCount >= maxFlag) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < coloum; j++) {
                    if (board[i][j] != myBoard[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }
    bool IsGameOver() {
        return isGameOver;
    }

    int getFlagCount() {
        return flagCount;
    }

    int getMaxFlag() {
        return maxFlag;
    }
    void print() {
        for (int j = 0; j <= coloum + 1; j++) {
            if (j == 0 || j == 1) {
                cout << " ";
            }
            else {
                cout << FIRST << " -";
            }
        }
        cout << endl;

        for (int i = 0; i < row; i++) {
            cout << FIRST << i + 1 << " |";

            for (int j = 0; j < coloum; j++) {
                if (myBoard[i][j] == mine) {
                    cout << SECOND << myBoard[i][j];
                }
                else if (myBoard[i][j] == '0' || myBoard[i][j] == '1' ||
                    myBoard[i][j] == '2' || myBoard[i][j] == '3') {
                    cout << THIRD << myBoard[i][j];
                }
                else if (myBoard[i][j] == flag) {
                    cout << FOUR << myBoard[i][j];
                }
                else {
                    cout << FIRST << myBoard[i][j];
                }
                cout << FIRST << "|";
            }
            cout << endl;

            for (int j = 0; j <= coloum + 1; j++) {
                if (j == 0 || j == 1) {
                    cout << " ";
                }
                else {
                    cout << FIRST << " -";
                }
            }
            cout << endl;
        }

        int i = 1;
        for (int j = 0; j <= coloum + 1; j++) {
            if (j == 0 || j == 1) {
                cout << " ";
            }
            else {
                cout <<FIRST << " " << i;
                i++;
            }
        }
        cout << endl;

    }
};
class GameRule {
public:
    GameRule() {
        displayGameTitle();
        gameRule();
        howToplay();
    }
    void displayGameTitle()
    {
        for (int i = 0; i < 40; i++) {
            cout << FIRST << "*";
        }
        cout << endl;
        cout << FIRST << "*                                      *" << endl;
        cout << FIRST << "*        WELCOME TO MINESWEEPR         *" << endl;
        cout << FIRST << "*                                      *" << endl;
        for (int i = 0; i < 40; i++) {
            cout << FIRST << "*";
        }
        cout << endl;
    }
    void gameRule() {
        cout << endl << endl << endl << endl;
        cout << FIRST << "Rules : " << endl;
        cout << FIRST << "1. The board is devided into cell, With Mines (10) randomly distributed. " << endl;
        cout << FIRST << "2. To Win, you need to open all the Cell. " << endl;
        cout << FIRST << "3. You will loose, if you open Mines cell. " << endl;
        cout << FIRST << "4. The number on Cell represent the number of Mines adjecent to it." << endl;
        cout << FIRST << "   Using this information you can determine Cells are safe or contain Mines." << endl;
        cout << FIRST << "5. You will get only 10 Flags.. " << endl;

    }
    void howToplay()
    {
        cout << endl << endl << endl << endl;
        cout << FIRST << "How to Play : " << endl;
        cout << FIRST << "1. Select option ." << endl;
        cout << FIRST<< "     1) Open Cell - To open a new Cell. " << endl;
        cout << FIRST<< "     2) Set Flag - If cells not safe to open, you can mark it as flag. " << endl;
        cout << FIRST << "2. Enter Row and Coloum number to open or set Flag." << endl;
    }
    void gameStatusLogo(string status) {
        for (int i = 0; i < 30; i++) {
            cout << FIRST << "_";
        }
        cout << endl;
        cout << FIRST << "|                            |" << endl;
        cout << FIRST << "|        " << status << "          |" << endl;
        cout << FIRST << "|                            |" << endl;
        for (int i = 0; i < 30; i++) {
            cout << FIRST << "-";
        }
        cout << endl;
    }
};
class GamePlay
{
private:
    int i, j, input;
    int maxInput = 9;
    int minInput = 1;
    int optionMaxInput = 2;
    int optionMinInput = 1;
    GameRule* rule;
public:
    GamePlay() {
        rule = new GameRule();
        wantToPlay();
    }
    bool isInputInRange() {
        return i >= minInput && j >= minInput && i <= maxInput && j <= maxInput;
    }

    bool isOptionInRange() {
        return input >= optionMinInput && input <= optionMaxInput;
    }

    void getUserInput() {
        cout << FIRST << "\nEnter Row Number of Cell: ";
        cin >> i;
        cout << FIRST << "Enter Coloum Number of Cell : ";
        cin >> j;
    }
    void optionSelect() {
        cout << FIRST << "\nSelect Option : " << endl;
        cout <<FIRST<< "  1. Open Cell " << endl;
        cout << FIRST<< "  2. Set Flag " << endl;
        cin >> input;
    }
    void gameLoop() {
        getUserInput();
        if (isInputInRange() == false) {
            cout << SECOND << "Input Not in Range " << endl;
            gameLoop();
        }
        Board board(i - 1, j - 1);
        board.openSelectedCell(i - 1, j - 1);
        board.print();
        while (!board.IsGameOver() && !board.checkIfWon()) {
            optionSelect();
            if (isOptionInRange() == false) {
                continue;
            }
        enterAgain:  // label
            getUserInput();
            if (isInputInRange() == false) {
                cout << SECOND << "Input Not in Range " << endl;
                goto enterAgain;
            }
            if (input == 2) {
                if (board.getFlagCount() < board.getMaxFlag()) {
                    board.insertFlag(i - 1, j - 1);
                }
                else {
                    cout << SECOND << "Flag Stock : NILL (Can't insert more flag) " << endl;
                }
            }
            else {
                board.openSelectedCell(i - 1, j - 1);
            }
            board.print();
        }
        if (board.IsGameOver()) {
            //cout<< RED <<" You Lost "<<endl;
            cout << endl << endl;
            rule->gameStatusLogo(" YOU LOST ");
        }
        else {
            //cout<< GREEN <<" You Won" <<endl;
            cout << endl << endl;
            rule->gameStatusLogo("  YOU WON ");
        }
    }
    void wantToPlay() {
        char play;
        cout << "\n\nEnter Y/y - To Play or N/n - To Quit :";
        cin >> play;

        if (play == 'Y' || play == 'y') {
            rule->gameStatusLogo("GAME START");
            cout << endl << endl;
            gameLoop();
        }
        else {
            rule->gameStatusLogo("   QUIT   ");
        }
    }
};
int main() {

    GamePlay play;

    return 0;
}

