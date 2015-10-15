#ifndef _PWM_H
#define	_PWM_H

#include <stdint.h>

#define MAX_OPE 124
#define DEAD_TIME 100

void pwm_reg();
void stop();
void keep();
void right();
void left();
void speed(uint8_t ration);

#endif  //_PWM_H

