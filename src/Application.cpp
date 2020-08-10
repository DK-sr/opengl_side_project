#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "GL STUDY", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::unique_ptr<VertexArray> va = std::make_unique<VertexArray>();
    std::unique_ptr<VertexBuffer> vb = std::make_unique<VertexBuffer>(positions, 4 * 2 * sizeof(float));

    std::unique_ptr<VertexBufferLayout> layout = std::make_unique<VertexBufferLayout>();
    layout->Push<float>(2);
    va->AddBuffer(*vb, *layout);

    std::unique_ptr<IndexBuffer>  ib = std::make_unique<IndexBuffer>(indices, 6);

    std::unique_ptr <Shader> shader = std::make_unique<Shader>("res/shaders/Basic.glsl");
    shader->Bind();
    shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    //Unbind shader, index buffer and array buffer
    va->Unbind();
    vb->Unbind();
    ib->Unbind();
    shader->Unbind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        shader->Bind();
        shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.Draw(*va, *ib, *shader);

        if (r > 1.0f) {
            increment = -0.05f;
        }
        else if (r < 0.0f) {
            increment = 0.05f;
        }
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    vb.reset();
    ib.reset();
    layout.reset();
    va.reset();
    shader.reset();
    glfwTerminate();
    return 0;
}