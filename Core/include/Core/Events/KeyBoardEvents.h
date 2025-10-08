//
// Created by Janam Shrestha on 10/6/25.
//

#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

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

}
#endif //KEYPRESSEDEVENT_H

