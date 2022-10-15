/*

题目来源：https://leetcode.cn/problems/permutations/

给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

示例 1：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：

输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例 3：

输入：nums = [1]
输出：[[1]]
 

提示：

1 <= nums.length <= 6
-10 <= nums[i] <= 10
nums 中的所有整数 互不相同
*/

#include <vector>
#include <iostream>
#include <algorithm>

void permutev1(std::vector<int>& nums, int start, std::vector<int> path, std::vector<bool> used, std::vector<std::vector<int>>& result) {
    if(path.size() == nums.size())
    {
        result.push_back(path);
        return;
    }
    for(int i = 0 ; i < nums.size(); i++)
    {
        //std::vector<bool>used(nums.size(),0);
        if(used[i] == false)
        {
            path.push_back(nums[i]);
            used[i] = true;
            permutev1(nums, i+1, path, used, result);
            path.pop_back();
            used[i] = false;
        }
    }
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    std::vector<bool>used(nums.size(),0);
    permutev1(nums,0,path,used,result);
    return result;
}

int main()
{
    std::vector<int>nums = {1,2,3};
    std::vector<std::vector<int>>result = permute(nums);
    return 0;
}