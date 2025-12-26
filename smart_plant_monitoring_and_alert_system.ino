#include <Bonezegei_DHT11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int red_led = 9;   // PWM Pin
const int blue_led = 10; // PWM Pin
const int green_led = 11;  // PWM Pin

const int buzzer_pin = 13;

const int soil_pin_a = A0;
const int soil_power_d = 8;

const int dht_pin_a = A1;
#define DHTTYPE DHT11
DHT dht(dht_pin_a, DHTTYPE);

const int DRY_VALUE = 590;
const int WET_VALUE = 240; // Raw value from analogRead() in water

// Define your alert thresholds in percentage
const int DRY_THRESHOLD = 35; // Below 35% is "Too Dry"
const int WET_THRESHOLD = 65; // Above 65% is "Too Wet"

// --- Global Variables ---
float g_temperature = 0.0;
float g_humidity = 0.0;
int g_soil_percent = 0;
String g_soil_status = "Booting";

// =============================================================
//  SETUP: Runs once at the beginning
// =============================================================
void setup() {
  Serial.begin(115200);

  // Initialize Pins
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  // --- Soil Sensor Pin Fix ---
  // A0 (soil_pin_a) must be an INPUT to read data
  pinMode(soil_pin_a, INPUT);
  // D8 (soil_power_d) must be an OUTPUT to supply power
  pinMode(soil_power_d, OUTPUT);
  // Start with the sensor powered OFF
  digitalWrite(soil_power_d, LOW);

  // Initialize Sensors & Display
  dht.begin();
  lcd.init();
  lcd.backlight();

  // --- Startup Sequence (Moved from loop) ---
  lcd.setCursor(1, 0);
  lcd.print("Hello, Allyana!");
  delay(1500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Starting system");
  
  // Play startup sound
  tone(buzzer_pin, 1000, 150);
  delay(200);
  tone(buzzer_pin, 1200, 150);
  delay(1000); // Wait for sensors to stabilize

  lcd.clear();
}

// =============================================================
//  LOOP: Runs forever
// =============================================================
void loop() {
  // 1. Read all sensor data
  readSoil();
  bool dhtOk = readTempAndHumid(); // Check if DHT read was successful

  // 2. Process data and determine status
  g_soil_status = getSoilStatus(g_soil_percent);

  // 3. Trigger alerts based on status
  updateAlerts(g_soil_status);

  // 4. Display all information on the LCD
  updateDisplay(dhtOk);

  // Wait 2 seconds before the next reading (required for DHT11)
  delay(2000);
}

// =============================================================
//  Helper Functions
// =============================================================

/**
 * @brief Reads the soil sensor and updates the global soil percentage.
 * Powers the sensor on/off to prevent corrosion.
 */
void readSoil() {
  digitalWrite(soil_power_d, HIGH); // Turn sensor ON
  delay(10); // Wait for power to stabilize
  
  // --- Syntax Fix: analogPin() -> analogRead() ---
  int soilRaw = analogRead(soil_pin_a);
  
  digitalWrite(soil_power_d, LOW);  // Turn sensor OFF

  // Map the raw value to a 0-100% scale
  // Note: Uses DRY_VALUE and WET_VALUE from calibration
  g_soil_percent = map(soilRaw, DRY_VALUE, WET_VALUE, 0, 100);
  
  // Constrain the value just in case it goes out of bounds
  g_soil_percent = constrain(g_soil_percent, 0, 100);

  Serial.print("Soil Raw: "); Serial.print(soilRaw);
  Serial.print(" | Soil Percent: "); Serial.println(g_soil_percent);
}

/**
 * @brief Reads temperature and humidity, updates global variables.
 * @return bool - true if read was successful, false if failed.
 */
bool readTempAndHumid() {
  // --- Logic Fix: Replaced analogRead with proper DHT library ---
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Reads in Celsius

  // Check if any reads failed (e.g., sensor not connected)
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }
  
  // Update globals
  g_temperature = t;
  g_humidity = h;
  return true;
}

/**
 * @brief Returns a String status based on soil percentage.
 */
String getSoilStatus(int percent) {
  if (percent < DRY_THRESHOLD) {
    return "Dry";
  } else if (percent <= WET_THRESHOLD) {
    return "Normal";
  } else {
    return "Wet";
  }
}

/**
 * @brief Sets all alerts (LED and Buzzer) based on soil status.
 */
void updateAlerts(String status) {
  if (status == "Dry") {
    // Set LED to Red (User pins: R=9, B=10, G=11)
    setColor(255, 0, 0); 
    // Sound alert (low pitch)
    tone(buzzer_pin, 800, 200); 
  } 
  else if (status == "Normal") {
    // Set LED to Green
    setColor(0, 255, 0); 
    // No sound
    noTone(buzzer_pin);
  } 
  else { // "Wet"
    // Set LED to Blue
    setColor(0, 0, 255); 
    // Sound alert (high pitch)
    tone(buzzer_pin, 1200, 200); 
  }
}

/**
 * @brief Updates the 16x2 LCD display with all data.
 */
void updateDisplay(bool dhtConnected) {
  lcd.clear();

  // --- Line 1: Temperature & Humidity ---
  lcd.setCursor(0, 0);
  if (dhtConnected) {
    lcd.print("T:");
    lcd.print(g_temperature, 1); // 1 decimal place
    lcd.print("C H:");
    lcd.print(g_humidity, 1); // 1 decimal place
    lcd.print("%");
  } else {
    // This makes it functional even without the DHT11
    lcd.print("DHT11 Error");
  }

  // --- Line 2: Soil Status & Percentage ---
  lcd.setCursor(0, 1);
  lcd.print("Soil: ");
  lcd.print(g_soil_status);
  lcd.print(" (");
  lcd.print(g_soil_percent);
  lcd.print("%)");
}

/**
 * @brief Sets the color of the RGB LED using analogWrite (PWM).
 * Uses your pin definitions: R=9, B=10, G=11.
 * @param r Red value (0-255)
 * @param g Green value (0-255)
 * @param b Blue value (0-255)
 */
void setColor(int r, int g, int b) {
  // --- Implementation Fix ---
  // Using analogWrite for PWM color mixing, as pins 9, 10, 11 support it.
  // Note: Your pins are R=9, G=11, B=10
  analogWrite(red_led, r);
  analogWrite(green_led, g);
  analogWrite(blue_led, b);
}