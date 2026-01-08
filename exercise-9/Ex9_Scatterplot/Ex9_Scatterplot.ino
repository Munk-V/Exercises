/*
  EX9d/9e/9f - LM35DZ
  Output for Serial Plotter: Voltage  TemperatureC (numbers only)

  Wiring (flat face toward you):
  Left  -> 5V
  Middle-> A0
  Right -> GND
*/

const uint8_t TEMP_PIN = A0;

float adcToVoltage(int adc) {
  return adc * (5.0 / 1023.0);   // default 5V reference
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  int adc = analogRead(TEMP_PIN);
  float v  = adcToVoltage(adc);  // 9d: ADC -> V
  float tC = v * 100.0;          // 9e: LM35 (10mV/°C) => T = V*100

  // Serial Plotter: ONLY numbers (2 columns)
  // Column 1: V (volts), Column 2: T (°C)
  Serial.print(v, 3);
  Serial.print(" ");
  Serial.println(tC, 2);

  delay(200);
}
