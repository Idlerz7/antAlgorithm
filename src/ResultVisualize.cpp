#include "ResultVisualize.h"
#include "Param.h"

void ResultVisualize::framebufferSizeCallback(GLFWwindow* frame, int width, int height)
{
	glViewport(0, 0, width, height);
}

ResultVisualize::ResultVisualize(const char* vShaderPath, const char* fShaderPath)
{
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->vShaderPath = vShaderPath;
	this->fShaderPath = fShaderPath;
	vbufHasSet = false;
	ibufHasSet = false;
}

ResultVisualize::~ResultVisualize()
{
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
	auto func = ResultVisualize::framebufferSizeCallback;
	glfwSetFramebufferSizeCallback(mainFrame, func);	//�󶨻ص�����

	this->setVertexShader(vShaderPath);
	this->setFragementShader(fShaderPath);
	shaderProgram = glCreateProgram();	//����shader����
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragementShader);
	int success;
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR::SHADER::LINK_FAILED\n" << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragementShader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
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

void ResultVisualize::setIterateTimes(int times)
{
	this->iterateTimes = times;
}

void ResultVisualize::processInput()
{
	if (glfwGetKey(this->mainFrame, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->mainFrame, true);
	}
}

void ResultVisualize::setVertexBuffers(float *vertex)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if (!vbufHasSet)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * NODE_NUM, vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//���ö�������ָ��
		glEnableVertexAttribArray(0);
		vbufHasSet = true;
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * NODE_NUM, vertex);
	}
}

void ResultVisualize::setIndicesBuffers(unsigned int *indices)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	if (!ibufHasSet)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*(NODE_NUM + 1), indices, GL_STREAM_DRAW);
		ibufHasSet = true;
	}
	else
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int)*(NODE_NUM + 1), indices);
	}
}