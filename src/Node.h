#pragma once
#include <map>
#include <cmath>

class Node
{
	static int nodeIndex;	//用于生成唯一的节点id
private:
	int id;
	int coordinate[2];	//坐标矩阵
	std::map<int,double> distanceCache;	//与其他节点的距离缓存
public:
	Node();	//构造函数
	Node(Node &node); //拷贝构造
	void setCoordinate(int x, int y);	//设置节点的坐标
	int* getCoordinate();	//获取节点坐标
	double getDistance(Node &node);	//获取节点间距离
};

int Node::nodeIndex = 0;

Node::Node()
{
	this->id = nodeIndex;
	nodeIndex++;
}

Node::Node(Node &node)
{
	this->coordinate[0] = node.coordinate[0];
	this->coordinate[1] = node.coordinate[1];
	this->id = node.id;
	this->distanceCache = node.distanceCache;
}

void Node::setCoordinate(int x, int y)
{
	this->coordinate[0] = x;
	this->coordinate[1] = y;
}

int* Node::getCoordinate()
{
	return this->coordinate;
}

double Node::getDistance(Node &node)
{
	if (!this->distanceCache.empty())
	{
		auto it = this->distanceCache.find(node.id);
		if (it != this->distanceCache.end())
		{
			return it->second;
		}
	}
	double res = std::sqrt(std::pow(this->coordinate[0] - node.coordinate[0], 2) + std::pow(this->coordinate[1] - node.coordinate[1],2));
	this->distanceCache.insert({ node.id,res });
	node.distanceCache.insert({ this->id, res });
	//std::pair<int, double>(11, 22.5);
	return res;
}