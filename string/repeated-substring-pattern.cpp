/*
给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。

 

示例 1:

输入: s = "abab"
输出: true
解释: 可由子串 "ab" 重复两次构成。
示例 2:

输入: s = "aba"
输出: false
示例 3:

输入: s = "abcabcabcabc"
输出: true
解释: 可由子串 "abc" 重复四次构成。 (或子串 "abcabc" 重复两次构成。)
 

提示：

1 <= s.length <= 104
s 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/repeated-substring-pattern
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/

//假设字符串s使用多个重复子串构成（这个子串是最小重复单位），
//重复出现的子字符串长度是x，所以s是由n * x组成。
//因为字符串s的最长相同前后缀的的长度一定是不包含s本身，
//所以 最长相同前后缀长度必然是m * x，而且 n - m = 1
//所以如果 nx % (n - m)x = 0，就可以判定有重复出现的子字符串。
//https://programmercarl.com/0459.%E9%87%8D%E5%A4%8D%E7%9A%84%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2.html#kmp

#include<vector>
#include<iostream>
#include<algorithm>

std::vector<int> getNext(std::string s)
{
    //如果next[0], next[1], ... next[i-1]均已知，那么如何求出 next[i] ？
    //第一种情况：A[temp]等于A[i]，也就是说在前一个next结果上又多了一个字符串相同的长度，因此next[i]为next[i-1]+1
    //当A[temp]和A[i]不相等的时候，我们需要缩小temp,把temp变成next[temp-1]，直到A[temp]=A[i]为止。A[now]=A[i]时，就可以直接向右扩展了。
    //temp记录当前的匹配位置，i从1开始，temp从0开始
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
            temp = next[temp-1];
        }else{
            //temp为0，从字符串开头开始匹配
            next[i] = 0;
            i++;
        }
    }
    return next;
}

int main()
{
    std::string repeated_str = "asdfasdfasdf";
    std::vector<int> next = getNext(repeated_str);
    int ssize = repeated_str.size();
    int longest_common_prefix_postfix = next[ssize-1];
    int repeated_len = ssize - (longest_common_prefix_postfix+1);
    bool has_repeated_str = false;
    if(longest_common_prefix_postfix != -1 && ssize % repeated_len == 0)
    {
        has_repeated_str =  true;
    }
    std::cout << "has repeated str:" << has_repeated_str << std::endl;
}

