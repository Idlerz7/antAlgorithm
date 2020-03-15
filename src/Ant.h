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
	std::set<int> travelNode;	//��¼�Ѿ�ȥ���ĳ��У�Ҳ���ǽ��ɱ�
	std::vector<int> path;	//��¼ѡ���·���ڵ�
	int startNode;	//��ʼ�ڵ㣨index��
	int curentNode;	//��ǰ�ڵ�(index)
	double pathLenght = 0;
	bool isRandom;	//�Ƿ����������һ���ڵ�
public:
	Ant() { this->startNode = -1; }
	int selectNextNode(Node* nodes, double (*pheromone_matrix)[NODE_NUM]);	//������ʣ�ѡ����һ���ڵ�
	void updateTravelNode(int node);	//�����Ѿ����й��ĵط�
	bool isTravel(int node);	//����Ƿ��Ѿ����й���
	double getPathLength();	//��ȡ·������
	std::string getPathString();	//���ַ�����ʽ��ȡ·��
	std::vector<int> &getPath();
	void updateCurentNode(int node);
	void setStartNode(int node);
	void updatePath(int node);
	void initiazation(int startNode,bool isRandom);	//�������ϵ����
};

