//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glad/glad.h>
//#include <glfw3.h>
//#include <iostream>
//
//#pragma region Funções
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//#pragma endregion
//
//
//
//int main() {
//#pragma region Declarações
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"layout (location = 1) in vec3 aColor;\n"
//		"out vec3 ourColor;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos, 1.0);\n"
//		"   ourColor = aColor;\n"
//		"}\0";
//
//	const char* fragmentShaderSource = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"in vec3 ourColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(ourColor, 1.0f);\n"
//		"}\n\0";
//
//	const unsigned int S_WIDTH = 800;
//	const unsigned int S_HEIGHT = 600;
//	GLFWwindow* window;
//	unsigned int vertexShader;
//	unsigned int fragmentShader;
//	unsigned int shaderProgram;
//	unsigned int VBOs[2], VAOs[2], EBO[2];
//	int success;
//	char infoLog[512];
//	float Vertices[] = {
//		// positions         // colors
//		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
//		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
//		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
//	};
//	unsigned int indices[] = {
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//	glm::mat4 transform;
//	unsigned int transformLoc;
//#pragma endregion
//
//#pragma region Inicializações
//		#pragma region glfwInit
//				glfwInit();
//				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//				#ifdef __APPLE__
//					glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//				#endif
//		#pragma endregion
//
//		#pragma region Window
//					window = glfwCreateWindow(S_WIDTH, S_HEIGHT, "LearnOpenGL", NULL, NULL);
//					if (window == NULL)
//					{
//						std::cout << "Failed to create GLFW window" << std::endl;
//						glfwTerminate();
//						return -1;
//					}
//					glfwMakeContextCurrent(window);
//					glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//		#pragma endregion
//
//		#pragma region GLAD
//					if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//					{
//						std::cout << "Failed to initialize GLAD" << std::endl;
//						return -1;
//					}
//		#pragma endregion
//		
//		#pragma region Shaders
//					//-------------------CREATE//-------------------
//					vertexShader = glCreateShader(GL_VERTEX_SHADER);
//					fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//					shaderProgram = glCreateProgram();
//					//-------------------//-------------------//-------------------
//
//
//
//					//-------------------COMPILE VERTEX//-------------------
//					glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//					glCompileShader(vertexShader);
//					glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//					if (!success)
//					{
//						glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//						std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//					}
//					//-------------------//-------------------//-------------------
//
//
//
//					//-------------------COMPILE FRAGMENT//-------------------
//					glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//					glCompileShader(fragmentShader);
//					glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//					if (!success)
//					{
//						glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//						std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//					}
//					//-------------------//-------------------//-------------------
//
//
//
//					//-------------------ATTACH SHADER//-------------------
//					glAttachShader(shaderProgram, vertexShader);
//					glAttachShader(shaderProgram, fragmentShader);
//					glLinkProgram(shaderProgram);
//					glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//					if (!success) {
//						glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//						std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//					}
//					//-------------------//-------------------//-------------------
//
//					glDeleteShader(vertexShader);
//					glDeleteShader(fragmentShader);
//
//					//-------------------VAO, VBO e EBO//-------------------
//					glGenVertexArrays(2, VAOs); 
//					glGenBuffers(2, VBOs);
//					//glGenBuffers(2, EBO);
//
//					glBindVertexArray(VAOs[0]);
//					glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
//					glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
//				
//					// position attribute
//					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//					glEnableVertexAttribArray(0);
//
//					// color attribute
//					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//					glEnableVertexAttribArray(1);
//					//-------------------//-------------------//-------------------
//
//					glUseProgram(shaderProgram);
//		#pragma endregion
//
//#pragma endregion
//
//#pragma region Render
//	while (!glfwWindowShouldClose(window))
//	{					
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// render the triangle
//		glBindVertexArray(VAOs[0]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//#pragma endregion
//
//#pragma region Final
//	glDeleteVertexArrays(2, VAOs);
//	glDeleteBuffers(2, VBOs);
//	glDeleteProgram(shaderProgram);
//	glfwTerminate();
//#pragma endregion
//
//
//	return 0;
//}
//
//#pragma region Imp. Funções
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//#pragma endregion
