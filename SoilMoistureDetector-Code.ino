#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define relay A1
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows
int sensorValue;

void setup() {
  lcd.init();           // Initialize the LCD
  lcd.backlight();      // Turn on backlight
  Serial.begin(9600);   // Begin serial communication
  delay(100);
  lcd.print("  WELCOME user ");
  delay(3000);
  // Display scrolling welcome message
  String welcomeMessage = "  Soil Moisture Detector created by Anmol and Parvathi      ");
  scrollText(welcomeMessage, 10000); // Scroll for 5 seconds
  // Display "Loading..." message
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Loading...");
  delay(5000);          // Display for 2 seconds
  lcd.clear();          // Clear the LCD for main functionality
  pinMode(relay, OUTPUT);
}

void loop() {
  sensorValue = analogRead(A0);  // Read sensor value
  Serial.println(sensorValue);  // Print value to Serial Monitor

  if (sensorValue > 900) {
    lcd.setCursor(0, 0); 
    lcd.print("Low Moisture     "); // Spaces to clear previous text
    lcd.setCursor(0, 1); 
    lcd.print("WATER SUPPLY ON   ");
    digitalWrite(relay, HIGH);
    
  } else {
    lcd.setCursor(0, 0); 
    lcd.print("The soil is wet  "); 
    lcd.setCursor(0, 1); 
    lcd.print("WATER SUPPLY OFF");
    digitalWrite(relay, LOW);
    
  }
}

// Function to scroll text from left to right
void scrollText(String text, int duration) {
  int textLength = text.length();    // Length of the text
  int displayWidth = 16;            // Width of the LCD
  unsigned long startTime = millis(); // Record the start time

  while (millis() - startTime < duration) { // Run for the specified duration
    for (int i = 0; i < textLength - displayWidth + 1; i++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(text.substring(i, i + displayWidth)); // Display a substring of the text
      delay(300); // Adjust delay for scrolling speed
    }
  }
}