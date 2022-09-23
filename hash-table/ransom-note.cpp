/*
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/ransom-note
给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。

如果可以，返回 true ；否则返回 false 。

magazine 中的每个字符只能在 ransomNote 中使用一次。

示例 1：

输入：ransomNote = "a", magazine = "b"
输出：false
示例 2：

输入：ransomNote = "aa", magazine = "ab"
输出：false
示例 3：

输入：ransomNote = "aa", magazine = "aab"
输出：true
 
提示：
1 <= ransomNote.length, magazine.length <= 105
ransomNote 和 magazine 由小写英文字母组成
*/
#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;

bool canConstructv1(string ransomNote, string magazine) {
    std::unordered_map<char,int> mgz_char_count_map;
    for(char c: magazine){
        mgz_char_count_map[c]++;
    }
    for(char c:ransomNote)
    {
        mgz_char_count_map[c]--;
        if(mgz_char_count_map[c] < 0)
        {
            return false;
        }
    }
    return true;
}

//和上面的不同在于利用了为小写字符的信息，使用更加简单的hash方法
//对magazine字符串的每一个字符取其hash值为当前字符减去'a'，结果为0-25；
//可以定义一个26长度的整数数组，索引位置即为hash值，方便了存取，其对应的值为字符出现的个数
//当ransomNote中也同样依次遍历每一个字符，其对应的值减一，如果小于0，说明magazine中该字符的
//个数不足以取来组成randomNote，返回false;
bool canConstruct(string ransomNote, string magazine) {
    int mgz_char_count_map[26];
    for(char c: magazine){
        mgz_char_count_map[c-'a']++;
    }
    for(char c:ransomNote)
    {
        mgz_char_count_map[c-'a']--;
        if(mgz_char_count_map[c-'a'] < 0)
        {
            return false;
        }
    }
    return true;
}


int main()
{
    //string ransomNote = "aa", magazine = "aab";
    string ransomNote = "aa", magazine = "ab";
    bool can_constrcut = canConstruct(ransomNote, magazine);
    cout << can_constrcut << endl;
    return 0;
}