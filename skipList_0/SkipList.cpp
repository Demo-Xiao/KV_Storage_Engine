#include "SkipList.h"

int SkipList::randomLevel()
{
	//�����ֲַ��£���һ��Ľڵ�����࣬ÿ����һ�㣬�ڵ����ͻ���롣
    int level = 1;
	while (std::rand() % 2 && level < maxLevel)
	{
		level++;
	}

    return level;
}

void SkipList::display()
{
	for (int i = maxLevel - 1; i >= 0; i--) {
		Node* node = head->forward[i];
		std::cout << "Level " << i + 1 << ": HEAD ";
		while (node != nullptr) {
			std::cout << "--> " << node->key << " ";
			node = node->forward[i];
		}
		std::cout << "--> NULL" << std::endl;
	}
}

void SkipList::dumpFile()
{
	file_writer_.open(fileName_);
	Node* node = head;
	while (node != nullptr)
	{
		if (!dumpFlag_[node->key])   
		{
			file_writer_ << node->key << ":" << node->val << '\n';
			dumpFlag_[node->key] = true;
		}
		node = node->forward[0];
	}

	file_writer_.flush();
	file_reader_.close();
	return;
}

void SkipList::insert(int key, int val)
{
	mtx_.lock();
	std::vector<Node*> update(maxLevel, nullptr);
	Node* x = head;

	for (int i = maxLevel - 1; i >= 0; i--) 
	{
		while (x->forward[i] != nullptr && x->forward[i]->key < key) 
		{
			x = x->forward[i];
		}
		update[i] = x;
	}

	//std::cout << "current key is :" << x->forward[0]->key << std::endl;

	if (x->forward[0] != NULL && x->forward[0]->key == key) {
		//std::cout << "key: " << key << ", exists" << std::endl;
		mtx_.unlock();
		return ;
	}


	int level = randomLevel();
	/*
		���ܻ����Ӷ�������ߵ��޸ġ�
	*/

	x = new Node(key, val, level);
	for (int i = 0; i < level; i++) 
	{
		x->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = x;
	}
	
	dumpFlag_.insert(std::make_pair(key, false));
	//dumpFlag_.push_back(std::make_pair(key, false));
	//std::cout << "successfully inserted key:" << key << ",value:" << val << '\n';
	mtx_.unlock();
}

bool SkipList::search(int key, int& val)
{
	Node* x = head;
	for (int i = maxLevel - 1; i >= 0; i--) 
	{
		while (x->forward[i] != nullptr && x->forward[i]->key < key)
		{
			x = x->forward[i];
		}
	}

	x = x->forward[0];
	if (x && x->key == key) 
	{
		val = x->val;
		return true;
	}
	return false;
}

bool SkipList::remove(int key)
{
	mtx_.lock();
	std::vector<Node*> updata(maxLevel, nullptr);
	Node* x = head;

	for (int i = maxLevel - 1; i >= 0; i--) 
	{
		while (x->forward[i] != nullptr && x->forward[i]->key < key)
		{
			x = x->forward[i];
		}
		updata[i] = x;
	}

	x = x->forward[0];

	if (x && x->key == key) // �ҵ���Ҫɾ����key
	{
		for (int i = 0; i < maxLevel; i++) 
		{
			if (updata[i]->forward[i] != x) 
			{
				break;
			}
			updata[i]->forward[i] = x->forward[i];
		}

		//delete x;
		mtx_.unlock();
		return true;
	}
	mtx_.unlock();
	return false;
}
