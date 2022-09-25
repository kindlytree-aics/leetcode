/*

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/ti-huan-kong-ge-lcof

请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

 

示例 1：

输入：s = "We are happy."
输出："We%20are%20happy."
 

限制：

0 <= s 的长度 <= 10000
*/

#include<vector>
#include<iostream>

using namespace std;


string replaceSpace(string s) {
    int space_count = 0, ori_size = s.size();
    for(char c : s){
        if(c == ' '){
            space_count++;
        }
    }
    //string s_new(s.size()+2*space_count, ' ');
    s.resize(s.size() + space_count * 2);
    for(int i = s.size()-1, j = ori_size-1; i>=0, j>=0; i--,j--)
    {
        if(s[j] != ' '){
            s[i] = s[j];
        }else{
            s[i--] = '0';
            s[i--] = '2';
            s[i] = '%';
        }
    }
    return s;
}