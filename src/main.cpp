#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

//    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//    float currentFrame = glfwGetTime();
//    deltaTime = currentFrame - lastFrame;
//    lastFrame = currentFrame;
//
//    float cameraSpeed = 2.5f * deltaTime;
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

GLFWwindow* initWindows()
{
    // In the main function we first initialize GLFW with glfwInit,
    // after which we can configure GLFW using glfwWindowHint.
    glfwInit();

    // The first argument of glfwWindowHint tells us what option we want to configure
    //  The second argument is an integer that sets the value of our option.

    // We set the major and minor version both to 3. We also tell GLFW we want to explicitly use the core-profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Note that on Mac OS X you need to add glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); to your initialization code for it to work
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

int main() {
    std::cout << "Hello, World!" << std::endl;
    GLFWwindow* window = initWindows();
    if (window == NULL)
        return -1;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        // rendering commands here
        // the glClearColor function is a state-setting function and glClear is a state-using function
        // uses the current state to retrieve the clearing color from.
        glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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

    return 0;
}
