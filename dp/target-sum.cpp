/*
https://leetcode.cn/problems/target-sum/
给你一个整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：

例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

 

示例 1：

输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
示例 2：

输入：nums = [1], target = 1
输出：1
 

提示：

1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/target-sum
*/

#include<vector>
#include<iostream>

//思路1：每个数字前面可以为+，-两种可能，一红有2^n种可能，并判断结果，复杂度比较高;
void findTargetSumWaysv1(std::vector<int>& nums, int idx, int target, int& count,std::vector<char>solution, std::vector<std::vector<char>>&solutions) 
{
    if(idx < nums.size()-1)
    {
        int target1 = target - nums[idx];
        solution.push_back('+');
        findTargetSumWaysv1(nums, idx+1, target1, count, solution, solutions);
        solution.pop_back();
        solution.push_back('-');
        int target2 = target + nums[idx];
        findTargetSumWaysv1(nums, idx+1, target2, count, solution, solutions);
        solution.pop_back();
    }else{
        int target1 = target - nums[idx];
        if(target1 == 0)
        {
            solution.push_back('+');
            solutions.push_back(solution);
            solution.pop_back();
            count +=1;
        }
        int target2 = target + nums[idx];
        if(target2 == 0)
        {
            solution.push_back('-');
            solutions.push_back(solution);
            solution.pop_back();
            count +=1;
        }
    }
}

//思路2：先求出max和min，然后求[0, max-min]
//solution[i][t]的可能性
//dp[0][-min+nums[0]] = 1,dp[0]-[min-nums[i]] = 1
int findTargetSumWays(std::vector<int>& nums, int target) {
    int max = 0, min = 0;
    int size = nums.size();
    for(int i = 0; i < nums.size(); i++)
    {
        if(nums[i] < 0)
        {
            min += nums[i];
            max += -1*nums[i];
        }else{
            min += -1*nums[i];
            max += nums[i];            
        }
    }

    int span = max-min+1;
    int dp[size][span];
    for(int i =0; i < size; i++)
    {
        for(int j = 0; j < span; j++)
        {
            dp[i][j] = INT_MIN;
        }

    }
    if(-min+nums[0] < span)
    {
        dp[0][-min+nums[0]] = 1;
    }
    if(-min-nums[0] < span && dp[0][-min-nums[0]] < 0)
    {
        dp[0][-min-nums[0]] = 1;
    }else{
        dp[0][-min-nums[0]] += 1;
    }
    for(int i = 1; i < size; i++)
    {
        for(int m = 0; m < span; m++)
        {
            if(dp[i-1][m] > 0)
            {
                if(m+nums[i] < span && dp[i][m+nums[i]] < 0)
                {
                    dp[i][m+nums[i]] = dp[i-1][m];
                }else{
                    dp[i][m+nums[i]] += dp[i-1][m];
                }

                if( m-nums[i] < span && dp[i][m-nums[i]] < 0)
                {
                    dp[i][m-nums[i]] = dp[i-1][m];
                }else{
                    dp[i][m-nums[i]] += dp[i-1][m];
                }              
            }
        }
    }
    int idx = -min+target;
    //return dp[size-1][idx];
    //nums=[100], taget=-200时idx<0;
    if(idx < span && idx >=0)
    {
        if(dp[size-1][idx] < 0)//为INT_MIN，个数为0
        {
            return 0;
        }
        return dp[size-1][idx];
    }else{
        return 0;
    }
}

int main()
{
    // std::vector<int>nums = {1,1,1,1,1};
    //std::vector<int>nums = {1};
    //std::vector<int>nums = {0,0,0,0,0,0,0,0,1};
    std::vector<int>nums = {7,9,3,8,0,2,4,8,3,9};
    int count = 0;
    int target = 0;
    //int target = 1;
    //int target = 3;
    // int idx = 0;
    // std::vector<char>solution;
    // std::vector<std::vector<char>>solutions;
    //findTargetSumWaysv1(nums, idx, target, count, solution, solutions);
    count = findTargetSumWays(nums,target);
    std::cout << count << std::endl;

}