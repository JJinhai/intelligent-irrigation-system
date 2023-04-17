2650 2650 2200 2200 
200 3800ms

2200 2200 -2200 -2200
2Pi 3950

K = 52.63;
K_angle = 1.5607;


g++ -o testMotor testMotor.cpp pca9685/pca9685.c -lwiringPi -pthread
./testMotor 2000 1/0


g++ -o pre_guidance pre_guidance.cpp pca9685/pca9685.c -lwiringPi -pthread

