#include "Graph.h"
#include "ghost.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>


unordered_map<int, vector<int>> Graph::graph;
unordered_map<int, Graph::Node> Graph::nodesInfo;
vector<vector<float>> Graph::edgeWeights;

Graph::Node Graph::ConstructNode(int i, int j, int nodeSize) {
	Node node;
	node.x = i;
	node.y = j;
	node.XstartPoint = j * nodeSize;
	node.YstartPoint = i * nodeSize;
	node.XendPoint = node.XstartPoint + nodeSize - 1;
	node.YendPoint = node.YstartPoint + nodeSize - 1;
	node.Xcenter = node.XstartPoint + (nodeSize / 2);
	node.Ycenter = node.YstartPoint + (nodeSize / 2);
	return node;
}


vector<vector<int>> Graph::pacmanMatrix = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
   {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


unordered_map<int, vector<int>> Graph::constructGraph(vector<vector<int>>& pacmanMatrix, int nodeSize) {

	int row = pacmanMatrix.size();
	int col = pacmanMatrix[0].size();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (pacmanMatrix[i][j] != 0)
			{
				vector <int>v;
				if ((i - 1 >= 0 && pacmanMatrix[i - 1][j] != 0)) { // up
					int x = (i - 1) * col + j;
					v.push_back(x);
				}
				if ((i + 1 < row && pacmanMatrix[i + 1][j] != 0)) {// down
					int x = (col * (i + 1)) + j;
					v.push_back(x);
				}
				if ((j - 1 >= 0 && pacmanMatrix[i][j - 1] != 0)) {// left 
					int x = (col * (i)) + j - 1;
					v.push_back(x);
				}

				if ((j + 1 < col && pacmanMatrix[i][j + 1] != 0)) {// right
					int x = (col * (i)) + j + 1;
					v.push_back(x);
				}
				if (v.size())
				{
					int nodeId = (col * i) + j;
					graph[nodeId] = v;
					nodesInfo[nodeId] = ConstructNode(i, j, nodeSize);

				}
			}
		}


	}




	return graph;
}

Graph::Graph() {
	graph = constructGraph(Graph::pacmanMatrix);
	//intialize wights to preform dijkstra 
	edgeWeights.resize(ROWS * COLS);
	for (int i = 0; i < ROWS * COLS; i++) {
		edgeWeights[i].resize(ROWS * COLS, 1.0f);
	}


	edgeWeights.resize(ROWS * COLS);
	for (int i = 0; i < ROWS * COLS; i++) {
		edgeWeights[i].resize(ROWS * COLS, 1.0f);
	}


}


vector <int> Graph::bfs(int start, int target, int id) {
	queue<int> q;
	static int s = ROWS * COLS + 5;
	vector<bool> visited(s, false);
	vector<int> parent(s, -1);
	q.push(start);
	visited[start] = true;
	while (q.size())
	{
		int front = q.front();
		q.pop();
		for (int child : graph[front]) {
			if (!visited[child])
			{
				visited[child] = 1;
				parent[child] = front;
				q.push(child);
			}
		}
	}
	vector <int> path = ReconstructPath(parent, start, target + id);
	return path;
}
void Graph::updateWeights(const vector<unique_ptr<Food>>& foodList) {
	// all weights to 1.0 back to 1st state again(game loop)
	for (int i = 0; i < ROWS * COLS; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			int neighbor = graph[i][j];
			edgeWeights[i][neighbor] = 1.0f;
		}
	}

	for (const auto& food : foodList) {
		// skip
		if (food->eaten()) continue;

		Vector2f pos = food->getPosition();
		int nodeI = static_cast<int>(pos.y / NODESIZE);
		int nodeJ = static_cast<int>(pos.x / NODESIZE);
		int nodeId = nodeI * COLS + nodeJ;

		float weightModifier;
		switch (food->getType()) {
		case FoodType::Skill:
			weightModifier = 1.5f;
			break;
		case FoodType::Fruit:
			weightModifier = 0.6f;  // the ghost will mostly target fruits (we can change it for another ghost)
			break;
		default:
			weightModifier = 1.0f;
		}
		// reAssign wights accordingly
		for (int neighbor : graph[nodeId]) {
			edgeWeights[nodeId][neighbor] = weightModifier;
		}
	}

}

vector<int> Graph::dijkstra(int start, int target) {

	vector<float> mydist(ROWS * COLS, numeric_limits<float>::max());
	vector<int> prev(ROWS * COLS, -1);
	// priority queue for Dijkstra	1q (distance, node id)
	priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

	// distance to start is 0
	mydist[start] = 0;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int u = pq.top().second;
		float d = pq.top().first;
		pq.pop();

		// if we reached our target
		if (u == target) break;

		// if we've already found a better path
		if (d > mydist[u]) continue;
		// check all neighbors
		for (int v : graph[u]) {
			float weight = edgeWeights[u][v];
			if (mydist[u] + weight < mydist[v]) {
				mydist[v] = mydist[u] + weight;
				prev[v] = u;
				pq.push({ mydist[v], v });
			}
		}
	}

	auto path = ReconstructPath(prev, start, target);
	if (path.empty() || path[0] != start)
		return {}; //its possible not to found any fruit (all is eaten)
	return path;
}


float Graph::heuristic(int a, int b) {
	//3mo manhatn equation 
	int ax = a / COLS, ay = a % COLS;
	int bx = b / COLS, by = b % COLS;
	return abs(ax - bx) + abs(ay - by);
}
vector<int>Graph::a_star(int start, int target) {
	priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> unchecked;

	//34an n3rf e7na fen wgaen mnin
	static int size = COLS * ROWS;
	const float inf = 10000000;
	vector<int> parent(size, -1);
	vector<float> g(size, inf);  //coast to decide the shortest path
	vector<float> f(size, inf);  // f=g+h h-->(3mo manhten equation)

	g[start] = 0;
	f[start] = heuristic(start, target);
	parent[start] = -1;
	unchecked.push({ f[start],start });


	while (!unchecked.empty()) {
		int current = unchecked.top().second;
		unchecked.pop();
		if (current == target) {
			return ReconstructPath(parent, start, target);
		}
		for (int child : graph[current]) {
			float g_coast = g[current] + 1;  //ask Yousab if the coast of all nodes is just 1? or we have another logic
			if (g_coast < g[child]) {
				parent[child] = current;
				g[child] = g_coast;
				f[child] = g_coast + heuristic(child, target);
				unchecked.push({ f[child], child });
			}
		}
	}

	//if there is no way  return an empty vector
	return{};
}


vector <int> Graph::ReconstructPath(vector <int>& parent, int start, int target) {
	vector <int> path;
	int current = target;
	while (current != -1)
	{
		path.push_back(current);
		current = parent[current];
	}
	reverse(path.begin(), path.end());
	return path;
}