#pragma once
#include <set>
#include <vector>
#include <string>
#include <random>
#include "Node.h"
#include "Param.h"

class Ant
{
private:
	std::set<int> travelNode;	//记录已经去过的城市，也就是禁忌表
	std::vector<int> path;	//记录选择的路径节点
	int startNode;	//起始节点（index）
	int curentNode;	//当前节点(index)
	double pathLenght = 0;
	bool isRandom;	//是否随机分配下一个节点
public:
	Ant() { this->startNode = -1; }
	int selectNextNode(Node* nodes, double (*pheromone_matrix)[NODE_NUM]);	//计算概率，选择下一个节点
	void updateTravelNode(int node);	//更新已经旅行过的地方
	bool isTravel(int node);	//检测是否已经旅行过了
	double getPathLength();	//获取路径长度
	std::string getPathString();	//以字符串形式获取路径
	std::vector<int> &getPath();
	void updateCurentNode(int node);
	void setStartNode(int node);
	void updatePath(int node);
	void initiazation(int startNode,bool isRandom);	//重置蚂蚁的情况
};

int Ant::selectNextNode(Node* nodes, double (*pheromone_matrix)[NODE_NUM])
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
	
	for (int targetNode = 0; targetNode < NODE_NUM; targetNode++)
	{
		
		if (targetNode == curentNode || this->isTravel(targetNode))
		{
			continue;
		}
		//非随机选择的蚂蚁选择路径方法
		double molecule = std::pow(pheromone_matrix[curentNode][targetNode],PHEROMONE_FACTOR)*std::pow(100/nodes[curentNode].getDistance(nodes[targetNode]),HEURISTIC_FACTOR);	//计算式的分子
		double denominator = 0;	//计算式的分母
		for (int nodeIndex = 0; nodeIndex < NODE_NUM; nodeIndex++)
		{
			if (nodeIndex == curentNode || this->isTravel(nodeIndex))
			{
				continue;
			}
			denominator += std::pow(pheromone_matrix[curentNode][nodeIndex], PHEROMONE_FACTOR)*std::pow(100/ nodes[curentNode].getDistance(nodes[nodeIndex]), HEURISTIC_FACTOR);
		}
		double curP = molecule / denominator;
		if (curP > max_p)
		{
			max_p = curP;
			selectNode = targetNode;	//选择概率最大的
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

void Ant::initiazation(int startNode,bool isRandom)
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