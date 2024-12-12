#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the I2C address if needed

// Keypad setup
const byte ROWS = 4; // 4 rows
const byte COLS = 4; // 4 columns

// Define the keys on the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};    // Connect to row pins of the keypad
byte colPins[COLS] = {8, 9, 10, 11};  // Connect to column pins of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Set your correct code here
String correctCode = "11";
String inputCode = ""; // Store the user input

// LED pins
const int ledGrantedPin = 13; // Pin for "Access Granted" LED
const int ledDeniedPin = 12;  // Pin for "Access Denied" LED

// Servo motor
Servo motor;
const int motorPin = 6; // Servo motor control pin

void setup() {
  // Initialize Serial, LCD, LEDs, and motor
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight(); // Turn on the LCD backlight
  pinMode(ledGrantedPin, OUTPUT);
  pinMode(ledDeniedPin, OUTPUT);
  motor.attach(motorPin);

  // Ensure LEDs are off and motor is in initial position
  digitalWrite(ledGrantedPin, LOW);
  digitalWrite(ledDeniedPin, LOW);
  motor.write(0); // Set motor to initial position (0 degrees)

  lcd.setCursor(0, 0);
  lcd.print("Enter Code:");
  delay(1000);
}

void loop() {
  char key = keypad.getKey(); // Get the pressed key

  // Check for serial input
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'S') { // If the 'S' command is received
      String currentTime = String(millis() / 1000); // Time in seconds since startup
      grantAccess(currentTime);  // Pass time to the grantAccess function
    }
  }

  if (key) { // If a key is pressed
    if (key == '#') { // '#' is the "Enter" key
      lcd.clear();
      String currentTime = String(millis() / 1000); // Time in seconds since startup
      if (inputCode == correctCode) { // Check if the code is correct
        grantAccess(currentTime); // Pass time to the grantAccess function
      } else {
        denyAccess(currentTime); // Pass time to the denyAccess function
      }
      delay(2000); // Display the result for 2 seconds
      inputCode = ""; // Reset the input code
      lcd.clear();
      lcd.print("Enter Code:");
    } else if (key == '*') { // '*' is the "Clear" key
      inputCode = ""; // Clear the input code
      lcd.clear();
      lcd.print("Enter Code:");
    } else {
      inputCode += key; // Append the key to the input code
      lcd.setCursor(0, 1); // Move to the second row
      lcd.print(inputCode); // Display the entered code
    }
    Serial.println(inputCode); // Debugging: Show the entered code
  }
}

void grantAccess(String time) {
  lcd.setCursor(0, 0);
  lcd.print("Access Granted");
  Serial.println("Access Granted");

  // Send data to the Qt application (time, entered code, granted status)
  Serial.print("Time: ");
  Serial.print(time);
  Serial.print(", Code: ");
  Serial.print(inputCode);
  Serial.println(", Status: Granted");

  // Light up the "Access Granted" LED and open the motor
  digitalWrite(ledGrantedPin, HIGH);
  motor.write(90); // Move motor to open position (90 degrees)

  // Display countdown timer on LCD
  for (int i = 10; i >= 0; i--) {
    lcd.setCursor(0, 1);
    lcd.print("Closing in: ");
    lcd.print(i);
    lcd.print("s  "); // Clear extra digits
    delay(1000);
  }

  // Return motor to initial position and turn off LED
  motor.write(0); // Close the motor
  digitalWrite(ledGrantedPin, LOW);
}

void denyAccess(String time) {
  lcd.setCursor(0, 0);
  lcd.print("Access Denied");
  Serial.println("Access Denied");

  // Send data to the Qt application (time, entered code, denied status)
  Serial.print("Time: ");
  Serial.print(time);
  Serial.print(", Code: ");
  Serial.print(inputCode);
  Serial.println(", Status: Denied");

  // Light up the "Access Denied" LED
  digitalWrite(ledDeniedPin, HIGH);
  delay(2000); // Keep the LED on for 2 seconds
  digitalWrite(ledDeniedPin, LOW); // Turn off the LED
}
void sendDataToQt(String code, String status) {
    String data = "Code: " + code + ", Status: " + status;
    Serial.println(data);  // Send formatted data over serial
}
