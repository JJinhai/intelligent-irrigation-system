#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#include "ultrasonic.cpp"
#include "motor.cpp"
#include "light.cpp"
#include "Infrared.cpp"
#include "irrigation.cpp"



int main(int argc, char* argv[]){
  if(wiringPiSetup()==-1){
    printf("setup wiringPi failed!\n");
    printf("please check your setup\n");
    return -1;
  }
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);

  std::string str = argv[1]; 
  if(str == "ultrasonic"){
    Ultrasonic u = Ultrasonic();
    int d = u.getDistance();
    printf("Main the distance is %d cm",d);
  }else if(str == "motor"){
    Motor m1 = Motor(fd);
    m1.MotorGo(1000,1000,1000,1000);
  }else if(str == "light"){
    Light l1 = Light();
    l1.start();
    delay(15000);
    l1.end();
  }else if(str == "infrared"){
    Infrared inf = Infrared();
    int t0=time(0);
    while(time(0) - t0 < 10 ){
      float infrared_value = inf.getValue();
      cout<<"infrared_vale of the front: "<<infrared_value<<endl;
      float infrared_value_back = inf.getBackValue();
      cout<<"infrared_vale of the back: "<<infrared_value_back<<endl;
    }
  }else if(str == "irrigation"){
    Irrigation ir = Irrigation();
    ir.start();
    delay(10000);
    ir.end();
  }
  return 0;
}
