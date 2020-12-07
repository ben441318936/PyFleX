import os
import numpy as np
import pyflex
import time


def rand_float(lo, hi):
    return np.random.rand() * (hi - lo) + lo

exp = "exp800"
time_step = 400
num_particles = 2000

scale = 10

particle_path_prefix = "/home/jingbin/Documents/Github/PBF3D_taichi/viz_results/3D/new_MPC/{}/particles/".format(exp)   
tool_path_prefix = "/home/jingbin/Documents/Github/PBF3D_taichi/viz_results/3D/new_MPC/{}/tool/".format(exp)

des_dir = "test_Custom_{}".format(exp)
os.system('mkdir -p ' + des_dir)


pyflex.init()

# Scene params
# params[0] -> radius
# params[1] -> scale
# params[2] -> max number of particles
# params[3,4,5] -> lower limit of scene box
# params[6,7,8] -> upper limit of scene box
# params[9,10,11,12] -> fluid color
# params[13] -> draw options, 0 = particles, 1 = fluid render
scene_params = np.array([0.1, 
                         scale,
                         num_particles,
                         0.0, 0.0, 0.0,
                         10, 10, 8.2,
                         1.0, 0.0, 0.0, 1.0,
                         1.0])
pyflex.set_scene(11, scene_params, 0)

print("Scene Upper:", pyflex.get_scene_upper())
print("Scene Lower:", pyflex.get_scene_lower())

pos = np.ones((num_particles,4))

# Set all the particles to unseen locations
def clear_pos():
    pos[:,0:3] = np.ones((num_particles,3)) * 20

# Function for putting particle positions into the array
def load_pos(particles):
    print(particles.shape[0])
    for i in range(particles.shape[0]):
        if i < num_particles and particles[i,1] < 3/scale:
            pos[i,0:3] = particles[i,0:3]

# # Load in the particles
# path = particle_path_prefix+"frame_{}.npy".format(599)
# particles = np.load(path)
# load_pos(particles)
# pyflex.set_positions(pos)

for i in range(time_step):
    # Load in the particles
    path = particle_path_prefix+"frame_{}.npy".format(i)
    particles = np.load(path) / scale
    clear_pos()
    load_pos(particles)
    pyflex.set_positions(pos)
    # pos[0] = np.array([i/100, 0.3, i/100, 1])
    # pyflex.set_positions(pos)
    # pos = pyflex.get_positions()
    # print(pos)
    # pyflex.step(capture=1, path=os.path.join(des_dir, "render_%04d.tga" % i))
    # if i == 200:
    path = tool_path_prefix+"frame_{}.npy".format(i)
    tool = np.load(path)
        # print(tool)
        # break
    states = pyflex.get_shape_states()
    # # print(states)
    states[17] = (tool[0]+0.5) / scale
    states[18] = tool[1] / scale + 0.15
    states[19] = tool[2] / scale
    pyflex.set_shape_states(states)
    pyflex.render(capture=1, path=os.path.join(des_dir, "render_%04d.tga" % i))
    

pyflex.clean()
