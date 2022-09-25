/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-words-in-a-string

给你一个字符串 s ，请你反转字符串中 单词 的顺序。

单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。

返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。

注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

示例 1：

输入：s = "the sky is blue"
输出："blue is sky the"
示例 2：

输入：s = "  hello world  "
输出："world hello"
解释：反转后的字符串中不能存在前导空格和尾随空格。
示例 3：

输入：s = "a good   example"
输出："example good a"
解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
 

提示：

1 <= s.length <= 104
s 包含英文大小写字母、数字和空格 ' '
s 中 至少存在一个 单词

进阶：如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用 O(1) 额外空间复杂度的 原地 解法。
*/

#include<vector>
#include<iostream>

using namespace std;

//输入：s = "the sky is blue"
//输出："blue is sky the"

//首先将字符窜中多余的空格过滤
//开头的，中间多余1个的，及结尾的多余空格
string remove_extra_spaces(string s)
{
    int left = 0, pos = 0;
    //trimleft
    while(s[left] == ' ')
    {
        left++;
    }
    for(int i = left; i < s.size(); i++)
    {   //在字符串里边，如果遇到第一个空格
        //将该空格写到字符串里边，同时检测后面是不是还是空格
        //如果是，则跳过后面的连续空格；
        if(s[i] == ' ')
        {
            s[pos] = s[i];
            pos++;
            while(s[i+1] == ' '){i++;};
        }else{
            s[pos] = s[i];
            pos++;
        }
    }
    //如果最后一个位置是空格，则仍会写到s里边，pos需要减一
    if(pos-1 > 0 && s[pos-1] == ' ')
    {
        s.resize(pos-1);
    }else
    {
        s.resize(pos);
    }
    return s;
}


string reverseWords(string s)
{
    s = remove_extra_spaces(s);
    int nsize = s.size();
    string s_new(nsize, ' ');
    int current_word_left = 0, current_word_rihgt =0, place_pos = nsize-1, end= nsize-1;
    for(int i = current_word_left; i < nsize; i++)
    {
        char c = s[i];
        //如果c不为空格，则当前word继续右边移动;
        if(c != ' '){
            current_word_rihgt++;
        }else{
            //否则right为当前word的最后一个字符位置
            int right = current_word_rihgt;
            //将当前word放到对应的位置上，从最后一个字符开始放起
            for(int k = 0; k < current_word_rihgt-current_word_left; k++)
            {
                s_new[place_pos] = s[right-1];
                right--;
                place_pos--;
            }
            //空格还要加上
            s_new[place_pos--] = ' ';
            //下一个word的起始位置和终止位置初始化
            current_word_left = ++current_word_rihgt;
            current_word_rihgt = current_word_left;
        }
        //遍历到最后一个字符位置，将最后一个word继续放入到s字符串对应的位置
        if(i == nsize-1)
        {
            int right = current_word_rihgt;
            for(int k = 0; k < current_word_rihgt-current_word_left; k++)
            {
                s_new[place_pos] = s[right-1];
                right--;
                place_pos--;
            }
        }
    }
    return s_new;
}

int main()
{
    string s = "the sky is blue";
    string reversed_words_str = reverseWords(s);
    cout << reversed_words_str << endl;
}