from curtsies import Input
from motor_driver import RobotController

bot = RobotController()
speed = 0.4  # Adjust as needed
move_duration = 1.0  # Set your 2-second timer here

print(f"Controls: W/A/S/D. Each press moves for {move_duration}s. Press 'Q' to quit.")

def main():
    with Input(keynames='curtsies') as input_generator:
        for key in input_generator:
            if key == 'w':
                print("Moving forward...")
                bot.move_forward(duration=move_duration, speed=speed)
            
            elif key == 's':
                print("Moving backward...")
                bot.move_backward(duration=move_duration, speed=speed)
            
            elif key == 'a':
                print("Turning left...")
                bot.turn_left(duration=move_duration, speed=speed)
            
            elif key == 'd':
                print("Turning right...")
                bot.turn_right(duration=move_duration, speed=speed)
            
            elif key == 'q':
                bot.stop()
                print("Exiting...")
                break
            
            # Note: We removed the 'None' stop logic so the timer can finish
            print("Action complete. Waiting for next command...")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        bot.stop()
