/*
  Exercise 10 - LM35DZ + 3 LEDs

  LM35 wiring (flat face toward you):
  Left  -> 5V
  Middle-> A0 (Vout)
  Right -> GND

  LED wiring:
  Each LED anode -> Arduino pin THROUGH resistor (60-220 ohm)
  Each LED cathode -> GND

  Behavior:
  Green  = LOW temperature
  Yellow = MEDIUM temperature
  Red    = HIGH temperature
*/

const uint8_t TEMP_PIN = A0;

const uint8_t GREEN_PIN  = 6;
const uint8_t YELLOW_PIN = 7;
const uint8_t RED_PIN    = 8;

// ======= SET THESE using your measured temps (10a) =======
// <= T_LOW_MAX  -> Green
// >= T_HIGH_MIN -> Red
// between       -> Yellow
float T_LOW_MAX  = 23.0;   // example
float T_HIGH_MIN = 30.0;   // example
// =========================================================

float readVoltage(uint8_t pin) {
  int adc = analogRead(pin);            // 0..1023
  return adc * (5.0 / 1023.0);          // volts (default AREF ~5V)
}

float voltageToC_LM35(float v) {
  return v * 100.0;                     // LM35: 10mV/°C
}

void setLEDs(bool g, bool y, bool r) {
  digitalWrite(GREEN_PIN,  g ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, y ? HIGH : LOW);
  digitalWrite(RED_PIN,    r ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  setLEDs(false, false, false);
}

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
