#pragma once
#include <string>
#include <vector>
#include "Graph.h"
using namespace std;

class File
{
	string path;
	void toLowerCase(string&);
public:
	vector<vector<string>> data;
	File(string);
	void readFile();
	void writeOnFile(Graph*);
	void convertToObjects(Graph*);
	~File();
};

