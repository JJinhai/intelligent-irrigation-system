#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

void run_motor(self,L,M,R){
  if (L < 30 and M < 30 and R <30){
    self.PWM.setMotorModel(-1450,-1450,-1450,-1450) 
    dealy(0.1);
    if(L < R){
      self.PWM.setMotorModel(1450,1450,-1450,-1450)
    }else{
      self.PWM.setMotorModel(-1450,-1450,1450,1450)
    }
  }else if(L < 30 and M < 30){
    PWM.setMotorModel(1500,1500,-1500,-1500)
  }else if( R < 30 and M < 30){
    PWM.setMotorModel(-1500,-1500,1500,1500)
  }else if( L < 20 ){
    PWM.setMotorModel(2000,2000,-500,-500)
    if(L < 10){
      PWM.setMotorModel(1500,1500,-1000,-1000)
    }
  }else if(R < 20){
    PWM.setMotorModel(-500,-500,2000,2000)
    if(R < 10){
      PWM.setMotorModel(-1500,-1500,1500,1500)
    }
  }else {
    self.PWM.setMotorModel(600,600,600,600)
  }
}

int main(void){
  if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
  }
	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
  self.PWM=Motor()
  self.pwm_S=Servo()
  int L = 300,M = 300,R = 300;
  while(True){
    for(int i = 30 ; i < 151 ; i = i+60){
      self.pwm_S.setServoPwm('0',i);
      delay(0.2);
      if(i==30){
        L = self.get_distance();
      }else if(i==90){
        M = self.get_distance();
      }else{
        R = self.get_distance();
      }
    }
    self.pwm_S.setServoPwm('0',90)
    self.run_motor(L,M,R)
  }
	return 0;
}

    
    