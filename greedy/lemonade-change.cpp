/*
https://leetcode.cn/problems/lemonade-change/

在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。

注意，一开始你手头没有任何零钱。

给你一个整数数组 bills ，其中 bills[i] 是第 i 位顾客付的账。如果你能给每位顾客正确找零，返回 true ，否则返回 false 。

 

示例 1：

输入：bills = [5,5,5,10,20]
输出：true
解释：
前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
由于所有客户都得到了正确的找零，所以我们输出 true。
示例 2：

输入：bills = [5,5,10,10,20]
输出：false
解释：
前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
由于不是每位顾客都得到了正确的找零，所以答案是 false。
 

提示：

1 <= bills.length <= 105
bills[i] 不是 5 就是 10 或是 20 

*/

#include<vector>

//具体思路，碰到5美元直接手下不找零，碰到10美元需要看一下前面是否还有5美元的零钱
//碰到20美元需要看看前面是否有三个5美元或者1个10美元加一个5美元，或者前面可以找的零钱10或5的总数是否大于15
//总体记录一下当前剩下5美元和10美元的个数；
bool lemonadeChange(std::vector<int>& bills) {
    std::vector<int> changes_five_dollar_left, changes_ten_dollar_left;//一开始为0
    for(int i = 0; i < bills.size(); i++)
    {
        int  current_pay_ = bills[i];
        if(current_pay_ == 5)
        {
           changes_five_dollar_left.push_back(current_pay_);
        }else if(current_pay_ == 10)
        {
            if(changes_five_dollar_left.size() > 0)
            {
                changes_five_dollar_left.pop_back();
                changes_ten_dollar_left.push_back(current_pay_);
            }else{
                return false;
            }
        }else if(current_pay_ == 20)
        {
            int changes = 15;
            if(changes_ten_dollar_left.size() > 0)
            {
                changes_ten_dollar_left.pop_back();
                changes -= 10;
            }
            if(changes / 5 > changes_five_dollar_left.size())return false;
            for(int i = 0; i < changes/5; i++)
            {
                changes_five_dollar_left.pop_back();
            }
        }
    }
    return true;
}


int main()
{
    std::vector<int>bills = {5,5,5,10,20};
    bool can_change = lemonadeChange(bills);
    return 0;
}