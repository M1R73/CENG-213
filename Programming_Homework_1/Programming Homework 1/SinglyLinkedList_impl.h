#ifndef SINGLY_LINKED_LIST_IMPL_H
#define SINGLY_LINKED_LIST_IMPL_H

#include "SinglyLinkedList.h"
#include "Exception.h"

// -------------------------
// Node Implementation
// -------------------------
template <class T>
SLLNode<T>::SLLNode(const T& data, SLLNode<T>* next)
    : data(data), next(next) {}

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // dummy head node
    head = new SLLNode<T>(T(), NULL);
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Clear();
    delete head;
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
   
    head = new SLLNode<T>(T(), NULL);
    SLLNode<T> *cur2=other.head->next,*cur=head;
    while(cur2!=NULL){
        cur->next= new SLLNode<T>(cur2->data,NULL);
        cur2=cur2->next;
        cur=cur->next;
    }
    
}

template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    SLLNode<T> *cur2=other.head->next,*cur=head;
    if(this!=&other){
        Clear();
        while(cur2!=NULL){
            cur->next= new SLLNode<T>(cur2->data,NULL);
            cur2=cur2->next;
            cur=cur->next;
        }
    }
    return *this;
}

// -------------------------
// Basic Operations
// -------------------------
template <class T>
void SinglyLinkedList<T>::PushFront(const T& value) {
    SLLNode<T> * newNode= new SLLNode<T>(value,head->next);
    head->next=newNode;
}

template <class T>
void SinglyLinkedList<T>::PushBack(const T& value) {
    
    SLLNode<T> * newNode= new SLLNode<T>(value,NULL);
    SLLNode<T> *cur=head->next;
    if(head->next==NULL){
        head->next=newNode;
    }
    else{
        while(cur->next){
            cur=cur->next;
        }
        cur->next=newNode;
    }
}

template <class T>
T SinglyLinkedList<T>::PopFront() {
    SLLNode<T> *temp;
    if(head->next==NULL){
        throw EmptyCollectionException();
        
    }
    T store;
    store=head->next->data;
    temp=head->next;
    head->next=head->next->next;
    delete temp;
    return store;
}

template <class T>
T SinglyLinkedList<T>::PopBack() {
    T store;
    SLLNode<T> *temp,*prev;
    SLLNode<T> *cur=head->next;
    if(head->next==NULL){
        throw EmptyCollectionException();
    }
    
    prev=head;
    while(cur->next){
        cur=cur->next;
        prev=prev->next;
    }
    temp=cur;
    store=cur->data;
    prev->next=NULL;
    delete temp;
    
    return store;
    
   
    
    
}

// -------------------------
// Accessors
// -------------------------
template <class T>
bool SinglyLinkedList<T>::IsEmpty() const {
    if(head->next==NULL)return true;
    else{
        return false;
    }
}

template <class T>
size_t SinglyLinkedList<T>::GetSize() const {
    if(head->next==NULL)return 0;
    SLLNode<T> *cur= head->next;
    int count=0;
    while(cur){
        count++;
        cur=cur->next;
    }
    return count;
}

template <class T>
T& SinglyLinkedList<T>::Front() {
    if(head->next==NULL)throw EmptyCollectionException();
    return head->next->data;
    
}

template <class T>
const T& SinglyLinkedList<T>::Front() const {
    if(head->next==NULL)throw EmptyCollectionException();
    return head->next->data;
}

template <class T>
T& SinglyLinkedList<T>::Back() {
    SLLNode<T> *cur= head->next;
    if(head->next==NULL)throw EmptyCollectionException();
    while(cur->next){
        cur=cur->next;
    }
    return cur->data;
    
}

template <class T>
const T& SinglyLinkedList<T>::Back() const {
    SLLNode<T> *cur= head->next;
    if(head->next==NULL)throw EmptyCollectionException();
    while(cur->next){
        cur=cur->next;
    }
    return cur->data;
}

// -------------------------
// Searching & Removal
// -------------------------
template <class T>
bool SinglyLinkedList<T>::Contains(const T& value) const {
    SLLNode<T> *cur= head;
    while(cur){
        if(cur->data==value){
            return true;
        }
        cur=cur->next;
    }
    return false;
}

template <class T>
bool SinglyLinkedList<T>::Remove(const T& value) {
     SLLNode<T> *cur= head,*temp;
    while(cur->next){
        if(cur->next->data==value){
            temp=cur->next;
            cur->next=cur->next->next;
            delete temp;
            return true;
        }
        cur=cur->next;
    }
    return false;
}

// -------------------------
// Utility
// -------------------------
template <class T>
void SinglyLinkedList<T>::Clear() {
    SLLNode<T> *cur=head->next,*temp;
    while(cur!=NULL){
        temp=cur;
        cur=cur->next;
        delete temp;
    }
    head->next=NULL;
}

template <class T>
void SinglyLinkedList<T>::Reverse() {
    SLLNode<T> *cur=head->next,*prev=NULL,*after=NULL;
    while(cur){
        after=cur->next;
        cur->next=prev;
        prev=cur;
        cur=after;
    }
    head->next=prev;
    
}

// -------------------------
// Operator << Overload
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
    if (list.head->next == NULL) {
        os << "Empty";
        return os;
    }
    SLLNode<T>* curr = list.head->next; 
    while (curr != NULL) {
        os << curr->data;
        if (curr->next != NULL)
            os << " -> ";
        curr = curr->next;
    }
    return os;
}

#endif // SINGLY_LINKED_LIST_IMPL_H
