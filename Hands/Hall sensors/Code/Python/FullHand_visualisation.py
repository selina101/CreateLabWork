import numpy as np
from comms_wrapper import *
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.animation import FuncAnimation

image_path = 'hand.png'  # Replace with your image path
img = Image.open(image_path)

# Convert the image to a format suitable for displaying with Matplotlib
img_array = np.array(img)

# Create a figure and axis
fig, ax = plt.subplots()

# Display the image
ax.imshow(img_array)

radius = 50  # Replace with the desired radius

# Create a circle patch
Th_T = patches.Circle((517, 345), radius, edgecolor='red', facecolor='none', linewidth=2)
Th_L = patches.Circle((500, 372), radius, edgecolor='green', facecolor='none', linewidth=2)
Th_R = patches.Circle((474, 340), radius, edgecolor='blue', facecolor='none', linewidth=2)

Idx_T = patches.Circle((387, 83), radius, edgecolor='red', facecolor='none', linewidth=2)
Idx_L = patches.Circle((390, 146), radius, edgecolor='green', facecolor='none', linewidth=2)
Idx_R = patches.Circle((353, 126), radius, edgecolor='blue', facecolor='none', linewidth=2)

Midd_T = patches.Circle((235, 33), radius, edgecolor='red', facecolor='none', linewidth=2)
Midd_L = patches.Circle((262, 76), radius, edgecolor='green', facecolor='none', linewidth=2)
Midd_R = patches.Circle((218, 78), radius, edgecolor='blue', facecolor='none', linewidth=2)

Ring_T = patches.Circle((121, 63), radius, edgecolor='red', facecolor='none', linewidth=2)
Ring_L = patches.Circle((155, 85), radius, edgecolor='green', facecolor='none', linewidth=2)
Ring_R = patches.Circle((108, 95), radius, edgecolor='blue', facecolor='none', linewidth=2)

Pinky_T = patches.Circle((25, 171), radius, edgecolor='red', facecolor='none', linewidth=2)
Pinky_L = patches.Circle((60, 196), radius, edgecolor='green', facecolor='none', linewidth=2)
Pinky_R = patches.Circle((23, 218), radius, edgecolor='blue', facecolor='none', linewidth=2)

# Add the circle to the plot
ax.add_patch(Th_T)
ax.add_patch(Th_L)
ax.add_patch(Th_R)

ax.add_patch(Idx_T)
ax.add_patch(Idx_L)
ax.add_patch(Idx_R)

ax.add_patch(Midd_T)
ax.add_patch(Midd_L)
ax.add_patch(Midd_R)

ax.add_patch(Ring_T)
ax.add_patch(Ring_L)
ax.add_patch(Ring_R)

ax.add_patch(Pinky_T)
ax.add_patch(Pinky_L)
ax.add_patch(Pinky_R)




# exit()

data_names={"Th_Dist_L_X", "Th_Dist_R_X", "Th_Dist_T_X", "Idx_Dist_L_X", "Idx_Dist_R_X", "Idx_Dist_T_X", "Midd_Dist_L_X", "Midd_Dist_R_X", "Midd_Dist_T_X","Midd_Midd_L_X", "Midd_Midd_R_X", "Ring_Dist_L_X", "Ring_Dist_R_X", "Ring_Dist_T_X", "Pinky_Dist_L_X", "Pinky_Dist_R_X", "Pinky_Dist_T_X"}

arduino1 = Arduino(descriptiveDeviceName="myArduino", portName="COM9", baudrate=9600)
arduino1.connect_and_handshake()

# data = [[] for _ in range(21)]
def update_radius(frame):

    arduino1.receive_message()
    arduino1.debug()
    if arduino1.newMsgReceived:
        data=arduino1.receivedMessages
        # print(f'data= {data}')
        
        Dist_Thumb=(np.array([data["Th_Dist_L_X"],data["Th_Dist_R_X"],data["Th_Dist_T_X"]])).astype(float)
        print(f'Dist_Thumb= {Dist_Thumb}')

        Dist_Index=(np.array([data["Idx_Dist_L_X"],data["Idx_Dist_R_X"],data["Idx_Dist_T_X"]])).astype(float)
        print(f'Dist_Index= {Dist_Index}')

        Dist_Middle=(np.array([data["Midd_Dist_L_X"],data["Midd_Dist_R_X"],data["Midd_Dist_T_X"]])).astype(float)
        print(f'Dist_Middle= {Dist_Middle}')

        Dist_Ring=(np.array([data["Ring_Dist_L_X"],data["Ring_Dist_R_X"],data["Ring_Dist_T_X"]])).astype(float)
        print(f'Dist_Ring= {Dist_Ring}')

        Dist_Pinky=(np.array([data["Pinky_Dist_L_X"],data["Pinky_Dist_R_X"],data["Pinky_Dist_T_X"]])).astype(float)
        print(f'Dist_Pinky= {Dist_Pinky}')
    # Here, 'frame' will be replaced by data coming from the microcontroller.
    # For demonstration, let's use a sinusoidal function to simulate data changes.
        # new_radius = radius + 20 * np.sin(frame * 0.1)
        
        # Update the circle radius
        coeff=2
        Th_T.set_radius(abs(Dist_Thumb[2])*coeff)
        Th_L.set_radius(abs(Dist_Thumb[0])*coeff)
        Th_R.set_radius(abs(Dist_Thumb[1])*coeff)

        Idx_T.set_radius(abs(Dist_Index[2])*coeff)
        Idx_L.set_radius(abs(Dist_Index[0])*coeff)
        Idx_R.set_radius(abs(Dist_Index[1])*coeff)

        Midd_T.set_radius(abs(Dist_Middle[2])*coeff)
        Midd_L.set_radius(abs(Dist_Middle[0])*coeff)
        Midd_R.set_radius(abs(Dist_Middle[1])*coeff)

        Ring_T.set_radius(abs(Dist_Ring[2])*coeff)
        Ring_L.set_radius(abs(Dist_Ring[0])*coeff)
        Ring_R.set_radius(abs(Dist_Ring[1])*coeff)
        
        Pinky_T.set_radius(abs(Dist_Pinky[2])*coeff)
        Pinky_L.set_radius(abs(Dist_Pinky[0])*coeff)
        Pinky_R.set_radius(abs(Dist_Pinky[1])*coeff)

    return Th_T,Th_L,Th_R,Idx_T,Idx_L,Idx_R,Midd_T,Midd_L,Midd_R,Ring_T,Ring_L,Ring_R,Pinky_T,Pinky_L,Pinky_R,

ani = FuncAnimation(fig, update_radius, frames=np.arange(0, 10, 0.1), interval=50, blit=True)


plt.show()

        
    # arduino1.debug()

# import numpy as np
# from comms_wrapper import *
# from PIL import Image
# import matplotlib.pyplot as plt
# import matplotlib.patches as patches
# from matplotlib.animation import FuncAnimation

# image_path = 'hand.png'  # Replace with your image path
# img = Image.open(image_path)

# # Convert the image to a format suitable for displaying with Matplotlib
# img_array = np.array(img)

# # Create a figure and axis
# fig, ax = plt.subplots()

# # Display the image
# ax.imshow(img_array)

# radius = 50  # Replace with the desired radius

# # Create a circle patch
# Th_T = patches.Circle((517, 345), radius, edgecolor='red', facecolor='none', linewidth=2)
# Th_L = patches.Circle((500, 372), radius, edgecolor='green', facecolor='none', linewidth=2)
# Th_R = patches.Circle((474, 340), radius, edgecolor='blue', facecolor='none', linewidth=2)

# Idx_T = patches.Circle((387, 83), radius, edgecolor='red', facecolor='none', linewidth=2)
# Idx_L = patches.Circle((390, 146), radius, edgecolor='green', facecolor='none', linewidth=2)
# Idx_R = patches.Circle((353, 126), radius, edgecolor='blue', facecolor='none', linewidth=2)

# Midd_T = patches.Circle((235, 33), radius, edgecolor='red', facecolor='none', linewidth=2)
# Midd_L = patches.Circle((262, 76), radius, edgecolor='green', facecolor='none', linewidth=2)
# Midd_R = patches.Circle((218, 78), radius, edgecolor='blue', facecolor='none', linewidth=2)
# MiddM_L = patches.Circle((262, 155), radius, edgecolor='green', facecolor='none', linewidth=2)
# MiddM_R = patches.Circle((223, 151), radius, edgecolor='blue', facecolor='none', linewidth=2)

# Ring_T = patches.Circle((121, 63), radius, edgecolor='red', facecolor='none', linewidth=2)
# Ring_L = patches.Circle((155, 85), radius, edgecolor='green', facecolor='none', linewidth=2)
# Ring_R = patches.Circle((108, 95), radius, edgecolor='blue', facecolor='none', linewidth=2)

# Pinky_T = patches.Circle((25, 171), radius, edgecolor='red', facecolor='none', linewidth=2)
# Pinky_L = patches.Circle((60, 196), radius, edgecolor='green', facecolor='none', linewidth=2)
# Pinky_R = patches.Circle((23, 218), radius, edgecolor='blue', facecolor='none', linewidth=2)

# # Add the circle to the plot
# ax.add_patch(Th_T)
# ax.add_patch(Th_L)
# ax.add_patch(Th_R)

# ax.add_patch(Idx_T)
# ax.add_patch(Idx_L)
# ax.add_patch(Idx_R)

# ax.add_patch(Midd_T)
# ax.add_patch(Midd_L)
# ax.add_patch(Midd_R)
# ax.add_patch(MiddM_L)
# ax.add_patch(MiddM_R)

# ax.add_patch(Ring_T)
# ax.add_patch(Ring_L)
# ax.add_patch(Ring_R)

# ax.add_patch(Pinky_T)
# ax.add_patch(Pinky_L)
# ax.add_patch(Pinky_R)

# # time_now=time.time()
# # time_previous=time.time()


# # exit()

# data_names={"Th_Dist_L_X", "Th_Dist_R_X", "Th_Dist_T_X", "Idx_Dist_L_X", "Idx_Dist_R_X", "Idx_Dist_T_X", "Midd_Dist_L_X", "Midd_Dist_R_X", "Midd_Dist_T_X", "Midd_Midd_L_X", "Midd_Midd_R_X", "Ring_Dist_L_X", "Ring_Dist_R_X", "Ring_Dist_T_X", "Pinky_Dist_L_X", "Pinky_Dist_R_X", "Pinky_Dist_T_X"}

# arduino1 = Arduino(descriptiveDeviceName="myArduino", portName="COM9", baudrate=9600)
# arduino1.connect_and_handshake()

# # data = [[] for _ in range(21)]
# def update_radius(frame):

#     arduino1.receive_message()
#     # arduino1.debug()
#     if arduino1.newMsgReceived:
#         time_now=time.time()
#         # print(f'time diff= {time_now-time_previous}')
#         data=arduino1.receivedMessages
#         # print(f'data= {data}')
        
#         Dist_Thumb=(np.array([data["Th_Dist_L_X"],data["Th_Dist_R_X"],data["Th_Dist_T_X"]])).astype(float)
#         print(f'Dist_Thumb= {Dist_Thumb}')

#         Dist_Index=(np.array([data["Idx_Dist_L_X"],data["Idx_Dist_R_X"],data["Idx_Dist_T_X"]])).astype(float)
#         print(f'Dist_Index= {Dist_Index}')

#         Dist_Middle=(np.array([data["Midd_Dist_L_X"],data["Midd_Dist_R_X"],data["Midd_Dist_T_X"]])).astype(float)
#         print(f'Dist_Middle= {Dist_Middle}')

#         Midd_Middle=(np.array([data["Midd_Midd_L_X"],data["Midd_Midd_R_X"]])).astype(float)
#         print(f'Dist_Middle= {Dist_Middle}')
#         print(f'Midd_Middle= {Midd_Middle}')

#         Dist_Ring=(np.array([data["Ring_Dist_L_X"],data["Ring_Dist_R_X"],data["Ring_Dist_T_X"]])).astype(float)
#         print(f'Dist_Ring= {Dist_Ring}')

#         Dist_Pinky=(np.array([data["Pinky_Dist_L_X"],data["Pinky_Dist_R_X"],data["Pinky_Dist_T_X"]])).astype(float)
#         print(f'Dist_Pinky= {Dist_Pinky}')
#     # Here, 'frame' will be replaced by data coming from the microcontroller.
#     # For demonstration, let's use a sinusoidal function to simulate data changes.
#         # new_radius = radius + 20 * np.sin(frame * 0.1)
        
#         # Update the circle radius
#         coeff=2
#         Th_T.set_radius(abs(Dist_Thumb[2])*coeff)
#         Th_L.set_radius(abs(Dist_Thumb[0])*coeff)
#         Th_R.set_radius(abs(Dist_Thumb[1])*coeff)

#         Idx_T.set_radius(abs(Dist_Index[2])*coeff)
#         Idx_L.set_radius(abs(Dist_Index[0])*coeff)
#         Idx_R.set_radius(abs(Dist_Index[1])*coeff)

#         Midd_T.set_radius(abs(Dist_Middle[2])*coeff)
#         Midd_L.set_radius(abs(Dist_Middle[0])*coeff)
#         Midd_R.set_radius(abs(Dist_Middle[1])*coeff)

#         MiddM_L.set_radius(abs(Midd_Middle[0])*coeff)
#         MiddM_R.set_radius(abs(Midd_Middle[1])*coeff)

#         Ring_T.set_radius(abs(Dist_Ring[2])*coeff)
#         Ring_L.set_radius(abs(Dist_Ring[0])*coeff)
#         Ring_R.set_radius(abs(Dist_Ring[1])*coeff)
        
#         Pinky_T.set_radius(abs(Dist_Pinky[2])*coeff)
#         Pinky_L.set_radius(abs(Dist_Pinky[0])*coeff)
#         Pinky_R.set_radius(abs(Dist_Pinky[1])*coeff)
#         # time_previous=time_now

#     return Th_T,Th_L,Th_R,Idx_T,Idx_L,Idx_R,Midd_T,Midd_L,Midd_R,MiddM_L,MiddM_R,Ring_T,Ring_L,Ring_R,Pinky_T,Pinky_L,Pinky_R,

# ani = FuncAnimation(fig, update_radius, frames=np.arange(0, 10, 0.1), interval=50, blit=True)


# plt.show()

# # while True:
# #     arduino1.receive_message()
# #     if arduino1.newMsgReceived:
# #         data=arduino1.receivedMessages
# #         # print(f'data= {data}')
        
# #         Dist_Thumb=(np.array([data["Th_Dist_L_X"],data["Th_Dist_R_X"],data["Th_Dist_T_X"]])).astype(float)
# #         print(f'Dist_Thumb= {Dist_Thumb}')

# #         Dist_Index=(np.array([data["Idx_Dist_L_X"],data["Idx_Dist_R_X"],data["Idx_Dist_T_X"]])).astype(float)
# #         print(f'Dist_Index= {Dist_Index}')

# #         Dist_Middle=(np.array([data["Midd_Dist_L_X"],data["Midd_Dist_R_X"],data["Midd_Dist_T_X"]])).astype(float)
# #         print(f'Dist_Middle= {Dist_Middle}')

# #         Dist_Ring=(np.array([data["Ring_Dist_L_X"],data["Ring_Dist_R_X"],data["Ring_Dist_T_X"]])).astype(float)
# #         print(f'Dist_Ring= {Dist_Ring}')

# #         Dist_Pinky=(np.array([data["Pinky_Dist_L_X"],data["Pinky_Dist_R_X"],data["Pinky_Dist_T_X"]])).astype(float)
# #         print(f'Dist_Pinky= {Dist_Pinky}')

        
# #     # arduino1.debug()

