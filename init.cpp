#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "motor.cpp"

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

int main(void){
  if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
  }
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
  Motor m1 = Motor(fd);
	m1.MotorGo(1000,1000,1000,1000,t*1000);
  motor.stop_car();
  return 0;
}