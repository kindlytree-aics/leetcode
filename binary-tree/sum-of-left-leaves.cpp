/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/sum-of-left-leaves

给定二叉树的根节点 root ，返回所有左叶子之和。

示例 1：
输入: root = [3,9,20,null,null,15,7] 
输出: 24 
解释: 在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24


示例 2:
输入: root = [1]
输出: 0

提示:

节点数在 [1, 1000] 范围内
-1000 <= Node.val <= 1000
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>



void sumOfLeftLeaves(TreeNode* root, TreeNode* parent, int& sum) {
    if(root && !root->left && !root->right){
        if(parent->left == root)
        {
            sum += root->val;
        }
    }else{
        if(root->left){
            sumOfLeftLeaves(root->left, root, sum);
        }
        if(root->right){
            sumOfLeftLeaves(root->right, root, sum);
        }
    }
}

//层序遍历，判断每一个叶子节点是否是左叶子几点
int sumOfLeftLeavesv0(TreeNode* root) {
    int sum_of_left_leaves_ = 0;
    std::queue<TreeNode*> queue_;
    if(root)
    {
        if(!root->left && !root->right){
            return 0;
        }
        queue_.push(root);
    }
    while(!queue_.empty())
    {
        TreeNode* cur_node_ = queue_.front();
        queue_.pop();
        if(cur_node_->left)
        {
            if(!cur_node_->left->left && !cur_node_->left->right)
            {
                //left leaf node;
                sum_of_left_leaves_ += cur_node_->left->val;
            }else{
                queue_.push(cur_node_->left);
            }
        }
        if(cur_node_->right)
        {
            if(!cur_node_->right->left && !cur_node_->right->right)
            {
                //right leaf node;
                //sum_of_left_leaves_ += cur_node_->left->val;
            }else{
                queue_.push(cur_node_->right);
            }                
        }
    }
    return sum_of_left_leaves_;
}

int main(){
    //std::vector<int> root = {3,9,NULL,NULL,20,15, NULL, NULL, 7, NULL, NULL};
    std::vector<int> root = {1,2,4,NULL,NULL, NULL,3, NULL,5, NULL, NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    int sum = 0;
    sumOfLeftLeaves(root_node_, root_node_, sum);
    return 0;

    //int result = sumOfLeftLeavesv0(root_node_);
    //std::cout << result << std::endl;
}