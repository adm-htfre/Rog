import os
from curtsies import Input
from motor_driver import RobotController
from launch_motor_driver import LaunchController

# Initialize controllers
bot = RobotController()
launcher = LaunchController()

# LED Setup for Pi 5
# We track the state manually since we aren't using a class
led_state = 1 

def toggle_pi5_led(state):
    """Controls the ACT LED on Pi 5 via system calls"""
    # 1 is ON, 0 is OFF
    os.system(f"echo {state} | sudo tee /sys/class/leds/ACT/brightness > /dev/null")

# Initialize LED to OFF
toggle_pi5_led(0)

speed = 0.4 
move_duration = 0.5 

print("--- Dual Controller Active (Pi 5) ---")
print("W/A/S/D : Move Robot")
print("'r'     : Ramp Launcher up to 20%")
print("'e'     : Ramp Launcher down to 0%")
print("'l'     : Toggle Onboard LED")
print("'q'     : Quit all")

def main():
    global led_state
    with Input(keynames='curtsies') as input_generator:
        for key in input_generator:
            if key == 'w':
                bot.move_forward(duration=move_duration, speed=speed)
            elif key == 's':
                bot.move_backward(duration=move_duration, speed=speed)
            elif key == 'a':
                bot.turn_left(duration=move_duration, speed=speed)
            elif key == 'd':
                bot.turn_right(duration=move_duration, speed=speed)

            elif key == 'r':
                launcher.ramp_to(0.3)

            elif key == 'e':
                launcher.ramp_to(0.0)

            # --- Fixed LED Toggle Logic ---
            elif key == 'l':
                led_state = 1 if led_state == 0 else 0
                toggle_pi5_led(led_state)
                print(f"LED is now {'ON' if led_state else 'OFF'}")

            elif key == 'q':
                print("Stopping and exiting...")
                bot.stop()
                launcher.emergency_stop()
                toggle_pi5_led(0)
                break

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        bot.stop()
        launcher.emergency_stop()
        toggle_pi5_led(0)
