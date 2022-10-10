/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/combinations

给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

你可以按 任何顺序 返回答案。

示例 1：

输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
示例 2：

输入：n = 1, k = 1
输出：[[1]]
 

提示：

1 <= n <= 20
1 <= k <= n
通过次数436,531提交次数565,258
*/

#include <vector>
#include <iostream>
#include <queue>

// std::vector<std::vector<int>> combinev1(std::vector<int>nums, std::vector<int>prefix_, int left, int k, std::vector<std::vector<int>>&res)
// {
//     if(prefix_.size() < k)
//     {
//         std::vector<std::vector<int>> result1;
//         std::vector<std::vector<int>> result2;
//         if(prefix_.size() + nums.size()-left > k)
//         {
//             result1 = combinev1(nums, prefix_, left+1, k, res);
//         }
//         if(prefix_.size() + nums.size()-left > k-1)
//         {
//             prefix_.push_back(nums[left]);
//             result2 = combinev1(nums, prefix_, left+1, k, res);
//         }  

//         for(auto res1: result2){
//             result1.push_back(res1);
//         }
//         return result1;
//     }else{
//         //std::vector<int>res;
//         std::vector<std::vector<int>>cur_res_;
//         cur_res_.push_back(prefix_);
//         return cur_res_;
//     }
// }

// std::vector<std::vector<int>> combine(int n, int k) {
//     std::vector<int>nums(n,0);
//     for(int i = 0; i < nums.size();i++)
//     {
//         nums[i] = i+1;
//     }
//     std::vector<int>prefix_;
//     std::vector<std::vector<int>>res;
//     return combinev1(nums, prefix_, 0, k, res);
// }

void backtracking(int n, int k, int startIndex, std::vector<int>path, std::vector<std::vector<int>>res) {
    if (path.size() == k) {
        res.push_back(path);
        return;
    }
    for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) { // 优化的地方
        path.push_back(i); // 处理节点
        backtracking(n, k, i + 1, path, res);
        path.pop_back(); // 回溯，撤销处理的节点
    }
}


std::vector<std::vector<int>> combine(int n, int k) {
    std::vector<int>path;
    std::vector<std::vector<int>>res;
    backtracking(n, k, 1, path, res);
    return res;
}

int main()
{
    std::vector<std::vector<int>> res = combine(4, 2);
    return 0;
}