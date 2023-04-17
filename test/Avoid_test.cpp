#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Avoid.h" // 将原始代码中的 Avoid 类移动到一个单独的文件中，以便在测试中引用。

using namespace std;

TEST_GROUP(AvoidGroup) {
    int test_fd;
    Avoid *test_avoid;

    void setup() {
        test_fd = 100; // 一个模拟的文件描述符
        test_avoid = new Avoid(test_fd);
    }

    void teardown() {
        delete test_avoid;
    }
};

TEST(AvoidGroup, TestNormalDetect) {
    // 记录对 setServo 的预期调用
    for(int i = 30 ; i < 151 ; i = i+60){
        mock().expectOneCall("setServo").withIntParameter("fd", test_fd).withIntParameter("channel", 0).withIntParameter("angle", i);
    }
    test_avoid->normalDetect();

    // 检查预期调用是否发生
    mock().checkExpectations();
}

// 类似地，编写其他测试函数，例如 TestFakeMove 和 TestDetect

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
