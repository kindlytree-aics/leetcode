
/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/search-in-a-binary-search-tree

给定二叉搜索树（BST）的根节点 root 和一个整数值 val。

你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 null 。

示例 1:

输入：root = [4,2,7,1,3], val = 2
输出：[2,1,3]
示例 2:

输入：root = [4,2,7,1,3], val = 5
输出：[]
 
提示：

数中节点数在 [1, 5000] 范围内
1 <= Node.val <= 107
root 是二叉搜索树
1 <= val <= 107
*/


#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>
#include <queue>

//比较简单的递归算法，直接递归求解
TreeNode* searchBST(TreeNode* root, int val) {
    if(!root){
        return nullptr;
    }else{
        if(val == root->val){
            return root;
        }else if(val > root->val)
        {
            return searchBST(root->right, val);
        }else{
            return searchBST(root->left, val);
        }
    }
}


int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> root = {4,2,1,NULL,NULL,3,NULL,NULL,7,NULL,NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    int val = 2;
    //bool is_balanced = isBalanced(root_node_);
    TreeNode* root_node_searched_ = searchBST(root_node_, val);
    //std::cout << is_balanced << std::endl;
}