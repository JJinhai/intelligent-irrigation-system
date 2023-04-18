#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#include "irrigation.cpp"

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50
int main(int argc, char* argv[]){
  if(wiringPiSetup()==-1){
    printf("setup wiringPi failed!\n");
    printf("please check your setup\n");
    return -1;
  }
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
  Irrigation ir = Irrigation();
  ir.start();
  delay(10000);
  ir.end();
  return 0;
}
