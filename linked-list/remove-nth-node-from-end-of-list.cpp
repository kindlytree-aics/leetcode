/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/remove-nth-node-from-end-of-list
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

示例 1：


输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
示例 2：

输入：head = [1], n = 1
输出：[]
示例 3：

输入：head = [1,2], n = 1
输出：[1]
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

 ListNode* remove_nth_node_from_endof_list(ListNode* head, int n)
 {
    //利用快指针和慢指针实现；
    //快指针提前走n步，当快指针遍历到指针结尾的时候
    //慢指针就是需要删除的node
    ListNode* slow_node_ptr=head, *fast_node_ptr=head, *prev_node_ptr = head;
    int fast_steps = 1;
    while(fast_node_ptr->next != nullptr){
        if(fast_steps < n){
            fast_node_ptr = fast_node_ptr->next;
            fast_steps++;
            continue;
        }
        fast_node_ptr = fast_node_ptr->next;
        prev_node_ptr = slow_node_ptr;
        slow_node_ptr = slow_node_ptr->next;
    }
    if(fast_steps < n){
        return head;
    }else if(slow_node_ptr == head){
        head = head->next;
        delete slow_node_ptr;
    }else{
        prev_node_ptr->next = slow_node_ptr->next;
        delete slow_node_ptr;
    }
    return head;
 }

 int main()
 {
    vector<int>nums = {1,2,3,4,5};
    ListNode* head = create_linked_list(nums);
    ListNode* phead = remove_nth_node_from_endof_list(head, 2);
    print(phead);
    return 0;
 }