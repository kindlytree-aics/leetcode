/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/4sum
给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。

 

示例 1：

输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
示例 2：

输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]
 

提示：

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109
*/

#include<vector>
#include<unordered_map>
#include<iostream>
#include<algorithm>

using namespace std;

//首先对数组进行排序，用双指针（索引）的方式进行
//假设a+b+c=0，a为最小的，b为中间，c为最大的
//如果第一个元素a都大于0，则不满足条件，后续的b和c就不需要再遍历了
//第一个元素有从左边第一个元素开始尝试，b(left)和c(right)的指针分别指向第一个元素的右边一个和最后一个
//如果a+b+c>0,则right向左移动，小于0时向右移动
//等于0时，left向右移动（如果left移动时b值不变化，则持续移动），对应的right则会向左移动
//直至left=right跳出当前的a值，开始下一个a值去遍历新的可能的元组
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>>result;
    if(nums.size() < 4){return result;}
    for(int i = 0; i <= nums.size()-4; i++)
    {
        int a = nums[i];
        if(a > 0 && a > target){return result;}
        if(i >=1 && nums[i] == nums[i-1]){continue;}
        for(int j = i+1; j<= nums.size()-3; j++)
        {
            int b = nums[j], sum_ab = a+b;
            if(j > i+1 && nums[j] == nums[j-1]){continue;}
            if((long)a+b+b+b > target){
                break;
            }
            else{
                int c_index = j+1, d_index = nums.size()-1;
                while(c_index < d_index)
                {
                    int c = nums[c_index], d = nums[d_index];
                    long sum_abcd = (long)sum_ab+c+d;
                    if(sum_abcd == target){
                        result.push_back({a,b,c,d});
                        while(++c_index < d_index && c == nums[c_index]);
                    }else if(sum_abcd > target)
                    {
                        d_index--;
                    }else{
                        c_index++;
                    }
                }
            }
        }
    }
    return result;
}


int main()
{
    //vector<int>nums = {2,2,2,2,2};
    //vector<int>nums = {1000000000,1000000000,1000000000,1000000000};
    //vector<vector<int>> tuples = fourSum(nums, 0);
    vector<int>nums = {1,-2,-5,-4,-3,3,3,5};
    vector<vector<int>> tuples = fourSum(nums, -11);
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
