/*
题目来源： https://leetcode.cn/problems/letter-combinations-of-a-phone-number/

17. 电话号码的字母组合
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如本目录图片所示（与电话按键相同）。注意 1 不对应任何字母。

示例 1：

输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：

输入：digits = ""
输出：[]
示例 3：

输入：digits = "2"
输出：["a","b","c"]
 

提示：

0 <= digits.length <= 4
digits[i] 是范围 ['2', '9'] 的一个数字。
*/

#include <vector>
#include <iostream>
#include <queue>


void letterCombinationsv1(string& digits, int idx, string& s, std::string path, std::vector<std::string>&res) {
    if(idx == digits.size()-1)
    {
        std::string  idx_candiates = s(s.end()-4, s.end());
        for(int j = 0; j < idx_candiates.size(); j++)
        {
            path.push_back(idx_candiates[j]);
            //letterCombinations(digits, idx+1, s, path);
            res.push_back(path)
            path.pop_back();
        }
        res.push_back(path);
    }
    else{
        //int idx = digits[i]- 49-1;
        std::string  idx_candiates = s(s.begin()+idx*3, s.begin()+(idx+1)*3);
        for(int j = 0; j < idx_candiates.size(); j++)
        {
            path.push_back(idx_candiates[j]);
            letterCombinationsv1(digits, idx+1, s, path, res);
            path.pop_back();
        }
    }
}

std::vector<std::string> letterCombinations(string digits) {
    std::vector<std::string> res;
    std::string s="abcdefghijklmnopqrstuvwxyz";
    std::string path="";
    letterCombinationsv1(digits, 0, s, path, res);
    return res;
}

int main()
{
     
     std::string digits = "23";
     std::vector<std::string> res = letterCombinations(digits);


}