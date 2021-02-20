#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H
#include "EventHandlerInstance.h"

#include <memory>
#include <string>
#include <vector>
#include <esp_event.h>

namespace KC
{
class EventLoop {
public:
  EventLoop();
  EventLoop(std::string taskName,
            int32_t queueSize      = 10, // CONFIG_DEFAULT_QUEUE_SIZE
            uint32_t stackSize     = CONFIG_DEFAULT_TASK_STACK_DEPTH,
            UBaseType_t priority   = CONFIG_DEFAULT_TASK_PRIORITY,
            UBaseType_t taskCoreId = 0);
  ~EventLoop();

  template<class EventData>
  std::shared_ptr<EventHandlerInstance<EventData>> RegisterHandler(
    std::string eventBase,
    int32_t event_id,
    esp_event_handler_t eventHandler,
    std::shared_ptr<void> eventHandlerArg);

  template<class EventData>
  void UnregisterHandler(std::shared_ptr<EventHandlerInstance<EventData>>);

private:
  std::string _taskName;
  bool isDefault = false;
  int32_t _queueSize;
  uint32_t _taskStackSize;
  UBaseType_t _taskPriority;
  BaseType_t _taskCoreId;

  std::vector<esp_event_handler_instance_t> _handlerInstances;
};
} // namespace KC
#endif // EVENT_LOOP_H
