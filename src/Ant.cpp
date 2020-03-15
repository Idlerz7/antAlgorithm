#include "Ant.h"

int Ant::selectNextNode(Node* nodes, double(*pheromone_matrix)[NODE_NUM])
{
	if (this->travelNode.size() >= NODE_NUM)
	{
		//遍历完成
		//this->updateTravelNode(this->startNode);
		this->path.push_back(this->startNode);
		this->pathLenght += nodes[this->curentNode].getDistance(nodes[this->startNode]);
		this->updateCurentNode(this->startNode);
		return -1;
	}

	//随机选择的蚂蚁的选择路径方法
	if (this->isRandom)
	{
		int* randomIndex = new int[NODE_NUM];
		for (int index = 0; index < NODE_NUM; index++)randomIndex[index] = index;
		std::random_shuffle(randomIndex, randomIndex + NODE_NUM);	//打乱序列，按照随机数列进行选择

		int selectNode;
		for (int i = 0; i < NODE_NUM; i++)
		{
			selectNode = randomIndex[i];
			if (selectNode == this->startNode)continue;	//跳过开始节点不选择
			this->updateTravelNode(selectNode);
			this->path.push_back(selectNode);
			this->pathLenght += nodes[this->curentNode].getDistance(nodes[selectNode]);
			this->updateCurentNode(selectNode);
		}
		delete[]randomIndex;
		randomIndex = NULL;
		return selectNode;
	}

	//非随机选择的蚂蚁选择路径方法
	double max_p = 0;
	int selectNode;
	std::map<int, double> roulette;	//定于轮盘，用于轮盘赌选择路径

	for (int targetNode = 0; targetNode < NODE_NUM; targetNode++)
	{

		if (targetNode == curentNode || this->isTravel(targetNode))
		{
			continue;
		}
		//非随机选择的蚂蚁选择路径方法
		double molecule = std::pow(pheromone_matrix[curentNode][targetNode], PHEROMONE_FACTOR)*std::pow(NORMAL_NUM / nodes[curentNode].getDistance(nodes[targetNode]), HEURISTIC_FACTOR);	//计算式的分子
		double denominator = 0;	//计算式的分母
		for (int nodeIndex = 0; nodeIndex < NODE_NUM; nodeIndex++)
		{
			if (nodeIndex == curentNode || this->isTravel(nodeIndex))
			{
				continue;
			}
			denominator += std::pow(pheromone_matrix[curentNode][nodeIndex], PHEROMONE_FACTOR)*std::pow(NORMAL_NUM / nodes[curentNode].getDistance(nodes[nodeIndex]), HEURISTIC_FACTOR);
		}
		double curP = molecule / denominator;
		roulette.insert({ targetNode,curP });
	}
	//轮盘赌选择下一轮节点
	double randNum = rand() / (double)RAND_MAX;
	double cumulativeProbability = 0;	//累计概率
	for (auto iter = roulette.begin(); iter != roulette.end(); iter++)
	{
		cumulativeProbability += iter->second;
		selectNode = iter->first;
		if (cumulativeProbability >= randNum)
		{
			break;
		}
	}
	//更新信息
	this->updateTravelNode(selectNode);
	this->path.push_back(selectNode);
	this->pathLenght += nodes[this->curentNode].getDistance(nodes[selectNode]);
	this->updateCurentNode(selectNode);
	return selectNode;
}

void Ant::updateTravelNode(int node)
{
	this->travelNode.insert(node);
}

bool Ant::isTravel(int node)
{
	if (this->travelNode.find(node) != this->travelNode.end())
	{
		return true;
	}
	return false;
}

double Ant::getPathLength()
{
	return this->pathLenght;
}

std::string Ant::getPathString()
{
	char* buf = new char[this->path.size()];
	int index = 0;
	std::string res;
	for (int node : this->path)
	{
		res += std::to_string(node) + " ";
		//buf[index] = (char)(node + '0');
		index++;
	}
	//std::string res(buf);
	if (buf != NULL)
	{
		delete[]buf;
		buf = NULL;
	}
	return res;
}

std::vector<int> &Ant::getPath()
{
	return this->path;
}

void Ant::updateCurentNode(int node)
{
	this->curentNode = node;
}

void Ant::updatePath(int node)
{
	this->path.push_back(node);
}

void Ant::setStartNode(int node)
{
	this->startNode = node;
}

void Ant::initiazation(int startNode, bool isRandom)
{
	if (this->startNode != -1)	//已经初始化过一次，清空记忆
	{
		this->pathLenght = 0.0;
		this->path.clear();
		this->travelNode.clear();
	}
	//初始化蚂蚁起点
	this->updateCurentNode(startNode);
	this->updateTravelNode(startNode);
	this->setStartNode(startNode);
	this->updatePath(startNode);
	this->isRandom = isRandom;
}