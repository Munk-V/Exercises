/*
  Exercise 9d, 9e, 9f - LM35DZ temperature sensor

  Wiring (LM35 with flat face toward you):
  Left  pin  -> 5V
  Middle pin -> A0  (Vout)
  Right pin  -> GND
*/

const uint8_t TEMP_PIN = A0;

float readVoltage(uint8_t pin) {
  int adc = analogRead(pin);            // 0..1023
  return adc * (5.0 / 1023.0);          // volts (assuming 5V reference)
}

float voltageToC_LM35(float v) {
  // LM35: 10 mV/°C = 0.010 V/°C
  // => Temp(°C) = V / 0.010 = V * 100
  return v * 100.0;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  int adc = analogRead(TEMP_PIN);       // raw ADC (optional to print)
  float v = adc * (5.0 / 1023.0);       // 9d: ADC -> Voltage
  float tC = voltageToC_LM35(v);        // 9e: Voltage -> Celsius

  //Serial.print("ADC=");
  //Serial.print(adc);

  Serial.print("  V=");
  Serial.print(v, 3);

  Serial.print("  T=");
  Serial.print(tC, 1);
  Serial.print("\xC2\xB0");
  Serial.println("C");


  delay(500);                           // 9f: update rate
}
