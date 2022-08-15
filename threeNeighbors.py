from sklearn.neighbors import KDTree
import tables
from tables import *
import numpy as np
import glob
import tqdm
import os
import matplotlib.pyplot as plt
import re
import pandas as pd

# store common events (between tree id and event id) parameters values in h5 file
class commonEvents(IsDescription):
    idevent = UInt64Col(shape=3)
    energy = Float32Col(shape=3)
    hfirstint = Float32Col(shape=3)
    Imax = Float32Col(shape=3)
    impact = Float32Col(shape=3)
    alpha = Float32Col(shape=3)
    distances = Float32Col(shape=3)
    distance_mean = Float32Col()
    distance_std = Float32Col()

def write_file(E, Imax, ro, h, alpha, events, distances, distance_mean, distance_std, outputfile):
    h5file = open_file(outputfile, mode="w", title = "Common events parameters with the tree")

    #create a group
    group1 = h5file.create_group("/","Tree","Train Data Tree Info")
    #create a table
    table1 = h5file.create_table(group1, "common", commonEvents, "common parameters")
    params = table1.row # write data rows into the table
    #print("energy\n",E)
    for i,event in enumerate(events):
        params["idevent"] = event
        params["hfirstint"] = h[i]
        params["Imax"] = Imax[i]
        params["impact"] = ro[i]
        params["alpha"] = alpha[i]
        params["energy"] = E[i]
        params["distances"] = distances[i]
        params["distance_mean"] = distance_mean[i]
        params["distance_std"] = distance_std[i]

        params.append()
    table1.flush()


    h5file.close()

# retrieve some parameter values from dataset
def get_param_values(fnames):
    #read 1 column
    with open_file(fnames, "r", driver="H5FD_CORE") as f:
        idevent = f.root.Shower.gerbe.read(field="idevent")
        E = f.root.Shower.gerbe.read(field="energy")
        h = f.root.Shower.gerbe.read(field="hfirstint")
        Imax = f.root.Shower.gerbe.read(field="Imax")
        alpha = f.root.Shower.gerbe.read(field="alpha")
        impact = f.root.Shower.gerbe.read(field="impact")
    d = {"idevent":idevent, "energy": E, "hfirstint":h, "Imax":Imax, "alpha":alpha, "impact":impact}

    return d

if __name__=='__main__':

    # get gerbe parameters values
    train_fnames = glob.glob('hash_training/*.h5', recursive=True)


    nb_neighbors = 3 + 1
    distance_mean = pd.read_hdf("neighbors_" + str(nb_neighbors) + ".h5")["distance_mean"]
    distance_std = pd.read_hdf("neighbors_" + str(nb_neighbors) + ".h5")["distance_std"]
    distance = pd.read_hdf("neighbors_" + str(nb_neighbors) + ".h5")["distance"]
    idevent_pos = pd.read_hdf("neighbors_" + str(nb_neighbors) + ".h5")["idevent"]

    #print(idevent_pos)
    frame = []
    # get parameter values associated for id events
    for input in train_fnames:
        my_dataframe = get_param_values(input)
        frame.append(pd.DataFrame(my_dataframe))
    frame = pd.concat([df.set_index('idevent') for df in frame], axis=0)

    frame["idevent"] = frame.index
    print("number of events ",len(frame["idevent"]))
    E = []
    Imax = []
    ro = []
    h = []
    alpha =[]
    for pos in idevent_pos:
        E.append( np.full([1, 3], [frame.iloc[pos[0]]["energy"], frame.iloc[pos[1]]["energy"], frame.iloc[pos[2]]["energy"]]))
        Imax.append(np.full([1, 3], [frame.iloc[pos[0]]["Imax"], frame.iloc[pos[1]]["Imax"], frame.iloc[pos[2]]["Imax"]]))
        ro.append(np.full([1, 3], [frame.iloc[pos[0]]["impact"], frame.iloc[pos[1]]["impact"], frame.iloc[pos[2]]["impact"]]))
        alpha.append(np.full([1, 3], [frame.iloc[pos[0]]["alpha"], frame.iloc[pos[1]]["alpha"], frame.iloc[pos[2]]["alpha"]]))
        h.append(np.full([1, 3], [frame.iloc[pos[0]]["hfirstint"], frame.iloc[pos[1]]["hfirstint"], frame.iloc[pos[2]]["hfirstint"]]))

    #print("Tree status ",tree.get_tree_stats())

    # energy = []
    # Imaxpar = []
    # impact = []
    # hfirstint = []
    # angle = []
    # for i in range(len(E)):
    #     for r in ro[i]:
    #         impact.append(r)
    #     for e in E[i]:
    #         energy.append(e)
    #     for intensity in Imax[i]:
    #         Imaxpar.append(intensity)
    #     for a in alpha[i]:
    #         angle.append(a)
    #     for height in h[i]:
    #         hfirstint.append(height)

    write_file(E, Imax, ro, h , alpha, idevent_pos, distance, distance_mean, distance_std, "threeNeighbors.h5")