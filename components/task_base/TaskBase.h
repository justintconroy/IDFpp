/* Adapted from
   https://ppdevlog.wordpress.com/2018/11/12/using-c-with-freertos-on-stm32/
*/
#ifndef TASK_BASE_H
#define TASK_BASE_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class TaskBase
{
public:
  void start(const char *pcName,
             const uint32_t stackDepth,
             UBaseType_t priority);
  void Stop();

private:
  virtual void setup() = 0;
  virtual void loop() = 0;
  virtual void cleanup() = 0;
  static void bootstrap(void *pvParameters);

  bool stopCalled = false;
  TaskHandle_t handle = 0;
};

#endif // TASK_BASE_H
