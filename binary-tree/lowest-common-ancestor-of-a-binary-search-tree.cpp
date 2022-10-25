/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]

示例 1:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。
示例 2:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
 
说明:

所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉搜索树中。
*/

//分别求path，找出path中对应元素前面的最近的共同元素
#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

//如果当前根节点的值在两个节点之间，则直接返回该节点
//如果当前节点值均大于两个节点，则到左子树中找公共祖先，否则到右子树中找公共祖先
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root->val == p->val || root->val == q->val || root == nullptr){
        return root;
    }else
    {
        int root_val_ = root->val, p_val_ = p->val, q_val_ = q->val;
        TreeNode* left_ = nullptr, *right_ = nullptr;
        int min_p_q_ = p_val_ > q_val_ ? q_val_ :p_val_;
        int max_p_q_ = p_val_ > q_val_ ? p_val_ :q_val_;
        if(root->val > max_p_q_){
            return lowestCommonAncestor(root->left, p, q);
        }else if(root->val > min_p_q_)
        {
            return root;
        }else{
            return lowestCommonAncestor(root->right, p, q);
        }
    }
}


int main(){
    //std::vector<int> root = {3,5,6,NULL,NULL,2,7,NULL,NULL,4,NULL,NULL,1,0,NULL,NULL,8,NULL,NULL};
    std::vector<int> root = {6,2,0,NULL,NULL,4,3,NULL,NULL,5,NULL,NULL,8,7,NULL,NULL,9,NULL,NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    int p=2, q=8;
    TreeNode* tree_node_p_ = new TreeNode(p);
    TreeNode* tree_node_q_ = new TreeNode(q);
    TreeNode* ancestor = lowestCommonAncestor(root_node_, tree_node_p_, tree_node_q_);
    std::cout << std::endl;
}