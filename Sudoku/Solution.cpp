#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

const int MAX_SIZE = 9;        // 九宫格

int ktRound = 1;

struct Pos {
    Pos(int x, int y) : row(x), col(y) {};
    int row;
    int col;
};

typedef deque <Pos> qpos;
qpos Q;        // 记录要放置数字的位置

/// Sudoku Matrix (9 X 9)
int sudoku[MAX_SIZE][MAX_SIZE] = {0};

void printSudoku(int round) {
    
    ofstream solutionTxtFile;
    solutionTxtFile.open ("sudokuSolution.txt", ios_base::app); // ******************DEBUG******************
    
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            
            if (j != MAX_SIZE - 1) {
                solutionTxtFile << sudoku[i][j] << " ";
            } else {
                solutionTxtFile << sudoku[i][j];
            }
        }
        
        solutionTxtFile << endl;
    }
    
    solutionTxtFile << endl;
    
}

bool check(Pos p, int n) {
    int cur_row = p.row;
    int cur_col = p.col;
    // 验证行列是否合格
    for (int i = 0; i < MAX_SIZE; i++) {
        if (n == sudoku[i][cur_col] || n == sudoku[cur_row][i]) {
            return false;
        }
    }
    
    // 验证九宫格内是无复生数字
    int grid_row = ( cur_row / 3 ) * 3;
    int grid_col = ( cur_col / 3 ) * 3;
    for (int i = 0; i < 3; i++) {
        if (n == sudoku[grid_row][i + grid_col] ||
            n == sudoku[grid_row + i][grid_col]) {
            return false;
        }
    }
    
    return true;
}

bool place(qpos & Q) {
    // 递归结束条件为没有要断续放置数字的位置
    if (Q.empty()) {
        printSudoku(ktRound++);
        return true;
    }
    Pos cur(Q.front().row, Q.front().col);    // 当前需要放置的位置信息
    Q.pop_front();
    for (int i = 1; i <= 9; i++) {        // 从1到9轮流尝试
        if ( check(cur, i) ) {
            sudoku[cur.row][cur.col] = i;    // 放置数字i到当前位置
            if ( !place(Q) ) {        // 放置下一位置
                // 下一位置放置失败，则在当前位置尝试放置下一个i
                sudoku[cur.row][cur.col] = 0;    // 将当前位置值重置
            } else {    // 下一位置放置成功
                return true;
            }
        }
    }
    Q.push_front(cur);    //当前位置不论怎么放置数字，下一位置都无法放置成功，
    // 重新插入该位置信息，返回上一级放置位置
    return false;
}

/// Verify whether a file exists
bool is_file_exist(const char *fileName) {
    ifstream infile(fileName);
    return infile.good();
}

/// Verify there is a '/'
bool isInside(const std::string & str, char c) {
    return str.find(c) != std::string::npos;
}

void solve(const char *absolutePath) {
    
    // FIXME: Verify valid path
    if (!is_file_exist(absolutePath) || !isInside(absolutePath, '/')) {
        cout << "Path Error! Use a valid path please." << endl;
		exit(0);
	}
    
    ifstream inFile;
    inFile.open(absolutePath);

    int index = 0; // DEBUG
    
    while (1) {
        bool breakWhileFlag = false;
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                if (!inFile.eof()) {
                    char digit;
                    inFile >> digit;
                    sudoku[i][j] = digit - '0';
                    
                    index++; // DEBUG
                    
                } else {
                    breakWhileFlag =true;
                    break;
                }
            }
            
            if (breakWhileFlag) {
                break;
            }
        }
        
        if (index % 81 == 0) {
            
            /*xxxxxxxxxxxxxxxxxxxxxxxDON'T EVER TRY TO MODIFYxxxxxxxxxxxxxxxxxxxxxxxx*/
            // Q中保存需要放置数字的位置
            for (int i = 0; i < MAX_SIZE; i++) {
                for (int j = 0; j < MAX_SIZE; j++) {
                    if (0 == sudoku[i][j]) {
                        Q.push_back(Pos(i, j));
                    }
                }
            }
            place(Q);
            /*xxxxxxxxxxxxxxxxxxxxxxxDON'T EVER TRY TO MODIFYxxxxxxxxxxxxxxxxxxxxxxxx*/
            
        }
        
        if (breakWhileFlag) {
            break;
        }
        
    }
    
}

