/*
题目来源：https://leetcode.cn/problems/n-queens/

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

 

示例 1：


输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
示例 2：

输入：n = 1
输出：[["Q"]]

提示：

1 <= n <= 9
*/
#include <vector>
#include <iostream>

std::vector<bool> getCandidatePos(int n, std::vector<int>path)
{
    //std::vector<int>candidate_pos_;
    std::vector<bool>valid_pos_(n, true);
    for(int i = 0; i < path.size(); i++)
    {
        int his_row = i, his_col =path[i];
        int row_delta = path.size()-his_row;
        valid_pos_[his_col] = false;
        if(his_col -row_delta >= 0)
        {
            valid_pos_[his_col-row_delta] = false;
        }
        if(his_col + row_delta < n)
        {
            valid_pos_[his_col+row_delta] = false;
        }
    }
    return valid_pos_;
}

void solveNQueensv1(int n, std::vector<int>path, std::vector<std::vector<int>>&valid_results)
{
    if(path.size() == n)
    {
        valid_results.push_back(path);
        return;
    }
    std::vector<bool>valid_pos_ = getCandidatePos(n, path);
    //bool has_valid_pos = false;
    for(int i = 0; i < valid_pos_.size(); i++)
    {
        if(valid_pos_[i] == true)
        {
            //has_valid_pos = true;
            path.push_back(i);
            solveNQueensv1(n, path, valid_results);
            path.pop_back();
        }
    }
    // if(has_valid_pos == false)
    // {
    //     return false;
    // }
}

std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<int>>valid_results;
    std::vector<int>path;
    std::vector<std::vector<std::string>> results;
    solveNQueensv1(n, path, valid_results);
    for(int i =0; i < valid_results.size(); i++)
    {
        std::vector<std::string>cur_solution_;
        for(int j = 0; j <n; j++)
        {
            //cur_solution_ += valid_results[i][j]
            std::string row_pos_;
            for(int m = 0; m < n; m++)
            {
                if(valid_results[i][j] == m)
                {
                    row_pos_ +="Q";
                }else{
                    row_pos_ +=".";
                }
            }
            cur_solution_.push_back(row_pos_);
        }
        results.push_back(cur_solution_);
    }
    return results;
}

int main()
{
    std::vector<std::vector<std::string>>results;
    int n = 4;
    results = solveNQueens(n);
    return 0;
}