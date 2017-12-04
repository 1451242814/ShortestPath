#include <iostream>
#include <fstream>
#include <hash_map>
#include <string>
#include <cstring>
#include <list>
#include <vector>

using namespace std;
using namespace __gnu_cxx;

struct Edge
{
    int endID;
    float len;
    float speed;
};

struct Vertex
{
    int id;
    list<Edge> edgeList;
};

class Graph
{
private:
    int _verNum=0;
    hash_map<int,int> _verTb;
    void genVer(ifstream & verfs)
    {
        int key;
        Vertex ver;
        while(verfs)
        {

           verfs>>key;
           verfs.ignore();
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

            edgefs.ignore();
        }
    }

public:
    vector<Vertex> _ver;
    Graph(ifstream &verfs,ifstream &edgefs)
    {
       genVer(verfs);

       genEdgeList(_ver,edgefs);
    }
    int findDisPath(int start,int end,vector<vector<int>> & path);
    int findTimPath(int start,int end,vector<vector<int>> & path);
};

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

    cout<<map._ver[0].id<<'\t'<<map._ver[0].edgeList.front().len;
    return 0;
}
