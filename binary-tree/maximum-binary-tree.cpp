/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/maximum-binary-tree

给定一个不重复的整数数组 nums 。 最大二叉树 可以用下面的算法从 nums 递归地构建:

创建一个根节点，其值为 nums 中的最大值。
递归地在最大值 左边 的 子数组前缀上 构建左子树。
递归地在最大值 右边 的 子数组后缀上 构建右子树。
返回 nums 构建的 最大二叉树 。

 

示例 1：


输入：nums = [3,2,1,6,0,5]
输出：[6,3,5,null,2,0,null,null,1]
解释：递归调用如下所示：
- [3,2,1,6,0,5] 中的最大值是 6 ，左边部分是 [3,2,1] ，右边部分是 [0,5] 。
    - [3,2,1] 中的最大值是 3 ，左边部分是 [] ，右边部分是 [2,1] 。
        - 空数组，无子节点。
        - [2,1] 中的最大值是 2 ，左边部分是 [] ，右边部分是 [1] 。
            - 空数组，无子节点。
            - 只有一个元素，所以子节点是一个值为 1 的节点。
    - [0,5] 中的最大值是 5 ，左边部分是 [0] ，右边部分是 [] 。
        - 只有一个元素，所以子节点是一个值为 0 的节点。
        - 空数组，无子节点。
示例 2：


输入：nums = [3,2,1]
输出：[3,null,2,null,1]
 

提示：

1 <= nums.length <= 1000
0 <= nums[i] <= 1000
nums 中的所有整数 互不相同

*/


#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>
#include <queue>
#include <unordered_map>

TreeNode* constructMaximumBinaryTreeRecursive(std::vector<int>& nums, int left, int right)
{
    if(left == right){
        TreeNode* node = new TreeNode(nums[left]);
        return node;
    }else{
        int idx = left, max_value_ = nums[left];
        for(int i = left; i <= right; i++)
        {
            if(max_value_ < nums[i])
            {
                idx = i;
                max_value_ = nums[i];
            }
        }
        TreeNode* node = new TreeNode(nums[idx]);
        if(idx-1 >= left)
        {
            node->left = constructMaximumBinaryTreeRecursive(nums, left, idx-1);
        }
        if(idx+1 <= right)
        {
            node->right = constructMaximumBinaryTreeRecursive(nums, idx+1, right);
        }
        return node;
    }
}

TreeNode* constructMaximumBinaryTree(std::vector<int>& nums) {
    TreeNode* node = constructMaximumBinaryTreeRecursive(nums, 0, nums.size()-1);
    return node;
}


int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> root = {3,2,1,6,0,5};
    //TreeNode* root_node_ = buildBinaryTree(root);
    //bool is_balanced = isBalanced(root_node_);
    TreeNode* root_node_ = constructMaximumBinaryTree(root);
    //std::cout << is_balanced << std::endl;
}