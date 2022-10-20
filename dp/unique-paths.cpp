/*
题目来源： https://leetcode.cn/problems/unique-paths/

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

 

示例 1：


输入：m = 3, n = 7
输出：28
示例 2：

输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下
示例 3：

输入：m = 7, n = 3
输出：28
示例 4：

输入：m = 3, n = 3
输出：6
 

提示：

1 <= m, n <= 100
题目数据保证答案小于等于 2 * 10^9
*/

#include<vector>

//从(0,0)开始到达(m-1,n-1)只能向右或向下
//即当到达(s,t),则之前可能的路径为(s-1,t),(s,t-1)
//记录path[s][t]为到大s,t的路径
//则path[s][t] = path[s-1][t] + path[s][t-1];path[0][0]=0; 
//最终结果记为path[m-1][n-1]的值
int uniquePaths(int m, int n) {
    std::vector<std::vector<int>>path(m, std::vector<int>(n, 0));
    for(int row = 1; row < m; row++)
    {
        path[row][0] = 1; //第一行和第一列只有一种走法，即一直横着向右走或一直向下走
    }
    for(int col = 1; col < n; col++)
    {
        path[0][col] = 1;
    }
    for(int col = 1; col<n; col++)
    {
        for(int row = 1; row < m; row++)
        {
            path[row][col] = path[row][col-1] + path[row-1][col];
        }
    }
    return path[m-1][n-1];
}

int main()
{
    int m = 7, n = 3;
    int path  = uniquePaths(7,3);
    return 0;
}

    