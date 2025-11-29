//
// Created by Janam Shrestha on 10/6/25.
//

#ifndef KEYBOARDEVENTS_H
#define KEYBOARDEVENTS_H

#include <GLFW/glfw3.h>
#include "Event.h"


namespace Core {
    enum Keys {
        KEY_ESCAPE  = GLFW_KEY_ESCAPE,
        KEY_A       = GLFW_KEY_A,
        KEY_S       = GLFW_KEY_S,
        KEY_D       = GLFW_KEY_D,
        KEY_W       = GLFW_KEY_W,
        KEY_SPACE   = GLFW_KEY_SPACE,
        KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        KEY_TAB       = GLFW_KEY_TAB,
        KEY_LEFT = GLFW_KEY_LEFT, 
        KEY_RIGHT = GLFW_KEY_RIGHT,
        KEY_UP = GLFW_KEY_UP,
        KEY_DOWN = GLFW_KEY_DOWN,
        KEY_T = GLFW_KEY_T
    };

    class KeyPressedEvent : public EventBase<KeyPressedEvent,EventType::KeyPressed,EventCategoryKeyboard || EventCategoryInput> {
    public:
        KeyPressedEvent(int keyCode, bool repeat = false) : m_KeyCode(keyCode), m_Repeat(repeat){}
        int GetKeyCode() const { return m_KeyCode;}  ;

    private:
        int m_KeyCode;
        bool m_Repeat;
    };

    class KeyReleasedEvent: public EventBase<KeyReleasedEvent, EventType::KeyReleased,EventCategoryInput | EventCategoryKeyboard> {
    public :
        explicit KeyReleasedEvent(int keyCode) : m_KeyCode(keyCode){}
        int GetKeyCode() const { return m_KeyCode;}

    private:
        int m_KeyCode;
    };

}
#endif //KEYBOARDEVENTS_H

