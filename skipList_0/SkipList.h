#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <mutex>
#include <map>
struct SkipListNode 
{
	int key;
	int val;
	std::vector<SkipListNode*> forward;
	SkipListNode(int k, int v, int level)
		:key(k), val(v), forward(level, nullptr){}
};
class SkipList 
{
using Node = SkipListNode;
private:
	Node* head;
	int maxLevel;
	int nodeCount_;
	int randomLevel();
	std::map<int, bool> dumpFlag_;
	//std::vector<std::pair<int, bool>> dumpFlag_;

	// »¥³âËø
	std::mutex mtx_;

	// file operator
	std::ofstream file_writer_;
	std::ifstream file_reader_;
	const std::string fileName_ = "storge";
public:
	SkipList()
		:maxLevel(1) 
	{
		head = new Node(-1,-1, maxLevel);
		std::srand(std::time(nullptr));
	}
	SkipList(int maxle)
		:maxLevel(maxle)
	{
		head = new Node(-1, -1, maxLevel);
		std::srand(std::time(nullptr));
	}

	void insert(int key, int val);
	bool search(int key, int& val);
	bool remove(int key);
	void display();
	void dumpFile();
};