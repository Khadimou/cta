import matplotlib.pyplot as plt
from astropy import units as u
import numpy as np
import ctaplot
import tables
from tables import *


# retrieve parameter values from the tree file
with open_file("threeNeighbors.h5", "r", driver="H5FD_CORE") as f:
    E = f.root.Tree.common.read(field="energy")
    Ro = f.root.Tree.common.read(field="impact")
    Imax = f.root.Tree.common.read(field="Imax")
    Alpha = f.root.Tree.common.read(field="alpha")
    H = f.root.Tree.common.read(field="hfirstint")
    distance = f.root.Tree.common.read(field="distance_mean")

# Erreur relative sur l'energie
deltaE = (E[:,0] - E[:,1])/E[:,0]
maskE = (deltaE*u.TeV)[distance<0.01]
print(len(maskE))
ctaplot.plots.plots.plot_energy_resolution(maskE,(E[:,0]*u.TeV)[distance<0.01])
plt.show()