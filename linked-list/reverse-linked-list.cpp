/*

题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-linked-list

给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 

示例 1：


输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
示例 2：


输入：head = [1,2]
输出：[2,1]
示例 3：

输入：head = []
输出：[]
 

提示：

链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000
 

进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
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

 ListNode* reverse_linked_list(ListNode* head)
 {
    if(head == nullptr){ return nullptr;}
    ListNode* pre_node=nullptr, *cur_node=head, *next_node=head->next;
    while(cur_node != nullptr)
    {
        cur_node->next = pre_node;
        pre_node = cur_node;
        cur_node = next_node;
        if(next_node != nullptr){
            next_node = next_node->next;
        }
    }
    return pre_node;
 }

 int main()
 {
    vector<int>nums = {1,2,3,4,5};
    ListNode* head = create_linked_list(nums);
    ListNode* reversed_head = reverse_linked_list(head);
    print(reversed_head);
    return 0;
 }