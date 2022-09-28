/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。

示例 1：

输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
示例 2：

输入：haystack = "leetcode", needle = "leeto"
输出：-1
解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。

提示：
1 <= haystack.length, needle.length <= 104
haystack 和 needle 仅由小写英文字符组成
*/

//KMP 算法（Knuth-Morris-Pratt 算法）是一个著名的字符串匹配算法，效率很高，但是确实有点复杂。
//KMP 算法永不回退 txt 的指针 i，不走回头路（不会重复扫描 txt），
//而是借助 dp 数组中储存的信息把 pat 移到正确的位置继续匹配，时间复杂度只需 O(N)，
//用空间换时间，所以我认为它是一种动态规划算法。
//https://zhuanlan.zhihu.com/p/83334559 用dp算法思想解决状态机的问题
//https://zhuanlan.zhihu.com/p/145536254 next数组实质上就是找出模式串中前后字符重复出现的个数
//前缀表里，统计了各个位置为终点字符串的最长相同前后缀的长度。
#include<vector>
#include<iostream>
#include<algorithm>


std::vector<int> getNext(std::string s)
{
    //如果next[0], next[1], ... next[i-1]均已知，那么如何求出 next[i] ？
    //第一种情况：A[temp]等于A[i]，也就是说在前一个next结果上又多了一个字符串相同的长度，因此next[i]为next[i-1]+1
    //当A[temp]和A[i]不相等的时候，我们需要缩小temp,把temp变成next[temp-1]，直到A[temp]=A[i]为止。A[now]=A[i]时，就可以直接向右扩展了。
    //temp记录当前的匹配位置，i从1开始，temp从0开始
    //next里记录了最长相同前后缀的长度
    std::vector<int> next(s.size(), 0);
    int i = 1, temp = 0;
    while(i < s.size())
    {
        //当前字符和temp位置字符匹配，next[i]值直接加一，i和temp同时滑动
        if(s[temp] == s[i]){
            temp++;
            next[i] = temp;
            i++;
        }else if(temp > 0){
            //不等时，需要找到当前的temp-1的串的最长最前最后子串，并返回改串长度值
            //并开始下一次和s[i]的比较（此时s[i]中的i）不动
            temp = next[temp-1];
        }else{
            //temp为0，从字符串开头开始匹配
            next[i] = 0;
            i++;
        }
    }
    return next;
}

int KMP(std::string haystack, std::string needle) {
    std::vector<int>next = getNext(needle);
    int i = 0, j = 0;
    while(i < haystack.size())
    {
        if(haystack[i] == needle[j])
        {
            j++;
            i++;
            if(j == needle.size()){
                return i-needle.size();
            }
        }else{
            if(j > 0)
            {
                j = next[j-1];
            }else{
                i++;
            } 
        }
    }
    return -1;
}

int main()
{
    std::string haystack = "mississippi";
    std::string needle = "issip";
    int index = KMP(haystack, needle);
    std::cout << index << std::endl;
    std::cout << "the index of substring:" << index << std::endl;
}
