/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/intersection-of-two-arrays
给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。

示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]
示例 2：

输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
解释：[4,9] 也是可通过的
 
提示：

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
*/
#include<iostream>
#include<vector>
#include<string>
#include <unordered_set>

using namespace std;

//用根据题目的提示用比较直观的方式实现，空间复杂度比较高
vector<int> intersection_v1(vector<int>& nums1, vector<int>& nums2) 
{
    vector<int>nums_count_a(1001, 0);
    vector<int>nums_count_b(1001, 0);
    vector<int>intersection;
    for(int i = 0; i< nums1.size(); i++)
    {
        nums_count_a[nums1[i]]++;
    }
    for(int i = 0; i< nums2.size(); i++)
    {
        nums_count_b[nums2[i]]++;
    }
    for(int i =0; i < 1001; i++)
    {
        if(nums_count_a[i] >0 && nums_count_b[i] > 0)
        {
            intersection.push_back(i);
        }
    }
    return intersection;    
}

/*
std::set和std::multiset底层实现都是红黑树，

multiset是<set>库中一个非常有用的类型，
它可以看成一个序列，插入一个数，删除一个数都能够在O(logn)的时间内完成，
而且他能时刻保证序列中的数是有序的，而且序列中可以存在重复的数

std::unordered_set的底层实现是哈希表， 
使用unordered_set 读写效率是最高的，并不需要对数据进行排序，
而且还不要让数据重复，所以选择unordered_set。
*/
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    //unordered_set容器内部存储的各个元素的值都互不相等，且不能被修改
    unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
    unordered_set<int> nums_set(nums1.begin(), nums1.end());
    //c++11新语法
    //还可以写成std::for_each(arr.begin(), arr.end(), func);
    for (int num : nums2) {
        // 发现nums2的元素 在nums_set里又出现过
        if (nums_set.find(num) != nums_set.end()) {
            result_set.insert(num);
        }
    }
    return vector<int>(result_set.begin(), result_set.end());
}


int main()
{
    vector<int>nums1 = {4,9,5};
    vector<int>nums2 = {9,4,9,8,4};

    vector<int>common_set = intersection(nums1, nums2);
    for(int i= 0; i < common_set.size(); i++)
    {
        cout << common_set[i] << " ";
    }
    return 0;
}
