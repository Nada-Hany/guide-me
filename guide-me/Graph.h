#pragma once
#include <vector>
#include <map>
#include <list>
#include <string>
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;


class Node
{

public:

	Node* previous = nullptr;
	unordered_map<Node*, vector<pair<string, float>>> weights;
	string value;

	bool isVisted = false;
	int weightExist(Node*, Node*, string);
	bool changeWeightValue(vector<pair<string, float>>&, float, string);
	void changeWeightType(vector<pair<string, float>>&, string);
	bool deleteWeight(Node*, Node*, string);
	bool addWeight(Node*, Node*, float, string);
	Node(string);
	~Node();

};

class Graph
{
	unordered_map <string, int> indices;
	bool inOpen(Node*, queue<Node*>);
	bool childExist(Node*, Node*);
	void toLowerCase(string&);
	void getEachPath(Node*);
	vector<vector<string>> paths;
	
	//mariam
	unordered_map<string, vector<pair<string, vector<pair<int, string>>>>> graph;

public:
	set<string> allNodes;
	int nodesNumber = 0;
	Node* destination = nullptr;
	unordered_map<Node*, vector<Node*>> adj;

	Graph();
	void getPaths();
	Node* getNode(string);
	void addEdge(string, string);
	void addEdge(string, string, string, float, int);
	//traversing
	void dfs(Node*, string&);
	//all possible paths without considering the weights
	void dfs(Node*, Node*);
	string bfs(Node*);
	void clearVisted();
	void clearPrevious();
	bool checkCompleteness();
	void getWeightedPaths(vector <vector< pair<vector<string>, float >> >&, float);
	void validWeightedPath(Node*, Node*, float);

	//mariam
	vector<pair<vector<string>, float>> lowestPath(string src, string dest, vector<string>& path, float budget, set<string>& visited);
	float getWeight(Node* parent, Node* child);
	unordered_map<string, vector<pair<string, vector<pair<int, string>>>>>& getGraph() {
		return graph;
	}
	~Graph();
};

