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

//递归方法，分别递归调用左子树和右子树找节点，如果都能找到，则肯定是最近公共祖先
//该方法可能会有多于的计算，即使已经找到也会计算下去
TreeNode* lowestCommonAncestorv1(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root->val == q->val || root->val == p->val || root == NULL) return root;
    TreeNode* left = lowestCommonAncestorv1(root->left, p, q);
    TreeNode* right = lowestCommonAncestorv1(root->right, p, q);
    if (left != NULL && right != NULL) return root;
    if (left == NULL) return right;
    return left;
}

//enum found_status{found_none=0, found_p=1, found_q=2, found_both=3, found_finished=4;};
//另一种递归方法，找到后就直接返回4，后面的就不需要再去找了，和上面的递归相比，在有时节省了部分多余的计算
int lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode** d) {
    //if (root == q || root == p || root == NULL) return root;
    int status  = 0;
    // if(root->val == p->val){status = 1;}
    // if(root->val == q->val){status =  2;}
    if(root == nullptr){ return  0;}
    int status_left =  lowestCommonAncestor(root->left, p, q, d);
    if(status_left >=4){return status_left;}
    if(status_left == 3)
    {
        *d = root->left;
        return 4;      
    }
    status += status_left;
    if(root == p)
    {
        status += 1;
    }
    else if(root == q)
    {
        status +=  2;
    }    
    if(status == 3) 
    {
        *d = root;
        return 4;
    }
    int status_right =  lowestCommonAncestor(root->right, p, q, d);
    if(status_right == 3) 
    {
        *d = root->right;
        return 4;
    }
    if(status_right >=4){return status_right;}
    status += status_right;
    if(status == 3) 
    {
        *d = root;
        return 4;
    }  
    else{
        return status;
    }
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
    TreeNode* d = nullptr;
    int status = lowestCommonAncestor(root_node_, tree_node_p_, tree_node_q_, &d);
    std::cout << std::endl;
}