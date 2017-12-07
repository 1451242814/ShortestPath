#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include "heap.h"


using namespace std;

struct Edge
{
    int endVer;
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
    unordered_map<int,int> _verTb;//建立一个从顶点id到顶点数组索引的映射
    void genVer(ifstream & verfs)
    {
        int key;
        Vertex ver;
        while(verfs)
        {

           verfs>>key;
           verfs.ignore(1024,'\n');
           ver.id=key;
		   ver.dis = Graph::MAX_DIS;
           _ver.push_back(ver);
           _verTb[key]=_verNum;
           _verNum+=1;
        }
    }
    void genEdgeList(vector<Vertex> &verLs,ifstream &edgefs)
    {
        int start;
        int end;
        Edge edg;

        while(edgefs)
        {
            edgefs.ignore(20,':');
            edgefs>>start;

            edgefs.ignore(20,':');
            edgefs>>end;
            edg.endVer=_verTb[end];

            edgefs.ignore(20,':');
            edgefs>>edg.len;

            edgefs.ignore(20,':');
            edgefs>>edg.speed;

            verLs[_verTb[start]].edgeList.push_front(edg);

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
    float findDisPath(int start, int end,unordered_map<int,int> &path,unordered_map<int,float> &time);
};

const float Graph::MAX_DIS = 1e10;


struct Node
{
	Vertex * ver;
	Node():ver(NULL)
	{

	}
	Node(Vertex *_ver) :ver(_ver)
	{

	}
    bool operator <(const Node &node)
    {
		return this->ver->dis < node.ver->dis;
    }
};

float Graph::findDisPath(int start,int end,unordered_map<int,int> &path,unordered_map<int,float> &time)
{
    bool *visited=new bool[_verNum];//保存已经探索到的节点
	Node *heapArray = new Node[_verNum];//堆操作的数组
	
    for(int i=0;i<_verNum;i++)
    {
		visited[i] = false;
    }

	int startNode = _verTb[start];

	_ver[startNode].dis = 0.0;
    Heap<Node> heap(heapArray,0);

	Node t = &_ver[startNode];
	heap.insert(t);
    float newDis;
    int endNode;
	time[start] = 0.0;
    while(heap.empty()==false)
    {
       t=heap.extractMin();
       for(auto iter:t.ver->edgeList)
       {
           newDis=iter.len+t.ver->dis;
           endNode=iter.endVer;
           if(visited[endNode] == false && newDis<_ver[endNode].dis)
           {
			   _ver[endNode].dis = newDis;
			   heap.insert(Node(&_ver[endNode]));
			   path[_ver[iter.endVer].id] = t.ver->id;
			   time[_ver[iter.endVer].id] = iter.len / iter.speed + time[t.ver->id];
           }
       }
       visited[t.ver-&_ver[0]]=true;
    }
	delete[] heapArray;
	delete[] visited;
	return _ver[_verTb[end]].dis;

}

void printPath(int start,int end,unordered_map<int, int> & path)
{
	if (end != start)
	{
		printPath(start, path[end], path);
		cout << "->" << end;
	}
	else
		cout << end;

}


int main(int argc,char *argv[])
{

	if (argc != 5)
	{
		cerr << "Wrong parameter!" << endl;
		return 1;
	}
	const char* verfname = argv[2];
	const char* edgfname = argv[1];

    ifstream verfs,edgfs;
    verfs.open(verfname);

    if(verfs.fail())
    {
        cerr<<"Open vertex file failed!"<<endl;
        return 1;
    }

    edgfs.open(edgfname);
    if(edgfs.fail())
    {
        cerr<<"Open edge file failed! "<<endl;
        return 1;
    }

    Graph map(verfs,edgfs);

    unordered_map<int,int> path;
	unordered_map<int, float> time;
    int start,end;
    start=atoi(argv[3]);
    end=atoi(argv[4]);
    float minDis=map.findDisPath(start,end,path,time);
	if (minDis == Graph::MAX_DIS)
	{
		cout << "Path not exist!"<<endl;
		system("pause");
		return 1;
	}

	cout << "Min Distance: " << minDis << endl;
	cout << "Path node ID: ";
	printPath(start, end, path);
	cout << endl << "Time used: " << time[end] << endl;


	system("pause");
    return 0;
}
