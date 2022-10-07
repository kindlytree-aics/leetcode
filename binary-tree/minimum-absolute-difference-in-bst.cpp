/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-absolute-difference-in-bst

给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。

差值是一个正数，其数值等于两值之差的绝对值。

示例 1：

输入：root = [4,2,6,1,3]
输出：1
示例 2：

输入：root = [1,0,48,null,null,12,49]
输出：1

提示：

树中节点的数目范围是 [2, 104]
0 <= Node.val <= 105
*/
#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>
#include <queue>

//中序遍历递增,相邻的两个元素的差值比较小，最小值在其中产生。
void inorderTraverse(TreeNode* root, std::vector<int>&inorder){
    if(root){
        if(root->left){
            inorderTraverse(root->left, inorder);
        }
        inorder.push_back(root->val);
        if(root->right)
        {
            inorderTraverse(root->right, inorder);
        }
    }else{
        return;
    }
}

int getMinimumDifference(TreeNode* root) {
    std::vector<int> inorder;
    inorderTraverse(root, inorder);
    int min = inorder[1]-inorder[0];
    for(int i =2; i< inorder.size(); i++)
    {
        int diff_ = inorder[i]-inorder[i-1];
        if(diff_ < min)
        {
            min = diff_;
        }
    }
    return min;
}

int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> root = {4,2,1,NULL,NULL,3, NULL,NULL,6,NULL,NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    //bool is_balanced = isBalanced(root_node_);
    int min_diff_ = getMinimumDifference(root_node_);
    //std::cout << is_balanced << std::endl;
}