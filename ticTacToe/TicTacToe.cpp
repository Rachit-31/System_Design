#include<bits/stdc++.h>
using namespace std;
class Player{
    public:
    string name;
    char symbol;

    Player(string name, char symbol){
        this->name = name;
        this->symbol = symbol;
    }
};
class Board{
private:
    vector<vector<char>>grid;

public:
    Board(){
        grid = vector<vector<char>>(3, vector<char>(3, ' '));
    }

    void printBoard() {
        cout << endl;
        for (int i = 0; i < 3; i++) {
            cout << " ";
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "---+---+---" << endl;
        }
        cout << endl;
    }

    bool markCell(int row, int col, char symbol){
        if(row >= 0 && row < 3 && col >=0 && col < 3 && grid[row][col] == ' '){
            grid[row][col] = symbol;
            return true;
        }


        return false;
    }

    bool checkWin(char symbol) {
        for (int i = 0; i < 3; i++) {
            if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
                (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)) {
                return true;
            }
        }
        if ((grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
            (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)) {
            return true;
        }

        return false;
    }
    bool isFull() {
        for (auto row : grid)
            for (auto cell : row)
                if (cell == ' ')
                    return false;
        return true;
    }
};


class Game{
private:
    Player player1;
    Player player2;
    Board board;
    int turn;

public:
    Game(Player p1, Player p2) : player1(p1), player2(p2), turn(0) {}

    void switchTurn() {
        turn = 1 - turn;
    }


    void start(){
        while(true){
            board.printBoard();
            Player current = (turn == 0) ? player1 : player2;
            int row, col;
            cout << current.name << "'s turn (" << current.symbol << ")." << endl;
            cout << "Enter row and column (0-2): ";
            cin>>row>>col;

            if(board.markCell(row, col, current.symbol)){
                if (board.checkWin(current.symbol)) {
                    board.printBoard();
                    cout << current.name << " wins! 🎉" << endl;
                    break;
                } else if (board.isFull()) {
                    board.printBoard();
                    cout << "It's a draw!" << endl;
                    break;
                } else {
                    switchTurn();
                }
            }
            else{
                cout << "Invalid move. Try again." << endl;
            }
        }
    }
};
int main(){
    string name1, name2;

    cout<<"enter the player 1 name: ";
    cin>>name1;

    cout<<"enter the player 2 name: ";
    cin>>name2;


    Player p1(name1, 'X');
    Player p2(name2, '0');


    Game game(p1, p2);

    game.start();

    return 0;
}