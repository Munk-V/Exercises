/**
 * @file EX10_LM35_3LEDs.ino
 * @brief Exercise 10: LM35DZ temperature sensor with 3 LEDs indicating LOW/MEDIUM/HIGH temperature.
 *
 * This sketch reads the LM35DZ analog output, converts it to temperature in °C, and then lights
 * one of three LEDs:
 * - Green  = LOW temperature
 * - Yellow = MEDIUM temperature
 * - Red    = HIGH temperature
 *
 * ## Wiring
 * ### LM35DZ (flat face toward you)
 * - Left pin  -> 5V
 * - Middle pin-> A0 (Vout)
 * - Right pin -> GND
 *
 * ### LEDs
 * - Each LED anode -> Arduino digital pin THROUGH a resistor (60–220 Ω)
 * - Each LED cathode -> GND
 *
 * ## Thresholds
 * - tC <= T_LOW_MAX   => Green
 * - tC >= T_HIGH_MIN  => Red
 * - otherwise         => Yellow
 */

#include <Arduino.h>

/** @brief Analog pin connected to LM35 output (Vout). */
const uint8_t TEMP_PIN = A0;

/** @brief Digital pin for the GREEN LED (LOW temperature). */
const uint8_t GREEN_PIN  = 6;
/** @brief Digital pin for the YELLOW LED (MEDIUM temperature). */
const uint8_t YELLOW_PIN = 7;
/** @brief Digital pin for the RED LED (HIGH temperature). */
const uint8_t RED_PIN    = 8;

// ======= SET THESE using your measured temps (Exercise 10a) =======
/**
 * @brief Maximum temperature considered "LOW".
 *
 * If tC <= T_LOW_MAX, the GREEN LED is turned on.
 */
float T_LOW_MAX  = 23.0;   // example

/**
 * @brief Minimum temperature considered "HIGH".
 *
 * If tC >= T_HIGH_MIN, the RED LED is turned on.
 */
float T_HIGH_MIN = 30.0;   // example
// ==================================================================

/**
 * @brief Read an analog pin and convert ADC reading to voltage (V).
 *
 * Assumes:
 * - 10-bit ADC: 0..1023
 * - 5.0 V reference (default AREF on many Arduino Uno setups)
 *
 * @param pin Analog pin to read (e.g., A0).
 * @return Voltage in volts.
 */
float readVoltage(uint8_t pin) {
  int adc = analogRead(pin);            // 0..1023
  return adc * (5.0 / 1023.0);          // volts (default AREF ~5V)
}

/**
 * @brief Convert LM35 output voltage to temperature in Celsius.
 *
 * LM35 sensitivity: 10 mV/°C = 0.010 V/°C.
 * Therefore: Temp(°C) = V / 0.010 = V * 100.
 *
 * @param v Voltage in volts.
 * @return Temperature in degrees Celsius.
 */
float voltageToC_LM35(float v) {
  return v * 100.0;                     // LM35: 10mV/°C
}

/**
 * @brief Set the three LEDs in one call.
 *
 * @param g True to turn GREEN LED on, false to turn it off.
 * @param y True to turn YELLOW LED on, false to turn it off.
 * @param r True to turn RED LED on, false to turn it off.
 */
void setLEDs(bool g, bool y, bool r) {
  digitalWrite(GREEN_PIN,  g ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, y ? HIGH : LOW);
  digitalWrite(RED_PIN,    r ? HIGH : LOW);
}

/**
 * @brief Arduino setup function.
 *
 * Initializes Serial output and configures LED pins as outputs.
 */
void setup() {
  Serial.begin(115200);

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  setLEDs(false, false, false);
}

/**
 * @brief Arduino main loop.
 *
 * Reads temperature from LM35DZ, applies threshold logic, updates LEDs,
 * prints voltage and temperature to Serial Monitor, then waits 200 ms.
 *
 * Output example:
 * `V=0.251  T=25.1°C`
 *
 * @note Degree symbol is printed using UTF-8 bytes: "\\xC2\\xB0".
 */
void loop() {
  float v  = readVoltage(TEMP_PIN);
  float tC = voltageToC_LM35(v);

  // LED logic
  if (tC <= T_LOW_MAX) {
    setLEDs(true, false, false);        // low -> green
  } else if (tC >= T_HIGH_MIN) {
    setLEDs(false, false, true);        // high -> red
  } else {
    setLEDs(false, true, false);        // medium -> yellow
  }

  // Debug print (Serial Monitor friendly)
  Serial.print("V=");
  Serial.print(v, 3);
  Serial.print("  T=");
  Serial.print(tC, 1);
  Serial.print("\xC2\xB0");
  Serial.println("C");

  delay(200);
}
