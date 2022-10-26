/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/merge-two-binary-trees

给你两棵二叉树： root1 和 root2 。

想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为 null 的节点将直接作为新二叉树的节点。

返回合并后的二叉树。

注意: 合并过程必须从两个树的根节点开始。

 

示例 1：


输入：root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
输出：[3,4,5,5,4,null,7]
示例 2：

输入：root1 = [1], root2 = [1,2]
输出：[2,2]
 

提示：

两棵树中的节点数目在范围 [0, 2000] 内
-104 <= Node.val <= 104
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>
#include <queue>

//方法：先序遍历,先合并根节点，然后递归合并左子树和右子树，如果左子树和右子树均为空则返回

TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if(root1 && root2){
        TreeNode* node = new TreeNode(root1->val+root2->val);
        node->left = mergeTrees(root1->left, root2->left);
        node->right = mergeTrees(root1->right, root2->right);
        return node;
    }else if(root1)
    {
        TreeNode* node = new TreeNode(root1->val);
        node->left = root1->left;
        node->right = root1->right;
        return node;
    }else if(root2)
    {
        TreeNode* node = new TreeNode(root2->val);
        node->left = root2->left;
        node->right = root2->right;   
        return node;    
    }
    return nullptr;
}

int main()
{
    std::vector<int> root1 = {1,3,5, NULL, NULL, NULL, 2, NULL, NULL}; 
    std::vector<int> root2 = {2,1,NULL, 4, NULL, NULL, 3 ,NULL,7, NULL, NULL};
    TreeNode* root1_ = buildBinaryTree(root1);
    TreeNode* root2_ = buildBinaryTree(root2);
    TreeNode* root = mergeTrees(root1_, root2_);
}
