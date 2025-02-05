#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PH_SENSOR_PIN A0  // pH sensor analog input pin
#define CALIBRATION_OFFSET 0.00  // Adjust this after calibration

// Initialize the LCD (address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);
    
    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("pH Sensor Ready");

    Serial.println("pH Sensor Calibration Started...");
}

void loop() {
    int sensorValue = analogRead(PH_SENSOR_PIN);  // Read raw sensor value
    float voltage = sensorValue * (5.0 / 1023.0);  // Convert to voltage
    float pH = 2 * voltage + CALIBRATION_OFFSET;  // Convert to pH (adjust formula)

    // Print values to Serial Monitor
    Serial.print("Raw Value: ");
    Serial.print(sensorValue);
    Serial.print(" | Voltage: ");
    Serial.print(voltage, 3);
    Serial.print("V | pH Value: ");
    Serial.println(pH, 2);

    // Display pH value on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("pH Value:");
    lcd.setCursor(0, 1);
    lcd.print(pH, 2);

    delay(1000);  // Wait for 1 second
}
