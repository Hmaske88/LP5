#include <iostream>
#include <omp.h>

// #include <bits/stdc++.h>
#include <ctime>
#include <iomanip>

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

void BFS(vector<vector<int>>& graph, int start)
{
    int n=graph.size();
    vector<bool> visited(n,false);
    queue<int> q;

    visited[start]=true;
    q.push(start);

    while(!q.empty())
    {
        int current=q.front();
        q.pop();
        cout<<current<<" ";

        for(int i=0; i<graph[current].size(); i++)
        {
            if(visited[graph[current][i]]==false)
            {
                visited[graph[current][i]]=true;
                q.push(graph[current][i]);
            }
        }

    }
}

void parallelBFS(vector<vector<int>>& graph, int start)
{
        int n=graph.size();
        vector<bool> visited(n,false);
        queue<int> q;

        visited[start]=true;
        q.push(start);

    while(!q.empty())
    {
        #pragma omp parallel
        {
            int current=q.front();
            q.pop();
            cout<<current<<" ";
            #pragma omp for
            for(int i=0; i<graph[current].size(); i++)
            {
                #pragma omp critical
                if(visited[graph[current][i]]==false)
                {
                    visited[graph[current][i]]=true;
                    q.push(graph[current][i]);
                }
            }

        }
    }
}

void DFSutil(vector<vector<int>>& graph, int current, vector<bool>& visited)
{
    visited[current]=true;
    cout<<current<<" ";

    for(int i=0; i<graph[current].size(); i++)
    {
        int adjacent=graph[current][i];
        if(!visited[adjacent])
        {
            DFSutil(graph, adjacent, visited);
        }
    }
}

void DFS(vector<vector<int>>& graph, int start)
{
    int n= graph.size();
    vector<bool> visited(n,false);

    DFSutil(graph, start, visited);
}


void parallelDFSutil(vector<vector<int>>& graph, int current, vector<bool>& visited)
{
    visited[current]=true;
    cout<<current<<" ";

    #pragma omp parallel for
    for(int i=0; i<graph[current].size(); i++)
    {
        int adjacent=graph[current][i];
        if(!visited[adjacent])
        {
            DFSutil(graph, adjacent, visited);
        }
    }
}

void parallelDFS(vector<vector<int>>& graph, int start)
{
    int n= graph.size();
    vector<bool> visited(n,false);

    parallelDFSutil(graph, start, visited);
}

int main()
{
    vector<vector<int>> graph={{1,2},{0,3,4},{0,5},{1},{1},{2}};

    clock_t start, end;
    double total1, total2;

    start=clock();
    cout<<"sequential BFS output : ";
    BFS(graph,0);
    end=clock();

    total1=double(end-start)/double(CLOCKS_PER_SEC);
    cout<<"\nSequential time : "<<fixed<<setprecision(10)<<total1;

    start=clock();
    cout<<"\nparallel BFS output : ";
    parallelBFS(graph,0);
    end=clock();

    total2=double(end-start)/double(CLOCKS_PER_SEC);
    cout<<"\nParallel time : "<<fixed<<setprecision(10)<<total2;

    cout<<"\nSpeedup : "<<total1/total2;



    start=clock();
    cout<<"\n\nsequential DFS output : ";
    DFS(graph,0);
    end=clock();

    total1=double(end-start)/double(CLOCKS_PER_SEC);
    cout<<"\nSequential time : "<<fixed<<setprecision(10)<<total1;

    start=clock();
    cout<<"\nparallel DFS output : ";
    parallelBFS(graph,0);
    end=clock();

    total2=double(end-start)/double(CLOCKS_PER_SEC);
    cout<<"\nParallel time : "<<fixed<<setprecision(10)<<total2;

    cout<<"\nSpeedup : "<<total1/total2;

    return 0;
}



// CODE FOR USER INPUT GRAPH

// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//     // Prompt the user to enter the number of nodes in the graph
//     int numNodes;
//     cout << "Enter the number of nodes in the graph: ";
//     cin >> numNodes;
    
//     // Initialize the graph as a vector of vectors
//     vector<vector<int>> graph(numNodes);
    
//     // Prompt the user to enter the adjacency list for each node
//     for (int i = 0; i < numNodes; ++i) {
//         cout << "Enter the adjacency list for node " << i << " (separated by spaces, terminate with -1): ";
//         int neighbor;
//         while (cin >> neighbor && neighbor != -1) {
//             graph[i].push_back(neighbor);
//         }
//     }
    
//     // Display the entered graph
//     cout << "Entered graph:" << endl;
//     for (int i = 0; i < numNodes; ++i) {
//         cout << "Node " << i << ": ";
//         for (int j = 0; j < graph[i].size(); ++j) {
//             cout << graph[i][j] << " ";
//         }
//         cout << endl;
//     }
    
//     return 0;
// }
