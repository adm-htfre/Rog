#define RPWM 5
#define LPWM 6
#define buttonPin 7

bool buttonPressed = false;
bool isRampedUp = false;

const int pwmFreq = 20000;  // 20 kHz
const int pwmChannelRPWM = 0;
const int pwmChannelLPWM = 1;
const int pwmResolution = 8;

int PWM_amount = 100;
int delay_time = 500;

void setup() {
  pinMode(buttonPin, INPUT_PULLDOWN);  // Use internal pull-down resistor

  // Configure PWM channels for RPWM and LPWM pins
  ledcSetup(pwmChannelRPWM, pwmFreq, pwmResolution);
  ledcSetup(pwmChannelLPWM, pwmFreq, pwmResolution);

  ledcAttachPin(RPWM, pwmChannelRPWM);
  ledcAttachPin(LPWM, pwmChannelLPWM);

  // Stop motors initially
  ledcWrite(pwmChannelRPWM, 0);
  ledcWrite(pwmChannelLPWM, 0);+

  
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == HIGH && !buttonPressed) {
    buttonPressed = true;  // Mark button as pressed
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
  for (int i = 0; i <= PWM_amount; i++) {
    ledcWrite(pwmChannelLPWM, i);
    delay(delay_time);
  }
  ledcWrite(pwmChannelLPWM, PWM_amount); // Keep at PWM_amount
}

void ramp_down_topspin() {
  for (int i = PWM_amount; i >= 0; i--) {
    ledcWrite(pwmChannelLPWM, i);
    delay(delay_time);
  }
  ledcWrite(pwmChannelLPWM, 0); // Stop the motor
}
