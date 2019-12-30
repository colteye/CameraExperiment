#ifndef EVENT_H_
#define EVENT_H_

#include <vector>
#include "EventHandler.h"

class Event
{
public:
    void addEventHandler(EventHandler* handler);
    void removeEventHandler(EventHandler* handler);
    void invoke();

private:
    std::vector<EventHandler*> handlers;
};
#endif
