from gpiozero import PWMOutputDevice
import time

class LaunchController:
    def __init__(self):
        # Initializing with a higher frequency to prevent motor humming at low speeds
        self.top_r = PWMOutputDevice(12, frequency=10000)
        self.top_l = PWMOutputDevice(13, frequency=10000)
        self.bottom_r = PWMOutputDevice(20, frequency=10000)
        self.bottom_l = PWMOutputDevice(21, frequency=10000)
        
        self.current_speed = 0.0
        print("[READY] Launcher initialized. Ready for 30s transitions.")

    def ramp_to(self, target_speed, duration=30.0):
        """
        Smoothly transitions motor speed over a long duration.
        Default duration is now 30 seconds.
        """
        print(f"[ACTION] Starting {duration}s ramp: {self.current_speed*100}% -> {target_speed*100}%")
        
        # Increase steps for a smoother 30-second transition (10 updates per second)
        steps = int(duration * 10) 
        wait = duration / steps
        total_change = target_speed - self.current_speed
        increment = total_change / steps
        
        start_time = time.time()

        for i in range(1, steps + 1):
            self.current_speed += increment
            
            # Safety clipping
            self.current_speed = max(0.0, min(self.current_speed, 1.0))
            
            # Apply to hardware
            self.top_r.value = self.current_speed
            self.bottom_r.value = self.current_speed
            self.top_l.value = 0
            self.bottom_l.value = 0
            
            # Print progress every 5 seconds so you know it hasn't frozen
            if i % 50 == 0:
                elapsed = time.time() - start_time
                print(f"  [RAMPING] {elapsed:.1f}s elapsed... Power: {self.current_speed*100:.1f}%")
            
            time.sleep(wait)
            
        # Final set for accuracy
        self.current_speed = target_speed
        self.top_r.value = self.current_speed
        self.bottom_r.value = self.current_speed
        print(f"[COMPLETE] Launcher is now held at {self.current_speed*100}% power.")

    def emergency_stop(self):
        self.top_r.value = 0
        self.bottom_r.value = 0
        self.top_l.value = 0
        self.bottom_l.value = 0
        self.current_speed = 0
        print("[HALT] Launcher killed immediately.")
