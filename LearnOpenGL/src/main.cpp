#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <stb_image.h>
#include <learnopengl/filesystem.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLFWwindow* initWindows()
{
	// In the main function we first initialize GLFW with glfwInit,
		// after which we can configure GLFW using glfwWindowHint. 
		glfwInit();

	// The first argument of glfwWindowHint tells us what option we want to configure
	//  The second argument is an integer that sets the value of our option.

	// We set the major and minor version both to 3. We also tell GLFW we want to explicitly use the core-profile. 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Note that on Mac OS X you need to add glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); to your initialization code for it to work
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD before we call any OpenGL function:
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	glViewport(0, 0, 800, 600);

	// the moment a user resizes the window the viewport should be adjusted as well.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

int CreateTexture(char const *filename, int mode)
{
	// load and create a texture 
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return texture;
}

int InitVAO()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// Once your vertex coordinates have been processed in the vertex shader,
	// they should be in normalized device coordinates (NDC),
	// which is a small space where the x, y and z values vary from -1.0 to 1.0. 
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // generate one with a buffer ID (first argument is size, second is id)
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first
	// from this point on we should bind/configure the corresponding VBO(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // buffer type of a vertex buffer object is GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copies the previously defined vertex data into the buffer's memory:

	// copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object 
	// so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. 
	// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	return VAO;
}

int main()
{
	
	GLFWwindow* window = initWindows();
	if (window == NULL)
		return -1;

	Shader shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");

	int VAO = InitVAO();
	if (VAO == -1)
		return -1;

	int texture0 = CreateTexture("resources/textures/container.jpg", GL_RGB);
	int texture1 = CreateTexture("resources/textures/window.png", GL_RGBA);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// rendering commands here
		// the glClearColor function is a state-setting function and glClear is a state-using function 
		// uses the current state to retrieve the clearing color from.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		shader.use();

		// either set it manually like so:
		//glUniform1i(glGetUniformLocation(shader.ID, "texture0"), 0);
		//glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 1);

		shader.setInt("texture0", 0); // or with shader class
		shader.setInt("texture1", 1); // or with shader class
		shader.setVec4("baseColor", 0.0f, 0.0f, 0.1f, 0.0f);

		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// seeing as we only have a single VAO there's no need to bind it every time,
		// but we'll do so to keep things a bit more organized
		glBindVertexArray(VAO); 

		// glDrawElements(mode, number of elements, type of the indices, indices pointer)
		// ps: leave last argument null if element buffer have binded.
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		// glBindVertexArray(0); // no need to unbind it every time 

		// Double buffer
		// The front buffer contains the final output image that is shown at the screen, 
		// while all the rendering commands draw to the back buffer.
		// As soon as all the rendering commands are finished we swap the back buffer to the front buffer,
		// so the image is instantly displayed to the user
		glfwSwapBuffers(window);

		//The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events), 
		//updates the window state, and calls the corresponding functions (which we can set via callback methods). 
		glfwPollEvents();
	}

	// As soon as we exit the render loop we would like to properly clean/delete all resources that were allocated. 
	glfwTerminate();

	return 0;
}