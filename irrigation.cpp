#include <iostream>
#include <wiringPi.h>
#include <thread>

using namespace std;



const int SOIL_MOISTURE_SENSOR_PIN = 29;  // Pin 40, BCM code 21
const int WATER_PUMP_PIN = 22;  // Pin 31, BCM code 22
const int WATERING_THRESHOLD_LOW = 400;  // Lower watering threshold
const int WATERING_THRESHOLD_HIGH = 650;  // Watering threshold limit



class Irrigation{
  public:
    bool isRunning = false;
    std::thread loopThread; // The thread where the loop is located
    Irrigation(){
      pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);  // Set the soil moisture detection pin to input mode
      pinMode(WATER_PUMP_PIN, OUTPUT);  // Set the pump control pin to output mode
    }
    void start(){
      isRunning = true;
      loopThread = std::thread([this]() {
        while(isRunning) {  // Infinite loop
          int soil_moisture_digital_value = digitalRead(SOIL_MOISTURE_SENSOR_PIN);
          printf("digitalRead(SOIL_MOISTURE_SENSOR_PIN) %d\n",soil_moisture_digital_value);
          int soil_moisture_value = analogRead(SOIL_MOISTURE_SENSOR_PIN);  // Reading soil moisture values
          cout << "Soil moisture value: " << soil_moisture_value << endl;
          if(soil_moisture_digital_value == HIGH) {  //  soil_moisture_value < WATERING_THRESHOLD_LOW
            cout << "Soil moisture too low, please water the plant." << endl;
            digitalWrite(WATER_PUMP_PIN, LOW);  // Turn on the pump
          }
          else if(soil_moisture_digital_value == LOW) {  // soil_moisture_value > WATERING_THRESHOLD_HIGH
            cout << "Soil moisture is moderate, stop watering the plant." << endl;
            digitalWrite(WATER_PUMP_PIN, HIGH);  // Turn off the pump
          }else{
            digitalWrite(WATER_PUMP_PIN, HIGH);  // Turn off the pump
          }
          delay(1000);  
        }
      });
   }
   void end(){
    isRunning = false;
    loopThread.join();
    digitalWrite(WATER_PUMP_PIN, HIGH);  // close bump
   }
};

int main(void) {
    if(wiringPiSetup() == -1) {  // Initialising the wiringPi library
        cout << "Failed to initialize wiringPi library." << endl;
        return 0;
    }

    Irrigation ir = Irrigation();
    ir.start();
    delay(10000);
    ir.end();

    return 0;
}
