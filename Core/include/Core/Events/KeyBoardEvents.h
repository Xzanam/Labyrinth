//
// Created by Janam Shrestha on 10/6/25.
//

#ifndef KEYBOARDEVENTS_H
#define KEYBOARDEVENTS_H

#include "Event.h"

namespace Core {

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

