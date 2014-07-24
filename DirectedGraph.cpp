//Bryan Clark
//509-294-4161
//bryan.clark@email.wsu.edu

DirectedGraph::DirectedGraph()
{
	// No initialization needed
}

DirectedGraph::~DirectedGraph()
{
	// Free all nodes and edges
	for (int i = 0; i < m_nodes.size(); i++)
	{
		delete m_nodes[i];
	}
	m_nodes.clear();
	for (int i = 0; i < m_edges.size(); i++)
	{
		delete m_edges[i];
	}
	m_edges.clear();

	// Free/clear additional things here if needed
}

bool DirectedGraph::AddNode(const string& nodeName, const string& nodeData)
{
	// We don't add the node if one with the same name already exists
	if (NodeExists(nodeName)) { return false; }

	// You must complete the implementation of this function. Allocate a new 
	// node and add it to your node list(s) and return true on success.
	Node* newNode = new Node(nodeName, nodeData);
	 m_nodes.push_back(newNode);
	return true;


}
	
// Adds an edge to the graph that starts at the source node, 
// and goes to the target node.
// If the graph already contains an edge going from the specified 
// source to target node then false is returned and no modification 
// occurs.
// If either or both of the two nodes don't exist in the graph then 
// false is returned and no modification occurs.
// Otherwise the edge will be added. Note that an edge from N1 (source) 
// to N2 (target) is different than an edge from N2 (source) to N1 (target).
bool DirectedGraph::AddEdge(const string& sourceNodeName,
	const string& targetNodeName)
{
	// You must implement this function
	// Make sure to do the following:
	// 1. First make sure both nodes exist. If either one does NOT exist then 
	//    return false and do not add the edge.
	if((NodeExists(sourceNodeName) == false) || (NodeExists(targetNodeName) == false))
	{
		return false;
	}
	// 2. Allocate a new edge and add it to the edge list. Remember that the 
	//    the edges refer to nodes by index value, so you'll need to find the 
	//    indices of the source and target nodes based on their names.
	
	// two arbitrary index values 
	int i = 0;
	int j = 0;

	// iterate through the list of nodes from beginning to end
	// then compare to value trying to find, if true, find distance of index
	for(std::vector<Node*>::iterator item = m_nodes.begin(); item != m_nodes.end(); ++item)
	{
		// *item gets item at current dereferenced location
		if((*item)->Name.compare(sourceNodeName) == 0)
		{
			// i is the index of where it occurs in m_nodes
			i = std::distance(m_nodes.begin(),item);
			break;
		}
	}
	
	// iterate through the list of nodes from beginning to end
	// then compare to value trying to find, if true, find distance of index
	for(std::vector<Node*>::iterator item = m_nodes.begin(); item != m_nodes.end(); ++item)
	{
		// *item gets item at current dereferenced location
		if((*item)->Name.compare(targetNodeName) == 0)
		{
			// j is index of where it occurs in m_nodes
			j = std::distance(m_nodes.begin(),item);
			break;
		}
	}
	
	//create source and target indicies
	int SourceEdge = i;
	int TargetEdge= j;
	//crete new edge based on indicies
	Edge* newEdge = new Edge( SourceEdge, TargetEdge);

	// 3. Add the edge as an outgoing edge for the source node 		
	m_nodes.at(i)->Out.push_back(newEdge);
	//and an incoming edge for the target node.
	m_nodes.at(j)->In.push_back(newEdge);

	// 4. Return true if you did 2 through 4 successfully.
	return true;
}

// Gets the degree of the node with the specified name. -1 is returned 
// if no such node exists in the graph.
int DirectedGraph::GetDegree(const string& nodeName)
{
	// You must implement this function
	// Remember that the degree of a node is the sum of the number of edges 
	int edgesIN = 0; //
	int edgesOut = 0;
	int size = m_nodes.size();
	// go through the vector list
	for(int i = 0; i <= size; i++)
	{
		//compare the current node name to the name passed in
		if(m_nodes.at(i)->Name.compare(nodeName) == 0)
		{
			// get edges going in to Node
			edgesIN = m_nodes.at(i)->In.size();
			// get edges going out to Node
			edgesOut = m_nodes.at(i)->Out.size();
			// return sum
			return (edgesIN + edgesOut);
		}

	}
	return 0;

}

bool DirectedGraph::GetShortestPath(const string& startNode, const string& endNode, 
	bool nodeDataInsteadOfName, vector<string>& traversalList)
{
	// You must implement this function
	int INFINITY = 10000;
	// Find a path from the starting node to the ending node

	// If no such path exists, return false and you're done
	// If such a path DOES exist, you need to add either each node's Name (if 
	// nodeDataInsteadOfName is false) or each node's Data (if nodeDataInsteadOfName 
	// is true) to the traversal list. So after the function completes the traversal 
	// list consists of values (Name or Data) from nodes along the shortest path 
	// from start to end.


	/*You don't need to add anything to the node struct. In the shortest path algorithm just 
	allocate an array of ints for the distances and an array of bools for keeping track of 
	visited nodes. The number of items in both arrays will be equal to m_nodes.size().*/

	int* distance = new int[m_nodes.size()];
	bool* visited = new bool[m_nodes.size()];
	
	//initialize two arrays
	/*for(int initial = 0; initial <= m_nodes.size(); initial++)
	{
		distance[initial] = INFINITY;
		visited[initial] = false;
	}*/
	memset(distance,INFINITY,m_nodes.size());
	memset(visited,false,m_nodes.size());
	
	int i = 0;
	for(std::vector<Node*>::iterator item = m_nodes.begin(); item != m_nodes.end(); ++item)
	{
		// *item gets item at current dereferenced location
		if((*item)->Name.compare(startNode) == 0)
		{
			// i is index of where it occurs in m_nodes
			i = std::distance(m_nodes.begin(),item);
			break;
		}
	}

	distance[i] = 0;
	//visited[i] = true;
	

	int x = 0;
	for(int currDist = 0; currDist < m_nodes.size(); currDist++)
	{
		//for each vertex v
		//cout << m_nodes.at(currDist)->Name << endl;
		for(std::vector<Node*>::iterator item = m_nodes.begin(); item != m_nodes.end(); ++item)
		{
			 x = std::distance(m_nodes.begin(),item);
			if((visited[x] == false) && (distance[x] == currDist))
			{
				// v.known = true;
				visited[x] = true;
				
				// for each vertex w adjacent to v
				for(std::vector<Edge*>::iterator adj = m_nodes.at(x)->Out.begin(); adj != m_nodes.at(x)->Out.end(); ++adj)
				{
				   // get the location in distance, nodes, and visited.
					int y = (*adj)->targetI;
					// if w.dist == INFINITY
					if(abs(distance[y]) >= (currDist+1))
					{
						// w.dist = currDist+1;
						distance[y] = currDist+1;
						 // w.path = v
					}
				}
			}
		
			
		}
	}

	//locate end node 
	int j = 0;
	for(std::vector<Node*>::iterator item = m_nodes.begin(); item != m_nodes.end(); ++item)
	{
		// *item gets item at current dereferenced location
		if((*item)->Name.compare(endNode) == 0)
		{
			// j is index of where it occurs in m_nodes
			j = std::distance(m_nodes.begin(),item);
			//pathFind = (*item);
			break;
		}
	}

	// << visited[j] << endl;
	//cout << distance[j] << endl;

	if(visited[j] == false)
	{
		delete [m_nodes.size()] distance;
		delete [m_nodes.size()] visited;
		return false;
	}
	else if(visited[j] == true)
	{
		//NAME if nodeDataInsteadOfName is false
		
		// get distance of traverse vector
		int traverseDistance = distance[j];

		//resize traversal list to the correct size
		traversalList.resize(traverseDistance+1);

		if( nodeDataInsteadOfName == false)
		{
			traversalList.at(traverseDistance) = m_nodes.at(j)->Name;
			int len = 0;
			while(traverseDistance >= 0)
			{
				for(std::vector<Edge*>::iterator path = m_nodes.at(j)->In.begin(); path != m_nodes.at(j)->In.end(); ++path)
				{
					// *item gets item at current dereferenced location
					if(distance[(*path)->srcI] == (traverseDistance - 1))
					{
						traversalList[traverseDistance - 1] = m_nodes.at((*path)->srcI)->Name;
						len = ((*path)->srcI);
						break;
					}
				}
				traverseDistance -= 1;
				j = len;
			}
		delete [m_nodes.size()] distance;
		delete [m_nodes.size()] visited;
		return true;
		}
		//NAME if nodeDataInsteadOfName is true
		else
		{
			traversalList.at(traverseDistance) = m_nodes.at(j)->Data;
			int len = 0;
			while(traverseDistance >= 0)
			{
				for(std::vector<Edge*>::iterator path = m_nodes.at(j)->In.begin(); path != m_nodes.at(j)->In.end(); ++path)
				{
					// *item gets item at current dereferenced location
					if(distance[(*path)->srcI] == (traverseDistance - 1))
					{
						traversalList[traverseDistance - 1] = m_nodes.at((*path)->srcI)->Data;
						len = ((*path)->srcI);
						break;
					}
				}
				traverseDistance -= 1;
				j = len;
			}
		delete [m_nodes.size()] distance;
		delete [m_nodes.size()] visited;
		return true;
		}	

	
	}
}

bool DirectedGraph::NodeExists(const string& nodeName)
{
	// You must implement this function
	// Return true if the node exists in the graph, false otherwise.
	bool found = false;

	for(std::vector<Node*>::iterator item = m_nodes.begin(); item != m_nodes.end(); ++item)
	{
		// *item gets item at current dereferenced location
		if((*item)->Name.compare(nodeName) == 0)
		{
			found = true;
			return found;
		}
	}
	return found;

}
