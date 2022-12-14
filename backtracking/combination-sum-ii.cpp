/*
题目来源：https://leetcode.cn/problems/combination-sum-ii/
给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用 一次 。

注意：解集不能包含重复的组合。 

 

示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
]
 

提示:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
*/

#include <vector>
#include <iostream>
#include<algorithm>

void combinationSum2v1(std::vector<int>& candidates, int target, int sum, int idx, std::vector<int>path, std::vector<bool>& used, std::vector<std::vector<int>>&result) {
    //if(idx < candidates.size())
    //for(int i = idx; i < candidates.size(); i++)
    while(idx <= candidates.size()-1)
    {

        sum += candidates[idx];
        path.push_back(candidates[idx]);
        used[idx] = true;
        if(sum < target)
        {
            //combinationSum2v1(candidates, target, sum, idx+1, path, result);
            if(idx < candidates.size()-1)
            {
                combinationSum2v1(candidates, target, sum, idx+1, path, used, result);
            }
        }else if(sum == target)
        {
            result.push_back(path);
        }
        path.pop_back();
        sum -= candidates[idx];
        used[idx]=false;
        idx++;
        //连续数字有一样的情况，后面的数字和前面的数字相同，
        //used[idx-1]什么时候设为了false呢？说明是递归已经回溯到更前面的时候的情况，这个时候说明前面已经使用过了
        //如5555，如果已经回退到国第2个5了，则后面的55都不要再去往后取值了（已经取值过了）
        //再次使用还会出现重复
        //且前面的设为未使用（前面肯定先设为了true，然后再设置成false的），
        //则后面的也要设为未使用
        while(idx >=1 && idx <= candidates.size()-1 && candidates[idx] == candidates[idx-1] && used[idx-1] == false)
        {
            used[idx] = false;
            idx++;
        }
    }
}
std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>>result;
    std::vector<int> path;
    std::vector<bool> used(candidates.size(), false);
    combinationSum2v1(candidates, target, 0, 0, path, used, result);
    return result;
}

int main()
{
    std::vector<int>nums = {10,1,2,7,6,1,5};
    sort(nums.begin(), nums.end());
    int target = 8;
    std::vector<std::vector<int>> res = combinationSum2(nums, target);
    return 0;
}