//
// Created by Janam Shrestha on 10/2/25.
//

#include <glad/gl.h>
#include "Core/Window.h"


#include <iostream>
#include <bits/ostream.tcc>

#include "KeyBoardEvents.h"
#include "MouseEvents.h"


namespace Core {
    Window::Window(const WindowSpecification& specification) :
    m_WindowSpec(specification)
    {
    }

    Window::~Window() {
        Destroy();
    }

    void Window::Create() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE);

        m_Handle = glfwCreateWindow(m_WindowSpec.Width, m_WindowSpec.Height, m_WindowSpec.Title.c_str(),nullptr,nullptr);
        if (!m_Handle) {
            std::cerr << "Failed to create GLFW window." << std::endl;
            assert(false);
        }
        glfwMakeContextCurrent(m_Handle);
        glfwSetWindowUserPointer(m_Handle,this);
        SetUpCallbacks();
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(m_WindowSpec.VSync ? 1 : 0);
    }

    void Window::Destroy() {
        if (m_Handle) {
            glfwDestroyWindow(m_Handle);
        }
        m_Handle = nullptr;
    }

    void Window::Update() {
        glfwSwapBuffers(m_Handle);
    }

    glm::vec2 Window::GetFramebufferSize() {
        int width, height;
        glfwGetFramebufferSize(m_Handle, &width, &height);
        return {width, height};
    }

    bool Window::ShouldClose() const{
        return glfwWindowShouldClose(m_Handle) != 0;
    }

    void Window::SetUpCallbacks() {

        glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (!win->m_EventCallback) { return;}
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, false);
                    win->m_EventCallback(event);
                    break;
                }
                case GLFW_REPEAT : {
                    KeyPressedEvent event(key, true);
                    win->m_EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    win->m_EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xpos, double ypos) {
            auto *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (!win -> m_EventCallback) { return; }
            MouseMovedEvent event((float) xpos, (float) ypos);
            win->m_EventCallback(event);
        });

        glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) {
            auto *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (!win -> m_EventCallback) { return; }
            glViewport(0, 0, width, height);
            std::cout<<"Window Resized to - Width: " << width<<" | Height: " << height<<std::endl;
        });

    }



}
