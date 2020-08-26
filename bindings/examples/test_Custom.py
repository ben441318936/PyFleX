import os
import numpy as np
import pyflex
import time


def rand_float(lo, hi):
    return np.random.rand() * (hi - lo) + lo

exp = "exp36"
time_step = 400
num_particles = 2700

scale = 5

particle_path_prefix = "/home/jingbin/Documents/Github/PBF3D_taichi/viz_results/3D/new_MPC/{}/particles/".format(exp)    

des_dir = "test_Custom_{}".format(exp)
os.system('mkdir -p ' + des_dir)


pyflex.init()

# Scene params
# params[0] -> radius
# params[1] -> max number of particles
# params[2,3,4] -> lower limit of scene box
# params[5,6,7] -> upper limit of scene box
# params[8,9,10,11] -> fluid color
# params[12] -> draw options, 0 = particles, 1 = fluid render
scene_params = np.array([0.2, 
                         num_particles,
                         0.0, 0.0, 0.0,
                         15/scale, 20/scale, 15/scale,
                         1.0, 0.0, 0.0, 1.0,
                         1.0])
pyflex.set_scene(10, scene_params, 0)

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
        if i < num_particles:
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
    # pyflex.step(capture=1, path=os.path.join(des_dir, "render_%04d.tga" % i))
    pyflex.render(capture=1, path=os.path.join(des_dir, "render_%04d.tga" % i))


pyflex.clean()
