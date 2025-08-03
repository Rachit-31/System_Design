#include<bits/stdc++.h>
using namespace std;

class Player{
    public:
    string name;
    int position;

    Player(string name){
        this->name = name;
        this->position = 0;
    }
};

class Dice {
public:
    int roll() {
        return rand() % 6 + 1;
    }
};

class Board {
public:
    map<int, int> snakes;
    map<int, int> ladders;

    Board() {
        snakes[99] = 54;
        snakes[70] = 55;
        snakes[52] = 42;
        snakes[25] = 2;
        snakes[95] = 72;

        ladders[6] = 25;
        ladders[11] = 40;
        ladders[60] = 85;
        ladders[46] = 90;
        ladders[17] = 69;
    }

    int getNewPosition(int pos) {
        if (snakes.count(pos)) {
            cout << "Oops! Bitten by a snake 🐍 from " << pos << " to " << snakes[pos] << endl;
            return snakes[pos];
        }
        if (ladders.count(pos)) {
            cout << "Yay! Climbed a ladder 🪜 from " << pos << " to " << ladders[pos] << endl;
            return ladders[pos];
        }
        return pos;
    }
};

class Game{
    Board board;
    Dice dice;
    queue<Player*>players;

public:
    Game(Player* p1, Player* p2) {
        players.push(p1);
        players.push(p2);
        srand(time(NULL));
    }

        void play() {
            while (true) {
                Player* curr = players.front();
                players.pop();

                cout << curr->name << "'s turn. Press enter to roll dice.";
                cin.get();

                int rollValue = dice.roll();
                cout << curr->name << " rolled a " << rollValue << endl;

                int nextPos = curr->position + rollValue;

                if (nextPos > 100) {
                    cout << "Can't move! Need exact roll to reach 100." << endl;
                } else {
                    nextPos = board.getNewPosition(nextPos);
                    curr->position = nextPos;
                    cout << curr->name << " moved to " << curr->position << endl;
                }

                if (curr->position == 100) {
                    cout << "🎉 " << curr->name << " wins the game! 🎉" << endl;
                    break;
                }

                players.push(curr);
            }
    }

};
int main(){
    Player* p1 = new Player("Alice");
    Player* p2 = new Player("Bob");

    
    Game game(p1, p2);
    game.play();

    delete p1;
    delete p2;
    return 0;

    return 0;
}