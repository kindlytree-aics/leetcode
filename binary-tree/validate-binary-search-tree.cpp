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
-2^31 <= Node.val <= 2^31 - 1
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
    inorderTraverse(root, inorder);
    for(int i =1; i< inorder.size(); i++)
    {
        if(inorder[i] <= inorder[i-1])
        {
            return false;
        }
    }
    return true;
}

//也可以递归实现，递归判断左节点是否小于当前节点，有节点是否大于当前节点（可以通过递归先序遍历）
//下面的逻辑有缺陷，不能保证右子树的最小节点比根节点要大
bool isValidBSTRecursiveOld(TreeNode* root) {
    if(!root)return true;
    if(root->left){
        if(root->val <= root->left->val){
            return false;
        }else{
            if(!isValidBSTRecursiveOld(root->left))
            {
                return false;
            }
        }
    }
    if(root->right)
    {
        if(root->val >= root->right->val){
            return false;
        }else{
            if(!isValidBSTRecursiveOld(root->right))
            {
                return false;
            }
        }        
    }
}


//中序遍历记录下数组判断和前面一个值的关系
bool isValidBSTRecursive(TreeNode* root, std::vector<int>&path) {
    if(!root)return true;
    if(!isValidBSTRecursive(root->left, path))return false;
    if(path.size() > 0)
    {
        int before_val_ = path.back();
        if(before_val_ < root->val)
        {
            path.push_back(root->val);
        }else{
            return false;
        }
    }else{
        path.push_back(root->val);
    }
    if(!isValidBSTRecursive(root->right, path))return false;
    return true;
}

int main()
{
    std::vector<int> root = {5, 1, NULL, NULL, 4, 3, NULL, NULL, 6, NULL, NULL}; 
    TreeNode* root_ = buildBinaryTree(root);
    bool is_valid_bst_ = isValidBST(root_);
}