// LearnOpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void render();
const char* getVertexShader();
const char* getFragmentShader();
void setupShaders();
int setupGLFW();
void shutdown();

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLFWwindow* window;
unsigned int shaderProgram;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int VAO;
unsigned int VBO;

int main()
{
    std::cout << "Hello World!\n";

    int result = setupGLFW();

    if (result < 0)
    {
        exit(1);
    }

    setupShaders();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // rendering code goes here
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shutdown();

    return 0;
}

void shutdown()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwTerminate();
}

int setupGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return 0;
}

void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void setupShaders()
{
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char* vShaderSource = getVertexShader();

    glShaderSource(vertexShader, 1, &vShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* fShaderSource = getFragmentShader();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

const char *getVertexShader()
{
    return 
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
}

const char *getFragmentShader()
{
    return "#version 330 core\n"
        "out vec4 FragColor; \n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
        "}\0";
}