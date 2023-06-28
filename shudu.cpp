#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstring>
#include <string>
#include <numeric>

#define BOARD_SIZE 9
#define EMPTY 0

// 检查数字是否可以放置在给定位置
bool isSafe(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // 检查同一行或同一列中是否已存在该数字
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // 检查该数字是否已存在于同一 3x3 网格中
    int gridStartRow = row - row % 3;
    int gridStartCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + gridStartRow][j + gridStartCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// 使用回溯解决数独难题的功能
bool solveSudoku(std::vector<std::vector<int>>& board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Find an empty cell
            if (board[row][col] == EMPTY) {
                // Try placing numbers from 1 to 9
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku(board)) {
                            return true;
                        }

                        board[row][col] = EMPTY;
                    }
                }

                return false;
            }
        }
    }

    return true;
}

// 生成数独谜题
void generateSudoku(int numPuzzles) {
    //std::ofstream file("sudoku_puzzles.txt");
    std::ofstream file("test.txt");

    std::vector<int> nums(BOARD_SIZE);
    std::iota(nums.begin(), nums.end(), 1);

    std::random_device rd;
    std::mt19937 generator(rd());

    for (int i = 0; i < numPuzzles; i++) {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

        std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

        for (int j = 0; j < BOARD_SIZE; j++) {
            board[0][j] = nums[j];
        }

        solveSudoku(board);

        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                file << board[row][col] << " ";
            }
            file << std::endl;
        }
        file << std::endl;
    }

    file.close();
}

// 从文件中读取和解决数独谜题
void solveSudokuFromFile(const char* path) {
    std::ifstream file(path);
    if (!file) {
        std::cout << "File not found." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        int row = 0;
        char* token = strtok(const_cast<char*>(line.c_str()), " ");
        while (token != nullptr) {
            board[row / BOARD_SIZE][row % BOARD_SIZE] = std::atoi(token);
            token = strtok(nullptr, " ");
            row++;
        }

        if (row == BOARD_SIZE * BOARD_SIZE) {
            solveSudoku(board);

            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; col++) {
                    std::cout << board[row][col] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            board = std::vector<std::vector<int>>(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));
        }
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        int numPuzzles = std::atoi(argv[2]);
        generateSudoku(numPuzzles);
        std::cout << "Sudoku puzzles generated successfully." << std::endl;
    } else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        solveSudokuFromFile(argv[2]);
    } else {
        std::cout << "Invalid command-line arguments." << std::endl;
        std::cout << "Usage: shudu.exe -c numPuzzles" << std::endl;
        std::cout << "       shudu.exe -s path_of_file" << std::endl;
    }

    return 0;
}