#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

// screen parameters
const unsigned int scr_width = 800;
const unsigned int scr_height = 600;
const char *scr_title = "Hello, triangle!";

// shaders paths
const char *vertPath = "shaders/shader.vert";
const char *fragPath = "shaders/shader.frag";

void inputProcess(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(){

	// initialize GLFW and creating context
	if(!glfwInit()){
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating window
	GLFWwindow *window = glfwCreateWindow(scr_width, scr_height, scr_title, NULL, NULL);
	if(!window){
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to load GLAD" << std::endl;
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader ourShader(vertPath, fragPath);

	// vertices of hello_triangle
	float vertices[] = {
		// positions 		// colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	// creating buffers and vertices attributes
	unsigned int VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// render loop
	while(!glfwWindowShouldClose(window)){

		inputProcess(window);

		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean memory
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

// check input and update
void inputProcess(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// callback on resize window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
