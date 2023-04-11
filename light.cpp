#include <wiringPi.h>
#include <pcf8591.h>
#include <stdio.h>
#include <time.h>
#include <thread>
//PCF8591默认的I2C设备地址
#define Address 0x48

//模拟信号输入端的地址
#define BASE 0x40
#define A0 0x40
#define A1 0x41

//供电(mV)
#define POWER 5000

//函数声明
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
      float AD_val = 0; //定义处理后的数值AD_val为浮点数
      unsigned char i;
      for (i = 0; i < 10; i++) 
        AD_val += analogRead(channel); //转换10次求平均值(提高精度)
      AD_val /= 10;
      AD_val = (AD_val * POWER)/ 255 ; //AD的参考电压是单片机上的5v，所以乘5即为实际电压值
      return AD_val;
    }
    //显示系统时间
    void ShowTime(){
      time_t t;
      struct tm *p;
      int hour = 0, min = 0, sec = 0;
      time(&t);
      p = gmtime(&t);
      hour = 8 + p->tm_hour; //获取当地时间，与UTC时间相差8小时
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
          AD_val_left = AD_work(A0);//读取A0端口的电压值
          AD_val_right = AD_work(A1);//读取A1端口的电压值
          ShowTime(); //打印当前时间
          printf("left value: %fmV\n", AD_val_left); //打印A0引脚的输入电压
          printf("right value: %fmV\n", AD_val_right); //打印A0引脚的输入电压
          delay(1000);
        }
      });
    }
    void end(){
      isLighting = false;
      loopThread.join();
    }
};

int main(void)
{
  if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
  }
  Light l1 = Light();
  l1.start();
	delay(15000);
  l1.end();

	return 0;
}

