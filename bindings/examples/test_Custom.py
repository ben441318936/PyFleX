import os
import numpy as np
import pyflex
import time


def rand_float(lo, hi):
    return np.random.rand() * (hi - lo) + lo


time_step = 150
des_dir = 'test_Custom'
os.system('mkdir -p ' + des_dir)


pyflex.init()

# Scene params
# params[0] -> radius
# params[1] -> max number of particles
# params[2,3,4] -> lower limit of scene box
# params[5,6,7] -> upper limit of scene box
# params[8,9,10,11] -> fluid color
# params[12] -> draw options, 0 = particles, 1 = fluid render
scene_params = np.array([0.3, 
                         100.0,
                         0.0, 0.0, 0.0,
                         15.0, 20.0, 15.0,
                         1.0, 1.0, 1.0, 1.0,
                         1.0])
pyflex.set_scene(10, scene_params, 0)

print("Scene Upper:", pyflex.get_scene_upper())
print("Scene Lower:", pyflex.get_scene_lower())

# particle_pos = pyflex.get_positions()
# print(particle_pos)
# print(particle_pos.shape)

# new_pos = particle_pos.reshape((135,4))
# new_pos[134,0] = 1
# new_pos = new_pos.reshape((135*4,))

# pyflex.set_positions(new_pos)

pos = np.ones((135,4))
pos[:,0:3] = pos[:,0:3] * 10
pos[0,0:3] = np.array([0.0, 0.0, 0.0])
pos[1,0:3] = np.array([0.0, 0.0, 0.0])

# print(pos)

for i in range(time_step):
    pos[0,0] = 0.005*i
    pos[1,0] = 0.005*i
    pos[1,1] = 0.005*i
    pyflex.set_positions(pos)
    # pyflex.step(capture=0, path=os.path.join(des_dir, 'render_%d.tga' % i))
    pyflex.render(capture=0, path=os.path.join(des_dir, 'render_%d.tga' % i))
    # print("Num particles:", pyflex.get_n_particles())

# particle_pos = pyflex.get_positions()
# print(particle_pos)
# print(particle_pos.shape)

pyflex.clean()
