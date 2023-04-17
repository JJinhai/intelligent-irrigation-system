#include <wiringPi.h>
#include <pcf8591.h>
#include <stdio.h>
#include <time.h>
#include <thread>
//PCF8591 default I2C device address
#define Address 0x48

//Address of the analogue signal input
#define BASE 0x40
#define A0 0x40
#define A1 0x41

//Power supply (mV)
#define POWER 5000

//Function declarations
void ShowTime();
float AD_work(unsigned char channel);

class Light{
  public:
    bool isLighting;
    std::thread loopThread;
    Light(){
      pcf8591Setup(BASE, Address);
      isLighting = false;
    }
    float AD_work(unsigned char channel){
      float AD_val = 0; //Define the processed value AD_val as a floating point number
      unsigned char i;
      for (i = 0; i < 10; i++) 
        AD_val += analogRead(channel); //Average of 10 conversions (to improve accuracy)
      AD_val /= 10;
      AD_val = (AD_val * POWER)/ 255 ; //The reference voltage of the AD is 5v on the microcontroller, so multiplying by 5 is the actual voltage value
      return AD_val;
    }
    //Show system time
    void ShowTime(){
      time_t t;
      struct tm *p;
      int hour = 0, min = 0, sec = 0;
      time(&t);
      p = gmtime(&t);
      hour = 8 + p->tm_hour; //Get local time, 8 hours difference from UTC time
      min = p->tm_min;
      sec = p->tm_sec;
      printf("\nNow time: %.2d:%.2d:%.2d\n", hour, min, sec);
    }
    void start(){
      isLighting = true;
      loopThread = std::thread([this]() {
        float AD_val_left;
        float AD_val_right;
        while (isLighting){
          AD_val_left = AD_work(A0);//Reading the voltage value of port A0
          AD_val_right = AD_work(A1);//Reading the voltage value of port A1
          ShowTime(); //Print current time
          printf("left value: %fmV\n", AD_val_left); //Print the input voltage of the A0 pin
          printf("right value: %fmV\n", AD_val_right); //Print the input voltage of the A0 pin
          delay(1000);
        }
      });
    }
    void end(){
      isLighting = false;
      loopThread.join();
    }

    float getLeftValue(){
      float AD_val_left;
      AD_val_left = AD_work(A0);//Reading the voltage value of port A0
      return AD_val_left;
    }
    float getRightValue(){
      float AD_val_right;
      AD_val_right = AD_work(A1);//Reading the voltage value of port A1
      return AD_val_right;
    }
};

// int main(void)
// {
//   if(wiringPiSetup()==-1){
//       printf("setup wiringPi failed!\n");
//       printf("please check your setup\n");
//       return -1;
//   }
//   Light l1 = Light();
//   l1.start();
// 	delay(15000);
//   l1.end();

// 	return 0;
// }

