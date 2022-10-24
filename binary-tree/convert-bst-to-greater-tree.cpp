/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/convert-bst-to-greater-tree

给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。
注意：本题和 1038: https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/ 相同

 

示例 1：



输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
示例 2：

输入：root = [0,null,1]
输出：[1,null,1]
示例 3：

输入：root = [1,0,2]
输出：[3,3,2]
示例 4：

输入：root = [3,2,4,1]
输出：[7,9,4,10]
 

提示：

树中的节点数介于 0 和 104 之间。
每个节点的值介于 -104 和 104 之间。
树中的所有值 互不相同 。
给定的树为二叉搜索树。
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

//按照题目的要求，应该采用中序遍历，而且先右子树然后左子树的顺序进行遍历，使得给节点赋新值的时候原树的大于其节点的值的和已经计算出来
TreeNode* convertBST(TreeNode* root, int& cur_value_) {
    if(root)
    {
        convertBST(root->right, cur_value_);
        //values_path_.push_back(root->val);
        root->val += cur_value_;
        cur_value_ = root->val;
        //root->val += cur_value_;
        convertBST(root->left, cur_value_);
    }
    return root;
}

int main(){
    std::vector<int> root = {4,1,6,0,2,5,7,NULL,NULL,NULL,3,NULL,NULL,NULL,8,NULL,NULL};
    // std::vector<int> nums = {-10,-3,0,5,9};
    // //TreeNode* root_node_ = buildBinaryTree(root);
    // //[3,0,4,null,2,null,null,1]
    // //1
    // //3
    // TreeNode* root_node_ = trimBST(nums);
    TreeNode* root_node_ = buildBinaryTreeByLevelOrder(root);
    int cur_value_ = 0;
    TreeNode* root_node_bst_ = convertBST(root_node_, cur_value_);
    std::cout << std::endl;
}