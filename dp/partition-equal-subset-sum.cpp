/*
题目来源： https://leetcode.cn/problems/partition-equal-subset-sum/

给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例 1：

输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。
示例 2：

输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。
 

提示：

1 <= nums.length <= 200
1 <= nums[i] <= 100
*/
#include<vector>

//思路：先求出总和，如果能被2整除(%2==0),则有可能并记下这个数为target，否则不可能
//从nums的一个元素开始遍历，如果当前就之前的所有元素的组合的可能和为target，则返回
//如果小于，则作为candidate继续后面的遍历；如
//sums[0] = [0], sums[1] = [0,1]的和（如果小于target）还有[0]以及[1]的和
//假设当前遍历到i，其潜在的数字组合为candidate[i]为当前所有可能的小于等于i个元素的组合和（且小于target）
//则到i+1时，前面cadidate[i-1]的每一项继续保留(当前i不参与组合)，
//同时如果某一个candiate加上i(参与组合)等于target则返回true，如果小于target则也加入到candiate里
//否则其和不加入到candiate里，因为已经大于target，后续也不会再满足条件了（都是正整数）
//以下代码在特殊nums下性能不够，中间candidates数组比较长
//如：[100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,99,97]
bool canPartitionv0(std::vector<int>& nums) {
    int sum = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        sum+=nums[i];
    }
    int target = sum / 2;
    if(sum %2 != 0) return false;
    std::vector<int>candidates;
    if(target > nums[0]){candidates.push_back({nums[0]});}
    if(target == nums[0]) return true;
    for(int i = 1; i <nums.size(); i++)
    {
        if(target == nums[i])
        {
            return true;
        }else if(target < nums[i])
        {
            return false;
        }else{
            if(candidates.size() == 0)
            {
                candidates.push_back({nums[i]});
                continue;
            }
            int last_candidate_num = candidates.size(); 
            for(int m = 0; m < last_candidate_num; m++)
            {
                int new_candiate_sum = nums[i] + candidates[m];
                if(new_candiate_sum == target)
                {
                    return true;
                }else if(new_candiate_sum< target)
                {
                    candidates.push_back(new_candiate_sum);
                }
            }
            candidates.push_back(nums[i]);
        }
    }
    return false;
}

//官方题解：
//https://leetcode.cn/problems/partition-equal-subset-sum/solutions/442320/fen-ge-deng-he-zi-ji-by-leetcode-solution/
//或https://leetcode.cn/problems/partition-equal-subset-sum/solutions/13059/0-1-bei-bao-wen-ti-xiang-jie-zhen-dui-ben-ti-de-yo/
//为0，1背包问题
//具体做法是：画一个 nums.size() 行，target + 1 列的表格。这里 len 是物品的个数，target 是背包的容量。
//每一个行表示一个一个物品考虑，target + 1多出来的那 1 列，表示背包容量从 0 开始考虑。很多时候，我们需要考虑这个容量为 0 的数值。
//dp[i][j]={dp[i-1][j], nums[i], dp[i-1][j-nums[i]]}上面如果前两项为真，则直接为真，否则结果为第三项
bool canPartition(std::vector<int>& nums) {
    int sum = 0, max_element = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        sum+=nums[i];
        if(max_element < nums[i])
        {
            max_element = nums[i];
        }
    }
    int target = sum / 2;
    if(sum %2 != 0) return false;
    std::vector<std::vector<bool>>dp(nums.size(), std::vector<bool>(target+1,false));
    if(target == nums[0]) return true;
    if(target < nums[0])return false;
    dp[0][nums[0]]=true;
    for(int i =1; i < nums.size(); i++)
    {
        for(int j = 0; j <= target; j++)
        {
            if(dp[i-1][j] == true){
                dp[i][j] = true;
            }else if(nums[i] == j)
            {
                dp[i][j] = true;
            }else if(j-nums[i] > 0){
                dp[i][j] = dp[i-1][j-nums[i]];
            }
        }
    }
    return dp[nums.size()-1][target];
}


int main()
{
    //std::vector<int>nums = {1,5,11,5};
    // std::vector<int>nums = {1,2,3,5};
    //std::vector<int>nums = {9,5};
    std::vector<int>nums = {1,2,5};
    bool can_partition = canPartition(nums);
    return 0;
}