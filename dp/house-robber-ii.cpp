/*
https://leetcode.cn/problems/house-robber-ii/

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。
这个地方所有的房屋都围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。

示例 1：

输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
示例 2：

输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 3：

输入：nums = [1,2,3]
输出：3
 
提示：

1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/

//dp[0] = nums[0]  {true}
//dp[1] = max(nums[0],nums[1]){true,false} or {false,true}
//dp[2] = max(dp[1], dp[2-2]+nums[2])
//dp[i] = max(dp[i-1], dp[i-2]+nums[i])
//要记录下情况再去判断,除了dp还要solution，solution记录具体偷的房间的序号情况true表示偷，false表示不偷
#include<vector>
#include<iostream>

//dp[0][0] = 0  {false}, dp[0][1] = nums[0]{true}
//dp[1][0] = std::max(dp[0][0],dp[0][1])
//dp[1][1] = std::max(nums[1], dp[0][0])
//dp[i][0] = std::max(dp[i-1][1], dp[i-2][1]+nums[i])
//dp[i][1] = std::max(dp[i-1][0]+nums[i], dp[i-2][1]+nums[i])
//dp[n][0] = std::max(dp[n-1][1], dp[n-2][0]+nums[1])
//dp[n][1] = std::max(dp[n-1][0]+nums[n], dp[n-2][1]+nums[n])
//如下思路有问题，std::vector<int>nums={2,2,4,3,2,5}//不通过;
// int rob(std::vector<int>& nums) {
//     std::vector<std::vector<int>>dp(nums.size(), std::vector<int>(2,0));
//     std::vector<std::vector<std::vector<int>>>solution(nums.size(), std::vector<std::vector<int>>(2, std::vector<int>({})));
//     dp[0][0] = 0;
//     dp[0][1] = nums[0];
//     solution[0][0].push_back(0);
//     solution[0][1].push_back(1);
//     if(nums.size() <=3)
//     {
//         if(nums.size() >= 2)
//         {
//             dp[1][0] = dp[0][1];
//             dp[1][1] = nums[1];
//         }
//         if(nums.size() == 3)
//         {
//             dp[2][1] = nums[2];
//             dp[2][0] = std::max(nums[0], nums[1]);           
//         }
//         return std::max(dp[nums.size()-1][0], dp[nums.size()-1][1]);
//     }
//     dp[1][0] = dp[0][1];
//     dp[1][1] = nums[1];
//     solution[1][0] = solution[0][1];
//     solution[1][0].push_back(0);
//     solution[1][1] = solution[0][0];
//     solution[1][1].push_back(1);
//     for(int i = 2; i < nums.size(); i++)
//     {
//         int max = std::max(dp[i-1][0], dp[i-1][1]);
//         //dp[i][0] = std::max(dp[i-1][1],dp[i-1][0]);
//         //dp[i-1][1] >= dp[i-2][0]
//         ///dp[i-1][0] >= dp[i-2][1]
//         //取最大，如果有相等，则判断第1个元素优先选0；
//         if(dp[i-1][1] > dp[i-1][0])
//         {
//             solution[i][0] = solution[i-1][1];
//             max = dp[i-1][1];
//         }else{
//             if(dp[i-1][0] > dp[i-1][1])
//             {
//                 solution[i][0] = solution[i-1][0];
//             }else if(dp[i-1][0] == dp[i-1][1])
//             {
//                 if(solution[i-1][0][0] == 0)
//                 {
//                     solution[i][0] = solution[i-1][0];
//                 }else{
//                     solution[i][0] = solution[i-1][1];
//                 }
//             }         
//         }
//         solution[i][0].push_back(0);
//         dp[i][0] = max;
//         //[i-2][0]
//         //dp[i-1][0],dp[i-2][1],dp[i-2][0]
//         //dp[i][1] = std::max(dp[i-1][0]+nums[i], dp[i-1][1], dp[i-2][0]+nums[i]
//         int r = dp[i-1][0]+nums[i];
//         int s = dp[i-2][0]+nums[i];
//         max = std::max(r,s);
//         if(r > s)
//         {
//             solution[i][1] = solution[i-1][0];
//             solution[i][1].push_back(1);        
//         }else if(r == s)
//         {
//             if(solution[i-1][0][0] == 0)
//             {
//                 solution[i][1] = solution[i-1][0];
//                 solution[i][1].push_back(1);
//             }else{
//                 solution[i][1] = solution[i-2][0];
//                 solution[i][1].push_back(0);
//                 solution[i][1].push_back(1);
//             }            
//         }else
//         {
//             solution[i][1] = solution[i-2][0];
//             solution[i][1].push_back(0);
//             solution[i][1].push_back(1);               
//         }
//         dp[i][1] = max;
//     }
//     if(solution[nums.size()-1][1][0] == 1)
//     {
//         int k = dp[nums.size()-1][1];
//         dp[nums.size()-1][1] = std::max(k-nums[0], k-nums[nums.size()-1]);
//     }
//     return std::max(dp[nums.size()-1][0], dp[nums.size()-1][1]);
// }

//思路和house-robber类似，不过第一个和最后一个不能同时偷窃，因此分成两段分别求，然后求最大值
//分成0-n-2和1-n-1两个分别求，然后求最大值即可。
//https://leetcode.cn/problems/house-robber-ii/solutions/722767/da-jia-jie-she-ii-by-leetcode-solution-bwja/
int rob(std::vector<int>& nums) {
    return -1;
}
int main()
{
    // std::vector<int>nums={1,2,3,1};
    //  std::vector<int>nums={2,2,3};
    //std::vector<int>nums={1,2,3,1};
    //std::vector<int>nums={200,3,140,20,10};
    //std::vector<int>nums={1,1,3,6,7,10,7,1,8,5,9,1,4,4,3}//41;
    std::vector<int>nums={2,2,4,3,2,5};//注释的函数不通过;
    int max_rob_count = rob(nums);
    std::cout<< max_rob_count <<std::endl;
}