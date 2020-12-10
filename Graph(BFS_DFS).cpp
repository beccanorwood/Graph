//Rebecca Norwood
//Student ID: 200430599
//Email: norwo009@cougars.csusm.edu

//=======================================================================

#include <array>
#include <string>
#include <iostream>

using namespace std; 

//=======================================================================
						/*Classes*/ 
						/*Methods*/
						/*Variables*/ 
						
class Queue; 
class Graph; 
class Node; 

typedef Node* NodePtr;

//=======================================================================

			/*Node structure for adjacency list*/


struct edge{
	int adj_vtx; 
	edge *next; 
};

struct Edge
{
    edge *head;  //pointer to head node of list
};


//Function to create a new node 
edge* newEdge(int adj_vtx)
{
    edge *ptr = new edge;
    ptr->adj_vtx = adj_vtx;
    ptr->next = NULL;
    return ptr;
}

//=======================================================================

							/*Node class*/
							
class Node
{
public:
	int Number;
	NodePtr next;
	Node() { Number = 0; next = NULL; }
	Node(int n) { Number = n; next=NULL;}
};							
							
//=======================================================================

							/*Queue class*/							
				
class Queue
{
	NodePtr first; 
	NodePtr last; 
	int currSize; 
	
public:
	Queue(); 
	bool push(int num); //"Enqueue"
	int peek() const; 
	bool pop();  //"Dequeue" 
	bool empty(); 
}; 


Queue::Queue()
{
	first = NULL; 
	last = NULL; 
	currSize = 0; 
}

bool Queue::push(int num)
{

	NodePtr n = new Node(num);  
	if(last == NULL)
	{
		first = last = n; 
		currSize++; 
		return true;
	}

	last->next = n; 
	last = n; 
	currSize++;
	return true; 
	
}

int Queue::peek() const
{
	return first->Number; 
}

bool Queue::pop()
{
	if(empty())
	{
		return false;
	}
	
	NodePtr temp = first; 
	first = first->next;
	delete temp; 
	currSize--; 
	return true; 
}


bool Queue::empty()
{
	return currSize == 0; 
}

//=======================================================================


class Graph{
	int V; //NUmber from vertices 
	Edge *adj; //Pointer to an array containing adjacency lists
	void DFSUtil(int v, bool visited[]); //A function used by DFS
	
public: 
	Graph(int V); //Constructor
	void addEdge(int v, int w); //A function to add an edge to the graph
	void BFS(int s); //BFS traversal of the vertices reachable from s 
	void DFS(int v); //DFS traversal of the vertices reachable from v
	bool hasCycle(); //Check whether the graph has cycles 
	void print(); 
	int listLength(int index);
	
};

Graph::Graph(int V)
{

	this->V = V;  
	adj = new Edge[V]; 
	
	//Initalize all values to of nodes to be null 
	for(int i = 0; i < V; i++){ 
		adj[i].head = nullptr; 
	}

}


void Graph::addEdge(int v, int w)
{
    //add an edge from src to dest
    edge *nptr = newEdge(w);
    nptr->next = adj[v].head;
    adj[v].head = nptr;

    // as graph is undirected, add an edge from dest to src also
    nptr = newEdge(v);
    nptr->next = adj[w].head;
    adj[w].head = nptr;
}

void Graph::BFS(int s)
{
	bool *visited = new bool[V]; 
	
	for(int i = 0; i < V; i++){
		visited[i] = false;
	}
	
	Queue q; 
	q.push(s);
	visited[s] = true; 
	
	int length = listLength(s); 
	
	edge* temp = adj[s].head; 
	
	while(!q.empty())
	{
		s = q.peek(); 
		cout << s << " "; 
		q.pop(); 
		
		for(int i = 0; i < length; i++)
		{
			if(!visited[temp->adj_vtx])
			{
				visited[temp->adj_vtx] = true; 
				q.push(temp->adj_vtx); 	
			}	
		} 
		
	}
	
}


void Graph::DFSUtil(int v, bool visited[])
{
	visited[v] = true; 
	cout << v << " "; 
	
	edge* temp = adj[v].head; 
	
	int length = listLength(v); 
	
	for(int i = 0; i < length; i++){
		
		if(!visited[temp->adj_vtx])
		{
			DFSUtil(temp->adj_vtx, visited); 	
		}
	}
	
}

void Graph::DFS(int v)
{
	bool* visited = new bool[V]; 
	
	for(int i = 0; i < V; i++){
		visited[i] = false; 
	}
	
	DFSUtil(v, visited); 
}

int Graph::listLength(int index)
{
	edge* temp = adj[index].head; 
	
	int count = 0; 
	
	while(temp != NULL){
		count++; 
		temp = temp->next; 
	}	
	
	cout << "Count: " << count; 
	
	return count; 
	
}


//function to print the graph
void Graph::print()
{
   for(int i=0;i<V;i++)
    {
        edge *root = adj[i].head;
        
        cout<<"Adjacency list of vertex "<<i<<endl;

        while(root!=NULL)
        {
            cout << root->adj_vtx <<" -> ";
            root=root->next;
        }
        
        cout<<endl;
    }
}


int main()
{
    Graph g(4); 

    //connect edges
    g.addEdge(0,3);
    g.addEdge(0,1);
    g.addEdge(2,3);
    g.addEdge(1,3);
    g.addEdge(4,3);
    

    g.print();
    
    //g.BFS(0);
  

	return 0; 
}

