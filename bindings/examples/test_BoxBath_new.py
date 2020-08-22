import os
import numpy as np
import pyflex
import time


def rand_float(lo, hi):
    return np.random.rand() * (hi - lo) + lo


time_step = 600
des_dir = 'test_BoxBath_new'
os.system('mkdir -p ' + des_dir)


pyflex.init()

scene_params = np.array([])
pyflex.set_scene(9, scene_params, 0)

print("Scene Upper:", pyflex.get_scene_upper())
print("Scene Lower:", pyflex.get_scene_lower())

# particle_pos = pyflex.get_positions()
# print(particle_pos)
# print(particle_pos.shape)

# new_pos = particle_pos.reshape((135,4))
# new_pos[134,0] = 1
# new_pos = new_pos.reshape((135*4,))

# pyflex.set_positions(new_pos)

# pos = np.ones((135,4))
# pos[:,0:3] = pos[:,0:3] * 10
# pos[0,0:3] = np.array([0.0, 0.0, 0.0])

# print(pos)

for i in range(time_step):
    # pos[0,0] = 0.005*i
    # pyflex.set_positions(pos)
    pyflex.step(capture=0, path=os.path.join(des_dir, 'render_%d.tga' % i))
    # pyflex.render(capture=0, path=os.path.join(des_dir, 'render_%d.tga' % i))
    # print("Num particles:", pyflex.get_n_particles())

# particle_pos = pyflex.get_positions()
# print(particle_pos)
# print(particle_pos.shape)

pyflex.clean()
