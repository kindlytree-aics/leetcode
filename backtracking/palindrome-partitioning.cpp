/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/palindrome-partitioning

给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

回文串 是正着读和反着读都一样的字符串。

 

示例 1：

输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
示例 2：

输入：s = "a"
输出：[["a"]]
 

提示：

1 <= s.length <= 16
s 仅由小写英文字母组成
*/

#include <vector>
#include <iostream>
#include<algorithm>

bool isPalindrome(std::string s)
{
    if(s.size() == 0)return false;
    int left = 0, right = s.size()-1;
    while(left <= right)
    {
        if(s[left] != s[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

void partitionv1(std::string& s, int start, std::string path, std::vector<std::string>partion,std::vector<std::vector<std::string>>&result)
{
    if(start < s.size()-1)
    {
        // if(path=="")
        // {
        //     std::string s_(s.begin()+start, s.begin()+start+1);
        //     partion.push_back(s_);
        //     path = s_;
        //     partitionv1(s, start+1, path, partion, result);
        //     //partion.pop_back();
        // }
        // else
        std::string s_(s.begin()+start, s.begin()+start+1); 
        path += s_;
        if(isPalindrome(path))
        {
            partion.push_back(path);
            partitionv1(s, start+1, "", partion, result);
            partion.pop_back();
        }
        partitionv1(s, start+1, path, partion, result);
        // std::string s_(s.begin()+start, s.begin()+start+1);
        // std::string path_ = path+s_;
        // partitionv1(s, start+1, path_, partion, result);
    }else{
        std::string s_(s.end()-1, s.end());
        path += s_;
        if(isPalindrome(path))
        {
            partion.push_back(path);
            result.push_back(partion);
        }
    }
}

std::vector<std::vector<std::string>> partition(std::string s) {
    std::vector<std::vector<std::string>> result;
    std::string path = "";
    std::vector<std::string>current_partition;
    partitionv1(s, 0, path, current_partition, result);
    return result;
}

int main()
{
    std::string s = "aab";
    std::vector<std::vector<std::string>> result = partition(s);
    return 0;
}
