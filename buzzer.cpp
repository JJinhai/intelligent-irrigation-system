#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#define Buzzer_Pin 0
  
class Buzzer{
  public:
    Buzzer(){
      pinMode(Buzzer_Pin,OUTPUT);
    }
    void run(int time = 100){
      digitalWrite(Trigger_pin,HIGH); 
      delay(time);
      digitalWrite(Trigger_pin,LOW); 
    }
  }
};