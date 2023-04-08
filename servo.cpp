#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50


class Servor{
  public:
   int fd;
   Motor(){
    fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0){
      printf("Error in setup\n");

    }
   }
  void setServo(int chanel,int angle){
    int error = 10;
    int port = 0;
    int pulse = 0;
    if(chanel==0){
      port = 8;
      pulse = 2500-int((angle+error)/0.09);
    }else if(chanel==1){
      port = 9;
      pulse = 500+int((angle+error)/0.09);
    }
    pulse = pulse*4096/20000;
    pca9685PWMWrite(fd, port, 0, pulse);
  }
}

int main(void){
  if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
  }
	Servor serv1= Servor();
  Serv1.setServo(0,0);
  delay(500);
  Serv1.setServo(0,90);
  delay(500);
  Serv1.setServo(0,180);
  delay(500);
  Serv1.setServo(1,0);
  delay(500);
  Serv1.setServo(1,90);
  delay(500);
  Serv1.setServo(1,180);
	return 0;
}
