/*
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。

 

示例 1：

输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
示例 2：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 

提示：

1 <= nums.length <= 8
-10 <= nums[i] <= 10
*/


#include <vector>
#include <iostream>
#include <unordered_set>

void permutev1(std::vector<int>& nums, int start, std::vector<int> path, std::vector<bool> used, std::vector<std::vector<int>>& result) {
    if(path.size() == nums.size())
    {
        result.push_back(path);
        return;
    }
    std::unordered_set<int> uset; // 使用set对本层元素进行去重
    for(int i = 0 ; i < nums.size(); i++)
    {
        //std::vector<bool>used(nums.size(),0);
        if(used[i] == false)
        {
            if(uset.find(nums[i]) != uset.end())
            {
                continue;
            }
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            used[i] = true;
            permutev1(nums, i+1, path, used, result);
            path.pop_back();
            used[i] = false;
        }
    }
}

std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    std::vector<bool>used(nums.size(),0);
    permutev1(nums,0,path,used,result);
    return result;
}

int main()
{
    std::vector<int>nums = {1,1,2};
    std::vector<std::vector<int>>result = permuteUnique(nums);
    return 0;
}