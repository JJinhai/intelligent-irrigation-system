// 参考链接 https://osoyoo.com/2020/11/06/osoyoo-pie-car-v2-0-for-raspberry-pi-lesson-1-basic-framework-and-programming-gpio-pca9685-c-version/
#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include "motor.cpp"

int main(int argc, char* argv[])
{
  wiringPiSetup();
 int fd = pca9685Setup(300, 0x40, 50);
  Motor m1 = Motor(fd);
  int duration = std::atoi(argv[1]);
  int direction = std::atoi(argv[2]);
  if(direction == 1){
    m1.MotorGo(2500,2500,2400,2400,duration); // 37 2
  }else{
    m1.MotorGo(2500,2500,-2500,-2500,duration); // 3000 2pi
  }
  return 0;
}
