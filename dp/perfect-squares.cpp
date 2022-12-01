/*

https://leetcode.cn/problems/perfect-squares/

给你一个整数n ，返回和为n的完全平方数的最少数量 。
完全平方数是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

示例 1：

输入：n = 12
输出：3 
解释：12 = 4 + 4 + 4
示例 2：

输入：n = 13
输出：2
解释：13 = 4 + 9
 
提示：
1 <= n <= 10^4
*/

//int target = sqrt(n)
//[1,4,9,...target^2]
//dp[n] = min(dp[n], dp[n-j]+1)

#include<vector>
#include<iostream>
#include<math.h>

//本题思路和coin-change一题类似。只是要讲相关内容进行转化，如完全平方数为1,4,9...sqrt(n)^2
int numSquares(int n) {
    int target = sqrt(n);
    std::vector<int>squares(target+1, 0);
    for(int i = 1; i <= target; i++)
    {
        squares[i] = i*i;
    }
    //都为1是有n个，初始化为比n还要大1的值
    std::vector<int>dp(n+1, n+1);
    dp[0] = 0;
    for(int i = 1; i <=n; i++)
    {
        for(int j = 1; j <= target; j++)
        {
            if(squares[j] <= i)
            {
                dp[i] = std::min(dp[i], dp[i-squares[j]]+1);
            }
        }
    }
    return dp[n] > n ? -1 : dp[n];
}


int main()
{
    int n = 3;
    int num = numSquares(n);
    std::cout<< num << std::endl;
}