#ifndef __APPLICATIONEVENTS_H__
#define __APPLICATIONEVENTS_H__

#include <core/Events/Events.h>


class WindowCloseEvent : public Event
{
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CATEGORIES(ApplicationEvent)
};

class WindowMovedEvent : public Event
{
    public:
        WindowMovedEvent() = default;
        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CATEGORIES(ApplicationEvent)
};

class WindowFocusEvent : public Event
{
    public:
        WindowFocusEvent() = default;
        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CATEGORIES(ApplicationEvent)
};

class WindowLostFocusEvent : public Event
{
    public:
        WindowLostFocusEvent() = default;
        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CATEGORIES(ApplicationEvent)
};


class WindowResizeEvent : public Event
{
    public:
        WindowResizeEvent( uint16_t width, uint16_t height) : m_height(height), m_width(width) {}
        uint16_t GetWidth() const   { return m_width; }
        uint16_t GetHeight() const  { return m_height; }
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << "window resized to " << m_width << "x" << m_height;
            return ss.str();
        }
        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CATEGORIES(ApplicationEvent)

    private:
    uint16_t m_width;
    uint16_t m_height;
    
};
#endif // __APPLICATIONEVENTS_H__