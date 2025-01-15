// Define the pins for the motor driver
const int pwmPin = 9;     // PWM pin for speed control
const int dirPin = 8;     // Direction control pin

void setup() {
  // Set the direction and PWM pins as outputs
  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Control the motor speed and direction
  Serial.println("Direction Low");
  Serial.println();
  digitalWrite(dirPin, LOW);
  analogWrite(pwmPin, 128);
  delay(2000);  
  
  Serial.println("Direction High");
  Serial.println();
  digitalWrite(dirPin, HIGH);
  analogWrite(pwmPin, 128);
  delay(2000);  
  }

