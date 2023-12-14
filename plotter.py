import serial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyACM0', 9600)  # Replace with your Arduino's serial port and baud rate
plt.ion()  # Turn on interactive mode

x_data = []
y_data = []

try:
    while True:
        line = ser.readline().decode('utf-8').strip()
        if ',' in line:
            y, x = map(int, line.split(','))  # Assuming x and y are ints
            x_data.append(x)
            y_data.append(y)
            plt.scatter(x, y)
            plt.pause(0.1)
except KeyboardInterrupt:
    ser.close()
    plt.ioff()
    plt.show()
