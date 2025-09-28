#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string get_file_contents(const char* filename);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	//std::cout << "Hi mom" << std::endl;



	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif  



	//init the glfw window object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	//register resize function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	// glad: load all OpenGL function pointers
    // ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}



	//first two params set the location of the bottom left corner of the window
	glViewport(0, 0, 800, 600);



	//very simple render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//set background color		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/////////////////////////////////
		///* rendering commands here *///
		/////////////////////////////////

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// function for loading in shader files, did not feel like writing this every time
// ------------------------------------
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::cout << "ERROR? Make sure you typed the shader file namer correctly..." << std::endl;
	throw(errno);
}
