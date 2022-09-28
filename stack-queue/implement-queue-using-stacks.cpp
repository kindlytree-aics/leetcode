/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/implement-queue-using-stacks
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

实现 MyQueue 类：

void push(int x) 将元素 x 推到队列的末尾
int pop() 从队列的开头移除并返回元素
int peek() 返回队列开头的元素
boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：

你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。
 

示例 1：

输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false

提示：

1 <= x <= 9
最多调用 100 次 push、pop、peek 和 empty
假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作
*/

#include<stack>

//技巧是从stack_out栈pop元素，如果为空，将stack_in的元素push到stack_out
//push直接push到stack_in
class MyQueue {
public:
    std::stack<int> stack_in;
    std::stack<int> stack_out;
    
public:
    void push(int x) //将元素 x 推到队列的末尾
    {
        stack_in.push(x);

    }
    int pop() //从队列的开头移除并返回元素
    {
        if(stack_out.empty())
        {
            while(!stack_in.empty())
            {
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }
        int result = stack_out.top();
        stack_out.pop();
        return result;
    }
    int peek() //返回队列开头的元素
    {
        int res = this->pop(); // 直接使用已有的pop函数
        stack_out.push(res); // 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }
    bool empty() //如果队列为空，返回 true ；否则，返回 false
    {
        return stack_in.empty() && stack_out.empty();
    }
};
