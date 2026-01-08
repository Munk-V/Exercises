/**
 * @file EX9_LM35_ReadVoltage_ToC.ino
 * @brief Exercise 9d/9e/9f: Read LM35DZ temperature sensor, convert ADC->Voltage->°C, and print via Serial.
 *
 * This sketch demonstrates:
 * - 9d: Converting ADC readings to voltage.
 * - 9e: Converting LM35 voltage to temperature in Celsius (10 mV/°C).
 * - 9f: Setting an update rate using delay().
 *
 * ## Wiring (LM35DZ, flat face toward you)
 * - Left pin  -> 5V
 * - Middle pin-> A0 (Vout)
 * - Right pin -> GND
 */

#include <Arduino.h>

/**
 * @brief Analog input pin connected to LM35 output (Vout).
 */
const uint8_t TEMP_PIN = A0;

/**
 * @brief Read an analog pin and convert the ADC value to voltage (V).
 *
 * Assumes:
 * - 10-bit ADC: 0..1023
 * - 5.0 V analog reference (default on many Arduino Uno setups)
 *
 * @param pin The analog pin to read (e.g., A0).
 * @return Voltage in volts.
 */
float readVoltage(uint8_t pin) {
  int adc = analogRead(pin);            // 0..1023
  return adc * (5.0 / 1023.0);          // volts (assuming 5V reference)
}

/**
 * @brief Convert LM35 output voltage to temperature in Celsius.
 *
 * LM35 sensitivity is 10 mV/°C = 0.010 V/°C.
 * Therefore: Temp(°C) = V / 0.010 = V * 100.
 *
 * @param v Sensor output voltage in volts.
 * @return Temperature in degrees Celsius.
 */
float voltageToC_LM35(float v) {
  return v * 100.0;
}

/**
 * @brief Arduino setup function.
 *
 * Initializes Serial communication.
 */
void setup() {
  Serial.begin(115200);
}

/**
 * @brief Arduino main loop.
 *
 * Reads ADC from LM35, converts to voltage and temperature, prints formatted output,
 * then waits to control update rate.
 *
 * Output example:
 * `V=0.253  T=25.3°C`
 *
 * @note Degree symbol is printed using UTF-8 bytes: "\\xC2\\xB0".
 */
void loop() {
  int adc  = analogRead(TEMP_PIN);      ///< Raw ADC (optional to print)
  float v  = adc * (5.0 / 1023.0);      ///< 9d: ADC -> Voltage (V)
  float tC = voltageToC_LM35(v);        ///< 9e: Voltage -> Temperature (°C)

  // Uncomment to also print the raw ADC value:
  // Serial.print("ADC=");
  // Serial.print(adc);

  Serial.print("  V=");
  Serial.print(v, 3);

  Serial.print("  T=");
  Serial.print(tC, 1);
  Serial.print("\xC2\xB0");
  Serial.println("C");

  delay(500);                           ///< 9f: Update rate (ms)
}
