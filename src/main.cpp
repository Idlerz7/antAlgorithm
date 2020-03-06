#include "Ant.h"
#include "Node.h"
#include "Param.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

//��������

void baseAntAlgorithm(Node* node, Ant* ants);
void eliteAntAlgorithm(Node* node, Ant* ants);
void minmaxAntAlgorithm(Node* nodes, Ant* ants);

//������

int main()
{
	//�������
	Node nodes[NODE_NUM];
	Ant ants[ANT_NUM];
	//��ʼ���ڵ�
	srand((unsigned int)time(0));
	for (int i = 0; i < NODE_NUM; i++)
	{
		//��ʼ���ڵ�(�����ظ��������)
		nodes[i].setCoordinate(rand() % 100, rand() % 100);
	}
	baseAntAlgorithm(nodes, ants);
	eliteAntAlgorithm(nodes, ants);
	minmaxAntAlgorithm(nodes, ants);
	system("pause");
	return 0;
}

/*
* Comment:��������Ⱥ�㷨
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void baseAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];
	string bestPath;
	double bestPathLength = INT_MAX;
	string historyBestPath;
	double historyBestPathLength = INT_MAX;

	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//��ʼ����Ϣ�ؾ���
			pheromone_matrix[i][j] = 2;
		}
	}

	//��ʼ����
	vector<int> temp_path[ANT_NUM];
	double temp_length[ANT_NUM];
	int randomAntNum = (int)floor(ANT_NUM*ANT_RANDOM_RATE);
	int bestAntId;	//��¼��õ����ϣ�
	double bestLength = INT_MAX;
	for (int iterCount = 0; iterCount < ITERATE_TIMES; iterCount++)
	{
		
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			//��ʼ������
			if (antId > randomAntNum)
			{
				ants[antId].initiazation(rand() % NODE_NUM, false);
			}
			else
			{
				ants[antId].initiazation(rand() % NODE_NUM, true);
			}
			//ÿֻ���Ͽ�ʼ�ɻ�
			while (ants[antId].selectNextNode(nodes, pheromone_matrix) != -1);
			//�Ա�ѡ�񱾴��������·����Ϣ
			temp_path[antId] = ants[antId].getPath();
			temp_length[antId] = ants[antId].getPathLength();
			if (temp_length[antId] < bestLength)
			{
				bestAntId = antId;
				bestLength = temp_length[antId];
			}
		}
		if (iterCount == ITERATE_TIMES - 1)break;	//���һ�β��ø�����Ϣ�ؾ���ֱ������
		//������Ϣ�ؾ���
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				//��Ϣ�ػӷ�
				pheromone_matrix[i][j] *= (1 - VOLATILITY);
			}
		}
		int from, to;
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			for (auto it = temp_path[antId].begin() + 1; it != temp_path[antId].end(); it++)
			{
				//������Ϣ��
				from = *(it - 1);
				to = *it;
				pheromone_matrix[from][to] = pheromone_matrix[to][from] += NORMAL_NUM / temp_length[antId];
			}
		}

		//����ʷ����·���Ƚ�
		if (bestLength < historyBestPathLength)
		{
			historyBestPathLength = bestLength;
			historyBestPath = ants[bestAntId].getPathString();
		}
	}

	//��õ������·��
	/*for (int antId = 0; antId < ANT_NUM; antId++)
	{
		temp_length[antId] = ants[antId].getPathLength();
		if (temp_length[antId] < bestPathLength)
		{
			bestPathLength = temp_length[antId];
			bestPath = ants[antId].getPathString();
		}
	}*/

	cout << "--baseAntAlgorithm--" << endl;
	cout << "bestPath:" << historyBestPath << endl;
	cout << "bestPathLengt:" << historyBestPathLength << endl;
}

/*
* Comment:һ�ָĽ�����Ⱥ�㷨��ÿ�����ŵ�·����������Ϣ�ض����
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void eliteAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];
	string bestPath;
	double bestPathLength = INT_MAX;
	string historyBestPath;
	double historyBestPathLength = INT_MAX;

	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//��ʼ����Ϣ�ؾ���
			pheromone_matrix[i][j] = 2;
		}
	}

	//��ʼ����
	vector<int> temp_path[ANT_NUM];
	double temp_length[ANT_NUM];
	int randomAntNum = (int)floor(ANT_NUM*ANT_RANDOM_RATE);
	int bestAntId;	//��¼��õ����ϣ�
	double bestLength;
	for (int iterCount = 0; iterCount < ITERATE_TIMES; iterCount++)
	{
		bestLength = INT_MAX;
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			//��ʼ������
			if (antId > randomAntNum)
			{
				ants[antId].initiazation(rand() % NODE_NUM, false);
			}
			else
			{
				ants[antId].initiazation(rand() % NODE_NUM, true);
			}
			//ÿֻ���Ͽ�ʼ�ɻ�
			while (ants[antId].selectNextNode(nodes, pheromone_matrix) != -1);
			//�Ա�ѡ�񱾴��������·����Ϣ
			temp_path[antId] = ants[antId].getPath();
			temp_length[antId] = ants[antId].getPathLength();
			if (temp_length[antId] < bestLength)
			{
				bestAntId = antId;
				bestLength = temp_length[antId];
			}
		}
		if (iterCount == ITERATE_TIMES - 1)break;	//���һ�β��ø�����Ϣ�ؾ���ֱ������
		//������Ϣ�ؾ���
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				//��Ϣ�ػӷ�
				pheromone_matrix[i][j] *= (1 - VOLATILITY);
			}
		}
		int from, to;
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			for (auto it = temp_path[antId].begin() + 1; it != temp_path[antId].end(); it++)
			{
				//��Ӣ�Ķ�����Ϣ��
				double eliteEx = 0;
				if (antId == bestAntId)
				{
					eliteEx = NORMAL_NUM / bestLength;
				}
				//������Ϣ��
				from = *(it - 1);
				to = *it;
				pheromone_matrix[from][to] = pheromone_matrix[to][from] += (NORMAL_NUM / temp_length[antId] + ELITE_FACTOR * eliteEx);
			}
		}

		//����ʷ����·���Ƚ�
		if (bestLength < historyBestPathLength)
		{
			historyBestPathLength = bestLength;
			historyBestPath = ants[bestAntId].getPathString();
		}
	}

	//��õ������·��
	/*for (int antId = 0; antId < ANT_NUM; antId++)
	{
		temp_length[antId] = ants[antId].getPathLength();
		if (temp_length[antId] < bestPathLength)
		{
			bestPathLength = temp_length[antId];
			bestPath = ants[antId].getPathString();
		}
	}*/

	cout << "--eliteAntAlgorithm--" << endl;
	cout << "bestPath:" << historyBestPath << endl;
	cout << "bestPathLengt:" << historyBestPathLength << endl;
}

/*
* Comment:һ�ָĽ�����Ⱥ�㷨��ÿ��ֻ�����ŵ�·�������ʸ�������Ϣ��
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void minmaxAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];
	string bestPath;
	double bestPathLength = INT_MAX;
	string historyBestPath;
	double historyBestPathLength = INT_MAX;

	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//��ʼ����Ϣ�ؾ�������Ϊ��Ϣ�����������
			pheromone_matrix[i][j] = TAO_MAX;
		}
	}

	//��ʼ����
	vector<int> temp_path[ANT_NUM];
	double temp_length[ANT_NUM];
	int randomAntNum = (int)floor(ANT_NUM*ANT_RANDOM_RATE);
	int bestAntId;	//��¼��õ����ϣ�
	double bestLength;
	for (int iterCount = 0; iterCount < ITERATE_TIMES; iterCount++)
	{
		bestLength = INT_MAX;
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			//��ʼ������
			if (antId > randomAntNum)
			{
				ants[antId].initiazation(rand() % NODE_NUM, false);
			}
			else
			{
				ants[antId].initiazation(rand() % NODE_NUM, true);
			}
			//ÿֻ���Ͽ�ʼ�ɻ�
			while (ants[antId].selectNextNode(nodes, pheromone_matrix) != -1);
			//�Ա�ѡ�񱾴��������·����Ϣ
			temp_path[antId] = ants[antId].getPath();
			temp_length[antId] = ants[antId].getPathLength();
			if (temp_length[antId] < bestLength)
			{
				bestAntId = antId;
				bestLength = temp_length[antId];
			}
		}
		if (iterCount == ITERATE_TIMES - 1)break;	//���һ�β��ø�����Ϣ�ؾ���ֱ������
		double remain_matrix[NODE_NUM][NODE_NUM];
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				//��Ϣ�ظ��¾����ʼ��
				remain_matrix[i][j] = 0;
			}
		}
		//������������Ϣ��
		int from, to;

		for (auto it = temp_path[bestAntId].begin() + 1; it != temp_path[bestAntId].end(); it++)
		{
			//������Ϣ��
			from = *(it - 1);
			to = *it;
			remain_matrix[from][to] = remain_matrix[to][from] += NORMAL_NUM / temp_length[bestAntId];
		}
		//������Ϣ�ؾ���
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				double newValue = pheromone_matrix[i][j] * (1 - VOLATILITY) + remain_matrix[i][j];
				pheromone_matrix[i][j] = min(TAO_MAX, max(TAO_MIN, newValue));
			}
		}

		//����ʷ����·���Ƚ�
		if (bestLength < historyBestPathLength)
		{
			historyBestPathLength = bestLength;
			historyBestPath = ants[bestAntId].getPathString();
		}
	}

	cout << "--minmaxAntAlgorithm--" << endl;
	cout << "bestPath:" << historyBestPath << endl;
	cout << "bestPathLengt:" << historyBestPathLength << endl;
}