/*
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。

 

示例 1：

输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。
示例 2：

输入：nums = [9], target = 3
输出：0
 

提示：

1 <= nums.length <= 200
1 <= nums[i] <= 1000
nums 中的所有元素 互不相同
1 <= target <= 1000
 

进阶：如果给定的数组中含有负数会发生什么？问题会产生何种变化？如果允许负数出现，需要向题目中添加哪些限制条件？
*/



#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

//正确的 子问题 定义应该是，targets(k,i) = targets(k-1, i) + targets(k, i-k)
//即前 k 个数字凑齐target为i 的组合数等于前 k-1个数字凑齐数字i的组合数加上 
//在原来数字i-k的基础上使用数字k的组合数。说的更加直接一点，那就是用前k个数字凑齐数字i，
//要分为两种情况来看，一种是没有用第k个数字，前k-1个数字就凑齐了，一种是前面已经凑到了i-k，
//现在就差第k个数字了。
int combinationSum4v0(std::vector<int>& nums, int target) {
    int size = nums.size();
    int amount = target +1;
    std::vector<std::vector<int>>dp(size+1, std::vector<int>(amount, 0));
    std::sort(nums.begin(),nums.end());
    dp[0][0] = 1;
    for(int k = 1; k <= size; k++)
    {
        dp[k][0] = 1;
        for(int i =1; i <= target; i++)
        {
            if(i >= nums[k-1])
            {
                dp[k][i] = dp[k-1][i] + dp[k][i-nums[k-1]];
            }
            else{
                dp[k][i] = dp[k-1][i];
            }
        }   
    }
    return dp[size][target];
}

//题目中明确指出顺序不同视为不同组合，因此本题目和爬楼梯的题目类似
//std::vector<int> nums = {1,2,3};时dp[n]=dp[n-1]+dp[n-2]+dp[n-3]
//TODO
int combinationSum4(std::vector<int>& nums, int target) {
    int size = nums.size();
    int amount = target +1;
    std::vector<int>dp(amount, 0);
    dp[0] = 1;
    // int* dp = (int*)malloc(amount*sizeof(int));
    // memset(dp, 0, amount);
    // dp[0] = 1;    
    for(int i =1; i <= target; i++)
    {
        for(int j = 0; j < nums.size(); j++)
        {
            int m = nums[j];
            int n = i-m;
            if(n >=0 && n <= target)
            {
                dp[i] += dp[n];
            }
        }
    }
    return dp[target];
    // std::vector <int> a(target+1);
    // for(int i=1;i<=target;i++)
    // {
    //         long long  max=0;
    //         for(int k=0;k<nums.size();k++)
    //         {
    //             if(i==nums[k])
    //             {
    //                 max++;
    //                 continue;
    //             }
    //             else if(nums[k]>i)
    //             continue;
    //             max+=a[i-nums[k]];
    //         }
    //         a[i]=max;
    // }
    // return a[target];   
}


int main()
{
    //std::vector<int> nums = {1,2,3};
    //int target = 4;
    std::vector<int> nums = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,111};
    int target = 999;
    int result = combinationSum4(nums, target);
    std::cout << result << std::endl;
}