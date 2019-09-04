#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;


int board [4][4];                             //sets board
int LineDirection[] = {1, 0, -1, 0};          //sets possible directions of movement
int ColumnDirection[] = {0, 1, 0, -1};

pair<int, int> GeneratePosition() {                  //sets if position is occupied or not by use of variable
    int occupied = 1, line, column;
    while (occupied) {
         line = rand() % 4;
         column = rand() % 4;
        if (board[line][column] == 0)
            occupied = 0;
    }
    return make_pair(line, column);
}

void addPiece() {                                 //adds a piece to the board
    pair<int, int> pos = GeneratePosition();
    board[pos.first][pos.second] = 2;

}

void newGame() {                           //sets board to 0 and calls ad piece
    for (int a = 0; a < 4; ++a)
        for (int b = 0; b < 4; ++b)
            board[a][b] = 0;

    addPiece();
}

void printUI() {                              //prints the game interface
    system("cls");
    for (int a = 0; a < 4; ++a) {
        for (int b = 0; b < 4; ++b)
            if (board [a][b] == 0)
                cout << setw(4) << "-";
            else
                cout << setw(4) << board[a][b];
        cout << "\n";
    }
    cout <<"n: New Game, w: Up, s: Down, d: Right, a: Left, q: Quit\n";
}



bool PossibleMove(int line, int column, int nextLine, int nextColumn) {              //checks if the move is possible or not
    if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >=4 || (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
        return false;
    return true;
}

void Move(int direction) {                                                     //sets the movement of the pieces
    int LineStart = 0, ColumnStart = 0, LineStep = 1, ColumnStep = 1;
    if (direction == 0){
        LineStart = 3;
        LineStep = -1;
    }
    if (direction == 1) {
        ColumnStart = 3;
        ColumnStep = -1;
    }
    int movePossible, canAddPiece = 0;                                         //checks if move is possible then adds the numbers together
    cout << "test2";
    do{
        movePossible = 0;
        for (int a = LineStart; a >= 0 && a < 4; a += LineStep){
            for (int b = ColumnStart; b >= 0 && b < 4; b += ColumnStep){
               int nextA = a + LineDirection[direction];
               int nextB = b + ColumnDirection[direction];
            //      cout<<a<<" "<<b<<" "<<nextA<<" "<<nextB<<\n";
                if (board[a][b] && PossibleMove(a, b, nextA, nextB)) {
                    board[nextA][nextB] += board[a][b];
                    board[a][b] = 0;
                    movePossible = 1 ;
                    canAddPiece = 1;
                }
            }
        }
        printUI();
    cout <<"test4";
    } while (movePossible);                           // adds new pieces as moves are executed
    if (canAddPiece)
        addPiece();
    cout <<"test3";
}

int main(){
    srand(time(0));
    char UserCommand[128];
    UserCommand['s'] = 0;
    UserCommand['d'] = 1;
    UserCommand['w'] = 2;
    UserCommand['a'] = 3;
    newGame();
    cout << UserCommand['x'] << "\n";

    while (true){
        printUI();
        char command;
        cin >> command;
        if (command == 'n')
            newGame();
        if (command == 'q')
            break;
        else {
            int currentDirection = UserCommand[command];
            cout << currentDirection << "\n";
            Move(currentDirection);
            cout << "test";
        }
    }
    return 0;
}
