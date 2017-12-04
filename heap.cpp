#include "heap.h"

template<typename T>
void Heap<T>::heapfy(T *ch)
{
    if(ch-root==len)
        return;
    T *less;
    less=left(ch);
    if(right(ch)<root+len && *right(ch)<*less)
        less=right(ch);
    if(*less<*ch)
    {
        T t=*ch;
        *ch=*less;
        *less=t;
        if(less-root<len/2-1)
            heapfy(less);
    }
}

template<typename T>
void Heap<T>::build(T ch[])
{
    for(int i=len/2-1;i>=0;i--)
    {
        heapfy(ch+i);
    }
}


template<typename T>
T Heap<T>::extractMin()
{
    T t=root[0];
    root[0]=root[len-1];
    len--;
    heapfy(root);
    return t;
}


template<typename T>
void Heap<T>::insert(T ch)
{
    len++;
    root[len-1]=ch;

    T *child=root +len-1;
    T *p=parent(child);
    while(child!=root && *child<*p)
    {
        T t;
        t=*p;
        *p=*child;
        *child=t;
        child=p;
        p=parent(p);
    }
}

template<typename T>
void Heap<T>::decreaseKey(T *node,int key)
{
    node->key=key;
    T t;
    while(node->key<parent(node)->key)
    {
        t=*node;
        *node=*parent(node);
        *parent(node)=t;
    }
}
