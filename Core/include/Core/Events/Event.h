//
// Created by Janam Shrestha on 10/2/25.
//

#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <typeinfo>

namespace Core {
        enum class EventType {
                None = 0,
                WindowClose,
                WindowResize,
                WindowFocus,
                WindowLostFocus,
                WindowMoved,
                KeyPressed, KeyReleased, KeyTyped,
                MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
        };

        enum EventCategory {
                None = 0,
                EventCategoryApplication = 1 << 0,
                EventCategoryInput = 1 << 1,
                EventCategoryKeyboard = 1 << 2,
                EventCategoryMouse = 1 << 3,
                EventCategoryMouseButton = 1 << 4,
        };
        class Event {
        public:
                virtual ~Event() = default;
                virtual EventType GetEventType() const = 0;
                virtual const char* GetName() const = 0;
                virtual int GetCategoryFlags() const = 0;
                virtual std::string ToString() const { return GetName(); }

                bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

                bool Handled = false;
        };

        class EventDispatcher {
        public :
                EventDispatcher(Event& event) : m_Event(event){ }


                template<typename T, typename F>
                bool Dispatch(const F& func) {
                if (m_Event.GetEventType() == T::GetStaticType()) {
                        m_Event.Handled = func(static_cast<T&>(m_Event));
                        return true;
                }
                return false;
                }
        private:
                Event& m_Event;
        };

        template<typename Derived, EventType Type, int CategoryFlags>
        class EventBase: public Event {
        public :
                static constexpr EventType StaticType = Type;
                static constexpr EventType GetStaticType() { return StaticType;}
                EventType GetEventType() const override{ return StaticType ;}
                const char* GetName() const override { return typeid(Derived).name(); }
                int GetCategoryFlags() const override { return CategoryFlags;}
        };


}

#endif //EVENT_H
