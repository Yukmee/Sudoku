#include <iostream>
#include <fstream>
using namespace std;

int sudokuMatrix[9][9];
int sudokuMatrixCount = 0, priNumber = 0;


// MARK: -Helper Methods:
int generateInteger(const char *string) {
    int integer = 0;
    int multiplier = 1;
    for (unsigned int i = 0; i < strlen(string); i++) {
        if (string[i] > '9' || string[i] < '0') {
            cout << "InputError! Type<int> and make sure it's also positive please." << endl;
            exit(0);
        }
    }
    for (long int i = strlen(string) - 1; i >= 0; i--) {
        integer += (string[i] - '0') * multiplier;
        multiplier *= 10;
    }
    if (integer <= 0 || integer > 1000000) {
        cout << "InputError! Use a smaller(or bigger) integer please." << endl;
        exit(0);
    }
    return integer;
}


void print() {

    ofstream sudokuTxtFile;
    sudokuTxtFile.open ("sudoku.txt", ios_base::app);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudokuTxtFile << sudokuMatrix[i][j];
            if (j != 8) {
                sudokuTxtFile << " ";
            }
        }
        sudokuTxtFile << endl;
    }
    
    sudokuTxtFile << endl;
}


bool judge(int x, int y) {
    for (int i = 0; i < 9; i++) {
        if (sudokuMatrix[x][i] == sudokuMatrix[x][y] && y != i) {
            return true;
        }
        if (sudokuMatrix[i][y] == sudokuMatrix[x][y] && x != i) {
            return true;
        }
    }
    int n1 = x / 3;
    int n2 = y / 3;
    n1 *= 3;
    n2 *= 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudokuMatrix[n1 + i][n2 + j] == sudokuMatrix[x][y] && n1 + i != x && n2 + j != y) {
                return true;
            }
        }
    }
    return false;
}


void dfs(int x, int y) {
    for (int i = 1; i <= 9; i++) {
        sudokuMatrix[x][y] = i;
        if (judge(x, y) == 0) {
            if (x == 8 && y == 8) {
                print();
                priNumber++;
                if (priNumber == sudokuMatrixCount) {
                    exit(0);
                }
            }
            else if (y == 8) {
                dfs(x + 1, 0);
                sudokuMatrix[x + 1][0] = 0;
            }
            else if (y != 8) {
                dfs(x, y + 1);
                sudokuMatrix[x][y + 1] = 0;
            }
        }
    }
}

void sudokuConstructor(int n) {
    sudokuMatrixCount = n;
    sudokuMatrix[0][0] = 3; // (4 + 6) % 9 + 1 = 2
    priNumber = 0;
    dfs(0, 1);
}

// MARK: - Constructor:
void construct(const char *string) {
    
    int integer = generateInteger(string);
    sudokuConstructor(integer);
    
}




