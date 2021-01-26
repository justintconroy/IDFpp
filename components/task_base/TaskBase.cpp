/* Adapted from
   https://ppdevlog.wordpress.com/2018/11/12/using-c-with-freertos-on-stm32/
*/
#include "TaskBase.h"

void TaskBase::start(const char *name,
                     const uint32_t stackDepth,
                     UBaseType_t priority)
{
  this->stopCalled = false;
  xTaskCreate(TaskBase::bootstrap, name, stackDepth, this, priority, &this->handle);
}
void TaskBase::stop()
{
  this->stopCalled = true;
}

void TaskBase::bootstrap(void *pvParameters)
{
  TaskBase *taskObject = reinterpret_cast<TaskBase *>(pvParameters);

  taskObject->setup();

  while (!taskObject->stopCalled)
  {
    taskObject->loop();
  }

  taskObject->cleanup();
  vTaskDelete(taskObject->handle);
}
