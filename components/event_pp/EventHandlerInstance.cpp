#include "EventHandlerInstance.h"

#include <functional>
#include <string>
#include <esp_event.h>

using namespace KC;
using namespace std;

template<class EventData>
EventHandlerInstance<EventData>::EventHandlerInstance(
  esp_event_loop_handle_t eventLoop,
  string eventBase,
  int32_t eventId,
  function<void(esp_event_base_t, int, EventData*)> cb)
  : _eventLoopHandle{eventLoop},
    _eventBase{eventBase},
    _eventId{eventId},
    _cb{cb}
{
  esp_event_handler_instance_register_with(
    eventLoop, eventBase.c_str(), eventId, &_cbHandler, this, _instanceHandle);
}

template<class EventData>
EventHandlerInstance<EventData>::EventHandlerInstance(
  string eventBase,
  int32_t eventId,
  function<void(esp_event_base_t, int, EventData*)> cb)
  : _eventBase{eventBase}, _eventId{eventId}, _cb{cb}
{
  esp_event_handler_instance_register(
    eventBase.c_str(), eventId, &_cbHandler, this, _instanceHandle);
}

template<class EventData>
EventHandlerInstance<EventData>::~EventHandlerInstance()
{
  if (_eventLoopHandle != nullptr) {
    esp_event_handler_instance_unregister_with(
      _eventLoopHandle, _eventBase.c_str(), _eventId, _instanceHandle);
  }
  else {
    // Unregister from the default event loop.
    esp_event_handler_instance_unregister(
      _eventBase.c_str(), _eventId, _instanceHandle);
  }
}

template<class EventData>
void EventHandlerInstance<EventData>::_cbHandler(void* arg,
                                                 esp_event_base_t event_base,
                                                 int event_id,
                                                 void* event_data)
{
  auto obj  = reinterpret_cast<EventHandlerInstance*>(arg);
  auto data = reinterpret_cast<EventData*>(event_data);
  obj->_cb(event_base, data);
}