#include "Graph.h"
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define el endl
#define MAX 10000

//node class
Node::Node(string val) {
	value = val;
}

//if exists->return index else return -1
int Node::weightExist(Node* parent, Node* child, string weightType) {
	//if the edge already exist either ways.
	if (parent->weights.find(child) != parent->weights.end())
	{
		/*for (auto t : parent->transportations[child])
			if(t.first == weightType)
				return;*/

		for (int i = 0; i < parent->weights[child].size(); i++)
			if (parent->weights[child][i].first == weightType)
				return i;
	}
	return -1;
}
//update el mfrod tkon fel weight value bs wla type w weight value?
bool Node::changeWeightValue(vector<pair<string, float>>& allWeights, float weightValue, string weightType) {
	for (auto& t : allWeights) {
		if (weightType == t.first)
		{
			t.second = weightValue;
			return true;
		}
	}
	return false;
}
void Node::changeWeightType(vector<pair<string, float>>& allweights, string weightType) {
	for (auto& t : allweights) {
		if (weightType == t.first)
		{
			t.first = weightType;
			return;
		}
	}
}
bool Node::deleteWeight(Node* parent, Node* child, string weightType) {
	int index = parent->weightExist(parent, child, weightType);
	if (index != -1)
	{
		parent->weights[child].erase(parent->weights[child].begin() + index);
		int i = child->weightExist(child, parent, weightType);
		if (i != -1)
			child->weights[parent].erase(child->weights[parent].begin() + i);
		return true;
	}
	else
		return false;
}
bool Node::addWeight(Node* parent, Node* child, float weightValue, string weightType) {
	if(parent->weightExist(parent, child, weightType) == -1)
	{
		parent->weights[child].push_back(make_pair(weightType, weightValue));
		child->weights[parent].push_back(make_pair(weightType, weightValue));
		return true;
	}
	return false;
}

Node::~Node() {}


//graph class -----------
Graph::Graph() {}

void Graph::toLowerCase(string& str) {
	string result;
	for (char c : str)
		result += tolower(c);
	str = result;
}
//Node*, vector<pair<string, float>> >  <<- transportation stucture
//actions: 1->add a new transp, 2->delete, 3->update 
//hayhsal eh lw ana b add transp already mwgoda? ha3ml update wla a-drop el request
void Graph::addEdge(string node1, string node2, string weightType, float weightValue, int action) {
	toLowerCase(node1);
	toLowerCase(node2);
	toLowerCase(weightType);
	Node* node2_obj = getNode(node2);
	Node* node1_obj = getNode(node1);

	if (node2_obj == nullptr)
		node2_obj = new Node(node2);
	if (node1_obj == nullptr)
		node1_obj = new Node(node1);

	//if the child doesn't exist -> so as the transportations else i need to check if it already exists
	if (!childExist(node1_obj, node2_obj))
	{
		adj[node1_obj].push_back(node2_obj);
		node1_obj->weights[node2_obj].push_back(make_pair(weightType, weightValue));
	}
	//child already exists so we need to check for options;
	else {
		switch (action)
		{
			//add
		case 1:
			if (node1_obj->weightExist(node1_obj, node2_obj, weightType) == -1)
				bool x = node1_obj->addWeight(node1_obj, node2_obj, weightValue, weightType);
			break;
			//delete
		case 2:
			if (node1_obj->weightExist(node1_obj, node2_obj, weightType) != -1)
				bool x = node1_obj->deleteWeight(node1_obj, node2_obj, weightType);
			break;
			//update weightValue
		case 3:
			if (node1_obj->weightExist(node1_obj, node2_obj, weightType) != -1)
				bool x = node1_obj->changeWeightValue(node1_obj->weights[node2_obj], weightValue, weightType);
			break;
		default:
			break;
		}

	}
	if (!childExist(node2_obj, node1_obj))
	{
		adj[node2_obj].push_back(node1_obj);
		node2_obj->weights[node1_obj].push_back(make_pair(weightType, weightValue));
	}
	else {
		switch (action)
		{
			//add
		case 1:
			if (node2_obj->weightExist(node2_obj, node1_obj, weightType) == -1)
				node2_obj->addWeight(node2_obj, node1_obj, weightValue, weightType);
			break;
			//delete
		case 2:
			if (node2_obj->weightExist(node2_obj, node1_obj, weightType) != -1)
				node2_obj->deleteWeight(node2_obj, node1_obj, weightType);
			break;
			//update weightValue
		case 3:
			if (node2_obj->weightExist(node2_obj, node1_obj, weightType) != -1)
				node2_obj->changeWeightValue(node2_obj->weights[node1_obj], weightValue, weightType);
			break;
		default:
			break;
		}
	}

}
void Graph::addEdge(string node1, string node2) {
	toLowerCase(node1);
	toLowerCase(node2);
	Node* node2_obj = getNode(node2);
	Node* node1_obj = getNode(node1);

	if (node2_obj == nullptr)
		node2_obj = new Node(node2);
	if (node1_obj == nullptr)
		node1_obj = new Node(node1);

	if (!childExist(node1_obj, node2_obj))
		adj[node1_obj].push_back(node2_obj);
	if (!childExist(node2_obj, node1_obj))
		adj[node2_obj].push_back(node1_obj);
}

string Graph::bfs(Node* node) {
	queue<Node*> open;
	open.push(node);
	string out = "";
	while (open.size())
	{
		Node* current = open.front();
		open.pop();
		out = out + current->value + " ";
		current->isVisted = true;
		for (Node* child : adj[current])
			if (!child->isVisted && !inOpen(child, open))
				open.push(child);
	}
	return out;
}
bool Graph::inOpen(Node* node, queue<Node*> open) {
	while (open.size())
	{
		Node* check = open.front();
		open.pop();
		if (check == node)
			return true;
	}
	return false;
}

void Graph::dfs(Node* node, string &out) {
	node->isVisted = true;
	out = out + node->value + " ";
	for (Node* child : adj[node])
		if (!(child->isVisted))
			dfs(child, out);
}
void Graph::dfs(Node* node, Node* dest) {
	node->isVisted = true;
	if (node == dest)
		getEachPath(dest);

	for (Node* child : adj[node])
	{
		//no collision between paths
		if (!(child->isVisted))
		{
			child->previous = node;
			dfs(child, dest);
			child->isVisted = false;
		}
	}
}

void Graph::getEachPath(Node* dest) {
	destination = dest;
	vector<string> path;
	if (dest->previous == nullptr)
		path.push_back("destination is start");
	else {
		Node* tmp = dest;
		while (tmp->previous != nullptr) {
			path.push_back(tmp->value);
			tmp = tmp->previous;
			if (tmp->previous == nullptr)
				path.push_back(tmp->value);
		}
	}
	paths.push_back(path);
}

Node* Graph::getNode(string value) {
	for (auto& node : adj) {
		if (node.first->value == value)
			return node.first;
	}
	return nullptr;
}
bool Graph::childExist(Node* parent, Node* child) {
	for (Node* node : adj[parent])
		if (child == node)
			return true;
	return false;
}

bool Graph::checkCompleteness() {
	if (adj.size() != nodesNumber)
		return false;
	for (auto& node : adj)
		if (node.second.size() != nodesNumber - 1)
			return false;
	return true;
}

void Graph::clearPrevious() {
	for (auto& n : adj) {
		n.first->previous = nullptr;
		for (auto x : n.second)
			x->previous = nullptr;
	}
}
void Graph::clearVisted() {
	for (auto& node : adj)
		node.first->isVisted = false;
}

float Graph::getCurrentWeight(vector<pair<string, float>> allweights, string transport) {
	for (auto& t : allweights) {
		if (transport == t.first)
			return t.second;
	}
	return -1;
}

//dont ask me abt complexity pls 
void Graph::getWeightedPaths(vector <vector< pair<vector<string>, float >> >& allPaths, float budget) {
	vector < pair<vector<string>, float>>final;
	bool firstTime = true;
	//each possible path
	vector <string> test;
	for (auto& eachPath : paths) {
		bool firstTime = true;
		//each node for each path
		for (int i = eachPath.size() - 2; i >= 0; i--) {
			Node* node1 = getNode(eachPath[i]);
			Node* node2 = getNode(eachPath[i + 1]);
			vector<pair <vector< string>, float >> tmp;
			vector<pair <vector< string>, float >> combinations;
			vector<string> ways;
			//all weight types for each edge 
			for (auto weight : node1->weights[node2]) {
				ways.clear();
				if (weight.second > budget)
					continue;
				ways.push_back(weight.first);
				tmp.push_back(make_pair(ways, weight.second));
			}
			//no combinations yet
			if (firstTime)
			{
				firstTime = false;
				final = tmp;
			}
			//final -> 1st edge , tmp -> 2nd edge >> add on final /
			else {
				for (int outer = 0; outer < final.size(); outer++) {
					for (int inner = 0; inner < tmp.size(); inner++) {
						vector<string> weightType;
						//valid combin.
						if (final[outer].second + tmp[inner].second <= budget) {

							final[outer].first.push_back(tmp[inner].first[0]);
							final[outer].second += tmp[inner].second;
						}
					}
				}

			}
		}
		/*next iteration -> another path*/
		allPaths.push_back(final);
	}
}

vector<pair<float, string>> Graph::getAllPaths(Node* start, Node* dest, float budget) {
	vector<pair<float, string>> out;
	dfs(start, dest);
	vector <vector< pair<vector<string>, float >> > p;
	getWeightedPaths(p, budget);
	for (int i = 0; i < p.size(); i++) {
		for (auto allWeights : p[i]) {
			string s = "";
			int indWeight = 0;
			if (allWeights.first.size() != paths[i].size() - 1)
				continue;
			if (paths[i].size() > 2)
			{
				s = s + paths[i][paths[i].size() - 1] + " ";
				for (int nodeInd = paths[i].size() - 2; nodeInd >= 0; nodeInd--) {
					s = s + allWeights.first[indWeight] + " " + paths[i][nodeInd] + " ";
					indWeight++;
				}
			}
			else {
				s = s + paths[i][1] + " ";
				s = s + allWeights.first[0] + " " + paths[i][0] + " ";
			}
			out.push_back(make_pair(allWeights.second, s));
		}
	}
	sort(out.begin(), out.end());
	return out;
}
//find paths with lowest price  -- mariam
vector<pair<vector<string>, float>> Graph::lowestPath(string src, string dest, vector<string>& path, float budget, set<string>& visited) {
	path.push_back(src);
	visited.insert(src);
	toLowerCase(src);
	toLowerCase(dest);
	vector<pair<vector<string>, float>> result;
	if (src == dest) {
		float total_budget = 0;
		//iterationg over all nodes in a specific path
		for (float i = 0; i < path.size() - 1; i++) { // CALC
			float min_cost = MAX;
			//iterating over all childs of a parent in each iteration
			Node* parent = getNode(path[i]);
			//path -> cairo-----mansoura damietta 
			//child 
			for (auto eachChild : adj[parent]) {
				//path[i+1] -> represents 
				Node* child = getNode(path[i + 1]);
				if (child->value == path[i + 1]) {
					//iterating over the budget of the created edge 
					for (auto weight : child->weights[parent]) {
						if (weight.second < min_cost && weight.second <= budget) {
							min_cost = weight.second;
						}
					}
					break;
				}
			}
			total_budget += min_cost;
		}
		result.push_back({ path, total_budget });
	}
	else {
		Node* srcNode = getNode(src);
		for (auto neighbor : adj[srcNode]) {

			if (visited.find(neighbor->value) == visited.end() && budget >= getLeastWeight(srcNode,neighbor)) { //check the DFS s not called 4 visited node
				vector<string> new_path = path;
				set<string> new_visited = visited;
				vector<pair<vector<string>, float>> sub_paths = lowestPath(neighbor->value, dest, new_path, budget, new_visited);
				result.insert(result.end(), sub_paths.begin(), sub_paths.end());
			}
		}
	}

	path.pop_back();
	visited.erase(src);

	return result;
}

float Graph::getLeastWeight(Node * parent, Node * child) {
	int min = MAX;
	for (auto& childs : adj[parent]) {
		if(child->value == childs->value)
		{
			for (auto& weight : child->weights[parent]) {
				if (weight.second <= min) {
					min = weight.second;
				}
			}
		}
	}
	return min;
}

Graph::~Graph() {}