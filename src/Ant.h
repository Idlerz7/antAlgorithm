#pragma once
#include <set>
#include <vector>
#include <string>
#include <random>
#include <map>
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

