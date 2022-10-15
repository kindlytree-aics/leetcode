/*
题目来源：https://leetcode.cn/problems/subsets/

给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

 

示例 1：

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
示例 2：

输入：nums = [0]
输出：[[],[0]]
 

提示：

1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums 中的所有元素 互不相同
*/


#include <vector>
#include <iostream>

void subsetsv1(std::vector<int>& nums, int start, std::vector<int>subset, std::vector<std::vector<int>>&result)
{
    if(start <= nums.size()-1)
    {
        //result.push_back(subset);
        subset.push_back(nums[start]);
        subsetsv1(nums, start+1, subset, result);
        subset.pop_back();
        subsetsv1(nums, start+1, subset, result);
    }else{
        result.push_back(subset);
    }
}
std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>>result;
    std::vector<int>subset;
    subsetsv1(nums, 0, subset, result);
    return result;
}

int main()
{
    std::vector<int>nums = {1,2,3};
    std::vector<std::vector<int>> result = subsets(nums);
    return 0;
}