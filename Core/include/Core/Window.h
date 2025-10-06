//
// Created by Janam Shrestha on 10/2/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <functional>
#include "Events/Event.h"

namespace Core {
    struct WindowSpecification {
        std::string Title;
        uint32_t Width = 1280;
        uint32_t Height = 720;
        bool IsResizable = true;
        bool VSync = true;
    };
    class Window {
    public :
        Window(const WindowSpecification& spec = WindowSpecification());
        ~Window();

        void Create();
        void SetUpCallbacks();
        void Destroy();
        void Update();
        glm::vec2  GetFramebufferSize();
        bool ShouldClose() const;


        GLFWwindow* GetHandle() const {return m_Handle;}

        using EventCallBackFn = std::function<void(Event&)>;
        void SetEventCallback(const EventCallBackFn& callback){m_EventCallback = callback;}

    private:
        WindowSpecification m_WindowSpec;
        GLFWwindow* m_Handle;
        EventCallBackFn m_EventCallback;
    };



}

#endif //WINDOW_H
