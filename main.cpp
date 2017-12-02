#include <iostream>
#include <fstream>
#include <hash_map>
#include <string>
#include <cstring>

using namespace std;
using namespace __gnu_cxx;
class Graph
{
public:
    Graph()
    {

    }
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
     int t;
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
    const string fname="D:\\Qt\\build\\ShortestPath\\sfo_nodes.txt";
    hash_map<int,int> verTb;
    genTb(verTb,fname);
    cout<<verTb.size();
    return 0;
}
