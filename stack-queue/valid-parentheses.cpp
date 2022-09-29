
/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/valid-parentheses
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。
 

示例 1：

输入：s = "()"
输出：true
示例 2：

输入：s = "()[]{}"
输出：true
示例 3：

输入：s = "(]"
输出：false
 

提示：

1 <= s.length <= 104
s 仅由括号 '()[]{}' 组成
*/

#include<string>
#include<iostream>
#include<stack>

bool is_map(char a, char b){
    if( a == '(' && b == ')')
    {
        return true;
    }else if(a == '[' && b == ']')
    {
        return true;
    }else if(a == '{' && b == '}')
    {
        return true;
    }else{
        return false;
    }
}

//基于堆栈实现，遍历每一个字符，如果是左括号就入栈，否则就和栈顶的元素进行匹配，
//若果成功，栈顶元素pop出来,进入下一个字符的判断
//如果完全匹配，最后栈为空；
bool isValid(std::string s) {
    if (s.size() % 2 != 0) return false;
    std::stack<char> stack_;
    for(char c: s)
    {
        if(c == ')' || c == ']' || c == '}')
        {
            if(stack_.empty()){
                return false;
            }else{
                char m = stack_.top();
                if(is_map(m, c)){
                    stack_.pop();
                }else{
                    return false;
                }
            }
        }else{
            stack_.push(c);
        }
    }
    return stack_.empty();
}

int main()
{
    std::string s = "()[]{}";
    bool is_valid = isValid(s);
    std::cout << s << " is " << is_valid << std::endl;
}
