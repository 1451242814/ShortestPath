#ifndef HEAP_H
#define HEAP_H
#include <algorithm>


template<class T>
class Heap {
private:
    int len;
    T *root;
    void heapfy(T *ch)
    {
        if(ch-root==len)
            return;
        T *less;
        less=left(ch);
        if(right(ch)<root+len && *right(ch)<*less)
            less=right(ch);
        if(*less<*ch)
        {
            std::swap(*less,*ch);
            if(less-root<len/2-1)
                heapfy(less);
        }
    }

    void build(T ch[])
    {
        for(int i=len/2-1;i>=0;i--)
        {
           heapfy(ch+i);
        }
    }
public:

    Heap(T* r,int n):
        len(n),root(r)
    {
        build(r);
    }


    T *right(T * ch)
    {
        return (ch-root+1)*2+root;
    }
    T *left(T *ch)
    {
        return (ch-root+1)*2-1+root;
    }
    T *parent(T *ch)
    {
        return (ch-root-1)/2+root;
    }

    T extractMin()
    {
        T t=root[0];
        root[0]=root[len-1];
        len--;
        heapfy(root);
        return t;
    }
    void insert(const T &ch)
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

    bool empty() const
    {
        return len<1;
    }
};


#endif // HEAP_H
