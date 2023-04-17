#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Motor.h" // 将原始代码中的 Motor 类移动到一个单独的文件中，以便在测试中引用。

using namespace std;

TEST_GROUP(MotorGroup) {
    int test_fd;
    Motor *test_motor;

    void setup() {
        test_fd = 100; // 一个模拟的文件描述符
        test_motor = new Motor(test_fd);
    }

    void teardown() {
        delete test_motor;
    }
};

TEST(MotorGroup, TestLeftUpperWheel) {
    // 记录对 pca9685PWMWrite 的预期调用
    mock().expectOneCall("pca9685PWMWrite").withIntParameter("fd", test_fd).withIntParameter("channel", Motor1_F).withIntParameter("on", 0).withIntParameter("off", 4095 - 1000);

    test_motor->left_Upper_Wheel(test_fd, 1000);

    // 检查预期调用是否发生
    mock().checkExpectations();
}

// 类似地，编写其他测试函数，例如 TestLeftLowerWheel, TestRightUpperWheel, TestRightLowerWheel, TestMotorGo 和 TestStopCar

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
