#ifndef __KEYEVENTS_H__
#define __KEYEVENTS_H__

#include <core/Events/Events.h>
#include <core/Events/KeyCodes.h>




class KeyEvent : public Event
{
    public: 
        KeyCode GetKeyCode() const { return m_KeyCode; }
        EVENT_CATEGORIES(InputEvent | KeyboardEvent)

    protected:
        KeyCode m_KeyCode;
        KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}
};


class KeyPressedEvent : public KeyEvent
{
    public:
        KeyPressedEvent(const KeyCode keycode, const uint16_t repeatcount)     
        :  KeyEvent(keycode),  RepeatCount(repeatcount) {} 
        uint16_t GetRepeatCount() const { return RepeatCount; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyCode: " << m_KeyCode << "pressed ---> repeated " << RepeatCount << " times";
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyPressed)

    private:
        uint16_t RepeatCount;
};


class KeyReleasedEvent : public KeyEvent
{
    public:
        KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}
        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyCode: " << m_KeyCode << " released ";
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyReleased)
};


class KeyTypedEvent : public KeyEvent
{
    KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}
    std::string toString() const override {
        std::stringstream ss;
        ss << "Keycode: " << m_KeyCode << " typed";
        return ss.str();
    }
    EVENT_CLASS_TYPE(KeyTyped)
};



#endif // __KEYEVENTS_H__