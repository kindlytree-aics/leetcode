/*
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/4sum-ii

给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l) 能满足：

0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 

示例 1：

输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
输出：2
解释：
两个元组如下：
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
示例 2：

输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
输出：1
 

  提示：

n == nums1.length
n == nums2.length
n == nums3.length
n == nums4.length
1 <= n <= 200
-228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228
*/

#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;


int fourSumCountv1(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    std::unordered_map<int, int> ab_sum_map;
    int count = 0;
    for(int i = 0 ; i < nums1.size(); i++)
    {
        for(int j = 0; j < nums2.size(); j++)
        {
            int sum=nums1[i]+nums2[j];
            auto iter = ab_sum_map.find(sum);
            if(iter != ab_sum_map.end())
            {
                iter->second++;
            }else
            {
                ab_sum_map.insert(pair<int,int>(sum, 1));
            }
        }
    }
    for(int i = 0; i < nums3.size(); i++)
    {
        for(int j =0; j < nums4.size(); j++)
        {
            int sum = nums3[i] + nums4[j];
            auto iter = ab_sum_map.find(-sum);
            if(iter != ab_sum_map.end())
            {
                count += iter->second;
            }
        }
    }
    return count;
}


//在使用map的[]操作符对其进行访问时，如果map中尚没有查询的key值，则将创建一个新的键值对。其key值为查询的值，value值分为以下两种情况：
//value为内置类型时，其值将被初始化为0
//value为自定义数据结构时，如果定义了默认值则初始化为默认值，否则初始化为0
//参考https://blog.csdn.net/code_star_one/article/details/94394094 

int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int, int> ab_sum_map; //key:a+b的数值，value:a+b数值出现的次数
    // 遍历大nums1和大nums2数组，统计两个数组元素之和，和出现的次数，放到map中
    for (int a : nums1) {
        for (int b : nums2) {
            ab_sum_map[a + b]++;
        }
    }
    int count = 0; // 统计a+b+c+d = 0 出现的次数
    // 在遍历大nums3和大nums4数组，找到如果 0-(c+d) 在map中出现过的话，就把map中key对应的value也就是出现次数统计出来。
    for (int c : nums3) {
        for (int d : nums4) {
            if (ab_sum_map.find(0 - (c + d)) != ab_sum_map.end()) {
                count += ab_sum_map[0 - (c + d)];
            }
        }
    }
    return count;
}

int main()
{

    vector<int>nums1 = {1,2}, nums2 = {-2,-1}, nums3 = {-1,2}, nums4 = {0,2};
    int count = fourSumCount(nums1, nums2, nums3, nums4);
    cout << count << endl;
    return 0;
}

