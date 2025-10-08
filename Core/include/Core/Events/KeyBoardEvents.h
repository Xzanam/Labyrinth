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

