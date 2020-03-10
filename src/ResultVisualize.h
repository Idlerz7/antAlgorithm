#pragma once
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
	unsigned int *VAOs;
	unsigned int *VBOs;
	unsigned int *EBOs;
	int objectNum;
	unsigned int shaderProgram;
	void framebufferSizeCallback(GLFWwindow* frame, int width, int height);	//窗口大小改变的回调函数
public:
	ResultVisualize();	//构造函数，初始化glfw
	~ResultVisualize();
	bool createWindow(int width, int height,const char* title);	//创建窗口指针，加载glad，设置视图
	bool setVertexShader(const char* glslPath);	//设置顶点着色器
	bool setFragementShader(const char* glslPath);	//设置片段着色器
};

void ResultVisualize::framebufferSizeCallback(GLFWwindow* frame, int width, int height)
{
	glViewport(0, 0, width, height);
}

ResultVisualize::ResultVisualize()
{
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	shaderProgram = glCreateProgram();	//创建shader程序
}

ResultVisualize::~ResultVisualize()
{
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(objectNum, VAOs);
	glDeleteBuffers(objectNum, VBOs);
	glDeleteBuffers(objectNum, EBOs);
	glfwTerminate();
	if (VAOs != NULL)
	{
		delete[]VAOs;
	}
	if (VBOs != NULL)
	{
		delete[]VBOs;
	}
	if (EBOs != NULL)
	{
		delete[]EBOs;
	}
}

bool ResultVisualize::createWindow(int width, int height, const char* title)
{
	bool OK = true;
	mainFrame = glfwCreateWindow(width, height, title, NULL, NULL);	//创建窗口
	if (mainFrame == NULL)OK = false;
	glfwMakeContextCurrent(mainFrame);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))OK = false;	//加载glad
	if (!OK)return OK;
	glViewport(0, 0, width, height);	//设置视口
	glfwSetFramebufferSizeCallback(mainFrame,this->framebufferSizeCallback);	//绑定回调函数
	return OK;
}

bool ResultVisualize::setVertexShader(const char* glslPath)
{
	std::string vertexShaderCode;
	std::ifstream vertexShaderFile;
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	//保证ifstream对象可以抛出异常
	try
	{
		//打开glsl顶点着色器源码文件
		vertexShaderFile.open(glslPath);
		std::stringstream vertexShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();	//关闭文件流
		vertexShaderCode = vertexShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FAILED_TO_OPEN_FILE" << std::endl;
		return false;
	}
	const char* vertexShaderSource = vertexShaderCode.c_str();	//转化为c字符串
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//检查是否编译成功
	char infoLog[512];
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILE_FAILED:\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool ResultVisualize::setFragementShader(const char* glslPath)
{
	std::string fragementShaderCode;
	std::ifstream fragementShaderFile;
	fragementShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	//保证ifstream对象可以抛出异常
	try
	{
		//打开glsl顶点着色器源码文件
		fragementShaderFile.open(glslPath);
		std::stringstream fragementShaderStream;
		fragementShaderStream << fragementShaderFile.rdbuf();
		fragementShaderFile.close();	//关闭文件流
		fragementShaderCode = fragementShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FAILED_TO_OPEN_FILE" << std::endl;
		return false;
	}
	const char* fragementShaderSource = fragementShaderCode.c_str();	//转化为c字符串
	unsigned int fragementShader;
	fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragementShader, 1, &fragementShaderSource, NULL);
	glCompileShader(fragementShader);
	//检查是否编译成功
	char infoLog[512];
	int success;
	glGetShaderiv(fragementShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragementShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILE_FAILED:\n" << infoLog << std::endl;
		return false;
	}
	return true;
}