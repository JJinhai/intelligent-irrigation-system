#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "motor.cpp"
#include "servo.cpp"
#include "ultrasonic.cpp"

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

void run_motor(Motor motor,int L,int M,int R){
  if ((L < 30 && M < 30 && R <30) || (L > 30 && M < 30 && R > 30)){
    motor.MotorGo(-1450,-1450,-1450,-1450);
    delay(0.1);
    if(L < R){
      motor.MotorGo(1450,1450,-1450,-1450);
    }else{
      motor.MotorGo(-1450,-1450,1450,1450);
    }
  }else if(L < 30 && M < 30){
    motor.MotorGo(1500,1500,-1500,-1500);
  }else if( R < 30 && M < 30){
    motor.MotorGo(-1500,-1500,1500,1500);
  }else if( L < 20 ){
    motor.MotorGo(2000,2000,-500,-500);
    if(L < 10){
      motor.MotorGo(1500,1500,-1000,-1000);
    }
  }else if(R < 20){
    motor.MotorGo(-500,-500,2000,2000);
    if(R < 10){
      motor.MotorGo(-1500,-1500,1500,1500);
    }
  }else {
    motor.MotorGo(600,600,600,600);
  }
};

int main(void){
  if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
  }
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
  Motor motor=Motor(fd);
  Servo servo=Servo(fd);
  Ultrasonic u = Ultrasonic();
  int L = 300,M = 300,R = 300;
  int t0 = time(0);
  while(time(0)-t0 < 60){     
    for(int i = 30 ; i < 151 ; i = i+60){
      servo.setServo(0,i);
      delay(1000);
      if(i==30){
        L = u.getDistance();
      }else if(i==90){
        M = u.getDistance();
      }else{
        R = u.getDistance();
      }
    }
    servo.setServo(0,90);
    run_motor(motor,L,M,R);
  }
  return 0;
}

    
    