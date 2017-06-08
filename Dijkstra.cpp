#include <iostream>
using std::cout; using std::endl; using std::cin;
#include <vector>
#include <string>
using std::string;
#include<unordered_set>
#include<list> 
#include<map>

struct Node
{
	int id;
	int weight;
	Node(int id, int weight)
	{
		this->id = id;
		this->weight = weight;
	}
};

struct Graph
{
	std::vector< std::list<Node> > adj;
	
	Graph(int size)
	{
		for(int i = 0; i < size; i++)
		{
			adj.push_back( std::list<Node>() );
		}
	}
	
	void add(int from, int to, int weight)
	{
		adj[from].push_back( Node(to, weight)  );
		adj[to].push_back( Node(from, weight)  );
	}
	
	void remove(int from, int to)
	{
		for(auto it = adj[from].begin(); it != adj[from].end(); it++)
		{
			if( (*it).id == to )
			{
				adj[from].erase(it);
				break;
			}
		}
		
		
		for(auto it = adj[to].begin(); it != adj[to].end(); it++)
		{
			if( (*it).id == from )
			{
				adj[to].erase(it);
				break;
			}
		}
	}
	
	//For debugging, prints out the adjacency list
	void p()
	{
		for(int i = 0; i < adj.size(); i++)
		{
			cout << i << ": ";
			for(Node entry : adj[i])
			{
				cout << "[" << entry.id << ", " << entry.weight << "] ";
			}
			cout << endl;
		}
		cout << endl;
	}
	
	//Finds the node with the lowest distance in the open set. 
	int minDist(std::unordered_set<int>& open, std::map<int, int>& dist)
	{
		int minId;
		int min = 999999;
		
		for(auto entry: open)
		{
			if (dist[entry] < min)
			{
				minId = entry;
				min = dist[entry];
			}
		}
		
		return minId;
	}
	
	void path(int start, int goal)
	{
		std::unordered_set<int> closed;
		std::unordered_set<int> open;
		open.insert(start);
		
		std::map<int, int> cameFrom;
		std::map<int, int> dist;
		
		dist[start] = 0;
		
		while(open.size() > 0)
		{
			int current = minDist(open, dist);
			if(current == goal)
			{
				printPath(cameFrom, current);
				return;
			}
			
			open.erase( open.find(current) );
			closed.insert(current);
			
			for(auto node: adj[current])
			{
				if( closed.find(node.id) != closed.end() )
					continue;
				
				int tempDist = dist[current] + node.weight;
				if( open.find(node.id) == open.end()  )
				{
					open.insert(node.id);
				}
				else if(tempDist >= dist[node.id])
				{
					continue;
				}
				
				cameFrom[node.id] = current;
				dist[node.id] = tempDist;
			}
		}
		
		cout << "no path found!" << endl;
		
	}
	
	void printPath(std::map<int,int> cameFrom, int current)
	{
		std::vector<int> path;
		path.push_back(current);
		
		while(cameFrom.find(current) != cameFrom.end())
		{
			path.push_back(cameFrom[current]);
			current = cameFrom[current];	
		}
		
		for(int i = path.size()-1; i >= 0; i--)
		{
			cout << path[i] << " ";
		}
		cout << endl;
	}
	
};


int main()
{
	int size, edges;
	cout << "Enter the number of nodes and number of edges, space seperated (e.g. 7 6): ";
	cin >> size >> edges;
	Graph graph(size);
	
	cout << "Input connections for weighted undirected graph. Enter two Node IDs and the weight of their edge (e.g. 0 2 10) " << endl;
	for(int i = 0; i < edges; i++)
	{
		int from, to, weight;
		cout << edges-i << " edges left" << endl;
		cin >> from >> to >> weight;
		graph.add(from, to, weight);
	}
	cout << endl;
	
	cout << "Adjacency list: " << endl;
	graph.p();
	cout << endl;
	
	cout << "enter starting node and ending node: ";
	int start, goal;
	cin >> start >> goal;
	graph.path(start, goal);
		
	
	return 0;
}