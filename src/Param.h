#pragma once
//参数宏定义
#define ITERATE_TIMES 100	//最大迭代次数
#define NODE_NUM 20 //设定节点个数
#define ANT_NUM 50	//设定蚂蚁个数
#define ANT_RANDOM_RATE 0.1	//随机蚂蚁的占有率
#define VOLATILITY 0.2	//信息素的挥发性
#define NORMAL_NUM 10	//正常数
#define PHEROMONE_FACTOR 2	//设定信息素因子
#define HEURISTIC_FACTOR 4	//设定启发式因子
#define ELITE_FACTOR 0.3	//精英蚂蚁的额外信息素权值
#define TAO_MIN 0.1	//最大最小蚂蚁算法中信息素浓度下限
#define TAO_MAX 2.5	//最大最小蚂蚁算法中信息素浓度上限