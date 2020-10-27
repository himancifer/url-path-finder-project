#include<bits/stdc++.h>
using namespace std;

//Adj List Implementation for Integer Nodes
class Graph{
    int V;

    //Array of Linked Lists, Size = V, So there will be V linked lists
    list<int> *adjList;

public:
    Graph(int v){
        V = v;
        adjList = new list<int>[V];
    }

    //Taking edge to be biderectional by default
    void addEdge(int u,int v,bool bidir = true){
        adjList[u].push_back(v);
        if(bidir){
            adjList[v].push_back(u);
        }
    }

    void printAdjList(){
        //For all the vertices
        for(int i = 0; i<V;i++){
            cout<<i<<"--> ";
            //For each node in the array .... For eg all the nodes that are present in the adjList[0] block
            for(int node : adjList[i]){
                cout<<node<<",";
            }
            cout<<endl;
        }
    }

    void printPath(vector<int>& srcParent, vector<int>& destParent,int src, int dest, int intersectNode)
    {
        vector<int> path;
        path.push_back(intersectNode);
        int i = intersectNode;
        while (i != src)
        {      
            path.insert(path.begin(),srcParent[i]);
            i = srcParent[i];
        }  
        i = intersectNode;
        while(i != dest)
        {
            path.push_back(destParent[i]);
            i = destParent[i];
        }
 
        cout<<"Path :: "<<endl;
        for(int el : path){
            cout<<el<<" --> ";
        }
        cout<<endl;
    }

    int isIntersecting(vector<bool>& srcVisited, vector<bool>& destVisited)
    {
        int intersectNode = -1;
        for(int i=0; i < V; i++)
        {
            // if a vertex is visited by both front
            // and back BFS search return that node
            // else return -1
            if(srcVisited[i] && destVisited[i])
                return i;
        }
        return -1;
    }
 

    void BFS(queue<int>& q,vector<bool>& visited,vector<int>& parent){ 
        int current = q.front();
        q.pop();
        for(int neighbour : adjList[current]){
            if(!visited[neighbour]){
                q.push(neighbour);
                visited[neighbour] = true;
                parent[neighbour] = current;
            }
        }
    }

    int bidirectional(int src,int dest){

        vector<bool> srcVisited(V,false);
        vector<bool> destVisited(V,false);
        vector<int> srcParent(V,-1);
        vector<int> destParent(V,-1);
        queue<int> srcQueue, destQueue;
        int intersectNode = -1;
        
        srcQueue.push(src);
        srcVisited[src] = true;
        srcParent[src] = -1;
        
        destQueue.push(dest);
        destVisited[dest] = true;
        destParent[dest] = -1;

        while(!srcQueue.empty() && !destQueue.empty()){
             // Do BFS from source and target vertices
            BFS(srcQueue, srcVisited, srcParent);
            BFS(destQueue, destVisited, destParent);
 
            // check for intersecting vertex
            intersectNode = isIntersecting(srcVisited, destVisited);
 
            // If intersecting vertex is found
            // that means there exist a path
            if(intersectNode != -1)
            {
                cout << "Path exist between " << src << " and "
                 << dest << "\n";
                cout << "Intersection at: " << intersectNode << "\n";
 
                // print the path and exit the program
                printPath(srcParent, destParent, src, dest, intersectNode);
                
                exit(0);
            }
        }

        return -1;
    }
};

int main(){
    int n=15;
 
    // source vertex
    int s=0;
 
    // target vertex
    int t=14;
 
    // create a graph given in above diagram
    Graph g(n);
    g.addEdge(0, 4);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(8, 9);
    g.addEdge(8, 10);
    g.addEdge(9, 11);
    g.addEdge(9, 12);
    g.addEdge(10, 13);
    g.addEdge(10, 14);
    if (g.bidirectional(s, t) == -1)
        cout << "Path don't exist between "
             << s << " and " << t << "\n";
 
    return 0;
}