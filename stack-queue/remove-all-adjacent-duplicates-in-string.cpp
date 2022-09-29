/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string
给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。

在 S 上反复执行重复项删除操作，直到无法继续删除。

在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。

示例：

输入："abbaca"
输出："ca"
解释：
例如，在 "abbaca" 中，我们可以删除 "bb" 由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串 "aaca"，其中又只有 "aa" 可以执行重复项删除操作，所以最后的字符串为 "ca"。
 

提示：

1 <= S.length <= 20000
S 仅由小写英文字母组成。
*/

#include<string>
#include<iostream>
#include<stack>
#include<algorithm>

std::string removeDuplicates(std::string s) {
    std::stack<char> stack_;
    for(auto c: s){
        if(stack_.empty()){
            stack_.push(c);
        }else{
            char m = stack_.top();
            if(m == c)
            {
                stack_.pop();
            }else{
                stack_.push(c);
            }
        }
    }
    // int nsize = stack_.size();
    // if(nsize == 0){return "";}
    // std::string r(stack_.size(), ' ');
    // while(nsize)
    // {
    //     char c = stack_.top();
    //     stack_.pop();
    //     r[nsize-1] = c;
    //     nsize--;
    // }
    std::string r="";
    while(!stack_.empty())
    {
        r += stack_.top();
        stack_.pop();
    }
    reverse(r.begin(), r.end());
    return r;
}

int main()
{
    std::string s = "abbaca";
    std::string r = removeDuplicates(s);
    std::cout << "result is " << r << std::endl;
}