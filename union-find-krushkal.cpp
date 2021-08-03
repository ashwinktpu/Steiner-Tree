 #include<iostream>
 #include<algorithm>
 #include<vector>
 #include<bits/stdc++.h>
 using namespace std;
 
 struct edgepairs{
  int x;
  int y;
  int weight;
};

//class for an edge in a graph
 class Edge{
   public:
   int ss, dd, ww;
   //ss = source edge
   //dd = destination edge
   //ww = weight of an edge
   Edge( int ss, int dd, int ww)
   { //constructor
     this->ss = ss;
     this->dd = dd;
     this->ww = ww;
   }
 };

//class for a graph
 class Graph{
   public:
   vector<Edge>  All_edges;// to hold list of all edges of the graph

   //member function to add an edge to the undirected graph
   void addEdge(int s, int d, int w)
   {
      Edge obj(s, d, w);//create one edge
      All_edges.push_back(obj);//push one edge to edge container
   }

   };

  //declare a displayMST function to define it later
  void displayMST(const vector<Edge> &);

//class for finding MST in the graph
  class Kruskal {

  public:
  int totalVertices;//total vertices

  vector<pair<int,int>> subsets;
  // subsets will hold list of [parent - rank] pairs
  // which we will use in Union Find
  // by path compression algorithm

  vector<Edge> mst;//declare a container to store edges of MST

 //constructor
    Kruskal( int totalVertices)
    {
       this->totalVertices =totalVertices;

       subsets.resize(totalVertices);
       //resize subsets equal to total vertices

       for( int i= 0; i<totalVertices; ++i)
        {
          subsets[i].first =i; //set parent value equal to respective index
          subsets[i].second = 0; //set rank value equal to zero
        }
    }

    static bool comparator( Edge &a , Edge& b)
    {
      return a.ww < b.ww;
    }

    void createMST( Graph& graph)
    {
      //sort the edges of graph in increasing order of their weights
     sort( graph.All_edges.begin(), graph.All_edges.end(), comparator );

    int i=0, e=0;
    // i =  variable to keep track of total vertices
    // e = variable to keep track of total edges in MST formed so far
    // total edges in MST  == (total vertices - 1)

    //iterate through list of edges in a graph
    while( e < (totalVertices-1) && i < graph.All_edges.size() )
    {
      //store current edge
      Edge currEdge = graph.All_edges[i++];

      //find absolute parent
     //to detect if current edge form a cycle with MST formed so far
      int x = _find( currEdge.ss);//pass current source vertex
      int y = _find( currEdge.dd );//pass current destination vertex

      if( x != y)//is they don't form a cycle
      {
        //push current edge to MST
        mst.push_back( currEdge );
        //then make that two vertex Union
        // in other words to create edge between two vertices
        makeUnion( x, y);
      }
    }

    //finally display the MST created by the above function
    displayMST( mst );

    }

   int _find(  int i)
   {
       if( subsets[i].first!=i)//if index is not equal to parent value
       {
         //recursively call _find()
         // and pass current parent value
         subsets[i].first = _find( subsets[i].first );

       }

       return subsets[i].first;
   }

   void makeUnion( int x, int y)
   {
     int xroot = _find( x);
     int yroot = _find(y);

    // if-else for rank comparison & update parent-rank values
     if( subsets[xroot].second < subsets[yroot].second)
     {
       subsets[xroot].first= yroot;
     }
     else if( subsets[xroot].second > subsets[yroot].second)
     {
       subsets[yroot].first=xroot;
     }
     else{
       subsets[xroot].first=yroot;
       subsets[yroot].second++;
      }
   }

 };

  // funciton to display all edges of MST & total cost
  void displayMST(  const vector<Edge>&  edges)
  {
     long long int totalMinimumCost=0;
    cout<<"All MST edges [source - destination = weight]\n";

    for( auto edge : edges)
    {
      cout<<edge.ss<<" - "<<edge.dd<<" = "<<edge.ww<<'\n';

      totalMinimumCost+=edge.ww;
    }
    cout<<"total minimum cost = "<<totalMinimumCost<<endl;
  }


 int main(int argc, char **argv)
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
		
        
        

    Graph g;
   
      for(int i=0;i<COO.size();i++){
            g.addEdge(COO[i].x,COO[i].y,COO[i].weight);

        }
        

   clock_t start , end1;
   double cpu_time_used;


   //create and object of kruskal class
   Kruskal graph(n);

   //call kruskal class's member function to find MST
   start = clock();
   graph.createMST( g);
   end1 = clock();

   cpu_time_used = ((double) (end1 - start)) / CLOCKS_PER_SEC;
    printf("the time taken = %f in sec",cpu_time_used);

   return 0;

 }
