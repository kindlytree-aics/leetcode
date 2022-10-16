/*

https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/

给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。

 

示例 1：

输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
     总利润为 4 + 3 = 7 。
示例 2：

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     总利润为 4 。
示例 3：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。
 

提示：

1 <= prices.length <= 3 * 104
0 <= prices[i] <= 104
*/

//首先高点只能卖出不能买入
//然后有先后顺序，先买入再卖出
//递增时持有，下降时抛出，下降到最低点反弹时再买入
//注意最后如果一直在递增时也有加上最后点抛出时的利润
#include <vector>

enum broke_status {unknown=-2, decreasing=-1, increasing};

int maxProfit(std::vector<int>& prices) {
    int buy_idx = 0, sold_idx = 0, i=1;
    int profit = 0;
    broke_status status_ = broke_status::unknown ;
    while(i < prices.size())
    {   
        if(prices[i]-prices[i-1] > 0)
        {
            if(status_ == broke_status::increasing)
            {
                status_ = broke_status::increasing;
            }else if(status_ == broke_status::unknown)
            {
                status_ = broke_status::increasing;
                buy_idx = i-1;
            }else if(status_ == broke_status::decreasing)
            {
                status_ = broke_status::increasing;
                buy_idx = i-1;
            }
        }else if(prices[i]-prices[i-1] < 0)
        {
            if(status_ == broke_status::increasing)
            {
                sold_idx = i-1;
                profit += (prices[sold_idx] - prices[buy_idx]);
                status_ = broke_status::decreasing;
            }else if(status_ == broke_status::unknown)
            {
                status_ = decreasing;
            }else if(status_ == broke_status::decreasing)
            {
                status_ = broke_status::decreasing;
            }
        }
        i++;
    }
    if(status_ == broke_status::increasing)
    {
        profit += (prices.back() - prices[buy_idx]);
    }
    return profit;
}


int main()
{
    std::vector<int>prices = {7,1,5,3,6,4};
    //std::vector<int>prices = {1,2,3,4,5};
    int max_profit = maxProfit(prices);
    return 0;
}