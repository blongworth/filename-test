import serial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyACM0', 9600)  # Replace with your Arduino's serial port and baud rate
plt.ion()  # Turn on interactive mode

x_data = []
y_data = []

output_file = open("sd_write_stats.txt", "w")  # Open a file for writing
with open("sd_write_stats.txt", "w") as output_file:
    try:
        while True:
            line = ser.readline().decode('utf-8').strip()
            if ',' in line:
                y, x = map(int, line.split(','))  # Assuming x and y are ints
                x_data.append(x)
                y_data.append(y)
                plt.scatter(x, y, c='blue')
                plt.pause(0.1)
                output_file.write(f"{x},{y}\n")
    except KeyboardInterrupt:
        ser.close()
        plt.ioff()
        plt.show()
