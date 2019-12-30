#include "BaseEventSystem.h"

void BaseEventSystem::subscribeToEvent(EventHandler* handler)
{
    events[handler->getType()].addEventHandler(handler);
}

void BaseEventSystem::executeEvent(int eventType)
{
    events[eventType].invoke();
}

void BaseEventSystem::baseControlFlow()
{
    events[ON_START].invoke();

    while (shutdown != 1)
    {
        events[PER_FRAME].invoke();
        //delay(1000/FRAMES_PER_SEC);
    }

    events[ON_CLOSE].invoke();
}
