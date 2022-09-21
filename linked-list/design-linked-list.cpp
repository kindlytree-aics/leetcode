/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/design-linked-list

设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：val 和 next。val 是当前节点的值，next 是指向下一个节点的指针/引用。如果要使用双向链表，则还需要一个属性 prev 以指示链表中的上一个节点。假设链表中的所有节点都是 0-index 的。

在链表类中实现这些功能：

get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。
 

示例：

MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1,2);   //链表变为1-> 2-> 3
linkedList.get(1);            //返回2
linkedList.deleteAtIndex(1);  //现在链表是1-> 3
linkedList.get(1);            //返回3
 

提示：

所有val值都在 [1, 1000] 之内。
操作次数将在  [1, 1000] 之内。
请不要使用内置的 LinkedList 库。
*/

#include <vector>
#include <iostream>
using namespace std;


typedef struct Node{
    int val;
    Node* next;
    Node(int val):val(val),next(nullptr){}
}Node;

class MyLinkedList {

public:
    Node* pHead;

    MyLinkedList() {
        pHead = nullptr;
    }
    
    int get(int index) {//获取第index个node的val值
        if(index<0 || pHead == nullptr){
            return -1;
        }else{
            int cur_iter_index = -1;
            Node* cur_iter_node = pHead;
            while(cur_iter_node != nullptr)
            {
                cur_iter_index++;
                if(cur_iter_index == index){
                    break;
                }
                cur_iter_node = cur_iter_node->next;
            }
            if(cur_iter_index == index){
                return cur_iter_node->val;
            }else{
                return -1;
            }
        } 
    }
    
    void addAtHead(int val) {
        Node* cur_node = new Node(val);
        if(pHead == nullptr)
        {
            pHead = cur_node;
        }else{
            cur_node->next = pHead;
            pHead = cur_node;
        }
    }
    
    void addAtTail(int val) {
        Node* cur_node = new Node(val);
        if(pHead == nullptr)
        {
            pHead = cur_node;
        }else{
            Node* iter_node = pHead, *prev_node = pHead;
            while(iter_node != nullptr){
                prev_node = iter_node;
                iter_node = iter_node->next;
            }
            prev_node->next = cur_node;
        }
    }
    //在链表中的第 index 个节点之前添加值为 val  的节点。
    //如果 index 等于链表的长度，则该节点将附加到链表的末尾。
    //如果 index 大于链表长度，则不会插入节点。
    //如果index小于0，则在头部插入节点。
    void addAtIndex(int index, int val) {//0-index
        if(index <=0){
            Node* cur_node = new Node(val);
            if(pHead == nullptr)
            {
                pHead = cur_node;
            }else{
                cur_node->next = pHead;
                pHead = cur_node;
            } 
        }else{
            if(pHead == nullptr){
                return;
            }
            Node* iter_node = pHead, *prev_node = pHead;
            int cur_iter_index = -1;//index=1,index=n
            while(iter_node != nullptr){
                cur_iter_index++;
                if(cur_iter_index == index){
                    break;
                }
                prev_node = iter_node;
                iter_node = iter_node->next;
            }
            //index == cur_iter_index+1时为末尾
            if(cur_iter_index == index || index == cur_iter_index+1){
                Node* cur_node = new Node(val);
                cur_node->next = iter_node;
                prev_node->next = cur_node;
            }
        }
    }
    //如果索引 index 有效，则删除链表中的第 index 个节点。
    void deleteAtIndex(int index) {
        if(index < 0 || pHead == nullptr) return;
        int cur_iter_idx = -1;
        Node* cur_iter_node = pHead, *prev_node=pHead;
        while(cur_iter_node != nullptr){
            cur_iter_idx++;
            if(cur_iter_idx == index){
                break;
            }
            prev_node = cur_iter_node;
            cur_iter_node = cur_iter_node->next;
        }
        if(cur_iter_idx == index){
            if(index == 0)
            {
                Node* to_be_deleted_node  = pHead;
                pHead = pHead->next;
                delete to_be_deleted_node;
                return;
            }else{
                prev_node->next = cur_iter_node->next;
                delete cur_iter_node;
            }
        }
    }
};

int main()
{
    MyLinkedList* obj = new MyLinkedList();
// ["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]
// [[],[1],[3],[1,2],[1],[1],[1]]
    // obj->addAtHead(1);
    // obj->addAtTail(3);
    // obj->addAtIndex(1,2);
    // cout << obj->get(1) << endl;
    // obj->deleteAtIndex(1);
    // cout << obj->get(1) << endl;

    obj->addAtHead(7);
    obj->addAtHead(2);
    obj->addAtHead(1);
    obj->addAtIndex(3,0);
    obj->deleteAtIndex(2);
    obj->addAtHead(6); 
    obj->addAtHead(4);
    cout << obj->get(4) << endl;
    obj->addAtHead(4);
    obj->addAtIndex(5,0);
    obj->addAtHead(6);
    // obj->addAtHead(1);
    // obj->addAtTail(3);
    // obj->addAtIndex(1,2);   //链表变为1-> 2-> 3
    // obj->get(1);            //返回2
    // obj->deleteAtIndex(1);  //现在链表是1-> 3
    // obj->get(1);            //返回3  
    return 0;


// ["MyLinkedList","addAtHead","addAtHead","addAtHead","addAtIndex","deleteAtIndex","addAtHead","addAtTail","get","addAtHead","addAtIndex","addAtHead"]
// [[],[7],[2],[1],[3,0],[2],[6],[4],[4],[4],[5,0],[6]]
}
