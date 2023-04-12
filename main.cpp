#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "light.cpp"
#include "Infrared.cpp"
#include "guidance.cpp"

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50


bool checkEnv(float infrared_value,float infrared_value_back,float light_left inf,float light_right){ //   std::thread loopThread = std::thread([this]() {})
  bool isRun = true;
  int count = 0;
  while(isRun){ // && time(0) - t0 < 30
    // float infrared_value = inf.getFrontValue();
    cout<<"front infrared: "<<infrared_value<<"--";
    // float infrared_value_back = inf.getBackValue();
    cout<<"back infrared: "<<infrared_value_back<<"--";
    // float light_left = l1.getLeftValue();
    cout<<"light_left: "<<light_left<<"--";
    // float light_right = l1.getRightValue();
    cout<<"light_right: "<<light_right<<endl;
    if(infrared_value == LOW || infrared_value_back == LOW || light_left > 2000 || light_right > 2000){
      count += 1;
    }
    if(count >= 3){
      isRun = false;
      return true;
    }
  }
};

int main(void){
  if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
  }
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);


  Infrared inf = Infrared();
  Light l1 = Light();
  bool triggle = false;
  Guidance guidance1 = Guidance(fd);

  guidance1.go_to_garden();
  while(1){
    float infrared_value = inf.getFrontValue();
    float infrared_value_back = inf.getBackValue();
    float light_left = l1.getLeftValue();
    float light_right = l1.getRightValue();
    triggle = checkEnv(infrared_value,infrared_value_back,light_left,light_right);
    if(triggle){
      guidance1.back_home();
      triggle = false;
      delay(10000);
      guidance1.go_to_garden();
    }
  }

  return 0;
}

    
    