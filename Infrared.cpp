
#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "guidance.cpp"


using namespace std;

const int Infrared_pin = 23;  // Pin33 , BCM code 13


class Infrared{
	public:
		bool isRuning = false;
	std::thread loopThread;
	Infrared(){
		pinMode(INFRARED_PIN, INPUT);
	}

	float getValue(){

		float infrared_value = digitalread(Infrared_pin);
		
		return infrared_value;		
	}	 

}


int main(void) {
    if(wiringPiSetup() == -1) {  // Initialising the wiringPi library
        cout << "Failed to initialize wiringPi library." << endl;
        return 0;
    }
    Infrared inf = Infrared();
	int t0=time.time();
    while(time.time() - t0 < 10 ){
		float infrared_vale = inf.getValue();
		cout<<"infrared_vale: "<<infrared_value;

	}
	
    

    return 0;
}




