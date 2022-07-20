import tables
from tables import *
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib
from matplotlib import animation
from mpl_toolkits.mplot3d import Axes3D

# retrieve parameter values from the tree file
with open_file("tree.h5", "r", driver="H5FD_CORE") as f:
    Etrain = f.root.Train.common.read(field="energy")
    Rotrain = f.root.Train.common.read(field="impact")    
    Imaxtrain = f.root.Train.common.read(field="Imax")                   
    Alphatrain = f.root.Train.common.read(field="alpha")
    Htrain = f.root.Train.common.read(field="hfirstint")
    Distancetrain = f.root.Train.common.read(field="distances")
    Etest = f.root.Test.common.read(field="energy")
    Rotest = f.root.Test.common.read(field="impact")    
    Imaxtest = f.root.Test.common.read(field="Imax")                   
    Alphatest = f.root.Test.common.read(field="alpha")
    Htest = f.root.Test.common.read(field="hfirstint")
    Distancetest = f.root.Test.common.read(field="distances")

# Erreur relative sur l'energie
deltaE = (Etest - Etrain[0:len(Etest)])/Etest
#print(deltaE)

# retrieve parameter values from the tree file
with open_file("TestDataProjection.h5", "r", driver="H5FD_CORE") as f:
    axeX = f.root.Test.projection.read(field="firstCol")
    axeY = f.root.Test.projection.read(field="secondCol")    
    axeZ = f.root.Test.projection.read(field="thirdCol") 

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")
# ax.scatter(axeX, axeY, axeZ, s=5)
# ax.set_xlabel('X axis')
# ax.set_ylabel('Y axis')
# ax.set_zlabel('Z axis')
def update(num, data, line):
    line.set_data(data[:2, :num])
    line.set_3d_properties(data[2, :num])

N = 3000000
data = np.array([axeX,axeY,axeZ])
line, = ax.plot(axeX, axeY, axeZ, linestyle="", marker="*")

# Setting the axes properties
#ax.set_xlim3d([0, 20000])
ax.set_xlabel('X')

#ax.set_ylim3d([-10000, 0])
ax.set_ylabel('Y')

#ax.set_zlim3d([0, 10000])
ax.set_zlabel('Z')

ani = animation.FuncAnimation(fig, update, N, fargs=(data, line), interval=10, blit=False)
ax.set_title('3D Animated Scatter Projection Space')
plt.show()

plt.hist2d(Distancetest, deltaE, bins=(30,30), norm=matplotlib.colors.LogNorm())
plt.colorbar()
# plt.scatter(Distancetrain, Etrain)
plt.xlabel("distances")
plt.ylabel("energy")
plt.yscale("log")
plt.title("Erreur relative des energies du training data et du testing data")
plt.grid()
plt.show()