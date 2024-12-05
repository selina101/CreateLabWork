from comms_wrapper import * 
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
import random

rows, cols = 6, 11
names = {f"value_{i}_{j}": 0 for i in range(rows) for j in range(cols)}

arduino1 = Arduino(descriptiveDeviceName="myArduino", portName="COM8", baudrate=9600)
arduino1.connect_and_handshake()

fig, ax = plt.subplots(figsize=(8, 4))
plt.xticks(range(cols), [f'Col {i}' for i in range(cols)])
plt.yticks(range(rows), [f'Row {i}' for i in range(rows)])
plt.grid(visible=False)  # Hide grid lines if unwanted
plt.title('6x11 Value Grid')
values = np.random.randint(0, 1024, (rows, cols))
data=values/1023
image = ax.imshow(data, cmap='viridis', interpolation='nearest')


def update_values(frame):
    
    arduino1.receive_message()
    if arduino1.newMsgReceived:
        data=arduino1.receivedMessages
        values = np.array([int(value) for value in data.values()])
        values=values.reshape((6, 11))
        print(f'numeric_values= {values}')
        normalized_values = values / 1023
    # data = np.random.randint(0, 1024, (rows, cols))
    # data=data/1023
    # plt.imshow(data, cmap='viridis', interpolation='nearest')  # Use a colormap
        image.set_array(normalized_values)  # Update the image data
    return [image]

ani = FuncAnimation(fig, update_values, interval=1, blit=True)

plt.imshow(data, cmap='viridis', interpolation='nearest')  # Use a colormap
plt.show()







# # from comms_wrapper import * 
# # import matplotlib.pyplot as plt
# # import numpy as np
# # #from matplotlib.animation import FuncAnimation


# # rows, cols = 6, 11
# # names = {f"value_{i}_{j}": 0 for i in range(rows) for j in range(cols)}


# # arduino1 = Arduino(descriptiveDeviceName="myArduino", portName="COM8", baudrate=9600)

# # arduino1.connect_and_handshake()

# # while 1: 
# #     arduino1.receive_message()
# #     if arduino1.newMsgReceived:

# #         data=arduino1.receivedMessages
# #         # print(f'data= {data}')
        
# #         values = np.array([int(value) for value in data.values()])
# #         values=values.reshape((6, 11))
# #         print(f'numeric_values= {values}')

# #         normalized_values = values / 1023

# #         print(np.shape(normalized_values))
# #         plt.figure(figsize=(8, 4))  # Set the figure size
# #         plt.imshow(normalized_values, cmap='viridis', interpolation='nearest')  # Use a colormap

# #         # Add a color bar to show value mapping
# #         cbar = plt.colorbar()
# #         cbar.set_label('Value (0 to 1023)', rotation=270, labelpad=15)

# #         # Add gridlines and labels
# #         plt.xticks(range(cols), [f'Col {i}' for i in range(cols)])
# #         plt.yticks(range(rows), [f'Row {i}' for i in range(rows)])
# #         plt.grid(visible=False)  # Hide grid lines if unwanted
# #         plt.title('6x11 Value Grid')

# #         # Show the plot
# #         plt.show()
                
