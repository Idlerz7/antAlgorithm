#pragma once
#include "Ant.h"
#include "Node.h"
#include "Param.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

/*
* Comment:��ʼ����Ϣ�ؾ���
* Param matrix ��Ϣ�ؾ��� double**
* Param initVal ��ʼ��ֵ double
* @Return void
*/
void initPheromoneMatrix(double(*matrix)[NODE_NUM], double initVal);

/*
* Comment:һ�ε�������
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param retPath ���ε�����·�����ز��� vector<int>[ANT_NUM]
* Param retBestAntId ���ε������������������ int &
* @Return double ���ر������·����·������
*/
double iterOneTime(Node* nodes, Ant* ants, double(*pheromone_matrix)[NODE_NUM], std::vector<int> retPath[ANT_NUM], int &retBestAntId);

/*
* Comment:ԭʼ�㷨������Ϣ�ؾ���ķ���
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param iterPath ���ε�����·�� vector<int>[ANT_NUM]
* Param bestAntId ���ε������������������ int
* @Return void
*/
void baseUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], std::vector<int> iterPath[ANT_NUM], int bestAntId);

/*
* Comment:��Ӣ��Ⱥ�㷨������Ϣ�ؾ���ķ���
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param iterPath ���ε�����·�� vector<int>[ANT_NUM]
* Param bestAntId ���ε������������������ int
* @Return void
*/
void eliteUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId);

/*
* Comment:�����С��Ⱥ�㷨������Ϣ�ؾ���ķ���
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param iterPath ���ε�����·�� vector<int>[ANT_NUM]
* Param bestAntId ���ε������������������ int
* @Return void
*/
void minmaxUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId);

/*
* Comment:����ʷ���·���Ƚϲ�������Ϣ
* Param historyBestPath ���϶������� string &
* Param historyBestPathLength ��Ϣ�ؾ��� double &
* Param iterBestPath ���ε�����·�� string
* Param iterBestPathLength ���ε��������·������ int
* @Return void
*/
void compareWithHistory(string &historyBestPath, double &historyBestPathLength, string iterBestPath, double iterBestPathLength);

/*
* Comment:��������Ⱥ�㷨
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void baseAntAlgorithm(Node* nodes, Ant* ants);

/*
* Comment:һ�ָĽ�����Ⱥ�㷨��ÿ�����ŵ�·����������Ϣ�ض����
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void eliteAntAlgorithm(Node* nodes, Ant* ants);

/*
* Comment:һ�ָĽ�����Ⱥ�㷨��ÿ��ֻ�����ŵ�·�������ʸ�������Ϣ��
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void minmaxAntAlgorithm(Node* nodes, Ant* ants);

/*
* Comment:�����������
* Param nodes ����������� Node*
* Param vertex �����󶥵����� float*
* @Return void
*/
void praseNode(Node* nodes, float *vertex);

/*
* Comment:�����������
* Param path ·�� vector<int>
* Param indices �������������� unsigned int *
* @Return void
*/
void prasePath(vector<int> path, unsigned int *indices);