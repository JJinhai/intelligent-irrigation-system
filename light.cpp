//light sensor, when light is strong, car start to run

#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


void recvADC(self,channel){
    if self.Index=="PCF8591":
        data=self.recvPCF8591(channel)
    elif self.Index=="ADS7830":
        data=self.recvADS7830(channel)
    return data
}

class Light{
  public:
    Adc adc;
    void Light(){
      adc=Adc();
    }
    float[] getLight(){
      L = recvADC(adc,0)
      R = recvADC(adc,1)
      return { L,R }
    }
}

