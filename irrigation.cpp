// 接线方法：YL-69有模拟输出（AO口）和数字输出（DO口），由于树莓派的GPIO只支持数字输入，
// 所以AO口悬空。将VCC连接物理接口2，GND引脚连接物理接口14，DO引脚连接物理接口40。
// 接好线以后，电源灯（红灯）会亮起，调节传感器上的阈值旋钮，使得在空气中绿灯不亮。
// 此时将传感器触角伸入水中，可以看到绿灯亮起。

#include <iostream>
#include <wiringPi.h>

using namespace std;

const int SOIL_MOISTURE_SENSOR_PIN = 29;  // WPI 29 管脚40，BCM编码为21
const int WATERING_THRESHOLD_LOW = 400;  // 浇水阈值下限
const int WATERING_THRESHOLD_HIGH = 650;  // 浇水阈值上限

int main(void) {
    if(wiringPiSetup() == -1) {  // 初始化wiringPi库
        cout << "Failed to initialize wiringPi library." << endl;
        return 0;
    }
    pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);  // 设置引脚为输入模式
    while(1) {  // 无限循环
        if(digitalRead(SOIL_MOISTURE_SENSOR_PIN) == LOW) {
            cout << "Soil moisture result: wet" << endl;
        }else {
          int soil_moisture_value = analogRead(SOIL_MOISTURE_SENSOR_PIN);  // 读取模拟输入值
          cout << "Soil moisture value: " << soil_moisture_value << endl;
          if(soil_moisture_value < WATERING_THRESHOLD_LOW) {
              cout << "Soil moisture too low, please water the plant." << endl;
          }
          else if(soil_moisture_value > WATERING_THRESHOLD_HIGH) {
              cout << "Soil moisture is moderate, stop watering the plant." << endl;
          }
        }
        delay(1000);  // 延迟1秒钟
    }
    return 0;
}
