/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/sliding-window-maximum

给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：

输入：nums = [1], k = 1
输出：[1]

提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/

#include<vector>
#include<deque>
#include<iostream>

class MyQueue { //单调队列（从大到小）

public:
    std::deque<int> que; 
    // 使用deque双端队列来实现单调队列
    // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，
    // 如果相等则弹出(相等说明滑动窗口移走的位置就是最大值)。
    // 同时pop之前判断队列当前是否为空。
    void pop(int value) {
        if (!que.empty() && value == que.front()) {
            que.pop_front();
        }
    }
    // 如果push的数值大于入口元素的数值，
    // 那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
    // 这样就保持了队列里的数值是单调从大到小的了。
    // 并不需要保留窗口内所有的值
    void push(int value) {
        while (!que.empty() && value > que.back()) {
            que.pop_back();
        }
        que.push_back(value);

    }
    // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
    int front() {
        return que.front();
    }
};

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    MyQueue que;
    std::vector<int> result;
    for(int i =0 ; i < k; i++)
    {
        que.push(nums[i]);
    }
    result.push_back(que.front());
    for(int i=k ; i < nums.size(); i++)
    {
        que.pop(nums[i-k]);
        que.push(nums[i]);
        result.push_back(que.front());
    }
    return result;
}

int main()
{
    std::vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    std::vector<int> result = maxSlidingWindow(nums, k);
    for(int i = 0; i < result.size(); i++)
    {
        std::cout << nums[i] ;
    }
}