#include "app.h"
#include "util.h"

#include "Motor.h"
#include "Clock.h"

#include <stdio.h>

using namespace ev3api;

static FILE *bt = NULL;

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused) {
  bt = ev3_serial_open_file(EV3_SERIAL_BT);

  Motor leftWheel(PORT_C);
  Motor rightWheel(PORT_B);
  Clock clock;

  const int8_t pwm = (Motor::PWM_MAX) / 6;
  const uint32_t duration = 2000;

  int i=0;
  init_f(__FILE__);
  while(1) {
    fprintf(bt, "debug: %d\n", i++);
    //msg_f("Forwarding...", 1);
    leftWheel.setPWM(pwm);
    rightWheel.setPWM(pwm);
    clock.sleep(duration);
// end::main_task_1[]
// tag::main_task_2[]
    //msg_f("Backwarding...", 1);
    leftWheel.setPWM(-pwm);
    rightWheel.setPWM(-pwm);
    clock.sleep(duration);

    // 左ボタンを長押し、それを捕捉する
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      break;
    }
  }

  msg_f("Stopped.", 1);
  leftWheel.stop();
  rightWheel.stop();
  while(ev3_button_is_pressed(LEFT_BUTTON)) {
    ;
  }

  ext_tsk();
}
// end::main_task_2[]
