/*
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/find-bottom-left-tree-value

给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。

假设二叉树中至少有一个节点。

示例 1:

输入: root = [2,1,3]
输出: 1
示例 2:

输入: [1,2,3,4,null,5,6,null,null,7]
输出: 7
 
提示:

二叉树的节点个数的范围是 [1,104]
-231 <= Node.val <= 231 - 1 
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
//#include <stack>
#include <queue>

//方法：层序遍历，记录当前遍历层的输出，最后返回最后一层的最先输出的结果
int findBottomLeftValue(TreeNode* root) {
    std::queue<TreeNode*>queue_;
    if(root)
    {
        queue_.push(root);
    }
    std::vector<int>last_level_values_;
    while(!queue_.empty())
    {
        int cur_level_size = queue_.size();
        last_level_values_.clear();
        for(int i = 0; i < cur_level_size; i++)
        {
            TreeNode* cur_node = queue_.front();
            queue_.pop();
            last_level_values_.push_back(cur_node->val);
            if(cur_node->left)
            {
                queue_.push(cur_node->left);
            }
            if(cur_node->right)
            {
                queue_.push(cur_node->right);
            }
        }
    }
    return last_level_values_[0];
}

int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> root = {1, NULL, 2, NULL,3,NULL, NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    bool is_balanced = findBottomLeftValue(root_node_);
    std::cout << is_balanced << std::endl;
}