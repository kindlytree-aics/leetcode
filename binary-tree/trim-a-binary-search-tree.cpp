/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/trim-a-binary-search-tree

给你二叉搜索树的根节点 root ，同时给定最小边界low 和最大边界 high。通过修剪二叉搜索树，使得所有节点的值在[low, high]中。修剪树 不应该 改变保留在树中的元素的相对结构 (即，如果没有被移除，原有的父代子代关系都应当保留)。 可以证明，存在 唯一的答案 。

所以结果应当返回修剪好的二叉搜索树的新的根节点。注意，根节点可能会根据给定的边界发生改变。

示例 1：

输入：root = [1,0,2], low = 1, high = 2
输出：[1,null,2]
示例 2：

输入：root = [3,0,4,null,2,null,null,1], low = 1, high = 3
输出：[3,2,null,1]

提示：

树中节点数在范围 [1, 104] 内
0 <= Node.val <= 104
树中每个节点的值都是 唯一 的
题目数据保证输入是一棵有效的二叉搜索树
0 <= low <= high <= 104
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

//to be update;
// void destroyTree(TreeNode* root)
// {
//     std::queue<TreeNode*>queue_;
// }

// TreeNode* deleteNode(TreeNode* root, TreeNode* parent) {
//     if(!root){return root;}
//     if(!root->left && root->right){
//         if(parent){
//             parent->left == root ? parent->left = root->right:parent->right = root->right;
//         }
//         TreeNode* temp = root;
//         root = root->right;
//         delete temp;
//         temp = nullptr;
//     }else if(root->left && !root->right)
//     {
//         if(parent)
//         {
//             parent->left == root ? parent->left = root->left:parent->right = root->left;
//         }
//         TreeNode* temp = root;
//         root = root->left;
//         delete temp;  
//         temp = nullptr;       
//     }else if(!root->left && !root->right)
//     {
//         if(parent)
//         {
//             parent->left == root ? parent->left = nullptr: parent->right = nullptr;
//         }
//         delete root;
//         root = nullptr;       
//     }
//     else{
//         TreeNode* temp = root->right;
//         //删除节点的左右子树非空，从右边节点找到要补上来的点值
//         //如果有子树的左边节点为空，则直接将右子树的右边补上
//         //直接删除temp，将其右节点拼接上
//         if(!temp->left && temp->right)
//         {
//             root->val = temp->val;
//             TreeNode* to_be_deleted = temp;
//             root->right = temp->right;
//             delete to_be_deleted;
//             to_be_deleted = nullptr;
//             return root;
//         }//如果右节点左右孩子均为空，右节点直接补上
//         else if(!temp->left && !temp->right)
//         {
//             root->val = temp->val;
//             TreeNode* to_be_deleted = temp;
//             root->right = nullptr;
//             delete to_be_deleted;
//             to_be_deleted = nullptr;
//             return root;
//         }
//         //否则迭代遍历右节点的左子树，将最后一个左孩子节点的值填充；
//         while(temp->left->left)
//         {
//             temp = temp->left;
//         }
//         root->val = temp->left->val;
//         TreeNode* to_be_deleted = temp->left;
//         //emp->left->right不为空，则直接接过来
//         temp->left = temp->left->right;
//         delete to_be_deleted;
//         to_be_deleted=nullptr;
//     }
//     return root;
// }

// TreeNode* trimBSTLower(TreeNode* root, TreeNode* parent, int key) {
//     if(!root){return root;}
//     if(root->val > key)
//     {
//         return trimBSTLower(root->left, root, key);
//     }else if(root->val < key)
//     {
//         root->left = nullptr;
//         //parent->left == root ? parent->left = nullptr: parent->right = nullptr;
//         TreeNode* new_root_ = deleteNode(root, parent);
//         if(parent)
//         {
//             bool parent_left = parent->left == root ? true:false;
//             parent_left == true ? parent->left = new_root_ : parent->right = new_root_;
//         }
//         if(!new_root_ || new_root_->val == key)
//         {
//             root =  new_root_;
//         }else if(new_root_->val < key)
//         {
//             root = trimBSTLower(new_root_, parent, key);
//         }else{
//             trimBSTLower(new_root_->left, new_root_, key);
//         }
//         //trimBSTLower(root->left, root, key);
//         //trimBSTLower(root->right, key);
//         //TreeNode* root_ = root;
//     }else{
//         //destroyTree(root->left);
//         root->left = nullptr;

//     }
//     return root;
// }

// TreeNode* trimBSTUpper(TreeNode* root, TreeNode* parent, int key) {
//     if(!root){return root;}
//     if(root->val > key)
//     {
//         root->right = nullptr;
//         //bool parent_left = parent->left == root ? true:false;
//         //parent->left == root ? parent->left = nullptr: parent->right = nullptr;
//         TreeNode* new_root_ = deleteNode(root, parent);
//         if(parent)
//         {
//             bool parent_left = parent->left == root ? true:false;
//             parent_left == true ? parent->left = new_root_ : parent->right = new_root_;
//         }
//         root = new_root_;
//         if(!new_root_ || new_root_->val == key)
//         {
//             root =  new_root_;
//         }else if(new_root_->val > key)
//         {
//             root = trimBSTUpper(new_root_, parent, key);
//         }else{
//             trimBSTUpper(new_root_->right, new_root_, key);
//         }
//     }else if(root->val < key)
//     {
//         trimBSTUpper(root->right, root, key);
//         //trimBSTLower(root->left, root, key);
//         //trimBSTLower(root->right, key);
//         //TreeNode* root_ = root;
//     }else{
//         //destroyTree(root->left);
//         root->right = nullptr;

//     }
//     return root;
// }

// TreeNode* trimBST(TreeNode* root, int low, int high) {

//     TreeNode* root_trim_lower_ = trimBSTLower(root, nullptr, low);
//     TreeNode* root_trim_lower_upper_ = trimBSTUpper(root_trim_lower_, nullptr, high);
//     return root_trim_lower_upper_;
// }

TreeNode* buildSortedArrayToBst(std::vector<int>& nums, int left, int right)
{
    if(left > right || nums.size() == 0) return nullptr;
    int middle = left + (right-left)/2;
    TreeNode* node = new TreeNode(nums[middle]);
    if(left == right)
    {
        return node;
    }else
    {
        node->left = buildSortedArrayToBst(nums, left, middle-1);
        node->right = buildSortedArrayToBst(nums, middle+1, right);
    }
    return node;
}

TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    //int 
    TreeNode* node = buildSortedArrayToBst(nums, 0, nums.size()-1);
    return node;
}

int main(){
    //std::vector<int> root = {3,0,4,NULL,2,NULL,NULL,1};
    std::vector<int> nums = {-10,-3,0,5,9};
    //TreeNode* root_node_ = buildBinaryTree(root);
    //[3,0,4,null,2,null,null,1]
    //1
    //3
    TreeNode* root_node_ = sortedArrayToBST(nums);
    std::cout << std::endl;
}