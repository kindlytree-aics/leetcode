/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-preorder-traversal

给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

示例 1：

输入：root = [1,null,2,3]
输出：[1,2,3]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [1]
输出：[1]
示例 4：


输入：root = [1,2]
输出：[1,2]
示例 5：


输入：root = [1,null,2]
输出：[1,2]
 

提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>



std::vector<int> preorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> statck_;
    TreeNode* cur_iter_node_ = root;
    std::vector<int>result;
    while(cur_iter_node_)
    {
        result.push_back(cur_iter_node_->val);
        statck_.push(cur_iter_node_);
        if(cur_iter_node_->left){
            cur_iter_node_ = cur_iter_node_->left;
        }else{
            while(!statck_.empty() && !statck_.top()->right)
            {
                statck_.pop();
            }
            if(!statck_.empty())
            {
                cur_iter_node_ = statck_.top()->right;
                statck_.pop();
            }else{
                return result;
            }
        }
    }
    return result;
}

std::vector<int> inorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack_;
    TreeNode* cur_iter_node_ = root;
    std::vector<int>result;
    while(cur_iter_node_)
    {
        while(cur_iter_node_->left){
            stack_.push(cur_iter_node_);
            cur_iter_node_ = cur_iter_node_->left;
        }
        result.push_back(cur_iter_node_->val);
        if(cur_iter_node_->right)
        {
            cur_iter_node_ = cur_iter_node_->right;
        }else{
            if(!stack_.empty()){
                cur_iter_node_ = stack_.top();
                result.push_back(cur_iter_node_->val);
                stack_.pop();
                while(!cur_iter_node_->right && !stack_.empty())
                {
                    cur_iter_node_ = stack_.top();
                    result.push_back(cur_iter_node_->val);
                    stack_.pop();
                }
                cur_iter_node_ = cur_iter_node_->right;
            }else{
                return result;
            }
        }
    }
    return result;
}


std::vector<int> postorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack_;
    TreeNode* cur_iter_node_ = root;
    std::vector<int>result;
    while(cur_iter_node_)
    {
        //当前节点左子树非空,递进遍历左节点
        while(cur_iter_node_->left){
            stack_.push(cur_iter_node_);
            cur_iter_node_ = cur_iter_node_->left;
        }
        //如果当前节点的左子树为空，但右子树不为空，继续将右子树的跟节点作为当前节点
        //开始下一轮迭代
        if(cur_iter_node_->right)
        {
            stack_.push(cur_iter_node_);
            cur_iter_node_ = cur_iter_node_->right;
        }else{
            //左右子树均为空，输出叶子节点到数组
            result.push_back(cur_iter_node_->val);
            while(!stack_.empty())
            {
                TreeNode* stack_top_ = stack_.top();
                //如果当前节点为左节点，则循环检测栈顶的有节点是否为空
                if(cur_iter_node_ == stack_top_->left)
                {
                    //如果当前节点的右节点为空，循环遍历直至右节点非空
                    while(!stack_.empty() && !stack_.top()->right)
                    {
                        cur_iter_node_ = stack_.top();
                        result.push_back(cur_iter_node_->val);
                        stack_.pop();
                    }
                    //否则
                    if(!stack_.empty() && cur_iter_node_ == stack_.top()->right)
                    {
                        cur_iter_node_ = stack_.top();
                        result.push_back(cur_iter_node_->val);
                        stack_.pop();
                        if(!stack_.empty())
                        {
                            cur_iter_node_ = stack_.top();
                            break;
                        }else{
                            return result;
                        }

                    }
                    else if(!stack_.empty())
                    {
                        cur_iter_node_ = stack_.top()->right;
                        break;
                    }
                }else{//为右节点，循环直至栈为空，或者不为右节点，即为左节点
                    while(!stack_.empty() && cur_iter_node_ == stack_.top()->right)
                    {
                        cur_iter_node_ = stack_.top();
                        result.push_back(cur_iter_node_->val);
                        stack_.pop();
                    }
                    if(!stack_.empty())
                    {
                        result.push_back(cur_iter_node_->val);
                    }
                }
            }
            if(stack_.empty())
            {
                return result;
            }
        }
    }
    return result;
}

int main(){
    //std::vector<int> root = {1,NULL,2,3};
    //std::vector<int> root = {2,3,NULL,1};
    //std::vector<int> root = {1,NULL,2,3};
    //std::vector<int> root = {3,2,NULL,NULL,4,1};
    //std::vector<int> root = {1,NULL,2};
    std::vector<int> root = {3,1,NULL,NULL,2};
    TreeNode* root_node_ = buildBinaryTree(root);
    std::vector<int> result_preorder = preorderTraversal(root_node_);
    for(int i = 0; i < result_preorder.size(); i++)
    {
        std::cout << result_preorder[i] ;
    }
    std::cout << std::endl;

    std::vector<int> result_inorder = inorderTraversal(root_node_);
    for(int i = 0; i < result_inorder.size(); i++)
    {
        std::cout << result_inorder[i] ;
    }
    std::cout << std::endl;

    std::vector<int> result_postorder = postorderTraversal(root_node_);
    for(int i = 0; i < result_postorder.size(); i++)
    {
        std::cout << result_postorder[i] ;
    }
    std::cout << std::endl;
    // std::vector<int> result_postorder;
    // postorderTraversal(root_node_, result_postorder);
    // for(int i = 0; i < result_postorder.size(); i++)
    // {
    //     std::cout << result_postorder[i] ;
    // }
}