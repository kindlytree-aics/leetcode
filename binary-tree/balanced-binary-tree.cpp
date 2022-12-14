/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/balanced-binary-tree

给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：true
示例 2：

输入：root = [1,2,2,3,3,null,null,4,4]
输出：false
示例 3：

输入：root = []
输出：true

提示：

树中的节点数在范围 [0, 5000] 内
-104 <= Node.val <= 104
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>
#include <queue>
#include <unordered_map>

//就是求二叉树的层数，和层序遍历的思想类似；在这里就暂时不重复写了


//下面的代码采用后序遍历的非递归方式实现，求得每一个节点得层数（高度），并将左右子节点的高度进行比较
bool isBalancedv0(TreeNode* root) {
    std::stack<TreeNode*>stack_;
    std::unordered_map<TreeNode*, int>node_depth_map_;
    if(root){
        stack_.push(root);
    }
    while(!stack_.empty())
    {
        TreeNode* cur_node_ = stack_.top();
        stack_.pop();
        if(cur_node_)
        {
            stack_.push(cur_node_);
            stack_.push(nullptr);
        }else{
            cur_node_ = stack_.top();
            stack_.pop();
            if(!cur_node_->left && !cur_node_->right){//左右子树均为空，叶子节点，记深度为1，这里不以树的根节点去记录深度
                node_depth_map_[cur_node_] = 1;
            }else if(cur_node_->left && cur_node_->right){//左右子树均不为空的情况
                int left_depth_ = node_depth_map_[cur_node_->left];
                int right_depth_ = node_depth_map_[cur_node_->right];
                if(abs(left_depth_-right_depth_) >= 2){
                    return false;
                }
                node_depth_map_[cur_node_] = (left_depth_ > right_depth_ ? left_depth_: right_depth_) + 1;
            }else{
                if(cur_node_->left && node_depth_map_[cur_node_->left] > 1)//右子树为空且左子树的深度大于1，高度差大于1
                {
                    return false;
                }
                if(cur_node_->right && node_depth_map_[cur_node_->right] > 1)//左子树为空且右子树的深度大于1，高度差大于1
                {
                    return false;
                }else{
                    node_depth_map_[cur_node_] = 2;//有左树或右子树，且存在的那个子节点的深度为1，当前节点的深度变为2
                }
            }
            continue;
        }
        if(cur_node_->right)
        {
            stack_.push(cur_node_->right);
        }
        if(cur_node_->left)
        {
            stack_.push(cur_node_->left);
        }
    }
    return true;
}

//后序递归求解
bool nodeHeight(TreeNode* root, int& height)
{
    if(!root) 
    {
        height = 0;
        return true;
    }
    int left_height, right_height;
    if(!nodeHeight(root->left, left_height))return false;
    if(!nodeHeight(root->right, right_height))return false;
    int height_diff = abs(left_height-right_height);
    if(height_diff >= 2)
    {
        return false;
    }
    height = std::max(left_height, right_height) + 1;
    return true;
}

bool isBalanced(TreeNode* root) {
    int height;
    bool is_balanced = nodeHeight(root, height);
    return is_balanced; 
}


int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> root = {1, NULL, 2, NULL,3,NULL, NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    bool is_balanced = isBalanced(root_node_);
    std::cout << is_balanced << std::endl;
}