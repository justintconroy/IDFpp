/* Adapted from
   https://ppdevlog.wordpress.com/2018/11/12/using-c-with-freertos-on-stm32/
*/
#include "TaskBase.h"

#include <string>

using namespace std;
using namespace IDF;

void TaskBase::Start(const string name,
                     const uint32_t stackDepth,
                     const UBaseType_t priority)
{
  this->stopCalled = false;
  xTaskCreate(TaskBase::bootstrap,
              name.c_str(),
              stackDepth,
              this,
              priority,
              &this->handle);
}
void TaskBase::Stop()
{
  this->stopCalled = true;
}

void TaskBase::bootstrap(void *pvParameters)
{
  TaskBase *taskObject = reinterpret_cast<TaskBase *>(pvParameters);

  taskObject->setup();

  while (!taskObject->stopCalled) {
    taskObject->loop();
  }

  taskObject->cleanup();
  vTaskDelete(taskObject->handle);
}
