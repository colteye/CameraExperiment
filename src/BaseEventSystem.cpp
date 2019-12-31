#include "BaseEventSystem.h"
#include <QTimer>

#define FRAMES_PER_SEC 60

BaseEventSystem::BaseEventSystem()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&BaseEventSystem::updateEvent));
    timer->start((int)(1000/FRAMES_PER_SEC));
}

void BaseEventSystem::subscribeToEvent(EventHandler* handler)
{
    events[handler->getType()].addEventHandler(handler);
}

void BaseEventSystem::executeEvent(int eventType)
{
    events[eventType].invoke();
}

void BaseEventSystem::startEvent()
{
    executeEvent(ON_START);
    puts("starting");
}

void BaseEventSystem::updateEvent()
{
    executeEvent(PER_FRAME);
}
