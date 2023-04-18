初始化
g++ -o init init.cpp pca9685/pca9685.c -lwiringPi -pthread
./init

避障演示
g++ -o pre_avoid avoidObstale.cpp pca9685/pca9685.c -lwiringPi -pthread
./pre_avoid

路径规划
g++ -o pre_guidance pre_guidance_test.cpp pca9685/pca9685.c -lwiringPi -pthread 
./pre_guidance

测试motor
g++ -o testMotor testMotor.cpp pca9685/pca9685.c -lwiringPi -pthread
./testMotor 2000 1/0


传感器各项
g++ -o pre_detect pre_detect.cpp pca9685/pca9685.c -lwiringPi -pthread 
./pre_detect

灌溉测试
g++ -o pre_irrigation pre_irrigation_test.cpp pca9685/pca9685.c -lwiringPi -pthread
./pre_irrigation