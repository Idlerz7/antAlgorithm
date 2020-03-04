#include "Ant.h"
#include "Node.h"
#include "Param.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

//函数声明

void baseAntAlgorithm(Node* node, Ant* ants);
void eliteAntAlgorithm(Node* node, Ant* ants);

//主函数

int main()
{
	//定义变量
	Node nodes[NODE_NUM];
	Ant ants[ANT_NUM];
	//初始化节点
	srand((unsigned int)time(0));
	for (int i = 0; i < NODE_NUM; i++)
	{
		//初始化节点(可能重复，待解决)
		nodes[i].setCoordinate(rand() % 100, rand() % 100);
	}
	baseAntAlgorithm(nodes, ants);
	eliteAntAlgorithm(nodes, ants);
	system("pause");
	return 0;
}

/*
* Comment:基础的蚁群算法
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
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
			//初始化信息素矩阵
			pheromone_matrix[i][j] = 2;
		}
	}

	//开始迭代
	vector<int> temp_path[ANT_NUM];
	double temp_length[ANT_NUM];
	int bestAntId;	//记录最好的蚂蚁！
	double bestLength = INT_MAX;
	for (int iterCount = 0; iterCount < ITERATE_TIMES; iterCount++)
	{
		
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			//初始化蚂蚁
			if (antId < NODE_NUM)
			{
				ants[antId].initiazation(antId, false);
			}
			else
			{
				ants[antId].initiazation(rand() % NODE_NUM, true);
			}
			//每只蚂蚁开始干活
			while (ants[antId].selectNextNode(nodes, pheromone_matrix) != -1);
			//对比选择本次最优秀的路径信息
			temp_path[antId] = ants[antId].getPath();
			temp_length[antId] = ants[antId].getPathLength();
			if (temp_length[antId] < bestLength)
			{
				bestAntId = antId;
				bestLength = temp_length[antId];
			}
		}
		if (iterCount == ITERATE_TIMES - 1)break;	//最后一次不用更新信息素矩阵，直接跳出
		//更新信息素矩阵
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				//信息素挥发
				pheromone_matrix[i][j] *= (1 - VOLATILITY);
			}
		}
		int from, to;
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			for (auto it = temp_path[antId].begin() + 1; it != temp_path[antId].end(); it++)
			{
				//增加信息素
				from = *(it - 1);
				to = *it;
				pheromone_matrix[from][to] = pheromone_matrix[to][from] += NORMAL_NUM / temp_length[antId];
			}
		}

		//与历史最优路径比较
		if (bestLength < historyBestPathLength)
		{
			historyBestPathLength = bestLength;
			historyBestPath = ants[bestAntId].getPathString();
		}
	}

	//获得迭代后的路径
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
* Comment:一种改进的蚁群算法，每次只有最优的路径才有资格留下信息素
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
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
			//初始化信息素矩阵
			pheromone_matrix[i][j] = 2;
		}
	}

	//开始迭代
	vector<int> temp_path[ANT_NUM];
	double temp_length[ANT_NUM];
	int bestAntId;	//记录最好的蚂蚁！
	double bestLength;
	for (int iterCount = 0; iterCount < ITERATE_TIMES; iterCount++)
	{
		bestLength = INT_MAX;
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			//初始化蚂蚁
			if (antId < NODE_NUM)
			{
				ants[antId].initiazation(antId, false);
			}
			else
			{
				ants[antId].initiazation(rand() % NODE_NUM, true);
			}
			//每只蚂蚁开始干活
			while (ants[antId].selectNextNode(nodes, pheromone_matrix) != -1);
			//对比选择本次最优秀的路径信息
			temp_path[antId] = ants[antId].getPath();
			temp_length[antId] = ants[antId].getPathLength();
			if (temp_length[antId] < bestLength)
			{
				bestAntId = antId;
				bestLength = temp_length[antId];
			}
		}
		if (iterCount == ITERATE_TIMES - 1)break;	//最后一次不用更新信息素矩阵，直接跳出
		//更新信息素矩阵
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				//信息素挥发
				pheromone_matrix[i][j] *= (1 - VOLATILITY);
			}
		}
		int from, to;
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			for (auto it = temp_path[antId].begin() + 1; it != temp_path[antId].end(); it++)
			{
				//精英的额外信息素
				double eliteEx = 0;
				if (antId == bestAntId)
				{
					eliteEx = NORMAL_NUM / bestLength;
				}
				//增加信息素
				from = *(it - 1);
				to = *it;
				pheromone_matrix[from][to] = pheromone_matrix[to][from] += (NORMAL_NUM / temp_length[antId] + ELITE_FACTOR * eliteEx);
			}
		}

		//与历史最优路径比较
		if (bestLength < historyBestPathLength)
		{
			historyBestPathLength = bestLength;
			historyBestPath = ants[bestAntId].getPathString();
		}
	}

	//获得迭代后的路径
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