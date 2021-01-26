/* Adapted from
   https://ppdevlog.wordpress.com/2018/11/12/using-c-with-freertos-on-stm32/
*/
#ifndef TASK_BASE_H
#define TASK_BASE_H

#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace IDF
{
  class TaskBase
  {
  public:
    void Start(const std::string pcName,
               const uint32_t stackDepth,
               const UBaseType_t priority);
    void Stop();

  private:
    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual void cleanup() = 0;
    static void bootstrap(void *pvParameters);

    bool stopCalled = false;
    TaskHandle_t handle = 0;
  }; // class TaskBase
} // namespace IDF
#endif // TASK_BASE_H
