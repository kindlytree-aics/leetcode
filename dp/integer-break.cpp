/*
题目来源：https://leetcode.cn/problems/integer-break/

给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2 ），并使这些整数的乘积最大化。

返回 你可以获得的最大乘积 。

 

示例 1:

输入: n = 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。
示例 2:

输入: n = 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
 

提示:

2 <= n <= 58

*/

//官方解答：https://leetcode.cn/problems/integer-break/solutions/352875/zheng-shu-chai-fen-by-leetcode-solution/
//方法，动态规划dp[i]=max(j*(i-j), j*dp[i-j])(1<=j<=i-1)，其中d[i]表示将i分拆成k(k>=2)个正正数后最大的乘积;
//d[2]=[1,1]=1,dp[3]=max([1,2],1*d[2])=2,dp[4]=max[max([1,3],1*dp[3], max([2,2],2*dp[2]))
//当为i时，可以将i拆分成j和i-j(i-j不继续分拆)，以及i-j继续分拆，这个时候可以记为dp[i-j]
//同时上述的j的范围可以从1到i-1

#include <vector>

int integerBreak(int n) {
    std::vector<int> dp(n+1, 1);
    if(n==2)return 1;
    for(int i = 3; i <= n; i++)
    {
        for(int j = 1; j<= i-1; j++)
        {
            int temp_max = std::max(j*(i-j),j*dp[i-j]);
            dp[i] = std::max(temp_max, dp[i]);
        }
    }
    return dp[n];
}

int main()
{
    int n = 10;
    int res = integerBreak(n);
    return 0;
}