#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pins
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

// Servo motor and LCD initialization
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address if necessary (default is 0x27)

// State variable to track manual override
bool isManualControl = false;
String command = "";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo motor
  servo.attach(servoPin);
  servo.write(0); // Close door initially

  // Initialize LCD
  lcd.init();         // Use init() instead of begin()
  lcd.backlight();    // Turn on LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready");
}

void loop() {
  // Check if a manual command is received
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim(); // Remove extra spaces or newline characters

    if (command == "OPEN") {
      isManualControl = true;
      servo.write(80); // Open door
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DOOR IS OPENED");
      delay(1000); // Short delay to avoid flickering
    } else if (command == "CLOSE") {
      isManualControl = true;
      servo.write(0); // Close door
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Door IS CLOSED");
      delay(1000);
    } else if (command == "AUTO") {
      isManualControl = false; // Resume automatic control
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mode: AUTO");
      delay(1000);
    }
  }

  // Run automatic mode only if manual control is not active
  if (!isManualControl) {
    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the echo duration
    long duration = pulseIn(echoPin, HIGH);

    // Calculate distance in cm
    int distance = duration * 0.034 / 2;

    // Debug distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Update LCD with distance
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    if (distance < 100) { // Prevent overflow of display
      lcd.print(distance);
      lcd.print(" cm ");
    } else {
      lcd.print(">99 cm "); // Handle large distances
    }

    // Open or close the door based on distance
    if (distance < 50 && distance > 0) { // Person detected within 50cm
      servo.write(90); // Open door
      lcd.setCursor(0, 1);
      lcd.print("Door IS OPENED");
      delay(3000); // Keep door open for 3 seconds
    } else {
      servo.write(0); // Close door
      lcd.setCursor(0, 1);
      lcd.print("Door IS CLOSED");
    }
    delay(500);
  }
}
