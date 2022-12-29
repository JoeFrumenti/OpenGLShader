#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <OpenGL/Shader.h>
#include <iostream>

GLuint VAO;
GLuint VBO;

float horizontalOffset = 0.0f;
float verticalOffset = 0.0f;


//vertices to make a triangle hopefully
float vertices[] = { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
					  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
					  0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

//Vertex buffer object


//resize window function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//input function
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		horizontalOffset -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		horizontalOffset += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_UP))
		verticalOffset += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		verticalOffset -= 0.01f;


}

int main()
{
	

	//initialize and configure window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	//set window to be the one we are working on
	glfwMakeContextCurrent(window);

	
	//Load GLAD, ensure it's working
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	//int nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes;

	//set GL to work properly and dynamically with the window (stretchy stuff)
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	Shader ourShader("vertexshader.vs", "fragmentshader.fs");
	std::string offvalx = "offsetValueX";
	std::string offvaly = "offsetValueY";


	//set up Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	//Bind all the buffers to the right buffer objects
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//tell opengl how to read the buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//set attribute array to the 0 position
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// unbind buffer (everything has been registered in Vertex Attribute Pointer)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	ourShader.use();

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering commands
		ourShader.setFloat(offvalx, horizontalOffset);
		ourShader.setFloat(offvaly, verticalOffset);

		//background color
		glClearColor(.27f, 0.38f, 0.92f, 1.0f); //set glclearcolor
		glClear(GL_COLOR_BUFFER_BIT);	//apply glclearcolor


		//draw triangle
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate(); //terminate program


	return 0;
}
