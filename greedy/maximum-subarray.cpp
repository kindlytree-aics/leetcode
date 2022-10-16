/*
题目来源 https://leetcode.cn/problems/maximum-subarray/

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。

示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
示例 2：

输入：nums = [1]
输出：1
示例 3：

输入：nums = [5,4,-1,7,8]
输出：23
 

提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。

*/

#include <vector>
#include <iostream>

//和为负值，分段，否则记录当前最大的和数，以及当前的和
//并随着后面的求和将当前和和最大的和进行比较
//根据应用情况更新当前的最大

int maxSubArray(std::vector<int>& nums) {
    int left = 0, right= nums.size()-1, max_sum = nums[0], cur_sum=0;
    for(int i = 0; i < nums.size(); i++)
    {
        cur_sum += nums[i];
        if(cur_sum < 0)
        {
            if(max_sum  <= cur_sum)
            {
                max_sum = cur_sum;
            }
            cur_sum = 0;//分段，重新计算
        }else{
            if(cur_sum > max_sum)
            {
                max_sum = cur_sum;
            }
        }
    }
    return max_sum;
}

int main()
{
    //std::vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    std::vector<int> nums = {5,4,-1,7,8};
    int max_cont_sum = maxSubArray(nums);
    return 0;
}