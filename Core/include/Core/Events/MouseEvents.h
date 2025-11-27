//
// Created by Janam Shrestha on 10/7/25.
//

#ifndef MOUSEEVENTS_H
#define MOUSEEVENTS_H
#include "Event.h"

namespace Core {
    class MouseMovedEvent : public EventBase<MouseMovedEvent, EventType::MouseMoved,EventCategoryInput | EventCategoryMouse > {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y){}
        float GetX(){ return m_MouseX;}
        float GetY(){ return m_MouseY;}
    private:
        float m_MouseX;
        float m_MouseY;
    };

};

#endif //MOUSEEVENTS_H
