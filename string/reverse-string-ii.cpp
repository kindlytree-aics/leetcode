/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-string-ii
给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
 

示例 1：

输入：s = "abcdefg", k = 2
输出："bacdfeg"
示例 2：

输入：s = "abcd", k = 2
输出："bacd"
 

提示：

1 <= s.length <= 104
s 仅由小写英文组成
1 <= k <= 104
*/

#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;


void reverseSubString(string& s, int left, int right)
{
    char temp;
    while(left < right)
    {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}

string reverseStrv1(string s, int k) {
    int left = 0, right = k-1, ssize =s.size(), left_char_size=s.size();
    while(true)
    {
        if(left_char_size < k){
            //剩余字符全部翻转，left,right
            right = left + left_char_size-1;
            reverseSubString(s, left, right);
            break;
        }else if(left_char_size >= k && left_char_size < 2*k)
        {
            right = left +k-1;
            reverseSubString(s, left, right);
            break;
        }else{
            right = left +k-1;
            reverseSubString(s, left, right);
            left_char_size -= 2*k;
            left += 2*k; 
        }
    }
    return s;
}


string reverseStr(string s, int k) {
    for (int i = 0; i < s.size(); i += (2 * k)) {
        // 1. 每隔 2k 个字符的前 k 个字符进行反转
        // 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
        if (i + k <= s.size()) {
            reverse(s.begin() + i, s.begin() + i + k );
        } else {
            // 3. 剩余字符少于 k 个，则将剩余字符全部反转。
            reverse(s.begin() + i, s.end());
        }
    }
    return s;
}

int main()
{
    string s = "abcdefg";
    int k = 2;
    string reversed_s = reverseStr(s, k);
    cout << s << endl;
    cout << "reversed string :" << reversed_s << endl;
}