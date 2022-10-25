/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/invert-binary-tree

给你一棵二叉树的根节点 root ，翻转这棵二叉树（树的左右子树对调），并返回其根节点。

示例 1：

输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]
示例 2：

输入：root = [2,1,3]
输出：[2,3,1]
示例 3：

输入：root = []
输出：[]
 
提示：

树中节点数目范围在 [0, 100] 内
-100 <= Node.val <= 100
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
//#include <stack>
#include <queue>


//按照层序遍历也是可以的，遍历每个节点，将左右子树互换。
TreeNode* invertTree(TreeNode* root) {
    std::queue<TreeNode*> queue_;
    if(root)
    {
        queue_.push(root);
    }
    while(!queue_.empty())
    {
        int cur_q_size = queue_.size();
        for(int i = 0; i < cur_q_size; i++)
        {
            TreeNode* node = queue_.front();
            TreeNode* node_left_ = node->left, *node_right_ = node->right;
            if(node_left_)
            {
                queue_.push(node_left_);
            }
            if(node_right_)
            {
                queue_.push(node_right_);
            }
            node->left = node_right_;
            node->right = node_left_;
            queue_.pop();
        }
    }
    return root;
}

//递归调用即可
TreeNode* invertTreeRecursive(TreeNode* root) {
    if(root){
        TreeNode* cur_node_left_ = root->left;
        TreeNode* cur_node_right_ = root->right;
        root->left = cur_node_right_;
        root->right = cur_node_left_;
        if(cur_node_left_)
        {
            invertTreeRecursive(cur_node_left_);
        }
        if(cur_node_right_)
        {
            invertTreeRecursive(cur_node_right_);
        }
    }
    return root;
}

int main(){
    std::vector<int> root = {3,1,NULL,NULL,2};
    TreeNode* root_node_ = buildBinaryTree(root);
    invertTreeRecursive(root_node_);
    std::cout << std::endl;
}