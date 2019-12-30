#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <functional>

class EventHandler
{
public:
    EventHandler(std::function<void()> func, int handlerType);

    int getType() const { return type; }
    std::function<void()> getResponse() const { return response; }

private:
    int type;
    std::function<void()> response;
};
#endif
