避障演示
g++ -o pre_avoid avoidObstale.cpp pca9685/pca9685.c -lwiringPi -pthread
./pre_avoid


g++ -o testMotor testMotor.cpp pca9685/pca9685.c -lwiringPi -pthread
./testMotor 2000 1/0


g++ -o pre_guidance pre_guidance.cpp pca9685/pca9685.c -lwiringPi -pthread

