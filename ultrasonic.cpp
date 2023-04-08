#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define Trigger_pin 27
#define Echo_pin 22
#define MAX_DISTANCE 300    
#define TimeOut MAX_DISTANCE*60

// class Ultrasonic{
//   public:

// }

int main(void){
  pinMode(Trigger_pin,OUTPUT);
  pinMode(Echo_pin,INPUT);
  function pulseIn(){
    int t0 = time();
    while(digitalRead(Echo_pin) != HIGH):
        if((time() - t0) > TimeOut*0.000001):
            return 0;
    t0 = time.time();
    while(digitalRead(Echo_pin) == HIGH):
        if((time() - t0) > TimeOut*0.000001):
            return 0;
    pulseTime = (time.time() - t0)*1000000;
    return pulseTime;
  }
  distance_cm=[0,0,0,0,0];
  int distance_cm[] = { 5, 3, 1, 4, 2 }; // 待排序的数组

  for(int i=0 ;i<5;i++){
    digitalWrite(Trigger_pin,HIGH)      # make trigger_pin output 10us HIGH level 
    delay(0.00001);
    digitalWrite(Trigger_pin,LOW) 
    int pulseTime = pulseIn()* 340.0 / 2.0 / 10000.0;
    distance_cm[i] = pulseTime;
  }
  std::sort(distance_cm, distance_cm + 5); // 调用std::sort函数对数组进行排序
  printf(distance_cm[2]);
  return 0;
}