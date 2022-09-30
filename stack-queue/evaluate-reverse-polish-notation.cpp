/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/evaluate-reverse-polish-notation
根据 逆波兰表示法，求表达式的值。

有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

注意 两个整数之间的除法只保留整数部分。

可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

示例 1：

输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
示例 2：

输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
示例 3：

输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

提示：

1 <= tokens.length <= 104
tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围 [-200, 200] 内的一个整数
 

逆波兰表达式：

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中
*/

#include<stack>
#include<iostream>
#include<vector>

int isOp(std::string s)
{
    if(s == "+"){
        return 0;
    }else if(s == "-"){
        return 1;
    }else if(s == "*"){
        return 2;
    }else if(s == "/"){
        return 3;
    }else{
        return -1;
    }
}

int parseInt(std::string s)
{
    int factor = 1;
    int eval_num;
    if(s[0] == '-'){
        factor = -1;
        eval_num = s[1]-48;
    }else{
        eval_num = (s[0]-48);
        if(s.size() == 1){
            return eval_num;
        }else{
            eval_num = eval_num*10 + s[1] - 48;
        }
    }
    for(int i = 2; i < s.size();i++)
    {
        eval_num *=10;
        eval_num += s[i]-48;
    }
    return eval_num * factor;
}

long evalRPN(std::vector<std::string>& tokens) {
    std::stack<long>cal_stack_;
    long result;
    for(auto s : tokens)
    {
        int is_op = isOp(s);
        if(is_op == -1){
            //int num = parseInt(s);
            int num = stoi(s);
            cal_stack_.push(num); 
            continue;
        }
        long b = cal_stack_.top();
        cal_stack_.pop();
        long a = cal_stack_.top();
        cal_stack_.pop();
        switch(is_op){
            case 0:
            {
                result = a+b;
                cal_stack_.push(result);
                break;
            }
            case 1:
            {
                result = a-b;
                cal_stack_.push(result);
                break;
            }
            case 2:
            {
                result = a*b;
                cal_stack_.push(result);                
                break;
            }
            case 3:
            {
                result = a/b;
                cal_stack_.push(result);                
                break;
            }
        }
    }
    if(!cal_stack_.empty())
    {
        return cal_stack_.top();
    }
    return result;
}

int main()
{
    //std::vector<std::string>tokens = {"4","13","5","/","+"};
    //std::vector<std::string>tokens = {"3","-4","+"};
    std::vector<std::string>tokens = {"-128","-128","*","-128","*","-128","*","8","*","-1","*"};
    int result = evalRPN(tokens);
    std::cout << result << std::endl;
}