#pragma once
#include "algorithmProcess.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class ResultVisualize
{
private:
	GLFWwindow *mainFrame;	//窗口指针
	unsigned int VAO;
	bool vbufHasSet;
	unsigned int VBO;
	bool ibufHasSet;
	unsigned int EBO;
	unsigned int vertexShader;
	unsigned int fragementShader;
	int iterateTimes;
	unsigned int shaderProgram;
	const char* vShaderPath;
	const char* fShaderPath;
	static void framebufferSizeCallback(GLFWwindow* frame, int width, int height);	//窗口大小改变的回调函数
public:
	ResultVisualize(const char* vShaderPath, const char* fShaderPath);	//构造函数，初始化glfw
	~ResultVisualize();
	bool createWindow(int width, int height,const char* title);	//创建窗口指针，加载glad，设置视图
	bool setVertexShader(const char* glslPath);	//设置顶点着色器
	bool setFragementShader(const char* glslPath);	//设置片段着色器
	void setIterateTimes(int times);	//设置迭代次数
	void processInput();	//IO输出的处理
	void setVertexBuffers(float *vertex);	//设置顶点缓存
	void setIndicesBuffers(unsigned int *indices);	//设置索引缓存

	template <typename lambda>
	void mainLoop(lambda func);	//主要循环，需要传入算法的主要过程
};

template <typename lambda>
void ResultVisualize::mainLoop(lambda func)
{
	int currentTimes = 0;
	glPointSize(10.0f);
	
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//信息素矩阵
	double historyBestPathLength = INT_MAX;	//当前最短路径
	initPheromoneMatrix(pheromone_matrix,TAO_MAX);

	while (!glfwWindowShouldClose(this->mainFrame))
	{
		this->processInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (currentTimes < ITERATE_TIMES)
		{
			vector<int> historyBestPath;
			func(pheromone_matrix, historyBestPathLength, historyBestPath);
			unsigned int indices[NODE_NUM + 1];
			prasePath(historyBestPath, indices);
			this->setIndicesBuffers(indices);
			currentTimes++;
		}
		else
		{
			cout << "迭代完成" << endl;
		}
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_POINTS, NODE_NUM, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_LINE_STRIP, NODE_NUM+1, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(this->mainFrame);	//缓冲绘图
		glfwPollEvents();
	}
	glfwTerminate();
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}