/*
题目来源：https://leetcode.cn/problems/min-cost-climbing-stairs/

给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。

你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。

请你计算并返回达到楼梯顶部的最低花费。

示例 1：

输入：cost = [10,15,20]
输出：15
解释：你将从下标为 1 的台阶开始。
- 支付 15 ，向上爬两个台阶，到达楼梯顶部。
总花费为 15 。
示例 2：

输入：cost = [1,100,1,1,1,100,1,1,100,1]
输出：6
解释：你将从下标为 0 的台阶开始。
- 支付 1 ，向上爬两个台阶，到达下标为 2 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 4 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 6 的台阶。
- 支付 1 ，向上爬一个台阶，到达下标为 7 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 9 的台阶。
- 支付 1 ，向上爬一个台阶，到达楼梯顶部。
总花费为 6 。
 

提示：

2 <= cost.length <= 1000
0 <= cost[i] <= 999
*/

//方法：动态规划
//具体实现：总cost记为total_cost,首先从第0或1步开始
//total_cost[1] = cost[0],total_cost[2] = min(cost[0],cost[1])
//total_cost[3] = min(total_cost[1]+cost[1], total_cost[2]+cost[2])
//total_cost[n] = min(total_cost[n-1]+cost[n-1], total_cost[n-2]+cost[n-2])

#include <vector>


int minCostClimbingStairs(std::vector<int>& cost) {
    int nsize = cost.size();
    std::vector<int>total_cost(nsize+1);
    total_cost[0]= 0;
    total_cost[1] = 0;//可以从0或1开始
    total_cost[2] = std::min(cost[0], cost[1]);
    for(int i = 3; i <= nsize; i++)
    {
        total_cost[i] = std::min(total_cost[i-1]+cost[i-1], total_cost[i-2]+cost[i-2]);
    }
    return total_cost[nsize];
}

int main()
{
    std::vector<int> cost = {10,15,20};
    int total_min_cost = minCostClimbingStairs(cost);
    return 0;
}