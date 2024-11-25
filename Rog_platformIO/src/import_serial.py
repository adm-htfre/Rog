import serial
import matplotlib.pyplot as plt
import csv
import time

# Replace 'COM12' with your serial port
ser = serial.Serial('COM12', 9600, timeout=1)

# Lists to store the data
rpm_values = []
r_is_values = []

plt.ion()  # Turn on interactive mode
fig, ax = plt.subplots()
line1, = ax.plot(rpm_values, r_is_values, label='R_IS')
ax.set_xlabel('RPM')
ax.set_ylabel('R_IS Value')
ax.legend()

# Open a CSV file for writing
with open('serial_data.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(['RPM', 'R_IS'])  # Write the header

    def update_plot():
        line1.set_xdata(rpm_values)
        line1.set_ydata(r_is_values)
        ax.relim()
        ax.autoscale_view()
        plt.draw()
        plt.pause(0.01)

    while True:
        if ser.in_waiting > 0:
            rpm_line = ser.readline().decode('utf-8').strip()
            r_is_line = ser.readline().decode('utf-8').strip()
            print(rpm_line)
            print(r_is_line)

            if rpm_line.startswith("RPM:") and r_is_line.startswith("R_IS:"):
                try:
                    # Extract RPM and R_IS values
                    rpm = int(rpm_line.split(':')[1].strip())
                    r_is = int(r_is_line.split(':')[1].strip())

                    rpm_values.append(rpm)
                    r_is_values.append(r_is)

                    # Write to CSV
                    csvwriter.writerow([rpm, r_is])
                    
                    # Update the plot
                    update_plot()
                except (IndexError, ValueError) as e:
                    print(f"Error parsing lines: {rpm_line}, {r_is_line} - {e}")
        
        time.sleep(0.1)  # Small delay