/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/delete-node-in-a-bst


给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

首先找到需要删除的节点；
如果找到了，删除它。
 

示例 1:

输入：root = [5,3,6,2,4,NULL,7], key = 3
输出：[5,4,6,2,NULL,NULL,7]
解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。
一个正确的答案是 [5,4,6,2,NULL,NULL,7], 如下图所示。
另一个正确答案是 [5,2,6,NULL,4,NULL,7]。


示例 2:

输入: root = [5,3,6,2,4,NULL,7], key = 0
输出: [5,3,6,2,4,NULL,7]
解释: 二叉树不包含值为 0 的节点
示例 3:

输入: root = [], key = 0
输出: []
 

提示:

节点数的范围 [0, 104].
-105 <= Node.val <= 105
节点值唯一
root 是合法的二叉搜索树
-105 <= key <= 105
 
进阶： 要求算法时间复杂度为 O(h)，h 为树的高度。
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

TreeNode* deleteNode(TreeNode* root, TreeNode* parent, int key) {
    if(!root){return root;}
    if(root->val > key)
    {
        deleteNode(root->left, root, key);
    }else if(root->val < key)
    {
        deleteNode(root->right, root, key);
    }else{
        //特殊情况要记录parent节点；
        if(!root->left && root->right){
            parent->left == root ? parent->left = root->right:parent->right = root->right;
            TreeNode* temp = root;
            root = root->right;
            delete temp;
            temp = nullptr;
        }else if(root->left && !root->right)
        {
            parent->left == root ? parent->left = root->left:parent->right = root->left;
            TreeNode* temp = root;
            root = root->left;
            delete temp;  
            temp = nullptr;       
        }else if(!root->left && !root->right)
        {
            parent->left == root ? parent->left = nullptr: parent->right = nullptr;
            delete root;
            root = nullptr;       
        }
        else{
            TreeNode* temp = root->right;
            //删除节点的左右子树非空，从右边节点找到要补上来的点值
            //如果有子树的左边节点为空，则直接将右子树的右边补上
            //直接删除temp，将其右节点拼接上
            if(!temp->left && temp->right)
            {
                root->val = temp->val;
                TreeNode* to_be_deleted = temp;
                root->right = temp->right;
                delete to_be_deleted;
                return root;
            }//如果右节点左右孩子均为空，右节点直接补上
            else if(!temp->left && !temp->right)
            {
                root->val = temp->val;
                TreeNode* to_be_deleted = temp;
                root->right = nullptr;
                delete to_be_deleted;
                return root;
            }
            //否则迭代遍历右节点的左子树，将最后一个左孩子节点的值填充；
            while(temp->left->left)
            {
                temp = temp->left;
            }
            root->val = temp->left->val;
            TreeNode* to_be_deleted = temp->left;
            //emp->left->right不为空，则直接接过来
            temp->left = temp->left->right;
            delete to_be_deleted;
        }
    }
    return root;
}
// TreeNode* deleteNode(TreeNode* root, int key) {
//     if(!root){return root;}
//     if(root->val > key){
//         if(root->left && root->left->val == key && root->left->left == nullptr && root->left->right == nullptr){
//             delete root->left;
//             root->left= nullptr;
//         }else if(root->left && root->left->val == key && root->left->left == nullptr){
//             TreeNode* temp = root->left;
//             root->left = root->left->right;
//             delete temp;
//         }else if(root->left && root->left->val == key && root->left->right == nullptr){
//             TreeNode* temp = root->left;
//             root->left = root->left->left;
//             delete temp;
//         }else if(root->left && root->left->val == key)
//         {
//             TreeNode*  temp = root->left->right;
//             if(!temp->left)
//             {
//                 //delete root->left;
//                 root->left->val = temp->val;
//                 root->left->right = temp->right;
//                 delete temp;
//             }else{
//                 while(temp->left->left)
//                 {
//                     temp = temp->left;
//                 }
//                 root->left->val = temp->left->val;
//                 delete temp->left;
//                 temp->left = nullptr;
//             }
//         }
//         else if(!root->left)
//         {
//             return root;
//         }
//         else{
//             deleteNode(root->left, key);
//         }
//     }else if(root->val < key)
//     {
//         if(root->right && root->right->val == key && root->right->left == nullptr && root->right->right == nullptr){
//             delete root->right;
//             root->right= nullptr;
//         }else if(root->right && root->right->val == key && root->right->left == nullptr){
//             TreeNode* temp = root->right;
//             root->right = root->right->right;
//             delete temp;
//         }else if(root->right && root->right->val == key && root->right->right == nullptr){
//             TreeNode* temp = root->right;
//             root->right = root->right->left;
//             delete temp;
//         }else if(root->right && root->right->val == key){
//             TreeNode*  temp = root->right->right;
//             if(!temp->left)
//             {
//                 //delete root->left;
//                 root->right->val = temp->val;
//                 root->right->right = temp->right;
//                 delete temp;
//             }else{
//                 bool running_ = true;
//                 while(running_)
//                 {
//                     while(temp->left->left)
//                     {
//                         temp = temp->left;
//                     }
//                     root->right->val = temp->left->val;
//                     if(temp->left->right)
//                     {


//                     }else{
//                         running_ = false;
//                         break;
//                     }
//                 }
    
//                 delete temp->left;
//                 temp->left = nullptr;
//             }
//         }
//         else if(!root->right)
//         {
//             return root;
//         }
//         else
//         {
//             deleteNode(root->right, key);
//         }
//     }else{
//         if(!root->left && !root->right)
//         {
//             delete root;
//             return nullptr;
//         }
//         else if(root->left && !root->right)
//         {
//             TreeNode*  temp = root->left;
//             delete root;
//             return temp;
//         }else if(!root->left && root->right){
//             TreeNode*  temp = root->right;
//             delete root;
//             return temp;
//         }else{
//             TreeNode*  temp = root->right;
//             if(!temp->left)
//             {
//                 //delete root->left;
//                 root->val = temp->val;
//                 root->right = temp->right;
//                 delete temp;
//             }else{
//                 while(temp->left->left)
//                 {
//                     temp = temp->left;
//                 }
//                 root->val = temp->left->val;
//                 delete temp->left;
//                 temp->left = nullptr;
//             }            
//         }
//     }
//     return root;
// }

int main(){
    //std::vector<int> root = {3,5,6,NULL,NULL,2,7,NULL,NULL,4,NULL,NULL,1,0,NULL,NULL,8,NULL,NULL};
    //std::vector<int> root = {5,3,2,NULL,NULL,4,NULL,NULL,6,NULL,7,NULL,NULL};
    //std::vector<int> root = {3,1,NULL,2,NULL,NULL,4,NULL,NULL};
    //std::vector<int> root = {1};
    //std::vector<int> root = {3,2,NULL,NULL,5,4,NULL,NULL,10,8,7,NULL,NULL,NULL,15,NULL,NULL};
    //std::vector<int> root = {3,1,NULL,2,NULL,NULL,4,NULL,NULL};
    //std::vector<int> root = {2,1,33,NULL,2,25,40,NULL,NULL,11,31,34,45,10,18,29,32,NULL,36,43,46,4,NULL,12,24,26,30,NULL,NULL,35,39,42,44,NULL,48,3,9,NULL,14,22,NULL,NULL,27,NULL,NULL,NULL,NULL,38,NULL,41,NULL,NULL,NULL,47,49,NULL,NULL,5,NULL,13,15,21,23,NULL,28,37,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,8,NULL,NULL,NULL,17,19,NULL,NULL,NULL,NULL,NULL,NULL,NULL,7,NULL,16,NULL,NULL,20,6};
// 33
    //TreeNode* root_node_ = buildBinaryTree(root);
    //std::vector<int> root = {5,3,6,2,4,NULL,7};
    std::vector<int> root = {3, 1, 4, NULL, 2, NULL, NULL};
    TreeNode* root_node_ = buildBinaryTreeByLevelOrder(root);
    //int key = 33;
    int key = 1;
    TreeNode* root_node_after_ = deleteNode(root_node_, root_node_, key);
    printBinaryTreeByLevelOrder(root_node_after_);
    std::cout << std::endl;
}