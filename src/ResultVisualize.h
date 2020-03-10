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
	GLFWwindow *mainFrame;	//����ָ��
	unsigned int *VAOs;
	unsigned int *VBOs;
	unsigned int *EBOs;
	int objectNum;
	unsigned int shaderProgram;
	void framebufferSizeCallback(GLFWwindow* frame, int width, int height);	//���ڴ�С�ı�Ļص�����
public:
	ResultVisualize();	//���캯������ʼ��glfw
	~ResultVisualize();
	bool createWindow(int width, int height,const char* title);	//��������ָ�룬����glad��������ͼ
	bool setVertexShader(const char* glslPath);	//���ö�����ɫ��
	bool setFragementShader(const char* glslPath);	//����Ƭ����ɫ��
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
	shaderProgram = glCreateProgram();	//����shader����
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
	mainFrame = glfwCreateWindow(width, height, title, NULL, NULL);	//��������
	if (mainFrame == NULL)OK = false;
	glfwMakeContextCurrent(mainFrame);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))OK = false;	//����glad
	if (!OK)return OK;
	glViewport(0, 0, width, height);	//�����ӿ�
	glfwSetFramebufferSizeCallback(mainFrame,this->framebufferSizeCallback);	//�󶨻ص�����
	return OK;
}

bool ResultVisualize::setVertexShader(const char* glslPath)
{
	std::string vertexShaderCode;
	std::ifstream vertexShaderFile;
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	//��֤ifstream��������׳��쳣
	try
	{
		//��glsl������ɫ��Դ���ļ�
		vertexShaderFile.open(glslPath);
		std::stringstream vertexShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();	//�ر��ļ���
		vertexShaderCode = vertexShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FAILED_TO_OPEN_FILE" << std::endl;
		return false;
	}
	const char* vertexShaderSource = vertexShaderCode.c_str();	//ת��Ϊc�ַ���
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//����Ƿ����ɹ�
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
	fragementShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	//��֤ifstream��������׳��쳣
	try
	{
		//��glsl������ɫ��Դ���ļ�
		fragementShaderFile.open(glslPath);
		std::stringstream fragementShaderStream;
		fragementShaderStream << fragementShaderFile.rdbuf();
		fragementShaderFile.close();	//�ر��ļ���
		fragementShaderCode = fragementShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FAILED_TO_OPEN_FILE" << std::endl;
		return false;
	}
	const char* fragementShaderSource = fragementShaderCode.c_str();	//ת��Ϊc�ַ���
	unsigned int fragementShader;
	fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragementShader, 1, &fragementShaderSource, NULL);
	glCompileShader(fragementShader);
	//����Ƿ����ɹ�
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