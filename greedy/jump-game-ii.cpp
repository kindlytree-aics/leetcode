/*
https://leetcode.cn/problems/jump-game-ii/
给你一个非负整数数组 nums ，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

假设你总是可以到达数组的最后一个位置。

 

示例 1:

输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
示例 2:

输入: nums = [2,3,0,1,4]
输出: 2
 

提示:

1 <= nums.length <= 10^4
0 <= nums[i] <= 1000
*/

//nums = [2,3,1,1,4]
//本题关键时求最少步骤
//每跳到一个位置如nums[i]=n，可以有对应的n中跳法，如1,2,..n,相当于构建了一颗可变子节点的搜索树
//通过递归求解可行跳法，然后找出最少的步骤的解法，当然可以考虑进行修枝剪枝

#include<vector>
#include<unordered_map>

//贪婪算法，根据每一步能走到的最远位置，如果哪一步能走到的最远位置达到末尾，则返回。
int jumpv0(std::vector<int>& nums) {
    //第一个元素不能跳，肯定就不能跳了
    if(nums.size() == 1) return 0;
    int farthest_ = nums[0];
    //std::vector<int>min_steps(nums.size(),0);
    //std::unordered_map<int, std::vector<int>>step_paths;//第几步能到达的位置
    int step = 1;
    int cur_left = 1, cur_right = farthest_;
    while(farthest_ < nums.size()-1)
    {
        for(int i = cur_left; i <= cur_right; i++)
        {
            //step_paths[step].push_back(i);
            if(nums[i]+i >farthest_)//第step+1步能走的最远位置
            {
                farthest_ = nums[i]+i;
                //path.push_back(i);
            }
        }
        step += 1;
        cur_left = cur_right+1;//下一步的范围更新
        cur_right = farthest_;
    }
    return step;
}


//递归搜索树求解
void jumpv1(std::vector<int>& nums, int i, std::vector<int>path, int& min_steps, std::unordered_map<int, int>&pos_min_steps) {
    int steps_ = nums[i];
    if(path.size() >= min_steps-1){return;}//修枝剪枝，不是更好的解法时不用再考虑
    //同理
    for(int s = steps_; s >= 1; s--)
    {
        //steps种跳法
        path.push_back(s);
        int next_candidate_pos = i+s;
        if(next_candidate_pos >= nums.size()-1)
        {
            if(path.size() < min_steps)
            {
                min_steps = path.size();
            }
        }else{
            if(pos_min_steps[next_candidate_pos] == 0)//第一次跳法
            {
                pos_min_steps[next_candidate_pos] = path.size();
                jumpv1(nums, next_candidate_pos, path, min_steps, pos_min_steps);
            }else if(pos_min_steps[next_candidate_pos] > path.size())
            {
                //只有到达当前位置的步骤更少的才可以考虑从当前位置继续往后跳
                pos_min_steps[next_candidate_pos] = path.size();
                jumpv1(nums, next_candidate_pos, path, min_steps, pos_min_steps);
            }
            //开始下一次跳，递归调用
        }
        //回溯，退出当前跳法，尝试下一种；
        path.pop_back();
    }
}

//该方法尽可能走最大步骤，但不能保证最优解
bool jumpv2(std::vector<int>& nums, int i, std::vector<int>path, int& min_steps) {
    int steps_ = nums[i];
    //if(path.size() >= min_steps-1){return;}//修枝剪枝，不是更好的解法时不用再考虑
    //
    for(int s = steps_; s >= 1; s--)
    {
        //steps种跳法
        path.push_back(s);
        int next_candidate_pos = i+s;
        if(next_candidate_pos >= nums.size()-1)
        {
            if(path.size() < min_steps)
            {
                min_steps = path.size();
                return true;
            }
        }else{
            if(jumpv2(nums, next_candidate_pos, path, min_steps))return true;
            //开始下一次跳，递归调用
        }
        //回溯，退出当前跳法，尝试下一种；
        path.pop_back();
    }
    return false;
}


int jump(std::vector<int>& nums) {
    int min_steps = nums.size()-1;
    std::vector<int>path;
    if(nums[0] == 0 || nums.size() == 1) return 0;
    std::unordered_map<int, int>pos_min_steps;//跳到同等位置时最少步骤
    jumpv1(nums, 0, path, min_steps, pos_min_steps);
    return min_steps;
}

int main()
{
    std::vector<int>nums = {2,3,1,1,4};
    int min_steps = jumpv0(nums);
    return 0;
}