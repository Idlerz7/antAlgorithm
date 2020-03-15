#include "algorithmProcess.h"

/*
* Comment:�����������
* Param nodes ����������� Node*
* Param vertex �����󶥵����� float*
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
* Comment:�����������
* Param path ·�� vector<int>
* Param indices �������������� unsigned int *
* @Return void
*/
void prasePath(vector<int> path, unsigned int *indices)
{
	int indicesIndex = 0;
	for_each(path.begin(), path.end(), [&](int value) {indices[indicesIndex++] = value; });
}

/*
* Comment:��ʼ����Ϣ�ؾ���
* Param matrix ��Ϣ�ؾ��� double**
* Param initVal ��ʼ��ֵ double
* @Return void
*/
void initPheromoneMatrix(double (*matrix)[NODE_NUM],double initVal)
{
	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			//��ʼ����Ϣ�ؾ���
			matrix[i][j] = initVal;
		}
	}
}

/*
* Comment:һ�ε�������
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param retPath ���ε�����·�����ز��� vector<int>[ANT_NUM]
* Param retBestAntId ���ε������������������ int &
* @Return double ���ر������·����·������
*/
double iterOneTime(Node* nodes, Ant* ants, double (*pheromone_matrix)[NODE_NUM],vector<int> retPath[ANT_NUM],int &retBestAntId)
{
	//һ�ε���
	vector<int> *temp_path = retPath;
	double temp_length[ANT_NUM];
	int randomAntNum = (int)floor(ANT_NUM*ANT_RANDOM_RATE);
	int bestAntId;	//��¼��õ����ϣ�
	double bestLength = INT_MAX;
	for (int antId = 0; antId < ANT_NUM; antId++)
	{
		//��������
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
	retBestAntId = bestAntId;
	return bestLength;
}

/*
* Comment:ԭʼ�㷨������Ϣ�ؾ���ķ���
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param iterPath ���ε�����·�� vector<int>[ANT_NUM]
* Param bestAntId ���ε������������������ int
* @Return void
*/
void baseUpdatePheromoneMatrix(Ant* ants, double (*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM],int bestAntId)
{
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
		for (auto it = iterPath[antId].begin() + 1; it != iterPath[antId].end(); it++)
		{
			//������Ϣ��
			from = *(it - 1);
			to = *it;
			pheromone_matrix[from][to] = pheromone_matrix[to][from] += NORMAL_NUM / ants[antId].getPathLength();
		}
	}
}

/*
* Comment:��Ӣ��Ⱥ�㷨������Ϣ�ؾ���ķ���
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param iterPath ���ε�����·�� vector<int>[ANT_NUM]
* Param bestAntId ���ε������������������ int
* @Return void
*/
void eliteUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId)
{
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
		for (auto it = iterPath[antId].begin() + 1; it != iterPath[antId].end(); it++)
		{
			//��Ӣ�Ķ�����Ϣ��
			double eliteEx = 0;
			if (antId == bestAntId)
			{
				eliteEx = NORMAL_NUM / ants[antId].getPathLength();
			}
			//������Ϣ��
			from = *(it - 1);
			to = *it;
			pheromone_matrix[from][to] = pheromone_matrix[to][from] += (NORMAL_NUM / ants[antId].getPathLength() + ELITE_FACTOR * eliteEx);
		}
	}
}


/*
* Comment:�����С��Ⱥ�㷨������Ϣ�ؾ���ķ���
* Param ants ���϶������� Ant*
* Param matrix ��Ϣ�ؾ��� double*[NODE_NUM]
* Param iterPath ���ε�����·�� vector<int>[ANT_NUM]
* Param bestAntId ���ε������������������ int
* @Return void
*/
void minmaxUpdatePheromoneMatrix(Ant* ants, double(*pheromone_matrix)[NODE_NUM], vector<int> iterPath[ANT_NUM], int bestAntId)
{
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

	for (auto it = iterPath[bestAntId].begin() + 1; it != iterPath[bestAntId].end(); it++)
	{
		//������Ϣ��
		from = *(it - 1);
		to = *it;
		remain_matrix[from][to] = remain_matrix[to][from] += NORMAL_NUM / ants[bestAntId].getPathLength();
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
}

/*
* Comment:����ʷ���·���Ƚϲ�������Ϣ
* Param historyBestPath ���϶������� string &
* Param historyBestPathLength ��Ϣ�ؾ��� double &
* Param iterBestPath ���ε�����·�� string
* Param iterBestPathLength ���ε��������·������ double
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
* Comment:��������Ⱥ�㷨
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void baseAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//��Ϣ�ؾ���
	string bestPath;	//��ǰ���·�����ַ����ͣ�
	double bestPathLength = INT_MAX;	//��ǰ���·������
	string historyBestPath;	//��ʷ���·�����ַ����ͣ�
	double historyBestPathLength = INT_MAX;	//��ǰ���·��
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
* Comment:һ�ָĽ�����Ⱥ�㷨��ÿ�����ŵ�·����������Ϣ�ض����
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void eliteAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//��Ϣ�ؾ���
	string bestPath;	//��ǰ���·�����ַ����ͣ�
	double bestPathLength = INT_MAX;	//��ǰ���·������
	string historyBestPath;	//��ʷ���·�����ַ����ͣ�
	double historyBestPathLength = INT_MAX;	//��ǰ���·��
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
* Comment:һ�ָĽ�����Ⱥ�㷨��ÿ��ֻ�����ŵ�·�������ʸ�������Ϣ��
* Param nodes �ڵ�������� Node*
* Param ants ���϶������� Ant*
* @Return void
*/
void minmaxAntAlgorithm(Node* nodes, Ant* ants)
{
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//��Ϣ�ؾ���
	string bestPath;	//��ǰ���·�����ַ����ͣ�
	double bestPathLength = INT_MAX;	//��ǰ���·������
	string historyBestPath;	//��ʷ���·�����ַ����ͣ�
	double historyBestPathLength = INT_MAX;	//��ǰ���·��
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