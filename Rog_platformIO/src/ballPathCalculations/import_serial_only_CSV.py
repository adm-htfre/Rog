import serial
import csv
import time

# Replace 'COM12' with your serial port
ser = serial.Serial('COM12', 9600, timeout=1)

# Open a CSV file for writing
with open('Try5.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(['RPM', 'R_IS'])  # Write the header

    buffer = []
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

                        # Write to CSV
                        csvwriter.writerow([rpm, r_is])
                    except (IndexError, ValueError) as e:
                        print(f"Error parsing lines: {rpm_line}, {r_is_line} - {e}")
                    
                    # Clear the buffer for next set of lines
                    buffer.clear()

        time.sleep(0.1)  # Small delay