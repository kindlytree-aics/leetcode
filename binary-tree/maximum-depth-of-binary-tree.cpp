
/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/maximum-depth-of-binary-tree

给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

    3
   / \
  9  20
    /  \
   15   7
返回它的最大深度 3 。
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
//#include <stack>
#include <queue>

//就是求二叉树的层数，和层序遍历的思想类似；在这里就暂时不重复写了
//int maxDepth(TreeNode* root) {
//
//}

int maxDepthRecursive(TreeNode* root) {
    if(root)
    {
        int depth_left_child_ =  root->left != nullptr ? maxDepthRecursive(root->left) + 1: 0;
        int depth_right_child_ =  root->right != nullptr ? maxDepthRecursive(root->right) + 1 :0;
        if(depth_left_child_ >= depth_right_child_)
        {
            return depth_left_child_;
        }else{
            return depth_right_child_;
        }
    }else{
        return 0;
    }
}

int main(){
    std::vector<int> root = {1,2,2,3,4,4,3};
    TreeNode* root_node_ = buildBinaryTree(root);
    int max_dep = maxDepthRecursive(root_node_);
    std::cout << max_dep << std::endl;
}