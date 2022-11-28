/*

https://leetcode.cn/problems/coin-change-ii/solutions/143948/ling-qian-dui-huan-iihe-pa-lou-ti-wen-ti-dao-di-yo/

https://leetcode.cn/problems/coin-change-ii

给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。

请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。

假设每一种面额的硬币有无限个。 

题目数据保证结果符合 32 位带符号整数。

示例 1：

输入：amount = 5, coins = [1, 2, 5]
输出：4
解释：有四种方式可以凑成总金额：
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
示例 2：

输入：amount = 3, coins = [2]
输出：0
解释：只用面额 2 的硬币不能凑成总金额 3 。
示例 3：

输入：amount = 10, coins = [10] 
输出：1
 

提示：

1 <= coins.length <= 300
1 <= coins[i] <= 5000
coins 中的所有值 互不相同
0 <= amount <= 5000
*/

#include<vector>
#include<algorithm>
#include<iostream>

//coins为{1, 2, 5};amount=5时dp[1]={1}=1，dp[2]={{1,1},{2}}=2,dp[3]={{1,1,1},{1,2}}=2
//dp[i]={...},dp[i+1]=sum{dp[i+1-every_element_in_coins_lt(i+1)], element_eq(i+1)}-duplicate;

//递归程序，有重复的现象，需要考虑怎么除去；
void changeRecursive(int amount, int idx, std::vector<int>& coins, std::vector<int>set, std::vector<std::vector<int>>& results)
{
    if(idx < coins.size())
    {
        
        int amount_left = amount-coins[idx];
        if(amount_left > 0)
        {
            set.push_back(coins[idx]);
            changeRecursive(amount_left, idx, coins, set, results);
            changeRecursive(amount_left, idx+1, coins, set, results);
            set.pop_back();
            changeRecursive(amount, idx+1, coins, set, results);
        }
        else if(amount_left == 0)
        {
            set.push_back(coins[idx]);
            results.push_back(set);
            set.pop_back();
            return;
        }else{
            return;
        }
    }
}

//正确的 子问题 定义应该是，problem(k,i) = problem(k-1, i) + problem(k, i-k)
//即前 k 个硬币凑齐金额 i 的组合数 等于 前 k-1 个硬币凑齐金额 i 的组合数 加上 
//在原来 i-k 的基础上使用硬币的组合数。说的更加直白一点，那就是用前 k 的硬币凑齐金额 i ，
//要分为两种情况开率，一种是没有用第k个硬币，前 k-1 个硬币就凑齐了，一种是前面已经凑到了 i-k ，
//现在就差第 k 个硬币了
//TODO
int change(int amount, std::vector<int>& coins) {
    //int dp[amount]={0};
    std::vector<int> dp(amount+1, 0);
    dp[0]=1;
    std::sort(coins.begin(),coins.end());

}

int main()
{
    std::vector<int>coins = {1, 2, 5};
    int amount = 5;
    int result = change(amount ,coins);
    std::cout << result << std::endl;
}

