#include "Event.h"

void Event::addEventHandler(EventHandler* handler)
{
    handlers.push_back(handler);
}

void Event::removeEventHandler(EventHandler* handler)
{
    int i = 0;
    for (EventHandler* h : handlers)
    {
        ++i;
        if (h == handler) break;
    }
    handlers.erase(handlers.begin() + i);
}

void Event::invoke()
{
    for (EventHandler* h : handlers)
    {
        if (h != NULL)
            if (h->getResponse() != NULL) h->getResponse()();
    }
}
