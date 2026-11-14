#include <Arduino.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200); // starting serial
  Serial.println("starting scan");
  Wire.begin(); // start the wire

  pinMode(A4, INPUT);
  digitalWrite(A4, LOW);

  pinMode(A5, INPUT);
  digitalWrite(A5, LOW);

  for (int i = 1; i <= 126; i++) {
    Wire.beginTransmission(i);
    int status = Wire.endTransmission();

    if (status == 0) {
      Serial.print("Addr: ");
      Serial.println(i, HEX);
    }
  }

  Serial.println("Done");
}

void loop() {}
