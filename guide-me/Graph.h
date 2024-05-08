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

	string value;
	Node* previous = nullptr;
	unordered_map<Node*, vector<pair<string, float>>> weights;

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
	
public:

	set<string> allNodes;
	vector<vector<string>> paths;
	int nodesNumber = 0;
	Node* destination = nullptr;
	unordered_map<Node*, vector<Node*>> adj;

	Graph();
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
	float getCurrentWeight(vector<pair<string, float>> allweights, string transport);

	vector<pair<float, string>> getAllPaths(Node* start, Node* dest, float budget);

	//mariam
	vector<pair<vector<string>, float>> lowestPath(string src, string dest, vector<string>& path, float budget, set<string>& visited);
	float getLeastWeight(Node* parent, Node* child);

	~Graph();
};

