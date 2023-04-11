//light sensor, when light is strong, car start to run

#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


def recvADC(self,channel):
    if self.Index=="PCF8591":
        data=self.recvPCF8591(channel)
    elif self.Index=="ADS7830":
        data=self.recvADS7830(channel)
    return data

int main(void){
    self.adc=Adc()
    self.PWM=Motor()
    self.PWM.setMotorModel(0,0,0,0)
    while True:
        L = self.adc.recvADC(0)
        R = self.adc.recvADC(1)

        if (L > 2.99 && R > 2.99) 
        {
            set.detect
        }
                    
                    
        except KeyboardInterrupt:
           led_Car.PWM.setMotorModel(0,0,0,0) 
}
            self.adc=Adc()
            self.PWM=Motor()
            self.PWM.setMotorModel(0,0,0,0)
            while True:
                L = self.adc.recvADC(0)
                R = self.adc.recvADC(1)

                if (L > 2.99 && R > 2.99) 
                {
                    set.detect
                }
                    
                    
        except KeyboardInterrupt:
           led_Car.PWM.setMotorModel(0,0,0,0) 

if __name__=='__main__':
    print ('Program is starting ... ')
    led_Car=Light()
    led_Car.run()


