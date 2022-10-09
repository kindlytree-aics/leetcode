/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

 

示例 1：

#这里边的定义时按照层次的顺序
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
示例 2：


输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
示例 3：

输入：root = [1,2], p = 1, q = 2
输出：1
 

提示：

树中节点数目在范围 [2, 105] 内。
-109 <= Node.val <= 109
所有 Node.val 互不相同 。
p != q
p 和 q 均存在于给定的二叉树中。
*/

//分别求path，找出path中对应元素前面的最近的共同元素
#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

//通过调用两次找到分别的路径，然后找到了目标最近的公共节点
void pathToNode(TreeNode* root, \
                            std::vector<int>path, int val,\
                            std::vector<std::vector<int>>&path_)
{
    if(root)
    {
        path.push_back(root->val);
        if(val == root->val){
            path_.push_back(path);
            return;
        }
        if(root->left)
        {
            pathToNode(root->left, path, val, path_);
        }
        if(root->right)
        {
            pathToNode(root->right, path, val, path_);
        }
    }
    return;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == q || root == p || root == NULL) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left != NULL && right != NULL) return root;
    if (left == NULL) return right;
    return left;
}

TreeNode* lowestCommonAncestorv0(TreeNode* root, TreeNode* p, TreeNode* q) {
    std::vector<int> path_to_p_, path_to_q_;
    std::vector<std::vector<int>> path_p_;
    std::vector<std::vector<int>> path_q_;
    pathToNode(root, path_to_p_, p->val, path_p_);
    pathToNode(root, path_to_q_, q->val, path_q_);
    for(int i = path_p_[0].size()-1; i >=0; i--)
    {
        for(int j =path_q_[0].size()-1; j >=0; j--)
        {
            if(path_p_[0][i] == path_q_[0][j]){
                return new TreeNode(path_p_[0][i]);
            }
        }
    }
    return nullptr;
}

//root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
int main(){
    //std::vector<int> root = {3,5,6,NULL,NULL,2,7,NULL,NULL,4,NULL,NULL,1,0,NULL,NULL,8,NULL,NULL};
    std::vector<int> root = {3,5,6,NULL,NULL,2,7,NULL,NULL,4,NULL,NULL,1,2,NULL,NULL,8,NULL,NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    int p=5, q=1;
    TreeNode* tree_node_p_ = new TreeNode(p);
    TreeNode* tree_node_q_ = new TreeNode(q);
    TreeNode* ancestor = lowestCommonAncestor(root_node_, tree_node_p_, tree_node_q_);
    std::cout << std::endl;
}