#define RPWM 3// Was 5
#define LPWM 4// Was 6

#define Top_RPWM 5 // Was 5
#define Top_LPWM 6 // Was 6
#define buttonPin 2

const int Top_R_IS = A2; //was A2 // Signal from motor connected to analog pin A0
const int Top_L_IS = A3; //Was A3 // Signal from motor connected to analog pin A1
const int R_IS = A0; //was A2 // Signal from motor connected to analog pin A0
const int L_IS = A1; //Was A3 // Signal from motor connected to analog pin A1

bool buttonPressed = false;
bool isRampedUp = false;

const int pwmFreq = 20000;  // 20 kHz
const int pwmChannelRPWM = 1;
const int pwmChannelLPWM = 0;
const int pwmResolution = 8;

int PWM_amount = 100;
int delay_time = 1500;

void setup() {
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(Top_RPWM, INPUT_PULLDOWN); //Pull down the motors that we are not using
  pinMode(Top_LPWM, INPUT_PULLDOWN);  // Use internal pull-down resistor
  pinMode(RPWM, INPUT_PULLDOWN); //Pull down the motors that we are not using
  pinMode(LPWM, INPUT_PULLDOWN);
  Serial.begin(115200);  // Initialize serial communication

  // Configure PWM channels for RPWM and LPWM pins
  ledcSetup(pwmChannelRPWM, pwmFreq, pwmResolution);
  ledcSetup(pwmChannelLPWM, pwmFreq, pwmResolution);

  ledcAttachPin(RPWM, pwmChannelRPWM);
  ledcAttachPin(LPWM, pwmChannelLPWM);

  // Stop motors initially
  ledcWrite(pwmChannelRPWM, 0);
  ledcWrite(pwmChannelLPWM, 0);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == HIGH && !buttonPressed) {
    buttonPressed = true;  // Mark button as pressed
    Serial.println("Button pressed");
    if (!isRampedUp) {
      ramp_up_topspin();
      isRampedUp = true;
    } else {
      ramp_down_topspin();
      isRampedUp = false;
    }
  }
  
  // Reset button state when not pressed
  if (digitalRead(buttonPin) == LOW) {
    buttonPressed = false;
  }
}

void ramp_up_topspin() {
  for (int i = 30; i <= PWM_amount; i++/*i -= 10*/) {
    ledcWrite(pwmChannelRPWM, i);
    Serial.print("RPM: ");
    Serial.println(i);  // Print the current RPM value

    // Read and plot R_IS and L_IS signals 10 times
    for (int j = 0; j < 50; j++) {
      int R_IS_value = analogRead(R_IS);
      int L_IS_value = analogRead(L_IS);
      Serial.print("RPM: ");
      Serial.println(i);
      // Serial.print("\t");
      Serial.print("R_IS: ");
      Serial.println(R_IS_value);
      // Serial.print("\t");
      // Serial.print("L_IS: ");
      // Serial.println(L_IS_value);
    }

    delay(200);  // Add a delay of 400 milliseconds
  }
  ledcWrite(pwmChannelRPWM, PWM_amount); // Keep at PWM_amount
}

void ramp_down_topspin() {
  for (int i = PWM_amount; i >= 0; i-- /*i -= 10*/) {
    ledcWrite(pwmChannelRPWM, i);
    Serial.print("RPM: ");
    Serial.println(i);  // Print the current RPM value

    // Read and plot R_IS and L_IS signals 10 times
    for (int j = 0; j < 200; j++) {
      int R_IS_value = analogRead(R_IS);
      int L_IS_value = analogRead(L_IS);
      Serial.print("RPM: ");
      Serial.println(i);
      // Serial.print("\t");
      Serial.print("R_IS: ");
      Serial.println(R_IS_value);
      // Serial.print("\t");
      // Serial.print("L_IS: ");
      // Serial.println(L_IS_value);
    }

    delay(200);  // Add a delay of 400 milliseconds
  }
  ledcWrite(pwmChannelRPWM, 0); // Stop the motor
}