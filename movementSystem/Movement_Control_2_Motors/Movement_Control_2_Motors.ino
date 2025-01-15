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
  controlMotor(pwmPin1, dirPin1, 10, true);   // Motor 1: Set speed to maximum and direction to forward
  controlMotor(pwmPin2, dirPin2, 10, false);   // Motor 2: Set speed to maximum and direction to forward
  delay(2000);                                 // Run for 2 seconds

  controlMotor(pwmPin1, dirPin1, 10, false);  // Motor 1: Set speed to half and direction to reverse
  controlMotor(pwmPin2, dirPin2, 10, true);  // Motor 2: Set speed to half and direction to reverse
  delay(2000);                                 // Run for 2 seconds
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
