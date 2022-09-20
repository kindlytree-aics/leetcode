/*给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

 

示例 1：

输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
示例 2：

输入：target = 4, nums = [1,4,4]
输出：1
示例 3：

输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
 

提示：

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 105
 

进阶：

如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-size-subarray-sum
*/

#include <vector>
#include <iostream>
#include<cmath>
using namespace std;


// int minSubArrayLen_v1(int target, vector<int>& nums) {
//     int nsize = nums.size();
//     vector<vector<int>> sum_(nsize, vector<int>(nsize, 0));
//     int min_len = nsize;
//     for(int i = 0; i < nsize; i++)
//     {
//         sum_[i][i] = nums[i];                    
//         if(sum_[i][i] == target){
//             return 1;
//         }
//         for(int j =i+1; j < nsize; j++)
//         {
//             sum_[i][j] = sum_[i][j-1] + nums[j];
//             if(sum_[i][j] >= target)
//             {
//                 if(min_len > (j-i+1)){
//                     min_len = j-i+1;
//                 }
//                 break;
//             }
//         }
//     }
//     return min_len;
// }

// int minSubArrayLen_v2(int target, vector<int>& nums) {


//         int start = 0, end = 0;
//         int nsize = nums.size();
//         //vector<vector<int>> sum_(nsize, vector<int>(nsize, 0));
//         //vector<int>nums ={2,3,1,2,4,3};
//         //int target = 7;
//         int min_len = INT_MAX;
//         int sum = nums[start];
//         while(end < nsize-1){
//             while(sum < target){
//                 if(end < nsize-1)
//                 {
//                     end += 1;
//                     sum += nums[end];
//                 }else
//                 {
//                     return min_len == INT_MAX ? 0 : min_len;
//                 }
//             }
//             while(sum >= target){
//                 sum -= nums[start];
//                 start++;//如果执行一次后sum<target,但是start已经加了1，后面的要再加回来1
//                 //如果执行一次后sum=target,条件满足，会进入下一次的while，start会加2，后面的要在加回来1
//             }
//             int cur_len = end-start+2;
//             if(cur_len < min_len){
//                 min_len = cur_len;
//             }
//         }
//         return min_len == INT_MAX ? 0: min_len ;        

// }


// int minSubArrayLen_v3(int target, vector<int>& nums) {


//         //vector<vector<int>> sum_(nsize, vector<int>(nsize, 0));
//         //vector<int>nums ={2,3,1,2,4,3};
//         //int target = 7;
//         int start = 0, end = 0;
//         int nsize = nums.size();        
//         int min_len = INT_MAX;
//         int sum = nums[start];
//         while(true){
//             if(sum >= target)
//             {
//                 while(sum >= target){
//                     sum -= nums[start];
//                     start++;//如果执行一次后sum<target,但是start已经加了1，后面的要再加回来1
//                     //如果执行一次后sum=target,条件满足，会进入下一次的while，start会加2，后面的要在加回来1
//                 }
//                 int cur_len = end-start+2;
//                 if(cur_len < min_len){
//                     min_len = cur_len;
//                 }
//             }

//             if(end < nsize-1)
//             {
//                 end += 1;
//                 sum += nums[end];
//             }else
//             {
//                 return min_len == INT_MAX ? 0 : min_len;
//             }
//         }
//         return min_len == INT_MAX ? 0: min_len ;        
// }

int minSubArrayLen(int target, vector<int>&nums)
{
    int nsize = nums.size();
    int start=0, end=0;
    int sum = nums[start];
    int min_len= INT_MAX;
    //vector<int>nums ={2,3,1,2,4,3};
    //int target = 7; 
    while(true)
    {
        if(sum >= target){
            while(sum >=target){
                sum -= nums[start]; //start=0->1
                start++;//sum=target, start=1, sum<target,start=2
            }
            int cur_len = end-start+2;
            if(cur_len < min_len){
                min_len = cur_len;
            }
        }
        if(end < nsize-1){
            end +=1;
            sum += nums[end];
        }else{
            return min_len == INT_MAX ? 0 :min_len;
        }
    }
}

int main(){
    //vector<int>nums = {2,3,1,2,4,3};
    //int target = 7;
    //vector<int>nums = {1,1,1,1,1,1,1,1};
    //int target = 11;
    // vector<int>nums = {1,2,3,4,5};
    // int target = 11;
    vector<int>nums ={2,3,1,2,4,3};
    int target = 7;    
    int len = minSubArrayLen(target, nums);
    cout << len << endl;
}