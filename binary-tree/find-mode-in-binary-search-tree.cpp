/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/find-mode-in-binary-search-tree

给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有 众数（即，出现频率最高的元素）。

如果树中有不止一个众数，可以按 任意顺序 返回。

假定 BST 满足如下定义：

结点左子树中所含节点的值 小于等于 当前节点的值
结点右子树中所含节点的值 大于等于 当前节点的值
左子树和右子树都是二叉搜索树
 

示例 1：


输入：root = [1,null,2,2]
输出：[2]
示例 2：

输入：root = [0]
输出：[0]
 

提示：

树中节点的数目在范围 [1, 104] 内
-105 <= Node.val <= 105
 

进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）

*/
#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <stack>
#include <queue>
#include <unordered_map>

struct cmp {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return lhs.second < rhs.second;
    }
};


//中序遍历递增,如果有重复的数字，则这些数字相邻
void inorderTraverse(TreeNode* root, std::vector<int>&inorder){
    if(root){
        if(root->left){
            inorderTraverse(root->left, inorder);
        }
        inorder.push_back(root->val);
        if(root->right)
        {
            inorderTraverse(root->right, inorder);
        }
    }else{
        return;
    }
}

//这道题可以不用priority_queue
//直接将map转换为vector，再对vector进行排序
//vector<pair<int, int>> vec(map.begin(), map.end());
//sort(vec.begin(), vec.end(), cmp); // 给频率排个序
//result.push_back(vec[0].first);
//for (int i = 1; i < vec.size(); i++) {
    // 取最高的放到result数组中
//    if (vec[i].second == vec[0].second) result.push_back(vec[i].first);
//    else break;
//}
//return result;


std::vector<int> findMode(TreeNode* root) {
    std::vector<int> inorder;
    inorderTraverse(root, inorder);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int, int>>, cmp> prio_queue;
    //没有key时，nums_count[i]进行初始化，
    std::unordered_map<int, int>nums_count;
    for(int i : inorder)
    {
        nums_count[i]++;
    }
    for(std::unordered_map<int ,int>::iterator it = nums_count.begin();
        it != nums_count.end(); it++)
        {
            prio_queue.push(*it);
        }
    std::vector<int> max_times_duplicate_values_;
    int duplicate_value_ = prio_queue.top().first;
    int max_duplicate_times = prio_queue.top().second;
    max_times_duplicate_values_.push_back(duplicate_value_);
    prio_queue.pop();
    while(!prio_queue.empty())
    {
        int cur_duplicate_times = prio_queue.top().second;
        if(cur_duplicate_times == max_duplicate_times)
        {
            max_times_duplicate_values_.push_back( prio_queue.top().first);
            prio_queue.pop();
        }else{
            break;
        }
    }
    return max_times_duplicate_values_;        
}

int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> root = {4,2,1,NULL,NULL,3, NULL,NULL,6,NULL,NULL};
    TreeNode* root_node_ = buildBinaryTree(root);
    //bool is_balanced = isBalanced(root_node_);
    std::vector<int> max_times_duplicate_values_ = findMode(root_node_);
    //std::cout << is_balanced << std::endl;
}