#pragma once
#include <map>
#include <cmath>

class Node
{
	static int nodeIndex;	//��������Ψһ�Ľڵ�id
private:
	int id;
	int coordinate[2];	//�������
	std::map<int,double> distanceCache;	//�������ڵ�ľ��뻺��
public:
	Node();	//���캯��
	Node(Node &node); //��������
	void setCoordinate(int x, int y);	//���ýڵ������
	int* getCoordinate();	//��ȡ�ڵ�����
	double getDistance(Node &node);	//��ȡ�ڵ�����
};

