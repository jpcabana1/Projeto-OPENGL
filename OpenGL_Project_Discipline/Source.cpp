#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "Shader.h"
#include "ship.h"
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H
#include "filesystem.h"

enum Color { red, green, blue };

#pragma region Funções
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void setColor(Color* color, int newColor);
void addCoordX(float* coord);
void addCoordY(float* coord);
void subCoordX(float* coord);
void subCoordY(float* coord);
void printCoordinates(float p_coordx, float p_coordy);
void moveEnemy();
void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

#pragma endregion

#pragma region Globais
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};
Color col = red;
float accel = 0.0005;
float coordx1 = 0.0, coordy1 = 0.0;
bool left = true;

ship jogador;
float Enemy1[] = {
	// X      Y      Z        // colors
	-0.7f, 0.9f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
	 -0.5f, 0.9f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	 -0.6f,  0.8f, 0.0f,  1.0f, 0.0f, 1.0f   // top
};
float Enemy2[] = {
	// X      Y      Z        // colors
	-0.1f, 0.9f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
	 0.1f, 0.9f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	 0.0f,  0.8f, 0.0f,  1.0f, 0.0f, 1.0f   // top
};
float Enemy3[] = {
	// X      Y      Z        // colors
	0.5f, 0.9f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
	 0.7f, 0.9f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	 0.6f,  0.8f, 0.0f,  1.0f, 0.0f, 1.0f   // top
};
float Enemy4[] = {
	// X      Y      Z        // colors
	-0.7f, 0.3f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
	 -0.5f, 0.3f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	 -0.6f,  0.2f, 0.0f,  1.0f, 0.0f, 1.0f   // top
};
float Enemy5[] = {
	// X      Y      Z        // colors
	-0.1f, 0.3f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
	 0.1f, 0.3f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	 0.0f,  0.2f, 0.0f,  1.0f, 0.0f, 1.0f   // top
};
float Enemy6[] = {
	// X      Y      Z        // colors
	0.5f, 0.3f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
	 0.7f, 0.3f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	 0.6f,  0.2f, 0.0f,  1.0f, 0.0f, 1.0f   // top
};

#pragma endregion

std::map<GLchar, Character> Characters;
unsigned int VBO[8], VAO[8];

int main() {
#pragma region Declarações
	const unsigned int S_WIDTH = 800;
	const unsigned int S_HEIGHT = 600;
	
	GLFWwindow* window;
	
	
	//float player[] = {
	//	// positions         // colors
	//	-0.06f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  // bottom left
	//	 0.06f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	//	 0.0f,  -0.4f, 0.0f,  0.0f, 1.0f, 1.0f   // top
	//};

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

/*
#pragma region Fonts
	FT_Library ft;

	Shader shader("text.vs", "text.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(S_WIDTH), 0.0f, static_cast<float>(S_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// FreeType
		// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}

	// find path to font
	std::string font_name = FileSystem::getPath("resources/fonts/Antonio-Bold.ttf");
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
		return -1;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

#pragma endregion
*/

#pragma region Shaders
	
Shader ourShader("transform.vs", "transform.fs");
Shader thisShader("newShader.vs", "newShader.fs");
	//-------------------VAO, VBO//-------------------
	glGenVertexArrays(8, VAO);
	glGenBuffers(8, VBO);


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, (int)jogador.getSize(), jogador.getFormat(), GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//inimigo 1
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy1), Enemy1, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//inimigo 2
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy2), Enemy2, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//inimigo 3
	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy3), Enemy3, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//inimigo 3
	glBindVertexArray(VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy4), Enemy4, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//inimigo 5
	glBindVertexArray(VAO[5]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy5), Enemy5, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//inimigo 6
	glBindVertexArray(VAO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy6), Enemy6, GL_STATIC_DRAW);
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
		float time = (float)glfwGetTime();
		processInput(window);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*RenderText(shader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		RenderText(shader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));*/
#pragma region Player
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(jogador.getX(), jogador.getY(), 0.0f));
		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		ourShader.use();
		unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
#pragma endregion

#pragma region Enemies
		#pragma region Enemy1
				glm::mat4 transform2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
				transform2 = glm::translate(transform2, glm::vec3(coordx1, coordy1, 0.0f));
				//transform2 = glm::rotate(transform2, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
				thisShader.use();
				unsigned int transformLoc2 = glGetUniformLocation(thisShader.ID, "newShader");
				glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform2));
				glBindVertexArray(VAO[1]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
		#pragma endregion

		#pragma region Enemy2
				glm::mat4 transform3 = glm::mat4(1.0f); 
				transform3 = glm::translate(transform3, glm::vec3(coordx1, coordy1, 0.0f));
				thisShader.use();
				unsigned int transformLoc3 = glGetUniformLocation(thisShader.ID, "newShader");
				glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(transform3));
				glBindVertexArray(VAO[2]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
		#pragma endregion

		#pragma region Enemy3
				glm::mat4 transform4 = glm::mat4(1.0f);
				transform4 = glm::translate(transform4, glm::vec3(coordx1, coordy1, 0.0f));
				thisShader.use();
				unsigned int transformLoc4 = glGetUniformLocation(thisShader.ID, "newShader");
				glUniformMatrix4fv(transformLoc4, 1, GL_FALSE, glm::value_ptr(transform4));
				glBindVertexArray(VAO[3]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
		#pragma endregion

		#pragma region Enemy4
				glm::mat4 transform5 = glm::mat4(1.0f);
				transform5 = glm::translate(transform5, glm::vec3(coordx1, coordy1, 0.0f));
				thisShader.use();
				unsigned int transformLoc5 = glGetUniformLocation(thisShader.ID, "newShader");
				glUniformMatrix4fv(transformLoc5, 1, GL_FALSE, glm::value_ptr(transform5));
				glBindVertexArray(VAO[4]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
		#pragma endregion

		#pragma region Enemy5
				glm::mat4 transform6 = glm::mat4(1.0f);
				transform6 = glm::translate(transform6, glm::vec3(coordx1, coordy1, 0.0f));
				thisShader.use();
				unsigned int transformLoc6 = glGetUniformLocation(thisShader.ID, "newShader");
				glUniformMatrix4fv(transformLoc6, 1, GL_FALSE, glm::value_ptr(transform6));
				glBindVertexArray(VAO[5]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
		#pragma endregion

		#pragma region Enemy6
				glm::mat4 transform7 = glm::mat4(1.0f);
				transform7 = glm::translate(transform7, glm::vec3(coordx1, coordy1, 0.0f));
				thisShader.use();
				unsigned int transformLoc7 = glGetUniformLocation(thisShader.ID, "newShader");
				glUniformMatrix4fv(transformLoc7, 1, GL_FALSE, glm::value_ptr(transform7));
				glBindVertexArray(VAO[6]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
		#pragma endregion
				if (coordx1 == -0.5) {
					left = false;
				}
				if (coordx1 == 0.5) {
					left = true;
				}
		//moveEnemy();
				
#pragma endregion

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

	glDeleteVertexArrays(7, VAO);
	glDeleteBuffers(7, VBO);

	glfwTerminate();
	return 0;
}

#pragma region Imp. Funções
void moveEnemy() 
{
	if (left) {
		subCoordX(&coordx1);
		return;
	}
	else{
		addCoordX(&coordx1);
	}	
}



void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		jogador.subCoordX();
	}
		
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		jogador.addCoordX();
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//jogador.addCoordY();
		addCoordX(&coordx1);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		subCoordX(&coordx1);
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

void printCoordinates(float p_coordx, float p_coordy)
{
	//system("CLS");
	std::cout << "(";
	std::cout << p_coordx;
	std::cout << " , ";
	std::cout << p_coordy;
	std::cout << ")";
	std::cout << std::endl;
}


void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state	
	shader.use();
	glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO[8]);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

#pragma endregion



