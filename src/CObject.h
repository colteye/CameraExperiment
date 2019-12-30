#ifndef COBJECT_H_
#define COBJECT_H_

#include "EventHandler.h"
#include "BaseEventSystem.h"

class CObject
{
public:
    CObject();
    void registerObject(BaseEventSystem *system);

protected:
    BaseEventSystem *baseSystem;
    std::vector<EventHandler*> handlers;

    virtual void onStart();
    virtual void perFrame();
    virtual void onClose();
    virtual void onCapture();
    virtual void onModeSwitch();
};

#endif
