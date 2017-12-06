#ifndef HEAP_H
#define HEAP_H
#include <algorithm>



template<class T>
class Heap {
private:
    int len;
    T *root;
    void decreaseDis(T *node,float dis)
    {
        node->ver->dis=dis;
        T t;
        while(node!=root && *node<*parent(node))
        {
            std::swap(rawTb[(*node).index],rawTb[(*parent(node)).index]);
            std::swap(*node,*parent(node));
            node=parent(node);
        }
    }
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
            std::swap(rawTb[(*less).index],rawTb[(*ch).index]);
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

    //Using a raw table to build a map from raw index to new index on heap

    int *rawTb;

    Heap(T* r,int n):
        len(n),root(r)
    {
        rawTb=new int[len];
        for(int i=0;i<n;i++)
            rawTb[i]=i;
        build(r);
    }

    ~Heap()
    {
        delete [] rawTb;
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
    void insert(T ch)
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
    void decDis(int index,float dis)
    {
        decreaseDis(&root[rawTb[index]],dis);
    }

    bool empty() const
    {
        return len<1;
    }
};


#endif // HEAP_H
