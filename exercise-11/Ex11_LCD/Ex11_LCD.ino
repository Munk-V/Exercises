/**
 * @file EX11_LM35_LCD_Warning.ino
 * @brief Exercise 11: Show LM35DZ temperature on a 16x2 I2C LCD and display a warning if too hot.
 *
 * The sketch reads the LM35DZ analog output on A0, converts it to voltage and then to temperature
 * in °C (LM35 sensitivity: 10 mV/°C). The temperature is shown on a 16x2 I2C LCD.
 *
 * If the temperature is >= 30°C, the LCD displays a warning message.
 *
 * ## Wiring
 * ### LM35DZ (flat face toward you)
 * - Left pin  -> 5V
 * - Middle pin-> A0 (Vout)
 * - Right pin -> GND
 *
 * ### I2C LCD (typical)
 * - VCC -> 5V
 * - GND -> GND
 * - SDA -> A4 (Arduino Uno)
 * - SCL -> A5 (Arduino Uno)
 *
 * @note The LCD I2C address is set to 0x27 (common). Some modules use 0x3F instead.
 */

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

/** @brief Analog input pin connected to LM35 output (Vout). */
const uint8_t TEMP_PIN = A0;

/**
 * @brief LCD object for a 16x2 I2C display.
 *
 * Constructor parameters: (I2C address, columns, rows).
 */
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

/**
 * @brief Convert an ADC reading from an analog pin into voltage (V).
 *
 * Assumes:
 * - 10-bit ADC: 0..1023
 * - 5.0 V analog reference (default on many Arduino Uno setups)
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
 * @brief Arduino setup function.
 *
 * Initializes Serial output (optional debug) and the I2C LCD.
 */
void setup() {
  Serial.begin(115200);

  lcd.init();        ///< Initialize the LCD
  lcd.backlight();   ///< Turn on LCD backlight
}

/**
 * @brief Arduino main loop.
 *
 * Reads the LM35 temperature and shows it on the LCD.
 * - If tC >= 30°C: displays "WARNING" and "TOO HOT"
 * - Else: displays "Temperature:" and the numeric temperature
 *
 * @note The LCD is cleared every loop; this may cause flicker. A more advanced approach
 *       is to only update when the displayed text changes.
 */
void loop() {
  lcd.clear();

  float v  = readVoltage(TEMP_PIN);
  float tC = voltageToC_LM35(v);

  if (tC >= 30) {
    lcd.setCursor(2, 0);     // 3rd column, 1st row
    lcd.print("WARNING");
    lcd.setCursor(2, 1);     // 3rd column, 2nd row
    lcd.print("TOO HOT");
  } else if (tC < 30) {
    lcd.setCursor(2, 0);     // 3rd column, 1st row
    lcd.print("Temperature:");
    lcd.setCursor(2, 1);     // 3rd column, 2nd row
    lcd.print
