#include "Node.h"

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
	double res = std::sqrt(std::pow(this->coordinate[0] - node.coordinate[0], 2) + std::pow(this->coordinate[1] - node.coordinate[1], 2));
	this->distanceCache.insert({ node.id,res });
	node.distanceCache.insert({ this->id, res });
	//std::pair<int, double>(11, 22.5);
	return res;
}