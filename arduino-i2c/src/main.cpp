#include <Arduino.h>
#include <Wire.h>

void setup() {
    Serial.begin(115200);
    Wire.begin();

    pinMode(A4, INPUT);
    digitalWrite(A4, LOW);

    pinMode(A5, INPUT);
    digitalWrite(A5, LOW);

    

}