#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "motor.cpp"
#include "servo.cpp"
#include "ultrasonic.cpp"
#include "light.cpp"
#include "Infrared.cpp"
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


  Infrared inf = Infrared();
  Light l1 = Light();
	int t0=time(0);
  bool isRun = true;
  int triggle = false;

  Guidance guidance1 = Guidance(fd);
  bool checkEnv(){ //   std::thread loopThread = std::thread([this]() {})
    isRun = true;
    while(isRun){ // && time(0) - t0 < 30
      float infrared_value = inf.getFrontValue();
      cout<<"front infrared: "<<infrared_value<<"--";
      float infrared_value_back = inf.getBackValue();
      cout<<"back infrared: "<<infrared_value_back<<"--";
      float light_left = l1.getLeftValue();
      cout<<"light_left: "<<light_left<<"--";
      float light_right = l1.getRightValue();
      cout<<"light_right: "<<light_right<<endl;
      if(infrared_value == LOW || infrared_value_back == LOW || light_left > 2000 || light_right > 2000){
        triggle += 1;
      }
      if(triggle >= 3){
        isRun = false
        return true;
      }
	  }
  }
  guidance1.go_to_garden();
  while(1){
    triggle = checkEnv();
    if(triggle){
      guidance1.back_home();
      triggle = false;
      delay(10000);
      guidance1.go_to_garden();
    }
  }

  return 0;
}

    
    