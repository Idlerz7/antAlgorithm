#include "Ant.h"
#include "Node.h"
#include "Param.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

//��������

//������
int main()
{
	//�������
	Node nodes[NODE_NUM];
	Ant ants[ANT_NUM];
	double pheromone_matrix[NODE_NUM][NODE_NUM];
	string bestPath;
	double bestPathLength = INT_MAX;

	//��ʼ������
	srand((unsigned int)time(0));
	for (int i = 0; i < NODE_NUM; i++)
	{
		//��ʼ���������
		//ants[i].updateCurentNode(i);
		//ants[i].updateTravelNode(i);
		//ants[i].setStartNode(i);
		//ants[i].updatePath(i);
		//��ʼ���ڵ�(�����ظ��������)
		nodes[i].setCoordinate(rand() % 100, rand() % 100);
	}
	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//��ʼ����Ϣ�ؾ���
			pheromone_matrix[i][j] = 2;
		}
	}

	//��ʼ����
	for (int iterCount = 0; iterCount < ITERATE_TIMES; iterCount++)
	{
		//vector<int> temp_path[ANT_NUM];
		//double temp_length[ANT_NUM];
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			//��ʼ������
			ants[antId].initiazation(antId);
			//ÿֻ���Ͽ�ʼ�ɻ�
			while (ants[antId].selectNextNode(nodes, pheromone_matrix) != -1);
		}
		if (iterCount == ITERATE_TIMES - 1)break;	//���һ�β��ø�����Ϣ�ؾ���ֱ������
		//������Ϣ�ؾ���
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				//��Ϣ�ػӷ�
				pheromone_matrix[i][j] *= (1-VOLATILITY) ;
			}
		}
		int from, to;
		vector<int> temp_path[ANT_NUM];
		double temp_length[ANT_NUM];
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			temp_path[antId] = ants[antId].getPath();
			temp_length[antId] = ants[antId].getPathLength();
			for (auto it = temp_path[antId].begin()+1; it != temp_path[antId].end(); it++)
			{
				//������Ϣ��
				from = *(it - 1);
				to = *it;
				pheromone_matrix[from][to] = pheromone_matrix[to][from] += NORMAL_NUM / temp_length[antId];
			}
		}
	}

	//���һ�ٴε������·��
	double temp_length[ANT_NUM];
	for (int antId = 0; antId < ANT_NUM; antId++)
	{
		temp_length[antId] = ants[antId].getPathLength();
		if (temp_length[antId] < bestPathLength)
		{
			bestPathLength = temp_length[antId];
			bestPath = ants[antId].getPathString();
		}
	}

	cout << "bestPath:" << bestPath << endl;
	cout << "bestPathLengt:" << bestPathLength << endl;
	system("pause");
	return 0;
}

