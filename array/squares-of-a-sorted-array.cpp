/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/squares-of-a-sorted-array

给你一个按 非递减顺序 排序的整数数组 nums，返回每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

示例 1：

输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]
示例 2：

输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
 

提示：

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 已按 非递减顺序 排序

进阶：

请你设计时间复杂度为 O(n) 的算法解决本问题
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> squares_of_a_sorted_array(vector<int>nums)
{
    int nsize = nums.size();
    int left =0, right = nsize-1;
    int index = nsize-1;
    vector<int> sorted_squares_nums(nsize, 0);
    int square_left = nums[left]*nums[left];
    int square_right = nums[right]*nums[right];
    while(index >=0)
    {   
        //目标数组从最后一个元素(最大的元素)开始放置
        //当前最大的元素是在索引left,或right
        //通过比较其值的大小，将大的放到index(index从数组最末一位开始逆序)位置
        //并进行对应的left或right的移动
        //如果左边的大，将当前值放到数组left向右移动
        //反之，right向左移动
        if(square_left >= square_right)
        {
            sorted_squares_nums[index] = square_left;
            index--;
            left++;
            //如果数组全为负值，则此时最后一个元素left会超过数组长度 
            if(left < nsize)
            {
                square_left = nums[left]*nums[left];
            } 
            
        }else{
            sorted_squares_nums[index] = square_right;
            index--;
            right--;
            //如果数组全为正值，则此时最后一个元素right会出现负值 
            if (right >= 0)
            {
                square_right = nums[right]*nums[right];
            }          
        }
    }
    return sorted_squares_nums;
}

int main()
{
    //vector<int>nums={-4,-1,0,3,10};
    vector<int>nums={1,3,5,7,10};
    vector<int> sorted_squares_nums = squares_of_a_sorted_array(nums);
    for(int i = 0; i < sorted_squares_nums.size();i++)
    {
        cout << sorted_squares_nums[i] << endl;
    }
    return 0;
}