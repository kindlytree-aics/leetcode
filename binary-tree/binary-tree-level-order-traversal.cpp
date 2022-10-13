/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-level-order-traversal
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]
示例 2：

输入：root = [1]
输出：[[1]]
示例 3：

输入：root = []
输出：[]

提示：

树中节点数目在范围 [0, 2000] 内
-1000 <= Node.val <= 1000
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

#define INT_MAX ((int)(~0U>>1))
#define INT_MIN (-INT_MAX - 1)
//用队列结构实现，队列先进先出，满足层次的需求
//在遍历每一层开始时，是知道当前队列的长度的，pop这个个长度的内容，就可以输出该层的内容
//同时下一层的内容也就已经在队列里边了，一层层就可以这样输出
//在这里我们
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::queue<TreeNode*> queue_;
    TreeNode* cur_iter_node_ = root;
    std::vector<std::vector<int>>result;
    if(root != nullptr)
    {
        queue_.push(root);
        TreeNode* node = new TreeNode(INT_MAX);
        queue_.push(node);
    }
    std::vector<int>level_;
    while(!queue_.empty())
    {
        cur_iter_node_ = queue_.front();
        if(cur_iter_node_ == nullptr){
            //level_.push_back(NULL);
            queue_.pop();
            continue;
        }else{
            //插入一个节点，为改行的结束，起val值为INT_MAX
            if(cur_iter_node_->val == INT_MAX)
            {
                queue_.pop();
                if(queue_.empty())
                {
                    break;
                }else{
                    TreeNode* node = new TreeNode(INT_MAX);
                    queue_.push(node);
                    delete cur_iter_node_;
                    std::vector<int> level_cur = level_;
                    result.push_back(level_cur);
                    level_.clear();
                    continue;
                }

            }else{
                level_.push_back(cur_iter_node_->val);
                queue_.push(cur_iter_node_->left);
                queue_.push(cur_iter_node_->right);
            }
        }
        queue_.pop();
    }
    return result;
}

//更简洁的实现;
std::vector<std::vector<int>> levelOrderv1(TreeNode* root) {\
    std::vector<std::vector<int>> result;
    if(!root){return result;}
    std::queue<TreeNode*> queue_;
    queue_.push(root);
    while(!queue_.empty())
    {
        std::vector<int> cur_level_res_;
        int cur_level_size = queue_.size();
        for(int i = 0; i < cur_level_size; i++)
        {
            TreeNode* cur_node_ = queue_.front();
            queue_.pop();
            if(cur_node_->left){
                queue_.push(cur_node_->left);
            }
            if(cur_node_->right)
            {
                queue_.push(cur_node_->right);
            }
            cur_level_res_.push_back(cur_node_->val);
        }
        result.push_back(cur_level_res_);
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
    std::vector<std::vector<int>> result_level = levelOrderv1(root_node_);
    for(int i = 0; i < result_level.size(); i++)
    {
        for(int j = 0; j < result_level[i].size(); j++)
        {
            std::cout << result_level[i][j] ;
        }
    }
    std::cout << std::endl;
}