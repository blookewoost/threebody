import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D

# Read the CSV file
df = pd.read_csv('data/results.csv')

# Extract time and positions
time = df['time']
body1_x = df['body1_x']
body1_y = df['body1_y']
body1_z = df['body1_z']
body2_x = df['body2_x']
body2_y = df['body2_y']
body2_z = df['body2_z']
body3_x = df['body3_x']
body3_y = df['body3_y']
body3_z = df['body3_z']

# Set up the figure, axis, and plot elements
fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim(-2e11, 2e11)
ax.set_ylim(-2e11, 2e11)
ax.set_zlim(-2e11, 2e11)
ax.set_xlabel('x position (m)')
ax.set_ylabel('y position (m)')
ax.set_zlabel('z position (m)')
ax.set_title('Three-Body Simulation')
ax.grid(True)

# Initialize the plot elements
line1, = ax.plot([], [], [], 'ro', label='Body 1')
line2, = ax.plot([], [], [], 'go', label='Body 2')
line3, = ax.plot([], [], [], 'bo', label='Body 3')
trail1, = ax.plot([], [], [], 'r.', markersize=2)
trail2, = ax.plot([], [], [], 'g.', markersize=2)
trail3, = ax.plot([], [], [], 'b.', markersize=2)

# Initialization function
def init():
    line1.set_data([], [])
    line1.set_3d_properties([])
    line2.set_data([], [])
    line2.set_3d_properties([])
    line3.set_data([], [])
    line3.set_3d_properties([])
    trail1.set_data([], [])
    trail1.set_3d_properties([])
    trail2.set_data([], [])
    trail2.set_3d_properties([])
    trail3.set_data([], [])
    trail3.set_3d_properties([])
    return line1, line2, line3, trail1, trail2, trail3

# Animation function
def animate(i):
    # Update the positions
    line1.set_data(body1_x[i], body1_y[i])
    line1.set_3d_properties(body1_z[i])
    line2.set_data(body2_x[i], body2_y[i])
    line2.set_3d_properties(body2_z[i])
    line3.set_data(body3_x[i], body3_y[i])
    line3.set_3d_properties(body3_z[i])

    # Update the trails
    trail1.set_data(body1_x[:i], body1_y[:i])
    trail1.set_3d_properties(body1_z[:i])
    trail2.set_data(body2_x[:i], body2_y[:i])
    trail2.set_3d_properties(body2_z[:i])
    trail3.set_data(body3_x[:i], body3_y[:i])
    trail3.set_3d_properties(body3_z[:i])

    return line1, line2, line3, trail1, trail2, trail3

# Create the animation
ani = animation.FuncAnimation(fig, animate, init_func=init, frames=len(time), interval=20, blit=True)

plt.legend()
plt.show()
