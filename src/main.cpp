#include "Ant.h"
#include "Node.h"
#include "Param.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

//函数声明

//主函数
int main()
{
	//定义变量
	Node nodes[NODE_NUM];
	Ant ants[ANT_NUM];
	double pheromone_matrix[NODE_NUM][NODE_NUM];
	string bestPath;
	double bestPathLength = INT_MAX;

	//初始化工作
	srand((unsigned int)time(0));
	for (int i = 0; i < NODE_NUM; i++)
	{
		//初始化蚂蚁起点
		//ants[i].updateCurentNode(i);
		//ants[i].updateTravelNode(i);
		//ants[i].setStartNode(i);
		//ants[i].updatePath(i);
		//初始化节点(可能重复，待解决)
		nodes[i].setCoordinate(rand() % 100, rand() % 100);
	}
	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//初始化信息素矩阵
			pheromone_matrix[i][j] = 2;
		}
	}

	//开始迭代
	for (int iterCount = 0; iterCount < ITERATE_TIMES; iterCount++)
	{
		//vector<int> temp_path[ANT_NUM];
		//double temp_length[ANT_NUM];
		for (int antId = 0; antId < ANT_NUM; antId++)
		{
			//初始化蚂蚁
			ants[antId].initiazation(antId);
			//每只蚂蚁开始干活
			while (ants[antId].selectNextNode(nodes, pheromone_matrix) != -1);
		}
		if (iterCount == ITERATE_TIMES - 1)break;	//最后一次不用更新信息素矩阵，直接跳出
		//更新信息素矩阵
		for (int i = 0; i < NODE_NUM; i++)
		{
			for (int j = 0; j < NODE_NUM; j++)
			{
				//信息素挥发
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
				//增加信息素
				from = *(it - 1);
				to = *it;
				pheromone_matrix[from][to] = pheromone_matrix[to][from] += NORMAL_NUM / temp_length[antId];
			}
		}
	}

	//获得一百次迭代后的路径
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

