/*

https://leetcode.cn/problems/coin-change/

给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
你可以认为每种硬币的数量是无限的。

示例 1：

输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1
示例 2：

输入：coins = [2], amount = 3
输出：-1
示例 3：

输入：coins = [1], amount = 0
输出：0
 

提示：

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
*/


//我们采用自下而上的方式进行思考。仍定义 F(i)
//F(i)为组成金额i所需最少的硬币数量，
//假设在计算 F(i)之前，我们已经计算出F(0)−F(i−1)的答案。
//则 F(i)对应的转移方程应为F(i) = min(F(i-coin[j])+1)，其中j满足i-coin[j] >=0

#include<vector>

int coinChange(std::vector<int>& coins, int amount) {
    int max = amount + 1;
    std::vector<int> dp(amount + 1, amount);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for(int j = 0; j < coins.size(); ++j) {
            if (coins[j] <= i) {
                dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    } 
    return dp[amount] > amount ? -1 : dp[amount];
}

