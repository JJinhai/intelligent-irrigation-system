#include <iostream>
#include <wiringPi.h>

using namespace std;

const int SOIL_MOISTURE_SENSOR_PIN = 29;  // 管脚40，BCM编码为21
const int WATER_PUMP_PIN = 22;  // 管脚31，BCM编码为22


int main(void) {
    if(wiringPiSetup() == -1) {  // 初始化wiringPi库
        cout << "Failed to initialize wiringPi library." << endl;
        return 0;
    }
    pinMode(WATER_PUMP_PIN, OUTPUT);  // 设置水泵控制引脚为输出模式
    digitalWrite(WATER_PUMP_PIN, HIGH);  // 开启水泵
    delay(1000);  // 延迟1秒钟
    digitalWrite(WATER_PUMP_PIN, LOW);  // 关闭水泵
    delay(1000);  // 延迟1秒钟
    return 0;
}