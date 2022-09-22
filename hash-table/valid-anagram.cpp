/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/valid-anagram
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。

 

示例 1:

输入: s = "anagram", t = "nagaram"
输出: true
示例 2:

输入: s = "rat", t = "car"
输出: false
 
提示:

1 <= s.length, t.length <= 5 * 104
s 和 t 仅包含小写字母
 
进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
*/

#include<iostream>
#include<string>

using namespace std;

bool is_valid_anagram(string& a ,string& b)
{
    //哈希映射，将字符映射为0-25的数组，以便对字符的个数进行统计
    //否则要用map，字符作为key处理起来不方便，也要用到更复杂的数据结构
    int char_count[26] = {0};
    for(int i = 0; i < a.size(); i++)
    {
        char_count[a[i]-'a']++;
    }

    for(int i = 0; i < b.size(); i++)
    {
        char_count[b[i]-'a']--;
    }

    for(int n = 0; n < 26; n++)
    {
        if(char_count[n] != 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    //char c = 'f';
    //cout << c << endl;
    string a = "rat", b = "car";

    bool valid_anagram = is_valid_anagram(a, b);
    cout << valid_anagram << endl;
    return 0;

}
