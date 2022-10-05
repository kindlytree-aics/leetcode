/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal

给定两个整数数组 inorder 和 postorder ，
其中 inorder 是二叉树的中序遍历， 
postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。

示例 1:

输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
输出：[3,9,20,null,null,15,7]
示例 2:

输入：inorder = [-1], postorder = [-1]
输出：[-1]
 
提示:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder 和 postorder 都由 不同 的值组成
postorder 中每一个值都在 inorder 中
inorder 保证是树的中序遍历
postorder 保证是树的后序遍历
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
# include <algorithm>

//后续遍历中最后一个元素为根节点
//到中序遍历的结果中找到该节点，为树的根节点
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

TreeNode* buildTreeRecursive( std::vector<int>& inorder, std::vector<int>& postorder) {
    if(inorder.size() == 0) return NULL;
    int root_val_ = postorder.back();
    TreeNode* node= new TreeNode(root_val_);
    int root_index =  findValueIndex(inorder, root_val_);

    std::vector<int>left_child_inorder_;
    //左闭右开区间
    //也可以这么写：vector<int> left_child_inorder_(inorder.begin(), inorder.begin() + root_index);
    left_child_inorder_.assign(inorder.begin(), inorder.begin()+root_index);
    std::vector<int>right_child_inorder_;
    right_child_inorder_.assign(inorder.begin()+root_index+1, inorder.end());
    std::vector<int>left_child_postorder_;
    left_child_postorder_.assign(postorder.begin(), postorder.begin()+root_index);
    std::vector<int>right_child_postorder_;
    right_child_postorder_.assign(postorder.begin()+root_index, postorder.end()-1);
    node->left = buildTreeRecursive(left_child_inorder_, left_child_postorder_);
    node->right = buildTreeRecursive(right_child_inorder_, right_child_postorder_);
    return node;
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
    std::vector<int>inorder = {1,2}, postorder = {2,1};
    TreeNode* root_node_ = buildTreeRecursive(inorder, postorder);
    return 0;
}