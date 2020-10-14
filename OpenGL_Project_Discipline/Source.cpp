#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "Shader.h"

enum Color { red, green, blue };

#pragma region Funções
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void setColor(Color* color, int newColor);
void addCoordX(float* coord);
void addCoordY(float* coord);
void subCoordX(float* coord);
void subCoordY(float* coord);
void printCoordinates();
#pragma endregion

#pragma region Globais
Color col = red;
float coordx = 0, coordy = 0, accel = 0.0005;
#pragma endregion



int main() {
#pragma region Declarações
	const unsigned int S_WIDTH = 800;
	const unsigned int S_HEIGHT = 600;
	
	GLFWwindow* window;
	unsigned int VBO[2], VAO[2];
	float player[] = {
		// positions         // colors
		-0.06f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  // bottom left
		 0.06f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		 0.0f,  -0.4f, 0.0f,  0.0f, 1.0f, 1.0f   // top
	};

	float Enemy[] = {
		// positions         // colors
		-0.06f, 0.5f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
		 0.06f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
		 0.0f,  0.4f, 0.0f,  1.0f, 0.0f, 1.0f   // top
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
#pragma endregion
#pragma region Inicializações
#pragma region glfwInit
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
#pragma endregion

#pragma region Window
	window = glfwCreateWindow(S_WIDTH, S_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#pragma endregion

#pragma region GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
#pragma endregion

#pragma region Shaders
	
	Shader ourShader("transform.vs", "transform.fs");
	Shader thisShader("newShader.vs", "newShader.fs");

	//-------------------VAO, VBO//-------------------
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(player), player, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);





	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy), Enemy, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//-------------------//-------------------//-------------------

#pragma endregion

#pragma endregion

#pragma region RENDER
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(coordx, coordy, 0.0f));
		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		ourShader.use();
		unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		 

		glm::mat4 transform2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform2 = glm::translate(transform2, glm::vec3(0.5f, -0.5f, 0.0f));
		thisShader.use();
		unsigned int transformLoc2 = glGetUniformLocation(thisShader.ID, "transform");
		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform2));
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);


	glfwTerminate();
	return 0;
}

#pragma region Imp. Funções
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		subCoordX(&coordx);
		
	}
		
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		addCoordX(&coordx);
		
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		addCoordY(&coordy);
		
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		subCoordY(&coordy);
		
	}
		
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	
	glViewport(0, 0, width, height);
}

void setColor(Color *color, int newColor) {
	if (newColor == 0)
	{
		*color = red;
	}
	else if (newColor == 1) {
		*color = green;
	}
	else {
		*color = blue;
	}
}

void addCoordX(float *coord) {
	if (*coord >= 0.95) {
		*coord = 0.95;
	}else{
		*coord = *coord + accel;
	}
	
}

void subCoordX(float* coord) {
	if (*coord <= -0.95) {
		*coord = -0.95;
	}
	else {
		*coord = *coord + (-1* accel);
	}
	
}
void addCoordY(float* coord) {
	if (*coord >= 1.39) {
		*coord = 1.39;
	}
	else {
		*coord = *coord + accel;
	}
	
}



void subCoordY(float* coord) {
	if (*coord <= -0.5) {
		*coord = -0.5;
	}
	else {
		*coord = *coord + (-1 * accel);
	}
}

void printCoordinates()
{
	//system("CLS");
	std::cout << "(";
	std::cout << coordx;
	std::cout << " , ";
	std::cout << coordy;
	std::cout << ")";
	std::cout << std::endl;
}
#pragma endregion
