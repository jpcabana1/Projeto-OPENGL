#include <glad/glad.h>
#include <glfw3.h>
#include "Config.h"
#include <iostream>

enum class  WindowType
{
	Menu,
	Game,
	Pause,
	GameOver,
	Exit
};

class ClasseJanela
{
private:
	GLFWwindow* window;
	WindowType wSettings = WindowType::Menu;
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

public:
    void IniciarJanela();
	void ProcessarInput();
	
	GLFWwindow* getWindow();
	WindowType getState();
};

void ClasseJanela::IniciarJanela() {
	try
	{
		this->window = glfwCreateWindow(
			SCR_WIDTH, SCR_HEIGHT, 
			"Teste Objeto Janela", 
			NULL,
			NULL
		);
	}
	catch (const std::exception&)
	{
		std::cout << "Erro: Iniciar Janela" << std::endl;
	}    
}

void ClasseJanela::ProcessarInput(){
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		wSettings = WindowType::Exit;
		glfwSetWindowShouldClose(window, true);
	}
}

GLFWwindow* ClasseJanela::getWindow() {
	return window;
}

WindowType ClasseJanela::getState() {
	return wSettings;
}
