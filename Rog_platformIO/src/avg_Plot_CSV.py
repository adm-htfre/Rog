import csv
import matplotlib.pyplot as plt
from collections import defaultdict

# Lists to store the data
rpm_values = []
r_is_values = []

# Dictionary to store multiple R_IS values for each RPM
rpm_dict = defaultdict(list)

# Open the CSV file for reading
with open('Try2.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile)
    next(csvreader)  # Skip the header row
    for row in csvreader:
        rpm = int(row[0])
        r_is = int(row[1])
        rpm_dict[rpm].append(r_is)

# Function to average R_IS values for each RPM
def average_r_is(rpm_dict):
    rpm_avg_values = []
    r_is_avg_values = []

    for rpm, r_is_list in rpm_dict.items():
        avg_r_is = sum(r_is_list) / len(r_is_list)
        rpm_avg_values.append(rpm)
        r_is_avg_values.append(avg_r_is)
    
    return rpm_avg_values, r_is_avg_values

# Calculate the averaged values
rpm_avg_values, r_is_avg_values = average_r_is(rpm_dict)

# Plot the averaged data
plt.figure(figsize=(10, 5))
plt.plot(rpm_avg_values, r_is_avg_values, label='R_IS', marker='o')
plt.xlabel('RPM')
plt.ylabel('Average R_IS Value')
plt.title('RPM vs Average R_IS Plot')
plt.legend()
plt.grid(True)
plt.show()