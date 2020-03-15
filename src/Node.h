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

