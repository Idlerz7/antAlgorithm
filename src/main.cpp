
#include "algorithmProcess.h"
#include "ResultVisualize.h"
#include <iostream>
#include <random>
#include <ctime>
#include <glad/glad.h>
#include <glfw3.h>
using namespace std;

//函数声明



//opengl函数
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//主函数

int main(int argc,char* argv[])
{
	/*glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1200, 800, "antAlgorithm", NULL, NULL);
	if (window == NULL)
	{
		cout << "创建窗口失败" << endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "初始化GLAD失败" << endl;
		return -1;
	}
	glViewport(0, 0, 1200, 800);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "layout (location = 1) in vec3 aColor;\n"
									 "out vec3 ourColor;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
									 "	ourColor = aColor;"
									 "}\n";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	const char* FragShaderSource = "#version 330 core\n"
								   "out vec4 FragColor;\n"
								   "in vec3 ourColor;\n"
								   "void main()\n"
								   "{\n"
								   "	FragColor = vec4(ourColor,1.0);\n"
								   "}\n";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		cout << "ERROR::SHADER::LINK_FAILED\n" << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(5.0f);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 3);
	
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	//注意删除掉
	return 0;

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
	minmaxAntAlgorithm(nodes, ants);*/
	//定义变量
	Node nodes[NODE_NUM];
	Ant ants[ANT_NUM];
	//初始化节点
	srand((unsigned int)time(0));
	for (int i = 0; i < NODE_NUM; i++)
	{
		//初始化节点(可能重复，待解决)
		int x = rand() % 100;
		int y = rand() % 100;
		nodes[i].setCoordinate(x, y);
	}
	ResultVisualize visualizer("./vertexShader.vert","./fragementShader.frag");
	visualizer.createWindow(800, 600, "antAlgorithm");
	float vertex[NODE_NUM * 3];
	praseNode(nodes, vertex);
	visualizer.setVertexBuffers(vertex);
	void (*updateFunction)(Ant*,double(*)[NODE_NUM],vector<int>[ANT_NUM],int) = baseUpdatePheromoneMatrix;
	auto funcForVisual = [&](double (*matrix)[NODE_NUM],double &historyBestLength, vector<int> &retHistoryBestPath) {
		vector<int> tempPath[ANT_NUM];
		int bestAntId;
		iterOneTime(nodes, ants, matrix, tempPath, bestAntId);
		updateFunction(ants, matrix, tempPath, bestAntId);
		if (historyBestLength > ants[bestAntId].getPathLength())
		{
			historyBestLength = ants[bestAntId].getPathLength();
			retHistoryBestPath = ants[bestAntId].getPath();
		}
	};
	visualizer.mainLoop(funcForVisual);
	baseAntAlgorithm(nodes, ants);
	eliteAntAlgorithm(nodes, ants);
	minmaxAntAlgorithm(nodes, ants);
	system("pause");
	return 0;
}



void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}