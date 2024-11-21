#include <Servo.h>

// Define pins
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

Servo servo;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach servo motor
  servo.attach(servoPin);
  servo.write(0); // Close door initially
}

void loop() {
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
  delay(500);
  // Open or close the door based on distance
  if (distance < 50 && distance > 0) { // Person detected within 50cm
    servo.write(90); // Open door
    delay(3000); // Keep door open for 3 seconds
  } else {
    servo.write(0); // Close door
  }
} 
