
/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/count-complete-tree-nodes

给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，
其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。
若最底层为第 h 层，则该层包含 1~ 2h 个节点。

示例 1：

输入：root = [1,2,3,4,5,6]
输出：6
示例 2：

输入：root = []
输出：0
示例 3：

输入：root = [1]
输出：1
 

提示：

树中节点的数目范围是[0, 5 * 104]
0 <= Node.val <= 5 * 104
题目数据保证输入的树是 完全二叉树
*/

//可以看出如果整个树不是满二叉树，就递归其左右孩子，直到遇到满二叉树为止，
//用公式计算这个子树（满二叉树）的节点数量。
//在完全二叉树中，如果递归向左遍历的深度等于递归向右遍历的深度，那说明就是满二叉树。

#include <vector>
#include <iostream>
#include "binary-tree.h"
//#include <stack>
#include <queue>

int countNodes(TreeNode* root) {
    if(root)
    {
        TreeNode* cur_node_left_ = root->left, *cur_node_right_ = root->right;
        int left_depth = 0, right_depth =0;
        while(cur_node_left_){
            left_depth++;
            cur_node_left_ = cur_node_left_->left;
        }

        while(cur_node_right_){
            right_depth++;
            cur_node_right_ = cur_node_right_->right;
        }
        if(left_depth == right_depth)//以root为节点的子树是满二叉树
        {
            return (2 << left_depth) -1;//不用再计算子树的节点数，直接按公式2^depth-1来求
        }else//不是满二叉树时再递归调用求其节点数
        {
            return 1+countNodes(root->left)+countNodes(root->right);
        }

    }else
    {
        return 0;
    }
}
//该方法没有用到完全二叉树的特性，纯粹的递归调用
int countNodesRecursivev1(TreeNode* root) {
    if(root)
    {
        int count_left_child_ = countNodesRecursivev1(root->left);
        int count_right_child_ = countNodesRecursivev1(root->right);
        int count = count_left_child_ + count_right_child_ +1;
        return count;
    }else{
        return 0;
    }
}

int main(){
    std::vector<int> root = {3,1,NULL,NULL,2};
    TreeNode* root_node_ = buildBinaryTree(root);
    int node_count_ = countNodesRecursivev1(root_node_);
    std::cout << node_count_ << std::endl;
}