#ifndef BASE_EVENT_SYSTEM_H_
#define BASE_EVENT_SYSTEM_H_

#include <vector>
#include <QObject>
#include "EventHandler.h"
#include "Event.h"

class BaseEventSystem : public QObject
{
public:
    enum cameraEvents : int {
        ON_START = 0,
        PER_FRAME,
        ON_CLOSE,
        ON_CAPTURE,
        ON_MODE_SWITCH
    };

    BaseEventSystem();
    void subscribeToEvent(EventHandler* handler);
    void executeEvent(int eventType);
    void startEvent();
    void updateEvent();

private:
    // Events are in same order as enum
    Event events[5]; // Keep track Of this whenever adding to enum.
};
#endif
