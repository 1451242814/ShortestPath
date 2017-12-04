#include <iostream>
#include <fstream>
#include <hash_map>
#include <string>
#include <cstring>
#include <list>
#include <vector>
#include <heap.h>


using namespace std;
using namespace __gnu_cxx;


/////Test


///////

struct Edge
{
    int endID;
    float len;
    float speed;
};

struct Vertex
{
    int id;
    float dis;
    list<Edge> edgeList;
};

class Graph
{
private:
    hash_map<int,int> _verTb;
    void genVer(ifstream & verfs)
    {
        int key;
        Vertex ver;
        while(verfs)
        {

           verfs>>key;
           verfs.ignore(1024,'\n');
           ver.id=key;
           _ver.push_back(ver);
           _verTb[key]=_verNum;
           _verNum+=1;
        }
    }
    void genEdgeList(vector<Vertex> &verLs,ifstream &edgefs)
    {
        int startNode;
        int endNode;
        Edge edg;

        while(edgefs)
        {
            edgefs.ignore(20,':');
            edgefs>>startNode;

            edgefs.ignore(20,':');
            edgefs>>endNode;
            edg.endID=endNode;

            edgefs.ignore(20,':');
            edgefs>>edg.len;

            edgefs.ignore(20,':');
            edgefs>>edg.speed;

            verLs[_verTb[startNode]].edgeList.push_front(edg);

            edgefs.ignore(1024,'\n');
        }
    }

public:
    const static float MAX_DIS;
    int _verNum;
    vector<Vertex> _ver;
    Graph(ifstream &verfs,ifstream &edgefs):_verNum(0)
    {
       genVer(verfs);

       genEdgeList(_ver,edgefs);
    }
    int findDisPath(int start, int end,hash_map<int,int> &path);
    int findTimPath(int start,int end,vector<vector<int>> & path);
};

const float Graph::MAX_DIS=1e10;

struct Node
{
    Vertex *ver;

    Node(int _dis)
    {
        ver->dis=_dis;
    }

    Node()
    {
    }

    bool operator <(const Node &node)
    {
        return this->ver->dis<node.ver->dis;
    }
};

int Graph::findDisPath(int start,int end,hash_map<int,int> &path)
{
    Node set[_verNum];//保存已经探索到的节点
    Node heapArray[_verNum];//堆操作的数组
    int setPos=0;//保存已经探索的节点在数组中的位置

    for(int i;i<_verNum;i++)
    {
        heapArray[i].ver=&_ver[i];
        heapArray[i].ver->dis=Graph::MAX_DIS;
    }

    heapArray[_verTb[start]].ver->dis=0;

    Heap<Node> heap(heapArray,_verNum);

    Node t;
    float newDis;
    int endNode;
    while(heap.empty()==false)
    {
       t=heap.extractMin();
       for(auto iter:t.ver->edgeList)
       {
           newDis=iter.len+t.ver->dis;
           endNode=_verTb[iter.endID];
           if(newDis<_ver[endNode].dis)
           {
               _ver[endNode].dis=newDis;
              // heap.decreaseKey(_ver[endNode]});
               path[iter.endID]=t.ver->id;
           }
           set[setPos++]=t;
       }
    }
    return _ver[_verTb[end]].dis;

}

void genTb(hash_map<int,int> &verTb,const string &fname)
{
     ifstream fs;
     fs.open(fname.c_str());
     if(fs.fail())
     {
         cout<<"Open vertex file failed!"<<endl;
         return;
     }
     string s;
     int verNum=0;
     int key;
     while(fs)
     {
        fs>>s;
        key=atoi(s.c_str());
        verTb[key]=verNum;
        verNum+=1;
     }
     return ;

}

int main(int argc,char *argv[])
{
    const string verfname="D:\\Qt\\build\\ShortestPath\\sfo_nodes.txt";
    const string edgfname="D:\\Qt\\build\\ShortestPath\\sfo_roads.txt";

    ifstream verfs,edgfs;
    verfs.open(verfname.c_str());

    if(verfs.fail())
    {
        cout<<"Open vertex file failed!"<<endl;
        return 1;
    }

    edgfs.open(edgfname.c_str());
    if(edgfs.fail())
    {
        cout<<"Open edge file failed! "<<endl;
        return 1;
    }

    Graph map(verfs,edgfs);


    hash_map<int,int> path;
    int start,end;
    cin>>start>>end;
    cout<<map.findDisPath(start,end,path);

    return 0;
}
