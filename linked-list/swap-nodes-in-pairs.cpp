/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/swap-nodes-in-pairs

给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

示例 1：

输入：head = [1,2,3,4]
输出：[2,1,4,3]
示例 2：

输入：head = []
输出：[]
示例 3：

输入：head = [1]
输出：[1]
 

提示：

链表中节点的数目在范围 [0, 100] 内
0 <= Node.val <= 100
*/


#include<vector>
#include<iostream>
using namespace std;

typedef struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 }ListNode;


void print(ListNode* list)
{
    while(list){
        cout << list->val;
        list = list->next;
    }
    cout << endl;
}

ListNode* swap_pair(ListNode* head, ListNode** pre_pair_right, ListNode** left, ListNode** right)
{
    if(head != nullptr && head->next == nullptr)
    {
        //当前pair只有一个节点，最后一个pair
        if((*pre_pair_right) != nullptr)
        {
            (*pre_pair_right)->next = head;
        }
        *left = head;
        *right = head;
        return nullptr;
    }else
    {
        ListNode* ori_left = head, *ori_right=head->next, *next_pair_head=ori_right->next;
        //节点swap
        *right = ori_left;
        *left = ori_right;
        (*left)->next = *right;
        //上一个pair的右节点的next指向当前pair置换后的左节点
        if(*pre_pair_right != nullptr){
            (*pre_pair_right)->next = *left;
        }
        //当前pair即将作为上一个pair，将当前pair置换后的右节点的指针赋给pre_pair_right变量后返回
        *pre_pair_right = *right;
        return next_pair_head;
    }
}

 ListNode* create_linked_list(vector<int>&nums){
    ListNode* phead= new ListNode(nums[0]);
    ListNode* cur_node = phead;
    for(int i=1; i< nums.size(); i++){
        ListNode* node = new ListNode(nums[i]);
        cur_node->next = node;
        cur_node = node;
    }
    return phead;
 }

 int main()
 {
    vector<int>nums = {1,2,3};
    ListNode* head = create_linked_list(nums);
    ListNode* next_pair_head = head, *new_head = nullptr;

    ListNode* left=nullptr, *right = nullptr, *pre_pair_right =nullptr;
    while(next_pair_head != nullptr)
    {
        next_pair_head = swap_pair(next_pair_head, &pre_pair_right, &left, &right);
        if(new_head == nullptr){
            new_head = left;
        }
    }
    if(right != nullptr)
    {
        right->next = nullptr;
    }
    print(new_head);
    return 0;
 }