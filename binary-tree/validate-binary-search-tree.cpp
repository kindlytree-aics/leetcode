/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/validate-binary-search-tree

给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：

节点的左子树只包含 小于 当前节点的数。
节点的右子树只包含 大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
 
示例 1：

输入：root = [2,1,3]
输出：true
示例 2：

输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是 5 ，但是右子节点的值是 4 。
 
提示：

树中节点数目范围在[1, 104] 内
-231 <= Node.val <= 231 - 1
*/
#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>


//中序遍历递增
void inorderTraverse(TreeNode* root, std::vector<int>&inorder){
    if(root){
        if(root->left){
            inorderTraverse(root->left, inorder);
        }
        inorder.push_back(root->val);
        if(root->right)
        {
            inorderTraverse(root->right, inorder);
        }
    }else{
        return;
    }
}

bool isValidBST(TreeNode* root) {
    std::vector<int> inorder;
    

}


int main()
{
    std::vector<int> root = {5, 1, NULL, NULL, 4, 3, NULL, NULL, 6, NULL, NULL}; 
    TreeNode* root_ = buildBinaryTree(root);
    bool is_valid_bst_ = isValidBST(root_);
}