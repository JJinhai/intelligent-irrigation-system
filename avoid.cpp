#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "motor.cpp"
#include "servo.cpp"
#include "ultrasonic.cpp"

class Avoid{
  public:
    int fd;
    Avoid(int fdReference){
      fd = fdReference; 
      if (fd < 0){
        printf("Error in setup\n");
      }
    }
    void normalDetect(){
      Servo servo=Servo(fd);
      // Ultrasonic u = Ultrasonic();
      int L,M,R;
      for(int i = 30 ; i < 151 ; i = i+60){
        servo.setServo(0,i);
        delay(200);
        if(i==30){
          // L = u.getDistance();
        }else if(i==90){
          // M = u.getDistance();
        }else{
          // R = u.getDistance();
        }
      }
      servo.setServo(0,90);
    }
    void fakeMove(){
      Motor m1 = Motor(fd);
      const float K = 30;
      const float K_angle = 1;

      const int distance = 60;
      float obstacleLength = 120;

      float steerDegree = M_PI / 2;
      float steerTime = steerDegree / K_angle;

      m1.MotorGo(1000,1000,-1000,-1000,steerTime*1000); // turn right
      m1.MotorGo(1000,1000,1000,1000,distance/K*1000); 
      normalDetect();
      m1.MotorGo(-1000,-1000,1000,1000,steerTime*1000); // turn leftt
      m1.MotorGo(1000,1000,1000,1000,obstacleLength/K*1000); 
      normalDetect();
      m1.MotorGo(-1000,-1000,1000,1000,steerTime*1000); // turn leftt
      m1.MotorGo(1000,1000,1000,1000,distance/K*1000); 
      m1.MotorGo(1000,1000,-1000,-1000,steerTime*1000); // turn right
    }
    bool detect(){
      Servo servo=Servo(fd);
      Ultrasonic u = Ultrasonic();
      int L,M,R;
      for(int i = 30 ; i < 151 ; i = i+60){
        servo.setServo(0,i);
        delay(200);
        if(i==30){
          L = u.getDistance();
        }else if(i==90){
          M = u.getDistance();
        }else{
          R = u.getDistance();
        }
      }
      servo.setServo(0,90);
      if(M < 30){
        return true;
      }else{
        return false;
      }
    }

};
