// Wiring method: The YL-69 has an analogue output (AO port) and a digital output (DO port), as the Raspberry Pi's GPIO only supports digital inputs.
// so the AO port is left hanging. Connect VCC to physical interface 2, the GND pin to physical interface 14 and the DO pin to physical interface 40.
// Once wired, the power light (red light) will come on, adjust the threshold knob on the sensor so that the green light does not come on in air.
// At this point stick the sensor contacts into the water and you will see the green light come on.

#include <iostream>
#include <wiringPi.h>

using namespace std;

const int SOIL_MOISTURE_SENSOR_PIN = 29;  // WPI 29 pin 40, BCM code 21
const int WATERING_THRESHOLD_LOW = 400;  // Lower watering threshold
const int WATERING_THRESHOLD_HIGH = 650;  // Watering threshold limit

int main(void) {
    if(wiringPiSetup() == -1) {  // Initialising the wiringPi library
        cout << "Failed to initialize wiringPi library." << endl;
        return 0;
    }
    pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);  // Set pins to input mode
    while(1) {  // Infinite loop
        if(digitalRead(SOIL_MOISTURE_SENSOR_PIN) == LOW) {
            cout << "Soil moisture result: wet" << endl;
        }else {
          int soil_moisture_value = analogRead(SOIL_MOISTURE_SENSOR_PIN);  // Reading analogue input values
          cout << "Soil moisture value: " << soil_moisture_value << endl;
          if(soil_moisture_value < WATERING_THRESHOLD_LOW) {
              cout << "Soil moisture too low, please water the plant." << endl;
          }
          else if(soil_moisture_value > WATERING_THRESHOLD_HIGH) {
              cout << "Soil moisture is moderate, stop watering the plant." << endl;
          }
        }
        delay(1000);  // Delayed by 1 second
    }
    return 0;
}
