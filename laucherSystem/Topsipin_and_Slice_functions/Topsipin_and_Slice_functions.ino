#define Bott_RPWM 3 // Was 5
#define Bott_LPWM 4 // Was 6
#define Top_RPWM 5 // Was 5
#define Top_LPWM 6 // Was 6
#define buttonPin 2 // Action Button

const int Top_R_IS = A2; //was A2 // Signal from motor connected to analog pin A0
const int Top_L_IS = A3; //Was A3 // Signal from motor connected to analog pin A1
const int Bott_R_IS = A0; //was A2 // Signal from motor connected to analog pin A0
const int Bott_L_IS = A1; //Was A3 // Signal from motor connected to analog pin A1

const int LED_PIN = 16; // Replace with the correct pin for onboard LED

bool buttonPressed = false;
bool isRampedUp = false;

const int pwmFreq = 20000;  // 20 kHz
const int Top_pwmChannelRPWM = 1;
const int Top_pwmChannelLPWM = 0;
const int Bott_pwmChannelRPWM = 0;
const int Bott_pwmChannelLPWM = 1;

const int pwmResolution = 8;

int PWM_amount = 80;
int delay_time = 1500;

void setup() {
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(Top_RPWM, INPUT_PULLDOWN); // Pull down the motors that we are not using
  pinMode(Top_LPWM, INPUT_PULLDOWN); // Use internal pull-down resistor
  pinMode(Bott_RPWM, INPUT_PULLDOWN); // Pull down the motors that we are not using
  pinMode(Bott_LPWM, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT); // Set LED_PIN as output

  Serial.begin(115200);  // Initialize serial communication

  // Configure PWM channels for Bott_RPWM and Bott_LPWM pins
  ledcSetup(Bott_pwmChannelRPWM, pwmFreq, pwmResolution);
  ledcSetup(Bott_pwmChannelLPWM, pwmFreq, pwmResolution);
  ledcAttachPin(Bott_RPWM, Bott_pwmChannelRPWM);
  ledcAttachPin(Bott_LPWM, Bott_pwmChannelLPWM);

  // Configure PWM channels for Top_RPWM and Top_LPWM pins
  ledcSetup(Top_pwmChannelRPWM, pwmFreq, pwmResolution);
  ledcSetup(Top_pwmChannelLPWM, pwmFreq, pwmResolution);
  ledcAttachPin(Top_RPWM, Top_pwmChannelRPWM);
  ledcAttachPin(Top_LPWM, Top_pwmChannelLPWM);

  // Stop motors initially
  ledcWrite(Top_pwmChannelRPWM, 0);
  ledcWrite(Top_pwmChannelLPWM, 0);
  ledcWrite(Bott_pwmChannelRPWM, 0);
  ledcWrite(Bott_pwmChannelLPWM, 0);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == HIGH && !buttonPressed) {
    buttonPressed = true;  // Mark button as pressed
    Serial.println("Button pressed");
    if (!isRampedUp) {
      digitalWrite(LED_PIN, HIGH); // Turn on the LED (blue)
      ramp_up_topspin();
      ledcWrite(Top_pwmChannelRPWM, PWM_amount); // Keep at PWM_amount
      ledcWrite(Bott_pwmChannelLPWM, PWM_amount); // Keep at PWM_amount
      digitalWrite(LED_PIN, LOW); // Turn off the LED (blue)
      isRampedUp = true;
    } else {
      digitalWrite(LED_PIN, HIGH); // Turn on the LED (blue)
      ramp_down_topspin();
      ledcWrite(Top_pwmChannelRPWM, 0); // Keep at PWM_amount
      ledcWrite(Bott_pwmChannelLPWM, 0); // Keep at PWM_amount
      digitalWrite(LED_PIN, LOW); // Turn off the LED (blue)
      isRampedUp = false;
    }
  }
  
  // Reset button state when not pressed
  if (digitalRead(buttonPin) == LOW) {
    buttonPressed = false;
  }
}

void ramp_up_topspin() {
  
  for (int i = 30; i <= PWM_amount; i++) {
    ledcWrite(Top_pwmChannelRPWM, i);
    ledcWrite(Bott_pwmChannelLPWM, i);
    Serial.print("RPM: ");
    Serial.println(i);  // Print the current RPM value

    // Read and plot Top_R_IS and Top_L_IS signals
    for (int j = 0; j < 50; j++) {
      int Top_R_IS_value = analogRead(Top_R_IS);
      int Top_L_IS_value = analogRead(Top_L_IS);
      int Bott_R_IS_value = analogRead(Bott_R_IS);
      int Bott_L_IS_value = analogRead(Bott_L_IS);
      Serial.print("RPM: ");
      Serial.println(i);
      Serial.print("\t");
      Serial.print("Top_R_IS_value: ");
      Serial.println(Top_R_IS_value);
      Serial.print("\t");
      Serial.print("Top_L_IS_value: ");
      Serial.println(Top_L_IS_value);
      Serial.print("\t");
      Serial.print("Bott_R_IS_value: ");
      Serial.println(Bott_R_IS_value);
      Serial.print("\t");
      Serial.print("Bott_L_IS_value: ");
      Serial.println(Bott_L_IS_value);
      Serial.print("\t");
    }

    delay(200);  // Add a delay of 200 milliseconds
  }

}

void ramp_down_topspin() {
  digitalWrite(LED_PIN, HIGH); // Turn on the LED (blue)
  for (int i = PWM_amount; i >= 0; i--) {
    ledcWrite(Top_pwmChannelRPWM, i);
    ledcWrite(Bott_pwmChannelLPWM, i);
    Serial.print("RPM: ");
    Serial.println(i);  // Print the current RPM value

    // Read and plot Top_R_IS and Top_L_IS signals
    for (int j = 0; j < 200; j++) {
      int Top_R_IS_value = analogRead(Top_R_IS);
      int Top_L_IS_value = analogRead(Top_L_IS);
      int Bott_R_IS_value = analogRead(Bott_R_IS);
      int Bott_L_IS_value = analogRead(Bott_L_IS);
      Serial.print("RPM: ");
      Serial.println(i);
      Serial.print("\t");
      Serial.print("Top_R_IS_value: ");
      Serial.println(Top_R_IS_value);
      Serial.print("\t");
      Serial.print("Top_L_IS_value: ");
      Serial.println(Top_L_IS_value);
      Serial.print("\t");
      Serial.print("Bott_R_IS_value: ");
      Serial.println(Bott_R_IS_value);
      Serial.print("\t");
      Serial.print("Bott_L_IS_value: ");
      Serial.println(Bott_L_IS_value);
      Serial.print("\t");
    }

    delay(200);  // Add a delay of 200 milliseconds
  }
  ledcWrite(Top_pwmChannelRPWM, 0); // Keep at PWM_amount
  ledcWrite(Bott_pwmChannelLPWM, 0); // Keep at PWM_amount
  digitalWrite(LED_PIN, LOW); // Turn off the LED (blue)
}