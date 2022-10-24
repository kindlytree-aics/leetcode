
/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal

给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

示例 1:

输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
示例 2:

输入: preorder = [-1], inorder = [-1]
输出: [-1]
 
提示:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder 和 inorder 均 无重复 元素
inorder 均出现在 preorder
preorder 保证 为二叉树的前序遍历序列
inorder 保证 为二叉树的中序遍历序列
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
# include <algorithm>

//从前序和中序遍历序列
//前序的第一个节点为根节点，到中序遍历的结果中去找到该节点索引(左边为左子树，假设长度为l，右边为右子树)
//再从前序遍历中将1-l个元素作为左子树（因为前序遍历中左子树的元素均在右子树前面），后面的元素作为右子树
//找到了对应的左子树和右子树的子数组后，递归调用即可
int findValueIndex(std::vector<int>&nums, int value)
{
    for(int i = 0; i < nums.size(); i++)
    {
        if(nums[i] == value)
        {
            return i;
        }
    }
    return -1;
}

TreeNode* buildTreeRecursive( std::vector<int>& preorder, \
                                int preorder_begin_,
                                int preorder_end_,
                                std::vector<int>& inorder,
                                int inorder_begin_,
                                int inorder_end_) 
{
    if(preorder.size() == 0) return NULL;
    int root_val_ = preorder[preorder_begin_];
    TreeNode* node= new TreeNode(root_val_);
    if(preorder_begin_ == preorder_end_){return node;}

    int inorder_root_idx_ = findValueIndex(inorder, root_val_);
    if(inorder_root_idx_ == inorder_begin_)//左子树为空
    {
        node->right = buildTreeRecursive(preorder, preorder_begin_+1, preorder_end_, inorder, inorder_begin_+1, inorder_end_);
        return node;
    }
    else{
        //preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
        int preorder_begin_left_child_ = preorder_begin_+1;
        int j = preorder_begin_left_child_;
        int preorder_end_left_child_ = preorder_begin_left_child_+inorder_root_idx_-inorder_begin_-1;
        int inorder_begin_left_child_ = inorder_begin_;
        int inorder_end_left_child_ = inorder_root_idx_-1;
        int preorder_begin_right_child_ = preorder_end_left_child_+1, preorder_end_right_child_=preorder_end_;
        int inorder_begin_right_child_ = inorder_root_idx_+1, inorder_end_right_child_ = inorder_end_;

        node->left = buildTreeRecursive(preorder, preorder_begin_left_child_, preorder_end_left_child_, inorder, inorder_begin_left_child_, inorder_end_left_child_);
        if(preorder_begin_right_child_ <= preorder_end_)
        {
            node->right = buildTreeRecursive(preorder, preorder_begin_right_child_, preorder_end_right_child_, inorder, inorder_begin_right_child_, inorder_end_right_child_);
        }
        return node;
    }
}

TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) {
    //buildTreeRecursive
    //inorder.find
    //buildTreeLeft();
    //buildTreeRight();
}



int main(){
    //std::vector<int> root = {3,1,NULL,NULL,2};
    //std::vector<int>inorder = {9,3,15,20,7}, postorder = {9,15,7,20,3};
    //TreeNode* root_node_ = buildTree(inorder, postorder);
    //std::vector<int>preorder = {3,9,20,15,7}, inorder = {9,3,15,20,7};
    //std::vector<int>preorder = {1,2}, inorder = {2,1};
    std::vector<int>preorder = {1,2,3}, inorder = {3,2,1};
    //std::vector<int>preorder = {1,2,3}, inorder = {1,2,3};
    TreeNode* root_node_ = buildTreeRecursive(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    return 0;
}