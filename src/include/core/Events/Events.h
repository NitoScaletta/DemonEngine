#ifndef __EVENTS_H__
#define __EVENTS_H__
#include<iostream>
#include <functional>

#define EVENT_CLASS_TYPE(type)      static EventType GetStaticType() { return EventType::type; }\
                                    virtual EventType GetEventType() const override { return GetStaticType(); }\
                                    virtual const char* GetName() const override { return #type; }
#define EVENT_CATEGORIES(category)  virtual int GetCategories() const override { return category; }


enum EventType
{
    WindowClose, WindowFocus, WindowLostFocus, WindowResize, WindowMoved,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    None = 0,
    ApplicationEvent =                  (1 << 0),
    InputEvent =                        (1 << 1),
    KeyboardEvent =                     (1 << 2),
    MouseEvent =                        (1 << 3),
    MouseButtonEventCategory =          (1 << 4)
};

class Event{
    public:
        virtual ~Event() = default;
        bool isHandled =  false;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const  = 0;
        virtual int GetCategories() const = 0;
        virtual std::string toString() const { return GetName(); }
        bool IsInCategory(EventCategory category)   { return GetCategories() & category; }
};

class EventDispatcher
{
    template<typename T>
    using EventFun = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& e) : m_Event(e) {}

        template<typename T>
        bool Dispatch(EventFun<T> func)
        {
            if(m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.isHandled = func(*(static_cast<T*>(&m_Event)));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;

};




#endif // __EVENTS_H__