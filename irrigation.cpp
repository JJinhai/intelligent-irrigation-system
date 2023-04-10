#include <iostream>
#include <wiringPi.h>

using namespace std;

const int SOIL_MOISTURE_SENSOR_PIN = 29;  // 管脚40，BCM编码为21
const int WATER_PUMP_PIN = 4;  // 管脚31，BCM编码为22
const int WATERING_THRESHOLD_LOW = 400;  // 浇水阈值下限
const int WATERING_THRESHOLD_HIGH = 650;  // 浇水阈值上限

int main(void) {
    if(wiringPiSetup() == -1) {  // 初始化wiringPi库
        cout << "Failed to initialize wiringPi library." << endl;
        return 0;
    }

    pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);  // 设置土壤湿度检测引脚为输入模式
    pinMode(WATER_PUMP_PIN, OUTPUT);  // 设置水泵控制引脚为输出模式

    while(1) {  // 无限循环
        int a = digitalRead(SOIL_MOISTURE_SENSOR_PIN);
        printf("digitalRead(SOIL_MOISTURE_SENSOR_PIN) %d\n",a);
        int soil_moisture_value = analogRead(SOIL_MOISTURE_SENSOR_PIN);  // 读取土壤湿度数值
        cout << "Soil moisture value: " << soil_moisture_value << endl;
        if(soil_moisture_value < WATERING_THRESHOLD_LOW) {  // 检查土壤湿度是否过低
            cout << "Soil moisture too low, please water the plant." << endl;
            digitalWrite(WATER_PUMP_PIN, HIGH);  // 开启水泵
        }
        else if(soil_moisture_value > WATERING_THRESHOLD_HIGH) {  // 检查土壤湿度是否过高
            cout << "Soil moisture is moderate, stop watering the plant." << endl;
            digitalWrite(WATER_PUMP_PIN, LOW);  // 关闭水泵
        }
        delay(1000);  // 延迟1秒钟
    }

    return 0;
}