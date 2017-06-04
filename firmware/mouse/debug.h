#pragma once

#include <Arduino.h>
#include "TaskBase.h"
#include "config.h"

#include "as5145.h"
#include "UserInterface.h"
#include "motor.h"
#include "mpu6500.h"
#include "reflector.h"
#include "WallDetector.h"
#include "SpeedController.h"
#include "MazeSolver.h"

#define EXTERNAL_CONTROLLER_TASK_PRIORITY 1
#define EXTERNAL_CONTROLLER_STACK_SIZE    4096

class ExternalController: TaskBase {
  public:
    ExternalController(): TaskBase("External Controller", EXTERNAL_CONTROLLER_TASK_PRIORITY, EXTERNAL_CONTROLLER_STACK_SIZE) {}
    virtual ~ExternalController() {}
    void init() {
      create_task();
    }
  private:
    virtual void task() {
      portTickType xLastWakeTime;
      xLastWakeTime = xTaskGetTickCount();
      while (1) {
        vTaskDelayUntil(&xLastWakeTime, 10 / portTICK_RATE_MS);
        while (Serial.available()) {
          char c = Serial.read();
          printf("%c\n", c);
          switch (c) {
            case 't':
              bz.play(Buzzer::CONFIRM);
              mpu.calibration();
              wd.calibration();
              break;
          }
        }
      }
    }
};

extern ExternalController ec;

