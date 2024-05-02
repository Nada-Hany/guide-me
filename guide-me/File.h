#pragma once
#include <string>
#include <vector>
#include "Graph.h"
using namespace std;

class File
{
	string path;
public:
	vector<vector<string>> data;
	File(string);
	void readFile();
	void writeOnFile(Graph*);
	void convertToObjects(Graph*);
	void convertWeights(Graph*);
	void toLowerCase(string&);
	~File();
};

