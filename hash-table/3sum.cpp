/*
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/3sum

给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请

你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
示例 2：

输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
示例 3：

输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。
 
提示：
3 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/

#include<vector>
#include<unordered_map>
#include<iostream>
#include<algorithm>

using namespace std;

//比较原始的写法：判断是否时重复的元组
//如果元组元素相同（数序可能不同），则返回true
bool duplicate(vector<int>nums1, vector<int>nums2)
{
    int count = 0;
    vector<bool>equaled(nums1.size(),0);
    for(int i =0; i< nums1.size(); i++)
    {
        for(int j =0; j < nums2.size(); j++)
        {
            if(nums1[i] == nums2[j] && equaled[j] ==false)
            {
                count +=1;
                equaled[j] = true;
                break;
            }
        }
    }
    return count == 3;
}

//比较暴力的方法，不建议
vector<vector<int>> threeSumv1(vector<int>& nums) {
    std::unordered_map<int, vector<int>>sum_idx_map;
    for(int i =0; i < nums.size(); i++)
    {
        for(int j = i+1; j < nums.size(); j++)
        {
            int sum = nums[i] + nums[j];
            for(int k = 0 ; k < sum_idx_map[sum].size(); k+=2)
            {
                if(nums[sum_idx_map[sum][k]] == nums[i] || nums[sum_idx_map[sum][k+1]] == nums[i])
                {
                    continue;
                }
            }
            sum_idx_map[sum].push_back(i);
            sum_idx_map[sum].push_back(j);
        }
    }
    vector<vector<int>> result_tuple;
    for(int k = 0; k < nums.size(); k++)
    {   
        int num = nums[k];
        auto iter = sum_idx_map.find(-num);
        if( iter != sum_idx_map.end())
        {
            vector<int>two_sums_tuple = iter->second;
            for(int s = 0; s < two_sums_tuple.size(); s+=2)
            {
                int i = two_sums_tuple[s];
                int j = two_sums_tuple[s+1];
                if( k != i && k != j)
                {
                    bool is_duplicate = false;
                    for(int m = 0; m < result_tuple.size(); m++)
                    {
                        is_duplicate = duplicate(result_tuple[m], {nums[i], nums[j], nums[k]});
                        if(is_duplicate == true)
                        {
                            break;
                        }
                    }
                    if(!is_duplicate)
                    {
                        result_tuple.push_back({nums[i], nums[j], nums[k]});
                    }
                }
            }
        }
    }
    return result_tuple;
}

//首先对数组进行排序，用双指针（索引）的方式进行
//假设a+b+c=0，a为最小的，b为中间，c为最大的
//如果第一个元素a都大于0，则不满足条件，后续的b和c就不需要再遍历了
//第一个元素有从左边第一个元素开始尝试，b(left)和c(right)的指针分别指向第一个元素的右边一个和最后一个
//如果a+b+c>0,则right向左移动，小于0时向右移动
//等于0时，left向右移动（如果left移动时b值不变化，则持续移动），对应的right则会向左移动
//直至left=right跳出当前的a值，开始下一个a值去遍历新的可能的元组
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>>result;
    for(int i =0; i < nums.size(); i++)
    {
        int a = nums[i];
        if(a > 0)
        {
            return result;
        }
        if(i >= 1 &&  nums[i] == nums[i-1]){continue;}
        int left = i+1, right = nums.size()-1;
        while(left < right)
        {
            int  b = nums[left], c = nums[right];
            if(a+b+c == 0)
            {
                result.push_back({nums[i], nums[left], nums[right]});
                while(nums[++left] == b && left < right);
            }
            else if(a+b+c > 0)
            {
                right--;
            }else{
                left++;
            }
        }
    }
    return result;
}


int main()
{
    //vector<int>nums = {-1,0,1,2,-1,-4};
    vector<int>nums = {0,0,0,0};
    vector<vector<int>> tuples = threeSum(nums);
    for(auto tuple:tuples)
    {
        for(auto item: tuple)
        {
            cout << item << " ";
        }
        cout << endl;
    }
    return 0;
}
