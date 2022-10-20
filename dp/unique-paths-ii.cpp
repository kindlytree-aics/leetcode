/*
https://leetcode.cn/problems/unique-paths-ii/

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。

 

示例 1：


输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
输出：2
解释：3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右
示例 2：


输入：obstacleGrid = [[0,1],[0,0]]
输出：1
 

提示：

m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] 为 0 或 1

*/

#include<vector>
int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    std::vector<std::vector<int>>path(m, std::vector<int>(n, 0));
    if(m == 1 && n == 1 && obstacleGrid[0][0] == 0)return 1;
    for(int col=1; col < n; col++)
    {
        if(obstacleGrid[0][col] == 1)
        {
            break;
        }else{
            path[0][col] = 1;
        }
    }
    for(int row=1; row < m; row++)
    {
        if(obstacleGrid[row][0] == 1)
        {
            break;
        }else{
            path[row][0] = 1;
        }
    }
    for(int col = 1; col<n; col++)
    {
        for(int row = 1; row < m; row++)
        {
            if(obstacleGrid[row][col] == 1) 
            {
                path[row][col] = 0;
            }else if(path[row][col-1] == 0 && path[row-1][col] ==0)
            {
                path[row][col] = 0;
            }else{
                path[row][col] = path[row-1][col] + path[row][col-1];
            }
        }
    }
    return path[m-1][n-1];
}


int main()
{
    std::vector<std::vector<int>>obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    int path = uniquePathsWithObstacles(obstacleGrid);
    return 0;
}