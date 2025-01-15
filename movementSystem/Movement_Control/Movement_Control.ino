// Define the pins for the first motor driver
const int pwmPin1 = 9;     // PWM pin for speed control (Motor 1)
const int dirPin1 = 7;     // Direction control pin (Motor 1)

// Define the pins for the second motor driver
const int pwmPin2 = 10;    // PWM pin for speed control (Motor 2)
const int dirPin2 = 5;     // Direction control pin (Motor 2)

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set the direction and PWM pins as outputs for both motors
  pinMode(pwmPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  
  Serial.println("Setup complete. Starting motor control...");
}

void loop() {
  // Control the motors' speed and direction
  int delay1 = 5000;
  moveForward(10);    // Move both motors forward at speed 10 PWM
  delay(delay1);        // Run for 2 seconds

  moveReverse(10);    // Move both motors reverse at speed 10 PWM
  delay(delay1);        // Run for 2 seconds
  
  turnRight(10);      // Turn right at speed 10 PWM
  delay(delay1);        // Turn for 2 seconds

  turnLeft(10);       // Turn left at speed 10 PWM
  delay(delay1);        // Turn for 2 seconds
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
