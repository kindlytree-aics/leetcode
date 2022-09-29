
/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/implement-stack-using-queues

请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
 

注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。
你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
 

示例：

输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False
 
提示：

1 <= x <= 9
最多调用100 次 push、pop、top 和 empty
每次调用 pop 和 top 都保证栈不为空
 
进阶：你能否仅用一个队列来实现栈。
*/


#include<queue>

//思路1：题目中要用两个队列模拟堆栈，可以用一个队列做备份，pop时将前面的元素push到备份队列中
//取出最后一个后，再将从备份队列中push回来
//思路2：只用一个队列，也可以实现，将队列前面的元素重新添加到队尾就可以
//下面就写一下思路2；
class MyStack {
public:
    std::queue<int> queue;

public:
    void push(int x) //将元素 x 推到队列的末尾
    {
        queue.push(x);

    }
    int pop() //从队列的开头移除并返回元素
    {
        int qsize = queue.size();
        while(qsize > 1)
        {
            queue.push(queue.front());
            queue.pop();
            qsize--;
        }
        int result = queue.front();
        queue.pop();
        return result;
    }
    int top() //返回队列开头的元素
    {
        return queue.back();
    }
    bool empty() //如果队列为空，返回 true ；否则，返回 false
    {
        return queue.empty();
    }
};