
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include"Food.h"
#pragma once
using namespace std;

class Graph
{
public:
	struct Node {
		int XstartPoint, YstartPoint, XendPoint, YendPoint, Xcenter, Ycenter;
		int x, y;
	};
	Graph();
	static const int ROWS = 22;
	static const int COLS = 40;
	static const int NODESIZE = 48;

	static unordered_map<int, vector<int>> graph;
	static unordered_map<int, Node>nodesInfo;
	static vector<vector<int>> pacmanMatrix;



	static Node ConstructNode(int i, int j, int nodeSize);

	static unordered_map<int, vector<int>> constructGraph(vector<vector<int>>& pacmanMatrix, int nodeSize = NODESIZE);

	static vector<int> bfs(int start, int target,int id);
	vector<int>a_star(int start, int target);
	float heuristic(int a, int b);
	vector<vector<float>> edgeWeights;



	void updateWeights(const vector<unique_ptr<Food>>& foodList); //when food is eaten we update the weights of the node back to normal
	
	vector<int> dijkstra(int start, int target);
	static vector<int> ReconstructPath(vector<int>& parent, int start, int target);

};