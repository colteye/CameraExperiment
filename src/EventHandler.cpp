#include "EventHandler.h"

EventHandler::EventHandler(std::function<void()> func, int handlerType)
{
    type = handlerType;
    response = func;
}


