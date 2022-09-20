
/*
给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
示例 1：

输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
示例 2：

输入：n = 1
输出：[[1]]
 
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/spiral-matrix-ii
*/  


#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> generateMatrix(int n)
{
    int circle_num = int((n+1)/2);
    int start = 1;
    vector<vector<int>>spiral_matrix(n, vector<int>(n, 0));
    //螺旋矩阵的绘制可以看作一圈一圈进行绘制
    //圈的数目为(n+1)/2;
    for(int circle_idx =0; circle_idx < circle_num; circle_idx++)
    {
        //圈顺时针进行绘制，上右下左顺序进行
        //top;right,bottom,left;
        for(int row=circle_idx, col=circle_idx; col < n-circle_idx; col++)
        {
            spiral_matrix[row][col] = start++;
        }
        //right;
        for(int col=n-circle_idx-1, row=circle_idx+1; row < n-circle_idx; row++)
        {
            spiral_matrix[row][col] = start++;
        }
        //bottom
        for(int row=n-circle_idx-1, col=n-circle_idx-2;  col >= circle_idx; col--)
        {
            spiral_matrix[row][col] = start++;
        }
        //left;
        for(int col = circle_idx, row=n-circle_idx-2; row >circle_idx; row--)
        {
            spiral_matrix[row][col] = start++;
        }
    }
    return spiral_matrix;
}
int main(){
    //vector<int>nums = {2,3,1,2,4,3};
    //int target = 7;
    //vector<int>nums = {1,1,1,1,1,1,1,1};
    //int target = 11;
    // vector<int>nums = {1,2,3,4,5};
    // int target = 11;
    //vector<int>nums ={2,3,1,2,4,3};
    int n = 3;    
    vector<vector<int>>spiral_matrix = generateMatrix(n);
    for (int a = 0; a < n; a++)
    {
        for (int b = 0; b < n; b++)
        {
            cout << spiral_matrix[a][b] << " ";
        }
        cout << endl;
    } 
    //cout << len << endl;
}
