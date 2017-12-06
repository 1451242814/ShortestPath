#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <vector>
#include "heap.h"
#include <unordered_map>


using namespace std;



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
    unordered_map<int,int> _verTb;
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
	const static float MAX_TIM;
    int _verNum;
    vector<Vertex> _ver;
    Graph(ifstream &verfs,ifstream &edgefs):_verNum(0)
    {
       genVer(verfs);

       genEdgeList(_ver,edgefs);
    }
    float findDisPath(int start, int end,unordered_map<int,int> &path,unordered_map<int,float> &time);
};

const float Graph::MAX_DIS=1e10;
const float Graph::MAX_TIM = 1e10;

struct Node
{
    Vertex *ver;
    int index;

    Node(float _dis)
    {
        ver->dis=_dis;
    }

    Node():ver(NULL)
    {
    }

    bool operator <(const Node &node)
    {
        return this->ver->dis<node.ver->dis;
    }
};

float Graph::findDisPath(int start,int end,unordered_map<int,int> &path,unordered_map<int,float> &time)
{
    bool *visited=new bool[_verNum];//保存已经探索到的节点
    Node *heapArray=new Node[_verNum];//堆操作的数组

    for(int i=0;i<_verNum;i++)
    {
        heapArray[i].ver=&_ver[i];
        heapArray[i].ver->dis=Graph::MAX_DIS;
        heapArray[i].index=i;
		visited[i] = false;
    }

    int startnode=_verTb[start]    ;
    heapArray[_verTb[start]].ver->dis=0;

    Heap<Node> heap(heapArray,_verNum);

    Node t;
    float newDis;
    int endNode;
	time[start] = 0.0;
    while(heap.empty()==false)
    {
       t=heap.extractMin();
       for(auto iter:t.ver->edgeList)
       {
           newDis=iter.len+t.ver->dis;
           endNode=_verTb[iter.endID];
           if(visited[endNode] == false && newDis<_ver[endNode].dis)
           {
               heap.decDis(endNode,newDis);
               path[iter.endID]=t.ver->id;
			   time[iter.endID] = iter.len / iter.speed + time[t.ver->id];
           }
       }
       visited[_verTb[t.ver->id]]=true;
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


int main(int argcc,char *argvv[])
{
	int argc = 5;
	char argv[][100] = {" ",
		"D:\\Qt\\build\\ShortestPath\\sfo_roads.txt",
		"D:\\Qt\\build\\ShortestPath\\sfo_nodes.txt",
		"984478356",
		"48531353"
	};

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
//    cin>>start>>end;
    start=atoi(argv[3]);
    end=atoi(argv[4]);
    float minDis=map.findDisPath(start,end,path,time);
	cout << "Min Distance: " << minDis << endl;
	cout << "Path node ID: ";
	printPath(start, end, path);
	cout << endl << "Time used: " << time[end] << endl;


	system("pause");
    return 0;
}
