import csv
import matplotlib.pyplot as plt

# Lists to store the data
rpm_values = []
r_is_values = []

# Open the CSV file for reading
with open('Try2.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile)
    next(csvreader)  # Skip the header row
    for row in csvreader:
        rpm_values.append(int(row[0]))
        r_is_values.append(int(row[1]))

# Plot the data
plt.figure(figsize=(10, 5))
plt.plot(rpm_values, r_is_values, label='R_IS', marker='o')
plt.xlabel('RPM')
plt.ylabel('R_IS Value')
plt.title('RPM vs R_IS Plot')
plt.legend()
plt.grid(True)
plt.show()
