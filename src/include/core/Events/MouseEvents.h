#ifndef __MOUSEEVENTS_H__
#define __MOUSEEVENTS_H__

#include <core/Events/Events.h>
#include <core/Events/KeyCodes.h>


class MouseMovedEvent : public Event
{
    public:
        MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}
        float GetMouseX() const { return m_MouseX; }
        float GetMouseY() const { return m_MouseY; }
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << "mouse position: x) " << m_MouseX << " y) " << m_MouseY;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CATEGORIES(MouseEvent | InputEvent)

    private:
        float m_MouseX;
        float m_MouseY;
};



class MouseScrolledEvent : public Event
{
    public:
        MouseScrolledEvent(const float xoffset, const float yoffset) : m_xoffset(xoffset), m_yoffset(yoffset) {} 
        float GetXoffset() const { return m_xoffset; }
        float GetYoffset() const { return m_yoffset; }
        std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXoffset() << ", " << GetYoffset();
			return ss.str();
		}
        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CATEGORIES(MouseEvent | InputEvent)

    private:
        float m_xoffset;
        float m_yoffset;
};


class MouseButtonEvent : public Event
{
    public:
        MouseCode GetMouseButton() const { return m_Button; }
        EVENT_CATEGORIES(MouseButtonEventCategory | MouseEvent | InputEvent)
    protected:
        MouseCode m_Button;
        MouseButtonEvent(const MouseCode buttoncode) 
        : m_Button(buttoncode) {}
};


class MouseButtonPressedEvent : public MouseButtonEvent
{
    public:
        MouseButtonPressedEvent(MouseCode button) 
        : MouseButtonEvent(button) {}
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "mouse button: " << m_Button << " pressed";
            return ss.str();
        } 
        EVENT_CLASS_TYPE(MouseButtonPressed)
};


class MouseButtonReleasedEvent : public MouseButtonEvent
{
    public:
        MouseButtonReleasedEvent(const MouseCode button) 
        : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "mouse button: " << m_Button << " released";
            return ss.str();
        } 
        EVENT_CLASS_TYPE(MouseButtonReleased)

};
#endif // __MOUSEEVENTS_H__