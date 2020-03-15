#include "Ant.h"

int Ant::selectNextNode(Node* nodes, double(*pheromone_matrix)[NODE_NUM])
{
	if (this->travelNode.size() >= NODE_NUM)
	{
		//�������
		//this->updateTravelNode(this->startNode);
		this->path.push_back(this->startNode);
		this->pathLenght += nodes[this->curentNode].getDistance(nodes[this->startNode]);
		this->updateCurentNode(this->startNode);
		return -1;
	}

	//���ѡ������ϵ�ѡ��·������
	if (this->isRandom)
	{
		int* randomIndex = new int[NODE_NUM];
		for (int index = 0; index < NODE_NUM; index++)randomIndex[index] = index;
		std::random_shuffle(randomIndex, randomIndex + NODE_NUM);	//�������У�����������н���ѡ��

		int selectNode;
		for (int i = 0; i < NODE_NUM; i++)
		{
			selectNode = randomIndex[i];
			if (selectNode == this->startNode)continue;	//������ʼ�ڵ㲻ѡ��
			this->updateTravelNode(selectNode);
			this->path.push_back(selectNode);
			this->pathLenght += nodes[this->curentNode].getDistance(nodes[selectNode]);
			this->updateCurentNode(selectNode);
		}
		delete[]randomIndex;
		randomIndex = NULL;
		return selectNode;
	}

	//�����ѡ�������ѡ��·������
	double max_p = 0;
	int selectNode;
	std::map<int, double> roulette;	//�������̣��������̶�ѡ��·��

	for (int targetNode = 0; targetNode < NODE_NUM; targetNode++)
	{

		if (targetNode == curentNode || this->isTravel(targetNode))
		{
			continue;
		}
		//�����ѡ�������ѡ��·������
		double molecule = std::pow(pheromone_matrix[curentNode][targetNode], PHEROMONE_FACTOR)*std::pow(NORMAL_NUM / nodes[curentNode].getDistance(nodes[targetNode]), HEURISTIC_FACTOR);	//����ʽ�ķ���
		double denominator = 0;	//����ʽ�ķ�ĸ
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
	//���̶�ѡ����һ�ֽڵ�
	double randNum = rand() / (double)RAND_MAX;
	double cumulativeProbability = 0;	//�ۼƸ���
	for (auto iter = roulette.begin(); iter != roulette.end(); iter++)
	{
		cumulativeProbability += iter->second;
		selectNode = iter->first;
		if (cumulativeProbability >= randNum)
		{
			break;
		}
	}
	//������Ϣ
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
	if (this->startNode != -1)	//�Ѿ���ʼ����һ�Σ���ռ���
	{
		this->pathLenght = 0.0;
		this->path.clear();
		this->travelNode.clear();
	}
	//��ʼ���������
	this->updateCurentNode(startNode);
	this->updateTravelNode(startNode);
	this->setStartNode(startNode);
	this->updatePath(startNode);
	this->isRandom = isRandom;
}