
#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

const int Infrared_pin = 23;  // Pin33 , BCM code 13
const int Infrared_pin_back = 26;  // Pin32 , BCM code 12



class Infrared{
	public:
		bool isRuning = false;
	std::thread loopThread;
	Infrared(){
		pinMode(Infrared_pin, INPUT);
	}

	float getFrontValue(){
		float infrared_value = digitalRead(Infrared_pin);
		return infrared_value;
	}	 
  float getBackValue(){
		float infrared_value = digitalRead(Infrared_pin_back);
		return infrared_value;
	}	

};


int main(void) {
  if(wiringPiSetup() == -1) {  // Initialising the wiringPi library
      cout << "Failed to initialize wiringPi library." << endl;
      return 0;
  }
  Infrared inf = Infrared();
	int t0=time(0);
  while(time(0) - t0 < 10 ){
		float infrared_value = inf.getValue();
		cout<<"infrared_vale of the front: "<<infrared_value<<endl;
    float infrared_value_back = inf.getBackValue();
		cout<<"infrared_vale of the back: "<<infrared_value_back<<endl;
	}
	
  return 0;
}




