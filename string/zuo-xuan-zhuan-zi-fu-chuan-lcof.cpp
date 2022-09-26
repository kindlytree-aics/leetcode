/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof
字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

示例 1：

输入: s = "abcdefg", k = 2
输出: "cdefgab"
示例 2：

输入: s = "lrloseumgh", k = 6
输出: "umghlrlose"
 

限制：

1 <= k < s.length <= 10000
*/


#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
//O(1)空间复杂度实现方法，但时间复杂度会比较高
//该方法比较原始笨拙，不建议参考
string reverseLeftWordsv1(string s, int n) {
     int nsize = s.size();
     while(nsize)
     {
        if(n <= nsize-n)
        {
            for(int i=0; i < n; i++)
            {
                char temp = s[i];
                s[i] = s[nsize-n+i];
                s[nsize-n+i] =temp;
            }
            nsize -=n;
        }else{
            for(int i=0; i < nsize-n; i++)
            {
                char temp = s[i];
                s[i] = s[n+i];
                s[n+i] =temp;
            }
            int temp = n;
            n = nsize-n;
            nsize = temp;        
        }
     }
     return s;
}

//具体步骤为：
//反转区间为前n的子串
//反转区间为n到末尾的子串
//反转整个字符串
string reverseLeftWords(string s, int n) 
{
    reverse(s.begin(), s.begin() + n);
    reverse(s.begin() + n, s.end());
    reverse(s.begin(), s.end());
    return s;
}

int main()
{
    string s = "abcdefg";
    int k = 2;
    string reversed_s = reverseLeftWords(s, k);
    cout << s << endl;
    cout << "reversed string :" << reversed_s << endl;
}
