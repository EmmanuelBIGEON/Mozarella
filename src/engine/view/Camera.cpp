#include "Camera.h"

void Camera::Update(Event& event)
{
    if(event.GetEventType() == EventType::EVENT_MOUSE)
    {
        MouseEvent* mouseEvent = (MouseEvent*)&event;
        if(mouseEvent->GetMouseEventType() == EventMouseType::EVENT_MOUSE_MOVED)
        {
            MouseMovedEvent* mouseMoveEvent = (MouseMovedEvent*)&event;
            
            if (_firstMouse)
            {
                _lastX = mouseMoveEvent->posX;
                _lastY = mouseMoveEvent->posY;
                _firstMouse = false;
            }
            
            float xoffset = mouseMoveEvent->posX - _lastX;
            float yoffset = _lastY - mouseMoveEvent->posY; // reversed since y-coordinates go from bottom to top

            _lastX = mouseMoveEvent->posX;
            _lastY = mouseMoveEvent->posY;

            ProcessMouseMovement(xoffset, yoffset);
        }
    }
    if(event.GetEventType() == EventType::EVENT_KEY)
    {
        KeyEvent* keyEvent = (KeyEvent*)&event;
        if(keyEvent->GetKeyType() == EventKeyType::EVENT_KEY_PRESSED)
        {
            KeyPressedEvent* keyPressedEvent = (KeyPressedEvent*)&event;
            if (keyPressedEvent->key == Key_Z)
                ProcessKeyboard(FORWARD, Window::activeWindow->frameDeltaTime);
            else if (keyPressedEvent->key == Key_S)
                ProcessKeyboard(BACKWARD, Window::activeWindow->frameDeltaTime);
            else if (keyPressedEvent->key == Key_Q)
                ProcessKeyboard(LEFT, Window::activeWindow->frameDeltaTime);
            else if (keyPressedEvent->key == Key_D)
                ProcessKeyboard(RIGHT, Window::activeWindow->frameDeltaTime);
            else if (keyPressedEvent->key == Key_Ctrl)
                ProcessKeyboard(DOWN, Window::activeWindow->frameDeltaTime);
            else if (keyPressedEvent->key == Key_Space)
                ProcessKeyboard(UP, Window::activeWindow->frameDeltaTime);
        }else if(keyEvent->GetKeyType() == EventKeyType::EVENT_KEY_REPEATED)
        {
            KeyRepeatedEvent* keyRepeatedEvent = (KeyRepeatedEvent*)&event;
            if (keyRepeatedEvent->key == Key_Z)
                ProcessKeyboard(FORWARD, Window::activeWindow->frameDeltaTime);
            else if (keyRepeatedEvent->key == Key_S)
                ProcessKeyboard(BACKWARD, Window::activeWindow->frameDeltaTime);
            else if (keyRepeatedEvent->key == Key_Q)
                ProcessKeyboard(LEFT, Window::activeWindow->frameDeltaTime);
            else if (keyRepeatedEvent->key == Key_D)
                ProcessKeyboard(RIGHT, Window::activeWindow->frameDeltaTime);
            else if (keyRepeatedEvent->key == Key_Ctrl)
                ProcessKeyboard(DOWN, Window::activeWindow->frameDeltaTime);
            else if (keyRepeatedEvent->key == Key_Space)
                ProcessKeyboard(UP, Window::activeWindow->frameDeltaTime);
        }
    }
}

