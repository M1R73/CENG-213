#ifndef SORTED_DOUBLY_LINKED_LIST_IMPL_H
#define SORTED_DOUBLY_LINKED_LIST_IMPL_H

#include "SortedDoublyLinkedList.h"
#include "Exception.h"

// -------------------------
// Node Implementation
// -------------------------
template <class T>
DLLNode<T>::DLLNode(const T& item, DLLNode<T>* nextNode, DLLNode<T>* prevNode)
    : item(item), next(nextNode), prev(prevNode) {}

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
SortedDoublyLinkedList<T>::SortedDoublyLinkedList() {
    head = new DLLNode<T>(T());
    tail = new DLLNode<T>(T());
    head->next = tail;
    tail->prev = head;
}

template <class T>
SortedDoublyLinkedList<T>::~SortedDoublyLinkedList() {
    DLLNode<T> *cur=head,*temp;
    while(cur!=tail){
        temp=cur;
        cur=cur->next;
        delete temp;
    }
    delete tail;
}

template <class T>
SortedDoublyLinkedList<T>::SortedDoublyLinkedList(const SortedDoublyLinkedList<T>& other) {
    head = new DLLNode<T>(T());
    tail = new DLLNode<T>(T());
    head->next = tail;
    tail->prev = head;
    DLLNode<T> *cur=other.head->next,*newNode,*cur2=head;
    while(cur!=other.tail){
        InsertItem(cur->item);
        cur=cur->next;
        /*newNode=new DLLNode<T>(cur->item,NULL,NULL);
        cur2->next=newNode;
        newNode->prev=cur2;
        cur=cur->next;
        cur2=cur2->next;*/
    }
    /*cur2->next=tail;
    tail->prev=cur2;*/
    
    
    
}

template <class T>
SortedDoublyLinkedList<T>& SortedDoublyLinkedList<T>::operator=(const SortedDoublyLinkedList<T>& other) {
    DLLNode<T> *cur=other.head->next,*newNode,*cur2=head;
    DLLNode<T> *cur1=head->next,*temp;
    if(this!=&other){
        
        while(cur1!=tail){
            temp=cur1;
            cur1=cur1->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
            while(cur!=other.tail){
            InsertItem(cur->item);
            cur=cur->next;
        }
        
        
    }
    return *this;
}

// -------------------------
// Core Operations
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::InsertItem(const T& item) {
    
    
    
    DLLNode<T> *newNode,*cur=head,*next;
    if(head->next==tail){
        newNode=new DLLNode<T>(item,tail,head);
        tail->prev=newNode;
        head->next=newNode;
        return;
    }
    while(cur->next!=tail){
        if(item.P<cur->next->item.P){
            next=cur->next;
            newNode=new DLLNode<T>(item,cur->next,cur);
            cur->next=newNode;
            next->prev=newNode;
            return;
            
        }
        else {
            cur=cur->next;
        }
    }
    if(cur->item.P<item.P||cur->item.P==item.P){
        newNode=new DLLNode<T>(item,tail,cur);
        cur->next=newNode;
        tail->prev=newNode;
    }
}

template <class T>
void SortedDoublyLinkedList<T>::InsertItemPrior(const T& item) {
    
    
    
    
    DLLNode<T> *newNode,*cur=head,*next;
    if(head->next==tail){
        newNode=new DLLNode<T>(item,tail,head);
        tail->prev=newNode;
        head->next=newNode;
        return;
    }
    while(cur->next!=tail){
        if(item.P<cur->next->item.P||item.P==cur->next->item.P){
            next=cur->next;
            newNode=new DLLNode<T>(item,cur->next,cur);
            cur->next=newNode;
            next->prev=newNode;
            return;
            
        }
        
        else {
            cur=cur->next;
        }
    }
    if(cur->item.P<item.P){
        newNode=new DLLNode<T>(item,tail,cur);
        cur->next=newNode;
        tail->prev=newNode;
    }
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveFirstItem() {
    DLLNode<T> *cur,*next;
    T store;
    if(head->next==tail){
        throw EmptyCollectionException();
    }
    cur=head->next;
    next=head->next->next;
    store=cur->item;
    head->next=head->next->next;
    next->prev=head;
    delete cur;
    return store;
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveFirstItem(int priority) {
    DLLNode<T> *cur=head->next,*temp,*next,*prev=head;
    T store;
    if(head->next==tail){
        throw EmptyCollectionException();
    }
    while(cur!=tail){
        if(cur->item==priority){
            next=cur->next;
            temp=cur;
            store=cur->item;
            prev->next=cur->next;
            next->prev=prev;
            delete temp;
            return store;
        }
        cur=cur->next;
        prev=prev->next;
    }
    throw NotFoundException();
    
    /*DLLNode<T> *cur=head,*temp,*next;
    T store;
    if(head->next==tail){
        throw EmptyCollectionException();
    }
    while(cur->next!=tail){
        if(cur->next->item==priority){
            next=cur->next->next;
            temp=cur->next;
            store=cur->next->item;
            cur->next=cur->next->next;
            next->prev=cur;
            delete temp;
            return store;
        }
        cur=cur->next;
    }
    throw NotFoundException();*/
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveLastItem(int priority) {
    DLLNode<T> *cur=head,*temp=NULL,*prev,*next;
    T store;
    if(head->next==tail){
        throw EmptyCollectionException();
    }
    while(cur->next!=tail){
        if(cur->next->item==priority){
            prev=cur;
            next=cur->next->next;
            temp=cur->next;
        }
        cur=cur->next;
    }
    if(temp==NULL)throw NotFoundException();
    store=temp->item;
    prev->next=next;
    next->prev=prev;
    delete temp;
    
    
    return store ;
}

// -------------------------
// Query
// -------------------------
template <class T>
const T& SortedDoublyLinkedList<T>::FirstItem() const {
    if(head->next==tail){
        throw EmptyCollectionException();
    }
    return head->next->item;
}

template <class T>
const T& SortedDoublyLinkedList<T>::LastItem() const {
     if(head->next==tail){
        throw EmptyCollectionException();
    }
    return tail->prev->item;
}

template <class T>
bool SortedDoublyLinkedList<T>::IsEmpty() const {
    if(head->next==tail){
        return true;
    }
    return false;
}

template <class T>
size_t SortedDoublyLinkedList<T>::GetSize() const {
    DLLNode<T> *cur=head->next;
    size_t count=0;
    while(cur!=tail){
        cur=cur->next;
        count++;
    }
    return count;
}

// -------------------------
// Modification
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::SplitByPriority(SortedDoublyLinkedList<T>& low,
                                                SortedDoublyLinkedList<T>& high,
                                                int pivotPriority) {
    DLLNode<T> *cur=head->next;
    while(cur!=tail){
        if(cur->item.P<=pivotPriority){
            low.InsertItem(cur->item);
        }
        else{
            high.InsertItem(cur->item);
        }
        cur=cur->next;
    }
}

template <class T>
void SortedDoublyLinkedList<T>::SplitAlternating(SortedDoublyLinkedList<T>& listA,
                                                 SortedDoublyLinkedList<T>& listB) {
    DLLNode<T> *cur=head->next;
    while(cur!=tail&&cur->next!=tail){
        listA.InsertItem(cur->item);
        listB.InsertItem(cur->next->item);
        cur=cur->next->next;
    }
    if(cur!=tail){
        listA.InsertItem(cur->item);
    }
}

template <class T>
SortedDoublyLinkedList<T>
SortedDoublyLinkedList<T>::Merge(const SortedDoublyLinkedList<T>& a,
                                 const SortedDoublyLinkedList<T>& b) {
       
    SortedDoublyLinkedList<T> newList;                                 
    
    DLLNode<T> *cur1=a.head->next,*cur2=b.head->next;
    while(cur1!=a.tail&&cur2!=b.tail){
        if(cur1->item<cur2->item||cur1->item==cur2->item){
            newList.InsertItem(cur1->item);
            cur1=cur1->next;
        }
        else{
            newList.InsertItem(cur2->item);
            cur2=cur2->next;
        }
        
    }
    if(cur1==a.tail){
        while(cur2!=b.tail){
            newList.InsertItem(cur2->item);
            cur2=cur2->next;
        }
        
    }
    if(cur2==b.tail){
        while(cur1!=a.tail){
            newList.InsertItem(cur1->item);
            cur1=cur1->next;
        }
    }
    return newList;
}

// -------------------------
// Modification
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::Clear() {
    DLLNode<T> *cur=head->next,*temp;
    while(cur!=tail){
        temp=cur;
        cur=cur->next;
        delete temp;
        
    }
    head->next = tail;
    tail->prev = head;
}

// -------------------------
// Operator <<
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const SortedDoublyLinkedList<T>& list) {
    if (list.head->next == list.tail) {
        os << "Empty";
        return os;
    }
    DLLNode<T>* curr = list.head->next;
    while (curr != list.tail) {
        os << curr->item;
        if (curr->next != list.tail)
            os << " -> ";
        curr = curr->next;
    }
    return os;
}

#endif // SORTED_DOUBLY_LINKED_LIST_IMPL_H
