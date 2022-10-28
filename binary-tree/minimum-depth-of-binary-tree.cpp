/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-depth-of-binary-tree

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明：叶子节点是指没有子节点的节点。

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：2
示例 2：

输入：root = [2,null,3,null,4,null,5,null,6]
输出：5
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
//#include <stack>
#include <queue>

//直接层序遍历可以解决
//层序遍历找到的第一个叶子节点即为最小深度
//参考当前目录下binary-tree-level-order-traversal.cpp的实现
//注意这里有定义是到最近的叶子节点

//后序递归函数定义求解，先分别递归求左子树的最小深度和右子树的最小深度
//然后比较小者为当前节点为根的树的最小深度
int minDepthRecursive(TreeNode* root) {
    if(root)
    {
        if(root->left && root->right)
        {
            int depth_left_child_ =  root->left != nullptr ? minDepthRecursive(root->left) + 1: 1;
            int depth_right_child_ =  root->right != nullptr ? minDepthRecursive(root->right) + 1 :1;
            if(depth_left_child_ >= depth_right_child_)
            {
                return depth_right_child_;
            }else{
                return depth_left_child_;
            }
        }else if(root->left){
            return minDepthRecursive(root->left) + 1;
        }else if(root->right){
            return minDepthRecursive(root->right) + 1;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}

int main(){
    std::vector<int> root = {1,2,2,3,4,4,3};
    TreeNode* root_node_ = buildBinaryTree(root);
    int max_dep = minDepthRecursive(root_node_);
    std::cout << max_dep << std::endl;
}