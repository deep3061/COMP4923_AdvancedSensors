/* 
Name: Rubbaldeep Sandhu
Statement of Authorship: I certify that this is my own code and,
I have not broken any rules concerning Academic Dishonesty
*/
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 is connected to D3
const int oneWireBus = D3;

// Setup OneWire communication
OneWire oneWire(oneWireBus);

// Setup Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

// Stores the sensor address
DeviceAddress sensorAddress;

// Keeps track of whether a sensor was found
bool sensorFound = false;

void printAddress(DeviceAddress address) {
    for (int i = 0; i < 8; i++) {
        if (address[i] < 16) {
            Serial.print("0");
        }

        Serial.print(address[i], HEX);
    }

    Serial.println();
}

void setup() {
    Serial.begin(115200);

    Serial.println("Temperature Application");

    // Start the sensor
    DS18B20.begin();

    // Check whether a DS18B20 sensor is connected
    if (DS18B20.getAddress(sensorAddress, 0)) {
        sensorFound = true;

        Serial.print("Found DS18B20 sensor with address: ");
        printAddress(sensorAddress);
    }
    else {
        Serial.println("No DS18B20 temperature sensors are installed!");
    }
}

void loop() {

    // If no sensor was found, do nothing
    if (!sensorFound) {
        return;
    }

    float temperature;
    String temperatureStatus;

    // Ask sensor for temperature
    DS18B20.requestTemperatures();

    // Read temperature in Celsius
    temperature = DS18B20.getTempCByIndex(0);

    // Decide temperature judgement
    if (temperature < 10) {
        temperatureStatus = "Cold!";
    }
    else if (temperature >= 10 && temperature < 15) {
        temperatureStatus = "Cool";
    }
    else if (temperature >= 15 && temperature < 25) {
        temperatureStatus = "Perfect";
    }
    else if (temperature >= 25 && temperature < 30) {
        temperatureStatus = "Warm";
    }
    else if (temperature >= 30 && temperature < 35) {
        temperatureStatus = "Hot";
    }
    else {
        temperatureStatus = "Too Hot!";
    }

    // Print temperature and judgement
    Serial.println(
        "Current temperature is: " +
        String(temperature, 2) +
        " C or " +
        temperatureStatus
    );

    // Wait 5 seconds
    delay(5000);
}