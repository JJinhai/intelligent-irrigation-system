#include <wiringPi.h>
#include <pcf8591.h>
#include <stdio.h>
#include <time.h>

// Default I2C device address for PCF8591
#define Address 0x48

// Address of analog signal input pins
#define BASE 0x40
#define A0 0x40
#define A1 0x41

// Power supply voltage (mV)
#define POWER 5000

// Function declarations
void ShowTime();
float AD_work(unsigned char channel);

int main(void)
{
	// Initialize wiringPi settings
	wiringPiSetup();

	// Set the device address for PCF8591
	pcf8591Setup(BASE, Address);

	float AD_val_left;
	float AD_val_right;
	while (1){
		AD_val_left = AD_work(A0);/// Read voltage value on A0 pin
    AD_val_right = AD_work(A1);// Read voltage value on A1 pin
		ShowTime(); // Print current time
		printf("left value: %fmV\n", AD_val_left); // Print input voltage on A0 pin
    printf("right value: %fmV\n", AD_val_right); // Print input voltage on A1 pin
		delay(100);
	}
}

// Show system time
void ShowTime()
{
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

float AD_work(unsigned char channel)
{
	float AD_val = 0; //定义处理后的数值AD_val为浮点数
	unsigned char i;
	for (i = 0; i < 10; i++) 
		AD_val += analogRead(channel); //转换10次求平均值(提高精度)
	AD_val /= 10;
	AD_val = (AD_val * POWER)/ 255 ; //AD的参考电压是单片机上的5v，所以乘5即为实际电压值
	return AD_val;
}

