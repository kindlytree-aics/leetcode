/*
题目来源：https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/

给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：

选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
重复这个过程恰好 k 次。可以多次选择同一个下标 i 。

以这种方式修改数组后，返回数组 可能的最大和 。


示例 1：

输入：nums = [4,2,3], k = 1
输出：5
解释：选择下标 1 ，nums 变为 [4,-2,3] 。
示例 2：

输入：nums = [3,-1,0,2], k = 3
输出：6
解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。
示例 3：

输入：nums = [2,-3,-1,5,-4], k = 2
输出：13
解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。
 

提示：

1 <= nums.length <= 104
-100 <= nums[i] <= 100
1 <= k <= 104

*/

//想法：如果有负数，尽可能的将负数都转化为整数，
//思想，先排序，如果有负数，且负数的个数大于等于k，则将前面k个负数转化为正数即可
//如果负数的个数小于k，则将所有的负数转化为正数，剩下的k-n如果为偶数，则直接返回所有的和
//如果为奇数，则判断最大的负数和最小的正数(或为0)的绝对值大小，将绝对值小的转化为负数（或为0，可以统一表达）后求和
#include<vector>
#include<algorithm>

int largestSumAfterKNegations(std::vector<int>& nums, int k) {
    std::sort(nums.begin(), nums.end());
    int neg_count = 0;//负数的个数
    int none_neg_idx = -1;//有可能所有的数都是负数
    int sum = 0;
    for(int i = 0 ; i < nums.size(); i++)
    {
        if(nums[i] < 0){
            neg_count++;
        }else{
            none_neg_idx = i;
            break;
        }
    }
    //负数翻转次数
    int flip_count = neg_count >= k? k :neg_count;
    int i = 0;
    //包含flip_count=0的情况
    while(i < flip_count)
    {
        nums[i] = -nums[i];
        //flip_count--;
        i++;
    }
    for(int i =0; i < nums.size(); i++)
    {
        sum += nums[i];
    }
    if(flip_count == 0 && k%2 == 0)
    {
        //直接求和
        return sum;
    }else if(flip_count >=k){
        //k-flip_count
        //已经翻转，直接求和
        return sum;
    }else{
        //k更大，所有的负数都转为了正数，如果此时剩下的翻转次数为偶数，则直接求和
        if((k-flip_count)%2 == 0)
        {
            return sum;
        }else{
            //如果none_neg_idx=0时，需要,注意这里是2
            if(none_neg_idx == -1)//所有的数都是负数
            {
                sum -= 2*nums.back();
            }            
            else if(none_neg_idx == 0)
            {
                sum -= 2*nums[none_neg_idx];
            }
            else if(nums[none_neg_idx] < nums[none_neg_idx-1])
            {
                sum -= 2*nums[none_neg_idx];
            }else{
                sum -= 2*nums[none_neg_idx-1];
            }
            return sum;
        }
    }
    return sum;
}


int main()
{
    //std::vector<int>nums={3,-1,0,2};
    //std::vector<int>nums={2,-3,-1,5,-4};
    //std::vector<int>nums={4, 2, 3};
    std::vector<int>nums={-4,-2,-3};
    int k = 4;
    int res = largestSumAfterKNegations(nums, k);
    return 0;
}