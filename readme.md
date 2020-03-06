# 算法课研讨题目——蚁群算法

## 更新日志

* 原始蚁群算法已经实现。

* 新增随机选择节点的蚂蚁，添加随机因素，防止过快的收敛导致局部最优。

* 修改下一个节点的选择方式，由选择概率最大节点改为轮盘赌算法选择。

* 实现精英蚁群算法。

* 修复选择的路径不是历史最优的问题，并对参数做出调整。

* 实现最大最小蚁群算法；修改蚂蚁的起点分配方式为全体蚂蚁随机分配起点；修改随机选择下一节点的蚂蚁的数量为所有蚂蚁的10%；修正信息素挥发量过多的错误。

## 一点心得

* 随着要处理的节点的个数的增加，似乎要迭代的次数更多才会完成收敛得到一条局部最优的路径。其中，基础的算法迭代次数需要的最少，精英蚁群算法次之，最大最小蚁群算法需要的迭代次数最多。

* 目前设置处理节点20个，迭代次数选择300的效果不错。
