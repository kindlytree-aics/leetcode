/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/path-sum

给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

叶子节点 是指没有子节点的节点。

示例 1：

输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
解释：等于目标和的根节点到叶节点路径如上图所示。
示例 2：


输入：root = [1,2,3], targetSum = 5
输出：false
解释：树中存在两条根节点到叶子节点的路径：
(1 --> 2): 和为 3
(1 --> 3): 和为 4
不存在 sum = 5 的根节点到叶子节点的路径。
示例 3：

输入：root = [], targetSum = 0
输出：false
解释：由于树是空的，所以不存在根节点到叶子节点的路径。
 

提示：

树中节点的数目在范围 [0, 5000] 内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
*/
#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>

//更加高效的递归方法，只要有返回true的就返回。减少计算量
bool hasPathSumRecursivev2(TreeNode* root, int sum, int target)
{
    if(root){
        sum += root->val;
    }else{
        return false;
    }
    if(root->left){
        if(hasPathSumRecursivev2(root->left, sum, target))return true;
    }if(root->right)
    {
        if(hasPathSumRecursivev2(root->right, sum, target))return true;
    }
    else if(!root->left && !root->right){
    //else{
        if(sum == target)
        {
            return true;
        }else{
            return false;
        }
    }
    return false;
}


//通过先序遍历求得所有从根节点到叶子节点的路径，然后去判断是否存在sum为target的值
void hasPathSumRecursive(TreeNode* root, std::vector<int> path, std::vector<std::vector<int>>&all_paths)
{
    if(root){
        path.push_back(root->val);
    }else{
        return;
    }
    if(root->left){
        hasPathSumRecursive(root->left, path, all_paths);
    }if(root->right)
    {
        hasPathSumRecursive(root->right, path, all_paths);
    }
    if(!root->left && !root->right){
        all_paths.push_back(path);
    }
}

bool hasPathSum(TreeNode* root, int targetSum) {
    std::vector<int> path;
    std::vector<std::vector<int>>all_paths_;
    hasPathSumRecursive(root, path, all_paths_);
    for(int i = 0; i < all_paths_.size(); i++)
    {
        int sum = 0;
        for(int j = 0; j < all_paths_[i].size(); j++)
        {
            sum += all_paths_[i][j];
        }
        if(sum == targetSum)
        {
            return true;
        }
    }
    return false;
}


int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> root = {5, 4, 11, 7, NULL, NULL, 2, NULL, NULL,NULL, 8, 13, NULL, NULL, 4, NULL, 1, NULL, NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    int targetSum  = 22;
    //bool has_target_sum_ = hasPathSum(root_node_, targetSum);
    int sum = 0;
    bool has_target_sum_ = hasPathSumRecursivev2(root_node_, sum,  targetSum);
    std::cout << has_target_sum_ << std::endl;
}
