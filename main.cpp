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
  while(time(0) - t0 < 30 ){
		float infrared_value = inf.getValue();
		cout<<"front infrared: "<<infrared_value<<"--";
    float infrared_value_back = inf.getBackValue();
		cout<<"back infrared: "<<infrared_value_back<<"--";
    float light_left = l1.getLeftValue();
    cout<<"light_left: "<<light_left<<"--";
    float light_right = l1.getRightValue();
    cout<<"light_right: "<<light_right<<endl;
	}
  // Guidance guidance1 = Guidance(fd);
  // guidance1.go_to_garden();
  // delay(5000);
  // guidance1.back_home();

  
  return 0;
}

    
    