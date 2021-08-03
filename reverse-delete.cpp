// C++ program to find Minimum Spanning Tree
// of a graph using Reverse Delete Algorithm
#include<bits/stdc++.h>

using namespace std;

// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;

struct edgepairs{
  int x;
  int y;
  int weight;
};

// Graph class represents a directed graph
// using adjacency list representation
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;
    vector< pair<int, iPair> > edges;
    void DFS(int v, bool visited[]);

public:
    Graph(int V);   // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v, int w);

    // Returns true if graph is connected
    bool isConnected();

    void reverseDeleteMST();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(v); // Add w to v’s list.
    adj[v].push_back(u); // Add w to v’s list.
    edges.push_back({w, {u, v}});
}

void Graph::DFS(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to
    // this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i, visited);
}

// Returns true if given graph is connected, else false
bool Graph::isConnected()
{
    bool visited[V];
    memset(visited, false, sizeof(visited));

    // Find all reachable vertices from first vertex
    DFS(0, visited);

    // If set of reachable vertices includes all,
    // return true.
    for (int i=1; i<V; i++)
        if (visited[i] == false)
            return false;

    return true;
}

// This function assumes that edge (u, v)
// exists in graph or not,
void Graph::reverseDeleteMST()
{
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());

    long long int mst_wt = 0;  // Initialize weight of MST

    cout << "Edges in MST\n";

    // Iterate through all sorted edges in
    // decreasing order of weights
    for (int i=edges.size()-1; i>=0; i--)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        // Remove edge from undirected grap
        
        adj[u].remove(v);
        adj[v].remove(u);

        // Adding the edge back if removing it
        // causes disconnection. In this case this
        // edge becomes part of MST.
        
        if (isConnected() == false)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);

            // This edge is part of MST
            cout << "(" << u << ", " << v << ") \n";
            mst_wt += edges[i].first;
        }
        
        
    }

    cout << "Total weight of MST is " << mst_wt;
    
}

// Driver code
int main(int argc , char **argv)
{

    //File pointer declaration
    FILE *filePointer;
  long long int number;
 long long int n, m;

     char *filename = argv[1];
    filePointer = fopen( filename , "r") ;

    //checking if file ptr is NULL
        if ( filePointer == NULL )
        {
        printf( "input.txt file failed to open." ) ;
          return 0;
        }

        fscanf(filePointer, "%lld", &n );     //scaning the number of vertices
     fscanf(filePointer, "%lld", &m );
     
    printf("%lld %lld\n",n , m );
	  Graph g(n);

        vector <edgepairs> COO(m);
        //Reading from file and populate the COO
    for(int i=0 ; i<m ; i++ )
        {
        for(int j=0;j<2;j++){
   if ( fscanf(filePointer, "%lld", &number) != 1)
                        break;

        if( j == 0)
        {
            COO[i].x = number;
        }
        else if(j == 1)
        {
            COO[i].y = number;
        }

        }
        }
		
		for(long long int i=0 ; i<m ; i++ )
        {
			 COO[i].weight = i;
			
		}
        
        /*
		
        printf("printing coo matrix\n");

        for(int i=0;i<COO.size();i++){

            printf("%d %d %d\n",COO[i].x,COO[i].y,COO[i].weight);

        }
		
		 printf("finished coo matrix\n");
		 
		 */
		 
		 
       

  
   
      for(int i=0;i<COO.size();i++){
            g.addEdge(COO[i].x,COO[i].y,COO[i].weight);

        }
        

    

    clock_t start , end1;
    double cpu_time_used;

    start = clock();
    g.reverseDeleteMST();
    end1 = clock();


    cpu_time_used = ((double) (end1 - start)) / CLOCKS_PER_SEC;
    printf("\nthe time taken = %f in sec",cpu_time_used);
    return 0;
}
