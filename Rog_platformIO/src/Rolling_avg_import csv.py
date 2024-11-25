import csv
import matplotlib.pyplot as plt
from collections import deque

# Lists to store the data
rpm_values = []
r_is_values = []

# Deques to store the last 5 samples for rolling average
rpm_window = deque(maxlen=5)
r_is_window = deque(maxlen=5)

# Open the CSV file for reading
with open('Ramping_down_3.csv', 'r') as csvfile:
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

# Plot the averaged data
plt.figure(figsize=(10, 5))
plt.plot(rpm_values, r_is_values, label='R_IS (5-sample rolling average)', marker='o')
plt.xlabel('RPM')
plt.ylabel('Average R_IS Value')
plt.title('RPM vs Average R_IS Plot (5-sample rolling average)')
plt.legend()
plt.grid(True)
plt.show()
