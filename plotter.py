import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Read the CSV file
df = pd.read_csv('three_body_simulation.csv')

# Extract time and positions
time = df['time']
body1_x = df['body1_x']
body1_y = df['body1_y']
body2_x = df['body2_x']
body2_y = df['body2_y']
body3_x = df['body3_x']
body3_y = df['body3_y']

# Set up the figure, axis, and plot elements
fig, ax = plt.subplots(figsize=(10, 10))
ax.set_xlim(-2e11, 2e11)
ax.set_ylim(-2e11, 2e11)
ax.set_xlabel('x position (m)')
ax.set_ylabel('y position (m)')
ax.set_title('Three-Body Simulation')
ax.grid(True)
ax.set_aspect('equal')

line1, = ax.plot([], [], 'ro', label='Body 1')
line2, = ax.plot([], [], 'go', label='Body 2')
line3, = ax.plot([], [], 'bo', label='Body 3')

# Initialization function
def init():
    line1.set_data([], [])
    line2.set_data([], [])
    line3.set_data([], [])
    return line1, line2, line3

# Animation function
def animate(i):
    line1.set_data(body1_x[i], body1_y[i])
    line2.set_data(body2_x[i], body2_y[i])
    line3.set_data(body3_x[i], body3_y[i])
    return line1, line2, line3

# Create the animation
ani = animation.FuncAnimation(fig, animate, init_func=init, frames=len(time), interval=20, blit=True)

# Save the animation as a video file
#Writer = animation.writers['ffmpeg']
#writer = Writer(fps=30, metadata=dict(artist='Me'), bitrate=1800)
#ani.save('three_body_simulation.mp4', writer=writer)

plt.legend()
plt.show()
