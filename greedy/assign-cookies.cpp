/*
题目来源： https://leetcode.cn/problems/assign-cookies/
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

 
示例 1:

输入: g = [1,2,3], s = [1,1]
输出: 1
解释: 
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。
示例 2:

输入: g = [1,2], s = [1,2,3]
输出: 2
解释: 
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.
 

提示：

1 <= g.length <= 3 * 10e4
0 <= s.length <= 3 * 10e4
1 <= g[i], s[j] <= 2^31 - 1
*/

#include <vector>
#include <iostream>
#include <algorithm>

//s和g数组都先进行升序排序
//然后s和g分别进行匹配，如果当前匹配成功，说明可以进行匹配，将饼发给孩子
//否则如果不能匹配，孩子的需求g比饼的量s要大，则当前的饼不能够给当前的孩子
//这是个理想情况，不用考虑饼子进行划分组合等比较复杂的情形，直接用贪心算法求解即可。
int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
    std::sort(s.begin(), s.end());
    std::sort(g.begin(), g.end());
    int gsize = g.size(), ssize = s.size();
    int  g_idx = 0, s_idx= 0;
    int count = 0;
    while(s_idx < ssize && g_idx < gsize)
    {
        while(s_idx < ssize && s[s_idx] < g[g_idx])s_idx++;
        if(s_idx < ssize)
        {
            count++;
            s_idx++;
            g_idx++;
        }
    }
    return count;
}


int main()
{
    // std::vector<int>g = {1,2,3}, s = {1,1};
    std::vector<int>g = {1,2}, s = {1,2,3};
    //std::vector<int>g = {10,9,8,7}, s = { 5,6,7,8};
    int res = findContentChildren(g, s);
    return 0;
}