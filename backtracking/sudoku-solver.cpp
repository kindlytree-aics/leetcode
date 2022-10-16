/*
题目来源： https://leetcode.cn/problems/sudoku-solver/

编写一个程序，通过填充空格来解决数独问题。

数独的解法需 遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
数独部分空格内已填入了数字，空白格用 '.' 表示。

示例 1：


输入：board = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}}
输出：{{'5','3','4','6','7','8','9','1','2'},{'6','7','2','1','9','5','3','4','8'},{'1','9','8','3','4','2','5','6','7'},{'8','5','9','7','6','1','4','2','3'},{'4','2','6','8','5','3','7','9','1'},{'7','1','3','9','2','4','8','5','6'},{'9','6','1','5','3','7','2','8','4'},{'2','8','7','4','1','9','6','3','5'},{'3','4','5','2','8','6','1','7','9'}}
解释：输入的数独如上图所示，唯一有效的解决方案如下所示：


 

提示：

board.length == 9
board{i}.length == 9
board{i}{j} 是一位数字或者 '.'
题目数据 保证 输入数独仅有一个解
*/

//“字符"1"的ASCII值是49。

#include <vector>


std::vector<char> getCandidateChars(int i, int j, std::vector<std::vector<char>>& board)
{
    std::vector<char>chars={'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::vector<bool>row_candidates_(board.size(),true);
    std::vector<bool>col_candidates_(board.size(),true);
    std::vector<bool>block_candidates_(board.size(),true);
    std::vector<char>candidate_chars;
    for(int m = 0; m < board.size(); m++)
    {
        if(board[i][m] != '.')
        {
            row_candidates_[board[i][m]-49] = false;
        }
    }

    for(int m = 0; m < board.size(); m++)
    {
        if(board[m][j] != '.')
        {
            col_candidates_[board[m][j]-49] = false;
        }
    }

    for(int s = i/3*3; s < i/3*3+3; s++)
    {
        for(int t = j/3*3; t < j/3*3+3; t++)
        {
            if(board[s][t] != '.')
            {
                block_candidates_[board[s][t]-49] = false;
            }            
        }
    }

    for(int a = 0; a < board.size(); a++)
    {
        if(row_candidates_[a] && col_candidates_[a] && block_candidates_[a])
        {
            candidate_chars.push_back(a+49);
        }
    }
    return candidate_chars;
}


bool solveSudoku(std::vector<std::vector<char>>& board) {
    bool solved = true;
    for(int i = 0; i < board.size(); i++)
    {
        for(int j =0; j < board.size(); j++)
        {
            if(board[i][j] == '.')
            {
                solved = false;
                std::vector<char> chars = getCandidateChars(i, j, board);
                if(chars.size() == 0){return false;}
                for(auto c : chars)
                {
                    board[i][j] = c;
                    if(solveSudoku(board))return true;
                    board[i][j] = '.';
                }
            }
            if(board[i][j] == '.')
            {
                return false;
            }
        }
    }
    return solved;
}

int main()
{
    std::vector<std::vector<char>> board = {{'5','3','.','.','7','.','.','.','.'},\
                                            {'6','.','.','1','9','5','.','.','.'},\
                                            {'.','9','8','.','.','.','.','6','.'},\
                                            {'8','.','.','.','6','.','.','.','3'},\
                                            {'4','.','.','8','.','3','.','.','1'},\
                                            {'7','.','.','.','2','.','.','.','6'},\
                                            {'.','6','.','.','.','.','2','8','.'},\
                                            {'.','.','.','4','1','9','.','.','5'},\
                                            {'.','.','.','.','8','.','.','7','9'}};
    solveSudoku(board);
    return 0;
}


