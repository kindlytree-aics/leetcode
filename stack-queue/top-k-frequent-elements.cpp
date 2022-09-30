/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/top-k-frequent-elements

给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
示例 1:

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
示例 2:

输入: nums = [1], k = 1
输出: [1]
 
提示：

1 <= nums.length <= 105
k 的取值范围是 [1, 数组中不相同的元素的个数]
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的

进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。
*/


#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>

//用一个k个元素的小堆数据结构维护k个高频词，当前的频率大于堆顶的元素时（当前堆顶是k个最小的）
//如果后面有词汇的频率比当前的要大，当前的小堆堆顶元素要删除，而push进更大的
//priority_queue即为
//称为优先队列，其底层是用堆来进行实现的。
//在优先队列中，队首元素一定是当前队列中优先级最高的那一个。
//当然，可以在任何时候往优先队列里面加入元素，
//而优先队列底层的数据结构堆（heap）会随时调整结构，使得每次的队首元素都是优先级最高的

struct cmp {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};

std::vector<int> topKFrequent(std::vector<int>& nums, int k) 
{
    std::unordered_map<int, int>nums_count;
    for(int i : nums)
    {
        nums_count[i]++;
    }

    //std::priority_queue<pair<int
    //优先输出小数据
    //priority_queue<int, vector<int>, greater<int> > p;
    //自定义优先级，使用greater比较函数，小顶堆
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int, int>>, cmp> prio_queue;
    for(std::unordered_map<int ,int>::iterator it = nums_count.begin();
        it != nums_count.end(); it++)
        {
            prio_queue.push(*it);
            if(prio_queue.size() > k)
            {
                prio_queue.pop();
            }

        }
    std::vector<int> result(k);
    for(int i=k-1; i>=0; i--)
    {
        result[i] = prio_queue.top().first;
        prio_queue.pop();

    }
    return result;
}

int main()
{
    std::vector<int> nums = {1,1,1,2,2,3};
    int  k = 2;
    std::vector<int> max_repeated_k_nums = topKFrequent(nums, k);
    for(int i = 0; i < max_repeated_k_nums.size(); i++)
    {
        std::cout << max_repeated_k_nums[i] ;
    }
}


