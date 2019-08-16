#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <iterator>
#include <algorithm> 
#include <regex>
#include <queue>
#include "AVL_ADT.h"
using namespace std;


class FileReader {
private:
	void static print(DATA ss);
	void deleteLowFreq(int value);
	void static treeToDictionary(DATA transfer);

protected:
public:
	FileReader();
	~FileReader();
	void readSingle();
	void readMultiple(int NumberOfFiles);
	string processString(string Input);
	void printTree(int input);
	AvlTree<DATA, string> tree;
	AvlTree<DATA, string> treeTwo;
	void removeLowFreq(int value);
	void removeWord(string input);
	void findWord(string input);
	void searchResults();
	void treeToClass();
	void chopTreeDown();
	void readFromDictionary();
	bool isEmpty() { return tree.AVL_Empty(); };
	void printEntireTree();
};