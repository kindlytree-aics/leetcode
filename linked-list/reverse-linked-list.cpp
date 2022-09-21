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