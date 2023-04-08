#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#include "ultrasonic.cpp"

int main(void){
  if(wiringPiSetup()==-1){
    printf("setup wiringPi failed!\n");
    printf("please check your setup\n");
    return -1;
  }
  Ultrasonic u = Ultrasonic();
  int d = u.getDistance();
  printf("Main the distance is %d cm",d);
  return 0;
}