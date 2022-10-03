/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/symmetric-tree

给你一个二叉树的根节点 root ， 检查它是否轴对称。

示例 1：

输入：root = [1,2,2,3,4,4,3]
输出：true
示例 2：

输入：root = [1,2,2,null,3,null,3]
输出：false
 
提示：

树中节点数目在范围 [1, 1000] 内
-100 <= Node.val <= 100
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
//#include <stack>
#include <queue>

bool isSymmetric(TreeNode* root) {
    std::queue<TreeNode*> queue_;
    if(root)
    {
        if(root->left && root->right)
        {
            queue_.push(root->left);
            queue_.push(root->right);
        }else if(!root->left && !root->right){
            return true;
        }else{
            return false;
        }
    }
    while(!queue_.empty())
    {
        TreeNode* child_left = queue_.front();
        queue_.pop();
        TreeNode* child_right = queue_.front();
        queue_.pop();

        if(child_left && child_right){
            if(child_left->val != child_right->val)
            {
                return false;
            }
            queue_.push(child_left->left);
            queue_.push(child_right->right);
            queue_.push(child_left->right);
            queue_.push(child_right->left);
        }else if(!child_left && !child_right)
        {
            continue;
        }else{
            return false;
        }
    }
    return true;
}

bool isSymmetricTwoTrees(TreeNode* root1, TreeNode* root2)
{
    if(root1 && root2)
    {
        bool is_symmetric1 = isSymmetricTwoTrees(root1->left, root2->right);
        bool is_symmetric2 =  isSymmetricTwoTrees(root1->right, root2->left);
        bool is_equal_ = root1->val == root2->val;
        if(is_symmetric1 && is_symmetric2 && is_equal_)
        {
            return true;
        }else{
            return false;
        }
    }else if(!root1 && !root2)
    {
        return true;
    }else{
        return false;
    }
}

bool isSymmetricRecursive(TreeNode* root) {
    if(root)
    {
       bool is_symmetric =  isSymmetricTwoTrees(root->left, root->right);
       return is_symmetric;
    }else{
        return true;
    }
}


int main(){
    std::vector<int> root = {1,2,2,3,4,4,3};
    TreeNode* root_node_ = buildBinaryTree(root);
    bool is_symmetric_ = isSymmetric(root_node_);
    std::cout << is_symmetric_ << std::endl;
}