/*
https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/

给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

 

示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
 

提示：

1 <= prices.length <= 10^5
0 <= prices[i] <= 10^4

*/

//思路：
//思路1：暴力解法profit[i][j];j>i最大值
//思路2：求最小值，然后获取最大利润，要考虑开始时到最小值这段时间的情况
//https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/solutions/136684/121-mai-mai-gu-piao-de-zui-jia-shi-ji-by-leetcode-/
//思路3：动态规划
//第i天的最大收益只需要知道前i天的最低点就可以算出来了。
//而第i天以前（包括第i天）的最低点和i-1天的最低点有关，至此我们的动态方程就出来了。
//dp[i] = min(dp[i-1],prices[i])
//其中dp[0]=prices[0],然后动态计算之后的就可以了。
//dp[i]表示截止到i，价格的最低点是多少   dp[i]=min(dp[i-1],nums[i])
/*
int max = 0;
dp[i] = (dp[i - 1] < prices[i]) ? dp[i - 1] : prices[i];
max = (prices[i] - dp[i]) > max ? prices[i] - dp[i] : max;
*/