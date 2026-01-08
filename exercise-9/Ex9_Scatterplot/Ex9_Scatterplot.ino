/**
 * @file EX9_LM35_SerialPlotter.ino
 * @brief Exercise 9d/9e/9f: Read LM35DZ on A0, convert ADC->Voltage->Temperature and print for Serial Plotter.
 *
 * The sketch reads the analog value from the LM35DZ temperature sensor, converts it to voltage
 * using the assumed ADC reference (5.0 V), then converts voltage to temperature in °C using
 * the LM35 transfer function (10 mV/°C => 0.010 V/°C).
 *
 * ## Wiring (LM35DZ, flat face toward you)
 * - Left pin  -> 5V
 * - Middle pin-> A0 (Vout)
 * - Right pin -> GND
 *
 * ## Serial Plotter output format
 * Prints **numbers only** in **two columns** separated by a space:
 * 1) Voltage (V) with 3 decimals
 * 2) Temperature (°C) with 2 decimals
 */

/**
 * @brief Analog input pin connected to the LM35 output (Vout).
 */
const uint8_t TEMP_PIN = A0;

/**
 * @brief Convert a raw ADC reading to volts.
 *
 * Assumes a 10-bit ADC (0..1023) and a 5.0 V analog reference.
 *
 * @param adc Raw ADC value from analogRead(), expected range 0..1023.
 * @return Voltage in volts.
 */
float adcToVoltage(int adc) {
  return adc * (5.0 / 1023.0);   // default 5V reference
}

/**
 * @brief Arduino setup function.
 *
 * Initializes Serial communication for the Serial Plotter / Serial Monitor.
 */
void setup() {
  Serial.begin(115200);
}

/**
 * @brief Arduino main loop.
 *
 * Reads the sensor, converts to voltage and temperature, prints values for Serial Plotter,
 * then waits 200 ms before the next sample.
 *
 * @note LM35 sensitivity: 10 mV/°C => Temperature(°C) = V / 0.010 = V * 100
 */
void loop() {
  int adc = analogRead(TEMP_PIN);     ///< Raw ADC sample from A0
  float v  = adcToVoltage(adc);       ///< 9d: ADC -> Voltage (V)
  float tC = v * 100.0;               ///< 9e: Voltage -> Temperature (°C)

  // Serial Plotter: ONLY numbers (2 columns)
  // Column 1: V (volts), Column 2: T (°C)
  Serial.print(v, 3);
  Serial.print(" ");
  Serial.println(tC, 2);

  delay(200);
}
