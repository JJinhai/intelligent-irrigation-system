#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#define Trigger_pin 2
#define Echo_pin 3
#define MAX_DISTANCE 300    
#define TimeOut MAX_DISTANCE*60

class Ultrasonic{
  public:
    Ultrasonic(){
      pinMode(Trigger_pin,OUTPUT);
      pinMode(Echo_pin,INPUT);
    }
  long getTime(){
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    return tv1.tv_sec * 1000000 + tv1.tv_usec;
  }
  int pulseIn(){
    long t0 = getTime();
    while(digitalRead(Echo_pin) != HIGH){
      if((getTime() - t0) > TimeOut){
        return 17647;
      }
    }
    t0 = getTime();
    while(digitalRead(Echo_pin) == HIGH){
      if((getTime() - t0) > TimeOut){
        return 17647;
      }
    }
    int pulseTime = (getTime() - t0);
    return pulseTime;
  }
  int getDistance(){
    int distance_cm[5] = { 0, 0, 0, 0, 0 }; // Arrays to be sorted
    for(int i=0 ;i<5;i++){
      digitalWrite(Trigger_pin,HIGH);      // make trigger_pin output 10us HIGH level 
      delay(0.00001);
      digitalWrite(Trigger_pin,LOW); 
      int pulseTime = pulseIn()* 340.0 / 2.0 / 10000.0;
      distance_cm[i] = pulseTime;
    }
    std::sort(distance_cm, distance_cm + 5); // Calling the std::sort function to sort an array
    return distance_cm[2];
  }
};


// int main(void){
//   if(wiringPiSetup()==-1){
//     printf("setup wiringPi failed!\n");
//     printf("please check your setup\n");
//     return -1;
//   }
//   Ultrasonic u = Ultrasonic();
//   int d = u.getDistance();
//   printf("the distance is %d cm",d);
//   return 0;
// }
