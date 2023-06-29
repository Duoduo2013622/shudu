/*****************************************************************************
*  xxx xxx  Co., Ltd                                                         *
*  Copyright (C) 2014 xxx xxx                                                * 
*  This program implements a Sudoku program. You can use it to generate      *
*  Sudoku endings to files, and read Sudoku from files and solve puzzles. In *
*  this program, we have used backtracking algorithm to solve sudoku problem.*                                       *
*                                                                            *
*  @file     shudu.cpp                                                       *
*  @brief    数独                                                            *
*  Details.                                                                  *
*                                                                            *
*  @author   jlx lxk                                                         *
*  @email    jlx0626sammi@163.com                                            *
*  @version  1.0.0.1(版本号)                                                  *
*  @date     2023-06-27                                                      *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*   Date      |   Version | Author      | Description                        *
*----------------------------------------------------------------------------*
*  2023/06/27 | 1.0.0.1   | lxk jlx      | Create file                       *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

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

// 生成数独终局
void generateSudoku(int numPuzzles) {
    std::ofstream file("sudoku_finals.txt");

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

// 生成指定数量的数独游戏，并将结果保存到文件中
void generateSudokuGames(int numPuzzles, int numBlank) 
{
    std::ofstream file("sudoku_puzzles.txt");

    std::vector<int> nums(BOARD_SIZE);
    std::iota(nums.begin(), nums.end(), 1);

    std::random_device rd;
    std::mt19937 generator(rd());

    for (int i = 0; i < numPuzzles; i++) 
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

        std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            board[0][j] = nums[j];
        }

        solveSudoku(board);

        // 挖空
        for (int i = 0; i < numBlank; i++)
        {
            while(1)
            {
                int r = (rand() % 9);
                int c = (rand() % 9);
                if (board[r][c] != 0)
                {
                    board[r][c] = 0;
                    break;
                }
            }
        }

        for (int row = 0; row < BOARD_SIZE; row++) 
        {
            for (int col = 0; col < BOARD_SIZE; col++) 
            {
                if (board[row][col]==0) {
                    file << "$ ";
                    continue;
                }
                file << board[row][col] << " ";
            }
            file << std::endl;
        }
        file << std::endl;
    }

    file.close();
}

// 生成指定数量的数独游戏，设置挖空范围，并将结果保存到文件中
void generateSudokuGames_r(int numPuzzles, int a ,int b) 
{
    std::ofstream file("sudoku_puzzles.txt");

    std::vector<int> nums(BOARD_SIZE);
    std::iota(nums.begin(), nums.end(), 1);

    std::random_device rd;
    std::mt19937 generator(rd());

    for (int i = 0; i < numPuzzles; i++) 
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

        std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            board[0][j] = nums[j];
        }

        solveSudoku(board);

        // 挖空
        int numBlank = (rand() % (b-a+1))+ a;
        file << "numBlank = " << numBlank << std::endl;
        for (int i = 0; i < numBlank; i++)
        {
            while(1)
            {
                int r = (rand() % 9);
                int c = (rand() % 9);
                if (board[r][c] != 0)
                {
                    board[r][c] = 0;
                    break;
                }
            }
        }

        for (int row = 0; row < BOARD_SIZE; row++) 
        {
            for (int col = 0; col < BOARD_SIZE; col++) 
            {
                if (board[row][col]==0) {
                    file << "$ ";
                    continue;
                }
                file << board[row][col] << " ";
            }
            file << std::endl;
        }
        file << std::endl;
    }

    file.close();
}

// 生成指定数量的数独游戏，设置挖空范围，并将结果保存到文件中
void generateSudokuGames_u(int numPuzzles) 
{
    std::ofstream file("sudoku_puzzles.txt");

    std::vector<int> nums(BOARD_SIZE);
    std::iota(nums.begin(), nums.end(), 1);

    std::random_device rd;
    std::mt19937 generator(rd());

    for (int i = 0; i < numPuzzles; i++) 
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

        std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            board[0][j] = nums[j];
        }

        solveSudoku(board);

        // 默认挖空30个

        int numBlank = 30;
        for (int i = 0; i < numBlank; i++)
        {
            while(1)
            {
                int r = (rand() % 9);
                int c = (rand() % 9);
                if (board[r][c] != 0)
                {
                    board[r][c] = 0;
                    break;
                }
            }
        }

        //判断是否唯一解
        std::vector<std::pair<int, int>> empty_cells;
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) {
                    empty_cells.push_back(std::make_pair(row, col));
                }
            }
        }
    
    
        for (int i = 0; i < empty_cells.size(); i++) {
            int row = empty_cells[i].first;
            int col = empty_cells[i].second;
            int prev_num = board[row][col];
            board[row][col] = 0;
        
            std::vector<std::vector<int>> temp_board = board;
            solveSudoku(temp_board);
        
            bool unique_solution = true;
            if (solveSudoku(temp_board)) {
                unique_solution = false;
            }
        
            if (!unique_solution) {
                board[row][col] = prev_num;
            }
        }

        for (int row = 0; row < BOARD_SIZE; row++) 
        {
            for (int col = 0; col < BOARD_SIZE; col++) 
            {
                if (board[row][col]==0) {
                    file << "$ ";
                    continue;
                }
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

    std::ofstream file2("sudoku_solved.txt");

    std::string line;
    std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

    int row = 0;

    while (std::getline(file, line)) {
        if (line.empty()) {
            row=0;
            continue;
        }

        char* token = strtok(const_cast<char*>(line.c_str()), " ");
        while (token != nullptr) {
            if ( *token == '$'){
                *token = '0';
            }
            board[row / BOARD_SIZE][row % BOARD_SIZE] = std::atoi(token);
            token = strtok(nullptr, " ");
            row++;
        }

        if (row == BOARD_SIZE * BOARD_SIZE) {
            solveSudoku(board);

            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; col++) {
                    file2 << board[row][col] << " ";
                }
                file2 << std::endl;
            }
            file2 << std::endl;

            board = std::vector<std::vector<int>>(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));
        }
    }

    file.close();
    file2.close();
}

int main(int argc, char* argv[]) {
    if (argc == 3 && strcmp(argv[1], "-c") == 0) 
    {
        int numFinals = std::atoi(argv[2]);
        if (numFinals<1 || numFinals>1000000){
            std::cout << "The number of finals can only be set in the range of 1-1000000." << std::endl;
            return 0;
        }
        generateSudoku(numFinals);
        std::cout << "Sudoku Finals generated successfully." << std::endl;
    } 
    else if (argc == 3 && strcmp(argv[1], "-s") == 0) 
    {
        solveSudokuFromFile(argv[2]);
        std::cout << "Sudoku games were successfully completed." << std::endl;
    } 
    else if (strcmp(argv[1], "-n") == 0)
    {
        int numPuzzles = std::stoi(argv[2]);
        if (numPuzzles<1 || numPuzzles>10000){
            std::cout << "The number of puzzles can only be set in the range of 1-10000." << std::endl;
            return 0;
        }
        //难度，挖空个数参数缺省  Difficulty Rating
        if(argc == 3)
        {
             generateSudokuGames(numPuzzles, 10); //默认挖空10个 难度等级为1
        }
        else
        {
            if(strcmp(argv[3], "-m") == 0)
            {
                int Level = std::stoi(argv[4])*10;
                if (Level<10 || Level>30){
                    std::cout << "The difficulty Rating can only be set in the range of 1-3." << std::endl;
                    return 0;
                }
                generateSudokuGames(numPuzzles, Level);
            }
            else if (strcmp(argv[3], "-r") == 0)
            {
                //Usage: shudu.exe -n 20 -r 20~55
                //解析出输入字符串的个数
	            int longer = strlen(argv[4]);
                
	            //printf("longer = %d !\n",longer);
	
	            //解析出字符串中的数字 -- 数组实现
                int a=0,b=0;
	            for(int i = 0 ; i < longer ; i++)
	            {
		            if((argv[4][i] >= '0')&&(argv[4][i] <= '9'))
		            {
			            b = b*10 + argv[4][i] - '0';
		            }
                    else if (argv[4][i] == '~'){
                        a = b;
                        b = 0;
                    }
	            }

                //int a = std::stoi(argv[4]);
                //int b = std::stoi(argv[5]);
                if (a>b || b>55 || a<20){
                    std::cout << "The number of blanks can only be set in the range of 20-55." << std::endl;
                    return 0;
                }
                generateSudokuGames_r(numPuzzles, a,b);
            }
            else if(strcmp(argv[3], "-u") == 0)
            {
                generateSudokuGames_u(numPuzzles);
            }    
        }
        std::cout << "Sudoku games generated successfully." << std::endl;
    }





    else 
    {
        std::cout << "Invalid command-line arguments." << std::endl;
        std::cout << "Usage: shudu.exe -c numPuzzles" << std::endl;
        std::cout << "       shudu.exe -s path_of_file" << std::endl;
    }

    return 0;
}