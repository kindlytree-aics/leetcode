/*
题目来源： https://leetcode.cn/problems/subsets-ii/
给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。

 

示例 1：

输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
示例 2：

输入：nums = [0]
输出：[[],[0]]
 

提示：

1 <= nums.length <= 10
-10 <= nums[i] <= 10
*/

#include <vector>
#include <iostream>
#include <algorithm>

void subsetsv1(std::vector<int>& nums, int start, std::vector<bool>&used, std::vector<int>subset, std::vector<std::vector<int>>&result)
{
    if(start <= nums.size()-1)
    {
        //result.push_back(subset);
        while(start <= nums.size()-1 && start >= 1 && nums[start] == nums[start-1] && used[start-1] == false)
        {
            start++;
        }
        if(start <= nums.size()-1)
        {
            used[start] = true;
            subset.push_back(nums[start]);
            subsetsv1(nums, start+1, used, subset, result);
            subset.pop_back();
            used[start]=false;
            subsetsv1(nums, start+1, used, subset, result);
        }else{
            result.push_back(subset);
        }
    }else{
        result.push_back(subset);
    }
}
std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
    std::vector<std::vector<int>>result;
    std::vector<int>subset;
    std::vector<bool>used(nums.size(),0);
    sort(nums.begin(),nums.end());
    subsetsv1(nums, 0, used,subset, result);
    return result;
}

int main()
{
    std::vector<int>nums = {1,2,2};
    std::vector<std::vector<int>> result = subsetsWithDup(nums);
    return 0;
}