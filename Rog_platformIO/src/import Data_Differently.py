import serial
import csv
import os
import matplotlib.pyplot as plt
from collections import deque

# Replace 'COM12' with your serial port
ser = serial.Serial('COM12', 115200, timeout=1)

# Function to get the next file number
def get_next_file_number(prefix):
    files = [f for f in os.listdir() if f.startswith(prefix)]
    if not files:
        return 1
    numbers = [int(f.split('_')[-1].split('.')[0]) for f in files]
    return max(numbers) + 1

# Function to read CSV and calculate rolling average
def read_and_calculate_rolling_avg(file_name):
    rpm_values = []
    r_is_values = []

    # Deques to store the last 5 samples for rolling average
    rpm_window = deque(maxlen=5)
    r_is_window = deque(maxlen=5)

    with open(file_name, 'r') as csvfile:
        csvreader = csv.reader(csvfile)
        next(csvreader)  # Skip the header row
        for row in csvreader:
            rpm = int(row[0])
            r_is = int(row[1])

            # Add the current sample to the rolling window
            rpm_window.append(rpm)
            r_is_window.append(r_is)

            # Calculate the rolling average if we have enough samples
            if len(rpm_window) == 5:
                avg_rpm = sum(rpm_window) / 5
                avg_r_is = sum(r_is_window) / 5
                rpm_values.append(avg_rpm)
                r_is_values.append(avg_r_is)

    return rpm_values, r_is_values

# Get the next file numbers
up_file_num = get_next_file_number("Ramping_Up_")
down_file_num = get_next_file_number("Ramping_Down_")

# Open CSV files for writing
ramping_up_file = f'Ramping_Up_{up_file_num}.csv'
ramping_down_file = f'Ramping_Down_{down_file_num}.csv'

with open(ramping_up_file, 'w', newline='') as up_file, open(ramping_down_file, 'w', newline='') as down_file:
    up_writer = csv.writer(up_file)
    down_writer = csv.writer(down_file)
    
    up_writer.writerow(['RPM', 'R_IS'])  # Write the header for ramping up file
    down_writer.writerow(['RPM', 'R_IS'])  # Write the header for ramping down file

    buffer = []
    is_ramping_up = True
    zero_rpm_count = 0  # Counter for consecutive zero RPM values
    previous_rpm = None  # Initialize previous_rpm

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            buffer.append(line)

            # Ensure we have at least two lines (RPM and R_IS)
            if len(buffer) >= 2:
                rpm_line = buffer[-2]
                r_is_line = buffer[-1]

                if rpm_line.startswith("RPM:") and r_is_line.startswith("R_IS:"):
                    try:
                        # Extract RPM and R_IS values
                        rpm = int(rpm_line.split(':')[1].strip())
                        r_is = int(r_is_line.split(':')[1].strip())

                        # Determine if ramping up or down and write to respective CSV
                        if previous_rpm is not None and rpm < previous_rpm:
                            is_ramping_up = False  # Start ramping down

                        if is_ramping_up:
                            up_writer.writerow([rpm, r_is])
                            up_file.flush()  # Ensure data is written to file
                        else:
                            down_writer.writerow([rpm, r_is])
                            down_file.flush()  # Ensure data is written to file

                        # Check for consecutive zero RPM values
                        if rpm == 0:
                            zero_rpm_count += 1
                        else:
                            zero_rpm_count = 0

                        # Exit if RPM is zero for 5 consecutive samples
                        if zero_rpm_count >= 5:
                            print("RPM has been zero for 5 consecutive samples. Plotting data...")

                            # Read and calculate rolling average data from CSV files
                            up_rpm, up_r_is = read_and_calculate_rolling_avg(ramping_up_file)
                            down_rpm, down_r_is = read_and_calculate_rolling_avg(ramping_down_file)

                            # Plot the averaged data
                            plt.figure(figsize=(10, 5))
                            plt.plot(up_rpm, up_r_is, label='Ramping Up (5-sample rolling avg)', marker='o')
                            plt.plot(down_rpm, down_r_is, label='Ramping Down (5-sample rolling avg)', marker='x')
                            plt.xlabel('RPM')
                            plt.ylabel('Average R_IS Value')
                            plt.title('RPM vs Average R_IS Plot (5-sample rolling average)')
                            plt.legend()
                            plt.grid(True)
                            plt.show()

                            break

                        previous_rpm = rpm
                    except (IndexError, ValueError) as e:
                        print(f"Error parsing lines: {rpm_line}, {r_is_line} - {e}")

                    # Clear the buffer for next set of lines
                    buffer.clear()

# Increment file number for the next run
up_file_num += 1
down_file_num += 1