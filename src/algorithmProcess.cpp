#include "algorithmProcess.h"

/*
* Comment:解析顶点对象
* Param nodes 顶点对象数组 Node*
* Param vertex 解析后顶点数组 float*
* @Return void
*/
void praseNode(Node* nodes, float *vertex)
{
	int vertexIndex = 0;
	for (int nodeIndex = 0; nodeIndex < NODE_NUM; nodeIndex++)
	{
		int *coor = nodes[nodeIndex].getCoordinate();
		vertex[vertexIndex++] = (((float)coor[0] / 100) - 0.5f) * 2;
		vertex[vertexIndex++] = (((float)coor[1] / 100) - 0.5f) * 2;
		vertex[vertexIndex++] = 0.0f;
	}
}

/*
* Comment:解析顶点对象
* Param path 路径 vector<int>
* Param indices 解析后索引数组 unsigned int *
* @Return void
*/
void prasePath(vector<int> path, unsigned int *indices)
{
	int indicesIndex = 0;
	for_each(path.begin(), path.end(), [&](int value) {indices[indicesIndex++] = value; });
}

/*
* Comment:初始化信息素矩阵
* Param matrix 信息素矩阵 double**
* Param initVal 初始化值 double
* @Return void
*/
void initPheromoneMatrix(double (*matrix)[NODE_NUM],double initVal)
{
	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//初始化信息素矩阵
			matrix[i][j] = initVal;
		}
	}
}

/*
* Comment:一次迭代过程
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param retPath 本次迭代的路径返回参数 vector<int>[ANT_NUM]
* Param retBestAntId 本次迭代的最佳蚂蚁索引号 int &
* @Return double 返回本次最佳路径的路径长度
*/
double iterOneTime(Node* nodes, Ant* ants, double (*pheromone_matrix)[NODE_NUM],vector<int> retPath[ANT_NUM],int &retBestAntId)
{
	//一次迭代
	vector<int> *temp_path = retPath;
	double temp_length[ANT_NUM];
	int randomAntNum = (int)floor(ANT_NUM*ANT_RANDOM_RATE);
	int bestAntId;	//记录最好的蚂蚁！
	double bestLength = INT_MAX;
	for (int antId = 0; antId < ANT_NUM; antId++)
	{
		//重置蚂蚁
		if (antId > randomAntNum)
		{
			ants[antId].initiazation(rand() % NODE_NUM, false);
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
	retBestAntId = bestAntId;
	return bestLength;
}

/*
* Comment:原始算法更新信息素矩阵的方法
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param iterPath 本次迭代的路径 vector<int>[ANT_NUM]
* Param bestAntId 本次迭代的最佳蚂蚁索引号 int
* @Return void
*/
void baseUpdatePheromoneMatrix(Ant* ants, double (*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM],int bestAntId)
{
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
		for (auto it = iterPath[antId].begin() + 1; it != iterPath[antId].end(); it++)
		{
			//增加信息素
			from = *(it - 1);
			to = *it;
			pheromone_matrix[from][to] = pheromone_matrix[to][from] += NORMAL_NUM / ants[antId].getPathLength();
		}
	}
}

/*
* Comment:精英蚁群算法更新信息素矩阵的方法
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param iterPath 本次迭代的路径 vector<int>[ANT_NUM]
* Param bestAntId 本次迭代的最佳蚂蚁索引号 int
* @Return void
*/
void eliteUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId)
{
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
		for (auto it = iterPath[antId].begin() + 1; it != iterPath[antId].end(); it++)
		{
			//精英的额外信息素
			double eliteEx = 0;
			if (antId == bestAntId)
			{
				eliteEx = NORMAL_NUM / ants[antId].getPathLength();
			}
			//增加信息素
			from = *(it - 1);
			to = *it;
			pheromone_matrix[from][to] = pheromone_matrix[to][from] += (NORMAL_NUM / ants[antId].getPathLength() + ELITE_FACTOR * eliteEx);
		}
	}
}


/*
* Comment:最大最小蚁群算法更新信息素矩阵的方法
* Param ants 蚂蚁对象数组 Ant*
* Param matrix 信息素矩阵 double*[NODE_NUM]
* Param iterPath 本次迭代的路径 vector<int>[ANT_NUM]
* Param bestAntId 本次迭代的最佳蚂蚁索引号 int
* @Return void
*/
void minmaxUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId)
{
	double remain_matrix[NODE_NUM][NODE_NUM];
	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//信息素更新矩阵初始化
			remain_matrix[i][j] = 0;
		}
	}
	//计算遗留的信息素
	int from, to;

	for (auto it = iterPath[bestAntId].begin() + 1; it != iterPath[bestAntId].end(); it++)
	{
		//增加信息素
		from = *(it - 1);
		to = *it;
		remain_matrix[from][to] = remain_matrix[to][from] += NORMAL_NUM / ants[bestAntId].getPathLength();
	}
	//更新信息素矩阵
	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			double newValue = pheromone_matrix[i][j] * (1 - VOLATILITY) + remain_matrix[i][j];
			pheromone_matrix[i][j] = min(TAO_MAX, max(TAO_MIN, newValue));
		}
	}
}

/*
* Comment:与历史最好路径比较并更新信息
* Param historyBestPath 蚂蚁对象数组 string &
* Param historyBestPathLength 信息素矩阵 double &
* Param iterBestPath 本次迭代的路径 string
* Param iterBestPathLength 本次迭代的最佳路径长度 double
* @Return void
*/
void compareWithHistory(string &historyBestPath, double &historyBestPathLength, string iterBestPath, double iterBestPathLength)
{
	if (iterBestPathLength < historyBestPathLength)
	{
		historyBestPathLength = iterBestPathLength;
		historyBestPath = iterBestPath;
	}
}

/*
* Comment:基础的蚁群算法
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* @Return void
*/
void baseAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//信息素矩阵
	string bestPath;	//当前最短路径（字符串型）
	double bestPathLength = INT_MAX;	//当前最短路径长度
	string historyBestPath;	//历史最短路径（字符串型）
	double historyBestPathLength = INT_MAX;	//当前最短路径
	initPheromoneMatrix(pheromone_matrix, TAO_MAX);
	for (int iter = 0; iter < ITERATE_TIMES; iter++)
	{
		vector<int> tempPath[ANT_NUM];
		int bestAntId;
		iterOneTime(nodes, ants, pheromone_matrix, tempPath, bestAntId);
		baseUpdatePheromoneMatrix(ants, pheromone_matrix, tempPath, bestAntId);
		compareWithHistory(historyBestPath, historyBestPathLength, ants[bestAntId].getPathString(), ants[bestAntId].getPathLength());
	}
	cout << "--baseAntAlgorithm--" << endl;
	cout << "bestPath:" << historyBestPath << endl;
	cout << "bestPathLengt:" << historyBestPathLength << endl;
}

/*
* Comment:一种改进的蚁群算法，每次最优的路径会留下信息素额外的
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* @Return void
*/
void eliteAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//信息素矩阵
	string bestPath;	//当前最短路径（字符串型）
	double bestPathLength = INT_MAX;	//当前最短路径长度
	string historyBestPath;	//历史最短路径（字符串型）
	double historyBestPathLength = INT_MAX;	//当前最短路径
	initPheromoneMatrix(pheromone_matrix, TAO_MAX);
	for (int iter = 0; iter < ITERATE_TIMES; iter++)
	{
		vector<int> tempPath[ANT_NUM];
		int bestAntId;
		iterOneTime(nodes, ants, pheromone_matrix, tempPath, bestAntId);
		eliteUpdatePheromoneMatrix(ants, pheromone_matrix, tempPath, bestAntId);
		compareWithHistory(historyBestPath, historyBestPathLength, ants[bestAntId].getPathString(), ants[bestAntId].getPathLength());
	}
	cout << "--eliteAntAlgorithm--" << endl;
	cout << "bestPath:" << historyBestPath << endl;
	cout << "bestPathLengt:" << historyBestPathLength << endl;
}

/*
* Comment:一种改进的蚁群算法，每次只有最优的路径才有资格留下信息素
* Param nodes 节点对象数组 Node*
* Param ants 蚂蚁对象数组 Ant*
* @Return void
*/
void minmaxAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//信息素矩阵
	string bestPath;	//当前最短路径（字符串型）
	double bestPathLength = INT_MAX;	//当前最短路径长度
	string historyBestPath;	//历史最短路径（字符串型）
	double historyBestPathLength = INT_MAX;	//当前最短路径
	initPheromoneMatrix(pheromone_matrix, TAO_MAX);
	for (int iter = 0; iter < ITERATE_TIMES; iter++)
	{
		vector<int> tempPath[ANT_NUM];
		int bestAntId;
		iterOneTime(nodes, ants, pheromone_matrix, tempPath, bestAntId);
		minmaxUpdatePheromoneMatrix(ants, pheromone_matrix, tempPath, bestAntId);
		compareWithHistory(historyBestPath, historyBestPathLength, ants[bestAntId].getPathString(), ants[bestAntId].getPathLength());
	}
	cout << "--minmaxAntAlgorithm--" << endl;
	cout << "bestPath:" << historyBestPath << endl;
	cout << "bestPathLengt:" << historyBestPathLength << endl;
}