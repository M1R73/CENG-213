#ifndef MULTIPLE_QUEUE_IMPL_H
#define MULTIPLE_QUEUE_IMPL_H

#include "MultipleQueue.h"
#include "Exception.h"

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
MultipleQueue<T>::MultipleQueue(size_t n)
    : count(n)
{
    queues = new Queue<T>[count];
}

template <class T>
MultipleQueue<T>::~MultipleQueue() {
    size_t i;
    for(i=0;i<count;i++){
        queues[i].Clear();
    }
    delete [] queues;
}

// -------------------------
// Core Operations
// -------------------------
template <class T>
int MultipleQueue<T>::Enqueue(const T& value) {
    size_t i,least_size,ind=0;
    if(count==0)return -1;
    least_size=queues[0].GetSize();
    for(i=0;i<count;i++){
        if(queues[i].GetSize()<least_size){
            least_size=queues[i].GetSize();
            ind=i;
        }
        
    }
    queues[ind].Enqueue(value);
    return ind;
    
}

template <class T>
T MultipleQueue<T>::Dequeue(size_t index) {
    size_t i;
    if(index>=count)throw IndexOutOfRangeException();
    
     if(queues[index].IsEmpty()){
            throw EmptyCollectionException();
        }
    
    queues[index].Dequeue();
}

template <class T>
const Queue<T>& MultipleQueue<T>::GetQueue(size_t index) const {
    if(index>=count)throw IndexOutOfRangeException();
    
    return queues[index];
}

// -------------------------
// Utility
// -------------------------
template <class T>
size_t MultipleQueue<T>::GetNumberOfQueues() const {
    return count;
}

template <class T>
size_t MultipleQueue<T>::GetTotalSize() const {
    size_t i;
    int sum=0;
    for(i=0;i<count;i++){
        sum+=queues[i].GetSize();
    }
    return sum;
}

template <class T>
size_t MultipleQueue<T>::GetSizeOfQueue(size_t index) const {
    if(index>=count)return 0;
    
    return queues[index].GetSize();
}

// -------------------------
// Operator <<
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const MultipleQueue<T>& mq) {
    for (size_t i = 0; i < mq.count; ++i) {
        os << "Queue " << i << ": " << mq.queues[i];
        if (i < mq.count - 1) {
            os << std::endl;
        }
    }
    return os;
}
#endif // MULTIPLE_QUEUE_IMPL_H