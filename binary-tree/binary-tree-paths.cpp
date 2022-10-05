/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-paths

给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。

叶子节点 是指没有子节点的节点。

 
示例 1：


输入：root = [1,2,3,null,5]
输出：["1->2->5","1->3"]
示例 2：

输入：root = [1]
输出：["1"]
 

提示：

树中节点的数目在范围 [1, 100] 内
-100 <= Node.val <= 100
*/
#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>
#include <queue>
#include <string>
//std::vector<std::string>&paths
//std::vector<std::string>&paths_
void binaryTreePathsRecursive(TreeNode* root, std::string path, std::vector<std::string>&paths_) {
    if(root)
    {
        path += std::to_string(root->val);
        if(root->left){
           path += "->";
           binaryTreePathsRecursive(root->left, path, paths_);
           path.pop_back();
           path.pop_back();
        }
        if(root->right){
           path += "->";
           binaryTreePathsRecursive(root->right, path, paths_);
           path.pop_back();
           path.pop_back();
        }
        if(!root->left && !root->right)
        {
            paths_.push_back(path);
            return ;
        }
    }
}

// std::vector<std::string> binaryTreePathsV1(TreeNode* root) {
//     std::vector<std::string> all_paths_;
//     //binaryTreePathsRecursive(root, all_paths_);
// }
std::vector<std::string> binaryTreePaths(TreeNode* root) {
    std::stack<TreeNode*>stack_;
    std::vector<std::string>all_paths_;
    if(root)
    {
        stack_.push(root);
    }
    while(!stack_.empty())
    {
        TreeNode* cur_node_ = stack_.top();
        stack_.pop();
        if(cur_node_ == nullptr)
        {
            cur_node_ = stack_.top();
            stack_.pop();
            if(!cur_node_->left && !cur_node_->right)//leaf node;
            {
                std::stack<TreeNode*> stack_temp_ = stack_;
                int node_count_ = stack_temp_.size();
                std::string s="";
                //std::string s = std::to_string(cur_node_->val);
                std::vector<int>values_;
                //只有一个节点时候
                if(stack_temp_.empty())
                {
                    s = std::to_string(cur_node_->val);
                    all_paths_.push_back(s);
                    continue;
                }
                while(!stack_temp_.empty())
                {
                    TreeNode* node = stack_temp_.top();
                    if(node == nullptr)
                    {
                        stack_temp_.pop();
                        node = stack_temp_.top();
                        values_.push_back(node->val);
                    }
                    stack_temp_.pop();
                }
                s += std::to_string(values_[values_.size()-1]);
                for(int i = 1; i < values_.size(); i++)
                {
                    s += "->";
                    s += std::to_string(values_[values_.size()-i-1]);
                }
                s += "->";
                s += std::to_string(cur_node_->val);
                all_paths_.push_back(s);
            }
        }else{
            stack_.push(cur_node_);
            stack_.push(nullptr);
            if(cur_node_->right)
            {
                stack_.push(cur_node_->right);
            }
            if(cur_node_->left)
            {
                stack_.push(cur_node_->left);
            }
        }
    }
    return all_paths_;
}


int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    // std::vector<int> root = {1, 2, NULL, 5,NULL, NULL, 3, NULL, NULL};
    std::vector<int> root = {1, 2, NULL, 5,NULL, NULL, 3, NULL, NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    // //std::vector<std::string> tree_path_ = binaryTreePaths(root_node_);
    // std::vector<std::string> all_path_;
    std::vector<std::string> all_paths_;
    std::string path;
    if(!root_node_)
    {
        //return all_paths_;
    }else if(!root_node_->left && !root_node_->right)
    {
        std::string s = std::to_string(root_node_->val);
        all_paths_.push_back(s);
        //return all_paths_;
    }    
    binaryTreePathsRecursive(root_node_, path, all_paths_);
    for(auto s:all_paths_)
    {
        std::cout << s << std::endl;
    }
}