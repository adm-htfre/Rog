#include <Wire.h>

// Define the pins for the first motor driver
const int pwmPin1 = 9;     // PWM pin for speed control (Motor 1)
const int dirPin1 = 7;     // Direction control pin (Motor 1)

// Define the pins for the second motor driver
const int pwmPin2 = 10;    // PWM pin for speed control (Motor 2)
const int dirPin2 = 5;     // Direction control pin (Motor 2)

// Variable to store the received I2C command
volatile int receivedValue = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set the direction and PWM pins as outputs for both motors
  pinMode(pwmPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  
  // Initialize I2C communication
  Wire.begin(8);                // Join I2C bus with address #8
  Wire.onReceive(receiveEvent); // Register event

  Serial.println("Setup complete. Starting motor control...");
}

void loop() {
  if (receivedValue != 0) {
    // Execute the command based on the received value
    switch (receivedValue) {
      case 1:
        moveForward(10);
        break;
      case 2:
        moveReverse(10);
        break;
      case 3:
        turnLeft(10);
        break;
      case 4:
        turnRight(10);
        break;
      case 5:
        stopMotors();
        break;
    }
    delay(200);    // Run the motor for 200 milliseconds
    stopMotors();  // Stop the motors after 200 milliseconds
    receivedValue = 0;  // Reset the command to prevent repetition
  }
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    receivedValue = Wire.read(); // Read byte as an integer
  }
}

// Function to move both motors forward
void moveForward(int speed) {
  controlMotor(pwmPin1, dirPin1, speed, true);    // Motor 1 forward
  controlMotor(pwmPin2, dirPin2, speed, false);   // Motor 2 forward
  Serial.println("Moving forward");
}

// Function to move both motors reverse
void moveReverse(int speed) {
  controlMotor(pwmPin1, dirPin1, speed, false);   // Motor 1 reverse
  controlMotor(pwmPin2, dirPin2, speed, true);    // Motor 2 reverse
  Serial.println("Moving reverse");
}

// Function to turn right
void turnRight(int speed) {
  controlMotor(pwmPin1, dirPin1, speed, false);    // Motor 1 reverse
  controlMotor(pwmPin2, dirPin2, speed, false);    // Motor 2 forward
  Serial.println("Turning right");
}

// Function to turn left
void turnLeft(int speed) {
  controlMotor(pwmPin1, dirPin1, speed, true);    // Motor 1 forward
  controlMotor(pwmPin2, dirPin2, speed, true);    // Motor 2 reverse
  Serial.println("Turning left");
}

// Function to stop both motors
void stopMotors() {
  analogWrite(pwmPin1, 0); // Stop Motor 1
  analogWrite(pwmPin2, 0); // Stop Motor 2
  Serial.println("Stopping motors");
}

// Function to control the motor speed and direction
void controlMotor(int pwmPin, int dirPin, int speed, bool direction) {
  // Set the direction
  digitalWrite(dirPin, direction);
  delay(10); // Small delay to ensure the direction change is registered

  // Set the speed (PWM value)
  analogWrite(pwmPin, speed);
  delay(10); // Small delay to ensure the speed change is registered

  // Print the current state
  Serial.print("Motor on pin ");
  Serial.print(pwmPin);
  Serial.print(" - Direction: ");
  Serial.print(direction ? "Forward" : "Reverse");
  Serial.print(", Speed: ");
  Serial.println(speed);
}
