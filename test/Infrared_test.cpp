#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Infrared.h" // 将原始代码中的 Infrared 类移动到一个单独的文件中，以便在测试中引用。

using namespace std;

TEST_GROUP(InfraredGroup) {
    Infrared *test_infrared;

    void setup() {
        test_infrared = new Infrared();
    }

    void teardown() {
        delete test_infrared;
    }
};

TEST(InfraredGroup, TestGetFrontValue) {
    // 记录对 digitalRead 的预期调用
    mock().expectOneCall("digitalRead").withIntParameter("pin", Infrared_pin).andReturnValue(1);

    // 调用 getFrontValue
    float infrared_value = test_infrared->getFrontValue();

    // 检查预期调用是否发生
    mock().checkExpectations();
    CHECK_EQUAL(1, infrared_value);
}

TEST(InfraredGroup, TestGetBackValue) {
    // 记录对 digitalRead 的预期调用
    mock().expectOneCall("digitalRead").withIntParameter("pin", Infrared_pin_back).andReturnValue(0);

    // 调用 getBackValue
    float infrared_value = test_infrared->getBackValue();

    // 检查预期调用是否发生
    mock().checkExpectations();
    CHECK_EQUAL(0, infrared_value);
}

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
