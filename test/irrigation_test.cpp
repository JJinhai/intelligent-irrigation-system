#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <wiringPi.h>
#include "Irrigation.h" // 将原始代码中的 Irrigation 类移动到一个单独的文件中，以便在测试中引用。

using namespace std;

TEST_GROUP(IrrigationGroup) {
    Irrigation *test_irrigation;

    void setup() {
        test_irrigation = new Irrigation();
    }

    void teardown() {
        delete test_irrigation;
    }
};

TEST(IrrigationGroup, TestWaterPumpControl) {
    // 记录对 digitalRead, analogRead 和 digitalWrite 的预期调用
    mock().expectOneCall("digitalRead").withIntParameter("pin", SOIL_MOISTURE_SENSOR_PIN).andReturnValue(1);
    mock().expectOneCall("analogRead").withIntParameter("pin", SOIL_MOISTURE_SENSOR_PIN).andReturnValue(300);
    mock().expectOneCall("digitalWrite").withIntParameter("pin", WATER_PUMP_PIN).withIntParameter("value", LOW);

    // 启动灌溉系统
    test_irrigation->start();
    delay(1000); // 等待一秒，让线程执行

    // 检查预期调用是否发生
    mock().checkExpectations();

    // 停止灌溉系统
    test_irrigation->end();
}

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
