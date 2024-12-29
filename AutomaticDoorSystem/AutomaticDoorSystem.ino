#include <Servo.h> // Use ESP32Servo library for ESP32

// Pin definitions
const int trigPin = 10;
const int echoPin = 11;

// Variables
long duration;
int distance;

bool doorOpen = false;   
const int distanceThreshold = 20; // Distance threshold for door activation (in cm)

Servo doorServo; // Servo to simulate the door mechanism

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Start serial communication
  doorServo.attach(12); // Attach the servo motor to pin 12
  doorServo.write(0);   // Initially keep the door closed (0°)
}

void loop() {
  distance = calculateDistance(); // Get the distance from the ultrasonic sensor
  
   if (distance > 0 && distance <= distanceThreshold) { // Object detected within range
    if (!doorOpen) { // Only open the door if it is currently closed
      Serial.println("Object detected! Opening door.");
      openDoor();    // Open the door
      doorOpen = true;
    } else {
      Serial.println("Object detected, door is already open.");
    }
  } else { // No object detected or out of range
    if (doorOpen) { // Only close the door if it is currently open
      Serial.println("No object detected. Closing door.");
      closeDoor();   // Close the door
      doorOpen = false;
    } else {
      Serial.println("No object detected, door is already closed.");
    }
  }
   delay(500); // Small delay before the next measurement
}

// Function to calculate distance using ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time for the echo to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2; // Speed of sound = 343 m/s
  return distance;
}

// Function to open the door
void openDoor() {
  for (int i = 0; i <= 90; i++) { // Move servo from 0° to 90°
    doorServo.write(i);
    delay(20);
  }
}

// Function to close the door
void closeDoor() {
  for (int i = 90; i >= 0; i--) { // Move servo back from 90° to 0°
    doorServo.write(i);
    delay(20);
  }
}
