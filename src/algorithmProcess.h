#pragma once
#include "Ant.h"
#include "Node.h"
#include "Param.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

/*
* Comment:初始化信息素矩阵
* Param matrix 信息素矩阵 double**
* Param initVal 初始化值 double
* @Return void
*/
void initPheromoneMatrix(double(*matrix)[NODE_NUM], double initVal);

/*
* Comment:一次迭代过程
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param retPath 本次迭代的路径返回参数 vector<int>[ANT_NUM]
* Param retBestAntId 本次迭代的最佳蚂蚁索引号 int &
* @Return double 返回本次最佳路径的路径长度
*/
double iterOneTime(Node* nodes, Ant* ants, double(*pheromone_matrix)[NODE_NUM], std::vector<int> retPath[ANT_NUM], int &retBestAntId);

/*
* Comment:原始算法更新信息素矩阵的方法
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param iterPath 本次迭代的路径 vector<int>[ANT_NUM]
* Param bestAntId 本次迭代的最佳蚂蚁索引号 int
* @Return void
*/
void baseUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], std::vector<int> iterPath[ANT_NUM], int bestAntId);

/*
* Comment:精英蚁群算法更新信息素矩阵的方法
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param iterPath 本次迭代的路径 vector<int>[ANT_NUM]
* Param bestAntId 本次迭代的最佳蚂蚁索引号 int
* @Return void
*/
void eliteUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId);

/*
* Comment:最大最小蚁群算法更新信息素矩阵的方法
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param iterPath 本次迭代的路径 vector<int>[ANT_NUM]
* Param bestAntId 本次迭代的最佳蚂蚁索引号 int
* @Return void
*/
void minmaxUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId);

/*
* Comment:与历史最好路径比较并更新信息
* Param historyBestPath 蚂蚁对象数组 string &
* Param historyBestPathLength 信息素矩阵 double &
* Param iterBestPath 本次迭代的路径 string
* Param iterBestPathLength 本次迭代的最佳路径长度 int
* @Return void
*/
void compareWithHistory(string &historyBestPath, double &historyBestPathLength, string iterBestPath, double iterBestPathLength);

/*
* Comment:基础的蚁群算法
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* @Return void
*/
void baseAntAlgorithm(Node* nodes, Ant* ants);

/*
* Comment:一种改进的蚁群算法，每次最优的路径会留下信息素额外的
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* @Return void
*/
void eliteAntAlgorithm(Node* nodes, Ant* ants);

/*
* Comment:一种改进的蚁群算法，每次只有最优的路径才有资格留下信息素
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* @Return void
*/
void minmaxAntAlgorithm(Node* nodes, Ant* ants);

/*
* Comment:解析顶点对象
* Param nodes 顶点对象数组 Node*
* Param vertex 解析后顶点数组 float*
* @Return void
*/
void praseNode(Node* nodes, float *vertex);

/*
* Comment:解析顶点对象
* Param path 路径 vector<int>
* Param indices 解析后索引数组 unsigned int *
* @Return void
*/
void prasePath(vector<int> path, unsigned int *indices);