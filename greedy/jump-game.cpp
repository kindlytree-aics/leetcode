/*

https://leetcode.cn/problems/jump-game/

给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。

 

示例 1：

输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
示例 2：

输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
 

提示：

1 <= nums.length <= 3 * 104
0 <= nums[i] <= 105
*/
#include<vector>

//如果第一个元素大于数组的长度，则可以一步直接跳到
//否则计算当前可以跳到最远的位置，如[2,3,1,1,4]
//第一个元素可以达到下标2，可以包含第二个元素，第二个元素可以达到末尾，结束
//[3,2,1,0,4],第一个元素最远达到下标3，可以包含第二个元素，第二个元素最远达到下标3，
//包含第三个元素，第三个元素可以达到下标3，包含第四个元素，第四个元素为0，还是最远达到下表3，不包含第五个元素了
//因此不能到达终点；
bool canJump(std::vector<int>& nums) {
    //第一个元素不能跳，肯定就不能跳了
    if(nums[0] == 0 && nums.size() == 1) return true;
    if(nums[0] == 0 && nums.size() > 1 ) return false;
    int farthest_ = nums[0];
    for(int i = 1; i < nums.size(); i++)
    {
        if(farthest_ >= i)//可以跳到第i个元素，继续可以从第i个元素开始起跳
        {
            if(nums[i]+i >farthest_)//第i个元素起跳后能到达的最远位置
            {
                farthest_ = nums[i]+i;
            }
            //else{//否则farthest保持不变
            //}
        }else{//最远位置不能到达i了，不能从i起跳了
            return false;
        }
        if(farthest_ >= nums.size()-1)
        {
            return true;
        }
    }
    return true;
}

int main()
{
    //std::vector<int>nums={2,3,1,1,4};
    std::vector<int>nums={1,2};
    bool can_jump = canJump(nums);
    return 0;
}