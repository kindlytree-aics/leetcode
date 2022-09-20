/*给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
 

示例 1：


输入：head = [1,2,6,3,4,5,6], val = 6
输出：[1,2,3,4,5]
示例 2：

输入：head = [], val = 1
输出：[]
示例 3：

输入：head = [7,7,7,7], val = 7
输出：[]
 

提示：

列表中的节点数目在范围 [0, 104] 内
1 <= Node.val <= 50
0 <= val <= 50

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/remove-linked-list-elements
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


// ListNode* removeElements(ListNode* head, int val) {
//     ListNode* cur_node = head, *pre_node = head;
//     while(cur_node != NULL){
//         if(cur_node->val == val){
//             if(cur_node == head)
//             {
//                 head = cur_node->next;
//                 delete cur_node;
//                 pre_node = head;
//                 cur_node = head;
                
//             }else{
//                 pre_node->next = cur_node->next;
//                 delete cur_node;
//                 cur_node = pre_node->next;
//             }
//         }else{
//             pre_node = cur_node;
//             cur_node = cur_node->next;
//         }
//     }
//     return head;
// }

void print(ListNode* list)
{
    while(list){
        cout << list->val;
        list = list->next;
    }
    cout << endl;
}

ListNode* removeElements(ListNode* phead, int val)
{
    ListNode* cur_node = phead, *pre_node=phead;
    while(cur_node != NULL)
    {
        if(cur_node->val == val)
        {
            if(cur_node == phead)
            {
                cur_node = phead->next;
                pre_node = cur_node;
                delete phead;
                phead = cur_node;
            }else
            {
                pre_node->next = cur_node->next;
                delete cur_node;
                cur_node = pre_node->next;
            }
        }else
        {
            pre_node = cur_node;
            cur_node = cur_node->next;
        }
    }
    return phead;
}
 
 int main()
 {
    vector<int> nums = {1,2,6,3,4,5,6};
    int val = 6;
    ListNode* linked_list = create_linked_list(nums);
    ListNode* head = removeElements(linked_list, val);
    print(head);
 }