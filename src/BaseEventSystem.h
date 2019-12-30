#ifndef BASE_EVENT_SYSTEM_H_
#define BASE_EVENT_SYSTEM_H_

#include <vector>
#include "EventHandler.h"
#include "Event.h"

#define FRAMES_PER_SEC 60

class BaseEventSystem
{
public:
    enum cameraEvents {
        ON_START = 0,
        PER_FRAME,
        ON_CLOSE,
        ON_CAPTURE,
        ON_MODE_SWITCH
    };

    void subscribeToEvent(EventHandler* handler);
    void executeEvent(int eventType);
    void baseControlFlow();

private:
    int shutdown = 0;

    // Events are in same order as enum
    Event events[5]; // Keep track Of this whenever adding to enum.
};
#endif
