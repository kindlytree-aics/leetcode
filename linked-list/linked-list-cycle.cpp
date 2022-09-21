/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/linked-list-cycle-ii

给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

不允许修改 链表。

示例 1：

输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
示例 2：



输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：



输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。
 

提示：

链表中节点的数目范围在范围 [0, 104] 内
-105 <= Node.val <= 105
pos 的值为 -1 或者链表中的一个有效索引
 

进阶：你是否可以使用 O(1) 空间解决此题？
*/ 

#include <vector>
#include <iostream>
using namespace std;

typedef struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 }ListNode;

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

 ListNode* create_cycle_linked_list(vector<int>&nums, int pos){
    ListNode* phead= new ListNode(nums[0]);
    ListNode* cur_node = phead;
    ListNode* circle_entry_node = nullptr;
    int index = 0;
    if(pos == 0){ circle_entry_node = phead;}
    for(int i=1; i< nums.size(); i++){
        ListNode* node = new ListNode(nums[i]);
        cur_node->next = node;
        cur_node = node;
        index++;
        if(index == pos)
        {
            circle_entry_node = cur_node;
        }
    }
    cur_node->next = circle_entry_node;
    return phead;
 }

void print(ListNode* list)
{
    while(list){
        cout << list->val;
        list = list->next;
    }
    cout << endl;
}

ListNode *detectCycle_v0(ListNode *head) {
    int index = 0;
    ListNode* cur_node = head;
    vector<ListNode*>node_ptrs;
    while(cur_node != nullptr)
    {
        node_ptrs.push_back(cur_node);
        cur_node = cur_node->next;
        for(int i = 0; i<node_ptrs.size(); i++)
        {
            if(cur_node == node_ptrs[i])
            {
                return cur_node;
            }
        }
    }
    return nullptr;
}

ListNode *detectCycle(ListNode *head) {
    ListNode* slow_node_ptr = head, *fast_node_ptr = head;
    while(slow_node_ptr != nullptr && fast_node_ptr != nullptr)
    {
        slow_node_ptr = slow_node_ptr->next;
        if(fast_node_ptr->next != nullptr)
        {
            fast_node_ptr = fast_node_ptr->next->next;
        }else{
            return nullptr;
        }
        if(fast_node_ptr == slow_node_ptr){
            break;
        }
    }
    if(fast_node_ptr == nullptr){return nullptr;}
    slow_node_ptr = head;
    while(true)
    {
        //if语句要在上边判断，如果环形链表的头在第一个指针的时候直接就满足条件
        //表头为环形链表的入口指针时，fast指针走两圈，slow指针走一圈
        if(slow_node_ptr == fast_node_ptr){
            return slow_node_ptr;
        }
        slow_node_ptr= slow_node_ptr->next;
        fast_node_ptr = fast_node_ptr->next;
    }
}

 int main()
 {
    //vector<int> nums = {3, 2, 0, -4};
    //ListNode* cycle_linked_list = create_cycle_linked_list(nums, 1);
    vector<int> nums = {1,2};
    ListNode* cycle_linked_list = create_cycle_linked_list(nums, 0);
    ListNode* cycle_entry_node_ptr = detectCycle(cycle_linked_list);
    if(cycle_entry_node_ptr == nullptr)
    {
        cout << "null" << endl;
    }else{
        cout << cycle_entry_node_ptr->val << endl;
    }
    return 0;
    //print(head);
 }
