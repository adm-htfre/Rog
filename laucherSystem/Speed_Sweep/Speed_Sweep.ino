#define RPWM 5
#define LPWM 6
#define buttonPin 7

bool buttonPressed = false;
const int pwmFreq = 20000;  // 10 kHz
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

  // Stop motors
  ledcWrite(pwmChannelRPWM, 0);
  ledcWrite(pwmChannelLPWM, 0);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH && !buttonPressed) {
    buttonPressed = true;  // Mark button as pressed

    // Motor control routine
    for (int i = 0; i < PWM_amount; i++) {
      ledcWrite(pwmChannelLPWM, i);
      delay(delay_time);
    }
    delay(10000);
    for (int i = PWM_amount; i >= 0; i--) {
      ledcWrite(pwmChannelLPWM, i);
      delay(delay_time);
    }
    delay(500);
    for (int i = 0; i < PWM_amount; i++) {
      ledcWrite(pwmChannelRPWM, i);
      delay(delay_time);
    }
    delay(1000);
    for (int i = PWM_amount; i >= 0; i--) {
      ledcWrite(pwmChannelRPWM, i);
      delay(delay_time);
    }
    delay(500);
  }

  if (digitalRead(buttonPin) == LOW) {
    buttonPressed = false;  // Reset button state
  }
}
