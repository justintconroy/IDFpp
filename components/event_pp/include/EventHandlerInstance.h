#ifndef EVENT_HANDLER_INSTANCE_H
#define EVENT_HANDLER_INSTANCE_H
#include <functional>
#include <string>
#include <esp_event.h>

namespace KC
{
template<class EventData>
class EventHandlerInstance {
public:
  EventHandlerInstance(
    esp_event_loop_handle_t eventLoop,
    std::string eventBase,
    int32_t eventId,
    std::function<void(esp_event_base_t, int, EventData*)> cb);

  EventHandlerInstance(
    std::string eventBase,
    int32_t eventId,
    std::function<void(esp_event_base_t, int, EventData*)> cb);

  ~EventHandlerInstance();

private:
  esp_event_loop_handle_t _eventLoopHandle = nullptr;
  esp_event_handler_instance_t _instanceHandle;

  std::string _eventBase;
  int32_t _eventId;
  std::function<void(esp_event_base_t, int, EventData*)> _cb;

  static void _cbHandler(void* arg,
                         esp_event_base_t event_base,
                         int event_id,
                         void* event_data);
};
} // namespace KC
#endif // EVENT_HANDLER_INSTANCE_H