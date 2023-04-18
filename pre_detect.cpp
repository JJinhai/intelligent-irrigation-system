#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "light.cpp"
#include "Infrared.cpp"
#include "pre_guidance.cpp"
#include "buzzer.cpp"

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
  bool triggle = false;
  Guidance guidance1 = Guidance(fd);

  bool triggle_light = true;
  while(triggle_light){
    float light_left = l1.getLeftValue();
    cout<<"light_left: "<<light_left<<"--";
    float light_right = l1.getRightValue();
    cout<<"light_right: "<<light_right<<endl;
    if(light_left > 3000 || light_right > 3000){
      guidance1.go_to_garden();
      std::cout << "go to garden"<<endl;
      triggle_light = false;
    }
  }
  bool isRun = true;

  int count = 0;
  std::cout << "getFrontValue"<<std::endl;
  while(!triggle){ // && time(0) - t0 < 30
    delay(1000);
    std::cout << "while triggle"<<std::endl;
    float infrared_value = inf.getFrontValue();
    cout<<"front infrared: "<<infrared_value<<"--";
    float infrared_value_back = inf.getBackValue();
    cout<<"back infrared: "<<infrared_value_back<<"--";

    if(infrared_value == LOW || infrared_value_back == LOW ){
      count += 1;
    }
    if(count >= 3){
      isRun = false;
      triggle = true;
      count = 0;
    }
  }
  if(triggle){
    std::cout << "back home"<<std::endl;
    Buzzer buzzer = Buzzer();
    buzzer.run();
    guidance1.back_home();
    triggle = false;
  }
  return 0;
}

    
    