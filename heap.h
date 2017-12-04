#ifndef HEAP_H
#define HEAP_H


template<class T>
class Heap {
private:
    int len;
    T *root;
    void heapfy(T *ch);
    void build(T ch[]);
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

    T extractMin();
    void insert(T ch);
    void decreaseKey(T *node,int key);
};


#endif // HEAP_H
