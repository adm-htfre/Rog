# motor_driver.py

from gpiozero import PWMOutputDevice, OutputDevice
from time import sleep

class RobotController:
    def __init__(self):
        # Motor 1 (Left) - GPIO 18 (PWM), 17 (DIR), 27 (EN)
        self.left_pwm = PWMOutputDevice(18, frequency=2000)
        self.left_dir = OutputDevice(17)
        self.left_en = OutputDevice(27)

        # Motor 2 (Right) - GPIO 19 (PWM), 16 (DIR), 23 (EN)
        self.right_pwm = PWMOutputDevice(19, frequency=2000)
        self.right_dir = OutputDevice(16)
        self.right_en = OutputDevice(26)

    def _set_motors(self, l_speed, r_speed, l_dir, r_dir):
        self.left_en.off()
        self.right_en.off()
        self.left_dir.value = l_dir
        self.right_dir.value = r_dir
        self.left_pwm.value = l_speed
        self.right_pwm.value = r_speed

    def stop(self):
        self.left_pwm.value = 0
        self.right_pwm.value = 0
        self.left_en.off()
        self.right_en.off()

    def move_forward(self, duration=None, speed=0.5):
        self._set_motors(speed, speed, False, True)
        if duration:
            sleep(duration)
            self.stop()

    def move_backward(self, duration=None, speed=0.5):
        self._set_motors(speed, speed, True, False)
        if duration:
            sleep(duration)
            self.stop()

    def turn_left(self, duration=None, speed=0.5):
        self._set_motors(speed, speed, True, True)
        if duration:
            sleep(duration)
            self.stop()

    def turn_right(self, duration=None, speed=0.5):
        self._set_motors(speed, speed, False, False)
        if duration:
            sleep(duration)
            self.stop()
