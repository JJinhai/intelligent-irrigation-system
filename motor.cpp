// 参考链接 https://osoyoo.com/2020/11/06/osoyoo-pie-car-v2-0-for-raspberry-pi-lesson-1-basic-framework-and-programming-gpio-pca9685-c-version/
#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

/*
 * wiringPi C library use different GPIO pin number system from BCM pin numberwhich are often used by Python, 
 * you can lookup BCM/wPi/Physical pin relation by following Linux command : gpio readall
 */
#define Motor1_F 1  //right motor speed pin ENB connect to PCA9685 port 1
#define Motor1_B 0  //right motor speed pin ENB connect to PCA9685 port 1
#define Motor2_F 2  //right motor speed pin ENB connect to PCA9685 port 1
#define Motor2_B 3  //right motor speed pin ENB connect to PCA9685 port 1
#define Motor3_F 5  //right motor speed pin ENB connect to PCA9685 port 1
#define Motor3_B 4  //right motor speed pin ENB connect to PCA9685 port 1
#define Motor4_F 7  //right motor speed pin ENB connect to PCA9685 port 1
#define Motor4_B 6  //right motor speed pin ENB connect to PCA9685 port 1

#define ENA 0  //left motor speed pin ENA connect to PCA9685 port 0
#define ENB 1  //right motor speed pin ENB connect to PCA9685 port 1
#define IN1 4  //Left motor IN1 connect to wPi pin# 4 (Physical 16,BCM GPIO 23)
#define IN2 5  //Left motor IN2 connect to wPi pin# 5 (Physical 18,BCM GPIO 24)
// #define IN2 7  //Left motor IN2 connect to wPi pin# 5 (Physical 18,BCM GPIO 24)
#define IN3 2  //right motor IN3 connect to wPi pin# 2 (Physical 13,BCM GPIO 27)
#define IN4 3  //right motor IN4 connect to wPi pin# 3 (Physical 15,BCM GPIO 22)
#define SPEED 2000


class Motor{
  public:
   int fd;
   Motor(int fdReference){
    fd = fdReference; // pca9685Setup(PIN_BASE, 0x40, HERTZ)
    if (fd < 0){
      printf("Error in setup\n");

    }
   }
  void left_Upper_Wheel(int fd,int speed){
    if(speed>0){
      pca9685PWMWrite(fd, Motor1_F, 0, 4095-speed);
    }
    else if(speed<0){
      pca9685PWMWrite(fd, Motor1_B, 0, 4095-abs(speed));
    }
    else{
      pca9685PWMWrite(fd, Motor1_F, 0, 4095);
      pca9685PWMWrite(fd, Motor1_B, 0, 4095);
    }
  }

  void left_Lower_Wheel(int fd,int speed){
      if(speed>0){
        pca9685PWMWrite(fd, Motor2_F, 0, 4095-speed);
      }
      else if(speed<0){
        pca9685PWMWrite(fd, Motor2_B, 0, 4095-abs(speed));
      }	 
      else{
        pca9685PWMWrite(fd, Motor2_F, 0, 4095);
        pca9685PWMWrite(fd, Motor2_B, 0, 4095);
      }
  }

  void right_Lower_Wheel(int fd,int speed){
      if(speed>0){
        pca9685PWMWrite(fd, Motor3_F, 0, 4095-speed);
      }
      else if(speed<0){
        pca9685PWMWrite(fd, Motor3_B, 0, 4095-abs(speed));
      }	 
      else{
        pca9685PWMWrite(fd, Motor3_F, 0, 4095);
        pca9685PWMWrite(fd, Motor3_B, 0, 4095);
      }
  }

  void right_Upper_Wheel(int fd,int speed){
      if(speed>0){
        pca9685PWMWrite(fd, Motor4_F, 0, 4095-speed);
      }
      else if(speed<0){
        pca9685PWMWrite(fd, Motor4_B, 0, 4095-abs(speed));
      }	 
      else{
        pca9685PWMWrite(fd, Motor4_F, 0, 4095);
        pca9685PWMWrite(fd, Motor4_B, 0, 4095);
      }
  }

  void MotorGo(int speed1,int speed2,int speed3,int speed4,int duration = 1000){
    stop_car();
    left_Upper_Wheel(fd,speed1);
    left_Lower_Wheel(fd,speed2);
    right_Upper_Wheel(fd,speed3);
    right_Lower_Wheel(fd,speed4);
    delay(duration);
    stop_car();
  }
  void stop_car(){
    pca9685PWMWrite(fd, 0, 0, 4095);
    pca9685PWMWrite(fd, 1, 0, 4095);
    pca9685PWMWrite(fd, 2, 0, 4095);
    pca9685PWMWrite(fd, 3, 0, 4095);
    pca9685PWMWrite(fd, 4, 0, 4095);
    pca9685PWMWrite(fd, 5, 0, 4095);
    pca9685PWMWrite(fd, 6, 0, 4095);
    pca9685PWMWrite(fd, 7, 0, 4095);
    delay(100);
  }
};



     

// initialize  IN1,IN2,IN3,IN4 
void setup(){
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
}

// int main(int argc, char* argv[])
// {
//   wiringPiSetup();
//  int fd = pca9685Setup(300, 0x40, 50);
//   Motor m1 = Motor(fd);
//   int duration = argv[1];
//   cout << duration <<endl;
//   m1.MotorGo(1000,1000,1000,1000,duration);
//   m1.stop_car();
//   return 0;
// }
