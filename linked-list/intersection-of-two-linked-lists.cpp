/*
给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。

图示两个链表在节点 c1 开始相交：

题目数据 保证 整个链式结构中不存在环。

注意，函数返回结果后，链表必须 保持其原始结构 。

示例 1：

输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
输出：Intersected at '8'
解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。
在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
示例 2：



输入：intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
输出：Intersected at '2'
解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B 为 [3,2,4]。
在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。
示例 3：



输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
这两个链表不相交，因此返回 null 。
 

提示：

listA 中节点数目为 m
listB 中节点数目为 n
0 <= m, n <= 3 * 104
1 <= Node.val <= 105
0 <= skipA <= m
0 <= skipB <= n
如果 listA 和 listB 没有交点，intersectVal 为 0
如果 listA 和 listB 有交点，intersectVal == listA[skipA + 1] == listB[skipB + 1]
 

进阶：你能否设计一个时间复杂度 O(n) 、仅用 O(1) 内存的解决方案？

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci
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

 ListNode* appendList(ListNode* front, ListNode*end)
 {
    ListNode* head = front, *cur_node = front;
    while(cur_node->next != nullptr)
    {
        cur_node = cur_node->next;
    }
    cur_node->next = end;
    return head;
 }

ListNode* find_intersection_node(ListNode* a, ListNode* b)
{
    int len_a = 0, len_b = 0;
    ListNode* cur_node = a;
    //获取a和b链表的长度
    //将更长的链表首先移动delta个node
    //然后两个链表同时移动，并比较node的指针值是否相等
    while(cur_node!= nullptr)
    {
        len_a++;
        cur_node = cur_node->next;
    }
    cur_node = b;
    while(cur_node != nullptr)
    {
        len_b++;
        cur_node = cur_node->next;
    }
    //bool a_is_longer = len_a > len_b ? true: false;
    int delta = abs(len_a-len_b);
    ListNode* need_iter_first_list = len_a > len_b ? a: b;
    ListNode* list_short = len_a > len_b ? b: a;
    cur_node = need_iter_first_list;
    while(delta > 0){
        cur_node = cur_node->next;
        delta--;
    }
    ListNode* cur1 = cur_node, *cur2 = list_short;
    while(cur1 != nullptr && cur2 != nullptr)
    { 
        if(cur1 == cur2){
            return cur1;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return nullptr;
}

int main()
 {
    //listA = [4,1,8,4,5], listB = [5,0,1,8,4,5]
    vector<int>nums_a_front_part = {4, 1};
    vector<int>nums_b_front_part = {5, 0, 1};
    vector<int>common_part = {8, 4, 5};
    ListNode*list_a_front_part = create_linked_list(nums_a_front_part);
    ListNode*list_b_front_part = create_linked_list(nums_b_front_part);
    ListNode*list_common = create_linked_list(common_part);
    ListNode*list_a = appendList(list_a_front_part, list_common);
    ListNode*list_b = appendList(list_b_front_part, list_common);

    ListNode* intersection_node = find_intersection_node(list_a, list_b);
    print(intersection_node);
    return 0;
 }
