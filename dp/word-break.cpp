/*
https://leetcode.cn/problems/word-break/

给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

示例 1：

输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
示例 2：

输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
     注意，你可以重复使用字典中的单词。
示例 3：

输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false
 

提示：

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s 和 wordDict[i] 仅有小写英文字母组成
wordDict 中的所有字符串 互不相同
*/
#include<vector>
#include<string>
#include<iostream>

//dp[i] = dp[i-s]+s
//第一步对于每个单词，查看其是否s开头的那个单词的可能性，是的话dp[len_of_word]=true
bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    int size = s.size();
    std::vector<bool>dp(size+1, false);
    dp[0] = true;
    for(int j = 0; j < size; j++)
    {
        if(dp[j] == true)
        {
            for(int i = 0 ; i < wordDict.size(); i++)
            {
                std::string word = wordDict[i];
                std::string prob = s.substr(j,word.size());
                if(prob == word)
                {
                    int k = j+word.size();
                    dp[k] = true;
                    if(k == size)
                    {
                        return true;
                    }
                }
            }
        }
        dp[j] = false;
    }
    return false;
}

int main()
{
    std::string s = "leetcode";
    std::vector<std::string>wordDict = {"leet","code"};
    bool canconcat = wordBreak(s, wordDict);
    std::cout << canconcat << std::endl;
}
