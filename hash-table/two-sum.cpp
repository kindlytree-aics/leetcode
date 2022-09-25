/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/two-sum

给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

 

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：

输入：nums = [3,2,4], target = 6
输出：[1,2]
示例 3：

输入：nums = [3,3], target = 6
输出：[0,1]
 

提示：

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
只会存在一个有效答案
进阶：你可以想出一个时间复杂度小于 O(n2) 的算法吗？
*/

#include<iostream>
#include<vector>
#include<string>
#include <unordered_map>

using namespace std;

//基本思想:遍历当前的值，将target减去该值，如果能从后面找到减的结果值，则返回这两个值的index
vector<int> twoSum_v1(vector<int>& nums, int target) {
    vector<int>result;
    for(int i = 0; i< nums.size(); i++)
    {
        int another = target - nums[i];
        for(int j = i+1; j < nums.size(); j++)
        {
            if(another == nums[j])
            {
                result.push_back(i);
                result.push_back(j);
                return result;
            }
        }
    }
    return result;
}

//可以用map结构来存储数组的信息，key为元素的值，value为其索引
//遍历数组的元素，如果在map中能找到target-当前元素的值的key，说明已经找到了题目中要求的结果
//否则将当前的值和所谓作为map中元素进行插入
//同理，std::map 和std::multimap 的key也是有序的
//题目中并不需要key有序，选择std::unordered_map 效率更高
//nums=[2,7,11,5],target=9;
vector<int> twoSum(vector<int>& nums, int target)
{
    std::unordered_map<int, int>map;
    for(int i =0; i< nums.size(); i++)
    {
        auto iter = map.find(target-nums[i]);
        if(iter != map.end())
        {
            return {iter->second, i};
        }else{
            map.insert(pair<int, int>(nums[i], i));
        }
    }
}

int main()
{
    vector<int> nums = {2,7,11,5};
    vector<int> result  = twoSum(nums, 9);
    for(int i= 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    return 0;

}