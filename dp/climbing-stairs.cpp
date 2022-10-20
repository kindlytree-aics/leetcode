/*

题目来源： https://leetcode.cn/problems/climbing-stairs/

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

 

示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：

输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶
 

提示：

1 <= n <= 45

*/
#include<vector>


//方法一：递归解法，有可能会超过时间限制，比如当n较大时，如n=35，递归深度比较深;
void climbStairsRecursive(int n, int height, std::vector<int>path, std::vector<std::vector<int>>&climb_methods)
{
    if(height > n)
    {
        return;
    }
    else if(height == n)
    {
        climb_methods.push_back(path);
    }else
    {
        for(int i = 1; i <=2; i++)
        {
            path.push_back(i);
            climbStairsRecursive(n, height+i, path, climb_methods);
            path.pop_back();
        }
    }
}

//方法二：动态规划解法；记录
//有两种方式走到n，而且肯定会不相同
//1、走到n-1，再走一步到达n
//2、走到n-2直接两步到n，不经过n-1
//因此解法是dp[n]=dp[n-1]+dp[n-2]
//dp[0]=0,dp[1]=1,dp[2]=2；dp[3] =dp[2]+dp[1]
int climbStairs(int n) {
    // std::vector<std::vector<int>>climb_methods;
    // std::vector<int>path;
    // climbStairsRecursive(n, 0, path, climb_methods);
    // return climb_methods.size();
    if(n==1)return 1;
    if(n==2)return 2;
    std::vector<int>dp(n+1,0);
    dp[0]=0,dp[1]=1,dp[2]=2;
    for(int i=3; i <= n; i++)
    {
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}

int main()
{
    int n = 9;
    int methods = climbStairs(3);
    return 0;
}