#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define mk make_pair
#define pb push_back
#define MOD 1000000007
#define fo(i, a, b) for (i = a; i < b; i++)
#define boost                    \
    ios::sync_with_stdio(false); \
    cin.tie(0)
using namespace std;

 struct edgepairs{
  int x;
  int y;
  int weight;
};

// Adding u to v nodes to the graph and weight between them
void AddWeightedEdge(unordered_map<int, unordered_set<int>> &graph, vector<pair<int, pair<int, int>>> &edges, int u, int v, int w)
{
    graph[u].insert(v);
    graph[v].insert(u);
    edges.push_back({w, {u, v}});
}

// DFS on the node
void DFS(unordered_map<int, unordered_set<int>> &graph, vector<bool> &visited, int node)
{
    visited[node] = 1;
    for (auto neighbour : graph[node])
    {
        if (!visited[neighbour])
        {
            DFS(graph, visited, neighbour);
        }
    }
}

// Checking if the graph is connected after removing the edge
bool checkConnected(unordered_map<int, unordered_set<int>> &graph, int V)
{
    // vector to keep track of visited and initialized to 0
    vector<bool> visited(V, 0);

    // Starting DFS from node 0
    DFS(graph, visited, 0);

    // Checking if each node is visited. If a node is not visited that means the graph is disconnected and we return 0
    // The removed edge needs to be added again
    for (int i = 0; i < V; i++)
        if (visited[i] == 0)
            return 0;

    // If all nodes are visited removing the edge does keep the graph connected
    return 1;
}

void reverseDeleteMST(unordered_map<int, unordered_set<int>> &graph, vector<pair<int, pair<int, int>>> &edges, int V)
{
    // Sorting the edges
    sort(edges.begin(), edges.end());

    // Weight of the MST
    long long int mstWeight = 0;
    int u, v;

    for (int i = edges.size() - 1; i >= 0; i--)
    {
        u = edges[i].second.first;
        v = edges[i].second.second;

        // Deleting the edge from the graph
        graph[u].erase(v);
        graph[v].erase(u);

        // Check if the graph is connected after removing the edge
        if (checkConnected(graph, V) == 0)
        {
            // Re-adding the edge as the graph gets disconnected
            graph[u].insert(v);
            graph[v].insert(u);

            cout << "Edge : " << u << " " << v << "\n";
            mstWeight += edges[i].first;
        }
    }
    cout << "Weight of MST is : " << mstWeight << "\n";
}

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
		
		
		   
 
        printf("printing coo matrix\n");

        for(int i=0;i<COO.size();i++){

            printf("%d %d %d\n",COO[i].x,COO[i].y,COO[i].weight);

        }
        
		
        printf("finished printing coo");
		
        
   
      
    int V = n;
    unordered_map<int, unordered_set<int>> graph;
    vector<pair<int, pair<int, int>>> edges;
	
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    // Adding nodes to the graph and edges
    // Same graph as the one in the example
	
	auto t1 = high_resolution_clock::now();
	for(int i=0;i<COO.size();i++){
            AddWeightedEdge(graph, edges, COO[i].x, COO[i].y, COO[i].weight);

        }

    // Calling reverse Delete MST

    reverseDeleteMST(graph, edges, V);
	auto t2 = high_resolution_clock::now();
	
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	 std::cout << ms_int.count() << "ms\n";
}

