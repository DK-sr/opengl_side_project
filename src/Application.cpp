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
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    window = glfwCreateWindow(960, 540, "GL STUDY", NULL, NULL);
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
         100.0f, 100.0f, 0.0f, 0.0f,// 0
         100.0f, 200.0f, 1.0f, 0.0f,// 1
         200.0f, 200.0f, 1.0f, 1.0f,// 2
         200.0f, 100.0f, 0.0f, 1.0f // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::unique_ptr<VertexArray> va = std::make_unique<VertexArray>();
    std::unique_ptr<VertexBuffer> vb = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

    std::unique_ptr<VertexBufferLayout> layout = std::make_unique<VertexBufferLayout>();
    layout->Push<float>(2);
    layout->Push<float>(2);
    va->AddBuffer(*vb, *layout);

    std::unique_ptr<IndexBuffer> ib = std::make_unique<IndexBuffer>(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;

    std::unique_ptr<Shader> shader = std::make_unique<Shader>("res/shaders/Basic.glsl");
    shader->Bind();
    shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    shader->SetUniformMat4f("u_MVP", mvp);

    std::unique_ptr<Texture> texture = std::make_unique<Texture>("res/texture/sample.png");
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);

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
        //shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

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
    texture.reset();
    shader.reset();
    glfwTerminate();
    return 0;
}