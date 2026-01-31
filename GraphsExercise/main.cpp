#include <iostream>
#include <vector>
#include <stack>
#include <queue>


void DFSRecursive(const std::vector<std::vector<int>>& graph, std::stack<int> process, std::vector<bool>& visited)
{
	if (process.empty())
	{
		return;
	}

	int node = process.top();
	process.pop();

	if (!visited[node])
	{
		visited[node] = true;
		std::cout << node << " ";
		for (int i = 0; i < graph[node].size(); ++i)
		{
			if (!visited[graph[node][i]])
			{
				process.push(graph[node][i]);
			}
		}
	}
}

void DepthFirstSearchRecursive(const std::vector<std::vector<int>>& graph, int startNode)
{
	std::cout << "DFS Recursive:\n";
	std::vector<bool> visited;
	visited.resize(graph.size(), false);

	std::stack<int> process;
	process.push(startNode);
	DFSRecursive(graph, process, visited);
	std::cout << "\n";
}

void DepthFirstSearch(const std::vector<std::vector<int>>& graph, int startNode)
{
	std::vector<bool> visited;
	visited.resize(graph.size(), false);

	std::cout << "DFS Print All:\n ";
	// depth first uses a stack FIFO

	std::stack<int> process;
	process.push(startNode);

	while (!process.empty())
	{
		int node = process.top();
		process.pop();
		if (!visited[node])
		{
			visited[node] = true;
			std::cout << node << " ";
			
			for (int i = 0; i < graph[node].size(); ++i)
			{
				if (!visited[graph[node][i]])
				{
					process.push(graph[node][i]);
				}
			}
		}
	}
	std::cout << "\n";

}

bool CheckNodeConnectionDFS(const std::vector<std::vector<int>>& graph, int startNode, int endNode)
{
	//data to conrim the connection is made
	bool hasConnection = false;
	std::vector<int> connectedNodes;

	//DFS algorithm data
	std::vector<bool> visited;
	visited.resize(graph.size(), false);

	std::cout << "Checking if these nodes connect (DFS): ("
		<< startNode << "," << endNode << "}\n";

	std::stack<int> process;
	process.push(startNode);

	while (!process.empty())
	{
		int node = process.top();
		process.pop();
		if (!visited[node])
		{
			visited[node] = true;
			connectedNodes.push_back(node);
			if (node == endNode)
			{
				hasConnection = true;
				break;
			}
			for (int i = 0; i < graph[node].size(); ++i)
			{
				if (!visited[graph[node][i]])
				{
					process.push(graph[node][i]);
				}
			}
		}
	}
	if (hasConnection)
	{
		std::cout << "Connection was made\n";
		for (int i = 0; i < connectedNodes.size(); ++i)
		{
			std::cout << connectedNodes[i] << " ";
		}
		std::cout << "\n";
	}
	else
	{
		std::cout << "No connection found\n";
	}

	return hasConnection;
}

void BFSRecursive(const std::vector<std::vector<int>>& graph, std::queue<int>& process, std::vector<bool>& visited)
{
	if (process.empty())
	{
		return;
	}

	int node = process.front();
	process.pop();
	if (!visited[node])
	{
		visited[node] = true;
		std::cout << node << " ";

		for (int i = 0; 9 < graph[node].size(); ++i)
		{
			if (!visited[graph[node][i]])
			{
				process.push(graph[node][i]);
			}
		}
	}

	BFSRecursive(graph, process, visited);
}

void BreadthFirstRecursive(const std::vector<std::vector<int>>& graph, std::queue<int>& process, std::vector<bool>& visited)
{
	if (process.empty())
		return;

	int node = process.front();
	process.pop();

	std::cout << node << " ";

	for (int i = 0; i < graph[node].size(); ++i)
	{
		int neighbor = graph[node][i];
		if (!visited[neighbor])
		{
			visited[neighbor] = true;
			process.push(neighbor);
		}
	}

	BreadthFirstRecursive(graph, process, visited);
}


void BreadthFirst(const std::vector<std::vector<int>>& graph, int startNode)
{
	std::vector<bool> visited;
	visited.resize(graph.size(), false);
	std::cout << "Breadth First Search:\n";

	std::queue<int> process;
	process.push(startNode);

	while (!process.empty())
	{
		int node = process.front();
		process.pop();

		if (!visited[node])
		{
			std::cout << node << " ";
			for (int i = 0; graph[node].size(); ++i)
			{
				if (!visited[graph[node][i]])
				{
					process.push(graph[node][i]);
				}
			}
		}
	}

}

void CheckNodeConnectionBFS(const std::vector<std::vector<int>>& graph, int startNode, int endNode)
{
	//connection check info
	bool hasConnection = false;
	std::vector<int> connectedNodes;
	std::cout << "Checking if these nodes connect (DFS): ("
		<< startNode << "," << endNode << "}\n";

	std::vector<bool> visited;
	visited.resize(graph.size(), false);

	std::queue<int> process;
	process.push(startNode);
	while (!process.empty())
	{
		int node = process.front();
		process.pop();
		if(!visited[node])
		{
			visited[node] = true;
			connectedNodes.push_back(node);
			if (node == endNode)
			{
				hasConnection = true;
				break;
			}
			for (int i = 0; i < graph[node].size(); ++i)
			{
				if (!visited[graph[node][i]])
				{
					process.push(graph[node][i]);
				}
			}
		}

	}


}


int main()
{
	//graph traversal
	std::cout << "===Traversal Graph===\n\n";


	int numNodes = 0;
	std::cout << "Number of Nodes\n";
	std::cin >> numNodes;

	//store as an adjacency list
	//index is the "from:node and the vector is the list of node indices that are linked

	std::vector<std::vector<int>> adjacencyList;
	adjacencyList.resize(numNodes);

	int inputStart = 0;
	int inputEnd = 0;
	bool isDone = false;

	while (true)
	{
		std::cout << "Enter Start Node Index: ";
		std::cin >> inputStart;

		if (inputStart < 0 || inputStart >= numNodes)
		{
			break;
		}

		std::cout << "Enter End Node Index: ";
		std::cin >> inputEnd;

		if (inputEnd < 0 || inputEnd >= numNodes)
		{
			break;
		}

		auto iter = std::find(adjacencyList[inputStart].begin(), adjacencyList[inputStart].end(), inputEnd);

		if(iter == adjacencyList[inputStart].end())
		{
			adjacencyList[inputStart].push_back(inputEnd);// tells start node that its connected to the end node.
		}

		iter = std::find(adjacencyList[inputEnd].begin(), adjacencyList[inputEnd].end(), inputStart);
			if (iter == adjacencyList[inputEnd].end())
			{
				adjacencyList[inputEnd].push_back(inputStart);
			}

		system("cls");

		std::cout << "Print Out Adjacency List: \n";
		for (int s = 0; s < numNodes; ++s)
		{
			std::cout << s << ": { ";
			for (int e = 0; e < adjacencyList[s].size(); ++e)
			{
				std::cout << adjacencyList[s][e] << " ";

			}
			std::cout << "}\n";

		}

		int startNode = 0;
		std::cout << "Enter Node To Start: ";
		std::cin >> startNode;

		DepthFirstSearch(adjacencyList, startNode);
		BreadthFirst(adjacencyList, startNode);

		// --- BFS Recursive ---
		std::vector<bool> visitedBFS(adjacencyList.size(), false);
		std::queue<int> bfsProcess;
		visitedBFS[startNode] = true;
		bfsProcess.push(startNode);

		std::cout << "Breadth First Recursive:\n";
		BreadthFirstRecursive(adjacencyList, bfsProcess, visitedBFS);
		std::cout << "\n";

		// --- DFS Recursive ---
		std::vector<bool> visitedDFS(adjacencyList.size(), false);
		std::cout << "Depth First Recursive:\n";
		DepthFirstSearchRecursive(adjacencyList, startNode);
		std::cout << "\n";
	}

}