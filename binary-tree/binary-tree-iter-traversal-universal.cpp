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
#include <stack>


//将访问的节点放入栈中，把要处理的节点也放入栈中但是要做标记。
std::vector<int> preorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack_;
    TreeNode* cur_iter_node_ = root;
    std::vector<int>result;
    if(root != nullptr)
    {
        stack_.push(root);
    }
    while(!stack_.empty())
    {
        cur_iter_node_ = stack_.top();
        stack_.pop();
        if(cur_iter_node_ != nullptr)
        {
            if(cur_iter_node_->right){
                stack_.push(cur_iter_node_->right);
            }
            if(cur_iter_node_->left){
                stack_.push(cur_iter_node_->left);
            }
            stack_.push(cur_iter_node_);
            stack_.push(nullptr);
        }else{
            cur_iter_node_ = stack_.top();
            result.push_back(cur_iter_node_->val);
            stack_.pop();
            continue;
        }
    }
    return result;
}

std::vector<int> inorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack_;
    TreeNode* cur_iter_node_ = root;
    std::vector<int>result;
    if(root != nullptr)
    {
        stack_.push(root);
    }
    while(!stack_.empty())
    {
        TreeNode* cur_iter_node_ = stack_.top();
        stack_.pop();
        if(cur_iter_node_ == nullptr)
        {
            cur_iter_node_ = stack_.top();
            stack_.pop();
            result.push_back(cur_iter_node_->val);
            continue;
        }
        if(cur_iter_node_->right)
        {
            stack_.push(cur_iter_node_->right);
        }
        stack_.push(cur_iter_node_);
        stack_.push(nullptr);
        if(cur_iter_node_->left)
        {
            stack_.push(cur_iter_node_->left);
        }       
    }
    return result;
}


std::vector<int> postorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack_;
    TreeNode* cur_iter_node_ = root;
    std::vector<int>result;
    if(root != nullptr)
    {
        stack_.push(root);
    }
    while(!stack_.empty())
    {
        TreeNode* cur_iter_node_ = stack_.top();
        stack_.pop();
        if(cur_iter_node_ == nullptr)
        {
            cur_iter_node_ = stack_.top();
            stack_.pop();
            result.push_back(cur_iter_node_->val);
            continue;
        }
        stack_.push(cur_iter_node_);
        stack_.push(nullptr);
        if(cur_iter_node_->right){
            stack_.push(cur_iter_node_->right);
        }
        if(cur_iter_node_->left){
            stack_.push(cur_iter_node_->left);
        }
    }
    return result;
}

int main(){
    //std::vector<int> root = {1,NULL,2,3};
    //std::vector<int> root = {2,3,NULL,1};
    //std::vector<int> root = {1,NULL,2,3};
    //std::vector<int> root = {3,2,NULL,NULL,4,1};
    //std::vector<int> root = {1,NULL,2};
    std::vector<int> root = {3,1,NULL,NULL,2};
    TreeNode* root_node_ = buildBinaryTree(root);
    std::vector<int> result_preorder = preorderTraversal(root_node_);
    for(int i = 0; i < result_preorder.size(); i++)
    {
        std::cout << result_preorder[i] ;
    }
    std::cout << std::endl;

    std::vector<int> result_inorder = inorderTraversal(root_node_);
    for(int i = 0; i < result_inorder.size(); i++)
    {
        std::cout << result_inorder[i] ;
    }
    std::cout << std::endl;

    std::vector<int> result_postorder = postorderTraversal(root_node_);
    for(int i = 0; i < result_postorder.size(); i++)
    {
        std::cout << result_postorder[i] ;
    }
    std::cout << std::endl;
    // std::vector<int> result_postorder;
    // postorderTraversal(root_node_, result_postorder);
    // for(int i = 0; i < result_postorder.size(); i++)
    // {
    //     std::cout << result_postorder[i] ;
    // }
}