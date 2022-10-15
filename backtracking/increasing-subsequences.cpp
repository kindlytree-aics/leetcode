/*
题目来源： https://leetcode.cn/problems/increasing-subsequences/

给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中 至少有两个元素 。你可以按 任意顺序 返回答案。

数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。

 

示例 1：

输入：nums = [4,6,7,7]
输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
示例 2：

输入：nums = [4,4,3,2,1]
输出：[[4,4]]
 

提示：

1 <= nums.length <= 15
-100 <= nums[i] <= 100
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

//https://www.programmercarl.com/0491.%E9%80%92%E5%A2%9E%E5%AD%90%E5%BA%8F%E5%88%97.html#%E6%80%9D%E8%B7%AF
void findSubsequencesv1(std::vector<int>& nums, int start, std::vector<int> path, std::vector<std::vector<int>>&result)
{
    if (path.size() > 1) {
        result.push_back(path);
        // 注意这里不要加return，要取树上的节点
    }
    std::unordered_set<int> uset; // 使用set对本层元素进行去重
    for (int i = start; i < nums.size(); i++) {
        if ((!path.empty() && nums[i] < path.back())
                || uset.find(nums[i]) != uset.end()) {
                continue;
        }
        uset.insert(nums[i]); // 记录这个元素在本层用过了，本层后面不能再用了
        path.push_back(nums[i]);
        findSubsequencesv1(nums, i + 1,path, result);
        path.pop_back();
    }
}

std::vector<std::vector<int>> findSubsequences(std::vector<int>& nums) {
    std::vector<int> path;
    std::vector<std::vector<int>>result;
    //sort(nums.begin(),nums.end());
    findSubsequencesv1(nums, 0, path, result);
    return result;
}

int main()
{
    std::vector<int>  nums = {4,6,7,7};
    //std::vector<int>  nums = {4,4,3,2,1};
    std::vector<std::vector<int>>result = findSubsequences(nums);
    return 0;
}