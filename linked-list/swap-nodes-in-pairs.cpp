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