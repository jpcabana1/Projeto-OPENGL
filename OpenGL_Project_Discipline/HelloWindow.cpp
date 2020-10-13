//#include <glad/glad.h>
//#include <glfw3.h>
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//void InitGFLW();
//void InsideLoop(GLFWwindow* window);
//bool JanelaIniciou(GLFWwindow* window);
//bool GladIniciou();
//
//int main() {
//	const unsigned int SCR_WIDTH = 800;
//	const unsigned int SCR_HEIGHT = 600;
//    GLFWwindow* window;
//  
//    InitGFLW();
//
//    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL); 
//    if (!JanelaIniciou(window))
//        return -1;
//
//    //Colocar janela instanciada no contexto
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    
//    //Verifica se o GLAD Iniciou
//    if (!GladIniciou())
//        return -1;
//
//    //Render loop
//    while (window != NULL)
//    {
//        InsideLoop(window);
//    }
//
//    glfwTerminate();
//	return 0;
//}
//
//bool GladIniciou() {
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return false;
//    }
//    return true;
//}
//bool JanelaIniciou(GLFWwindow* window) {
//    
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return false;
//    }
//
//    return true;
//}
//void InitGFLW() {
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//}
//void InsideLoop(GLFWwindow* window) {
//    processInput(window);
//
//    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glfwSwapBuffers(window);
//    glfwPollEvents();
//}
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    //if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//    //    glfwSetWindowShouldClose(window, true);
//    //    free(window);
//    //    window = glfwCreateWindow(800, 600, "Nova", NULL, NULL);
//    //    glfwMakeContextCurrent(window);
//    //}
//    //    
//    //if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//    //    glfwSetWindowShouldClose(window, true);
//    //    free(window);
//    //    window = glfwCreateWindow(1600, 900, "Velha", NULL, NULL);
//    //    glfwMakeContextCurrent(window);
//    //}
//
//}
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
