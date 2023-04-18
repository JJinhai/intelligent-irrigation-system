#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "pre_guidance.cpp"
int main(void)
{
    if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
    }
    
    int fd = pca9685Setup(300, 0x40, 50);
    Guidance guidance1 = Guidance(fd);
    guidance1.go_to_garden();
    // delay(5000);
    // guidance1.back_home();
    return 0;
}