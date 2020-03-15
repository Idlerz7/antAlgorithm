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
	GLFWwindow *mainFrame;	//����ָ��
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
	static void framebufferSizeCallback(GLFWwindow* frame, int width, int height);	//���ڴ�С�ı�Ļص�����
public:
	ResultVisualize(const char* vShaderPath, const char* fShaderPath);	//���캯������ʼ��glfw
	~ResultVisualize();
	bool createWindow(int width, int height,const char* title);	//��������ָ�룬����glad��������ͼ
	bool setVertexShader(const char* glslPath);	//���ö�����ɫ��
	bool setFragementShader(const char* glslPath);	//����Ƭ����ɫ��
	void setIterateTimes(int times);	//���õ�������
	void processInput();	//IO����Ĵ���
	void setVertexBuffers(float *vertex);	//���ö��㻺��
	void setIndicesBuffers(unsigned int *indices);	//������������

	template <typename lambda>
	void mainLoop(lambda func);	//��Ҫѭ������Ҫ�����㷨����Ҫ����
};

template <typename lambda>
void ResultVisualize::mainLoop(lambda func)
{
	int currentTimes = 0;
	glPointSize(10.0f);
	
	double pheromone_matrix[NODE_NUM][NODE_NUM];	//��Ϣ�ؾ���
	double historyBestPathLength = INT_MAX;	//��ǰ���·��
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
			cout << "�������" << endl;
		}
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_POINTS, NODE_NUM, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_LINE_STRIP, NODE_NUM+1, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(this->mainFrame);	//�����ͼ
		glfwPollEvents();
	}
	glfwTerminate();
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}