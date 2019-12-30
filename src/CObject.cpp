#include "CObject.h"

CObject::CObject()
{
    handlers.push_back(new EventHandler(std::bind(&CObject::onStart, this),  BaseEventSystem::cameraEvents::ON_START));
    handlers.push_back(new EventHandler(std::bind(&CObject::perFrame, this),  BaseEventSystem::cameraEvents::PER_FRAME));
    handlers.push_back(new EventHandler(std::bind(&CObject::onClose, this), BaseEventSystem::cameraEvents::ON_CLOSE));
    handlers.push_back(new EventHandler(std::bind(&CObject::onCapture, this),  BaseEventSystem::cameraEvents::ON_CAPTURE));
    handlers.push_back(new EventHandler(std::bind(&CObject::onModeSwitch, this), BaseEventSystem::cameraEvents::ON_MODE_SWITCH));
}

void CObject::onStart() { }
void CObject::perFrame() { }
void CObject::onClose() { }
void CObject::onCapture() { }
void CObject::onModeSwitch() { }

void CObject::registerObject(BaseEventSystem *system)
{
    baseSystem = system;
    for (EventHandler* h : handlers)
    {
        system->subscribeToEvent(h);
    }
}
