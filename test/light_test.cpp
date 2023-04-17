#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <wiringPi.h>
#include "Light.h" // 将原始代码中的 Light 类移动到一个单独的文件中，以便在测试中引用。

using namespace std;

TEST_GROUP(LightGroup) {
    Light *test_light;

    void setup() {
        test_light = new Light();
    }

    void teardown() {
        delete test_light;
    }
};

TEST(LightGroup, TestLeftValueReading) {
    // 记录对 analogRead 的预期调用
    mock().expectOneCall("analogRead").withIntParameter("channel", A0).andReturnValue(1000);

    // 获取左侧光照值
    float left_value = test_light->getLeftValue();

    // 检查预期调用是否发生
    mock().checkExpectations();

    // 验证返回的光照值
    CHECK_EQUAL(5000.0 * 1000 / 255, left_value);
}

TEST(LightGroup, TestRightValueReading) {
    // 记录对 analogRead 的预期调用
    mock().expectOneCall("analogRead").withIntParameter("channel", A1).andReturnValue(1500);

    // 获取右侧光照值
    float right_value = test_light->getRightValue();

    // 检查预期调用是否发生
    mock().checkExpectations();

    // 验证返回的光照值
    CHECK_EQUAL(5000.0 * 1500 / 255, right_value);
}

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
