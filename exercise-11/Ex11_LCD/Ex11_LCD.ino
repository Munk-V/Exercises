#include <LiquidCrystal_I2C.h>

const uint8_t TEMP_PIN = A0;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

float readVoltage(uint8_t pin) {
  int adc = analogRead(pin);            // 0..1023
  return adc * (5.0 / 1023.0);          // volts (default AREF ~5V)
}

float voltageToC_LM35(float v) {
  return v * 100.0;                     // LM35: 10mV/°C
}

void setup() {
  Serial.begin(115200);
  
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  float v  = readVoltage(TEMP_PIN);
  float tC = voltageToC_LM35(v);

  if(tC>=30){
    lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
    lcd.print("WARNING"); // Print the temperature
    lcd.setCursor(2, 1); //
    lcd.print("TOO HOT");
  } else if (tC<30) {
    lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
    lcd.print("Temperature: "); // Print the temperature
    lcd.setCursor(2, 1); //
    lcd.print(tC);
  } else {
    lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
    lcd.print("ERROR"); // Print the temperature
  }
  
  delay(200);
}
