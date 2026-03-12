from gpiozero import PWMOutputDevice
import time

class LaunchController:
    def __init__(self):
        # BTS7960 Pins: 12/13 for Top Motor, 20/21 for Bottom Motor
        self.top_r = PWMOutputDevice(12, frequency=10000)
        self.top_l = PWMOutputDevice(13, frequency=10000)
        self.bottom_r = PWMOutputDevice(20, frequency=10000)
        self.bottom_l = PWMOutputDevice(21, frequency=10000)
        
        self.current_speed = 0.0
    def ramp_to(self, target_speed, duration=30.0):
        print(f"[ACTION] Starting {duration}s ramp: {self.current_speed*100}% -> {target_speed*100}%")

        steps = int(duration * 10) 
        wait = duration / steps
        total_change = target_speed - self.current_speed
        increment = total_change / steps

        start_time = time.time()

        for i in range(1, steps + 1):
            self.current_speed += increment
            self.current_speed = max(0.0, min(self.current_speed, 1.0))

            # --- REVERSED LOGIC FOR BTS7960 ---
            # To reverse the TOP motor, we set RPWM (12) to 0 and LPWM (13) to speed
            self.top_r.value = 0
            self.top_l.value = self.current_speed
            
            # BOTTOM motor stays in original direction (RPWM active)
            self.bottom_r.value = self.current_speed
            self.bottom_l.value = 0

            if i % 50 == 0:
                elapsed = time.time() - start_time
                print(f"  [RAMPING] {elapsed:.1f}s elapsed... Power: {self.current_speed*100:.1f}%")

            time.sleep(wait)

        self.current_speed = target_speed
        print(f"[COMPLETE] Launcher is now held at {self.current_speed*100}% power.")

    def emergency_stop(self):
        # Kill all PWM signals to the BTS7960
        self.top_r.value = 0
        self.top_l.value = 0
        self.bottom_r.value = 0
        self.bottom_l.value = 0
        self.current_speed = 0
        print("[HALT] Launcher killed immediately.")
