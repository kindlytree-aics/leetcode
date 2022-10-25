/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree

给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 二叉搜索树。

高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

示例 1：

输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：

示例 2：


输入：nums = [1,3]
输出：[3,1]
解释：[1,null,3] 和 [3,1] 都是高度平衡二叉搜索树。
 

提示：

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 按 严格递增 顺序排列
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

//数组的中间值作为根节点，左边的为左子树，右边的为右子树
//再对左边和右边的子树分别递归调用上述流程，这样的二叉搜索时是平衡的

TreeNode* buildSortedArrayToBst(std::vector<int>& nums, int left, int right)
{
    if(left > right || nums.size() == 0) return nullptr;
    int middle = left + (right-left)/2;
    TreeNode* node = new TreeNode(nums[middle]);
    if(left == right)
    {
        return node;
    }else
    {
        node->left = buildSortedArrayToBst(nums, left, middle-1);
        node->right = buildSortedArrayToBst(nums, middle+1, right);
    }
    return node;
}

TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    //int 
    TreeNode* node = buildSortedArrayToBst(nums, 0, nums.size()-1);
    return node;
}

int main(){
    //std::vector<int> root = {3,0,4,NULL,2,NULL,NULL,1};
    std::vector<int> nums = {-10,-3,0,5,9};
    //TreeNode* root_node_ = buildBinaryTree(root);
    //[3,0,4,null,2,null,null,1]
    //1
    //3
    TreeNode* root_node_ = sortedArrayToBST(nums);
    std::cout << std::endl;
}