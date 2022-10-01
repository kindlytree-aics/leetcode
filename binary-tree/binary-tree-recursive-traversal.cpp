/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-preorder-traversal

给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

示例 1：

输入：root = [1,null,2,3]
输出：[1,2,3]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [1]
输出：[1]
示例 4：


输入：root = [1,2]
输出：[1,2]
示例 5：


输入：root = [1,null,2]
输出：[1,2]
 

提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"


void preorderTraversal(TreeNode* root, std::vector<int>& result) {
    if(root)
    {
        result.push_back(root->val);
        preorderTraversal(root->left, result);
        preorderTraversal(root->right, result);
    }
}

void postorderTraversal(TreeNode* root, std::vector<int>& result) {
    if(root){
        postorderTraversal(root->left, result);
        postorderTraversal(root->right, result);
        result.push_back(root->val);
    }
}

void inorderTraversal(TreeNode* root, std::vector<int>& result) {
    if(root){
        inorderTraversal(root->left, result);
        result.push_back(root->val);
        inorderTraversal(root->right, result);
    }
}



int main(){
    std::vector<int> root = {1,NULL,2,3};
    std::vector<int> result_preorder;
    TreeNode* root_node_ = buildBinaryTree(root);
    preorderTraversal(root_node_, result_preorder);
    for(int i = 0; i < result_preorder.size(); i++)
    {
        std::cout << result_preorder[i] ;
    }

    std::vector<int> result_postorder;
    postorderTraversal(root_node_, result_postorder);
    for(int i = 0; i < result_postorder.size(); i++)
    {
        std::cout << result_postorder[i] ;
    }
}